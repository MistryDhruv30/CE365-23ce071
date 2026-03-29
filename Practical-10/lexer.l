%{
#include "parser.tab.h"
#include <stdlib.h>
%}
%%
[0-9]+(\.[0-9]+)? { yylval.dval = atof(yytext); return NUMBER; }
"+"|"-"|"*"|"/"|"^"|"("|")"|"\n" { return yytext[0]; }
[ \t] { ; }
. { return yytext[0]; }
%%
int yywrap() { return 1; }