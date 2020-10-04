%error-verbose
%debug
%locations

%{
#include <stdlib.h>
#include <stdio.h>

int yylex();
void yyerror(const char* msg) {
    fprintf(stderr, "%s\n", msg);
}
extern FILE *yyin;

%}

%token SEP
%token INT FLOAT BOOL STRING
%token TYPE
%token STMT
%token ASSIGN OP RELOP LOG
%token ID

%start prog
%%

prog: 
    decl-list {printf("%d", $1);}
;

decl-list: 
    decl-list var-decl {printf("%d %d", $1, $2);}
    | var-decl {printf("%d", $1);}
    | decl-list func {printf("%d %d", $1, $2);}
    | func {printf("%d", $1);}
;

var-decl:
    TYPE ID ';' {printf("%d %d %d", $1, $2, $3);}
;

func:
    TYPE ID '(' params ')' comp-stmt {printf("%d %d %d %d %d %d", $1, $2, $3, $4, $5, $6);}
;

params:
    params ',' TYPE ID {printf("%d %d %d", $1, $3, $4);}
    | TYPE ID {printf("%d %d", $1, $2);}
    | {}
;

comp-stmt:
    '{' local-decl stmt-list '}' {printf("%d %d", $2, $3);}
;

local-decl:
    local-decl TYPE ID ';' {printf("%d %d %d %d", $1, $2, $3, $4);}
    | {}
;

stmt-list:
    stmt-list stmt {printf("%d %d", $1, $2);}
    | {}
;

stmt: 
    expr {printf("%d", $1);}
    | conditional-stmt {printf("%d", $1);}
    | iteration-stmt {printf("%d", $1);}
    | return-stmt {printf("%d", $1);}
    | PRINT '(' STRING ')' {printf("%d %d", $1, $3);}
    | PRINT '(' ID ')' {printf("%d %d", $1, $3);}
    | SCAN '(' ID ')' {printf("%d %d", $1, $3);}
    | STRCONCAT '(' STRING ',' STRING ')' {printf("%d %d %d", $1, $3, $5);}
    | STRCOMPARE '(' STRING ',' STRING ')' {printf("%d %d %d", $1, $3, $5);}
    | STRCOPY '(' STRING ',' STRING ')' {printf("%d %d %d", $1, $3, $5);}
    | STRINSERT '(' STRING ',' STRING ',' ID ')' {printf("%d %d %d %d", $1, $3, $5, $7);}
    | STRUPPER '(' STRING ')' {printf("%d %d", $1, $3);}
    | STRLOWER '(' STRING ')' {printf("%d %d", $1, $3);}
;

expr:
    var ASSIGN expr {printf("%d %d", $1, $3);}
    | simple-expr {printf("%d", $1);}
;

simple-expr:
    op-expr RELOP op-expr {printf("%d %d", $1, $3);}
    | op-expr {printf("%d", $1);}
    | op-log {printf("%d", $1);}
;

conditional-stmt:
    IF '(' expr ')' comp-stmt {printf("%d %d %d", $1, $3, $5);}
    | IF '(' expr ')' comp-stmt ELSE comp-stmt {printf("%d %d %d %d", $1, $3, $5, $7);}
;

iteration-stmt:
    WHILE '(' expr ')' comp-stmt {printf("%d %d %d", $1, $3, $5);}
;

return-stmt:
    RETURN expr ';' {printf("%d %d", $1, $2);}
    | RETURN ';'
;

var:
    ID {printf("%d", $1);}
;

op-expr:
    op-expr OP term {printf("%d %d %d", $1, $2, $3);}
    | term {printf("%d", $1);}
;

op-log:
    op-log LOG term {printf("%d %d %d", $1, $2, $3);}
    | BOOL {printf("%d", $1);}
;

term:
    '(' simple-expr ')' {printf("%d", $2);}
    | var {printf("%d", $1);}
    | call {printf("%d", $1);}
    | STRING {printf("%d", $1);}
    | INT {printf("%d", $1);}
    | FLOAT {printf("%d", $1);}
;

call:
    ID '(' args ')' {printf("%d %d", $1, $3);}
;

args:
    arg-list {printf("%d", $1);}
    | {}
;

arg-list:
    arg-list ',' simple-expr {printf("%d %d", $1, $3);}
    | simple-expr {printf("%d", $1);}
;

%%

int main( int argc, char **argv ) {
    ++argv, --argc;
    if(argc > 0)
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    yylex();
    yylex_destroy();
    yyparse();
}