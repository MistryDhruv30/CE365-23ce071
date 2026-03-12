%{
#include <stdio.h>

int chars = 0;
int words = 0;
int lines = 0;
int inWord = 0;
%}

%%

[ \t]+        { 
                chars += yyleng; 
                inWord = 0; 
             }

\n            { 
                chars++; 
                lines++; 
                inWord = 0; 
                /* Stop after first newline as per practical */
                return 0;  
             }

.             { 
                chars++; 
                if(!inWord) { words++; inWord = 1; }
             }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter a line of text (terminated by Enter):\n");
    yylex();
    printf("\nCharacters : %d\n", chars);
    printf("Words : %d\n", words);
    printf("Lines : %d\n", lines);
    return 0;
}
