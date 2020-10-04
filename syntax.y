%error-verbose
%debug
%locations

%{
#include <stdlib.h>
#include <stdio.h>

int yylex();
extern int yylex_destroy(void);
void yyerror(const char* msg) {
    fprintf(stderr, "%s\n", msg);
}
extern FILE *yyin;

%}

%union {
    int qc;
}

%token <qc> INT FLOAT BOOL STRING
%token <qc> TYPE
%token <qc> IF ELSE WHILE RETURN PRINT SCAN 
%token <qc> STRUPPER STRLOWER STRCONCAT STRCOMPARE STRCOPY STRINSERT
%token <qc> ASSIGN OP RELOP LOG
%token <qc> ID

%type <qc> prog decl-list var-decl func params
%type <qc> stmt-list comp-stmt stmt local-decl
%type <qc> expr simple-expr conditional-stmt iteration-stmt return-stmt
%type <qc> var op-expr op-log term call args arg-list

%%

prog: 
    decl-list {printf("prog\n");}
;

decl-list: 
    decl-list var-decl {printf("multiple-var\n");}
    | var-decl {printf("var\n");}
    | decl-list func {printf("multiple-func\n");}
    | func {printf("func\n");}
;

var-decl:
    TYPE ID ';' {printf("var-decl\n");}
;

func:
    TYPE ID '(' params ')' comp-stmt {printf("func-decl\n");}
;

params:
    params ',' TYPE ID {printf("%d", $1);}
    | TYPE ID
    | {}
;

comp-stmt:
    '{' local-decl stmt-list '}' {printf("%d %d", $2, $3);}
;

local-decl:
    local-decl TYPE ID ';' {printf("%d", $1);}
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
    | PRINT '(' STRING ')'
    | PRINT '(' ID ')'
    | SCAN '(' ID ')'
    | STRCONCAT '(' STRING ',' STRING ')'
    | STRCOMPARE '(' STRING ',' STRING ')'
    | STRCOPY '(' STRING ',' STRING ')'
    | STRINSERT '(' STRING ',' STRING ',' ID ')'
    | STRUPPER '(' STRING ')'
    | STRLOWER '(' STRING ')'
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
    IF '(' expr ')' comp-stmt {printf("%d %d", $3, $5);}
    | IF '(' expr ')' comp-stmt ELSE comp-stmt {printf("%d %d %d", $3, $5, $7);}
;

iteration-stmt:
    WHILE '(' expr ')' comp-stmt {printf("%d %d", $3, $5);}
;

return-stmt:
    RETURN expr ';' {printf("%d", $2);}
    | RETURN ';'
;

var:
    ID
;

op-expr:
    op-expr OP term {printf("%d %d", $1, $3);}
    | term {printf("%d", $1);}
;

op-log:
    op-log LOG term {printf("%d %d", $1, $3);}
    | BOOL
;

term:
    '(' simple-expr ')' {printf("%d", $2);}
    | var {printf("%d", $1);}
    | call {printf("%d", $1);}
    | STRING
    | INT
    | FLOAT
;

call:
    ID '(' args ')' {printf("%d", $3);}
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

int main(int argc, char **argv) {
    ++argv, --argc;
    if(argc > 0)
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    yyparse();
    yylex_destroy();
    return 0;
}