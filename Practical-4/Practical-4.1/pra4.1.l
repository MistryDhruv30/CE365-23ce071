%option noyywrap
%{
#include <stdio.h>
%}

%%
[0-9]+    { printf("%s\n", yytext); }
.|\n      ;
%%

int main()
{
    yylex();
    return 0;
}
