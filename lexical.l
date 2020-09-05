%{

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

stringLen = 0

%}

SEPARATOR [{}();] // arrumar na gramática
DELIM [ \n\t]
WHITESPACE [{DELIM}+] // arrumar na gramática

LETTER [a-zA-Z]
DIGIT [0-9]

ID {LETTER}({LETTER}|{DIGIT})*
INT "-"?{DIGIT}+ //arrumar na gramatica
FLOAT "-"?{DIGIT}+"."({DIGIT}*)?
BOOL "true"|"false"
%x STRING //arrumar na gramatica
TYPE "int"|"float"|"bool"|"void"|"string" // arrumar string na gramatica

STMT "if"|"while"|"else"|"return"|"for"|"print"|"scan"|"strUpper"|"strLower"
OP "+"|"-"|"*"|"/"
RELOP "<="|"=="|">="|">"|"<"|"!="
LOG "and" | "or"
OPASSIGN "=" // arrumar na gramatica

%x COMMENT //arrumar na gramática

%%

{SEPARATOR} {}

{WHITESPACE} {}

{ID} {
    printf("ID  (%s) LENGTH %d\n", yytext, yyleng); 
}

{INT} {
    printf("INT (%s) LENGTH %d\n", yytext, yyleng); 
}

{FLOAT} {
    printf("FLOAT   (%s) LENGTH %d\n", yytext, yyleng); 
}

{BOOL} {
    printf("BOOL   (%s) LENGTH %d\n", yytext, yyleng); 
}

\" {
    printf("STRING  (%c)", yytext);
    stringLen += 1;
    BEGIN(STRING);
}

<STRING>\" {
    stringLen += 1
    printf("(%c) LENGTH %d\n", yytext, stringLen);
    stringLen = 0
    BEGIN(INITIAL);
}

<STRING>\n {
    printf("(%c)", yytext);
    stringLen += 1;
}

<STRING>. {
    printf("(%c)", yytext);
    stringLen += 1;
}

{TYPE} {
    printf("TYPE    (%s) LENGTH %d\n", yytext, yyleng);
}

{STMT} {
    printf("STMT    (%s) LENGTH %d\n", yytext, yyleng);
}

{OP} {
    printf("OP  (%s) LENGTH %d\n", yytext, yyleng);
}

{RELOP} {
    printf("RELOP   (%s) LENGTH %d\n", yytext, yyleng);
}

{LOG} {
    printf("LOG (%s) LENGTH %d\n", yytext, yyleng);
}

{OPASSIGN} {
    printf("OPASSIGN    (%s) LENGTH %d\n", yytext, yyleng);
}

"/*" {
    BEGIN(C_COMMENT);
}

<COMMENT>"*/" {
    BEGIN(INITIAL);
}

<COMMENT>\n {}

<COMMENT>. {}

%%

int main( int argc, char **argv ) {
    ++argv, --argc;
    if(argc > 0)
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    yylex();
}
