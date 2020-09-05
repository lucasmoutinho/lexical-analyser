%{

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int stringLen = 0;
char openParenthesis[] = "(";
char closeParenthesis[] = ")";

%}

SEPARATOR [{}();]
/*arrumar na gramatica*/
DELIM [ \n\t]
WHITESPACE {DELIM}+
/*arrumar na gramatica*/

LETTER [a-zA-Z]
UNDERSCORE "_"
DIGIT [0-9]

INT "-"?{DIGIT}+
/*arrumar na gramatica*/
FLOAT "-"?{DIGIT}+"."({DIGIT}*)?
BOOL "true"|"false"
%x STRING 
/*arrumar na gramatica*/
TYPE "int"|"float"|"bool"|"void"|"string" 
/*arrumar na gramatica*/

STMT "if"|"while"|"else"|"return"|"for"|"print"|"scan"|"strUpper"|"strLower"
OP "+"|"-"|"*"|"/"
ASSIGN "="
RELOP "<="|"=="|">="|">"|"<"|"!="
LOG "and"|"or"
/*arrumar na gramatica*/

ID {LETTER}({LETTER}|{DIGIT}|{UNDERSCORE})*

%x COMMENT
/*arrumar na gramatica*/

%%

{SEPARATOR} { }

{WHITESPACE} { }

{INT} {
    printf("INT\t\t(%s) LENGTH %d\n", yytext, yyleng); 
}

{FLOAT} {
    printf("FLOAT\t\t(%s) LENGTH %d\n", yytext, yyleng); 
}

{BOOL} {
    printf("BOOL\t\t(%s) LENGTH %d\n", yytext, yyleng); 
}

\" {
    printf("STRING\t\t%s%s", openParenthesis, yytext);
    stringLen += 1;
    BEGIN(STRING);
}

<STRING>\" {
    stringLen += 1;
    printf("%s%s LENGTH %d\n", yytext, closeParenthesis, stringLen);
    stringLen = 0;
    BEGIN(INITIAL);
}

<STRING>\n {
    printf("%s", yytext);
    stringLen += 1;
}

<STRING>. {
    printf("%s", yytext);
    stringLen += 1;
}

{TYPE} {
    printf("TYPE\t\t(%s) LENGTH %d\n", yytext, yyleng);
}

{STMT} {
    printf("STMT\t\t(%s) LENGTH %d\n", yytext, yyleng);
}

{OP} {
    printf("OP\t\t(%s) LENGTH %d\n", yytext, yyleng);
}

{ASSIGN} {
    printf("ASSIGN\t\t(%s) LENGTH %d\n", yytext, yyleng);
}

{RELOP} {
    printf("RELOP\t\t(%s) LENGTH %d\n", yytext, yyleng);
}

{LOG} {
    printf("LOG\t\t(%s) LENGTH %d\n", yytext, yyleng);
}

{ID} {
    printf("ID\t\t(%s) LENGTH %d\n", yytext, yyleng); 
}

"/*" {
    BEGIN(COMMENT);
}

<COMMENT>"*/" {
    BEGIN(INITIAL);
}

<COMMENT>\n { }

<COMMENT>. { }

%%

int main( int argc, char **argv ) {
    ++argv, --argc;
    if(argc > 0)
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    yylex();
}
