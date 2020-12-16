/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "syntax.y"

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


#line 206 "syntax.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_BOOL = 5,                       /* BOOL  */
  YYSYMBOL_STR = 6,                        /* STR  */
  YYSYMBOL_TYPE = 7,                       /* TYPE  */
  YYSYMBOL_ID = 8,                         /* ID  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_RETURN = 12,                    /* RETURN  */
  YYSYMBOL_PRINT = 13,                     /* PRINT  */
  YYSYMBOL_SCAN = 14,                      /* SCAN  */
  YYSYMBOL_STRUPPER = 15,                  /* STRUPPER  */
  YYSYMBOL_STRLOWER = 16,                  /* STRLOWER  */
  YYSYMBOL_STRCONCAT = 17,                 /* STRCONCAT  */
  YYSYMBOL_STRCOPY = 18,                   /* STRCOPY  */
  YYSYMBOL_STRINSERT = 19,                 /* STRINSERT  */
  YYSYMBOL_QUOTES = 20,                    /* QUOTES  */
  YYSYMBOL_ASSIGN = 21,                    /* ASSIGN  */
  YYSYMBOL_OP = 22,                        /* OP  */
  YYSYMBOL_RELOP = 23,                     /* RELOP  */
  YYSYMBOL_LOG = 24,                       /* LOG  */
  YYSYMBOL_25_ = 25,                       /* ';'  */
  YYSYMBOL_26_ = 26,                       /* '('  */
  YYSYMBOL_27_ = 27,                       /* ')'  */
  YYSYMBOL_28_ = 28,                       /* ','  */
  YYSYMBOL_29_ = 29,                       /* '{'  */
  YYSYMBOL_30_ = 30,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_prog = 32,                      /* prog  */
  YYSYMBOL_33_decl_list = 33,              /* decl-list  */
  YYSYMBOL_34_var_decl = 34,               /* var-decl  */
  YYSYMBOL_func = 35,                      /* func  */
  YYSYMBOL_36_1 = 36,                      /* $@1  */
  YYSYMBOL_37_params_list = 37,            /* params-list  */
  YYSYMBOL_params = 38,                    /* params  */
  YYSYMBOL_39_comp_stmt = 39,              /* comp-stmt  */
  YYSYMBOL_40_local_decl = 40,             /* local-decl  */
  YYSYMBOL_41_stmt_list = 41,              /* stmt-list  */
  YYSYMBOL_stmt = 42,                      /* stmt  */
  YYSYMBOL_expr = 43,                      /* expr  */
  YYSYMBOL_44_simple_expr = 44,            /* simple-expr  */
  YYSYMBOL_45_conditional_stmt = 45,       /* conditional-stmt  */
  YYSYMBOL_46_iteration_stmt = 46,         /* iteration-stmt  */
  YYSYMBOL_47_return_stmt = 47,            /* return-stmt  */
  YYSYMBOL_var = 48,                       /* var  */
  YYSYMBOL_49_op_expr = 49,                /* op-expr  */
  YYSYMBOL_term = 50,                      /* term  */
  YYSYMBOL_call = 51,                      /* call  */
  YYSYMBOL_args = 52,                      /* args  */
  YYSYMBOL_53_arg_list = 53,               /* arg-list  */
  YYSYMBOL_string = 54                     /* string  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   122

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  119

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   279


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      26,    27,     2,     2,    28,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   163,   163,   171,   175,   179,   183,   190,   198,   198,
     210,   214,   221,   226,   234,   241,   245,   252,   256,   263,
     267,   271,   275,   279,   283,   287,   294,   299,   306,   312,
     319,   323,   331,   338,   344,   352,   365,   371,   376,   384,
     388,   392,   396,   400,   404,   408,   415,   425,   430,   435,
     440,   445,   453,   457,   465,   469,   476,   480
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "BOOL",
  "STR", "TYPE", "ID", "IF", "ELSE", "WHILE", "RETURN", "PRINT", "SCAN",
  "STRUPPER", "STRLOWER", "STRCONCAT", "STRCOPY", "STRINSERT", "QUOTES",
  "ASSIGN", "OP", "RELOP", "LOG", "';'", "'('", "')'", "','", "'{'", "'}'",
  "$accept", "prog", "decl-list", "var-decl", "func", "$@1", "params-list",
  "params", "comp-stmt", "local-decl", "stmt-list", "stmt", "expr",
  "simple-expr", "conditional-stmt", "iteration-stmt", "return-stmt",
  "var", "op-expr", "term", "call", "args", "arg-list", "string", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    59,    40,    41,    44,   123,
     125
};
#endif

#define YYPACT_NINF (-97)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       2,     5,    34,     2,   -97,   -97,    10,   -97,   -97,   -97,
     -97,    12,    32,    41,    13,    36,   -97,    31,    60,   -97,
     -97,    77,    61,   -97,    78,   -97,    39,    10,   -97,   -97,
     -97,    62,    63,    64,     7,    65,    66,    67,    68,    69,
      70,    71,   -97,    58,   -97,   -97,   -97,    73,   -97,   -97,
     -97,    79,    48,   -97,   -97,    58,    58,    58,   -97,    74,
     -97,    21,    93,    58,    58,    58,    58,    58,     0,    75,
     -97,    58,    58,    58,    58,    59,    76,   -97,    80,    81,
     -97,   -97,   -97,    82,    83,    84,    85,    86,    87,    88,
     -97,   -97,   -97,   -97,   -97,   -17,   -97,    58,   -97,    31,
      31,     8,    91,    92,   -97,   -97,   -97,   -97,   -97,   -97,
      94,   -97,    95,   -97,   -97,    31,    96,   -97,   -97
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     4,     6,     8,     1,     3,     5,
       7,     0,    11,     0,     0,    10,    13,     0,     0,    16,
       9,     0,    18,    12,     0,    15,     0,     0,    43,    44,
      45,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,     0,    14,    17,    19,     0,    20,    21,
      22,    40,    29,    38,    41,    53,     0,     0,    34,     0,
      40,     0,     0,    53,    53,    53,    53,    53,     0,     0,
      27,     0,     0,     0,     0,    55,     0,    52,     0,     0,
      33,    35,    57,     0,     0,     0,     0,     0,     0,     0,
      56,    42,    39,    26,    36,    28,    37,     0,    46,     0,
       0,     0,     0,     0,    50,    51,    47,    48,    49,    54,
      30,    32,     0,    24,    25,     0,     0,    31,    23
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -97,   -97,   -97,    -1,   102,   -97,   -97,   -97,   -96,   -97,
     -97,   -97,    35,   -26,   -97,   -97,   -97,   -25,    45,   -56,
     -97,    16,    22,    38
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    11,    14,    15,    20,    22,
      26,    45,    46,    75,    48,    49,    50,    60,    52,    53,
      54,    76,    77,    68
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      47,    51,     8,   110,   111,    72,    90,    74,    59,     1,
      28,    29,    30,     6,    90,    31,    94,    69,    96,   117,
      91,    25,    37,    38,    39,    40,    41,    42,   112,    81,
      78,    79,    58,    43,     7,    10,    83,    84,    12,    13,
      17,    82,    28,    29,    30,    47,    51,    31,    32,    16,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      19,    28,    29,    30,    18,    43,    31,    21,    24,    44,
      72,    73,    74,    37,    38,    39,    40,    41,    42,    85,
      86,    87,    88,    89,    43,    23,    27,    97,    55,    56,
      57,    61,    62,    63,    64,    65,    66,    67,    70,    80,
      71,    81,    92,    98,   115,     9,    93,    99,   100,   102,
     103,   104,   105,   106,   107,   108,   113,   114,    95,   109,
     101,   118,   116
};

static const yytype_int8 yycheck[] =
{
      26,    26,     3,    99,   100,    22,     6,    24,    34,     7,
       3,     4,     5,     8,     6,     8,    72,    43,    74,   115,
      20,    22,    15,    16,    17,    18,    19,    20,    20,     8,
      56,    57,    25,    26,     0,    25,    61,    62,    26,     7,
      27,    20,     3,     4,     5,    71,    71,     8,     9,     8,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      29,     3,     4,     5,    28,    26,     8,     7,     7,    30,
      22,    23,    24,    15,    16,    17,    18,    19,    20,    63,
      64,    65,    66,    67,    26,     8,     8,    28,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    25,    25,
      21,     8,    27,    27,    10,     3,    71,    27,    27,    27,
      27,    27,    27,    27,    27,    27,    25,    25,    73,    97,
      82,    25,    27
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    32,    33,    34,    35,     8,     0,    34,    35,
      25,    36,    26,     7,    37,    38,     8,    27,    28,    29,
      39,     7,    40,     8,     7,    34,    41,     8,     3,     4,
       5,     8,     9,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    26,    30,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    26,    26,    26,    25,    44,
      48,    26,    26,    26,    26,    26,    26,    26,    54,    44,
      25,    21,    22,    23,    24,    44,    52,    53,    44,    44,
      25,     8,    20,    48,    48,    52,    52,    52,    52,    52,
       6,    20,    27,    43,    50,    49,    50,    28,    27,    27,
      27,    54,    27,    27,    27,    27,    27,    27,    27,    53,
      39,    39,    20,    25,    25,    10,    27,    39,    25
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    33,    33,    34,    36,    35,
      37,    37,    38,    38,    39,    40,    40,    41,    41,    42,
      42,    42,    42,    42,    42,    42,    43,    43,    44,    44,
      45,    45,    46,    47,    47,    48,    49,    49,    49,    50,
      50,    50,    50,    50,    50,    50,    51,    51,    51,    51,
      51,    51,    52,    52,    53,    53,    54,    54
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     3,     0,     7,
       1,     0,     4,     2,     4,     2,     0,     2,     0,     1,
       1,     1,     1,     7,     5,     5,     3,     2,     3,     1,
       5,     7,     5,     3,     2,     1,     3,     3,     1,     3,
       1,     1,     3,     1,     1,     1,     4,     4,     4,     4,
       4,     4,     1,     0,     3,     1,     2,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* prog: decl-list  */
#line 163 "syntax.y"
              { 
        parser_tree = (yyvsp[0].no);
        check_semantic_error_no_main();
        if (DEBUG_MODE) {printf("prog\n");}
    }
#line 1688 "syntax.tab.c"
    break;

  case 3: /* decl-list: decl-list var-decl  */
#line 171 "syntax.y"
                       { 
        (yyval.no) = insert_node(DECLARATION_LIST, (yyvsp[-1].no), (yyvsp[0].no), NULL, NULL);
        if (DEBUG_MODE) {printf("decl-list #1\n");} 
    }
#line 1697 "syntax.tab.c"
    break;

  case 4: /* decl-list: var-decl  */
#line 175 "syntax.y"
               { 
        (yyval.no) = (yyvsp[0].no);
        if (DEBUG_MODE) {printf("decl-list #2\n");}
    }
#line 1706 "syntax.tab.c"
    break;

  case 5: /* decl-list: decl-list func  */
#line 179 "syntax.y"
                     { 
        (yyval.no) = insert_node(DECLARATION_LIST, (yyvsp[-1].no), (yyvsp[0].no), NULL, NULL);
        if (DEBUG_MODE) {printf("decl-list #3\n");} 
    }
#line 1715 "syntax.tab.c"
    break;

  case 6: /* decl-list: func  */
#line 183 "syntax.y"
           { 
        (yyval.no) = (yyvsp[0].no);
        if (DEBUG_MODE) {printf("decl-list #4\n");}
    }
#line 1724 "syntax.tab.c"
    break;

  case 7: /* var-decl: TYPE ID ';'  */
#line 190 "syntax.y"
                { 
        (yyval.no) = insert_node(VARIABLE_DECLARATION, NULL, NULL, (yyvsp[-2].str), (yyvsp[-1].str));
        add_symbol((yyvsp[-1].str), (yyvsp[-2].str), 'V');
        if (DEBUG_MODE) {printf("var-decl %s %s\n", (yyvsp[-2].str), (yyvsp[-1].str));}
    }
#line 1734 "syntax.tab.c"
    break;

  case 8: /* $@1: %empty  */
#line 198 "syntax.y"
            { 
        add_symbol((yyvsp[0].str), (yyvsp[-1].str), 'F');
        push_stack((yyvsp[0].str), (yyvsp[-1].str));
    }
#line 1743 "syntax.tab.c"
    break;

  case 9: /* func: TYPE ID $@1 '(' params-list ')' comp-stmt  */
#line 202 "syntax.y"
                                  { 
        (yyval.no) = insert_node(FUNCTION, (yyvsp[-2].no), (yyvsp[0].no), (yyvsp[-6].str), (yyvsp[-5].str));
        pop_stack();
        if (DEBUG_MODE) {printf("func #1 %s %s\n", (yyvsp[-6].str), (yyvsp[-5].str));}
    }
#line 1753 "syntax.tab.c"
    break;

  case 10: /* params-list: params  */
#line 210 "syntax.y"
           {
        (yyval.no) = (yyvsp[0].no);
        if (DEBUG_MODE) {printf("params-list #1\n");}
    }
#line 1762 "syntax.tab.c"
    break;

  case 11: /* params-list: %empty  */
#line 214 "syntax.y"
      { 
        (yyval.no) = NULL; 
        if (DEBUG_MODE) {printf("params-list #2\n");}
    }
#line 1771 "syntax.tab.c"
    break;

  case 12: /* params: params ',' TYPE ID  */
#line 221 "syntax.y"
                       { 
        (yyval.no) = insert_node(PARAMETER, (yyvsp[-3].no), NULL, (yyvsp[-1].str), (yyvsp[0].str));
        add_symbol((yyvsp[0].str), (yyvsp[-1].str), 'P');
        if (DEBUG_MODE) {printf("params #1 %s %s\n", (yyvsp[-1].str), (yyvsp[0].str));}
    }
#line 1781 "syntax.tab.c"
    break;

  case 13: /* params: TYPE ID  */
#line 226 "syntax.y"
              { 
        (yyval.no) = insert_node(PARAMETER, NULL, NULL, (yyvsp[-1].str), (yyvsp[0].str));
        add_symbol((yyvsp[0].str), (yyvsp[-1].str), 'P');
        if (DEBUG_MODE) {printf("params #2 %s %s\n", (yyvsp[-1].str), (yyvsp[0].str));}
    }
#line 1791 "syntax.tab.c"
    break;

  case 14: /* comp-stmt: '{' local-decl stmt-list '}'  */
#line 234 "syntax.y"
                                 { 
        (yyval.no) = insert_node(COMPOUND_STATEMENT, (yyvsp[-2].no), (yyvsp[-1].no), NULL, NULL);
        if (DEBUG_MODE) {printf("comp-stmt\n");}
    }
#line 1800 "syntax.tab.c"
    break;

  case 15: /* local-decl: local-decl var-decl  */
#line 241 "syntax.y"
                        { 
        (yyval.no) = insert_node(LOCAL_DECLARATION_LIST, (yyvsp[-1].no), (yyvsp[0].no), NULL, NULL);
        if (DEBUG_MODE) {printf("local-decl #1");}
    }
#line 1809 "syntax.tab.c"
    break;

  case 16: /* local-decl: %empty  */
#line 245 "syntax.y"
      { 
        (yyval.no) = NULL; 
        if (DEBUG_MODE) {printf("local-decl #2\n");}
    }
#line 1818 "syntax.tab.c"
    break;

  case 17: /* stmt-list: stmt-list stmt  */
#line 252 "syntax.y"
                   { 
        (yyval.no) = insert_node(STATEMENT_LIST, (yyvsp[-1].no), (yyvsp[0].no), NULL, NULL);
        if (DEBUG_MODE) {printf("stmt-list #1\n");}
    }
#line 1827 "syntax.tab.c"
    break;

  case 18: /* stmt-list: %empty  */
#line 256 "syntax.y"
      { 
        (yyval.no) = NULL; 
        if (DEBUG_MODE) {printf("stmt-list #2\n");} 
    }
#line 1836 "syntax.tab.c"
    break;

  case 19: /* stmt: expr  */
#line 263 "syntax.y"
         { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("stmt #1\n");} 
    }
#line 1845 "syntax.tab.c"
    break;

  case 20: /* stmt: conditional-stmt  */
#line 267 "syntax.y"
                       { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("stmt #2\n");} 
    }
#line 1854 "syntax.tab.c"
    break;

  case 21: /* stmt: iteration-stmt  */
#line 271 "syntax.y"
                     { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("stmt #3\n");}
    }
#line 1863 "syntax.tab.c"
    break;

  case 22: /* stmt: return-stmt  */
#line 275 "syntax.y"
                  {
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("stmt #4\n");}
    }
#line 1872 "syntax.tab.c"
    break;

  case 23: /* stmt: PRINT '(' QUOTES string QUOTES ')' ';'  */
#line 279 "syntax.y"
                                             { 
        (yyval.no) = insert_node(PRINT_STATEMENT, (yyvsp[-3].no), NULL, "void", (yyvsp[-6].str));
        if (DEBUG_MODE) {printf("stmt #5 %s\n", (yyvsp[-6].str));}
    }
#line 1881 "syntax.tab.c"
    break;

  case 24: /* stmt: PRINT '(' var ')' ';'  */
#line 283 "syntax.y"
                            { 
        (yyval.no) = insert_node(PRINT_STATEMENT, (yyvsp[-2].no), NULL, "void", (yyvsp[-4].str)); 
        if (DEBUG_MODE) {printf("stmt #6 %s\n", (yyvsp[-4].str));} 
    }
#line 1890 "syntax.tab.c"
    break;

  case 25: /* stmt: SCAN '(' var ')' ';'  */
#line 287 "syntax.y"
                           { 
        (yyval.no) = insert_node(SCAN_STATEMENT, (yyvsp[-2].no), NULL, "void", (yyvsp[-4].str)); 
        if (DEBUG_MODE) {printf("stmt #7 %s\n", (yyvsp[-4].str));}
    }
#line 1899 "syntax.tab.c"
    break;

  case 26: /* expr: var ASSIGN expr  */
#line 294 "syntax.y"
                    { 
        (yyval.no) = insert_node(ASSIGN_EXPRESSION, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-1].str));
        define_type((yyval.no));
        if (DEBUG_MODE) {printf("expr #1 %s\n", (yyvsp[-1].str));} 
    }
#line 1909 "syntax.tab.c"
    break;

  case 27: /* expr: simple-expr ';'  */
#line 299 "syntax.y"
                      { 
        (yyval.no) = (yyvsp[-1].no); 
        if (DEBUG_MODE) {printf("expr #2\n");}
    }
#line 1918 "syntax.tab.c"
    break;

  case 28: /* simple-expr: op-expr RELOP op-expr  */
#line 306 "syntax.y"
                          { 
        (yyval.no) = insert_node(RELATIONAL_EXPRESSION, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-1].str));
        define_type((yyval.no));
        check_semantic_error_relop_type((yyval.no));
        if (DEBUG_MODE) {printf("simple-expr #1 %s\n", (yyvsp[-1].str));}
    }
#line 1929 "syntax.tab.c"
    break;

  case 29: /* simple-expr: op-expr  */
#line 312 "syntax.y"
              { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("simple-expr #2\n");}
    }
#line 1938 "syntax.tab.c"
    break;

  case 30: /* conditional-stmt: IF '(' simple-expr ')' comp-stmt  */
#line 319 "syntax.y"
                                     { 
        (yyval.no) = insert_node(CONDITIONAL_STATEMENT, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-4].str));
        if (DEBUG_MODE) {printf("conditional-stmt #1 %s\n", (yyvsp[-4].str));}
    }
#line 1947 "syntax.tab.c"
    break;

  case 31: /* conditional-stmt: IF '(' simple-expr ')' comp-stmt ELSE comp-stmt  */
#line 323 "syntax.y"
                                                      {
        node* aux_node = insert_node(CONDITIONAL_STATEMENT, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-1].str));
        (yyval.no) = insert_node(CONDITIONAL_STATEMENT, (yyvsp[-4].no), aux_node, NULL, (yyvsp[-6].str));
        if (DEBUG_MODE) {printf("conditional-stmt #2 %s\n", (yyvsp[-6].str));}
    }
#line 1957 "syntax.tab.c"
    break;

  case 32: /* iteration-stmt: WHILE '(' simple-expr ')' comp-stmt  */
#line 331 "syntax.y"
                                        { 
        (yyval.no) = insert_node(ITERATION_STATEMENT, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-4].str));
        if (DEBUG_MODE) {printf("iteration-stmt %s\n", (yyvsp[-4].str));}
    }
#line 1966 "syntax.tab.c"
    break;

  case 33: /* return-stmt: RETURN simple-expr ';'  */
#line 338 "syntax.y"
                           { 
        (yyval.no) = insert_node(RETURN_STATEMENT, (yyvsp[-1].no), NULL, NULL, (yyvsp[-2].str)); 
        define_type((yyval.no));
        check_semantic_error_return_type((yyval.no)->type, (yyval.no));
        if (DEBUG_MODE) {printf("return-stmt #1 %s\n", (yyvsp[-2].str));}
    }
#line 1977 "syntax.tab.c"
    break;

  case 34: /* return-stmt: RETURN ';'  */
#line 344 "syntax.y"
                 { 
        (yyval.no) = insert_node(RETURN_STATEMENT, NULL, NULL, "void", (yyvsp[-1].str)); 
        check_semantic_error_return_type((yyval.no)->type, (yyval.no));
        if (DEBUG_MODE) {printf("return-stmt #2 %s\n", (yyvsp[-1].str));}
    }
#line 1987 "syntax.tab.c"
    break;

  case 35: /* var: ID  */
#line 352 "syntax.y"
       { 
        symbol_node* s = find_symbol((yyvsp[0].str));
        char* type = NULL;
        if(s != NULL){
            type = s->type;
        }
        (yyval.no) = insert_node(VARIABLE, NULL, NULL, type, (yyvsp[0].str));
        if (DEBUG_MODE) {printf("var %s\n", (yyvsp[0].str));}
    }
#line 2001 "syntax.tab.c"
    break;

  case 36: /* op-expr: op-expr OP term  */
#line 365 "syntax.y"
                    {
        (yyval.no) = insert_node(ARITHIMETIC_EXPRESSION, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-1].str));
        define_type((yyval.no));
        check_semantic_error_op_type((yyval.no));
        if (DEBUG_MODE) {printf("op-expr #1 %s\n", (yyvsp[-1].str));}
    }
#line 2012 "syntax.tab.c"
    break;

  case 37: /* op-expr: op-expr LOG term  */
#line 371 "syntax.y"
                       { 
        (yyval.no) = insert_node(LOGICAL_EXPRESSION, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-1].str)); 
        define_type((yyval.no));
        if (DEBUG_MODE) {printf("op-expr #2 %s\n", (yyvsp[-1].str));}
    }
#line 2022 "syntax.tab.c"
    break;

  case 38: /* op-expr: term  */
#line 376 "syntax.y"
           { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("op-expr #3\n");}
    }
#line 2031 "syntax.tab.c"
    break;

  case 39: /* term: '(' simple-expr ')'  */
#line 384 "syntax.y"
                        { 
        (yyval.no) = (yyvsp[-1].no); 
        if (DEBUG_MODE) {printf("term #1\n");}
    }
#line 2040 "syntax.tab.c"
    break;

  case 40: /* term: var  */
#line 388 "syntax.y"
          { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("term #2\n");}
    }
#line 2049 "syntax.tab.c"
    break;

  case 41: /* term: call  */
#line 392 "syntax.y"
           { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("term #3\n");}
    }
#line 2058 "syntax.tab.c"
    break;

  case 42: /* term: QUOTES string QUOTES  */
#line 396 "syntax.y"
                           { 
        (yyval.no) = (yyvsp[-1].no); 
        if (DEBUG_MODE) {printf("term #4\n");}
    }
#line 2067 "syntax.tab.c"
    break;

  case 43: /* term: INT  */
#line 400 "syntax.y"
          { 
        (yyval.no) = insert_node(INTEGER, NULL, NULL, "int", (yyvsp[0].str)); 
        if (DEBUG_MODE) {printf("term #5 %s\n", (yyvsp[0].str));}
    }
#line 2076 "syntax.tab.c"
    break;

  case 44: /* term: FLOAT  */
#line 404 "syntax.y"
            { 
        (yyval.no) = insert_node(FLOATNUMBER, NULL, NULL, "float", (yyvsp[0].str)); 
        if (DEBUG_MODE) {printf("term #6 %s\n", (yyvsp[0].str));}
    }
#line 2085 "syntax.tab.c"
    break;

  case 45: /* term: BOOL  */
#line 408 "syntax.y"
           { 
        (yyval.no) = insert_node(BOOLEAN, NULL, NULL, "bool", (yyvsp[0].str)); 
        if (DEBUG_MODE) {printf("term #7 %s\n", (yyvsp[0].str));}
    }
#line 2094 "syntax.tab.c"
    break;

  case 46: /* call: ID '(' args ')'  */
#line 415 "syntax.y"
                    {
        symbol_node* s = find_symbol((yyvsp[-3].str));
        char* type = NULL;
        if(s != NULL){
            type = s->type;
        }
        (yyval.no) = insert_node(FUNCTION_CALL, (yyvsp[-1].no), NULL, type, (yyvsp[-3].str));
        check_semantic_error_type_mismatch_args((yyvsp[-1].no), (yyvsp[-3].str));
        if (DEBUG_MODE) {printf("call #1 %s\n", (yyvsp[-3].str));}
    }
#line 2109 "syntax.tab.c"
    break;

  case 47: /* call: STRCONCAT '(' args ')'  */
#line 425 "syntax.y"
                             { 
        (yyval.no) = insert_node(STRCONCAT_STATEMENT, (yyvsp[-1].no), NULL, "string", (yyvsp[-3].str)); 
        check_semantic_error_type_mismatch_args_native_function((yyvsp[-1].no), (yyvsp[-3].str));
        if (DEBUG_MODE) {printf("call #2 %s\n", (yyvsp[-3].str));}
    }
#line 2119 "syntax.tab.c"
    break;

  case 48: /* call: STRCOPY '(' args ')'  */
#line 430 "syntax.y"
                           { 
        (yyval.no) = insert_node(STRCOPY_STATEMENT, (yyvsp[-1].no), NULL, "string", (yyvsp[-3].str));
        check_semantic_error_type_mismatch_args_native_function((yyvsp[-1].no), (yyvsp[-3].str));
        if (DEBUG_MODE) {printf("call #4 %s\n", (yyvsp[-3].str));}
    }
#line 2129 "syntax.tab.c"
    break;

  case 49: /* call: STRINSERT '(' args ')'  */
#line 435 "syntax.y"
                             {  
        (yyval.no) = insert_node(STRINSERT_STATEMENT, (yyvsp[-1].no), NULL, "string", (yyvsp[-3].str));
        check_semantic_error_type_mismatch_args_native_function((yyvsp[-1].no), (yyvsp[-3].str));
        if (DEBUG_MODE) {printf("call #5 %s\n", (yyvsp[-3].str));}
    }
#line 2139 "syntax.tab.c"
    break;

  case 50: /* call: STRUPPER '(' args ')'  */
#line 440 "syntax.y"
                            {  
        (yyval.no) = insert_node(STRUPPER_STATEMENT, (yyvsp[-1].no), NULL, "string", (yyvsp[-3].str));
        check_semantic_error_type_mismatch_args_native_function((yyvsp[-1].no), (yyvsp[-3].str));
        if (DEBUG_MODE) {printf("call #6 %s\n", (yyvsp[-3].str));}
    }
#line 2149 "syntax.tab.c"
    break;

  case 51: /* call: STRLOWER '(' args ')'  */
#line 445 "syntax.y"
                            {  
        (yyval.no) = insert_node(STRLOWER_STATEMENT, (yyvsp[-1].no), NULL, "string", (yyvsp[-3].str));
        check_semantic_error_type_mismatch_args_native_function((yyvsp[-1].no), (yyvsp[-3].str));
        if (DEBUG_MODE) {printf("call #7 %s\n", (yyvsp[-3].str));}
    }
#line 2159 "syntax.tab.c"
    break;

  case 52: /* args: arg-list  */
#line 453 "syntax.y"
             { 
        (yyval.no) = (yyvsp[0].no);
        if (DEBUG_MODE) {printf("args #1\n");}
    }
#line 2168 "syntax.tab.c"
    break;

  case 53: /* args: %empty  */
#line 457 "syntax.y"
      { 
        (yyval.no) = NULL;
        if (DEBUG_MODE) {printf("args #2\n");}
    }
#line 2177 "syntax.tab.c"
    break;

  case 54: /* arg-list: simple-expr ',' arg-list  */
#line 465 "syntax.y"
                             { 
        (yyval.no) = insert_node(ARGS_LIST, (yyvsp[-2].no), (yyvsp[0].no), NULL, NULL); 
        if (DEBUG_MODE) {printf("args-list #1\n");}
    }
#line 2186 "syntax.tab.c"
    break;

  case 55: /* arg-list: simple-expr  */
#line 469 "syntax.y"
                  { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("args-list #2\n");}
    }
#line 2195 "syntax.tab.c"
    break;

  case 56: /* string: string STR  */
#line 476 "syntax.y"
               { 
        (yyval.no) = insert_node(STRING, (yyvsp[-1].no), NULL, "string", (yyvsp[0].str)); 
        if (DEBUG_MODE) {printf("string #1 %s\n", (yyvsp[0].str));}
    }
#line 2204 "syntax.tab.c"
    break;

  case 57: /* string: %empty  */
#line 480 "syntax.y"
      { 
        (yyval.no) = NULL; 
        if (DEBUG_MODE) {printf("string #2\n");}
    }
#line 2213 "syntax.tab.c"
    break;


#line 2217 "syntax.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 484 "syntax.y"


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


// **********TAC

// Printa tabela de símbolos
void print_symbol_table_TAC(FILE *tac_file) {
    symbol_node *s;
    char *aux = (char *)malloc(
        (1 + 100) * sizeof(char)
    );
    fputs(".table\n", tac_file);
    for(s=symbol_table; s != NULL; s=s->hh.next) {
        if(s->symbol_type != 'F'){
            if((strcmp(s->type, "string") == 0)){
                strcpy(aux, "char");
            }
            else{
                strcpy(aux, s->type);
            }
            strcat(aux, " ");
            strcat(aux, s->name);
            strcat(aux, "@");
            strcat(aux, s->scope_name);
            if((strcmp(s->type, "string") == 0)){
                strcat(aux, " [] ");
            }
            strcat(aux, "\n");
            fputs(aux, tac_file);
        }
    }
    free(aux);
}

void print_code_TAC(node* tree, FILE *tac_file){
    fputs(".code\n", tac_file);
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
