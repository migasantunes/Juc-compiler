%{
/*
 * Syntax analyzer and parser for the Juc programming language
 * Juc is a subset of Java with support for classes, methods, variables, and expressions
 * Generates abstract syntax trees and performs semantic analysis
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

int yylex(void);
void yyerror(char *s);

extern int token_line;
extern int token_col;
extern char *current_error_yytext;
extern bool emit_tokens;
extern bool lexical_error_found;

bool syntax_error_found = false;
bool semantic_error_found = false;

#include "ast.h"
#include "semantics.h"
#include "codegen.h"

%}

%union {
    char *str;
    struct node *node; 
}

%locations

%token CLASS PUBLIC STATIC INT BOOL DOUBLE VOID STRING
%token LBRACE RBRACE LPAR RPAR LSQ RSQ
%token COMMA SEMICOLON
%token ASSIGN PLUS MINUS STAR DIV MOD
%token AND OR NOT XOR LSHIFT RSHIFT
%token EQ NE GE LE GT LT
%token IF ELSE WHILE RETURN
%token PRINT PARSEINT DOTLENGTH ARROW
%token <str> RESERVED IDENTIFIER NATURAL DECIMAL STRLIT BOOLLIT

%type <node> Program DeclList MethodDecl FieldDecl AuxIdList
%type <node> Type MethodHeader FormalParams MethodBody MethodBodyDecls
%type <node> VarDecl StatementList Statement Expr OrExpr AndExpr XorExpr EqExpr RelExpr ShiftExpr AddExpr MulExpr UnaryExpr Primary MethodInvocation ExprList ParseArgs

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%right ASSIGN
%left OR
%left AND
%left XOR
%left EQ NE
%left GT GE LT LE
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR DIV MOD
%right NOT UNARY_PLUS UNARY_MINUS

%%

/* Program structure: class with declarations */
Program: CLASS IDENTIFIER LBRACE DeclList RBRACE
       {
           $$ = new_node_at("Program", NULL, @1.first_line, @1.first_column);
           add_child($$, new_node_at("Identifier", $2, @2.first_line, @2.first_column));
           if ($4 != NULL) { add_child($$, $4); }
           program_root = $$; 
       }
       ;

/* List of declarations (methods and fields) */
DeclList: /* Vazio */ { $$ = NULL; }
        | DeclList MethodDecl
        {
            if ($1 == NULL) { $$ = $2; }
            else { add_sibling($1, $2); $$ = $1; }
        }
        | DeclList FieldDecl
        {
            if ($1 == NULL) { $$ = $2; }
            else { add_sibling($1, $2); $$ = $1; }
        }
        | DeclList SEMICOLON { $$ = $1; }
        ;

/* Method declaration with public static modifier */
MethodDecl: PUBLIC STATIC MethodHeader MethodBody
          {
              $$ = new_node("MethodDecl", NULL);
              add_child($$, $3);
              add_child($$, $4);
          }
          ;

FieldDecl: PUBLIC STATIC Type IDENTIFIER AuxIdList SEMICOLON
         {
             $$ = new_node("FieldDecl", NULL);
             add_child($$, $3);
             add_child($$, new_node_at("Identifier", $4, @4.first_line, @4.first_column));
             
             Node *aux = $5;
             Node *last_decl = $$;
             while (aux != NULL) {
                 Node *next_aux = aux->sibling;
                 aux->sibling = NULL; 
                 
                 Node *new_decl = new_node("FieldDecl", NULL);
                 add_child(new_decl, new_node($3->type, NULL)); 
                 add_child(new_decl, aux);
                 
                 add_sibling(last_decl, new_decl);
                 last_decl = new_decl;
                 aux = next_aux;
             }
         }
         | error SEMICOLON { $$ = NULL; }
         ;

AuxIdList: /* Vazio */ { $$ = NULL; }
         | AuxIdList COMMA IDENTIFIER
         {
             Node *id_node = new_node_at("Identifier", $3, @3.first_line, @3.first_column);
             if ($1 == NULL) { $$ = id_node; }
             else { add_sibling($1, id_node); $$ = $1; }
         }
         ;

Type: BOOL   { $$ = new_node_at("Bool", NULL, @1.first_line, @1.first_column); }
    | INT    { $$ = new_node_at("Int", NULL, @1.first_line, @1.first_column); }
    | DOUBLE { $$ = new_node_at("Double", NULL, @1.first_line, @1.first_column); }
    ;

MethodHeader: Type IDENTIFIER LPAR RPAR
            {
                $$ = new_node("MethodHeader", NULL);
                add_child($$, $1);
                add_child($$, new_node_at("Identifier", $2, @2.first_line, @2.first_column));
                add_child($$, new_node("MethodParams", NULL));
            }
            | Type IDENTIFIER LPAR STRING LSQ RSQ IDENTIFIER RPAR
            {
                $$ = new_node("MethodHeader", NULL);
                add_child($$, $1);
                add_child($$, new_node_at("Identifier", $2, @2.first_line, @2.first_column));
                Node *params = new_node("MethodParams", NULL);
                Node *param = new_node("ParamDecl", NULL);
                add_child(param, new_node_at("StringArray", NULL, @4.first_line, @4.first_column));
                add_child(param, new_node_at("Identifier", $7, @7.first_line, @7.first_column));
                add_child(params, param);
                add_child($$, params);
            }
            | Type IDENTIFIER LPAR FormalParams RPAR
            {
                $$ = new_node("MethodHeader", NULL);
                add_child($$, $1);
                add_child($$, new_node_at("Identifier", $2, @2.first_line, @2.first_column));
                Node *params = new_node("MethodParams", NULL);
                add_child(params, $4);
                add_child($$, params);
            }
            | VOID IDENTIFIER LPAR RPAR
            {
                $$ = new_node("MethodHeader", NULL);
                add_child($$, new_node_at("Void", NULL, @1.first_line, @1.first_column));
                add_child($$, new_node_at("Identifier", $2, @2.first_line, @2.first_column));
                add_child($$, new_node("MethodParams", NULL));
            }
            | VOID IDENTIFIER LPAR STRING LSQ RSQ IDENTIFIER RPAR
            {
                $$ = new_node("MethodHeader", NULL);
                add_child($$, new_node_at("Void", NULL, @1.first_line, @1.first_column));
                add_child($$, new_node_at("Identifier", $2, @2.first_line, @2.first_column));
                Node *params = new_node("MethodParams", NULL);
                Node *param = new_node("ParamDecl", NULL);
                add_child(param, new_node_at("StringArray", NULL, @4.first_line, @4.first_column));
                add_child(param, new_node_at("Identifier", $7, @7.first_line, @7.first_column));
                add_child(params, param);
                add_child($$, params);
            }
            | VOID IDENTIFIER LPAR FormalParams RPAR
            {
                $$ = new_node("MethodHeader", NULL);
                add_child($$, new_node_at("Void", NULL, @1.first_line, @1.first_column));
                add_child($$, new_node_at("Identifier", $2, @2.first_line, @2.first_column));
                Node *params = new_node("MethodParams", NULL);
                add_child(params, $4);
                add_child($$, params);
            }
            ;

FormalParams: Type IDENTIFIER
            {
                $$ = new_node("ParamDecl", NULL);
                add_child($$, $1);
                add_child($$, new_node_at("Identifier", $2, @2.first_line, @2.first_column));
            }
            | FormalParams COMMA Type IDENTIFIER
            {
                Node *new_param = new_node("ParamDecl", NULL);
                add_child(new_param, $3);
                add_child(new_param, new_node_at("Identifier", $4, @4.first_line, @4.first_column));
                add_sibling($1, new_param);
                $$ = $1;
            }
            ;

MethodBody: LBRACE MethodBodyDecls RBRACE 
          { 
              $$ = new_node("MethodBody", NULL); 
              add_child($$, $2);
          }
          ;

MethodBodyDecls: /* Vazio */ { $$ = NULL; }
               | MethodBodyDecls Statement 
               { 
                   if ($1 == NULL) { $$ = $2; }
                   else { add_sibling($1, $2); $$ = $1; }
               }
               | MethodBodyDecls VarDecl 
               { 
                   if ($1 == NULL) { $$ = $2; }
                   else { add_sibling($1, $2); $$ = $1; }
               }
               ;

VarDecl: Type IDENTIFIER AuxIdList SEMICOLON 
       { 
             $$ = new_node("VarDecl", NULL);
             add_child($$, $1);
         add_child($$, new_node_at("Identifier", $2, @2.first_line, @2.first_column));
             
             Node *aux = $3;
             Node *last_decl = $$;
             while (aux != NULL) {
                 Node *next_aux = aux->sibling;
                 aux->sibling = NULL; 
                 
                 Node *new_decl = new_node("VarDecl", NULL);
                 add_child(new_decl, new_node($1->type, NULL)); 
                 add_child(new_decl, aux);
                 
                 add_sibling(last_decl, new_decl);
                 last_decl = new_decl;
                 aux = next_aux;
             }
       }
       ;

StatementList: /* Vazio */ { $$ = NULL; }
             | StatementList Statement 
             { 
                 if ($1 == NULL) { $$ = $2; }
                 else { add_sibling($1, $2); $$ = $1; }
             }
             | StatementList VarDecl
             {
                 if ($1 == NULL) { $$ = $2; }
                 else { add_sibling($1, $2); $$ = $1; }
             }
             ;

Statement: LBRACE StatementList RBRACE 
         { 
             if ($2 != NULL && count_siblings($2) > 1) {
                 $$ = new_node("Block", NULL);
                 add_child($$, $2);
             } else {
                 $$ = $2; 
             }
         }
         | IF LPAR Expr RPAR Statement %prec LOWER_THAN_ELSE 
         { 
             $$ = new_node_at("If", NULL, @1.first_line, @1.first_column);
             add_child($$, $3);
             add_child($$, create_block($5));
             add_child($$, new_node("Block", NULL));
         }
         | IF LPAR Expr RPAR Statement ELSE Statement 
         { 
             $$ = new_node_at("If", NULL, @1.first_line, @1.first_column);
             add_child($$, $3);
             add_child($$, create_block($5));
             add_child($$, create_block($7));
         }
         | WHILE LPAR Expr RPAR Statement 
         { 
             $$ = new_node_at("While", NULL, @1.first_line, @1.first_column);
             add_child($$, $3);
             add_child($$, create_block($5));
         }
         | RETURN SEMICOLON { $$ = new_node_at("Return", NULL, @1.first_line, @1.first_column); }
         | RETURN Expr SEMICOLON { $$ = new_node_at("Return", NULL, @1.first_line, @1.first_column); add_child($$, $2); }
         | MethodInvocation SEMICOLON { $$ = $1; }
         | IDENTIFIER ASSIGN Expr SEMICOLON
         { $$ = new_node_at("Assign", NULL, @2.first_line, @2.first_column); add_child($$, new_node_at("Identifier", $1, @1.first_line, @1.first_column)); add_child($$, $3); }
         | ParseArgs SEMICOLON { $$ = $1; }
         | SEMICOLON { $$ = NULL; }
         | PRINT LPAR Expr RPAR SEMICOLON { $$ = new_node_at("Print", NULL, @1.first_line, @1.first_column); add_child($$, $3); }
         | PRINT LPAR STRLIT RPAR SEMICOLON { $$ = new_node_at("Print", NULL, @1.first_line, @1.first_column); add_child($$, new_node_at("StrLit", $3, @3.first_line, @3.first_column)); }
         | error SEMICOLON { $$ = NULL; }
         ;

/* Expression parsing with proper precedence */
Expr: IDENTIFIER ASSIGN Expr
    { $$ = new_node_at("Assign", NULL, @2.first_line, @2.first_column); add_child($$, new_node_at("Identifier", $1, @1.first_line, @1.first_column)); add_child($$, $3); }
    | OrExpr { $$ = $1; }
    ;

/* Logical OR expression - lowest precedence */
OrExpr: OrExpr OR AndExpr { $$ = new_node_at("Or", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
      | AndExpr { $$ = $1; }
      ;

AndExpr: AndExpr AND XorExpr { $$ = new_node_at("And", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
       | XorExpr { $$ = $1; }
       ;

XorExpr: XorExpr XOR EqExpr { $$ = new_node_at("Xor", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
       | EqExpr { $$ = $1; }
       ;

EqExpr: EqExpr EQ RelExpr { $$ = new_node_at("Eq", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
      | EqExpr NE RelExpr { $$ = new_node_at("Ne", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
      | RelExpr { $$ = $1; }
      ;

RelExpr: RelExpr GE ShiftExpr { $$ = new_node_at("Ge", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
       | RelExpr GT ShiftExpr { $$ = new_node_at("Gt", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
       | RelExpr LE ShiftExpr { $$ = new_node_at("Le", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
       | RelExpr LT ShiftExpr { $$ = new_node_at("Lt", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
       | ShiftExpr { $$ = $1; }
       ;

ShiftExpr: ShiftExpr LSHIFT AddExpr { $$ = new_node_at("Lshift", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
         | ShiftExpr RSHIFT AddExpr { $$ = new_node_at("Rshift", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
         | AddExpr { $$ = $1; }
         ;

AddExpr: AddExpr PLUS MulExpr { $$ = new_node_at("Add", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
       | AddExpr MINUS MulExpr { $$ = new_node_at("Sub", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
       | MulExpr { $$ = $1; }
       ;

MulExpr: MulExpr STAR UnaryExpr { $$ = new_node_at("Mul", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
       | MulExpr DIV UnaryExpr { $$ = new_node_at("Div", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
       | MulExpr MOD UnaryExpr { $$ = new_node_at("Mod", NULL, @2.first_line, @2.first_column); add_child($$, $1); add_child($$, $3); }
       | UnaryExpr { $$ = $1; }
       ;

UnaryExpr: MINUS UnaryExpr %prec UNARY_MINUS { $$ = new_node_at("Minus", NULL, @1.first_line, @1.first_column); add_child($$, $2); }
         | PLUS UnaryExpr %prec UNARY_PLUS { $$ = new_node_at("Plus", NULL, @1.first_line, @1.first_column); add_child($$, $2); }
         | NOT UnaryExpr { $$ = new_node_at("Not", NULL, @1.first_line, @1.first_column); add_child($$, $2); }
         | Primary { $$ = $1; }
         ;

Primary: MethodInvocation { $$ = $1; }
       | ParseArgs { $$ = $1; }
       | IDENTIFIER DOTLENGTH { $$ = new_node_at("Length", NULL, @2.first_line, @2.first_column); add_child($$, new_node_at("Identifier", $1, @1.first_line, @1.first_column)); }
       | IDENTIFIER { $$ = new_node_at("Identifier", $1, @1.first_line, @1.first_column); }
       | NATURAL { $$ = new_node_at("Natural", $1, @1.first_line, @1.first_column); }
       | DECIMAL { $$ = new_node_at("Decimal", $1, @1.first_line, @1.first_column); }
       | BOOLLIT { $$ = new_node_at("BoolLit", $1, @1.first_line, @1.first_column); }
       | LPAR Expr RPAR { $$ = $2; }
       | LPAR error RPAR { $$ = NULL; }
       ;

MethodInvocation: IDENTIFIER LPAR RPAR 
                { $$ = new_node_at("Call", NULL, @1.first_line, @1.first_column); add_child($$, new_node_at("Identifier", $1, @1.first_line, @1.first_column)); }
                | IDENTIFIER LPAR ExprList RPAR 
                { $$ = new_node_at("Call", NULL, @1.first_line, @1.first_column); add_child($$, new_node_at("Identifier", $1, @1.first_line, @1.first_column)); add_child($$, $3); }
                | IDENTIFIER LPAR error RPAR { $$ = NULL; }
                ;

ExprList: Expr { $$ = $1; }
        | ExprList COMMA Expr { add_sibling($1, $3); $$ = $1; }
        ;

ParseArgs: PARSEINT LPAR IDENTIFIER LSQ Expr RSQ RPAR 
         { $$ = new_node_at("ParseArgs", NULL, @1.first_line, @1.first_column); add_child($$, new_node_at("Identifier", $3, @3.first_line, @3.first_column)); add_child($$, $5); }
         | PARSEINT LPAR error RPAR { $$ = NULL; }
         ;

%%



void yyerror(char *s) {
    syntax_error_found = true;
    /* Função de erro simples e infalível, igual à que resultou na perfeição! */
    printf("Line %d, col %d: %s: %s\n", token_line, token_col, s, current_error_yytext);
}

int main(int argc, char **argv) {
    bool parse_syntax = true;
    bool print_ast = false;
    bool run_semantic = true;
    bool print_semantic = false;
    bool errors_only_semantic = false;
    bool emit_llvm = false;
    
    if (argc > 1) {
        if (strcmp(argv[1], "-1") == 0 || strcmp(argv[1], "-l") == 0) {
            emit_tokens = true;
            parse_syntax = false;
            run_semantic = false;
        } else if (strcmp(argv[1], "-e1") == 0) {
            emit_tokens = false;
            parse_syntax = false;
            run_semantic = false;
        } else if (strcmp(argv[1], "-e2") == 0) {
            parse_syntax = true;
            run_semantic = false;
        } else if (strcmp(argv[1], "-t") == 0) {
            parse_syntax = true;
            print_ast = true;
            run_semantic = false;
        } else if (strcmp(argv[1], "-s") == 0) {
            parse_syntax = true;
            run_semantic = true;
            print_semantic = true;
        } else if (strcmp(argv[1], "-e3") == 0) {
            parse_syntax = true;
            run_semantic = true;
            errors_only_semantic = true;
        }
    } else {
        emit_llvm = true;
    }
    
    if (parse_syntax) {
        yyparse();
        if (!syntax_error_found && program_root != NULL) {
            if (run_semantic && !(errors_only_semantic && lexical_error_found)) {
                build_symbol_tables(program_root);
                annotate_program(program_root);
                if (print_semantic) {
                    print_symbol_tables();
                    printf("\n");
                    print_tree_annotated(program_root, 0);
                } else if (errors_only_semantic) {
                    /* errors already printed during analysis */
                }
            }
            if (print_ast) {
                print_tree(program_root, 0); 
            }
            if (emit_llvm && run_semantic && !lexical_error_found && !semantic_error_found) {
                codegen_program(program_root, stdout);
            }
        }
        free_symbol_tables();
        free_tree(program_root);
    } else {
        while (yylex() != 0);
    }
    return 0;
}