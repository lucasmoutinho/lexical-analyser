%error-verbose
%debug
%locations

%{
#include <stdlib.h>
#include <stdio.h>

int yylex();
extern int yylex_destroy(void);
extern int line;
void yyerror(const char* msg) {
    fprintf(stderr, "%s -- linha: %d\n", msg, line);
}
extern FILE *yyin;

typedef struct node {
    char node_class; // 'F' function, 'V' var, 'P' parameter, 'E' expression, 'A' abstract
    struct node* left;
    struct node* right;
    char* var_type; // Tipo da variável
    char* nome; // Nome

} node;

node* parser_tree = NULL; // Inicialização da árvore

node* insert_node(char node_class, node* left, node* right, char* var_type, char* nome){
    node* aux_node = (node*)calloc(1, sizeof(node));

    aux_node->node_class = node_class;
    aux_node->left = left;
    aux_node->right = right;
    aux_node->var_type = var_type;
    aux_node->nome = nome;

    return aux_node;
}

void print_tree(node * tree) {
    if (tree) {
        printf("class: %c\n", tree->node_class);
        if (tree->var_type != NULL){
            printf("var_type: %s\n", tree->var_type);
        }
        if (tree->nome != NULL){
            printf("nome: %s\n", tree->nome);
        }
        printf("\n");
        print_tree(tree->left);
        print_tree(tree->right);
    }
}

%}

%union {
    char* str;
    struct node* no;
}

%token <str> INT FLOAT BOOL STR
%token <str> TYPE
%token <str> ID
%token IF ELSE WHILE RETURN PRINT SCAN 
%token STRUPPER STRLOWER STRCONCAT STRCOMPARE STRCOPY STRINSERT
%token QUOTES

%right ASSIGN
%left OP RELOP LOG

%type <no> prog decl-list var-decl func params
%type <no> stmt-list comp-stmt stmt local-decl
%type <no> expr simple-expr conditional-stmt iteration-stmt return-stmt
%type <no> var op-expr op-log term call args arg-list string

%%

prog: 
    decl-list { parser_tree = $1; printf("prog\n"); }
;

decl-list: 
    decl-list var-decl { $$ = insert_node('A', $1, $2, NULL, NULL); printf("decl-list #1\n"); }
    | var-decl { $$ = $1; printf("decl-list #2\n"); }
    | decl-list func { $$ = insert_node('A', $1, $2, NULL, NULL); printf("decl-list #3\n"); }
    | func { $$ = $1; printf("decl-list #4\n"); }
;

var-decl:
    TYPE ID ';' { $$ = insert_node('V', NULL, NULL, $1, $2); printf("var-decl %s %s\n", $1, $2); }
;

func:
    TYPE ID '(' params ')' comp-stmt {}
;

params:
    params ',' TYPE ID {}
    | TYPE ID {}
    | {}
;

comp-stmt:
    '{' local-decl stmt-list '}' {}
;

local-decl:
    local-decl TYPE ID ';' {}
    | {}
;

stmt-list:
    stmt-list stmt {}
    | {}
;

// Arrumar na gramatica
stmt: 
    expr {}
    | conditional-stmt {}
    | iteration-stmt {}
    | return-stmt {}
    | PRINT '(' QUOTES string QUOTES ')' ';' {}
    | PRINT '(' ID ')' ';' {}
    | SCAN '(' ID ')' ';' {}
;

// Arrumar na gramatica
expr:
    var ASSIGN expr {}
    | simple-expr ';' {}
;

simple-expr:
    op-expr RELOP op-expr {}
    | op-expr {}
    | op-log {}
;

conditional-stmt:
    IF '(' simple-expr ')' comp-stmt {}
    | IF '(' simple-expr ')' comp-stmt ELSE comp-stmt {}
;

iteration-stmt:
    WHILE '(' expr ')' comp-stmt {}
;

return-stmt:
    RETURN expr ';' {}
    | RETURN ';' {}
;

var:
    ID {}
;

op-expr:
    op-expr OP term {}
    | term {}
;

op-log:
    op-log LOG term {}
    | BOOL {}
;

term:
    '(' simple-expr ')' {}
    | var {}
    | call {}
    | QUOTES string QUOTES {}
    | INT {}
    | FLOAT {}
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

int main(int argc, char **argv) {
    ++argv, --argc;
    if(argc > 0)
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    yyparse();
    printf("\n---------------\n");
    printf("Abstract Syntax Tree:\n\n");
    print_tree(parser_tree);
    yylex_destroy();
    return 0;
}