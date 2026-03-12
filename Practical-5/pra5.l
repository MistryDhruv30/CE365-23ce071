%{
#include<stdio.h>
#include<string.h>

int line = 1;
char sym[100][100];
int count = 0;

void add(char *s)
{
    for(int i=0;i<count;i++)
        if(strcmp(sym[i],s)==0) return;

    strcpy(sym[count++],s);
}
%}

letter  [a-zA-Z_]
digit   [0-9]
id      {letter}({letter}|{digit})*
num     {digit}+(\.{digit}+)?
str     \"([^"])*\"
ch      \'[^']\'

%%

"int"|"char"|"float"|"void"|"return"|"long"|"struct"
        printf("Keyword: %s\n",yytext);

{id}    { printf("Identifier: %s\n",yytext); add(yytext); }

{num}   printf("Constant: %s\n",yytext);

{ch}    printf("Constant: %s\n",yytext);

{str}   printf("String: %s\n",yytext);

"+"|"-"|"*"|"/"|"="|"&"|"."
        printf("Operator: %s\n",yytext);

"(" | ")" | "{" | "}" | ";" | ","
        printf("Punctuation: %s\n",yytext);

"//".*      ;
"/*"([^*]|\n|"*"[^/])*"*/"  ;

\n      line++;
[ \t]   ;

.       printf("Line %d : %s invalid lexeme\n",line,yytext);

%%

int main()
{
    printf("TOKENS\n");
    yylex();

    printf("\nSYMBOL TABLE\n");
    for(int i=0;i<count;i++)
        printf("%d) %s\n",i+1,sym[i]);

    return 0;
}

int yywrap()
{
    return 1;
}
