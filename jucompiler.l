%{
#include <stdio.h>
#include <string.h>

static int current_line = 1;
static int current_col = 1;
static int token_line = 1;
static int token_col = 1;

static bool emit_tokens = false;

static int comment_start_line = 1;
static int comment_start_col = 1;

static int string_start_line = 1;
static int string_start_col = 1;
static bool string_has_error = false;

static char string_buffer[8192];
static int string_pos = 0;

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

static void append_to_string(const char *text) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (string_pos < (int)sizeof(string_buffer) - 1) {
            string_buffer[string_pos++] = text[i];
        }
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
    printf("Line %d, col %d: invalid escape sequence (%s)\n", token_line, token_col, text);
}

static void print_unterminated_string(void) {
    printf("Line %d, col %d: unterminated string literal\n", string_start_line, string_start_col);
}

static void classify_identifier(const char *id) {
    if (strcmp(id, "boolean") == 0) { emit_simple("BOOL"); return; }
    if (strcmp(id, "class") == 0) { emit_simple("CLASS"); return; }
    if (strcmp(id, "double") == 0) { emit_simple("DOUBLE"); return; }
    if (strcmp(id, "else") == 0) { emit_simple("ELSE"); return; }
    if (strcmp(id, "if") == 0) { emit_simple("IF"); return; }
    if (strcmp(id, "int") == 0) { emit_simple("INT"); return; }
    if (strcmp(id, "public") == 0) { emit_simple("PUBLIC"); return; }
    if (strcmp(id, "return") == 0) { emit_simple("RETURN"); return; }
    if (strcmp(id, "static") == 0) { emit_simple("STATIC"); return; }
    if (strcmp(id, "String") == 0) { emit_simple("STRING"); return; }
    if (strcmp(id, "void") == 0) { emit_simple("VOID"); return; }
    if (strcmp(id, "while") == 0) { emit_simple("WHILE"); return; }
    if (strcmp(id, "true") == 0 || strcmp(id, "false") == 0) { emit_value("BOOLLIT", id); return; }

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
        strcmp(id, "Integer") == 0 || strcmp(id, "System") == 0
    ) {
        emit_value("RESERVED", id);
        return;
    }

    if (strcmp(id, "null") == 0) {
        emit_value("RESERVED", id);
        return;
    }

    emit_value("IDENTIFIER", id);
}

#define YY_USER_ACTION do { \
    token_line = current_line; \
    token_col = current_col; \
    advance_position(yytext); \
} while (0);
%}

%option noyywrap

DIGIT       [0-9]
ID_START    [A-Za-z_$]
ID_PART     [A-Za-z0-9_$]
IDENTIFIER  {ID_START}{ID_PART}*
NUMSEQ      {DIGIT}([0-9_]*{DIGIT})?
NATURAL     0|[1-9]([0-9_]*{DIGIT})?
EXPONENT    [eE][+-]?{NUMSEQ}
DECIMAL    {NUMSEQ}\.{NUMSEQ}?({EXPONENT})?|\.{NUMSEQ}({EXPONENT})?|{NUMSEQ}{EXPONENT}
WHITE_SPACE          [ \t\f\r\n]+

%x COMMENT
%x STRING

%%

"System.out.print"      { emit_simple("PRINT"); }
"Integer.parseInt"      { emit_simple("PARSEINT"); }
".length"               { emit_simple("DOTLENGTH"); }

"->"                    { emit_simple("ARROW"); }
"<<"                    { emit_simple("LSHIFT"); }
">>"                    { emit_simple("RSHIFT"); }
"&&"                    { emit_simple("AND"); }
"||"                    { emit_simple("OR"); }
"=="                    { emit_simple("EQ"); }
"!="                    { emit_simple("NE"); }
">="                    { emit_simple("GE"); }
"<="                    { emit_simple("LE"); }
"++"                    { emit_value("RESERVED", yytext); }
"--"                    { emit_value("RESERVED", yytext); }

"="                     { emit_simple("ASSIGN"); }
"*"                     { emit_simple("STAR"); }
","                     { emit_simple("COMMA"); }
"/"                     { emit_simple("DIV"); }
">"                     { emit_simple("GT"); }
"{"                     { emit_simple("LBRACE"); }
"("                     { emit_simple("LPAR"); }
"["                     { emit_simple("LSQ"); }
"<"                     { emit_simple("LT"); }
"-"                     { emit_simple("MINUS"); }
"%"                     { emit_simple("MOD"); }
"!"                     { emit_simple("NOT"); }
"+"                     { emit_simple("PLUS"); }
"}"                     { emit_simple("RBRACE"); }
")"                     { emit_simple("RPAR"); }
"]"                     { emit_simple("RSQ"); }
";"                     { emit_simple("SEMICOLON"); }
"^"                     { emit_simple("XOR"); }

{DECIMAL}                       { emit_value("DECIMAL", yytext); }
{NATURAL}                       { emit_value("NATURAL", yytext); }

"\"" {
    string_start_line = token_line;
    string_start_col = token_col;
    string_pos = 0;
    string_has_error = false;
    BEGIN(STRING);
}

<STRING>[^\\"\n\r]+   { append_to_string(yytext); }
<STRING>\\[fnrt\\\"]  { append_to_string(yytext); }
<STRING>\\\r\n|\\\n|\\\r {
    print_invalid_escape_text("\\");
    string_has_error = true;
    print_unterminated_string();
    BEGIN(INITIAL);
}
<STRING>\\[^fnrt\\\"\n\r] {printf("Line %d, col %d: invalid escape sequence (%s)\n", token_line, token_col, yytext); string_has_error = true; }
<STRING>\\ {
    print_invalid_escape_text("\\");
    string_has_error = true;
}
<STRING>\" {
    string_buffer[string_pos] = '\0';
    if (!string_has_error && emit_tokens) {
        printf("STRLIT(\"%s\")\n", string_buffer);
    }
    BEGIN(INITIAL);
}
<STRING>\r\n|\n|\r {
    print_unterminated_string();
    BEGIN(INITIAL);
}
<STRING><<EOF>> {
    print_unterminated_string();
    return 0;
}

"//"[^\r\n]*            { }
"/*" {
    comment_start_line = token_line;
    comment_start_col = token_col;
    BEGIN(COMMENT);
}
<COMMENT>"*/"             { BEGIN(INITIAL); }
<COMMENT>\r\n|\n|\r     { }
<COMMENT>.                { }
<COMMENT><<EOF>> {
    printf("Line %d, col %d: unterminated comment\n", comment_start_line, comment_start_col);
    return 0;
}

{WHITE_SPACE}                      { }
{IDENTIFIER}              { classify_identifier(yytext); }

.                         { printf("Line %d, col %d: illegal character (%s)\n", token_line, token_col, yytext); }

%%

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "-l") == 0) {
        emit_tokens = true;
    } else {
        emit_tokens = false;
    }

    yylex();
    return 0;
}