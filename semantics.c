#include "semantics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

SymTable *class_table = NULL;
MethodInfo *method_list = NULL;
const char *class_name = NULL;

static const char *type_to_str(TypeKind type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_DOUBLE: return "double";
        case TYPE_BOOL: return "boolean";
        case TYPE_VOID: return "void";
        case TYPE_STRING_ARRAY: return "String[]";
        case TYPE_STRING: return "String";
        case TYPE_UNDEF: default: return "undef";
    }
}

static bool is_numeric(TypeKind type) {
    return type == TYPE_INT || type == TYPE_DOUBLE;
}

static bool is_boolean(TypeKind type) {
    return type == TYPE_BOOL;
}

static bool is_assign_compatible(TypeKind dest, TypeKind src) {
    if (dest == TYPE_STRING_ARRAY || src == TYPE_STRING_ARRAY) return false;
    if (dest == TYPE_VOID || src == TYPE_VOID) return false;
    if (dest == src) return true;
    return dest == TYPE_DOUBLE && src == TYPE_INT;
}

static bool is_param_compatible(TypeKind arg, TypeKind param) {
    if (arg == param) return true;
    return param == TYPE_DOUBLE && arg == TYPE_INT;
}

static bool is_reserved_identifier(const char *name) {
    return name != NULL && strcmp(name, "_") == 0;
}

static void annotate_node(Node *node, const char *annot) {
    if (node != NULL) {
        node->annot = (char *)annot;
    }
}

static ParamType *create_param_type(TypeKind type) {
    ParamType *p = (ParamType *)malloc(sizeof(ParamType));
    p->type = type;
    p->next = NULL;
    return p;
}

static SymTable *create_table(const char *name) {
    SymTable *t = (SymTable *)malloc(sizeof(SymTable));
    t->name = name ? strdup(name) : NULL;
    t->symbols = NULL;
    return t;
}

static Symbol *create_symbol(const char *name, TypeKind type, bool is_param, bool is_method, ParamType *params, Node *decl_node) {
    Symbol *s = (Symbol *)malloc(sizeof(Symbol));
    s->name = strdup(name);
    s->type = type;
    s->is_param = is_param;
    s->is_method = is_method;
    s->params = params;
    s->decl_node = decl_node;
    s->next = NULL;
    return s;
}

static void append_symbol(SymTable *table, Symbol *symbol) {
    if (table == NULL || symbol == NULL) return;
    if (table->symbols == NULL) {
        table->symbols = symbol;
        return;
    }
    Symbol *cur = table->symbols;
    while (cur->next != NULL) cur = cur->next;
    cur->next = symbol;
}

static Symbol *find_variable_symbol(SymTable *table, const char *name) {
    if (table == NULL || name == NULL) return NULL;
    for (Symbol *cur = table->symbols; cur != NULL; cur = cur->next) {
        if (cur->is_method) continue;
        if (strcmp(cur->name, "return") == 0) continue;
        if (strcmp(cur->name, name) == 0) return cur;
    }
    return NULL;
}

static Symbol *find_field_symbol(const char *name) {
    return find_variable_symbol(class_table, name);
}

static bool param_types_equal(ParamType *a, ParamType *b) {
    while (a != NULL && b != NULL) {
        if (a->type != b->type) return false;
        a = a->next;
        b = b->next;
    }
    return a == NULL && b == NULL;
}

static int param_count(ParamType *params) {
    int count = 0;
    while (params != NULL) {
        count++;
        params = params->next;
    }
    return count;
}

static TypeKind type_from_node(Node *node) {
    if (node == NULL || node->type == NULL) return TYPE_UNDEF;
    if (strcmp(node->type, "StrLit") == 0) {
        annotate_node(node, type_to_str(TYPE_STRING));
        return TYPE_STRING;
    }
    if (strcmp(node->type, "Int") == 0) return TYPE_INT;
    if (strcmp(node->type, "Double") == 0) return TYPE_DOUBLE;
    if (strcmp(node->type, "Bool") == 0) return TYPE_BOOL;
    if (strcmp(node->type, "Void") == 0) return TYPE_VOID;
    if (strcmp(node->type, "StringArray") == 0) return TYPE_STRING_ARRAY;
    return TYPE_UNDEF;
}

static ParamType *build_param_types(Node *method_params_node) {
    if (method_params_node == NULL) return NULL;
    ParamType *head = NULL;
    ParamType *tail = NULL;
    Node *param = method_params_node->child;
    while (param != NULL) {
        Node *type_node = param->child;
        TypeKind type = type_from_node(type_node);
        ParamType *p = create_param_type(type);
        if (head == NULL) {
            head = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
        param = param->sibling;
    }
    return head;
}

static MethodInfo *create_method_info(const char *name, TypeKind return_type, ParamType *params, Node *decl_node, bool is_duplicate) {
    MethodInfo *m = (MethodInfo *)malloc(sizeof(MethodInfo));
    m->name = strdup(name);
    m->return_type = return_type;
    m->params = params;
    m->table = create_table(NULL);
    m->decl_node = decl_node;
    m->is_duplicate = is_duplicate;
    m->next = NULL;
    if (method_list == NULL) {
        method_list = m;
    } else {
        MethodInfo *cur = method_list;
        while (cur->next != NULL) cur = cur->next;
        cur->next = m;
    }
    return m;
}

static MethodInfo *find_method_info_by_decl(Node *decl) {
    for (MethodInfo *cur = method_list; cur != NULL; cur = cur->next) {
        if (cur->decl_node == decl) return cur;
    }
    return NULL;
}

static bool method_signature_exists(const char *name, ParamType *params) {
    for (MethodInfo *cur = method_list; cur != NULL; cur = cur->next) {
        if (strcmp(cur->name, name) == 0 && param_types_equal(cur->params, params)) {
            return true;
        }
    }
    return false;
}

static void report_symbol_already_defined(Node *id_node) {
    if (id_node == NULL || id_node->value == NULL) return;
    semantic_error_found = true;
    printf("Line %d, col %d: Symbol %s already defined\n", id_node->line, id_node->col, id_node->value);
}

static void report_symbol_reserved(Node *id_node) {
    if (id_node == NULL) return;
    semantic_error_found = true;
    printf("Line %d, col %d: Symbol _ is reserved\n", id_node->line, id_node->col);
}

static char* format_method_signature(const char *name, TypeKind *args, int arg_count) {
    char buf[1024];
    int pos = snprintf(buf, sizeof(buf), "%s(", name);
    for (int i = 0; i < arg_count; i++) {
        if (i > 0) pos += snprintf(buf + pos, sizeof(buf) - pos, ",");
        pos += snprintf(buf + pos, sizeof(buf) - pos, "%s", type_to_str(args[i]));
    }
    snprintf(buf + pos, sizeof(buf) - pos, ")");
    return strdup(buf);
}

static char* format_params_annot(ParamType *params) {
    char buf[1024];
    int pos = snprintf(buf, sizeof(buf), "(");
    ParamType *cur = params;
    while (cur != NULL) {
        pos += snprintf(buf + pos, sizeof(buf) - pos, "%s", type_to_str(cur->type));
        cur = cur->next;
        if (cur != NULL) pos += snprintf(buf + pos, sizeof(buf) - pos, ",");
    }
    snprintf(buf + pos, sizeof(buf) - pos, ")");
    return strdup(buf);
}

static void report_cannot_find_symbol(Node *node, TypeKind *args, int arg_count, bool is_method) {
    if (node == NULL || node->value == NULL) return;
    semantic_error_found = true;
    if (is_method) {
        char *sig = format_method_signature(node->value, args, arg_count);
        printf("Line %d, col %d: Cannot find symbol %s\n", node->line, node->col, sig);
        free(sig);
    } else {
        printf("Line %d, col %d: Cannot find symbol %s\n", node->line, node->col, node->value);
    }
}

static void report_operator_type(Node *node, const char *op, TypeKind type) {
    if (node == NULL || op == NULL) return;
    semantic_error_found = true;
    printf("Line %d, col %d: Operator %s cannot be applied to type %s\n", node->line, node->col, op, type_to_str(type));
}

static void report_operator_types(Node *node, const char *op, TypeKind t1, TypeKind t2) {
    if (node == NULL || op == NULL) return;
    semantic_error_found = true;
    printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", node->line, node->col, op, type_to_str(t1), type_to_str(t2));
}

static void report_incompatible_in_statement(int line, int col, TypeKind type, const char *stmt_token) {
    if (stmt_token == NULL) return;
    semantic_error_found = true;
    printf("Line %d, col %d: Incompatible type %s in %s statement\n", line, col, type_to_str(type), stmt_token);
}

static void report_number_out_of_bounds(Node *node) {
    if (node == NULL || node->value == NULL) return;
    semantic_error_found = true;
    printf("Line %d, col %d: Number %s out of bounds\n", node->line, node->col, node->value);
}

static void report_ambiguous_method(Node *id_node, TypeKind *args, int arg_count) {
    if (id_node == NULL || id_node->value == NULL) return;
    semantic_error_found = true;
    char *sig = format_method_signature(id_node->value, args, arg_count);
    printf("Line %d, col %d: Reference to method %s is ambiguous\n", id_node->line, id_node->col, sig);
    free(sig);
}

static void free_param_types(ParamType *p) {
    while (p != NULL) {
        ParamType *next = p->next;
        free(p);
        p = next;
    }
}

void build_symbol_tables(Node *program) {
    if (program == NULL || program->child == NULL) return;
    class_name = program->child->value;
    class_table = create_table("Class");

    for (Node *child = program->child; child != NULL; child = child->sibling) {
        if (child->type != NULL && strcmp(child->type, "FieldDecl") == 0) {
            Node *type_node = child->child;
            Node *id_node = type_node ? type_node->sibling : NULL;
            if (id_node == NULL) continue;
            TypeKind type = type_from_node(type_node);
            if (is_reserved_identifier(id_node->value)) {
                report_symbol_reserved(id_node);
            } else if (find_field_symbol(id_node->value) != NULL) {
                report_symbol_already_defined(id_node);
            } else {
                append_symbol(class_table, create_symbol(id_node->value, type, false, false, NULL, id_node));
            }
        } else if (child->type != NULL && strcmp(child->type, "MethodDecl") == 0) {
            Node *header = child->child;
            Node *body = header ? header->sibling : NULL;
            Node *ret_node = header ? header->child : NULL;
            Node *id_node = ret_node ? ret_node->sibling : NULL;
            Node *params_node = id_node ? id_node->sibling : NULL;
            if (id_node == NULL) continue;

            TypeKind ret_type = type_from_node(ret_node);
            ParamType *params = build_param_types(params_node);
            bool reserved = is_reserved_identifier(id_node->value);
            if (reserved) report_symbol_reserved(id_node);

            bool duplicate = method_signature_exists(id_node->value, params);
            if (duplicate && !reserved) {
                semantic_error_found = true;
                char *sig = format_params_annot(params);
                printf("Line %d, col %d: Symbol %s%s already defined\n", id_node->line, id_node->col, id_node->value, sig);
                free(sig);
            }

            if (!reserved && !duplicate) {
                MethodInfo *info = create_method_info(id_node->value, ret_type, params, child, duplicate);
                append_symbol(class_table, create_symbol(id_node->value, ret_type, false, true, params, id_node));
                append_symbol(info->table, create_symbol("return", ret_type, false, false, NULL, NULL));
                
                Node *param = params_node ? params_node->child : NULL;
                while (param != NULL) {
                    Node *t_node = param->child;
                    Node *i_node = t_node ? t_node->sibling : NULL;
                    if (i_node) {
                        TypeKind type = type_from_node(t_node);
                        if (is_reserved_identifier(i_node->value)) report_symbol_reserved(i_node);
                        else if (find_variable_symbol(info->table, i_node->value) != NULL) report_symbol_already_defined(i_node);
                        else append_symbol(info->table, create_symbol(i_node->value, type, true, false, NULL, i_node));
                    }
                    param = param->sibling;
                }
                Node *stmt = body ? body->child : NULL;
                while (stmt != NULL) {
                    if (stmt->type != NULL && strcmp(stmt->type, "VarDecl") == 0) {
                        Node *t_node = stmt->child;
                        Node *i_node = t_node ? t_node->sibling : NULL;
                        if (i_node) {
                            TypeKind type = type_from_node(t_node);
                            if (is_reserved_identifier(i_node->value)) report_symbol_reserved(i_node);
                            else if (find_variable_symbol(info->table, i_node->value) != NULL) report_symbol_already_defined(i_node);
                            else append_symbol(info->table, create_symbol(i_node->value, type, false, false, NULL, i_node));
                        }
                    }
                    stmt = stmt->sibling;
                }
            } else {
                free_param_types(params);
            }
        }
    }
}

static void print_param_types(ParamType *params) {
    printf("(");
    if (params != NULL) {
        ParamType *cur = params;
        printf("%s", type_to_str(cur->type));
        cur = cur->next;
        while (cur != NULL) {
            printf(",%s", type_to_str(cur->type));
            cur = cur->next;
        }
    }
    printf(")");
}

void print_symbol_tables(void) {
    if (class_table == NULL) return;
    printf("===== Class %s Symbol Table =====\n", class_name ? class_name : "");
    for (Symbol *sym = class_table->symbols; sym != NULL; sym = sym->next) {
        if (sym->is_method) {
            printf("%s\t", sym->name);
            print_param_types(sym->params);
            printf("\t%s\n", type_to_str(sym->type));
        } else {
            printf("%s\t\t%s\n", sym->name, type_to_str(sym->type));
        }
    }

    for (MethodInfo *m = method_list; m != NULL; m = m->next) {
        printf("\n===== Method %s", m->name);
        print_param_types(m->params);
        printf(" Symbol Table =====\n");
        for (Symbol *sym = m->table->symbols; sym != NULL; sym = sym->next) {
            if (sym->is_param) {
                printf("%s\t\t%s\tparam\n", sym->name, type_to_str(sym->type));
            } else {
                printf("%s\t\t%s\n", sym->name, type_to_str(sym->type));
            }
        }
    }
}

static char *strip_underscores(const char *text) {
    size_t len = strlen(text);
    char *buf = (char *)malloc(len + 1);
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (text[i] != '_') {
            buf[j++] = text[i];
        }
    }
    buf[j] = '\0';
    return buf;
}

static TypeKind lookup_variable_type(const char *name, SymTable *method_table, Node *current_node) {
    if (method_table != NULL) {
        for (Symbol *sym = method_table->symbols; sym != NULL; sym = sym->next) {
            if (strcmp(sym->name, name) == 0 && !sym->is_method) {
                if (sym->decl_node != NULL && current_node != NULL) {
                    if (sym->decl_node->line > current_node->line || 
                       (sym->decl_node->line == current_node->line && sym->decl_node->col > current_node->col)) {
                        return TYPE_UNDEF;
                    }
                }
                return sym->type;
            }
        }
    }
    Symbol *sym = find_field_symbol(name);
    if (sym != NULL) return sym->type;
    return TYPE_UNDEF;
}

static bool params_exact_match(ParamType *params, TypeKind *args, int arg_count) {
    if (param_count(params) != arg_count) return false;
    int i = 0;
    for (ParamType *cur = params; cur != NULL; cur = cur->next, i++) {
        if (args[i] == TYPE_UNDEF) return false;
        if (args[i] != cur->type) return false;
    }
    return true;
}

static bool params_compatible(ParamType *params, TypeKind *args, int arg_count) {
    if (param_count(params) != arg_count) return false;
    int i = 0;
    for (ParamType *cur = params; cur != NULL; cur = cur->next, i++) {
        if (!is_param_compatible(args[i], cur->type)) return false;
    }
    return true;
}

static MethodInfo *resolve_method(const char *name, TypeKind *args, int arg_count, Node *id_node) {
    MethodInfo *exact = NULL;
    MethodInfo *compatible = NULL;
    int candidate_count = 0;
    int compatible_count = 0;

    for (MethodInfo *cur = method_list; cur != NULL; cur = cur->next) {
        if (cur->is_duplicate) continue;
        if (strcmp(cur->name, name) != 0) continue;
        if (param_count(cur->params) != arg_count) continue;
        candidate_count++;
        if (params_exact_match(cur->params, args, arg_count)) {
            exact = cur;
            break;
        }
    }

    if (exact != NULL) return exact;

    if (candidate_count == 0) {
        report_cannot_find_symbol(id_node, args, arg_count, true);
        return NULL;
    }

    for (MethodInfo *cur = method_list; cur != NULL; cur = cur->next) {
        if (cur->is_duplicate) continue;
        if (strcmp(cur->name, name) != 0) continue;
        if (param_count(cur->params) != arg_count) continue;
        if (params_compatible(cur->params, args, arg_count)) {
            compatible = cur;
            compatible_count++;
        }
    }

    if (compatible_count == 1) return compatible;
    if (compatible_count > 1) {
        report_ambiguous_method(id_node, args, arg_count);
        return NULL;
    }

    report_cannot_find_symbol(id_node, args, arg_count, true);
    return NULL;
}

static TypeKind analyze_expr(Node *node, SymTable *method_table) {
    if (node == NULL) return TYPE_UNDEF;

    if (strcmp(node->type, "Natural") == 0) {
        char *clean = strip_underscores(node->value);
        errno = 0;
        long long value = strtoll(clean, NULL, 10);
        free(clean);
        if (errno == ERANGE || value > INT_MAX) {
            report_number_out_of_bounds(node);
        }
        annotate_node(node, type_to_str(TYPE_INT));
        return TYPE_INT;
    }

    if (strcmp(node->type, "Decimal") == 0) {
        annotate_node(node, type_to_str(TYPE_DOUBLE));
        return TYPE_DOUBLE;
    }

    if (strcmp(node->type, "BoolLit") == 0) {
        annotate_node(node, type_to_str(TYPE_BOOL));
        return TYPE_BOOL;
    }

    if (strcmp(node->type, "StrLit") == 0) {
        annotate_node(node, type_to_str(TYPE_STRING));
        return TYPE_STRING;
    }

    if (strcmp(node->type, "Identifier") == 0) {
        if (is_reserved_identifier(node->value)) {
            report_symbol_reserved(node);
            annotate_node(node, type_to_str(TYPE_UNDEF));
            return TYPE_UNDEF;
        }
        TypeKind type = lookup_variable_type(node->value, method_table, node);
        if (type == TYPE_UNDEF) {
            report_cannot_find_symbol(node, NULL, 0, false);
            annotate_node(node, type_to_str(TYPE_UNDEF));
            return TYPE_UNDEF;
        }
        annotate_node(node, type_to_str(type));
        return type;
    }

    if (strcmp(node->type, "Length") == 0) {
        Node *id_node = node->child;
        TypeKind id_type = analyze_expr(id_node, method_table);
        if (id_type != TYPE_STRING_ARRAY && id_type != TYPE_UNDEF) {
            report_operator_type(node, ".length", id_type);
        }
        annotate_node(node, type_to_str(TYPE_INT));
        return TYPE_INT;
    }

    if (strcmp(node->type, "ParseArgs") == 0) {
        Node *id_node = node->child;
        Node *idx_node = id_node ? id_node->sibling : NULL;
        TypeKind id_type = analyze_expr(id_node, method_table);
        TypeKind idx_type = analyze_expr(idx_node, method_table);
        if (id_type != TYPE_STRING_ARRAY || idx_type != TYPE_INT) {
            report_operator_types(node, "Integer.parseInt", id_type, idx_type);
        }
        annotate_node(node, type_to_str(TYPE_INT));
        return TYPE_INT;
    }

    if (strcmp(node->type, "Call") == 0) {
        Node *id_node = node->child;
        Node *arg_node = id_node ? id_node->sibling : NULL;
        int arg_count = count_siblings(arg_node);
        TypeKind *args = NULL;
        if (arg_count > 0) {
            args = (TypeKind *)malloc(sizeof(TypeKind) * arg_count);
        }

        Node *cur = arg_node;
        for (int i = 0; i < arg_count; i++) {
            args[i] = analyze_expr(cur, method_table);
            cur = cur->sibling;
        }

        if (id_node == NULL || id_node->value == NULL) {
            if (args != NULL) free(args);
            annotate_node(node, type_to_str(TYPE_UNDEF));
            return TYPE_UNDEF;
        }

        if (is_reserved_identifier(id_node->value)) {
            report_symbol_reserved(id_node);
            if (args != NULL) free(args);
            annotate_node(node, type_to_str(TYPE_UNDEF));
            annotate_node(id_node, type_to_str(TYPE_UNDEF));
            return TYPE_UNDEF;
        }

        MethodInfo *method = resolve_method(id_node->value, args, arg_count, id_node);
        if (args != NULL) free(args);
        if (method == NULL) {
            annotate_node(node, type_to_str(TYPE_UNDEF));
            annotate_node(id_node, type_to_str(TYPE_UNDEF));
            return TYPE_UNDEF;
        }
        annotate_node(node, type_to_str(method->return_type));
        annotate_node(id_node, format_params_annot(method->params)); 
        return method->return_type;
    }

    if (strcmp(node->type, "Assign") == 0) {
        Node *id_node = node->child;
        Node *expr_node = id_node ? id_node->sibling : NULL;
        TypeKind left = analyze_expr(id_node, method_table);
        TypeKind right = analyze_expr(expr_node, method_table);
        if (!is_assign_compatible(left, right)) {
            report_operator_types(node, "=", left, right);
        }
        annotate_node(node, type_to_str(left));
        return left;
    }

    if (strcmp(node->type, "Add") == 0 || strcmp(node->type, "Sub") == 0 ||
        strcmp(node->type, "Mul") == 0 || strcmp(node->type, "Div") == 0 ||
        strcmp(node->type, "Mod") == 0) {
        Node *left_node = node->child;
        Node *right_node = left_node ? left_node->sibling : NULL;
        TypeKind left = analyze_expr(left_node, method_table);
        TypeKind right = analyze_expr(right_node, method_table);
        TypeKind result = (left == TYPE_DOUBLE || right == TYPE_DOUBLE) ? TYPE_DOUBLE : TYPE_INT;
        if (!is_numeric(left) || !is_numeric(right)) {
            const char *op = strcmp(node->type, "Add") == 0 ? "+" :
                             strcmp(node->type, "Sub") == 0 ? "-" :
                             strcmp(node->type, "Mul") == 0 ? "*" :
                             strcmp(node->type, "Div") == 0 ? "/" : "%";
            report_operator_types(node, op, left, right);
            annotate_node(node, type_to_str(TYPE_UNDEF));
            return TYPE_UNDEF;
        }
        annotate_node(node, type_to_str(result));
        return result;
    }

    if (strcmp(node->type, "And") == 0 || strcmp(node->type, "Or") == 0) {
        Node *left_node = node->child;
        Node *right_node = left_node ? left_node->sibling : NULL;
        TypeKind left = analyze_expr(left_node, method_table);
        TypeKind right = analyze_expr(right_node, method_table);
        if (!is_boolean(left) || !is_boolean(right)) {
            const char *op = strcmp(node->type, "And") == 0 ? "&&" : "||";
            report_operator_types(node, op, left, right);
        }
        annotate_node(node, type_to_str(TYPE_BOOL));
        return TYPE_BOOL;
    }

    if (strcmp(node->type, "Xor") == 0) {
        Node *left_node = node->child;
        Node *right_node = left_node ? left_node->sibling : NULL;
        TypeKind left = analyze_expr(left_node, method_table);
        TypeKind right = analyze_expr(right_node, method_table);
        if (left != TYPE_INT || right != TYPE_INT) {
            report_operator_types(node, "^", left, right);
        }
        annotate_node(node, type_to_str(TYPE_INT));
        return TYPE_INT;
    }

    if (strcmp(node->type, "Lshift") == 0 || strcmp(node->type, "Rshift") == 0) {
        Node *left_node = node->child;
        Node *right_node = left_node ? left_node->sibling : NULL;
        TypeKind left = analyze_expr(left_node, method_table);
        TypeKind right = analyze_expr(right_node, method_table);
        if (left != TYPE_INT || right != TYPE_INT) {
            const char *op = strcmp(node->type, "Lshift") == 0 ? "<<" : ">>";
            report_operator_types(node, op, left, right);
        }
        annotate_node(node, type_to_str(TYPE_INT));
        return TYPE_INT;
    }

    if (strcmp(node->type, "Eq") == 0 || strcmp(node->type, "Ne") == 0) {
        Node *left_node = node->child;
        Node *right_node = left_node ? left_node->sibling : NULL;
        TypeKind left = analyze_expr(left_node, method_table);
        TypeKind right = analyze_expr(right_node, method_table);
        if (!((is_numeric(left) && is_numeric(right)) || (left == TYPE_BOOL && right == TYPE_BOOL))) {
            const char *op = strcmp(node->type, "Eq") == 0 ? "==" : "!=";
            report_operator_types(node, op, left, right);
        }
        annotate_node(node, type_to_str(TYPE_BOOL));
        return TYPE_BOOL;
    }

    if (strcmp(node->type, "Lt") == 0 || strcmp(node->type, "Gt") == 0 ||
        strcmp(node->type, "Le") == 0 || strcmp(node->type, "Ge") == 0) {
        Node *left_node = node->child;
        Node *right_node = left_node ? left_node->sibling : NULL;
        TypeKind left = analyze_expr(left_node, method_table);
        TypeKind right = analyze_expr(right_node, method_table);
        if (!is_numeric(left) || !is_numeric(right)) {
            const char *op = strcmp(node->type, "Lt") == 0 ? "<" :
                             strcmp(node->type, "Gt") == 0 ? ">" :
                             strcmp(node->type, "Le") == 0 ? "<=" : ">=";
            report_operator_types(node, op, left, right);
        }
        annotate_node(node, type_to_str(TYPE_BOOL));
        return TYPE_BOOL;
    }

    if (strcmp(node->type, "Not") == 0) {
        Node *expr_node = node->child;
        TypeKind type = analyze_expr(expr_node, method_table);
        if (!is_boolean(type)) {
            report_operator_type(node, "!", type);
        }
        annotate_node(node, type_to_str(TYPE_BOOL));
        return TYPE_BOOL;
    }

    if (strcmp(node->type, "Minus") == 0 || strcmp(node->type, "Plus") == 0) {
        Node *expr_node = node->child;
        TypeKind type = analyze_expr(expr_node, method_table);
        if (!is_numeric(type)) {
            const char *op = strcmp(node->type, "Minus") == 0 ? "-" : "+";
            report_operator_type(node, op, type);
            annotate_node(node, type_to_str(TYPE_UNDEF));
            return TYPE_UNDEF;
        }
        TypeKind result = type == TYPE_DOUBLE ? TYPE_DOUBLE : TYPE_INT;
        annotate_node(node, type_to_str(result));
        return result;
    }

    return TYPE_UNDEF;
}

static void analyze_statement(Node *stmt, SymTable *method_table, TypeKind return_type) {
    if (stmt == NULL || stmt->type == NULL) return;

    if (strcmp(stmt->type, "Block") == 0) {
        Node *child = stmt->child;
        while (child != NULL) {
            analyze_statement(child, method_table, return_type);
            child = child->sibling;
        }
        return;
    }

    if (strcmp(stmt->type, "If") == 0) {
        Node *cond = stmt->child;
        Node *then_stmt = cond ? cond->sibling : NULL;
        Node *else_stmt = then_stmt ? then_stmt->sibling : NULL;
        TypeKind cond_type = analyze_expr(cond, method_table);
        if (cond_type != TYPE_BOOL) {
            report_incompatible_in_statement(cond->line, cond->col, cond_type, "if");
        }
        analyze_statement(then_stmt, method_table, return_type);
        analyze_statement(else_stmt, method_table, return_type);
        return;
    }

    if (strcmp(stmt->type, "While") == 0) {
        Node *cond = stmt->child;
        Node *body = cond ? cond->sibling : NULL;
        TypeKind cond_type = analyze_expr(cond, method_table);
        if (cond_type != TYPE_BOOL) {
            report_incompatible_in_statement(cond->line, cond->col, cond_type, "while");
        }
        analyze_statement(body, method_table, return_type);
        return;
    }

    if (strcmp(stmt->type, "Return") == 0) {
        Node *expr = stmt->child;
        if (expr == NULL) {
            if (return_type != TYPE_VOID) {
                report_incompatible_in_statement(stmt->line, stmt->col, TYPE_VOID, "return");
            }
            return;
        }
        TypeKind expr_type = analyze_expr(expr, method_table);
        if (return_type == TYPE_VOID) {
            report_incompatible_in_statement(expr->line, expr->col, expr_type, "return");
            return;
        }
        if (!is_assign_compatible(return_type, expr_type)) {
            report_incompatible_in_statement(expr->line, expr->col, expr_type, "return");
        }
        return;
    }

    if (strcmp(stmt->type, "Print") == 0) {
        Node *expr = stmt->child;
        TypeKind expr_type = analyze_expr(expr, method_table);
        if (expr_type != TYPE_INT && expr_type != TYPE_DOUBLE && expr_type != TYPE_BOOL && expr_type != TYPE_STRING) {
            report_incompatible_in_statement(expr->line, expr->col, expr_type, "System.out.print");
        } else if (expr_type == TYPE_STRING_ARRAY) {
            report_incompatible_in_statement(expr->line, expr->col, expr_type, "System.out.print");
        }
        return;
    }

    analyze_expr(stmt, method_table);
}

static void analyze_method_body(Node *method_body, SymTable *method_table, TypeKind return_type) {
    if (method_body == NULL) return;
    Node *child = method_body->child;
    while (child != NULL) {
        if (child->type != NULL && strcmp(child->type, "VarDecl") == 0) {
            child = child->sibling;
            continue;
        }
        analyze_statement(child, method_table, return_type);
        child = child->sibling;
    }
}

static void analyze_method_decl(Node *method_decl) {
    MethodInfo *info = find_method_info_by_decl(method_decl);
    if (info == NULL) return;
    Node *header = method_decl->child;
    Node *body = header ? header->sibling : NULL;
    analyze_method_body(body, info->table, info->return_type);
}

void annotate_program(Node *program) {
    if (program == NULL || program->child == NULL) return;
    Node *decl = program->child->sibling;
    while (decl != NULL) {
        if (decl->type != NULL && strcmp(decl->type, "MethodDecl") == 0) {
            analyze_method_decl(decl);
        }
        decl = decl->sibling;
    }
}

void free_symbol_tables(void) {
    if (class_table != NULL) {
        Symbol *sym = class_table->symbols;
        while (sym != NULL) {
            Symbol *next = sym->next;
            free(sym->name);
            free(sym);
            sym = next;
        }
        if (class_table->name) free(class_table->name);
        free(class_table);
        class_table = NULL;
    }
    MethodInfo *m = method_list;
    while (m != NULL) {
        MethodInfo *next = m->next;
        free(m->name);
        free_param_types(m->params);
        if (m->table != NULL) {
            Symbol *sym = m->table->symbols;
            while (sym != NULL) {
                Symbol *snext = sym->next;
                free(sym->name);
                free(sym);
                sym = snext;
            }
            if (m->table->name) free(m->table->name);
            free(m->table);
        }
        free(m);
        m = next;
    }
    method_list = NULL;
}
