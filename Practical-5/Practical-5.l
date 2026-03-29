%{
#include <stdio.h>
#include <string.h>
int line = 1;
int sym_count = 0;
char symbol_table[100][100];
void add_symbol(char *id)
{
    int i;
    for(i=0;i<sym_count;i++)
    {
        if(strcmp(symbol_table[i], id)==0)
            return;
    }
    strcpy(symbol_table[sym_count++], id);
}
%}
%option noyywrap
digit      [0-9]
letter     [a-zA-Z]
id         {letter}({letter}|{digit})*
number     {digit}+(\.{digit}+)?
%%
"int"|"char"|"float"|"return"|"void"|"long"|"struct"   { printf("Keyword: %s\n", yytext); }
{id}        { 
                printf("Identifier: %s\n", yytext);
                add_symbol(yytext);
            }
{number}    { printf("Constant: %s\n", yytext); }
\'[^']\'    { printf("Constant: %s\n", yytext); }
\"[^\"\n]*\"  { printf("String: %s\n", yytext); }
"="|"+"|"-"|"*"|"/"  { printf("Operator: %s\n", yytext); }
"("|")"|"{"|"}"|";"|","  { printf("Punctuation: %s\n", yytext); }
[0-9]+[a-zA-Z]+  { printf("Line %d: %s invalid lexeme\n", line, yytext); }
"//".*      { }
"/*"([^*]|\*+[^*/])*\*+"/"  { }
[ \t]+      { }
\n          { line++; }
.           { }
%%
int main()
{
    int i;
    printf("TOKENS\n");
    yylex();
    printf("\nSYMBOL TABLE ENTRIES\n");
    for(i=0;i<sym_count;i++)
    {
        printf("%d) %s\n", i+1, symbol_table[i]);
    }
    return 0;
}
