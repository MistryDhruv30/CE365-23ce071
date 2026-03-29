%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void yyerror(const char *s);
int yylex();
%}

%union {
    double dval;
}

%token <dval> NUMBER
%type <dval> E T F G

%left '+' '-'
%left '*' '/'
%right '^'

%%
Line: E '\n' { printf("%.10g\n", $1); exit(0); }
    | '\n'   { exit(0); }
    ;

E: E '+' T { $$ = $1 + $3; }
 | E '-' T { $$ = $1 - $3; }
 | T       { $$ = $1; }
 ;

T: T '*' F { $$ = $1 * $3; }
 | T '/' F { if($3 == 0) { yyerror("div zero"); exit(0); } $$ = $1 / $3; }
 | F       { $$ = $1; }
 ;

F: G '^' F { $$ = pow($1, $3); }
 | G       { $$ = $1; }
 ;

G: '(' E ')' { $$ = $2; }
 | NUMBER    { $$ = $1; }
 ;

%%
void yyerror(const char *s) {
    printf("Invalid expression\n");
}

int main() {
    yyparse();
    return 0;
}