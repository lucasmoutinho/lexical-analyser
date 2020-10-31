%define parse.error verbose
%debug
%locations

%{
#include <stdlib.h>
#include <stdio.h>
#include "uthash.h"
#include "utlist.h"
#include "utstring.h"
#include "utstack.h"

// Defines
#define DEBUG_MODE 0 // 0 to hide parser prints, 1 to display
#define DECLARATION_LIST 1
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
#define PRINT_STATEMENT 18
#define SCAN_STATEMENT 19
#define STRING 20
#define FUNCTION_CALL 21
#define ARGS_LIST 22

// Extern variables
int yylex();
extern int yylex_destroy(void);
extern int total_errors;
extern int line;
extern int lex_error;
extern void yyerror(const char* msg);
extern FILE *yyin;

// Structs
typedef struct node {
    int node_class;     // identificador da classe
    struct node* left;  // Ponteiro pra esquerda 
    struct node* right; // Ponteiro pra direita
    char* var_type;     // Tipo da variável
    char* nome;         // Nome da variável, do operador, do valor, etc
} node;

node* parser_tree = NULL; // Inicialização da árvore

typedef struct scope {
    char* scope_name;    // Nome do escopo
    char* type;          // Tipo da variável
    struct scope *next;
} scope;

scope* stack = NULL; // Inicialização da pilha de escopo

typedef struct symbol_node {
    char* key;                      // key field
    char* name;                     // symbol name
    char* type;                     // int | float | bool | void | string 
    char symbol_type;               // 'V' (variable) | 'F' (function) | 'P' (parameter)
    char* scope_name;                // Nome do escopo
    UT_hash_handle hh;              // makes this structure hashable
} symbol_node;

symbol_node *symbol_table = NULL;    // Inicialização da tabela de símbolos

// Declarações de funções
node* insert_node(int node_class, node* left, node* right, char* var_type, char* nome);
void print_class(int node_class);
void print_tree(node * tree, int depth);
void print_depth(int depth);
void free_tree(struct node* no);
symbol_node* create_symbol(char* key, char *name, char* type, char symbol_type, char* scope_name);
void add_symbol(char *name, char* type, char symbol_type);
void print_symbol_table();
void free_symbol_table();
scope* get_stack_head();
void push_stack(char* scope_name, char* type);
void pop_stack();
void initialize_global_scope();
void semantic_error_redeclaration(char* name, char* scope);
void semantic_error_not_declared(char* name);
void check_semantic_error_not_declared(char* name);

%}

%union {
    char* str;
    struct node* no;
}

%token <str> INT FLOAT BOOL STR
%token <str> TYPE
%token <str> ID
%token <str> IF ELSE WHILE RETURN PRINT SCAN 
%token <str> STRUPPER STRLOWER STRCONCAT STRCOPY STRINSERT
%token QUOTES

%right <str> ASSIGN
%left <str> OP RELOP LOG

%type <no> prog decl-list var-decl func params
%type <no> stmt-list comp-stmt stmt local-decl
%type <no> expr simple-expr conditional-stmt iteration-stmt return-stmt
%type <no> var op-expr op-log term call args arg-list string

%%

prog: 
    decl-list { 
        parser_tree = $1;
        if (DEBUG_MODE) {printf("prog\n");}
    }
;
decl-list: 
    decl-list var-decl { 
        $$ = insert_node(DECLARATION_LIST, $1, $2, NULL, NULL);
        if (DEBUG_MODE) {printf("decl-list #1\n");} 
    }
    | var-decl { 
        $$ = $1;
        if (DEBUG_MODE) {printf("decl-list #2\n");}
    }
    | decl-list func { 
        $$ = insert_node(DECLARATION_LIST, $1, $2, NULL, NULL);
        if (DEBUG_MODE) {printf("decl-list #3\n");} 
    }
    | func { 
        $$ = $1;
        if (DEBUG_MODE) {printf("decl-list #4\n");}
    }
;

var-decl:
    TYPE ID ';' { 
        $$ = insert_node(VARIABLE_DECLARATION, NULL, NULL, $1, $2);
        add_symbol($2, $1, 'V');
        if (DEBUG_MODE) {printf("var-decl %s %s\n", $1, $2);}
    }
;

func:
    TYPE ID { 
        add_symbol($2, $1, 'F');
        push_stack($2, $1);
    }
    '(' params ')' comp-stmt { 
        $$ = insert_node(FUNCTION, $5, $7, $1, $2);
        pop_stack();
        if (DEBUG_MODE) {printf("func %s %s\n", $1, $2);}
    }
;

params:
    params ',' TYPE ID { 
        $$ = insert_node(PARAMETER, $1, NULL, $3, $4);
        add_symbol($4, $3, 'P');
        if (DEBUG_MODE) {printf("params #1 %s %s\n", $3, $4);}
    }
    | TYPE ID { 
        $$ = insert_node(PARAMETER, NULL, NULL, $1, $2);
        add_symbol($2, $1, 'P');
        if (DEBUG_MODE) {printf("params #2 %s %s\n", $1, $2);}
    }
    | { 
        $$ = NULL;
        if (DEBUG_MODE) {printf("params #3\n");}
    }
;

comp-stmt:
    '{' local-decl stmt-list '}' { 
        $$ = insert_node(COMPOUND_STATEMENT, $2, $3, NULL, NULL);
        if (DEBUG_MODE) {printf("comp-stmt\n");}
    }
;

local-decl:
    local-decl TYPE ID ';' { 
        $$ = insert_node(VARIABLE_DECLARATION, $1, NULL, $2, $3);
        add_symbol($3, $2, 'V');
        if (DEBUG_MODE) {printf("local-decl #1 %s %s\n", $2, $3);}
    }
    | { 
        $$ = NULL; 
        if (DEBUG_MODE) {printf("local-decl #2\n");}
    }
;

stmt-list:
    stmt-list stmt { 
        $$ = insert_node(STATEMENT_LIST, $1, $2, NULL, NULL);
        if (DEBUG_MODE) {printf("stmt-list #1\n");}
    }
    | { 
        $$ = NULL; 
        if (DEBUG_MODE) {printf("stmt-list #2\n");} 
    }
;

stmt: 
    expr { 
        $$ = $1; 
        if (DEBUG_MODE) {printf("stmt #1\n");} 
    }
    | conditional-stmt { 
        $$ = $1; 
        if (DEBUG_MODE) {printf("stmt #2\n");} 
    }
    | iteration-stmt { 
        $$ = $1; 
        if (DEBUG_MODE) {printf("stmt #3\n");}
    }
    | return-stmt { 
        $$ = $1; 
        if (DEBUG_MODE) {printf("stmt #4\n");}
    }
    | PRINT '(' QUOTES string QUOTES ')' ';' { 
        $$ = insert_node(PRINT_STATEMENT, $4, NULL, NULL, $1);
        if (DEBUG_MODE) {printf("stmt #4 %s\n", $1);}
    }
    | PRINT '(' var ')' ';' { 
        $$ = insert_node(PRINT_STATEMENT, $3, NULL, NULL, $1); 
        if (DEBUG_MODE) {printf("stmt #5 %s\n", $1);} 
    }
    | SCAN '(' var ')' ';' { 
        $$ = insert_node(SCAN_STATEMENT, $3, NULL, NULL, $1); 
        if (DEBUG_MODE) {printf("stmt #6 %s\n", $1);}
    }
;

expr:
    var ASSIGN expr { 
        $$ = insert_node(ASSIGN_EXPRESSION, $1, $3, NULL, $2); 
        if (DEBUG_MODE) {printf("expr #1 %s\n", $2);} 
    }
    | simple-expr ';' { 
        $$ = $1; 
        if (DEBUG_MODE) {printf("expr #2\n");}
    }
;

simple-expr:
    op-expr RELOP op-expr { 
        $$ = insert_node(RELATIONAL_EXPRESSION, $1, $3, NULL, $2); 
        if (DEBUG_MODE) {printf("simple-expr #1 %s\n", $2);}
    }
    | op-expr { 
        $$ = $1; 
        if (DEBUG_MODE) {printf("simple-expr #2\n");}
    }
    | op-log { 
        $$ = $1; 
        if (DEBUG_MODE) {printf("simple-expr #3\n");}
    }
;

conditional-stmt:
    IF '(' simple-expr ')' comp-stmt { 
        $$ = insert_node(CONDITIONAL_STATEMENT, $3, $5, NULL, $1);
        if (DEBUG_MODE) {printf("conditional-stmt #1 %s\n", $1);}
    }
    | IF '(' simple-expr ')' comp-stmt ELSE comp-stmt {
        node* aux_node = insert_node(CONDITIONAL_STATEMENT, $5, $7, NULL, $6);
        $$ = insert_node(CONDITIONAL_STATEMENT, $3, aux_node, NULL, $1);
        if (DEBUG_MODE) {printf("conditional-stmt #2 %s\n", $1);}
    }
;

iteration-stmt:
    WHILE '(' simple-expr ')' comp-stmt { 
        $$ = insert_node(ITERATION_STATEMENT, $3, $5, NULL, $1);
        if (DEBUG_MODE) {printf("iteration-stmt %s\n", $1);}
    }
;

return-stmt:
    RETURN simple-expr ';' { 
        $$ = insert_node(RETURN_STATEMENT, NULL, $2, NULL, $1); 
        if (DEBUG_MODE) {printf("return-stmt #1 %s\n", $1);}
    }
    | RETURN ';' { 
        $$ = insert_node(RETURN_STATEMENT, NULL, NULL, NULL, $1); 
        if (DEBUG_MODE) {printf("return-stmt #2 %s\n", $1);}
    }
;

var:
    ID { 
        $$ = insert_node(VARIABLE, NULL, NULL, NULL, $1);
        check_semantic_error_not_declared($1);
        if (DEBUG_MODE) {printf("var %s\n", $1);}
    }
;

op-expr:
    op-expr OP term { 
        $$ = insert_node(ARITHIMETIC_EXPRESSION, $1, $3, NULL, $2); 
        if (DEBUG_MODE) {printf("op-expr #1 %s\n", $2);}
    }
    | term { 
        $$ = $1; 
        if (DEBUG_MODE) {printf("op-expr #2\n");}
    }
;

op-log:
    op-log LOG term { 
        $$ = insert_node(LOGICAL_EXPRESSION, $1, $3, NULL, $2); 
        if (DEBUG_MODE) {printf("op-log #1 %s\n", $2);}
    }
    | BOOL { 
        $$ = insert_node(BOOLEAN, NULL, NULL, NULL, $1); 
        if (DEBUG_MODE) {printf("op-log #2 %s\n", $1);}
    }
;

term:
    '(' simple-expr ')' { 
        $$ = $2; 
        if (DEBUG_MODE) {printf("term #1\n");}
    }
    | var { 
        $$ = $1; 
        if (DEBUG_MODE) {printf("term #2\n");}
    }
    | call { 
        $$ = $1; 
        if (DEBUG_MODE) {printf("term #3\n");}
    }
    | QUOTES string QUOTES { 
        $$ = $2; 
        if (DEBUG_MODE) {printf("term #4\n");}
    }
    | INT { 
        $$ = insert_node(INTEGER, NULL, NULL, NULL, $1); 
        if (DEBUG_MODE) {printf("term #5 %s\n", $1);}
    }
    | FLOAT { 
        $$ = insert_node(FLOATNUMBER, NULL, NULL, NULL, $1); 
        if (DEBUG_MODE) {printf("term #6 %s\n", $1);}
    }
;

call:
    ID '(' args ')' {
        $$ = insert_node(FUNCTION_CALL, $3, NULL, NULL, $1);
        check_semantic_error_not_declared($1);
        if (DEBUG_MODE) {printf("call #1 %s\n", $1);}
    }
    | STRCONCAT '(' args ')' { 
        $$ = insert_node(FUNCTION_CALL, $3, NULL, NULL, $1); 
        if (DEBUG_MODE) {printf("call #2 %s\n", $1);}
    }
    | STRCOPY '(' args ')' { 
        $$ = insert_node(FUNCTION_CALL, $3, NULL, NULL, $1);
        if (DEBUG_MODE) {printf("call #4 %s\n", $1);}
    }
    | STRINSERT '(' args ')' {  
        $$ = insert_node(FUNCTION_CALL, $3, NULL, NULL, $1);
        if (DEBUG_MODE) {printf("call #5 %s\n", $1);}
    }
    | STRUPPER '(' args ')' {  
        $$ = insert_node(FUNCTION_CALL, $3, NULL, NULL, $1);
        if (DEBUG_MODE) {printf("call #6 %s\n", $1);}
    }
    | STRLOWER '(' args ')' {  
        $$ = insert_node(FUNCTION_CALL, $3, NULL, NULL, $1);
        if (DEBUG_MODE) {printf("call #7 %s\n", $1);}
    }
;

args:
    arg-list { 
        $$ = $1;
        if (DEBUG_MODE) {printf("args #1\n");}
    }
    | { 
        $$ = NULL;
        if (DEBUG_MODE) {printf("args #2\n");}
    }
;

arg-list:
    arg-list ',' simple-expr { 
        $$ = insert_node(ARGS_LIST, $1, $3, NULL, NULL); 
        if (DEBUG_MODE) {printf("args-list #1\n");}
    }
    | simple-expr { 
        $$ = $1; 
        if (DEBUG_MODE) {printf("args-list #2\n");}
    }
;

string: 
    string STR { 
        $$ = insert_node(STRING, $1, NULL, NULL, $2); 
        if (DEBUG_MODE) {printf("string #1 %s\n", $2);}
    }
    | { 
        $$ = NULL; 
        if (DEBUG_MODE) {printf("string #2\n");}
    }
%%

// Insere Nó
node* insert_node(int node_class, node* left, node* right, char* var_type, char* nome){
    node* aux_node = (node*)calloc(1, sizeof(node));

    aux_node->node_class = node_class;
    aux_node->left = left;
    aux_node->right = right;
    aux_node->var_type = var_type;
    aux_node->nome = nome;

    return aux_node;
}

// Printa informação da classe do Nó
void print_class(int node_class){
    switch(node_class){
        case DECLARATION_LIST:
            printf("DECLARATION_LIST");
        break;
        case VARIABLE:
            printf("VARIABLE");
        break;
        case VARIABLE_DECLARATION:
            printf("VARIABLE_DECLARATION");
        break;
        case FUNCTION:
            printf("FUNCTION_DECLARATION");
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
        case PRINT_STATEMENT:
            printf("PRINT");
        break;
        case SCAN_STATEMENT:
            printf("PRINT");
        break;
        case STRING:
            printf("STRING");
        break;
        case FUNCTION_CALL:
            printf("FUNCTION_CALL");
        break;
        case ARGS_LIST:
            printf("ARGS_LIST");
        break;
    }
    printf(" | ");
}

// Printa identação
void print_depth(int depth) {
    int i = depth;
    while(i != 0){
        printf("-");
        i--;
    }
}

// Printa árvore
void print_tree(node * tree, int depth) {
    if (tree) {
        print_depth(depth);
        print_class(tree->node_class);
        if (tree->var_type != NULL){
            printf("type: %s | ", tree->var_type);
        }
        if (tree->nome != NULL){
            printf("%s | ", tree->nome);
        }
        printf("\n");
        print_tree(tree->left, depth + 1);
        print_tree(tree->right, depth + 1);
    }
}

// Apaga a árvore
void free_tree(struct node* no){
    if(no == NULL) return;
    if(no->left) free_tree(no->left);
    if(no->right) free_tree(no->right);
    free(no);
}

// Create symbol node
symbol_node* create_symbol(char* key, char *name, char* type, char symbol_type, char* scope_name){
    symbol_node *s = (symbol_node *)malloc(sizeof *s);
    s->key = key;
    s->name = name;
    s->type = type;
    s->symbol_type = symbol_type;
    s->scope_name = scope_name;
    return s;
}

// Concatena strings do stackoverflow
char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, "::");
    strcat(result, s2);
    return result;
}

// Retorna o stack head
scope* get_stack_head() {
    scope* s = stack;
    while(s->next != NULL) {
        s = s->next;
    }
    return s;
}

// Push do scope stack
void push_stack(char* scope_name, char* type){
    scope* s = (scope *)malloc(sizeof *s);
    scope* stack_head;

    s->type = type;
    s->scope_name = scope_name;

    stack_head = get_stack_head();
    stack_head->next = s;
}

// Pop do scope stack
void pop_stack(){
    scope* s = stack;
    if(s->scope_name == "global" && s->next == NULL) {
        return;
    }
    while(s->next->next != NULL){
        s = s->next;
    }
    free(s->next);
    s->next = NULL;
}

// Adiciona simbolo na hash table
void add_symbol(char *name, char* type, char symbol_type) {
    symbol_node *s;
    scope* scope = get_stack_head();
    char *key = concat(name, scope->scope_name);
    HASH_FIND_STR(symbol_table, key, s);
    if(s == NULL){ // not declared -> add to symbol table
        s = create_symbol(key, name, type, symbol_type, scope->scope_name);
        HASH_ADD_STR(symbol_table, key, s);
    }
    else{ // redeclaration error
        semantic_error_redeclaration(name, scope->scope_name);
    }
}

// Printa tabela de símbolos
void print_symbol_table() {
    symbol_node *s;
    printf("\n\n----------  TABELA DE SÍMBOLOS ----------\n\n");
    for(s=symbol_table; s != NULL; s=s->hh.next) {
        printf("key: %30s | name: %20s | type: %10s | symbol_type: %c | scope: %10s\n", s->key, s->name, s->type, s->symbol_type, s->scope_name);
    }
}

// Inicializa o escopo como global
void initialize_global_scope(){
    scope* s = (scope *)malloc(sizeof *s);
    s->scope_name = "global";
    stack = s;
}

// Libera toda a memória da tabela de símbolos
void free_symbol_table(){
    symbol_node *s, *tmp;
    HASH_ITER(hh, symbol_table, s, tmp) {
        HASH_DEL(symbol_table, s);
        free(s);
    }
}

// Erro semantico redeclaração
void semantic_error_redeclaration(char* name, char* scope){
    char *error = (char *)malloc((strlen(name) + strlen(scope) + 1 + 45) * sizeof(char)); // +1 for the null-terminator and 45 for semantic error message
    sprintf(error, "semantic error, %s was already declared in %s", name, scope);
    yyerror(error);
    free(error);
}

// Erro semantico não declarado
void semantic_error_not_declared(char* name){
    char *error = (char *)malloc((strlen(name) + 1 + 35) * sizeof(char)); // +1 for the null-terminator and 35 for semantic error message
    sprintf(error, "semantic error, %s was not declared", name);
    yyerror(error);
    free(error);
}

// symbol_node* find_symbol_node(char* name){
//     symbol_node *s;
//     scope* scope = stack;

// }

// Checa se ocorreu erro semantico de não declaração
void check_semantic_error_not_declared(char* name){
    int found_symbol = 0;
    symbol_node *s;
    scope* scope = stack;
    char *key;
    while(scope != NULL){
        // Procura no escopo global e nos escopos empilhados
        key = concat(name, scope->scope_name);
        HASH_FIND_STR(symbol_table, key, s);
        if(s != NULL){
            found_symbol = 1;
            break;
        }
        scope = scope->next;
    }
    if(!found_symbol){ // Error not declared
        semantic_error_not_declared(name);
    }
}

// // Erro semantico de tipo incompatível
// void semantic_error_type_mismatch(char* type_left, char* name_left, char* type_right, char* name_right){
//     char *error = (char *)malloc(
//         (strlen(name_left) + strlen(type_left) + strlen(name_right) + strlen(type_right) + 1 + 55) * sizeof(char)
//     ); // +1 for the null-terminator and 55 for semantic error message
//     sprintf(error, "semantic error, type mismatch between %s(%s) and %s(%s)", type_left, name_left, type_right, name_right);
//     yyerror(error);
//     free(error);
// }

// // Checa se ocorreu erro semantico de tipos incompatíveis
// void check_semantic_error_type_mismatch(char* name_left, char* name_right){

// }

int main(int argc, char **argv) {
    ++argv, --argc;
    if(argc > 0)
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    initialize_global_scope();
    yyparse();
    yylex_destroy();
    if(total_errors == 0){
        printf("\n\n----------  ABSTRACT SYNTAX TREE ----------\n\n");
        print_tree(parser_tree, 0);
        print_symbol_table();
    }
    free_tree(parser_tree);
    free_symbol_table();
    return 0;
}