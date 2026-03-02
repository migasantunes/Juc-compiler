%{
    int line = 1, column = 0;
    char string_buffer[1024];
    int string_pos;
    int string_start_line, string_start_col;

    #define COUNT() do { \
        for (int i = 0; yytext[i] != '\0'; i++) { \
            if (yytext[i] == '\n') { \
                line++; \
                column = 0; \
            } else { \
                column++; \
            } \
        } \
    } while (0)

    #define YY_USER_ACTION do { \
        COUNT(); \
    } while (0);
%}
integer "integer"
double "double"
if "if"
then "then"
else "else"
digit   [0-9]
identifier    [a-zA-Z][a-zA-Z0-9]*
whitespace [ \t\n]+
tokens [()=,*/+-]
%X COMMENT
%X STRING
%%
"\"" { string_pos = 0; string_start_line = line;
       string_start_col = column; BEGIN(STRING); }

<STRING>\\f     { string_buffer[string_pos++] = '\\'; string_buffer[string_pos++] = 'f'; }
<STRING>\\n     { string_buffer[string_pos++] = '\\'; string_buffer[string_pos++] = 'n'; }
<STRING>\\r     { string_buffer[string_pos++] = '\\'; string_buffer[string_pos++] = 'r'; }
<STRING>\\t     { string_buffer[string_pos++] = '\\'; string_buffer[string_pos++] = 't'; }
<STRING>\\\\    { string_buffer[string_pos++] = '\\'; string_buffer[string_pos++] = '\\'; }
<STRING>\\\"    { string_buffer[string_pos++] = '\\'; string_buffer[string_pos++] = '"'; }
<STRING>\\(.)   { printf("Line %d, column %d: invalid escape sequence (\\%s)\n", line, column - 1, yytext + 1); }
<STRING>\"      {string_buffer[string_pos] = '\0'; printf("STRLIT(\"%s\")\n", string_buffer);
                BEGIN(INITIAL); }
<STRING>\n      { printf("Line %d, column %d: unterminated string\n", string_start_line, string_start_col); BEGIN(INITIAL); }
<STRING>\r      { printf("Line %d, column %d: unterminated string\n", string_start_line, string_start_col); BEGIN(INITIAL); }
<STRING>.       { string_buffer[string_pos++] = yytext[0]; }

"/*" { BEGIN(COMMENT); }
<COMMENT>. {;}
<COMMENT>\n {;}
<COMMENT>"*/" { BEGIN(INITIAL); }
{whitespace}            { }
{integer}               { printf("INTEGER\n"); }
{double}                { printf("DOUBLE\n"); }
{if}                    { printf("IF\n"); }
{then}                  { printf("THEN\n"); }
{else}                  { printf("ELSE\n"); }
{digit}+                { printf("NATURAL(%s)\n", yytext); }
{digit}*"."{digit}+     { printf("DECIMAL(%s)\n", yytext); }
{identifier}            { printf("IDENTIFIER(%s)\n", yytext); }
{tokens}                { printf("%s\n", yytext); }
.                       { printf("error in line %d, column %d: unrecognized character (%s)\n", line, column, yytext); line = 0; column = 0;}
%%
extern int yylex();
int main() {
    yylex();    /* run the lexical analysis automaton */
    return 0;
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}