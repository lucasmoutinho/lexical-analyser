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
#define STRCONCAT_STATEMENT 25
#define STRCOPY_STATEMENT 26
#define STRINSERT_STATEMENT 27
#define STRUPPER_STATEMENT 28
#define STRLOWER_STATEMENT 29
#define LOCAL_DECLARATION_LIST 30

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
} node; // Nó da árvore

node* parser_tree = NULL; // Inicialização da árvore

typedef struct scope {
    char* scope_name;    // Nome do escopo
    char* type;          // Tipo da variável
    struct scope *next;
} scope; // Escopo

scope* stack = NULL; // Inicialização da pilha de escopo

typedef struct args_node {
    char* name; // Nome do argumento
    char* type; // tipo do argumento
    struct args_node *next;    // Próximo parametro
} args_node; // Estrutura para criação de lista de argumentos

typedef struct param_node {
    char* key;                  // Chave pra tabela de símbolos
    struct param_node *next;    // Próximo parametro
} param_node; // Estrutura para armazenar uma lista de chaves da tabela de símbolos de parâmetros

typedef struct symbol_node {
    char* key;                      // key field
    char* name;                     // symbol name
    char* type;                     // int | float | bool | void | string 
    char symbol_type;               // 'V' (variable) | 'F' (function) | 'P' (parameter)
    param_node* param_list;
    char* scope_name;               // Nome do escopo
    UT_hash_handle hh;              // makes this structure hashable
} symbol_node; // Nó da tabela de símbolos

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
void add_implicit_conversion(node *no, char* func_type);
void define_type(node* no);
void semantic_error_return_type(char* return_type, char* type);
void check_semantic_error_return_type(char* return_type, node* no);
void semantic_error_relop_type(char* value);
void check_semantic_error_relop_type(node* no);
void semantic_error_op_type(char* value);
void check_semantic_error_op_type(node* no);
void semantic_error_wrong_number_arguments(char* value, int number_args, int number_param);
void semantic_error_type_mismatch_args(char* function_name, char* arg_name, char* type_arg, char* param_name, char* type_param);
args_node* create_args_list(node* no);
void free_args_list(args_node* args_list);
void check_semantic_error_type_mismatch_args(node* no, char* function_name);
args_node* create_param_list_native_function(char* function_name);
void check_semantic_error_type_mismatch_args_native_function(node* no, char* function_name);
void semantic_error_no_main();
void check_semantic_error_no_main();
node* find_arg(node* no, int i, int number_args, int* direction);
void add_implicit_args_conversion(node *no, char* expected_type, int direction);
void create_file_TAC(node* parser_tree);
void print_symbol_table_TAC(FILE *tac_file);
void print_code_TAC(node* tree, FILE *tac_file);
void parse_TAC(node *no, FILE *tac_file);
char* basic_instruction_TAC(char *instruction, char* arg1, char* arg2, char* arg3);
char* ari_instruction_TAC(node *no, char* register_symbol);
char* log_instruction_TAC(node *no, char* register_symbol);
char* rel_instruction_TAC(node *no, char* register_symbol);
char* intermediate_expression(node* no, char* register_symbol);
char* int_to_float_TAC(node* no, char* register_symbol);
char* float_to_int_TAC(node* no, char* register_symbol);
char* convert_instruction_TAC(node* no, char* register_symbol);

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
%token <str> QUOTES

%right <str> ASSIGN
%left <str> OP RELOP LOG

%type <no> prog decl-list var-decl func params-list params 
%type <no> stmt-list comp-stmt stmt local-decl
%type <no> expr simple-expr conditional-stmt iteration-stmt return-stmt
%type <no> var op-expr term call args arg-list string

%%

prog: 
    decl-list { 
        parser_tree = $1;
        check_semantic_error_no_main();
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
    '(' params-list ')' comp-stmt { 
        $$ = insert_node(FUNCTION, $5, $7, $1, $2);
        pop_stack();
        if (DEBUG_MODE) {printf("func #1 %s %s\n", $1, $2);}
    }
;

params-list: 
    params {
        $$ = $1;
        if (DEBUG_MODE) {printf("params-list #1\n");}
    }
    | { 
        $$ = NULL; 
        if (DEBUG_MODE) {printf("params-list #2\n");}
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
;

comp-stmt:
    '{' local-decl stmt-list '}' { 
        $$ = insert_node(COMPOUND_STATEMENT, $2, $3, NULL, NULL);
        if (DEBUG_MODE) {printf("comp-stmt\n");}
    }
;

local-decl:
    local-decl var-decl { 
        $$ = insert_node(LOCAL_DECLARATION_LIST, $1, $2, NULL, NULL);
        if (DEBUG_MODE) {printf("local-decl #1");}
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
        $$ = insert_node(PRINT_STATEMENT, $4, NULL, "void", $1);
        if (DEBUG_MODE) {printf("stmt #5 %s\n", $1);}
    }
    | PRINT '(' var ')' ';' { 
        $$ = insert_node(PRINT_STATEMENT, $3, NULL, "void", $1); 
        if (DEBUG_MODE) {printf("stmt #6 %s\n", $1);} 
    }
    | SCAN '(' var ')' ';' { 
        $$ = insert_node(SCAN_STATEMENT, $3, NULL, "void", $1); 
        if (DEBUG_MODE) {printf("stmt #7 %s\n", $1);}
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
        check_semantic_error_return_type($$->type, $$);
        if (DEBUG_MODE) {printf("return-stmt #1 %s\n", $1);}
    }
    | RETURN ';' { 
        $$ = insert_node(RETURN_STATEMENT, NULL, NULL, "void", $1); 
        check_semantic_error_return_type($$->type, $$);
        if (DEBUG_MODE) {printf("return-stmt #2 %s\n", $1);}
    }
;

var:
    ID { 
        symbol_node* s = find_symbol($1);
        char* type = NULL;
        if(s != NULL){
            type = s->type;
        }
        // Conversão pra TAC
        char *aux = (char *)malloc((1 + 100) * sizeof(char));
        strcpy(aux, s->name);
        strcat(aux, "__");
        strcat(aux, s->scope_name);
        // Conversão pra TAC
        $$ = insert_node(VARIABLE, NULL, NULL, type, aux);
        if (DEBUG_MODE) {printf("var %s\n", aux);}
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
        check_semantic_error_type_mismatch_args($3, $1);
        if (DEBUG_MODE) {printf("call #1 %s\n", $1);}
    }
    | STRCONCAT '(' args ')' { 
        $$ = insert_node(STRCONCAT_STATEMENT, $3, NULL, "string", $1); 
        check_semantic_error_type_mismatch_args_native_function($3, $1);
        if (DEBUG_MODE) {printf("call #2 %s\n", $1);}
    }
    | STRCOPY '(' args ')' { 
        $$ = insert_node(STRCOPY_STATEMENT, $3, NULL, "string", $1);
        check_semantic_error_type_mismatch_args_native_function($3, $1);
        if (DEBUG_MODE) {printf("call #4 %s\n", $1);}
    }
    | STRINSERT '(' args ')' {  
        $$ = insert_node(STRINSERT_STATEMENT, $3, NULL, "string", $1);
        check_semantic_error_type_mismatch_args_native_function($3, $1);
        if (DEBUG_MODE) {printf("call #5 %s\n", $1);}
    }
    | STRUPPER '(' args ')' {  
        $$ = insert_node(STRUPPER_STATEMENT, $3, NULL, "string", $1);
        check_semantic_error_type_mismatch_args_native_function($3, $1);
        if (DEBUG_MODE) {printf("call #6 %s\n", $1);}
    }
    | STRLOWER '(' args ')' {  
        $$ = insert_node(STRLOWER_STATEMENT, $3, NULL, "string", $1);
        check_semantic_error_type_mismatch_args_native_function($3, $1);
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

// Arrumar na gramática
arg-list:
    simple-expr ',' arg-list { 
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
        case STRCONCAT_STATEMENT:
            printf("STRCONCAT");
        break;
        case STRCOPY_STATEMENT:
            printf("STRCOPY");
        break;
        case STRINSERT_STATEMENT:
            printf("STRINSERT");
        break;
        case STRUPPER_STATEMENT:
            printf("STRUPPER");
        break;
        case STRLOWER_STATEMENT:
            printf("STRLOWER");
        break;
        case LOCAL_DECLARATION_LIST:
            printf("LOCAL_DECLARATION_LIST");
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

// Concatena strings do stackoverflow
char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, "::");
    strcat(result, s2);
    return result;
}

// Create symbol node
symbol_node* create_symbol(char* key, char *name, char* type, char symbol_type, char* scope_name){
    symbol_node *s = (symbol_node *)malloc(sizeof *s);
    s->key = key;
    s->name = name;
    s->type = type;
    s->symbol_type = symbol_type;
    s->scope_name = scope_name;
    s->param_list = NULL;

    // Referência de parâmetros para função
    if(symbol_type == 'P'){
        symbol_node *f;
        param_node *prev_p;
        scope* scope = get_stack_head();
        char* function_name = scope->scope_name;
        char* function_key = concat(function_name, stack->scope_name);
        HASH_FIND_STR(symbol_table, function_key, f);
        if(f != NULL){
            param_node *p = (param_node *)malloc(sizeof *p);
            p->key = key;
            p->next = NULL;
            if(f->param_list == NULL){
                f->param_list = p;
            }
            else{
                prev_p = f->param_list;
                while(prev_p->next != NULL){
                    prev_p = prev_p->next;
                }
                prev_p->next = p;
            }
        }
    }
    return s;
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
    if(
        (strcmp(s->scope_name, "global") == 0) && 
        s->next == NULL
    ) {
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
    symbol_node *ps;
    param_node *p;
    int number_of_space;
    printf("\n\n----------  TABELA DE SÍMBOLOS ----------\n\n");
    for(s=symbol_table; s != NULL; s=s->hh.next) {
        if(s->symbol_type != 'P'){
            printf("key: %30s | name: %20s | type: %10s | symbol_type: %c | scope: %10s |\n", s->key, s->name, s->type, s->symbol_type, s->scope_name);
            if(s->symbol_type == 'F'){
                for(p=s->param_list; p != NULL; p=p->next) {
                    HASH_FIND_STR(symbol_table, p->key, ps);
                    if(ps != NULL){
                        for(number_of_space = 36; number_of_space > 0; number_of_space--){
                            printf(" ");
                        }
                        printf("| param_name: %14s | type: %10s | symbol_type: %c | scope: %10s |\n", ps->name, ps->type, ps->symbol_type, ps->scope_name);
                    }
                }
            }
        }
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
    if(
        s == NULL && 
        (strcmp(scope->scope_name, "global") != 0)
    ){
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
void add_implicit_conversion(node *no, char* func_type){
    node* conversion_node;
    if(no->node_class == RETURN_STATEMENT){
        if(strcmp(no->left->type, "int") == 0 && strcmp(func_type, "float") == 0){
            conversion_node = insert_node(INT_TO_FLOAT, no->left, NULL, "float", NULL);
            no->left = conversion_node;
        }
        else{
            conversion_node = insert_node(FLOAT_TO_INT, no->left, NULL, "int", NULL); 
            no->left = conversion_node;
        }
    }
    else{
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
            add_implicit_conversion(no, NULL);
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

// Erro semantico de retorno existente em função void
void semantic_error_return_in_void(char* type){
    char *error = (char *)malloc(
        (strlen(type) + 1 + 81) * sizeof(char)
    ); // +1 for the null-terminator and 81 for semantic error message
    sprintf(error, "semantic error, return of type %s in void function, expected no return or return;", type);
    yyerror(error);
    free(error);
}

void check_semantic_error_return_type(char* return_type, node* no){
    symbol_node *s;
    scope* scope = get_stack_head();
    char* function_name = scope->scope_name;
    char* key = concat(function_name, stack->scope_name);
    HASH_FIND_STR(symbol_table, key, s);
    if(s != NULL){
        if(strcmp(return_type, s->type) != 0){
            if(strcmp("void", s->type) == 0){
                semantic_error_return_in_void(return_type);
            }
            else if( // type mismatch -- implicit conversion
                (strcmp(return_type, "int") == 0 && strcmp(s->type, "float") == 0) || 
                (strcmp(return_type, "float") == 0 && strcmp(s->type, "int") == 0)
            ){
                add_implicit_conversion(no, s->type);
                no->type = no->left->type;
            }
            else{ // type mismatch -- no implicit conversion
                semantic_error_return_type(return_type, s->type);
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

// Erro semantico de numero de argumentos errado
void semantic_error_wrong_number_arguments(char* function_name, int number_args, int number_param){
    char *error = (char *)malloc(
        (strlen(function_name) + 1 + 70) * sizeof(char)
    ); // +1 for the null-terminator and 70 for semantic error message
    sprintf(error, "semantic error, call of function (%s) with %d arguments, expected %d", function_name, number_args, number_param);
    yyerror(error);
    free(error);
}

// Erro semantico de tipo incompatível entre arg e params
void semantic_error_type_mismatch_args(char* function_name, char* arg_name, char* type_arg, char* param_name, char* type_param){
    char *error = (char *)malloc(
        (strlen(function_name) + strlen(type_param) + strlen(type_arg) + strlen(arg_name) + strlen(param_name) + 1 + 117) * sizeof(char)
    ); // +1 for the null-terminator and 117 for semantic error message
    sprintf(error, "semantic error, type mismatch between argument (%s) of type %s and param (%s) of type %s during call of function (%s)", arg_name, type_arg, param_name, type_param, function_name);
    yyerror(error);
    free(error);
}

// Cria lista de argumentos a partir de um nó da árvore
args_node* create_args_list(node* no){
    args_node* args_list = NULL;
    args_node* arg_atual = NULL;
    node* no_atual = no;

    // Monta lista de argumentos
    if(no != NULL){
        if(no_atual->node_class == ARGS_LIST){
            // Destrincha ARGS_lIST
            while(no_atual->node_class == ARGS_LIST){
                // Esquerda
                args_node *a = (args_node *)malloc(sizeof *a);
                a->name = no_atual->left->value;
                a->type = no_atual->left->type;
                a->next = NULL;
                if(args_list == NULL){
                    args_list = a;
                    arg_atual = args_list;
                }
                else{
                    arg_atual->next = a;
                    arg_atual = arg_atual-> next;
                }
                // Direita no fim
                if(no_atual->right->node_class != ARGS_LIST){
                    args_node *a = (args_node *)malloc(sizeof *a);
                    a->name = no_atual->right->value;
                    a->type = no_atual->right->type;
                    a->next = NULL;
                    arg_atual->next = a;
                    arg_atual = arg_atual-> next;
                }
                no_atual = no_atual->right;
            }
        }
        // Nó unico
        else{
            args_node *a = (args_node *)malloc(sizeof *a);
            a->name = no->value;
            a->type = no->type;
            a->next = NULL;
            args_list = a;
        }
    }
    return args_list;
}

// Retorno o no da árvore do argumento da posição i
node* find_arg(node* no, int i, int number_args, int* direction){
    int j;
    node* aux = no;
    if((i == number_args - 1) && (i != 0)){

        j = i - 1;
    }
    else{
        j = i;
    }
    while(j > 0){
        aux = aux->right;
        j--;
    }
    if((i == number_args - 1) && (i != 0)){
        *direction = 1;
        return aux;
    }
    else{
        *direction = 0;
        return aux;
    }
}

// Adiciona nó de conversão implícita na árvore para argumentos.
// 
void add_implicit_args_conversion(node *no, char* expected_type, int direction){
    node* conversion_node;
    if(direction == 0){
        if(strcmp(no->left->type, "int") == 0 && strcmp(expected_type, "float") == 0){
            conversion_node = insert_node(INT_TO_FLOAT, no->left, NULL, "float", NULL);
            no->left = conversion_node;
        }
        else{
            conversion_node = insert_node(FLOAT_TO_INT, no->left, NULL, "int", NULL); 
            no->left = conversion_node;
        }
    }
    else{
        if(strcmp(no->right->type, "int") == 0 && strcmp(expected_type, "float") == 0){
            conversion_node = insert_node(INT_TO_FLOAT, no->right, NULL, "float", NULL);
            no->right = conversion_node;
        }
        else{
            conversion_node = insert_node(FLOAT_TO_INT, no->right, NULL, "int", NULL); 
            no->right = conversion_node;
        }
    }
    
}

// Checa erro semantico de tipo incompatível para argumentos
void check_semantic_error_type_mismatch_args(node* no, char* function_name){
    args_node* args_list = create_args_list(no);
    args_node* arg_atual = NULL;
    int number_args = 0;
    int number_param = 0;
    param_node* param_list = NULL;
    param_node* param_atual = NULL;

    // Pega params_list    
    symbol_node* f;
    char* key = concat(function_name, stack->scope_name);
    HASH_FIND_STR(symbol_table, key, f);
    if(f != NULL){
        param_list = f->param_list;
    }

    // Conta número de arumentos e parametros
    arg_atual = args_list;
    while(arg_atual != NULL){
        number_args++;
        arg_atual = arg_atual->next;
    }
    param_atual = param_list;
    while(param_atual != NULL){
        number_param++;
        param_atual = param_atual->next;
    }

    // Checa pelos erros
    if(number_args != number_param){
        // Numero errado de argumentos
        semantic_error_wrong_number_arguments(function_name, number_args, number_param);
    }
    else{
        symbol_node* s;
        arg_atual = args_list;
        param_atual = param_list;
        int direction;
        node* aux;
        int i = 0;
        while(arg_atual != NULL){
            HASH_FIND_STR(symbol_table, param_atual->key, s);
            if(s != NULL){
                if(
                    arg_atual->type != NULL &&
                    s->type != NULL &&
                    (strcmp(arg_atual->type, s->type) != 0)
                ){
                    if( // type mismatch -- implicit conversion
                        (strcmp(arg_atual->type, "int") == 0 && strcmp(s->type, "float") == 0) || 
                        (strcmp(arg_atual->type, "float") == 0 && strcmp(s->type, "int") == 0)
                    ){
                        aux = find_arg(no, i, number_args, &direction);
                        add_implicit_args_conversion(aux, s->type, direction);
                    }
                    else{// type mismatch
                        semantic_error_type_mismatch_args(function_name, arg_atual->name, arg_atual->type, s->name, s->type);
                    }
                }
            }
            arg_atual = arg_atual->next;
            param_atual = param_atual->next;
            i++;
        }
    }
}

// Cria lista de parâmetros esperada para funções nativas
args_node* create_param_list_native_function(char* function_name){
    args_node* param_list = NULL;
    int param_type = -1;
    if(
        (strcmp(function_name, "strUpper") == 0)||
        (strcmp(function_name, "strLower") == 0)
    ){
        param_type = 1;
    }
    else if(
        (strcmp(function_name, "strConcat") == 0)||
        (strcmp(function_name, "strCopy") == 0)
    ){
        param_type = 2;
    }
    else if((strcmp(function_name, "strInsert") == 0)){
        param_type = 3;
    }

    if(param_type != -1){
        args_node *a = (args_node *)malloc(sizeof *a);
        a->name = "string1";
        a->type = "string";
        a->next = NULL;
        param_list = a;
    }

    if(param_type == 2 || param_type == 3){
        args_node *a2 = (args_node *)malloc(sizeof *a2);
        a2->name = "string2";
        a2->type = "string";
        a2->next = NULL;
        param_list->next = a2;
    }

    if(param_type == 3){
        args_node *a3 = (args_node *)malloc(sizeof *a3);
        a3-> name = "int1";
        a3->type = "int";
        a3->next = NULL;
        param_list->next->next = a3;
    }

    return param_list;
}

// Checa type mismatch para args de função nativa
void check_semantic_error_type_mismatch_args_native_function(node* no, char* function_name){
    args_node* args_list = create_args_list(no);
    args_node* arg_atual = NULL;
    int number_args = 0;
    int number_param = 0;
    args_node* param_list = create_param_list_native_function(function_name);
    args_node* param_atual = NULL;

    // Conta número de arumentos e parametros
    arg_atual = args_list;
    while(arg_atual != NULL){
        number_args++;
        arg_atual = arg_atual->next;
    }
    param_atual = param_list;
    while(param_atual != NULL){
        number_param++;
        param_atual = param_atual->next;
    }

    // Checa pelos erros
    if(number_args != number_param){
        // Numero errado de argumentos
        semantic_error_wrong_number_arguments(function_name, number_args, number_param);
    }
    else{
        arg_atual = args_list;
        param_atual = param_list;
        int direction;
        node* aux;
        int i = 0;
        while(arg_atual != NULL){
            if(
                arg_atual->type != NULL &&
                param_atual->type != NULL &&
                (strcmp(arg_atual->type, param_atual->type) != 0)
            ){
                if( // type mismatch -- implicit conversion
                    (strcmp(arg_atual->type, "int") == 0 && strcmp(param_atual->type, "float") == 0) || 
                    (strcmp(arg_atual->type, "float") == 0 && strcmp(param_atual->type, "int") == 0)
                ){
                    aux = find_arg(no, i, number_args, &direction);
                    add_implicit_args_conversion(aux, param_atual->type, direction);
                }
                else{// type mismatch
                    semantic_error_type_mismatch_args(function_name, arg_atual->name, arg_atual->type, param_atual->name, param_atual->type);
                }
            }
            arg_atual = arg_atual->next;
            param_atual = param_atual->next;
            i++;
        }
    }
}

// Erro semantico de main não declarada
void semantic_error_no_main(){
    char *error = (char *)malloc(
        (1 + 47) * sizeof(char)
    ); // +1 for the null-terminator and 47 for semantic error message
    sprintf(error, "semantic error, no declaration of function main");
    yyerror(error);
    free(error);
}

// Checa erro semântico de main não declarada
void check_semantic_error_no_main(){
    symbol_node* s;
    char* key = concat("main", stack->scope_name);
    HASH_FIND_STR(symbol_table, key, s);
    if(s == NULL){
        semantic_error_no_main();
    }
}


// **********TAC**********

// Printa tabela de símbolos
void print_symbol_table_TAC(FILE *tac_file) {
    symbol_node *s;
    char *str = (char *)malloc((1 + 100) * sizeof(char));
    fputs(".table\n", tac_file);
    for(s=symbol_table; s != NULL; s=s->hh.next) {
        if(s->symbol_type != 'F'){
            if((strcmp(s->type, "string") == 0)){
                strcpy(str, "char");
            }
            else if ((strcmp(s->type, "bool") == 0)){
                strcpy(str, "int");
            }
            else{
                strcpy(str, s->type);
            }
            strcat(str, " ");
            strcat(str, s->name);
            strcat(str, "__");
            strcat(str, s->scope_name);
            if((strcmp(s->type, "string") == 0)){
                strcat(str, " [] = \"\"");
            }
            strcat(str, "\n");
            fputs(str, tac_file);
        }
    }
    fputs("int true = 1\n", tac_file);
    fputs("int false = 0\n", tac_file);
    free(str);
}

char* basic_instruction_TAC(char *instruction, char* arg1, char* arg2, char* arg3){
    char *str = (char *)malloc((1 + 500) * sizeof(char));
    strcpy(str, instruction);
    if(arg1 != NULL){
        if((strcmp(instruction, "print") == 0)){
            strcat(str, " ");
            strcat(str, "\"");
            strcat(str, arg1);
            strcat(str, "\"");
        }
        else{
            strcat(str, " ");
            strcat(str, arg1);
        }
        if(arg2 != NULL){
            strcat(str, ", ");
            strcat(str, arg2);
            if(arg3 != NULL){
                strcat(str, ", ");
                strcat(str, arg3);
            }
        }
    }
    strcat(str, "\n");
    return str;
}

char* int_to_float_TAC(node* no, char* register_symbol){
    char *str = (char *)malloc((1 + 500) * sizeof(char));
    if(no->left->node_class == ARITHIMETIC_EXPRESSION){
        strcpy(str, ari_instruction_TAC(no->left, "$3"));
    }
    else{
        strcpy(str, "mov $3, ");
        strcat(str, no->left->value);
        strcat(str, "\n");
    }
    strcat(str, "inttofl ");
    strcat(str, register_symbol);
    strcat(str, ", $3\n");
    return str;
}

char* float_to_int_TAC(node* no, char* register_symbol){
    char *str = (char *)malloc((1 + 500) * sizeof(char));
    if(no->left->node_class == ARITHIMETIC_EXPRESSION){
        strcpy(str, ari_instruction_TAC(no->left, "$3"));
    }
    else{
        strcpy(str, "mov $3, ");
        strcat(str, no->left->value);
        strcat(str, "\n");
    }
    strcat(str, "fltoint ");
    strcat(str, register_symbol);
    strcat(str, ", $3\n");
    return str;
}

char* convert_instruction_TAC(node* no, char* register_symbol){
    char *str = (char *)malloc((1 + 500) * sizeof(char));
    if(no->node_class == INT_TO_FLOAT){
        strcpy(str, int_to_float_TAC(no, register_symbol));
    }
    else if(no->node_class == FLOAT_TO_INT){
        strcpy(str, float_to_int_TAC(no, register_symbol));
    }
    else{
        strcpy(str, "mov ");
        strcat(str, register_symbol);
        strcat(str, ", ");
        strcat(str, no->value);
        strcat(str, "\n");
    }
    return str;
}

char* ari_instruction_TAC(node *no, char* register_symbol){
    char *str = (char *)malloc((1 + 500) * sizeof(char));
    if(no->left->node_class == ARITHIMETIC_EXPRESSION){
        strcpy(str, ari_instruction_TAC(no->left, register_symbol));
        if(no->right->node_class == ARITHIMETIC_EXPRESSION){
            strcat(str, ari_instruction_TAC(no->right, "$5"));
        }
        else{
            strcat(str, convert_instruction_TAC(no->right, "$5"));
        }
        if(strcmp(no->value, "+") == 0){
            strcat(str, "add ");
        } 
        else if(strcmp(no->value, "-") == 0){
            strcat(str, "sub ");
        } 
        else if(strcmp(no->value, "*") == 0){
            strcat(str, "mul ");
        } 
        else if(strcmp(no->value, "/") == 0){
            strcat(str, "div ");
        }
        strcat(str, register_symbol);
        strcat(str, ", ");
        strcat(str, register_symbol);
        strcat(str, ", $5\n");
    }
    else if(no->right->node_class == ARITHIMETIC_EXPRESSION){
        strcpy(str, ari_instruction_TAC(no->right, register_symbol));
        strcat(str, convert_instruction_TAC(no->left, "$5"));
        if(strcmp(no->value, "+") == 0){
            strcat(str, "add ");
        } 
        else if(strcmp(no->value, "-") == 0){
            strcat(str, "sub ");
        } 
        else if(strcmp(no->value, "*") == 0){
            strcat(str, "mul ");
        } 
        else if(strcmp(no->value, "/") == 0){
            strcat(str, "div ");
        }
        strcat(str, register_symbol);
        strcat(str, ", $5, ");
        strcat(str, register_symbol);
        strcat(str, "\n");
    }
    else{
        strcpy(str, convert_instruction_TAC(no->left, "$5"));
        strcat(str, convert_instruction_TAC(no->right, "$6"));
        if(strcmp(no->value, "+") == 0){
            strcat(str, "add ");
        } 
        else if(strcmp(no->value, "-") == 0){
            strcat(str, "sub ");
        } 
        else if(strcmp(no->value, "*") == 0){
            strcat(str, "mul ");
        } 
        else if(strcmp(no->value, "/") == 0){
            strcat(str, "div ");
        }
        strcat(str, register_symbol);
        strcat(str, ", $5, $6\n");
    }
    return str;
}

char* log_instruction_TAC(node *no, char* register_symbol){
    char *str = (char *)malloc((1 + 500) * sizeof(char));
    if(
        no->left->node_class == LOGICAL_EXPRESSION ||
        no->left->node_class == RELATIONAL_EXPRESSION 
    ){
        strcpy(str, intermediate_expression(no->left, register_symbol));
        if(
            no->right->node_class == LOGICAL_EXPRESSION ||
            no->right->node_class == RELATIONAL_EXPRESSION
        ){
            strcat(str, intermediate_expression(no->right, "$4"));
        }
        if(strcmp(no->value, "&&") == 0){
            strcat(str, "and ");
        } 
        else if(strcmp(no->value, "||") == 0){
            strcat(str, "or ");
        } 
        else if(strcmp(no->value, "!") == 0){
            strcat(str, "not ");
        }
        strcat(str, register_symbol);
        strcat(str, ", ");
        strcat(str, register_symbol);
        strcat(str, ", ");
        if(
            no->right->node_class == LOGICAL_EXPRESSION ||
            no->right->node_class == RELATIONAL_EXPRESSION
        ){
            strcat(str, "$4");
        }
        else{
            strcat(str, no->right->value);
        }
        strcat(str, "\n");
    }
    else if(
        no->right->node_class == LOGICAL_EXPRESSION ||
        no->right->node_class == RELATIONAL_EXPRESSION
    ){
        strcpy(str, intermediate_expression(no->right, register_symbol));
        if(strcmp(no->value, "&&") == 0){
            strcat(str, "and ");
        } 
        else if(strcmp(no->value, "||") == 0){
            strcat(str, "or ");
        } 
        else if(strcmp(no->value, "!") == 0){
            strcat(str, "not ");
        }
        strcat(str, register_symbol);
        strcat(str, ", ");
        strcat(str, no->left->value);
        strcat(str, ", ");
        strcat(str, register_symbol);
        strcat(str, "\n");
    }
    else{
        if(strcmp(no->value, "&&") == 0){
            strcpy(str, "and ");
        } 
        else if(strcmp(no->value, "||") == 0){
            strcpy(str, "or ");
        } 
        else if(strcmp(no->value, "!") == 0){
            strcpy(str, "not ");
        }
        strcat(str, register_symbol);
        strcat(str, ", ");
        strcat(str, no->left->value);
        strcat(str, ", ");
        strcat(str, no->right->value);
        strcat(str, "\n");
    }
    return str;
}


char* rel_instruction_TAC(node *no, char* register_symbol){
    char *str = (char *)malloc((1 + 500) * sizeof(char));
    if(strcmp(no->value, "<") == 0){
        strcpy(str, intermediate_expression(no->left, "$1"));
        strcat(str, intermediate_expression(no->right, "$2"));
        strcat(str, "slt ");
        strcat(str, register_symbol);
        strcat(str, ", $1, $2\n");
    } 
    else if(strcmp(no->value, "<=") == 0){
        strcpy(str, intermediate_expression(no->left, "$1"));
        strcat(str, intermediate_expression(no->right, "$2"));
        strcat(str, "sleq ");
        strcat(str, register_symbol);
        strcat(str, ", $1, $2\n");
    }
    else if(strcmp(no->value, ">") == 0){
        strcpy(str, intermediate_expression(no->left, "$1"));
        strcat(str, intermediate_expression(no->right, "$2"));
        strcat(str, "slt ");
        strcat(str, register_symbol);
        strcat(str, ", $2, $1\n");
    }
    else if(strcmp(no->value, ">=") == 0){
        strcpy(str, intermediate_expression(no->left, "$1"));
        strcat(str, intermediate_expression(no->right, "$2"));
        strcat(str, "sleq ");
        strcat(str, register_symbol);
        strcat(str, ", $2, $1\n");
    }
    else if(strcmp(no->value, "==") == 0){
        strcpy(str, intermediate_expression(no->left, "$1"));
        strcat(str, intermediate_expression(no->right, "$2"));
        strcat(str, "seq ");
        strcat(str, register_symbol);
        strcat(str, ", $1, $2\n");
    }
    else if(strcmp(no->value, "!=") == 0){
        strcpy(str, intermediate_expression(no->left, "$1"));
        strcat(str, intermediate_expression(no->right, "$2"));
        strcat(str, "seq ");
        strcat(str, register_symbol);
        strcat(str, ", $1, $2\n");
        strcat(str, "not ");
        strcat(str, register_symbol);
        strcat(str, "\n");
    }
    return str;
}

char* intermediate_expression(node* no, char* register_symbol){
    char *str = (char *)malloc((1 + 500) * sizeof(char));
    if(no->node_class == ARITHIMETIC_EXPRESSION){
        str = ari_instruction_TAC(no, register_symbol);
    }
    else if(no->node_class == LOGICAL_EXPRESSION){
        str = log_instruction_TAC(no, register_symbol);
    }
    else if(no->node_class == RELATIONAL_EXPRESSION){
        str = rel_instruction_TAC(no, register_symbol);
    }
    else{
        str = basic_instruction_TAC("mov", register_symbol, no->value, NULL);
    }
    return str;
}

void parse_TAC(node *no, FILE *tac_file){
    char* str = NULL;
    if(no != NULL){
        switch(no->node_class){
            case PRINT_STATEMENT:
                if(no->left->node_class == STRING){
                    str = basic_instruction_TAC("print", no->left->value, NULL, NULL);
                }
                else{
                    str = basic_instruction_TAC("println", no->left->value, NULL, NULL);
                }
                break;
            case ASSIGN_EXPRESSION:
                if(no->right->node_class == LOGICAL_EXPRESSION){
                    str = log_instruction_TAC(no->right, "$0");
                    strcat(str, basic_instruction_TAC("mov", no->left->value, "$0", NULL));
                }
                else if(no->right->node_class == ARITHIMETIC_EXPRESSION){
                    str = ari_instruction_TAC(no->right, "$0");
                    strcat(str, basic_instruction_TAC("mov", no->left->value, "$0", NULL));
                }
                else if(no->right->node_class == RELATIONAL_EXPRESSION){
                    str = rel_instruction_TAC(no->right, "$0");
                    strcat(str, basic_instruction_TAC("mov", no->left->value, "$0", NULL));
                }
                else if(no->right->node_class == FLOAT_TO_INT || no->right->node_class == INT_TO_FLOAT){
                    str = convert_instruction_TAC(no->right, "$0");
                    strcat(str, basic_instruction_TAC("mov", no->left->value, "$0", NULL));
                }
                else{
                    str = basic_instruction_TAC("mov", no->left->value, no->right->value, NULL);
                }
                break;
            default:
                break;
        }
        if(str != NULL){
            fputs(str, tac_file);
            free(str);
        }
        parse_TAC(no->left, tac_file);
        parse_TAC(no->right, tac_file);
    }
}

void print_code_TAC(node* tree, FILE *tac_file){
    fputs(".code\n", tac_file);
    parse_TAC(tree, tac_file);
    fputs("nop", tac_file);
    fputs("\n", tac_file);
}

void create_file_TAC(node* parser_tree){
    FILE *tac_file;
    tac_file = fopen("a.tac", "w+");
    print_symbol_table_TAC(tac_file);
    print_code_TAC(parser_tree, tac_file);
    fclose(tac_file);
    printf("\nArquivo a.tac criado\n");
}


int main(int argc, char **argv) {
    ++argv, --argc;
    if(argc > 0)
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    initialize_global_scope();
    yyparse();
    print_symbol_table();
    if(total_errors == 0){
        printf("\n\n----------  ABSTRACT SYNTAX TREE ----------\n\n");
        print_tree(parser_tree, 0);
        create_file_TAC(parser_tree);
    }
    yylex_destroy();
    free_tree(parser_tree);
    free_symbol_table();
    return 0;
}