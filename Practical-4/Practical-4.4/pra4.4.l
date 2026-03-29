%{
#include <stdio.h>
#include <string.h>

int lower, upper, digit, symbol, len;
%}

%%

[a-zA-Z0-9*;#$@]+    {
                        len = yyleng;
                        lower = upper = digit = symbol = 0;

                        for(int i = 0; i < len; i++) {
                            char c = yytext[i];
                            if(c >= 'a' && c <= 'z') lower = 1;
                            else if(c >= 'A' && c <= 'Z') upper = 1;
                            else if(c >= '0' && c <= '9') digit = 1;
                            else if(c == '*' || c == ';' || c == '#' || c == '$' || c == '@') symbol = 1;
                        }

                        if(len >= 9 && len <= 15 && lower && upper && digit && symbol)
                            printf("Valid password\n");
                        else
                            printf("Invalid password\n");
                     }

\n                   { return 0; }   /* stop at newline */

.                    { /* ignore any other characters */ }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter password (newline to end):\n");
    yylex();
    return 0;
}
