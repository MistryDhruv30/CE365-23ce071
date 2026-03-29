%{
#include "parser.tab.h"
int yylineno = 1;
%}

%%

"int"           { return INT; }
"float"         { return FLOAT; }
"double"        { return DOUBLE; }
"char"          { return CHAR; }
"bool"          { return BOOL; }

[a-zA-Z_][a-zA-Z0-9_]*     { return ID; }
[0-9]+(\.[0-9]+)?           { return NUMBER; }
\'[^\']\' { return CHAR_LITERAL; }

"="             { return ASSIGN; }
","             { return COMMA; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
";"             { return SEMICOLON; }

[ \t]+          { /* skip whitespace */ }
\n              { yylineno++; }

.               { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() { return 1; }
