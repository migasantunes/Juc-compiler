#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "ast.h"
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_BOOL,
    TYPE_VOID,
    TYPE_STRING_ARRAY,
    TYPE_STRING,
    TYPE_UNDEF
} TypeKind;

typedef struct param_type {
    TypeKind type;
    struct param_type *next;
} ParamType;

typedef struct symbol {
    char *name;
    TypeKind type;
    bool is_param;
    bool is_method;
    ParamType *params;
    Node *decl_node;
    struct symbol *next;
} Symbol;

typedef struct symtable {
    char *name;
    Symbol *symbols;
} SymTable;

typedef struct method_info {
    char *name;
    TypeKind return_type;
    ParamType *params;
    SymTable *table;
    Node *decl_node;
    bool is_duplicate;
    struct method_info *next;
} MethodInfo;

extern SymTable *class_table;
extern MethodInfo *method_list;
extern const char *class_name;
extern bool semantic_error_found;

void build_symbol_tables(Node *program);
void annotate_program(Node *program);
void print_symbol_tables(void);
void free_symbol_tables(void);

#endif
