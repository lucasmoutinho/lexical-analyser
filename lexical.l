%option nounput
%option noinput

%{

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "syntax.tab.h"

// Variáveis globais
char openParenthesis[] = "(";
char closeParenthesis[] = ")";
int stringLen = 0;
int line = 1;
int lex_error = 0;
int inside_string = 0;
int total_errors = 0;

// Declarações de funções
void lexical_error_unrecognizable_symbol(char* symbol);
void yyerror(const char* msg);

%}
%option noyywrap

EOL \n
DELIM [ \t]
WHITESPACE {DELIM}+

LETTER [a-zA-Z]
UNDERSCORE "_"
DIGIT [0-9]

INT "-"?{DIGIT}+
FLOAT "-"?{DIGIT}+"."({DIGIT}*)?
BOOL "true"|"false"
%s STRING
STR [^\"]*
TYPE "int"|"float"|"bool"|"void"|"string" 

OP "+"|"-"|"*"|"/"
ASSIGN "="
RELOP "<="|"=="|">="|">"|"<"|"!="
LOG "&&"|"||"|"!"

ID {LETTER}({LETTER}|{DIGIT}|{UNDERSCORE})*

QUOTES \"

%x COMMENT

%%

{EOL} {
    line++;
}

{WHITESPACE} { }

<INITIAL,STRING>{QUOTES} {
    if(inside_string) { 
        BEGIN(0);
        inside_string--;
        // printf("%s%s\n", yytext, closeParenthesis);
        return QUOTES;
    }
    else { 
        BEGIN(STRING);
        inside_string++;
        // printf("STRING\t\t%s%s", openParenthesis, yytext);
        return QUOTES;
    }
}


<STRING>{STR} { 
    if(strcmp(yytext, "\n") == 0){line++;} 
    // printf("%s", yytext);
    yylval.str = (char *) strdup(yytext);
    return STR; 
}

{INT} {
    // printf("INT\t\t(%s) LENGTH %d\n", yytext, yyleng);
    yylval.str = (char *) strdup(yytext);
    return INT; 
}

{FLOAT} {
    // printf("FLOAT\t\t(%s) LENGTH %d\n", yytext, yyleng);
    yylval.str = (char *) strdup(yytext);
    return FLOAT; 
}

{BOOL} {
    // printf("BOOL\t\t(%s) LENGTH %d\n", yytext, yyleng);
    yylval.str = (char *) strdup(yytext);
    return BOOL; 
}


{TYPE} {
    // printf("TYPE\t\t(%s) LENGTH %d\n", yytext, yyleng);
    yylval.str = (char *) strdup(yytext);
    return TYPE;
}

"if" {
    // printf("IF\n");
    yylval.str = (char *) strdup(yytext);
    return IF;
}
"else" {
    // printf("ELSE\n");
    yylval.str = (char *) strdup(yytext);
    return ELSE;
}
"while" {
    // printf("WHILE\n");
    yylval.str = (char *) strdup(yytext);
    return WHILE;
}
"return" {
    // printf("RETURN\n");
    yylval.str = (char *) strdup(yytext);
    return RETURN;
}
"print" {
    // printf("PRINT\n");
    yylval.str = (char *) strdup(yytext);
    return PRINT;
}
"scan" {
    // printf("SCAN\n");
    yylval.str = (char *) strdup(yytext);
    return SCAN;
}
"strUpper" {
    // printf("STRUPPER\n");
    yylval.str = (char *) strdup(yytext);
    return STRUPPER;
}
"strLower" {
    // printf("STRLOWER\n");
    yylval.str = (char *) strdup(yytext);
    return STRLOWER;
}
"strConcat" {
    // printf("STRCONCAT\n");
    yylval.str = (char *) strdup(yytext);
    return STRCONCAT;
}
"strCopy" {
    // printf("STRCOPY\n");
    yylval.str = (char *) strdup(yytext);
    return STRCOPY;
}
"strInsert" {
    // printf("STRINSERT\n");
    yylval.str = (char *) strdup(yytext);
    return STRINSERT;
}

{OP} {
    // printf("OP\t\t(%s) LENGTH %d\n", yytext, yyleng);
    yylval.str = (char *) strdup(yytext);
    return OP;
}

{ASSIGN} {
    // printf("ASSIGN\t\t(%s) LENGTH %d\n", yytext, yyleng);
    yylval.str = (char *) strdup(yytext);
    return ASSIGN;
}

{RELOP} {
    // printf("RELOP\t\t(%s) LENGTH %d\n", yytext, yyleng);
    yylval.str = (char *) strdup(yytext);
    return RELOP;
}

{LOG} {
    // printf("LOG\t\t(%s) LENGTH %d\n", yytext, yyleng);
    yylval.str = (char *) strdup(yytext);
    return LOG;
}

{ID} {
    // printf("ID\t\t(%s) LENGTH %d ADDRESS %d\n", yytext, yyleng, address);
    yylval.str = (char *) strdup(yytext);
    return ID;
}

"/*" {
    BEGIN(COMMENT);
}

<COMMENT>"*/" {
    BEGIN(INITIAL);
}

<COMMENT>\n {line++;}

<COMMENT>. { }

"," {
    return yytext[0];
}

";" {
    return yytext[0];
}

"(" {
    return yytext[0];
}

")" {
    return yytext[0];
}

"{" {
    return yytext[0];
}

"}" {
    return yytext[0];
}

. {
    lexical_error_unrecognizable_symbol(yytext);
}

%%

void yyerror(const char* msg) {
    fprintf(stderr, "\n%s -- linha: %d\n", msg, line);
    total_errors++;
}

void lexical_error_unrecognizable_symbol(char* symbol){
    char *error = (char *)malloc((strlen(symbol) + 1 + 35) * sizeof(char)); // +1 for the null-terminator and 35 for lex error message
    sprintf(error, "lexical error, unrecognizable symbol %s", symbol);
    yyerror(error);
    free(error);
}
