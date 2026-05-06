#include <stdio.h>
extern int yylex();
extern int token_line;
extern int token_col;
extern char *yytext;
int main() {
    int tok;
    while ((tok = yylex()) != 0) {
        printf("tok: %d, line: %d, col: %d, text: '%s'\n", tok, token_line, token_col, yytext);
    }
    printf("EOF line: %d, col: %d\n", token_line, token_col);
    return 0;
}
