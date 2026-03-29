%{
#include <stdio.h>
#include <string.h>

char line[1000];
%}

%%

[Cc][Hh][Aa][Rr][Uu][Ss][Aa][Tt]    { printf("university"); }

.    { printf("%s", yytext); }

\n   { printf("\n"); }

%%

int main()
{
    YY_BUFFER_STATE bp;

    while(fgets(line, sizeof(line), stdin))
    {
        bp = yy_scan_string(line);  // create buffer
        yylex();
        yy_delete_buffer(bp);       // delete buffer (IMPORTANT FIX)
    }
    return 0;
}

int yywrap()
{
    return 1;
}