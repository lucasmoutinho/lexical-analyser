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
#define INT_TO_FLOAT 23
#define FLOAT_TO_INT 24

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
    char* type;         // Tipo da nó
    char* value;        // valor armazenado no nó
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
node* insert_node(int node_class, node* left, node* right, char* type, char* value);
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
void semantic_error_type_mismatch(char* type_left, char* type_right);
symbol_node* find_symbol(char* name);
void define_type(node* no);
void semantic_error_return_type(char* return_type, char* type);
void semantic_error_no_return(char* type);
void check_semantic_error_return_type(char* return_type);
void semantic_error_relop_type(char* value);
void check_semantic_error_relop_type(node* no);
void semantic_error_op_type(char* value);
void check_semantic_error_op_type(node* no);

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
%type <no> var op-expr term call args arg-list string

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
    '{' local-decl stmt-list return-stmt '}' { 
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
    | PRINT '(' QUOTES string QUOTES ')' ';' { 
        $$ = insert_node(PRINT_STATEMENT, $4, NULL, "void", $1);
        if (DEBUG_MODE) {printf("stmt #4 %s\n", $1);}
    }
    | PRINT '(' var ')' ';' { 
        $$ = insert_node(PRINT_STATEMENT, $3, NULL, "void", $1); 
        if (DEBUG_MODE) {printf("stmt #5 %s\n", $1);} 
    }
    | SCAN '(' var ')' ';' { 
        $$ = insert_node(SCAN_STATEMENT, $3, NULL, "void", $1); 
        if (DEBUG_MODE) {printf("stmt #6 %s\n", $1);}
    }
;

expr:
    var ASSIGN expr { 
        $$ = insert_node(ASSIGN_EXPRESSION, $1, $3, NULL, $2);
        define_type($$);
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
        define_type($$);
        check_semantic_error_relop_type($$);
        if (DEBUG_MODE) {printf("simple-expr #1 %s\n", $2);}
    }
    | op-expr { 
        $$ = $1; 
        if (DEBUG_MODE) {printf("simple-expr #2\n");}
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
        $$ = insert_node(RETURN_STATEMENT, $2, NULL, NULL, $1); 
        define_type($$);
        check_semantic_error_return_type($$->type);
        if (DEBUG_MODE) {printf("return-stmt #1 %s\n", $1);}
    }
    | RETURN ';' { 
        $$ = insert_node(RETURN_STATEMENT, NULL, NULL, "void", $1); 
        check_semantic_error_return_type($$->type);
        if (DEBUG_MODE) {printf("return-stmt #2 %s\n", $1);}
    }
    | {
        $$ = NULL;
        check_semantic_error_return_type(NULL);
        if (DEBUG_MODE) {printf("return-stmt #3\n");}
    }
;

var:
    ID { 
        symbol_node* s = find_symbol($1);
        char* type = NULL;
        if(s != NULL){
            type = s->type;
        }
        $$ = insert_node(VARIABLE, NULL, NULL, type, $1);
        if (DEBUG_MODE) {printf("var %s\n", $1);}
    }
;

// Arrumar na gramática
op-expr:
    op-expr OP term {
        $$ = insert_node(ARITHIMETIC_EXPRESSION, $1, $3, NULL, $2);
        define_type($$);
        check_semantic_error_op_type($$);
        if (DEBUG_MODE) {printf("op-expr #1 %s\n", $2);}
    }
    | op-expr LOG term { 
        $$ = insert_node(LOGICAL_EXPRESSION, $1, $3, NULL, $2); 
        define_type($$);
        if (DEBUG_MODE) {printf("op-expr #2 %s\n", $2);}
    }
    | term { 
        $$ = $1; 
        if (DEBUG_MODE) {printf("op-expr #3\n");}
    }
;

// Arrumar na gramática
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
        $$ = insert_node(INTEGER, NULL, NULL, "int", $1); 
        if (DEBUG_MODE) {printf("term #5 %s\n", $1);}
    }
    | FLOAT { 
        $$ = insert_node(FLOATNUMBER, NULL, NULL, "float", $1); 
        if (DEBUG_MODE) {printf("term #6 %s\n", $1);}
    }
    | BOOL { 
        $$ = insert_node(BOOLEAN, NULL, NULL, "bool", $1); 
        if (DEBUG_MODE) {printf("term #7 %s\n", $1);}
    }
;

call:
    ID '(' args ')' {
        symbol_node* s = find_symbol($1);
        char* type = NULL;
        if(s != NULL){
            type = s->type;
        }
        $$ = insert_node(FUNCTION_CALL, $3, NULL, type, $1);
        if (DEBUG_MODE) {printf("call #1 %s\n", $1);}
    }
    | STRCONCAT '(' args ')' { 
        $$ = insert_node(FUNCTION_CALL, $3, NULL, "string", $1); 
        if (DEBUG_MODE) {printf("call #2 %s\n", $1);}
    }
    | STRCOPY '(' args ')' { 
        $$ = insert_node(FUNCTION_CALL, $3, NULL, "string", $1);
        if (DEBUG_MODE) {printf("call #4 %s\n", $1);}
    }
    | STRINSERT '(' args ')' {  
        $$ = insert_node(FUNCTION_CALL, $3, NULL, "string", $1);
        if (DEBUG_MODE) {printf("call #5 %s\n", $1);}
    }
    | STRUPPER '(' args ')' {  
        $$ = insert_node(FUNCTION_CALL, $3, NULL, "string", $1);
        if (DEBUG_MODE) {printf("call #6 %s\n", $1);}
    }
    | STRLOWER '(' args ')' {  
        $$ = insert_node(FUNCTION_CALL, $3, NULL, "string", $1);
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
        $$ = insert_node(STRING, $1, NULL, "string", $2); 
        if (DEBUG_MODE) {printf("string #1 %s\n", $2);}
    }
    | { 
        $$ = NULL; 
        if (DEBUG_MODE) {printf("string #2\n");}
    }
%%

// Insere Nó
node* insert_node(int node_class, node* left, node* right, char* type, char* value){
    node* aux_node = (node*)calloc(1, sizeof(node));

    aux_node->node_class = node_class;
    aux_node->left = left;
    aux_node->right = right;
    aux_node->type = type;
    aux_node->value = value;

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
        case INT_TO_FLOAT:
            printf("INT_TO_FLOAT");
        break;
        case FLOAT_TO_INT:
            printf("FLOAT_TO_INT");
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
        if (tree->type != NULL){
            printf("type: %s | ", tree->type);
        }
        if (tree->value != NULL){
            printf("value: %s | ", tree->value);
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
void add_symbol(char* name, char* type, char symbol_type) {
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

// Procura símbolo na tabela de símbolos
symbol_node* find_symbol(char* name) {
    symbol_node *s;
    scope* scope = get_stack_head();
    char *key = concat(name, scope->scope_name);
    HASH_FIND_STR(symbol_table, key, s);
    if(s == NULL && scope->scope_name != "global"){
        scope = stack;
        key = concat(name, scope->scope_name);
        HASH_FIND_STR(symbol_table, key, s);
    }
    if(s == NULL){
        semantic_error_not_declared(name);
    }
    return s;
}

// Erro semantico de tipo incompatível
void semantic_error_type_mismatch(char* type_left, char* type_right){
    char *error = (char *)malloc(
        (strlen(type_left) + strlen(type_right) + 1 + 55) * sizeof(char)
    ); // +1 for the null-terminator and 55 for semantic error message
    sprintf(error, "semantic error, type mismatch between %s and %s", type_left, type_right);
    yyerror(error);
    free(error);
}

// Adiciona nó de conversão implícita na árvore.
// 
void add_implicit_conversion(node *no){
    node* conversion_node;
    node* aux;
    if(strcmp(no->left->type, "int") == 0 && strcmp(no->right->type, "float") == 0){
        if(no->node_class == ASSIGN_EXPRESSION){
            conversion_node = insert_node(FLOAT_TO_INT, no->right, NULL, "int", NULL); 
            no->right = conversion_node;
        }
        else{
            conversion_node = insert_node(INT_TO_FLOAT, no->left, NULL, "float", NULL);
            no->left = conversion_node;
        }
    }
    else{
        conversion_node = insert_node(INT_TO_FLOAT, no->right, NULL, "float", NULL);
        no->right = conversion_node;
    }
}

// Define tipo para nó da árvore (como para expressões), checando lado esquerdo e direito
void define_type(node* no){
    char* type_left = NULL;
    char* type_right = NULL;
    if(no->left != NULL){
        type_left = no->left->type;
    }
    if(no->right != NULL){
        type_right = no->right->type;
    }
    if(type_left != NULL && type_right != NULL && strcmp(type_left, type_right) != 0){ 
        if( // type mismatch -- implicit conversion
            (strcmp(type_left, "int") == 0 && strcmp(type_right, "float") == 0) || 
            (strcmp(type_left, "float") == 0 && strcmp(type_right, "int") == 0)
        ){
            add_implicit_conversion(no);
            type_left = no->left->type;
        }
        else{ // type mismatch -- no implicit conversion
            semantic_error_type_mismatch(type_left, type_right);
        }
    }
    if(no->node_class == RELATIONAL_EXPRESSION || no->node_class == LOGICAL_EXPRESSION){
        no->type = "bool";
    }
    else{
        no->type = type_left;
    }
}

// Erro semantico de tipo de retorno diferente de tipo da função
void semantic_error_return_type(char* return_type, char* type){
    char *error = (char *)malloc(
        (strlen(type) + strlen(return_type) + 1 + 51) * sizeof(char)
    ); // +1 for the null-terminator and 51 for semantic error message
    sprintf(error, "semantic error, return of type %s, expected type %s", return_type, type);
    yyerror(error);
    free(error);
}

// Erro semantico de retorno inexistente em função não void
void semantic_error_no_return(char* type){
    char *error = (char *)malloc(
        (strlen(type) + 1 + 59) * sizeof(char)
    ); // +1 for the null-terminator and 59 for semantic error message
    sprintf(error, "semantic error, no return found, expected return of type %s", type);
    yyerror(error);
    free(error);
}

// Erro semantico de retorno existente em função void
void semantic_error_return_in_void(char* type){
    char *error = (char *)malloc(
        (strlen(type) + 1 + 81) * sizeof(char)
    ); // +1 for the null-terminator and 81 for semantic error message
    sprintf(error, "semantic error, return of type %s in void function, expected no return or return;", type);
    yyerror(error);
    free(error);
}

void check_semantic_error_return_type(char* return_type){
    symbol_node *s;
    scope* scope = get_stack_head();
    char* function_name = scope->scope_name;
    char* key = concat(function_name, stack->scope_name);
    HASH_FIND_STR(symbol_table, key, s);
    if(s != NULL){
        if(return_type != NULL){
            if(strcmp(return_type, s->type) != 0){
                if(strcmp("void", s->type) == 0){
                    semantic_error_return_in_void(return_type);
                }
                else{
                    semantic_error_return_type(return_type, s->type);
                }
            }
        }
        else{
            if(strcmp("void", s->type) != 0){
                semantic_error_no_return(s->type);
            }
        }
    }
}

// Erro semantico de relop com booleans
void semantic_error_relop_type(char* value){
    char *error = (char *)malloc(
        (strlen(value) + 1 + 68) * sizeof(char)
    ); // +1 for the null-terminator and 68 for semantic error message
    sprintf(error, "semantic error, unexpected type boolean for relational operator (%s)", value);
    yyerror(error);
    free(error);
}

// Checa erro semantico de relop com booleans
void check_semantic_error_relop_type(node* no){
    char* type_left = NULL;
    char* type_right = NULL;
    if(no->left != NULL){
        type_left = no->left->type;
    }
    if(no->right != NULL){
        type_right = no->right->type;
    }
    if(// relop with booleans error
        (strcmp(no->value, "==") != 0) &&
        (strcmp(type_left, "bool") == 0 || strcmp(type_right, "bool") == 0)){
        semantic_error_relop_type(no->value);
    }
}

// Erro semantico de op com strings
void semantic_error_op_type(char* value){
    char *error = (char *)malloc(
        (strlen(value) + 1 + 56) * sizeof(char)
    ); // +1 for the null-terminator and 56 for semantic error message
    sprintf(error, "semantic error, unexpected type string for operator (%s)", value);
    yyerror(error);
    free(error);
}

// Checa erro semantico de op com strings
void check_semantic_error_op_type(node* no){
    char* type_left = NULL;
    char* type_right = NULL;
    if(no->left != NULL){
        type_left = no->left->type;
    }
    if(no->right != NULL){
        type_right = no->right->type;
    }
    if(// op with strings error
        (strcmp(no->value, "+") != 0) &&
        (strcmp(type_left, "string") == 0 || strcmp(type_right, "string") == 0)){
        semantic_error_op_type(no->value);
    }
}

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