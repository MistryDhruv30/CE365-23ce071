%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token IF EXP THEN STMT ELSE NL

%%
// This ensures it evaluates as soon as you hit Enter
input: S NL { printf("Valid string\n"); exit(0); }
     ;

S : IF EXP THEN S S_prime 
  | STMT 
  ;

S_prime : ELSE S 
        | /* epsilon */
        ;
%%

void yyerror(const char *s) {
    printf("Invalid string\n");
    exit(0);
}

int main() {
    printf("Enter string: ");
    yyparse();
    return 0;
}