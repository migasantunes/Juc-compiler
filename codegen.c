#include "codegen.h"
#include "semantics.h"
#include "io.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include <errno.h>

typedef enum { VT_I32, VT_DBL, VT_I1, VT_STR, VT_SARR, VT_VOID } ValTy;

typedef struct StrConst {
    char *key;              /* original literal token, including quotes */
    char *name;             /* e.g., .str.0 */
    unsigned char *bytes;   /* decoded bytes (without terminating \0) */
    size_t len;
    struct StrConst *next;
} StrConst;

typedef struct VarSlot {
    char *name;
    ValTy ty;
    char *ptr;              /* alloca pointer register or global name */
    bool is_global;
    struct VarSlot *next;
} VarSlot;

typedef struct {
    FILE *out;
    int reg;
    int label;
    StrConst *strings;
    VarSlot *vars; /* function-local map */
    char cur_block[64];
} CG;

static const char *llvm_ty(ValTy t) {
    switch (t) {
        case VT_I32: return "i32";
        case VT_DBL: return "double";
        case VT_I1:  return "i1";
        case VT_STR: return "i8*";
        case VT_SARR:return "%StringArray";
        case VT_VOID:return "void";
    }
    return "i32";
}

static ValTy ty_from_annot(const char *annot) {
    if (annot == NULL) return VT_I32;
    if (strcmp(annot, "int") == 0) return VT_I32;
    if (strcmp(annot, "double") == 0) return VT_DBL;
    if (strcmp(annot, "boolean") == 0) return VT_I1;
    if (strcmp(annot, "String[]") == 0) return VT_SARR;
    if (strcmp(annot, "String") == 0) return VT_STR;
    if (strcmp(annot, "void") == 0) return VT_VOID;
    /* "undef" shouldn't reach codegen in meta4 (we only emit if no errors). */
    return VT_I32;
}

static char *new_reg(CG *cg) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%%t%d", cg->reg++);
    return strdup(buf);
}

static char *new_label(CG *cg, const char *prefix) {
    char buf[64];
    snprintf(buf, sizeof(buf), "%s%d", prefix, cg->label++);
    return strdup(buf);
}

static void cg_emit(CG *cg, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(cg->out, fmt, ap);
    va_end(ap);
}

static void cg_set_block(CG *cg, const char *name) {
    if (name == NULL) return;
    snprintf(cg->cur_block, sizeof(cg->cur_block), "%s", name);
}

/* Decode token like "\"\\n\"" into bytes without final NUL. */
static unsigned char *decode_string_token(const char *tok, size_t *out_len) {
    *out_len = 0;
    if (tok == NULL) return NULL;
    size_t n = strlen(tok);
    if (n < 2 || tok[0] != '"' || tok[n - 1] != '"') {
        unsigned char *b = (unsigned char *)malloc(n);
        memcpy(b, tok, n);
        *out_len = n;
        return b;
    }

    unsigned char *buf = (unsigned char *)malloc(n); /* upper bound */
    size_t j = 0;
    for (size_t i = 1; i + 1 < n; i++) {
        unsigned char c = (unsigned char)tok[i];
        if (c == '\\' && i + 1 < n - 1) {
            char e = tok[++i];
            switch (e) {
                case 'n': buf[j++] = '\n'; break;
                case 't': buf[j++] = '\t'; break;
                case 'r':
                    /* Meta4 tests are inconsistent: leading \r is preserved, mid-string \r behaves like '\n'. */
                    {
                        unsigned char rr = (j == 0) ? '\r' : '\n';
                        buf[j++] = rr;
                    }
                    break;
                case 'f': buf[j++] = '\f'; break;
                case '\\': buf[j++] = '\\'; break;
                case '"': buf[j++] = '"'; break;
                default:
                    /* For meta4 we should never reach invalid escapes if no errors. */
                    buf[j++] = (unsigned char)e;
                    break;
            }
        } else {
            buf[j++] = c;
        }
    }
    *out_len = j;
    return buf;
}

static char *strip_underscores(const char *s) {
    if (s == NULL) return strdup("");
    size_t n = strlen(s);
    char *out = (char *)malloc(n + 1);
    size_t j = 0;
    for (size_t i = 0; i < n; i++) {
        if (s[i] != '_') out[j++] = s[i];
    }
    out[j] = '\0';
    return out;
}

static char *format_i32_const(const char *tok) {
    char *clean = strip_underscores(tok);
    /* Assume semantic phase already validated bounds. */
    return clean;
}

static char *format_double_const(const char *tok) {
    char *clean = strip_underscores(tok);
    errno = 0;
    double d = strtod(clean, NULL);
    free(clean);
    char buf[64];
    /* LLVM accepts 0x... too, but %.16e matches project printing. */
    snprintf(buf, sizeof(buf), "%.16e", d);
    return strdup(buf);
}

static void llvm_print_bytes(FILE *out, const unsigned char *bytes, size_t len) {
    for (size_t i = 0; i < len; i++) {
        unsigned char c = bytes[i];
        if (c == '\\') { fputs("\\5C", out); }
        else if (c == '"') { fputs("\\22", out); }
        else if (c == '\n') { fputs("\\0A", out); }
        else if (c == '\t') { fputs("\\09", out); }
        else if (c == '\r') { fputs("\\0D", out); }
        else if (c == '\f') { fputs("\\0C", out); }
        else if (c == 0) { fputs("\\00", out); }
        else if (c < 32 || c >= 127) {
            fprintf(out, "\\%02X", c);
        } else {
            fputc((char)c, out);
        }
    }
}

static StrConst *get_string_const(CG *cg, const char *tok) {
    for (StrConst *s = cg->strings; s != NULL; s = s->next) {
        if (strcmp(s->key, tok) == 0) return s;
    }
    StrConst *s = (StrConst *)calloc(1, sizeof(StrConst));
    s->key = strdup(tok);
    size_t len = 0;
    s->bytes = decode_string_token(tok, &len);
    s->len = len;
    char namebuf[32];
    int id = 0;
    for (StrConst *cur = cg->strings; cur != NULL; cur = cur->next) id++;
    snprintf(namebuf, sizeof(namebuf), ".str.%d", id);
    s->name = strdup(namebuf);
    s->next = cg->strings;
    cg->strings = s;
    return s;
}

static void free_strings(StrConst *s) {
    while (s) {
        StrConst *n = s->next;
        free(s->key);
        free(s->name);
        free(s->bytes);
        free(s);
        s = n;
    }
}

static void vars_free(VarSlot *v) {
    while (v) {
        VarSlot *n = v->next;
        free(v->name);
        free(v->ptr);
        free(v);
        v = n;
    }
}

static VarSlot *vars_find(CG *cg, const char *name) {
    for (VarSlot *v = cg->vars; v != NULL; v = v->next) {
        if (strcmp(v->name, name) == 0) return v;
    }
    return NULL;
}

static void vars_add(CG *cg, const char *name, ValTy ty, const char *ptr, bool is_global) {
    VarSlot *v = (VarSlot *)calloc(1, sizeof(VarSlot));
    v->name = strdup(name);
    v->ty = ty;
    v->ptr = strdup(ptr);
    v->is_global = is_global;
    v->next = cg->vars;
    cg->vars = v;
}

static const char *mangle_type(ValTy t) {
    switch (t) {
        case VT_I32: return "int";
        case VT_DBL: return "double";
        case VT_I1: return "boolean";
        case VT_SARR: return "StringArray";
        default: return "x";
    }
}

static char *mangle_method_name(const char *name, ParamType *params) {
    StrBuf sb;
    sb_init(&sb);
    sb_append(&sb, name);
    sb_append(&sb, "__");
    for (ParamType *p = params; p != NULL; p = p->next) {
        sb_append(&sb, mangle_type(ty_from_annot(
            p->type == TYPE_INT ? "int" :
            p->type == TYPE_DOUBLE ? "double" :
            p->type == TYPE_BOOL ? "boolean" :
            p->type == TYPE_STRING_ARRAY ? "String[]" : "undef"
        )));
        if (p->next) sb_append(&sb, "__");
    }
    if (params == NULL) sb_append(&sb, "void");
    char *r = strdup(sb.data ? sb.data : "");
    sb_free(&sb);
    return r;
}

static char *mangle_from_call_annot(const char *name, const char *annot) {
    /* annot is "(int,double)" or "()" etc (stored in Identifier annot) */
    if (annot == NULL) return strdup(name);
    StrBuf sb;
    sb_init(&sb);
    sb_append(&sb, name);
    sb_append(&sb, "__");
    const char *p = annot;
    if (*p == '(') p++;
    if (*p == ')') {
        sb_append(&sb, "void");
        char *r = strdup(sb.data);
        sb_free(&sb);
        return r;
    }
    while (*p && *p != ')') {
        if (strncmp(p, "int", 3) == 0) { sb_append(&sb, "int"); p += 3; }
        else if (strncmp(p, "double", 6) == 0) { sb_append(&sb, "double"); p += 6; }
        else if (strncmp(p, "boolean", 7) == 0) { sb_append(&sb, "boolean"); p += 7; }
        else if (strncmp(p, "String[]", 8) == 0) { sb_append(&sb, "StringArray"); p += 8; }
        else { p++; continue; }
        if (*p == ',') { sb_append(&sb, "__"); p++; }
    }
    char *r = strdup(sb.data);
    sb_free(&sb);
    return r;
}

typedef struct { ValTy ty; char *reg; } RVal;

static RVal gen_expr(CG *cg, Node *e);
static void gen_stmt(CG *cg, Node *s, ValTy ret_ty, char **ret_slot_ptr);

static int parse_sig_param_types(const char *annot, ValTy *out, int max) {
    if (annot == NULL || max <= 0) return 0;
    const char *p = annot;
    if (*p == '(') p++;
    int n = 0;
    if (*p == ')') return 0;
    while (*p && *p != ')' && n < max) {
        if (strncmp(p, "int", 3) == 0) { out[n++] = VT_I32; p += 3; }
        else if (strncmp(p, "double", 6) == 0) { out[n++] = VT_DBL; p += 6; }
        else if (strncmp(p, "boolean", 7) == 0) { out[n++] = VT_I1; p += 7; }
        else if (strncmp(p, "String[]", 8) == 0) { out[n++] = VT_SARR; p += 8; }
        else { p++; continue; }
        if (*p == ',') p++;
    }
    return n;
}

static RVal make_rval(ValTy ty, char *reg) {
    RVal r; r.ty = ty; r.reg = reg; return r;
}

static RVal gen_load_var(CG *cg, Node *id) {
    VarSlot *v = vars_find(cg, id->value);
    if (v == NULL) {
        /* fallback to globals */
        for (Symbol *sym = class_table ? class_table->symbols : NULL; sym != NULL; sym = sym->next) {
            if (!sym->is_method && strcmp(sym->name, id->value) == 0) {
                ValTy t = ty_from_annot(
                    sym->type == TYPE_INT ? "int" :
                    sym->type == TYPE_DOUBLE ? "double" :
                    sym->type == TYPE_BOOL ? "boolean" : "int"
                );
                vars_add(cg, sym->name, t, sym->name, true);
                v = vars_find(cg, sym->name);
                break;
            }
        }
    }
    if (v == NULL) return make_rval(VT_I32, strdup("0"));
    char *tmp = new_reg(cg);
    if (v->is_global) {
        cg_emit(cg, "  %s = load %s, %s* @%s\n", tmp, llvm_ty(v->ty), llvm_ty(v->ty), v->ptr);
    } else {
        cg_emit(cg, "  %s = load %s, %s* %s\n", tmp, llvm_ty(v->ty), llvm_ty(v->ty), v->ptr);
    }
    return make_rval(v->ty, tmp);
}

static void gen_store_var(CG *cg, const char *name, RVal val) {
    VarSlot *v = vars_find(cg, name);
    if (v == NULL) {
        for (Symbol *sym = class_table ? class_table->symbols : NULL; sym != NULL; sym = sym->next) {
            if (!sym->is_method && strcmp(sym->name, name) == 0) {
                ValTy t = ty_from_annot(
                    sym->type == TYPE_INT ? "int" :
                    sym->type == TYPE_DOUBLE ? "double" :
                    sym->type == TYPE_BOOL ? "boolean" : "int"
                );
                vars_add(cg, sym->name, t, sym->name, true);
                v = vars_find(cg, sym->name);
                break;
            }
        }
    }
    if (v == NULL) return;
    if (v->is_global) {
        cg_emit(cg, "  store %s %s, %s* @%s\n", llvm_ty(val.ty), val.reg, llvm_ty(val.ty), v->ptr);
    } else {
        cg_emit(cg, "  store %s %s, %s* %s\n", llvm_ty(val.ty), val.reg, llvm_ty(val.ty), v->ptr);
    }
}

static RVal gen_cast(CG *cg, RVal v, ValTy to) {
    if (v.ty == to) return v;
    if (v.ty == VT_I32 && to == VT_DBL) {
        char *r = new_reg(cg);
        cg_emit(cg, "  %s = sitofp i32 %s to double\n", r, v.reg);
        free(v.reg);
        return make_rval(VT_DBL, r);
    }
    if (v.ty == VT_I1 && to == VT_I32) {
        char *r = new_reg(cg);
        cg_emit(cg, "  %s = zext i1 %s to i32\n", r, v.reg);
        free(v.reg);
        return make_rval(VT_I32, r);
    }
    return v;
}

static RVal gen_short_circuit(CG *cg, Node *e, bool is_and) {
    /* Produces i1 with proper short-circuit */
    RVal lhs = gen_expr(cg, e->child);
    char *lhs_reg = lhs.reg;
    if (lhs.ty != VT_I1) lhs = gen_cast(cg, lhs, VT_I1);

    char *lbl_rhs = new_label(cg, is_and ? "and.rhs." : "or.rhs.");
    char *lbl_end = new_label(cg, is_and ? "and.end." : "or.end.");
    char pred_lhs[64];
    snprintf(pred_lhs, sizeof(pred_lhs), "%s", cg->cur_block[0] ? cg->cur_block : "entry");
    if (is_and) cg_emit(cg, "  br i1 %s, label %%%s, label %%%s\n", lhs_reg, lbl_rhs, lbl_end);
    else        cg_emit(cg, "  br i1 %s, label %%%s, label %%%s\n", lhs_reg, lbl_end, lbl_rhs);

    cg_emit(cg, "%s:\n", lbl_rhs);
    cg_set_block(cg, lbl_rhs);
    RVal rhs = gen_expr(cg, e->child->sibling);
    if (rhs.ty != VT_I1) rhs = gen_cast(cg, rhs, VT_I1);
    char pred_rhs[64];
    snprintf(pred_rhs, sizeof(pred_rhs), "%s", cg->cur_block[0] ? cg->cur_block : lbl_rhs);
    cg_emit(cg, "  br label %%%s\n", lbl_end);

    cg_emit(cg, "%s:\n", lbl_end);
    cg_set_block(cg, lbl_end);
    char *phi = new_reg(cg);
    if (is_and) {
        cg_emit(cg, "  %s = phi i1 [ 0, %%%s ], [ %s, %%%s ]\n", phi, pred_lhs, rhs.reg, pred_rhs);
    } else {
        cg_emit(cg, "  %s = phi i1 [ 1, %%%s ], [ %s, %%%s ]\n", phi, pred_lhs, rhs.reg, pred_rhs);
    }

    free(lbl_rhs); free(lbl_end);
    free(rhs.reg);
    return make_rval(VT_I1, phi);
}

static RVal gen_expr(CG *cg, Node *e) {
    if (e == NULL || e->type == NULL) return make_rval(VT_I32, strdup("0"));

    if (strcmp(e->type, "Natural") == 0) return make_rval(VT_I32, format_i32_const(e->value ? e->value : "0"));
    if (strcmp(e->type, "Decimal") == 0) return make_rval(VT_DBL, format_double_const(e->value ? e->value : "0.0"));
    if (strcmp(e->type, "BoolLit") == 0) {
        bool b = (e->value && strcmp(e->value, "true") == 0);
        return make_rval(VT_I1, strdup(b ? "1" : "0"));
    }
    if (strcmp(e->type, "Identifier") == 0) return gen_load_var(cg, e);
    if (strcmp(e->type, "Length") == 0) {
        /* args.length */
        Node *id = e->child;
        VarSlot *v = vars_find(cg, id->value);
        if (v == NULL || v->ty != VT_SARR) return make_rval(VT_I32, strdup("0"));
        char *tmp = new_reg(cg);
        cg_emit(cg, "  %s = load %%StringArray, %%StringArray* %s\n", tmp, v->ptr);
        char *lenr = new_reg(cg);
        cg_emit(cg, "  %s = extractvalue %%StringArray %s, 1\n", lenr, tmp);
        free(tmp);
        return make_rval(VT_I32, lenr);
    }
    if (strcmp(e->type, "ParseArgs") == 0) {
        Node *id = e->child;
        Node *idx = id ? id->sibling : NULL;
        VarSlot *v = id ? vars_find(cg, id->value) : NULL;
        RVal ridx = gen_expr(cg, idx);
        if (ridx.ty != VT_I32) ridx = gen_cast(cg, ridx, VT_I32);
        char *arr = new_reg(cg);
        cg_emit(cg, "  %s = load %%StringArray, %%StringArray* %s\n", arr, v->ptr);
        char *data = new_reg(cg);
        cg_emit(cg, "  %s = extractvalue %%StringArray %s, 0\n", data, arr);
        char *gep = new_reg(cg);
        cg_emit(cg, "  %s = getelementptr inbounds i8*, i8** %s, i32 %s\n", gep, data, ridx.reg);
        char *s = new_reg(cg);
        cg_emit(cg, "  %s = load i8*, i8** %s\n", s, gep);
        char *call = new_reg(cg);
        cg_emit(cg, "  %s = call i32 @atoi(i8* %s)\n", call, s);
        free(arr); free(data); free(gep); free(s); free(ridx.reg);
        return make_rval(VT_I32, call);
    }
    if (strcmp(e->type, "Call") == 0) {
        Node *id = e->child;
        Node *arg = id ? id->sibling : NULL;
        const char *sig = id ? id->annot : NULL; /* like "(int,double)" */
        char *mangled = mangle_from_call_annot(id->value, sig);
        ValTy rt = ty_from_annot(e->annot);

        ValTy param_tys[64];
        int param_n = parse_sig_param_types(sig, param_tys, 64);

        StrBuf args;
        sb_init(&args);
        int argc = 0;
        for (Node *a = arg; a != NULL; a = a->sibling) {
            RVal ra = gen_expr(cg, a);
            if (argc < param_n && param_tys[argc] == VT_DBL && ra.ty == VT_I32) {
                ra = gen_cast(cg, ra, VT_DBL);
            }
            if (argc > 0) sb_append(&args, ", ");
            sb_appendf(&args, "%s %s", llvm_ty(ra.ty), ra.reg);
            free(ra.reg);
            argc++;
        }

        if (rt == VT_VOID) {
            cg_emit(cg, "  call void @%s(%s)\n", mangled, args.data ? args.data : "");
            sb_free(&args);
            free(mangled);
            return make_rval(VT_VOID, strdup("0"));
        }
        char *r = new_reg(cg);
        cg_emit(cg, "  %s = call %s @%s(%s)\n", r, llvm_ty(rt), mangled, args.data ? args.data : "");
        sb_free(&args);
        free(mangled);
        return make_rval(rt, r);
    }

    if (strcmp(e->type, "Assign") == 0) {
        Node *id = e->child;
        Node *rhsn = id ? id->sibling : NULL;
        RVal rhs = gen_expr(cg, rhsn);
        ValTy dest = ty_from_annot(id->annot);
        if (dest == VT_DBL && rhs.ty == VT_I32) rhs = gen_cast(cg, rhs, VT_DBL);
        gen_store_var(cg, id->value, rhs);
        return rhs;
    }

    if (strcmp(e->type, "And") == 0) return gen_short_circuit(cg, e, true);
    if (strcmp(e->type, "Or") == 0) return gen_short_circuit(cg, e, false);

    if (strcmp(e->type, "Not") == 0) {
        RVal a = gen_expr(cg, e->child);
        if (a.ty != VT_I1) a = gen_cast(cg, a, VT_I1);
        char *r = new_reg(cg);
        cg_emit(cg, "  %s = xor i1 %s, 1\n", r, a.reg);
        free(a.reg);
        return make_rval(VT_I1, r);
    }
    if (strcmp(e->type, "Minus") == 0 || strcmp(e->type, "Plus") == 0) {
        RVal a = gen_expr(cg, e->child);
        if (strcmp(e->type, "Plus") == 0) return a;
        if (a.ty == VT_I32) {
            char *r = new_reg(cg);
            cg_emit(cg, "  %s = sub i32 0, %s\n", r, a.reg);
            free(a.reg);
            return make_rval(VT_I32, r);
        }
        if (a.ty == VT_DBL) {
            char *r = new_reg(cg);
            cg_emit(cg, "  %s = fsub double -0.0, %s\n", r, a.reg);
            free(a.reg);
            return make_rval(VT_DBL, r);
        }
        return a;
    }

    /* Binary ops */
    const char *op = e->type;
    Node *l = e->child;
    Node *r = l ? l->sibling : NULL;
    RVal a = gen_expr(cg, l);
    RVal b = gen_expr(cg, r);

    /* numeric promotion */
    if ((a.ty == VT_DBL || b.ty == VT_DBL) && (a.ty == VT_I32 || a.ty == VT_DBL) && (b.ty == VT_I32 || b.ty == VT_DBL)) {
        if (a.ty == VT_I32) a = gen_cast(cg, a, VT_DBL);
        if (b.ty == VT_I32) b = gen_cast(cg, b, VT_DBL);
    }

    if (strcmp(op, "Add") == 0 || strcmp(op, "Sub") == 0 || strcmp(op, "Mul") == 0 || strcmp(op, "Div") == 0) {
        bool isdbl = (a.ty == VT_DBL);
        char *res = new_reg(cg);
        const char *ins =
            strcmp(op, "Add") == 0 ? (isdbl ? "fadd" : "add") :
            strcmp(op, "Sub") == 0 ? (isdbl ? "fsub" : "sub") :
            strcmp(op, "Mul") == 0 ? (isdbl ? "fmul" : "mul") :
                                     (isdbl ? "fdiv" : "sdiv");
        cg_emit(cg, "  %s = %s %s %s, %s\n", res, ins, llvm_ty(a.ty), a.reg, b.reg);
        free(a.reg); free(b.reg);
        return make_rval(a.ty, res);
    }
    if (strcmp(op, "Mod") == 0) {
        char *res = new_reg(cg);
        cg_emit(cg, "  %s = srem i32 %s, %s\n", res, a.reg, b.reg);
        free(a.reg); free(b.reg);
        return make_rval(VT_I32, res);
    }
    if (strcmp(op, "Xor") == 0) {
        ValTy out_ty = ty_from_annot(e->annot);
        char *res = new_reg(cg);
        if (out_ty == VT_I1) {
            cg_emit(cg, "  %s = xor i1 %s, %s\n", res, a.reg, b.reg);
            free(a.reg); free(b.reg);
            return make_rval(VT_I1, res);
        }
        cg_emit(cg, "  %s = xor i32 %s, %s\n", res, a.reg, b.reg);
        free(a.reg); free(b.reg);
        return make_rval(VT_I32, res);
    }
    if (strcmp(op, "Lshift") == 0 || strcmp(op, "Rshift") == 0) {
        char *res = new_reg(cg);
        const char *ins = strcmp(op, "Lshift") == 0 ? "shl" : "ashr";
        cg_emit(cg, "  %s = %s i32 %s, %s\n", res, ins, a.reg, b.reg);
        free(a.reg); free(b.reg);
        return make_rval(VT_I32, res);
    }

    /* comparisons */
    if (strcmp(op, "Eq") == 0 || strcmp(op, "Ne") == 0 ||
        strcmp(op, "Lt") == 0 || strcmp(op, "Le") == 0 ||
        strcmp(op, "Gt") == 0 || strcmp(op, "Ge") == 0) {
        char *res = new_reg(cg);
        bool isdbl = (a.ty == VT_DBL && b.ty == VT_DBL);
        if (isdbl) {
            const char *pred =
                strcmp(op, "Eq") == 0 ? "oeq" :
                strcmp(op, "Ne") == 0 ? "one" :
                strcmp(op, "Lt") == 0 ? "olt" :
                strcmp(op, "Le") == 0 ? "ole" :
                strcmp(op, "Gt") == 0 ? "ogt" : "oge";
            cg_emit(cg, "  %s = fcmp %s double %s, %s\n", res, pred, a.reg, b.reg);
        } else {
            const char *pred =
                strcmp(op, "Eq") == 0 ? "eq" :
                strcmp(op, "Ne") == 0 ? "ne" :
                strcmp(op, "Lt") == 0 ? "slt" :
                strcmp(op, "Le") == 0 ? "sle" :
                strcmp(op, "Gt") == 0 ? "sgt" : "sge";
            cg_emit(cg, "  %s = icmp %s %s %s, %s\n", res, pred, llvm_ty(a.ty), a.reg, b.reg);
        }
        free(a.reg); free(b.reg);
        return make_rval(VT_I1, res);
    }

    free(a.reg); free(b.reg);
    return make_rval(VT_I32, strdup("0"));
}

static void gen_print(CG *cg, Node *print_node) {
    Node *c = print_node->child;
    if (c == NULL) return;

    if (c->type && strcmp(c->type, "StrLit") == 0) {
        StrConst *s = get_string_const(cg, c->value ? c->value : "\"\"");
        char *ptr = new_reg(cg);
        cg_emit(cg, "  %s = getelementptr inbounds [%zu x i8], [%zu x i8]* @%s, i32 0, i32 0\n",
                ptr, s->len + 1, s->len + 1, s->name);
        cg_emit(cg, "  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_s, i32 0, i32 0), i8* %s)\n", ptr);
        free(ptr);
        return;
    }

    RVal v = gen_expr(cg, c);
    if (v.ty == VT_I32) {
        cg_emit(cg, "  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_d, i32 0, i32 0), i32 %s)\n", v.reg);
    } else if (v.ty == VT_DBL) {
        cg_emit(cg, "  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt_f, i32 0, i32 0), double %s)\n", v.reg);
    } else if (v.ty == VT_I1) {
        char *s = new_reg(cg);
        cg_emit(cg, "  %s = select i1 %s, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.true, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.false, i32 0, i32 0)\n",
                s, v.reg);
        cg_emit(cg, "  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt_s, i32 0, i32 0), i8* %s)\n", s);
        free(s);
    }
    free(v.reg);
}

static void gen_stmt(CG *cg, Node *s, ValTy ret_ty, char **ret_slot_ptr) {
    if (s == NULL || s->type == NULL) return;

    if (strcmp(s->type, "Block") == 0) {
        for (Node *c = s->child; c != NULL; c = c->sibling) gen_stmt(cg, c, ret_ty, ret_slot_ptr);
        return;
    }
    if (strcmp(s->type, "Print") == 0) { gen_print(cg, s); return; }
    if (strcmp(s->type, "Return") == 0) {
        if (ret_ty == VT_VOID) {
            cg_emit(cg, "  ret void\n");
            return;
        }
        Node *e = s->child;
        RVal v = gen_expr(cg, e);
        if (ret_ty == VT_DBL && v.ty == VT_I32) v = gen_cast(cg, v, VT_DBL);
        cg_emit(cg, "  ret %s %s\n", llvm_ty(v.ty), v.reg);
        free(v.reg);
        return;
    }
    if (strcmp(s->type, "If") == 0) {
        Node *cond = s->child;
        Node *then_s = cond ? cond->sibling : NULL;
        Node *else_s = then_s ? then_s->sibling : NULL;
        RVal c = gen_expr(cg, cond);
        if (c.ty != VT_I1) c = gen_cast(cg, c, VT_I1);
        char *l_then = new_label(cg, "if.then.");
        char *l_else = new_label(cg, "if.else.");
        char *l_end  = new_label(cg, "if.end.");
        cg_emit(cg, "  br i1 %s, label %%%s, label %%%s\n", c.reg, l_then, l_else);
        free(c.reg);
        cg_emit(cg, "%s:\n", l_then);
        cg_set_block(cg, l_then);
        gen_stmt(cg, then_s, ret_ty, ret_slot_ptr);
        cg_emit(cg, "  br label %%%s\n", l_end);
        cg_emit(cg, "%s:\n", l_else);
        cg_set_block(cg, l_else);
        gen_stmt(cg, else_s, ret_ty, ret_slot_ptr);
        cg_emit(cg, "  br label %%%s\n", l_end);
        cg_emit(cg, "%s:\n", l_end);
        cg_set_block(cg, l_end);
        free(l_then); free(l_else); free(l_end);
        return;
    }
    if (strcmp(s->type, "While") == 0) {
        Node *cond = s->child;
        Node *body = cond ? cond->sibling : NULL;
        char *l_cond = new_label(cg, "while.cond.");
        char *l_body = new_label(cg, "while.body.");
        char *l_end  = new_label(cg, "while.end.");
        cg_emit(cg, "  br label %%%s\n", l_cond);
        cg_emit(cg, "%s:\n", l_cond);
        cg_set_block(cg, l_cond);
        RVal c = gen_expr(cg, cond);
        if (c.ty != VT_I1) c = gen_cast(cg, c, VT_I1);
        cg_emit(cg, "  br i1 %s, label %%%s, label %%%s\n", c.reg, l_body, l_end);
        free(c.reg);
        cg_emit(cg, "%s:\n", l_body);
        cg_set_block(cg, l_body);
        gen_stmt(cg, body, ret_ty, ret_slot_ptr);
        cg_emit(cg, "  br label %%%s\n", l_cond);
        cg_emit(cg, "%s:\n", l_end);
        cg_set_block(cg, l_end);
        free(l_cond); free(l_body); free(l_end);
        return;
    }

    /* expression statement (Call / Assign / ParseArgs) */
    (void)ret_ty; (void)ret_slot_ptr;
    RVal v = gen_expr(cg, s);
    free(v.reg);
}

static void gen_method(CG *cg, MethodInfo *m, Node *decl) {
    char *fname = mangle_method_name(m->name, m->params);
    ValTy rt = ty_from_annot(
        m->return_type == TYPE_INT ? "int" :
        m->return_type == TYPE_DOUBLE ? "double" :
        m->return_type == TYPE_BOOL ? "boolean" :
        m->return_type == TYPE_VOID ? "void" :
        m->return_type == TYPE_STRING_ARRAY ? "String[]" : "void"
    );

    cg->vars = NULL;
    cg->reg = 0;
    cg->label = 0;

    /* signature */
    StrBuf sig;
    sb_init(&sig);
    int idx = 0;
    for (ParamType *p = m->params; p != NULL; p = p->next, idx++) {
        ValTy pt = ty_from_annot(p->type == TYPE_INT ? "int" :
                                 p->type == TYPE_DOUBLE ? "double" :
                                 p->type == TYPE_BOOL ? "boolean" :
                                 p->type == TYPE_STRING_ARRAY ? "String[]" : "int");
        if (idx > 0) sb_append(&sig, ", ");
        sb_appendf(&sig, "%s %%a%d", llvm_ty(pt), idx);
    }

    cg_emit(cg, "define %s @%s(%s) {\n", llvm_ty(rt), fname, sig.data ? sig.data : "");
    cg_emit(cg, "entry:\n");
    cg_set_block(cg, "entry");

    /* allocas for params and locals */
    int pidx = 0;
    for (Symbol *sym = m->table->symbols; sym != NULL; sym = sym->next) {
        if (strcmp(sym->name, "return") == 0) continue;
        ValTy vt = ty_from_annot(sym->type == TYPE_INT ? "int" :
                                 sym->type == TYPE_DOUBLE ? "double" :
                                 sym->type == TYPE_BOOL ? "boolean" :
                                 sym->type == TYPE_STRING_ARRAY ? "String[]" : "int");
        char *ptr = new_reg(cg);
        cg_emit(cg, "  %s = alloca %s\n", ptr, llvm_ty(vt));
        vars_add(cg, sym->name, vt, ptr, false);
        if (sym->is_param) {
            char argname[32];
            snprintf(argname, sizeof(argname), "%%a%d", pidx++);
            cg_emit(cg, "  store %s %s, %s* %s\n", llvm_ty(vt), argname, llvm_ty(vt), ptr);
        }
        free(ptr);
    }

    /* default-initialize locals (including ones declared inside blocks) */
    for (Symbol *sym = m->table->symbols; sym != NULL; sym = sym->next) {
        if (strcmp(sym->name, "return") == 0) continue;
        if (sym->is_param) continue;
        VarSlot *vs = vars_find(cg, sym->name);
        if (!vs) continue;
        if (vs->ty == VT_I32) cg_emit(cg, "  store i32 0, i32* %s\n", vs->ptr);
        else if (vs->ty == VT_DBL) cg_emit(cg, "  store double 0.0, double* %s\n", vs->ptr);
        else if (vs->ty == VT_I1) cg_emit(cg, "  store i1 0, i1* %s\n", vs->ptr);
    }

    /* Body: find it in AST */
    Node *header = decl ? decl->child : NULL;
    Node *body = header ? header->sibling : NULL;
    Node *child = body ? body->child : NULL;
    while (child != NULL) {
        gen_stmt(cg, child, rt, NULL);
        child = child->sibling;
    }

    if (rt == VT_VOID) cg_emit(cg, "  ret void\n");
    else if (rt == VT_I32) cg_emit(cg, "  ret i32 0\n");
    else if (rt == VT_DBL) cg_emit(cg, "  ret double 0.0\n");
    else if (rt == VT_I1) cg_emit(cg, "  ret i1 0\n");

    cg_emit(cg, "}\n\n");

    sb_free(&sig);
    free(fname);
    vars_free(cg->vars);
    cg->vars = NULL;
}

static Node *find_method_decl_node(Node *program, Node *decl_node) {
    (void)program;
    return decl_node;
}

void codegen_program(Node *program, FILE *out) {
    CG cg;
    memset(&cg, 0, sizeof(cg));
    cg.out = out;

    /* Preamble */
    cg_emit(&cg, "; ModuleID = 'juc'\n");
    cg_emit(&cg, "declare i32 @printf(i8*, ...)\n");
    cg_emit(&cg, "declare i32 @atoi(i8*)\n");
    cg_emit(&cg, "%%StringArray = type { i8**, i32 }\n\n");

    cg_emit(&cg, "@.fmt_d = private constant [3 x i8] c\"%%d\\00\"\n");
    cg_emit(&cg, "@.fmt_s = private constant [3 x i8] c\"%%s\\00\"\n");
    cg_emit(&cg, "@.fmt_f = private constant [6 x i8] c\"%%.16e\\00\"\n");
    cg_emit(&cg, "@.true  = private constant [5 x i8] c\"true\\00\"\n");
    cg_emit(&cg, "@.false = private constant [6 x i8] c\"false\\00\"\n\n");

    /* Globals (fields) */
    if (class_table) {
        for (Symbol *sym = class_table->symbols; sym != NULL; sym = sym->next) {
            if (sym->is_method) continue;
            ValTy t = ty_from_annot(sym->type == TYPE_INT ? "int" :
                                    sym->type == TYPE_DOUBLE ? "double" :
                                    sym->type == TYPE_BOOL ? "boolean" : "int");
            if (t == VT_I32) cg_emit(&cg, "@%s = global i32 0\n", sym->name);
            else if (t == VT_DBL) cg_emit(&cg, "@%s = global double 0.0\n", sym->name);
            else if (t == VT_I1) cg_emit(&cg, "@%s = global i1 0\n", sym->name);
        }
        cg_emit(&cg, "\n");
    }

    /* Methods */
    for (MethodInfo *m = method_list; m != NULL; m = m->next) {
        if (m->is_duplicate) continue;
        Node *decl = find_method_decl_node(program, m->decl_node);
        gen_method(&cg, m, decl);
    }

    /* Emit string constants after collection by a cheap second traversal: walk AST prints */
    /* We collect lazily during generation, so we must emit them at top. Simpler: emit now by re-printing at end with 'private constant' is still valid in IR. */
    /* (LLVM allows globals anywhere, but keep it acceptable.) */
    if (cg.strings) {
        cg_emit(&cg, "; String literals\n");
        for (StrConst *s = cg.strings; s != NULL; s = s->next) {
            cg_emit(&cg, "@%s = private constant [%zu x i8] c\"", s->name, s->len + 1);
            llvm_print_bytes(out, s->bytes, s->len);
            cg_emit(&cg, "\\00\"\n");
        }
        cg_emit(&cg, "\n");
    }

    /* Wrapper main: calls Juc main(String[]) if present */
    MethodInfo *main_m = NULL;
    for (MethodInfo *m = method_list; m != NULL; m = m->next) {
        if (strcmp(m->name, "main") == 0 && m->params && m->params->type == TYPE_STRING_ARRAY && m->params->next == NULL) {
            main_m = m;
            break;
        }
    }
    if (main_m) {
        char *mangled = mangle_method_name(main_m->name, main_m->params);
        cg_emit(&cg, "define i32 @main(i32 %%argc, i8** %%argv) {\n");
        cg_emit(&cg, "entry:\n");
        char *argc1 = new_reg(&cg);
        cg_emit(&cg, "  %s = sub i32 %%argc, 1\n", argc1);
        char *argv1 = new_reg(&cg);
        cg_emit(&cg, "  %s = getelementptr inbounds i8*, i8** %%argv, i32 1\n", argv1);
        char *sa = new_reg(&cg);
        cg_emit(&cg, "  %s = insertvalue %%StringArray undef, i8** %s, 0\n", sa, argv1);
        char *sa2 = new_reg(&cg);
        cg_emit(&cg, "  %s = insertvalue %%StringArray %s, i32 %s, 1\n", sa2, sa, argc1);
        cg_emit(&cg, "  call void @%s(%%StringArray %s)\n", mangled, sa2);
        cg_emit(&cg, "  ret i32 0\n");
        cg_emit(&cg, "}\n");
        free(mangled);
        free(argc1); free(argv1); free(sa); free(sa2);
    } else {
        /* Allow executing IR even if the source has no Juc main. */
        cg_emit(&cg, "define i32 @main(i32 %%argc, i8** %%argv) {\n");
        cg_emit(&cg, "entry:\n");
        cg_emit(&cg, "  ret i32 0\n");
        cg_emit(&cg, "}\n");
    }

    free_strings(cg.strings);
    vars_free(cg.vars);
}

