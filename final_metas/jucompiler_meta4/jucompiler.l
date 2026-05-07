%{
/*Jose Miguel Luis Antunes 2023211288
Andre Jorge Balula Leao 2023210870*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "y.tab.h"

extern YYLTYPE yylloc;

int current_line = 1;
int current_col = 1;
int token_line = 1;
int token_col = 1;

bool emit_tokens = false;
bool lexical_error_found = false;

static int comment_start_line = 1;
static int comment_start_col = 1;

static int string_start_line = 1;
static int string_start_col = 1;
static bool string_has_error = false;

static char *string_buffer = NULL;
static int string_capacity = 0;
static int string_pos = 0;


char *current_error_yytext = "";

static void advance_position(const char *text) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\r') {
            current_line++;
            current_col = 1;
            if (text[i + 1] == '\n') {
                i++;
            }
        } else if (text[i] == '\n') {
            current_line++;
            current_col = 1;
        } else {
            current_col++;
        }
    }
}

static void ensure_capacity(int added_len) {
    if (string_capacity == 0) {
        string_capacity = 256;
        string_buffer = (char *)malloc(string_capacity);
    }
    while (string_pos + added_len + 1 >= string_capacity) {
        string_capacity *= 2;
        string_buffer = (char *)realloc(string_buffer, string_capacity);
    }
}

static void append_to_string(const char *text) {
    int i;
    int len = strlen(text);
    ensure_capacity(len);
    for (i = 0; i < len; i++) {
        string_buffer[string_pos++] = text[i];
    }
}

static void emit_simple(const char *token_name) {
    if (emit_tokens) {
        printf("%s\n", token_name);
    }
}

static void emit_value(const char *token_name, const char *value) {
    if (emit_tokens) {
        printf("%s(%s)\n", token_name, value);
    }
}

static void print_invalid_escape_text(const char *text) {
    lexical_error_found = true;
    printf("Line %d, col %d: invalid escape sequence (%s)\n", token_line, token_col, text);
}

static void print_unterminated_string(void) {
    lexical_error_found = true;
    printf("Line %d, col %d: unterminated string literal\n", string_start_line, string_start_col);
}

static int classify_identifier(const char *id) {
    if (strcmp(id, "boolean") == 0) { emit_simple("BOOL"); return BOOL; }
    if (strcmp(id, "class") == 0) { emit_simple("CLASS"); return CLASS; }
    if (strcmp(id, "double") == 0) { emit_simple("DOUBLE"); return DOUBLE; }
    if (strcmp(id, "else") == 0) { emit_simple("ELSE"); return ELSE; }
    if (strcmp(id, "if") == 0) { emit_simple("IF"); return IF; }
    if (strcmp(id, "int") == 0) { emit_simple("INT"); return INT; }
    if (strcmp(id, "public") == 0) { emit_simple("PUBLIC"); return PUBLIC; }
    if (strcmp(id, "return") == 0) { emit_simple("RETURN"); return RETURN; }
    if (strcmp(id, "static") == 0) { emit_simple("STATIC"); return STATIC; }
    if (strcmp(id, "String") == 0) { emit_simple("STRING"); return STRING; }
    if (strcmp(id, "void") == 0) { emit_simple("VOID"); return VOID; }
    if (strcmp(id, "while") == 0) { emit_simple("WHILE"); return WHILE; }
    
    if (strcmp(id, "true") == 0 || strcmp(id, "false") == 0) { 
        emit_value("BOOLLIT", id); 
        yylval.str = strdup(id); 
        return BOOLLIT; 
    }

    if (
        strcmp(id, "abstract") == 0 || strcmp(id, "assert") == 0 || strcmp(id, "break") == 0 ||
        strcmp(id, "byte") == 0 || strcmp(id, "case") == 0 || strcmp(id, "catch") == 0 ||
        strcmp(id, "char") == 0 || strcmp(id, "const") == 0 || strcmp(id, "continue") == 0 ||
        strcmp(id, "default") == 0 || strcmp(id, "do") == 0 || strcmp(id, "enum") == 0 ||
        strcmp(id, "extends") == 0 || strcmp(id, "final") == 0 || strcmp(id, "finally") == 0 ||
        strcmp(id, "float") == 0 || strcmp(id, "for") == 0 || strcmp(id, "goto") == 0 ||
        strcmp(id, "implements") == 0 || strcmp(id, "import") == 0 || strcmp(id, "instanceof") == 0 ||
        strcmp(id, "interface") == 0 || strcmp(id, "long") == 0 || strcmp(id, "native") == 0 ||
        strcmp(id, "new") == 0 || strcmp(id, "package") == 0 || strcmp(id, "private") == 0 ||
        strcmp(id, "protected") == 0 || strcmp(id, "short") == 0 || strcmp(id, "strictfp") == 0 ||
        strcmp(id, "super") == 0 || strcmp(id, "switch") == 0 || strcmp(id, "synchronized") == 0 ||
        strcmp(id, "this") == 0 || strcmp(id, "throw") == 0 || strcmp(id, "throws") == 0 ||
        strcmp(id, "transient") == 0 || strcmp(id, "try") == 0 || strcmp(id, "volatile") == 0 ||
        strcmp(id, "Integer") == 0 || strcmp(id, "System") == 0 || strcmp(id, "null") == 0
    ) {
        emit_value("RESERVED", id);
        yylval.str = strdup(id);
        return RESERVED;
    }

    emit_value("IDENTIFIER", id);
    yylval.str = strdup(id);
    return IDENTIFIER;
}

#define YY_USER_ACTION do { \
    yylloc.first_line = current_line; \
    yylloc.first_column = current_col; \
    yylloc.last_line = current_line; \
    yylloc.last_column = current_col + yyleng - 1; \
    token_line = current_line; \
    token_col = current_col; \
    advance_position(yytext); \
    current_error_yytext = yytext; \
} while (0);
%}

%option noyywrap

DIGIT                [0-9]
IDENTIFIER           [A-Za-z_$][A-Za-z0-9_$]*
NUMSEQ               {DIGIT}|{DIGIT}[0-9_]*{DIGIT}
NATURAL              {DIGIT}|[1-9][0-9_]*{DIGIT}
EXPONENT             [eE][+-]?{NUMSEQ}
DECIMAL              {NUMSEQ}\.{NUMSEQ}?({EXPONENT})?|\.{NUMSEQ}({EXPONENT})?|{NUMSEQ}{EXPONENT}
WHITE_SPACE          [ \t\f\r\n]+

%x COMMENT
%x STR_STATE

%%

"System.out.print" { emit_simple("PRINT"); return PRINT; }
"Integer.parseInt" { emit_simple("PARSEINT"); return PARSEINT; }
".length"          { emit_simple("DOTLENGTH"); return DOTLENGTH; }

"->"  { emit_simple("ARROW"); return ARROW; }
"<<"  { emit_simple("LSHIFT"); return LSHIFT; }
">>"  { emit_simple("RSHIFT"); return RSHIFT; }
"&&"  { emit_simple("AND"); return AND; }
"||"  { emit_simple("OR"); return OR; }
"=="  { emit_simple("EQ"); return EQ; }
"!="  { emit_simple("NE"); return NE; }
">="  { emit_simple("GE"); return GE; }
"<="  { emit_simple("LE"); return LE; }
"++"  { emit_value("RESERVED", yytext); yylval.str = strdup(yytext); return RESERVED; }
"--"  { emit_value("RESERVED", yytext); yylval.str = strdup(yytext); return RESERVED; }

"=" { emit_simple("ASSIGN"); return ASSIGN; }
"*" { emit_simple("STAR"); return STAR; }
"," { emit_simple("COMMA"); return COMMA; }
"/" { emit_simple("DIV"); return DIV; }
">" { emit_simple("GT"); return GT; }
"{" { emit_simple("LBRACE"); return LBRACE; }
"(" { emit_simple("LPAR"); return LPAR; }
"[" { emit_simple("LSQ"); return LSQ; }
"<" { emit_simple("LT"); return LT; }
"-" { emit_simple("MINUS"); return MINUS; }
"%" { emit_simple("MOD"); return MOD; }
"!" { emit_simple("NOT"); return NOT; }
"+" { emit_simple("PLUS"); return PLUS; }
"}" { emit_simple("RBRACE"); return RBRACE; }
")" { emit_simple("RPAR"); return RPAR; }
"]" { emit_simple("RSQ"); return RSQ; }
";" { emit_simple("SEMICOLON"); return SEMICOLON; }
"^" { emit_simple("XOR"); return XOR; }

{DECIMAL} { 
    emit_value("DECIMAL", yytext); 
    yylval.str = strdup(yytext); 
    return DECIMAL; 
}
{NATURAL} { 
    emit_value("NATURAL", yytext); 
    yylval.str = strdup(yytext); 
    return NATURAL; 
}

"\"" {
    string_start_line = token_line;
    string_start_col = token_col;
    string_pos = 0;
    string_has_error = false;
    BEGIN(STR_STATE);
}

<STR_STATE>[^\\"\n\r]+      { append_to_string(yytext); }
<STR_STATE>\\[fnrt\\\"]     { append_to_string(yytext); }
<STR_STATE>\\\r\n|\\\n|\\\r {
    print_invalid_escape_text("\\");
    string_has_error = true;
    print_unterminated_string();
    BEGIN(INITIAL);
}
<STR_STATE>\\[^fnrt\\\"\n\r] { lexical_error_found = true; printf("Line %d, col %d: invalid escape sequence (%s)\n", token_line, token_col, yytext); string_has_error = true; }
<STR_STATE>\\ {
    print_invalid_escape_text("\\");
    string_has_error = true;
}
<STR_STATE>\" {
    string_buffer[string_pos] = '\0';
    BEGIN(INITIAL);
    if (!string_has_error) {
        char *str_with_quotes = (char *)malloc(string_pos + 3);
        sprintf(str_with_quotes, "\"%s\"", string_buffer);
        
        if (emit_tokens) { 
            printf("STRLIT(%s)\n", str_with_quotes); 
        }
        
        yylval.str = str_with_quotes; 
        current_error_yytext = yylval.str;

        yylloc.first_line = string_start_line;
        yylloc.first_column = string_start_col;
        yylloc.last_line = string_start_line;
        yylloc.last_column = string_start_col;

        token_line = string_start_line;
        token_col = string_start_col;
        return STRLIT; 
    }
}
<STR_STATE>\r\n|\n|\r {
    print_unterminated_string();
    BEGIN(INITIAL);
}
<STR_STATE><<EOF>> {
    print_unterminated_string();
    token_line = current_line;
    token_col = current_col;
    current_error_yytext = "";
    return 0;
}

"//"[^\r\n]* { }
"/*" {
    comment_start_line = token_line;
    comment_start_col = token_col;
    BEGIN(COMMENT);
}
<COMMENT>"*/"       { BEGIN(INITIAL); }
<COMMENT>\r\n|\n|\r { }
<COMMENT>.          { }
<COMMENT><<EOF>> {
    lexical_error_found = true;
    printf("Line %d, col %d: unterminated comment\n", comment_start_line, comment_start_col);
    token_line = current_line;
    token_col = current_col;
    current_error_yytext = "";
    return 0;
}

{WHITE_SPACE} { }
{IDENTIFIER}  { return classify_identifier(yytext); }

. { lexical_error_found = true; printf("Line %d, col %d: illegal character (%s)\n", token_line, token_col, yytext); }

<INITIAL><<EOF>> {
    token_line = current_line;
    token_col = current_col;
    current_error_yytext = "";
    return 0;
}

%%