%{
    #include "hel.tab.h"
%}

number ([0-9])+
string ([a-z])+

%%

"\n" {return EOL;}
{number} {yylval.num = atoi(yytext); return (NUM);}

";"     {return (SEMICOLON);}
"+"     {return PLUS;}
"-"     {return MINUS;}
"*"     {return TIMES;}
"/"     {return DIVIDED_BY;}
"="     {return EQUALS;}
"\""    {return DQUOTES;}
"("     {return LPAREN;}
")"     {return RPAREN;}
"{"     {return LBRACKET;}
"}"     {return RBRACKET;}

"int" {yylval.num = TYPE_INT; return TYPE_INT;}

"show" {return KW_SHOW;}
"if" {return KW_IF;}

"debug" {return DEBUG;}
{string} {yylval.string = yytext; return STRING;}
. {}


%%

yywrap();

