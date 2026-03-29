%{
#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
void yyerror(const char *s);
int yylex();
%}

%token INT FLOAT DOUBLE CHAR BOOL
%token ID NUMBER CHAR_LITERAL
%token ASSIGN COMMA LBRACKET RBRACKET SEMICOLON

%%

program:
    declaration_list
    { printf("All declarations are valid.\n"); }
;

declaration_list:
    declaration
  | declaration_list declaration
;

declaration:
    type varlist SEMICOLON
;

type:
    INT | FLOAT | DOUBLE | CHAR | BOOL
;

varlist:
    var
  | var COMMA varlist
;

var:
    ID
  | ID ASSIGN value
  | ID LBRACKET NUMBER RBRACKET
;

value:
    NUMBER
  | CHAR_LITERAL
;

%%

void yyerror(const char *s) {
    printf("Syntax Error at line %d\n", yylineno);
}

int main(int argc, char *argv[]) {
    extern FILE *yyin;
    if (argc < 2) {
        printf("Usage: parser.exe <filename>\n");
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }
    yyparse();
    fclose(yyin);
    return 0;
}
