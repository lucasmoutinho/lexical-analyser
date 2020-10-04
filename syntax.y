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
  char *qc;
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


%start prog
%%

prog: 
    decl-list {printf("%s", $1);}
;

decl-list: 
    decl-list var-decl {printf("%s %s", $1, $2);}
    | var-decl {printf("%s", $1);}
    | decl-list func {printf("%s %s", $1, $2);}
    | func {printf("%s", $1);}
;

var-decl:
    TYPE ID ';'
;

func:
    TYPE ID '(' params ')' comp-stmt {printf("%s %s", $4, $6);}
;

params:
    params ',' TYPE ID {printf("%s", $1);}
    | TYPE ID
    | {}
;

comp-stmt:
    '{' local-decl stmt-list '}' {printf("%s %s", $2, $3);}
;

local-decl:
    local-decl TYPE ID ';' {printf("%s", $1);}
    | {}
;

stmt-list:
    stmt-list stmt {printf("%s %s", $1, $2);}
    | {}
;

stmt: 
    expr {printf("%s", $1);}
    | conditional-stmt {printf("%s", $1);}
    | iteration-stmt {printf("%s", $1);}
    | return-stmt {printf("%s", $1);}
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
    var ASSIGN expr {printf("%s %s", $1, $3);}
    | simple-expr {printf("%s", $1);}
;

simple-expr:
    op-expr RELOP op-expr {printf("%s %s", $1, $3);}
    | op-expr {printf("%s", $1);}
    | op-log {printf("%s", $1);}
;

conditional-stmt:
    IF '(' expr ')' comp-stmt {printf("%s %s", $3, $5);}
    | IF '(' expr ')' comp-stmt ELSE comp-stmt {printf("%s %s %s", $3, $5, $7);}
;

iteration-stmt:
    WHILE '(' expr ')' comp-stmt {printf("%s %s", $3, $5);}
;

return-stmt:
    RETURN expr ';' {printf("%s", $2);}
    | RETURN ';'
;

var:
    ID
;

op-expr:
    op-expr OP term {printf("%s %s", $1, $3);}
    | term {printf("%s", $1);}
;

op-log:
    op-log LOG term {printf("%s %s", $1, $3);}
    | BOOL
;

term:
    '(' simple-expr ')' {printf("%s", $2);}
    | var {printf("%s", $1);}
    | call {printf("%s", $1);}
    | STRING
    | INT
    | FLOAT
;

call:
    ID '(' args ')' {printf("%s", $3);}
;

args:
    arg-list {printf("%s", $1);}
    | {}
;

arg-list:
    arg-list ',' simple-expr {printf("%s %s", $1, $3);}
    | simple-expr {printf("%s", $1);}
;

%%

int main(int argc, char **argv) {
    ++argv, --argc;
    if(argc > 0)
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    yylex();
    yyparse();
    yylex_destroy();
    return 0;
}