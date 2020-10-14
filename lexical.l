%{

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "syntax.tab.h"

int stringLen = 0;
char openParenthesis[] = "(";
char closeParenthesis[] = ")";
int line = 1;
int error_pos = 0;
int tableSize = 0;

struct lexError {
    char symbol[100];
    char type[100];
    char message[100];
    int line;
};

struct lexError errors[100];

struct symbolItem {
    char symbol[100];
};

struct symbolItem symbolTable[500];

int insertTable();

int inside_string = 0;
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
STR [^"]*
TYPE "int"|"float"|"bool"|"void"|"string" 

OP "+"|"-"|"*"|"/"
ASSIGN "="
RELOP "<="|"=="|">="|">"|"<"|"!="
LOG "and"|"or"|"not"

ID {LETTER}({LETTER}|{DIGIT}|{UNDERSCORE})*

QUOTES \"

%x COMMENT

%%

{EOL} {
    line++;
}

{WHITESPACE} { }

{INT} {
    printf("INT\t\t(%s) LENGTH %d\n", yytext, yyleng);
    return INT; 
}

{FLOAT} {
    printf("FLOAT\t\t(%s) LENGTH %d\n", yytext, yyleng);
    return FLOAT; 
}

{BOOL} {
    printf("BOOL\t\t(%s) LENGTH %d\n", yytext, yyleng);
    return BOOL; 
}


<INITIAL,STRING>{QUOTES} {
    if(inside_string) { BEGIN(0); inside_string--; printf("%s%s\n", yytext, closeParenthesis); return QUOTES;}
    else              { BEGIN(STRING); inside_string++; printf("STRING\t\t%s%s", openParenthesis, yytext); return QUOTES;}
}


<STRING>{STR} { if(yytext == "\n"){line++;} 
                printf("%s", yytext); return STR; 
}


{TYPE} {
    printf("TYPE\t\t(%s) LENGTH %d\n", yytext, yyleng);
    return TYPE;
}

"if" { printf("IF\n"); return IF; }
"else" { printf("ELSE\n"); return ELSE; }
"while" { printf("WHILE\n"); return WHILE; }
"return" { printf("RETURN\n"); return RETURN; }
"print" { printf("PRINT\n"); return PRINT; }
"scan" { printf("SCAN\n"); return SCAN; }
"strUpper" { printf("STRUPPER\n"); return STRUPPER; }
"strLower" { printf("STRLOWER\n"); return STRLOWER; }
"strConcat" { printf("STRCONCAT\n"); return STRCONCAT; }
"strCompare" { printf("CTRCOMPARE\n"); return STRCOMPARE; }
"strCopy" { printf("STRCOPY\n"); return STRCOPY; }
"strInsert" { printf("STRINSERT\n"); return STRINSERT; }

{OP} {
    printf("OP\t\t(%s) LENGTH %d\n", yytext, yyleng);
    return OP;
}

{ASSIGN} {
    printf("ASSIGN\t\t(%s) LENGTH %d\n", yytext, yyleng);
    return ASSIGN;
}

{RELOP} {
    printf("RELOP\t\t(%s) LENGTH %d\n", yytext, yyleng);
    return RELOP;
}

{LOG} {
    printf("LOG\t\t(%s) LENGTH %d\n", yytext, yyleng);
    return LOG;
}

{ID} {
    int address = insertTable(yytext);
    printf("ID\t\t(%s) LENGTH %d ADDRESS %d\n", yytext, yyleng, address);
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

. {
    return yytext[0];
}

%%

int insertTable(char symbol[100]){
    int i = 0;
    int address = -1;
    while(i < tableSize && address == -1){
        if(strcmp(symbolTable[i].symbol, symbol) == 0){
            address = i;
        }
        i++;
    }
    if(address == -1){
        strcpy(symbolTable[tableSize].symbol, symbol);
        address = tableSize;
        tableSize++;
    }
    return address;
}

void showSymbolTable(){
    int address = 0;
    printf("\n\n------SYMBOL TABLE--------\n");
    while(address < tableSize){
        printf("%d -- Simbolo: %s\n", address, symbolTable[address].symbol);
        address++;
    }
    printf("----------------------\n\n\n");
}

void showError(){
    printf("----------------------\n");
    printf("Number of errors: %d\n\n", error_pos);
    int current_error = 0;
    while(current_error < error_pos){
        printf("------ERROR %d--------\n", current_error + 1);
        printf("Simbolo: %s\n", errors[current_error].symbol);
        printf("%s\n", errors[current_error].message);
        printf("Line: %d\n", errors[current_error].line);
        printf("----------------------\n");
        current_error++;
    }
}
