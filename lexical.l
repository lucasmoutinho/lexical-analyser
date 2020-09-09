%{

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int stringLen = 0;
char openParenthesis[] = "(";
char closeParenthesis[] = ")";
int line = 1;
int error_pos = 0;

struct lexError {
    char symbol[100];
    char type[100];
    char message[100];
    int line;
};

struct lexError errors[100];

%}

EOL \n
SEP [{}();]
DELIM [ \t]
WHITESPACE {DELIM}+

LETTER [a-zA-Z]
UNDERSCORE "_"
DIGIT [0-9]

INT "-"?{DIGIT}+
FLOAT "-"?{DIGIT}+"."({DIGIT}*)?
BOOL "true"|"false"
%x STRING 
TYPE "int"|"float"|"bool"|"void"|"string" 

STMT "if"|"while"|"else"|"return"|"for"|"print"|"scan"|"strUpper"|"strLower"
OP "+"|"-"|"*"|"/"
ASSIGN "="
RELOP "<="|"=="|">="|">"|"<"|"!="
LOG "and"|"or"|"not"

ID {LETTER}({LETTER}|{DIGIT}|{UNDERSCORE})*

SYMBOL_ERROR {DIGIT}+({LETTER}|{UNDERSCORE})+

%x COMMENT
/*arrumar na gramatica*/

%%

{EOL} {
    line++;
}

{SEP} {
    printf("SEP\t\t(%s) LENGTH %d\n", yytext, yyleng); 
}

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
    line++;
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

{SYMBOL_ERROR} {
    struct lexError error; 
    strcpy(error.symbol, yytext);
    strcpy(error.type, "NO_SIMBOL");
    strcpy(error.message, "Simbolo nao reconhecido pela analise lexica");
    error.line = line;
    errors[error_pos] = error;
    error_pos++;
}

"/*" {
    BEGIN(COMMENT);
}

<COMMENT>"*/" {
    BEGIN(INITIAL);
}

<COMMENT>\n {line++;}

<COMMENT>. { }

. { 
    struct lexError error; 
    strcpy(error.symbol, yytext);
    strcpy(error.type, "NO_SIMBOL");
    strcpy(error.message, "Simbolo nao reconhecido pela analise lexica");
    error.line = line;
    errors[error_pos] = error;
    error_pos++;
}

%%

void showError(struct lexError error, int current_error){
    printf("------ERROR %d--------\n", current_error + 1);
    printf("Simbolo: %s\n", error.symbol);
    printf("%s\n", error.message);
    printf("Line: %d\n", error.line);
    printf("----------------------\n");
}

int main( int argc, char **argv ) {
    ++argv, --argc;
    if(argc > 0)
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    yylex();

    if(error_pos > 0){
        printf("----------------\n");
        printf("Number of errors: %d\n\n", error_pos);
        int current_error = 0;
        while(current_error < error_pos){
            showError(errors[current_error], current_error);
            current_error++;
        }
    }
}
