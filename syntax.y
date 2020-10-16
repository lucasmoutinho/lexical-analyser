%error-verbose
%debug
%locations

%{
#include <stdlib.h>
#include <stdio.h>

#define DECLARATION 1
#define VARIABLE 2
#define VARIABLE_DECLARATION 3
#define FUNCTION 4
#define PARAMETER 5
#define COMPOUND_STATEMENT 6
#define STATEMENT_LIST 7
#define ASSIGN_EXPRESSION 8
#define ARITHIMETIC_EXPRESSION 9
#define RELATIONAL_EXPRESSION 10
#define LOGICAL_EXPRESSION 11
#define BOOLEAN 12
#define RETURN_STATEMENT 13
#define ITERATION_STATEMENT 14
#define CONDITIONAL_STATEMENT 15
#define INTEGER 16
#define FLOATNUMBER 17

int yylex();
extern int yylex_destroy(void);
extern int line;
void yyerror(const char* msg) {
    fprintf(stderr, "%s -- linha: %d\n", msg, line);
}
extern FILE *yyin;

typedef struct node {
    int node_class; // identificador da classe
    struct node* left;
    struct node* right;
    char* var_type; // Tipo da variável
    char* nome; // Nome da variável, do operador, do valor, etc

} node;

node* parser_tree = NULL; // Inicialização da árvore

// Declarações de funções
node* insert_node(int node_class, node* left, node* right, char* var_type, char* nome);
void print_class(int node_class);
void print_tree(node * tree, int depth);
void print_depth(int depth);

%}

%union {
    char* str;
    struct node* no;
}

%token <str> INT FLOAT BOOL STR
%token <str> TYPE
%token <str> ID
%token <str> IF ELSE WHILE RETURN PRINT SCAN 
%token <str> STRUPPER STRLOWER STRCONCAT STRCOMPARE STRCOPY STRINSERT
%token QUOTES

%right <str> ASSIGN
%left <str> OP RELOP LOG

%type <no> prog decl-list var-decl func params
%type <no> stmt-list comp-stmt stmt local-decl
%type <no> expr simple-expr conditional-stmt iteration-stmt return-stmt
%type <no> var op-expr op-log term call args arg-list string

%%

prog: 
    decl-list { parser_tree = $1; printf("prog\n"); }
;

decl-list: 
    decl-list var-decl { $$ = insert_node(DECLARATION, $1, $2, NULL, NULL); printf("decl-list #1\n"); }
    | var-decl { $$ = $1; printf("decl-list #2\n"); }
    | decl-list func { $$ = insert_node(DECLARATION, $1, $2, NULL, NULL); printf("decl-list #3\n"); }
    | func { $$ = $1; printf("decl-list #4\n"); }
;

var-decl:
    TYPE ID ';' { $$ = insert_node(VARIABLE_DECLARATION, NULL, NULL, $1, $2); printf("var-decl %s %s\n", $1, $2); }
;

func:
    TYPE ID '(' params ')' comp-stmt { $$ = insert_node(FUNCTION, $4, $6, $1, $2); printf("func %s %s\n", $1, $2); }
;

params:
    params ',' TYPE ID { $$ = insert_node(PARAMETER, $1, NULL, $3, $4); printf("params #1 %s %s\n", $3, $4); }
    | TYPE ID { $$ = insert_node(PARAMETER, NULL, NULL, $1, $2); printf("params #2 %s %s\n", $1, $2); }
    | { $$ = NULL; printf("params #3\n"); }
;

comp-stmt:
    '{' local-decl stmt-list '}' { $$ = insert_node(COMPOUND_STATEMENT, $2, $3, NULL, NULL); printf("comp-stmt\n"); }
;

local-decl:
    local-decl TYPE ID ';' { $$ = insert_node(VARIABLE_DECLARATION, $1, NULL, $2, $3); printf("local-decl #1 %s %s\n", $2, $3); }
    | { $$ = NULL; printf("local-decl #2\n"); }
;

stmt-list:
    stmt-list stmt { $$ = insert_node(STATEMENT_LIST, $1, $2, NULL, NULL); printf("stmt-list #1\n"); }
    | { $$ = NULL; printf("stmt-list #2\n"); }
;

// Arrumar na gramatica
stmt: 
    expr { $$ = $1; printf("stmt #1\n"); }
    | conditional-stmt { $$ = $1; printf("stmt #2\n"); }
    | iteration-stmt { $$ = $1; printf("stmt #3\n"); }
    | return-stmt { $$ = $1; printf("stmt #4\n"); }
    | PRINT '(' QUOTES string QUOTES ')' ';' {}
    | PRINT '(' ID ')' ';' {}
    | SCAN '(' ID ')' ';' {}
;

// Arrumar na gramatica
expr:
    var ASSIGN expr { $$ = insert_node(ASSIGN_EXPRESSION, $1, $3, NULL, $2); printf("expr #1 %s\n", $2);  }
    | simple-expr ';' { $$ = $1; printf("expr #2\n"); }
;

simple-expr:
    op-expr RELOP op-expr { $$ = insert_node(RELATIONAL_EXPRESSION, $1, $3, NULL, $2); printf("simple-expr #1 %s\n", $2); }
    | op-expr { $$ = $1; printf("simple-expr #2\n"); }
    | op-log { $$ = $1; printf("simple-expr #3\n"); }
;

conditional-stmt:
    IF '(' simple-expr ')' comp-stmt { $$ = insert_node(CONDITIONAL_STATEMENT, $3, $5, NULL, $1); printf("conditional-stmt #1 %s\n", $1);}
    | IF '(' simple-expr ')' comp-stmt ELSE comp-stmt {
        node* aux_node = insert_node(CONDITIONAL_STATEMENT, $5, $7, NULL, $6);
        $$ = insert_node(CONDITIONAL_STATEMENT, $3, aux_node, NULL, $1);
        printf("conditional-stmt #2 %s\n", $1);
    }
;

iteration-stmt:
    WHILE '(' simple-expr ')' comp-stmt { $$ = insert_node(ITERATION_STATEMENT, $3, $5, NULL, $1); printf("iteration-stmt %s\n", $1); }
;

return-stmt:
    RETURN simple-expr ';' { $$ = insert_node(RETURN_STATEMENT, NULL, $2, NULL, $1); printf("return-stmt #1 %s\n", $1); }
    | RETURN ';' { $$ = insert_node(RETURN_STATEMENT, NULL, NULL, NULL, $1); printf("return-stmt #2 %s\n", $1); }
;

var:
    ID { $$ = insert_node(VARIABLE, NULL, NULL, NULL, $1); printf("var %s\n", $1); }
;

op-expr:
    op-expr OP term { $$ = insert_node(ARITHIMETIC_EXPRESSION, $1, $3, NULL, $2); printf("op-expr #1 %s\n", $2); }
    | term { $$ = $1; printf("op-expr #2\n"); }
;

op-log:
    op-log LOG term { $$ = insert_node(LOGICAL_EXPRESSION, $1, $3, NULL, $2); printf("op-log #1 %s\n", $2); }
    | BOOL { $$ = insert_node(BOOLEAN, NULL, NULL, NULL, $1); printf("op-log #2 %s\n", $1); }
;

term:
    '(' simple-expr ')' { $$ = $2; printf("term #1\n"); }
    | var { $$ = $1; printf("term #2\n"); }
    | call { $$ = $1; printf("term #3\n"); }
    | QUOTES string QUOTES {}
    | INT { $$ = insert_node(INTEGER, NULL, NULL, NULL, $1); printf("term #5 %s\n", $1); }
    | FLOAT { $$ = insert_node(FLOATNUMBER, NULL, NULL, NULL, $1); printf("term #6 %s\n", $1); }
;

// Arrumar na gramatica
call:
    ID '(' args ')' {}
    | STRCONCAT '(' QUOTES string QUOTES ',' QUOTES string QUOTES ')' {}
    | STRCOMPARE '(' QUOTES string QUOTES ',' QUOTES string QUOTES ')' {}
    | STRCOPY '(' QUOTES string QUOTES ',' QUOTES string QUOTES ')' {}
    | STRINSERT '(' QUOTES string QUOTES ',' QUOTES string QUOTES ',' ID ')' {}
    | STRUPPER '(' QUOTES string QUOTES ')' {}
    | STRUPPER '(' ID ')' {}
    | STRLOWER '(' QUOTES string QUOTES ')' {}
    | STRLOWER '(' ID ')' {}
;

args:
    arg-list {}
    | {}
;

arg-list:
    arg-list ',' simple-expr {}
    | simple-expr {}
;

string: 
    string STR {}
    | {}
%%

node* insert_node(int node_class, node* left, node* right, char* var_type, char* nome){
    node* aux_node = (node*)calloc(1, sizeof(node));

    aux_node->node_class = node_class;
    aux_node->left = left;
    aux_node->right = right;
    aux_node->var_type = var_type;
    aux_node->nome = nome;

    return aux_node;
}

void print_class(int node_class){
    switch(node_class){
        case DECLARATION:
            printf("DECLARATION");
        break;
        case VARIABLE:
            printf("VARIABLE");
        break;
        case VARIABLE_DECLARATION:
            printf("VARIABLE_DECLARATION");
        break;
        case FUNCTION:
            printf("FUNCTION");
        break;
        case PARAMETER:
            printf("PARAMETER");
        break;
        case COMPOUND_STATEMENT:
            printf("COMPOUND_STATEMENT");
        break;
        case STATEMENT_LIST:
            printf("STATEMENT_LIST");
        break;
        case ASSIGN_EXPRESSION:
            printf("ASSIGN");
        break;
        case ARITHIMETIC_EXPRESSION:
            printf("ARITHIMETIC_EXPRESSION");
        break;
        case RELATIONAL_EXPRESSION:
            printf("RELATIONAL_EXPRESSION");
        break;
        case LOGICAL_EXPRESSION:
            printf("LOGICAL_EXPRESSION");
        break;
        case BOOLEAN:
            printf("BOOL");
        break;
        case RETURN_STATEMENT:
            printf("RETURN");
        break;
        case ITERATION_STATEMENT:
            printf("ITERATION");
        break;
        case CONDITIONAL_STATEMENT:
            printf("CONDITIONAL");
        break;
        case INTEGER:
            printf("INT");
        break;
        case FLOATNUMBER:
            printf("FLOAT");
        break;
    }
    printf(" | ");
}

void print_depth(int depth) {
    int i = depth;
    while(i != 0){
        printf("-");
        i--;
    }
}

void print_tree(node * tree, int depth) {
    if (tree) {
        print_depth(depth);
        print_class(tree->node_class);
        if (tree->var_type != NULL){
            printf("var_type: %s | ", tree->var_type);
        }
        if (tree->nome != NULL){
            printf("%s | ", tree->nome);
        }
        printf("\n");
        print_tree(tree->left, depth + 1);
        print_tree(tree->right, depth + 1);
    }
}

int main(int argc, char **argv) {
    ++argv, --argc;
    if(argc > 0)
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    yyparse();
    printf("\n---------------\n");
    printf("Abstract Syntax Tree:\n\n");
    print_tree(parser_tree, 0);
    yylex_destroy();
    return 0;
}