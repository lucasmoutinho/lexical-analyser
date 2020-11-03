/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 5 "syntax.y" /* yacc.c:339  */

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
    char* nome;         // Nome da nó
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
node* insert_node(int node_class, node* left, node* right, char* type, char* nome);
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
symbol_node* find_symbol(char* name);
void define_type(node* no);


#line 161 "syntax.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    BOOL = 260,
    STR = 261,
    TYPE = 262,
    ID = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    RETURN = 267,
    PRINT = 268,
    SCAN = 269,
    STRUPPER = 270,
    STRLOWER = 271,
    STRCONCAT = 272,
    STRCOPY = 273,
    STRINSERT = 274,
    QUOTES = 275,
    ASSIGN = 276,
    OP = 277,
    RELOP = 278,
    LOG = 279
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 100 "syntax.y" /* yacc.c:355  */

    char* str;
    struct node* no;

#line 231 "syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 262 "syntax.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   133

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  119

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
static const yytype_uint16 yyrline[] =
{
       0,   123,   123,   129,   133,   137,   141,   148,   156,   156,
     168,   173,   178,   185,   192,   197,   204,   208,   215,   219,
     223,   227,   231,   235,   239,   246,   251,   258,   263,   267,
     274,   278,   286,   293,   298,   306,   318,   323,   330,   335,
     342,   346,   350,   354,   358,   362,   369,   378,   382,   386,
     390,   394,   401,   405,   412,   416,   423,   427
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "BOOL", "STR", "TYPE",
  "ID", "IF", "ELSE", "WHILE", "RETURN", "PRINT", "SCAN", "STRUPPER",
  "STRLOWER", "STRCONCAT", "STRCOPY", "STRINSERT", "QUOTES", "ASSIGN",
  "OP", "RELOP", "LOG", "';'", "'('", "')'", "','", "'{'", "'}'",
  "$accept", "prog", "decl-list", "var-decl", "func", "$@1", "params",
  "comp-stmt", "local-decl", "stmt-list", "stmt", "expr", "simple-expr",
  "conditional-stmt", "iteration-stmt", "return-stmt", "var", "op-expr",
  "op-log", "term", "call", "args", "arg-list", "string", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    59,    40,    41,    44,   123,
     125
};
# endif

#define YYPACT_NINF -96

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-96)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -1,    -5,    44,    -1,   -96,   -96,   -13,   -96,   -96,   -96,
     -96,    24,    45,    43,   -17,   -96,    30,    53,   -96,   -96,
      54,    61,   -96,    63,    10,    36,   -96,   -96,   -96,    46,
      47,    49,    38,    50,    57,    60,    69,    76,    77,    78,
     -96,    62,   -96,   -96,   -96,    80,   -96,   -96,   -96,    48,
      12,    82,   -96,   -96,   -96,    62,    62,    62,   -96,    83,
     -96,    29,    79,    62,    62,    62,    62,    62,    -4,    84,
     -96,    62,    81,    81,    81,   -96,    85,    86,    88,    89,
     -96,   -96,   -96,    90,    91,    92,    93,    94,    95,    96,
     -96,   -96,   -96,   -96,   -96,    87,   -96,   -96,    62,    30,
      30,    25,    99,   100,   -96,   -96,   -96,   -96,   -96,   -96,
     103,   -96,   101,   -96,   -96,    30,   102,   -96,   -96
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     4,     6,     8,     1,     3,     5,
       7,     0,    12,     0,     0,    11,     0,     0,    15,     9,
       0,    17,    10,     0,     0,     0,    44,    45,    39,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,     0,    13,    16,    18,     0,    19,    20,    21,    41,
      28,    29,    37,    42,    14,    53,     0,     0,    34,     0,
      41,     0,     0,    53,    53,    53,    53,    53,     0,     0,
      26,     0,     0,     0,     0,    55,     0,    52,     0,     0,
      33,    35,    57,     0,     0,     0,     0,     0,     0,     0,
      56,    43,    40,    25,    36,    27,    38,    46,     0,     0,
       0,     0,     0,     0,    50,    51,    47,    48,    49,    54,
      30,    32,     0,    23,    24,     0,     0,    31,    22
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -96,   -96,   -96,   107,   123,   -96,   -96,   -95,   -96,   -96,
     -96,    58,   -24,   -96,   -96,   -96,   -23,    59,   -96,   -65,
     -96,    27,   -96,    51
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    11,    14,    19,    21,    24,
      43,    44,    75,    46,    47,    48,    60,    50,    51,    52,
      53,    76,    77,    68
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      45,    49,    90,     6,   110,   111,     1,    94,    59,    96,
      16,    17,    10,    26,    27,    28,    91,    69,    29,    30,
     117,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    90,    78,    79,    72,    73,    41,    81,    83,    84,
      42,    26,    27,    28,     7,   112,    29,    45,    49,    82,
      12,    15,    13,    35,    36,    37,    38,    39,    40,    18,
      20,    54,    22,    58,    41,    26,    27,    28,    23,    71,
      29,    25,    55,    56,   109,    57,    61,    35,    36,    37,
      38,    39,    40,    62,    26,    27,    63,    81,    41,    29,
      85,    86,    87,    88,    89,    64,    35,    36,    37,    38,
      39,    40,    65,    66,    67,    70,    74,    41,    80,    72,
       8,    92,    97,   115,    98,    99,   100,   102,   103,   104,
     105,   106,   107,   108,   113,   114,     9,   118,   116,    93,
       0,     0,    95,   101
};

static const yytype_int8 yycheck[] =
{
      24,    24,     6,     8,    99,   100,     7,    72,    32,    74,
      27,    28,    25,     3,     4,     5,    20,    41,     8,     9,
     115,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,     6,    56,    57,    22,    23,    26,     8,    61,    62,
      30,     3,     4,     5,     0,    20,     8,    71,    71,    20,
      26,     8,     7,    15,    16,    17,    18,    19,    20,    29,
       7,    25,     8,    25,    26,     3,     4,     5,     7,    21,
       8,     8,    26,    26,    98,    26,    26,    15,    16,    17,
      18,    19,    20,    26,     3,     4,    26,     8,    26,     8,
      63,    64,    65,    66,    67,    26,    15,    16,    17,    18,
      19,    20,    26,    26,    26,    25,    24,    26,    25,    22,
       3,    27,    27,    10,    28,    27,    27,    27,    27,    27,
      27,    27,    27,    27,    25,    25,     3,    25,    27,    71,
      -1,    -1,    73,    82
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    32,    33,    34,    35,     8,     0,    34,    35,
      25,    36,    26,     7,    37,     8,    27,    28,    29,    38,
       7,    39,     8,     7,    40,     8,     3,     4,     5,     8,
       9,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    26,    30,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    25,    26,    26,    26,    25,    43,
      47,    26,    26,    26,    26,    26,    26,    26,    54,    43,
      25,    21,    22,    23,    24,    43,    52,    53,    43,    43,
      25,     8,    20,    47,    47,    52,    52,    52,    52,    52,
       6,    20,    27,    42,    50,    48,    50,    27,    28,    27,
      27,    54,    27,    27,    27,    27,    27,    27,    27,    43,
      38,    38,    20,    25,    25,    10,    27,    38,    25
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    33,    33,    34,    36,    35,
      37,    37,    37,    38,    39,    39,    40,    40,    41,    41,
      41,    41,    41,    41,    41,    42,    42,    43,    43,    43,
      44,    44,    45,    46,    46,    47,    48,    48,    49,    49,
      50,    50,    50,    50,    50,    50,    51,    51,    51,    51,
      51,    51,    52,    52,    53,    53,    54,    54
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     3,     0,     7,
       4,     2,     0,     4,     4,     0,     2,     0,     1,     1,
       1,     1,     7,     5,     5,     3,     2,     3,     1,     1,
       5,     7,     5,     3,     2,     1,     3,     1,     3,     1,
       3,     1,     1,     3,     1,     1,     4,     4,     4,     4,
       4,     4,     1,     0,     3,     1,     2,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
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
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 123 "syntax.y" /* yacc.c:1646  */
    { 
        parser_tree = (yyvsp[0].no);
        if (DEBUG_MODE) {printf("prog\n");}
    }
#line 1514 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 129 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(DECLARATION_LIST, (yyvsp[-1].no), (yyvsp[0].no), NULL, NULL);
        if (DEBUG_MODE) {printf("decl-list #1\n");} 
    }
#line 1523 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 133 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[0].no);
        if (DEBUG_MODE) {printf("decl-list #2\n");}
    }
#line 1532 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 137 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(DECLARATION_LIST, (yyvsp[-1].no), (yyvsp[0].no), NULL, NULL);
        if (DEBUG_MODE) {printf("decl-list #3\n");} 
    }
#line 1541 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 141 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[0].no);
        if (DEBUG_MODE) {printf("decl-list #4\n");}
    }
#line 1550 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 148 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(VARIABLE_DECLARATION, NULL, NULL, (yyvsp[-2].str), (yyvsp[-1].str));
        add_symbol((yyvsp[-1].str), (yyvsp[-2].str), 'V');
        if (DEBUG_MODE) {printf("var-decl %s %s\n", (yyvsp[-2].str), (yyvsp[-1].str));}
    }
#line 1560 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 156 "syntax.y" /* yacc.c:1646  */
    { 
        add_symbol((yyvsp[0].str), (yyvsp[-1].str), 'F');
        push_stack((yyvsp[0].str), (yyvsp[-1].str));
    }
#line 1569 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 160 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(FUNCTION, (yyvsp[-2].no), (yyvsp[0].no), (yyvsp[-6].str), (yyvsp[-5].str));
        pop_stack();
        if (DEBUG_MODE) {printf("func %s %s\n", (yyvsp[-6].str), (yyvsp[-5].str));}
    }
#line 1579 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 168 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(PARAMETER, (yyvsp[-3].no), NULL, (yyvsp[-1].str), (yyvsp[0].str));
        add_symbol((yyvsp[0].str), (yyvsp[-1].str), 'P');
        if (DEBUG_MODE) {printf("params #1 %s %s\n", (yyvsp[-1].str), (yyvsp[0].str));}
    }
#line 1589 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 173 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(PARAMETER, NULL, NULL, (yyvsp[-1].str), (yyvsp[0].str));
        add_symbol((yyvsp[0].str), (yyvsp[-1].str), 'P');
        if (DEBUG_MODE) {printf("params #2 %s %s\n", (yyvsp[-1].str), (yyvsp[0].str));}
    }
#line 1599 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 178 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = NULL;
        if (DEBUG_MODE) {printf("params #3\n");}
    }
#line 1608 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 185 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(COMPOUND_STATEMENT, (yyvsp[-2].no), (yyvsp[-1].no), NULL, NULL);
        if (DEBUG_MODE) {printf("comp-stmt\n");}
    }
#line 1617 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 192 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(VARIABLE_DECLARATION, (yyvsp[-3].no), NULL, (yyvsp[-2].str), (yyvsp[-1].str));
        add_symbol((yyvsp[-1].str), (yyvsp[-2].str), 'V');
        if (DEBUG_MODE) {printf("local-decl #1 %s %s\n", (yyvsp[-2].str), (yyvsp[-1].str));}
    }
#line 1627 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 197 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = NULL; 
        if (DEBUG_MODE) {printf("local-decl #2\n");}
    }
#line 1636 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 204 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(STATEMENT_LIST, (yyvsp[-1].no), (yyvsp[0].no), NULL, NULL);
        if (DEBUG_MODE) {printf("stmt-list #1\n");}
    }
#line 1645 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 208 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = NULL; 
        if (DEBUG_MODE) {printf("stmt-list #2\n");} 
    }
#line 1654 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 215 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("stmt #1\n");} 
    }
#line 1663 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 219 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("stmt #2\n");} 
    }
#line 1672 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 223 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("stmt #3\n");}
    }
#line 1681 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 227 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("stmt #4\n");}
    }
#line 1690 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 231 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(PRINT_STATEMENT, (yyvsp[-3].no), NULL, NULL, (yyvsp[-6].str));
        if (DEBUG_MODE) {printf("stmt #4 %s\n", (yyvsp[-6].str));}
    }
#line 1699 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 235 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(PRINT_STATEMENT, (yyvsp[-2].no), NULL, NULL, (yyvsp[-4].str)); 
        if (DEBUG_MODE) {printf("stmt #5 %s\n", (yyvsp[-4].str));} 
    }
#line 1708 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 239 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(SCAN_STATEMENT, (yyvsp[-2].no), NULL, NULL, (yyvsp[-4].str)); 
        if (DEBUG_MODE) {printf("stmt #6 %s\n", (yyvsp[-4].str));}
    }
#line 1717 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 246 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(ASSIGN_EXPRESSION, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-1].str));
        define_type((yyval.no));
        if (DEBUG_MODE) {printf("expr #1 %s\n", (yyvsp[-1].str));} 
    }
#line 1727 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 251 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[-1].no); 
        if (DEBUG_MODE) {printf("expr #2\n");}
    }
#line 1736 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 258 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(RELATIONAL_EXPRESSION, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-1].str));
        define_type((yyval.no));
        if (DEBUG_MODE) {printf("simple-expr #1 %s\n", (yyvsp[-1].str));}
    }
#line 1746 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 263 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("simple-expr #2\n");}
    }
#line 1755 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 267 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("simple-expr #3\n");}
    }
#line 1764 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 274 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(CONDITIONAL_STATEMENT, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-4].str));
        if (DEBUG_MODE) {printf("conditional-stmt #1 %s\n", (yyvsp[-4].str));}
    }
#line 1773 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 278 "syntax.y" /* yacc.c:1646  */
    {
        node* aux_node = insert_node(CONDITIONAL_STATEMENT, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-1].str));
        (yyval.no) = insert_node(CONDITIONAL_STATEMENT, (yyvsp[-4].no), aux_node, NULL, (yyvsp[-6].str));
        if (DEBUG_MODE) {printf("conditional-stmt #2 %s\n", (yyvsp[-6].str));}
    }
#line 1783 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 286 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(ITERATION_STATEMENT, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-4].str));
        if (DEBUG_MODE) {printf("iteration-stmt %s\n", (yyvsp[-4].str));}
    }
#line 1792 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 293 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(RETURN_STATEMENT, NULL, (yyvsp[-1].no), NULL, (yyvsp[-2].str)); 
        define_type((yyval.no));
        if (DEBUG_MODE) {printf("return-stmt #1 %s\n", (yyvsp[-2].str));}
    }
#line 1802 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 298 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(RETURN_STATEMENT, NULL, NULL, NULL, (yyvsp[-1].str)); 
        define_type((yyval.no));
        if (DEBUG_MODE) {printf("return-stmt #2 %s\n", (yyvsp[-1].str));}
    }
#line 1812 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 306 "syntax.y" /* yacc.c:1646  */
    { 
        symbol_node* s = find_symbol((yyvsp[0].str));
        char* type = NULL;
        if(s != NULL){
            type = s->type;
        }
        (yyval.no) = insert_node(VARIABLE, NULL, NULL, type, (yyvsp[0].str));
        if (DEBUG_MODE) {printf("var %s\n", (yyvsp[0].str));}
    }
#line 1826 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 318 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.no) = insert_node(ARITHIMETIC_EXPRESSION, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-1].str));
        define_type((yyval.no));
        if (DEBUG_MODE) {printf("op-expr #1 %s\n", (yyvsp[-1].str));}
    }
#line 1836 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 323 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("op-expr #2\n");}
    }
#line 1845 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 330 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(LOGICAL_EXPRESSION, (yyvsp[-2].no), (yyvsp[0].no), NULL, (yyvsp[-1].str)); 
        define_type((yyval.no));
        if (DEBUG_MODE) {printf("op-log #1 %s\n", (yyvsp[-1].str));}
    }
#line 1855 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 335 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(BOOLEAN, NULL, NULL, "bool", (yyvsp[0].str)); 
        if (DEBUG_MODE) {printf("op-log #2 %s\n", (yyvsp[0].str));}
    }
#line 1864 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 342 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[-1].no); 
        if (DEBUG_MODE) {printf("term #1\n");}
    }
#line 1873 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 346 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("term #2\n");}
    }
#line 1882 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 350 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("term #3\n");}
    }
#line 1891 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 354 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[-1].no); 
        if (DEBUG_MODE) {printf("term #4\n");}
    }
#line 1900 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 358 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(INTEGER, NULL, NULL, "int", (yyvsp[0].str)); 
        if (DEBUG_MODE) {printf("term #5 %s\n", (yyvsp[0].str));}
    }
#line 1909 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 362 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(FLOATNUMBER, NULL, NULL, "float", (yyvsp[0].str)); 
        if (DEBUG_MODE) {printf("term #6 %s\n", (yyvsp[0].str));}
    }
#line 1918 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 369 "syntax.y" /* yacc.c:1646  */
    {
        symbol_node* s = find_symbol((yyvsp[-3].str));
        char* type = NULL;
        if(s != NULL){
            type = s->type;
        }
        (yyval.no) = insert_node(FUNCTION_CALL, (yyvsp[-1].no), NULL, type, (yyvsp[-3].str));
        if (DEBUG_MODE) {printf("call #1 %s\n", (yyvsp[-3].str));}
    }
#line 1932 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 378 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(FUNCTION_CALL, (yyvsp[-1].no), NULL, "string", (yyvsp[-3].str)); 
        if (DEBUG_MODE) {printf("call #2 %s\n", (yyvsp[-3].str));}
    }
#line 1941 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 382 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(FUNCTION_CALL, (yyvsp[-1].no), NULL, "string", (yyvsp[-3].str));
        if (DEBUG_MODE) {printf("call #4 %s\n", (yyvsp[-3].str));}
    }
#line 1950 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 386 "syntax.y" /* yacc.c:1646  */
    {  
        (yyval.no) = insert_node(FUNCTION_CALL, (yyvsp[-1].no), NULL, "string", (yyvsp[-3].str));
        if (DEBUG_MODE) {printf("call #5 %s\n", (yyvsp[-3].str));}
    }
#line 1959 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 390 "syntax.y" /* yacc.c:1646  */
    {  
        (yyval.no) = insert_node(FUNCTION_CALL, (yyvsp[-1].no), NULL, "string", (yyvsp[-3].str));
        if (DEBUG_MODE) {printf("call #6 %s\n", (yyvsp[-3].str));}
    }
#line 1968 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 394 "syntax.y" /* yacc.c:1646  */
    {  
        (yyval.no) = insert_node(FUNCTION_CALL, (yyvsp[-1].no), NULL, "string", (yyvsp[-3].str));
        if (DEBUG_MODE) {printf("call #7 %s\n", (yyvsp[-3].str));}
    }
#line 1977 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 401 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[0].no);
        if (DEBUG_MODE) {printf("args #1\n");}
    }
#line 1986 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 405 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = NULL;
        if (DEBUG_MODE) {printf("args #2\n");}
    }
#line 1995 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 412 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(ARGS_LIST, (yyvsp[-2].no), (yyvsp[0].no), NULL, NULL); 
        if (DEBUG_MODE) {printf("args-list #1\n");}
    }
#line 2004 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 416 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = (yyvsp[0].no); 
        if (DEBUG_MODE) {printf("args-list #2\n");}
    }
#line 2013 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 423 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = insert_node(STRING, (yyvsp[-1].no), NULL, "string", (yyvsp[0].str)); 
        if (DEBUG_MODE) {printf("string #1 %s\n", (yyvsp[0].str));}
    }
#line 2022 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 427 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.no) = NULL; 
        if (DEBUG_MODE) {printf("string #2\n");}
    }
#line 2031 "syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2035 "syntax.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

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
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 431 "syntax.y" /* yacc.c:1906  */


// Insere Nó
node* insert_node(int node_class, node* left, node* right, char* type, char* nome){
    node* aux_node = (node*)calloc(1, sizeof(node));

    aux_node->node_class = node_class;
    aux_node->left = left;
    aux_node->right = right;
    aux_node->type = type;
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
void semantic_error_type_mismatch(char* type_left, char* name_left, char* type_right, char* name_right){
    char *error = (char *)malloc(
        (strlen(name_left) + strlen(type_left) + strlen(name_right) + strlen(type_right) + 1 + 55) * sizeof(char)
    ); // +1 for the null-terminator and 55 for semantic error message
    sprintf(error, "semantic error, type mismatch between %s(%s) and %s(%s)", type_left, name_left, type_right, name_right);
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
        }
        else{ // type mismatch -- no implicit conversion
            semantic_error_type_mismatch(type_left, no->left->nome, type_right, no->right->nome);
        }
    }
    no->type = type_left;
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
