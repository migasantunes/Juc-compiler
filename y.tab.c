/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CLASS = 258,
     PUBLIC = 259,
     STATIC = 260,
     INT = 261,
     BOOL = 262,
     DOUBLE = 263,
     VOID = 264,
     STRING = 265,
     LBRACE = 266,
     RBRACE = 267,
     LPAR = 268,
     RPAR = 269,
     LSQ = 270,
     RSQ = 271,
     COMMA = 272,
     SEMICOLON = 273,
     ASSIGN = 274,
     PLUS = 275,
     MINUS = 276,
     STAR = 277,
     DIV = 278,
     MOD = 279,
     AND = 280,
     OR = 281,
     NOT = 282,
     XOR = 283,
     LSHIFT = 284,
     RSHIFT = 285,
     EQ = 286,
     NE = 287,
     GE = 288,
     LE = 289,
     GT = 290,
     LT = 291,
     IF = 292,
     ELSE = 293,
     WHILE = 294,
     RETURN = 295,
     PRINT = 296,
     PARSEINT = 297,
     DOTLENGTH = 298,
     ARROW = 299,
     RESERVED = 300,
     IDENTIFIER = 301,
     NATURAL = 302,
     DECIMAL = 303,
     STRLIT = 304,
     BOOLLIT = 305,
     LOWER_THAN_ELSE = 306,
     UNARY_MINUS = 307,
     UNARY_PLUS = 308
   };
#endif
/* Tokens.  */
#define CLASS 258
#define PUBLIC 259
#define STATIC 260
#define INT 261
#define BOOL 262
#define DOUBLE 263
#define VOID 264
#define STRING 265
#define LBRACE 266
#define RBRACE 267
#define LPAR 268
#define RPAR 269
#define LSQ 270
#define RSQ 271
#define COMMA 272
#define SEMICOLON 273
#define ASSIGN 274
#define PLUS 275
#define MINUS 276
#define STAR 277
#define DIV 278
#define MOD 279
#define AND 280
#define OR 281
#define NOT 282
#define XOR 283
#define LSHIFT 284
#define RSHIFT 285
#define EQ 286
#define NE 287
#define GE 288
#define LE 289
#define GT 290
#define LT 291
#define IF 292
#define ELSE 293
#define WHILE 294
#define RETURN 295
#define PRINT 296
#define PARSEINT 297
#define DOTLENGTH 298
#define ARROW 299
#define RESERVED 300
#define IDENTIFIER 301
#define NATURAL 302
#define DECIMAL 303
#define STRLIT 304
#define BOOLLIT 305
#define LOWER_THAN_ELSE 306
#define UNARY_MINUS 307
#define UNARY_PLUS 308




/* Copy the first part of user declarations.  */
#line 1 "jucompiler.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

int yylex(void);
void yyerror(char *s);

extern int token_line;
extern int token_col;
extern char *current_error_yytext;
extern bool emit_tokens;
extern bool lexical_error_found;

bool syntax_error_found = false;
bool semantic_error_found = false;

#include "ast.h"
#include "semantics.h"
#include "codegen.h"



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 27 "jucompiler.y"
{
    char *str;
    struct node *node; 
}
/* Line 193 of yacc.c.  */
#line 233 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 258 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   249

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNRULES -- Number of states.  */
#define YYNSTATES  181

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    10,    13,    16,    19,    24,    31,
      34,    35,    39,    41,    43,    45,    50,    59,    65,    70,
      79,    85,    88,    93,    97,    98,   101,   104,   109,   110,
     113,   116,   120,   126,   134,   140,   143,   147,   150,   155,
     158,   160,   166,   172,   175,   179,   181,   185,   187,   191,
     193,   197,   199,   203,   207,   209,   213,   217,   221,   225,
     227,   231,   235,   237,   241,   245,   247,   251,   255,   259,
     261,   264,   267,   270,   272,   274,   276,   279,   281,   283,
     285,   287,   291,   295,   299,   304,   309,   311,   315,   323
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,     3,    46,    11,    56,    12,    -1,    -1,
      56,    57,    -1,    56,    58,    -1,    56,    18,    -1,     4,
       5,    61,    63,    -1,     4,     5,    60,    46,    59,    18,
      -1,     1,    18,    -1,    -1,    59,    17,    46,    -1,     7,
      -1,     6,    -1,     8,    -1,    60,    46,    13,    14,    -1,
      60,    46,    13,    10,    15,    16,    46,    14,    -1,    60,
      46,    13,    62,    14,    -1,     9,    46,    13,    14,    -1,
       9,    46,    13,    10,    15,    16,    46,    14,    -1,     9,
      46,    13,    62,    14,    -1,    60,    46,    -1,    62,    17,
      60,    46,    -1,    11,    64,    12,    -1,    -1,    64,    67,
      -1,    64,    65,    -1,    60,    46,    59,    18,    -1,    -1,
      66,    67,    -1,    66,    65,    -1,    11,    66,    12,    -1,
      37,    13,    68,    14,    67,    -1,    37,    13,    68,    14,
      67,    38,    67,    -1,    39,    13,    68,    14,    67,    -1,
      40,    18,    -1,    40,    68,    18,    -1,    79,    18,    -1,
      46,    19,    68,    18,    -1,    81,    18,    -1,    18,    -1,
      41,    13,    68,    14,    18,    -1,    41,    13,    49,    14,
      18,    -1,     1,    18,    -1,    46,    19,    68,    -1,    69,
      -1,    69,    26,    70,    -1,    70,    -1,    70,    25,    71,
      -1,    71,    -1,    71,    28,    72,    -1,    72,    -1,    72,
      31,    73,    -1,    72,    32,    73,    -1,    73,    -1,    73,
      33,    74,    -1,    73,    35,    74,    -1,    73,    34,    74,
      -1,    73,    36,    74,    -1,    74,    -1,    74,    29,    75,
      -1,    74,    30,    75,    -1,    75,    -1,    75,    20,    76,
      -1,    75,    21,    76,    -1,    76,    -1,    76,    22,    77,
      -1,    76,    23,    77,    -1,    76,    24,    77,    -1,    77,
      -1,    21,    77,    -1,    20,    77,    -1,    27,    77,    -1,
      78,    -1,    79,    -1,    81,    -1,    46,    43,    -1,    46,
      -1,    47,    -1,    48,    -1,    50,    -1,    13,    68,    14,
      -1,    13,     1,    14,    -1,    46,    13,    14,    -1,    46,
      13,    80,    14,    -1,    46,    13,     1,    14,    -1,    68,
      -1,    80,    17,    68,    -1,    42,    13,    46,    15,    68,
      16,    14,    -1,    42,    13,     1,    14,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    63,    63,    72,    73,    78,    83,    86,    94,   115,
     118,   119,   127,   128,   129,   132,   139,   151,   160,   167,
     179,   190,   196,   206,   213,   214,   219,   226,   249,   250,
     255,   262,   271,   278,   285,   291,   292,   293,   294,   296,
     297,   298,   299,   300,   303,   305,   308,   309,   312,   313,
     316,   317,   320,   321,   322,   325,   326,   327,   328,   329,
     332,   333,   334,   337,   338,   339,   342,   343,   344,   345,
     348,   349,   350,   351,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   365,   367,   369,   372,   373,   376,   378
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "PUBLIC", "STATIC", "INT",
  "BOOL", "DOUBLE", "VOID", "STRING", "LBRACE", "RBRACE", "LPAR", "RPAR",
  "LSQ", "RSQ", "COMMA", "SEMICOLON", "ASSIGN", "PLUS", "MINUS", "STAR",
  "DIV", "MOD", "AND", "OR", "NOT", "XOR", "LSHIFT", "RSHIFT", "EQ", "NE",
  "GE", "LE", "GT", "LT", "IF", "ELSE", "WHILE", "RETURN", "PRINT",
  "PARSEINT", "DOTLENGTH", "ARROW", "RESERVED", "IDENTIFIER", "NATURAL",
  "DECIMAL", "STRLIT", "BOOLLIT", "LOWER_THAN_ELSE", "UNARY_MINUS",
  "UNARY_PLUS", "$accept", "Program", "DeclList", "MethodDecl",
  "FieldDecl", "AuxIdList", "Type", "MethodHeader", "FormalParams",
  "MethodBody", "MethodBodyDecls", "VarDecl", "StatementList", "Statement",
  "Expr", "OrExpr", "AndExpr", "XorExpr", "EqExpr", "RelExpr", "ShiftExpr",
  "AddExpr", "MulExpr", "UnaryExpr", "Primary", "MethodInvocation",
  "ExprList", "ParseArgs", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    56,    56,    56,    57,    58,    58,
      59,    59,    60,    60,    60,    61,    61,    61,    61,    61,
      61,    62,    62,    63,    64,    64,    64,    65,    66,    66,
      66,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    68,    68,    69,    69,    70,    70,
      71,    71,    72,    72,    72,    73,    73,    73,    73,    73,
      74,    74,    74,    75,    75,    75,    76,    76,    76,    76,
      77,    77,    77,    77,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    79,    79,    79,    80,    80,    81,    81
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     0,     2,     2,     2,     4,     6,     2,
       0,     3,     1,     1,     1,     4,     8,     5,     4,     8,
       5,     2,     4,     3,     0,     2,     2,     4,     0,     2,
       2,     3,     5,     7,     5,     2,     3,     2,     4,     2,
       1,     5,     5,     2,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     2,     1,     1,     1,     2,     1,     1,     1,
       1,     3,     3,     3,     4,     4,     1,     3,     7,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     0,     0,     2,
       6,     4,     5,     9,     0,    13,    12,    14,     0,     0,
       0,     0,    10,    24,     7,     0,     0,     0,     0,     0,
      18,     0,     0,     0,    15,     0,     0,     8,     0,    28,
      23,    40,     0,     0,     0,     0,     0,     0,     0,    26,
      25,     0,     0,     0,    21,    20,     0,     0,    17,    11,
      43,     0,     0,     0,     0,    35,     0,     0,     0,    77,
      78,    79,    80,     0,    45,    47,    49,    51,    54,    59,
      62,    65,    69,    73,    74,    75,     0,     0,     0,     0,
      10,    37,    39,     0,     0,     0,    31,    30,    29,     0,
       0,     0,     0,    77,    71,    70,    72,     0,    76,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    83,    86,     0,     0,     0,     0,    22,     0,     0,
       0,    82,    81,    44,    46,    48,    50,    52,    53,    55,
      57,    56,    58,    60,    61,    63,    64,    66,    67,    68,
       0,     0,    89,     0,    85,    84,     0,    38,    27,    19,
      16,    32,    34,    42,    41,     0,    87,     0,     0,    33,
      88
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,    11,    12,    27,    31,    20,    32,    24,
      28,    49,    61,    50,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,   133,    85
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -61
static const yytype_int16 yypact[] =
{
       8,   -30,    34,    27,   -61,   -61,    42,    52,    71,   -61,
     -61,   -61,   -61,   -61,   135,   -61,   -61,   -61,    62,    85,
      61,    97,   125,   -61,   -61,    67,    91,     6,    84,   133,
     -61,    88,    54,   142,   -61,    86,    94,   -61,   132,   -61,
     -61,   -61,   146,   153,    -6,   159,   168,     9,   136,   -61,
     -61,   165,   167,   178,   -61,   -61,    81,   181,   -61,   -61,
     -61,   121,   166,   166,    36,   -61,   175,   175,   175,    26,
     -61,   -61,   -61,   180,   174,   176,   182,    30,   120,    64,
      95,    96,   -61,   -61,   -61,   -61,   157,    12,     5,   166,
     -61,   -61,   -61,   163,   169,   172,   -61,   -61,   -61,   197,
     205,   206,   210,     7,   -61,   -61,   -61,   166,   -61,   -61,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   212,   213,   214,   215,
     217,   -61,   -61,    92,   211,   119,   218,   -61,   219,   134,
     134,   -61,   -61,   -61,   176,   182,    30,   120,   120,    64,
      64,    64,    64,    95,    95,    96,    96,   -61,   -61,   -61,
     216,   220,   -61,   166,   -61,   -61,   166,   -61,   -61,   -61,
     -61,   198,   -61,   -61,   -61,   221,   -61,   134,   225,   -61,
     -61
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -61,   -61,   -61,   -61,   -61,   145,     3,   -61,   222,   -61,
     -61,   179,   -61,   -60,   -59,   -61,   131,   138,   130,    33,
      74,    45,    47,   -58,   -61,   -28,   -61,   -26
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      51,    98,    52,    99,   100,   102,   130,    64,   104,   105,
     106,     1,    65,   128,    66,    67,     3,    19,    64,   131,
      88,    68,    88,    36,    37,    66,    67,   127,    89,   132,
     134,    48,    68,    51,     4,    52,    46,   101,     5,    88,
      69,    70,    71,     7,    72,   107,     8,    46,   143,    64,
     108,    69,    70,    71,     9,    72,    66,    67,   129,    94,
      10,   113,   114,    68,    48,   157,   158,   159,    55,   108,
      13,    56,    23,    15,    16,    17,    14,    29,    46,   171,
     172,    30,    69,    70,    71,    38,    72,    15,    16,    17,
      15,    16,    17,   119,   120,    39,    40,    15,    16,    17,
      58,    33,    41,    56,   175,    34,   165,   176,    21,   166,
      25,    51,    51,    52,    52,   121,   122,   179,   123,   124,
     125,    42,    38,    43,    44,    45,    46,    15,    16,    17,
      47,    22,    39,    96,    54,    38,    36,   168,    26,    41,
      59,    15,    16,    17,    18,    39,   147,   148,    53,    51,
      60,    52,    41,   115,   116,   117,   118,    57,    42,    62,
      43,    44,    45,    46,   153,   154,    63,    47,   155,   156,
      64,    42,    86,    43,    44,    45,    46,    66,    67,    64,
      47,    87,    90,    91,    68,    92,    66,    67,    64,   149,
     150,   151,   152,    68,    93,    66,    67,    95,   109,    46,
     110,   111,    68,    69,    70,    71,   126,    72,    46,   136,
     112,   139,    69,    70,    71,   137,    72,    46,   138,   140,
     141,   103,    70,    71,   142,    72,   160,   161,   162,   167,
     163,   164,   169,   170,   173,   135,   177,   178,   174,   180,
      97,   144,   146,     0,     0,     0,     0,     0,    35,   145
};

static const yytype_int16 yycheck[] =
{
      28,    61,    28,    62,    63,    64,     1,    13,    66,    67,
      68,     3,    18,     1,    20,    21,    46,    14,    13,    14,
      13,    27,    13,    17,    18,    20,    21,    86,    19,    88,
      89,    28,    27,    61,     0,    61,    42,     1,    11,    13,
      46,    47,    48,     1,    50,    19,     4,    42,   107,    13,
      43,    46,    47,    48,    12,    50,    20,    21,    46,    56,
      18,    31,    32,    27,    61,   123,   124,   125,    14,    43,
      18,    17,    11,     6,     7,     8,     5,    10,    42,   139,
     140,    14,    46,    47,    48,     1,    50,     6,     7,     8,
       6,     7,     8,    29,    30,    11,    12,     6,     7,     8,
      14,    10,    18,    17,   163,    14,    14,   166,    46,    17,
      13,   139,   140,   139,   140,    20,    21,   177,    22,    23,
      24,    37,     1,    39,    40,    41,    42,     6,     7,     8,
      46,    46,    11,    12,    46,     1,    17,    18,    13,    18,
      46,     6,     7,     8,     9,    11,   113,   114,    15,   177,
      18,   177,    18,    33,    34,    35,    36,    15,    37,    13,
      39,    40,    41,    42,   119,   120,    13,    46,   121,   122,
      13,    37,    13,    39,    40,    41,    42,    20,    21,    13,
      46,    13,    46,    18,    27,    18,    20,    21,    13,   115,
     116,   117,   118,    27,    16,    20,    21,    16,    18,    42,
      26,    25,    27,    46,    47,    48,    49,    50,    42,    46,
      28,    14,    46,    47,    48,    46,    50,    42,    46,    14,
      14,    46,    47,    48,    14,    50,    14,    14,    14,    18,
      15,    14,    14,    14,    18,    90,    38,    16,    18,    14,
      61,   110,   112,    -1,    -1,    -1,    -1,    -1,    26,   111
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    55,    46,     0,    11,    56,     1,     4,    12,
      18,    57,    58,    18,     5,     6,     7,     8,     9,    60,
      61,    46,    46,    11,    63,    13,    13,    59,    64,    10,
      14,    60,    62,    10,    14,    62,    17,    18,     1,    11,
      12,    18,    37,    39,    40,    41,    42,    46,    60,    65,
      67,    79,    81,    15,    46,    14,    17,    15,    14,    46,
      18,    66,    13,    13,    13,    18,    20,    21,    27,    46,
      47,    48,    50,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    81,    13,    13,    13,    19,
      46,    18,    18,    16,    60,    16,    12,    65,    67,    68,
      68,     1,    68,    46,    77,    77,    77,    19,    43,    18,
      26,    25,    28,    31,    32,    33,    34,    35,    36,    29,
      30,    20,    21,    22,    23,    24,    49,    68,     1,    46,
       1,    14,    68,    80,    68,    59,    46,    46,    46,    14,
      14,    14,    14,    68,    70,    71,    72,    73,    73,    74,
      74,    74,    74,    75,    75,    76,    76,    77,    77,    77,
      14,    14,    14,    15,    14,    14,    17,    18,    18,    14,
      14,    67,    67,    18,    18,    68,    68,    38,    16,    67,
      14
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
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
     `$$ = $1'.

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
#line 64 "jucompiler.y"
    {
           (yyval.node) = new_node_at("Program", NULL, (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column);
           add_child((yyval.node), new_node_at("Identifier", (yyvsp[(2) - (5)].str), (yylsp[(2) - (5)]).first_line, (yylsp[(2) - (5)]).first_column));
           if ((yyvsp[(4) - (5)].node) != NULL) { add_child((yyval.node), (yyvsp[(4) - (5)].node)); }
           program_root = (yyval.node); 
       }
    break;

  case 3:
#line 72 "jucompiler.y"
    { (yyval.node) = NULL; }
    break;

  case 4:
#line 74 "jucompiler.y"
    {
            if ((yyvsp[(1) - (2)].node) == NULL) { (yyval.node) = (yyvsp[(2) - (2)].node); }
            else { add_sibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); (yyval.node) = (yyvsp[(1) - (2)].node); }
        }
    break;

  case 5:
#line 79 "jucompiler.y"
    {
            if ((yyvsp[(1) - (2)].node) == NULL) { (yyval.node) = (yyvsp[(2) - (2)].node); }
            else { add_sibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); (yyval.node) = (yyvsp[(1) - (2)].node); }
        }
    break;

  case 6:
#line 83 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); }
    break;

  case 7:
#line 87 "jucompiler.y"
    {
              (yyval.node) = new_node("MethodDecl", NULL);
              add_child((yyval.node), (yyvsp[(3) - (4)].node));
              add_child((yyval.node), (yyvsp[(4) - (4)].node));
          }
    break;

  case 8:
#line 95 "jucompiler.y"
    {
             (yyval.node) = new_node("FieldDecl", NULL);
             add_child((yyval.node), (yyvsp[(3) - (6)].node));
             add_child((yyval.node), new_node_at("Identifier", (yyvsp[(4) - (6)].str), (yylsp[(4) - (6)]).first_line, (yylsp[(4) - (6)]).first_column));
             
             Node *aux = (yyvsp[(5) - (6)].node);
             Node *last_decl = (yyval.node);
             while (aux != NULL) {
                 Node *next_aux = aux->sibling;
                 aux->sibling = NULL; 
                 
                 Node *new_decl = new_node("FieldDecl", NULL);
                 add_child(new_decl, new_node((yyvsp[(3) - (6)].node)->type, NULL)); 
                 add_child(new_decl, aux);
                 
                 add_sibling(last_decl, new_decl);
                 last_decl = new_decl;
                 aux = next_aux;
             }
         }
    break;

  case 9:
#line 115 "jucompiler.y"
    { (yyval.node) = NULL; }
    break;

  case 10:
#line 118 "jucompiler.y"
    { (yyval.node) = NULL; }
    break;

  case 11:
#line 120 "jucompiler.y"
    {
             Node *id_node = new_node_at("Identifier", (yyvsp[(3) - (3)].str), (yylsp[(3) - (3)]).first_line, (yylsp[(3) - (3)]).first_column);
             if ((yyvsp[(1) - (3)].node) == NULL) { (yyval.node) = id_node; }
             else { add_sibling((yyvsp[(1) - (3)].node), id_node); (yyval.node) = (yyvsp[(1) - (3)].node); }
         }
    break;

  case 12:
#line 127 "jucompiler.y"
    { (yyval.node) = new_node_at("Bool", NULL, (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column); }
    break;

  case 13:
#line 128 "jucompiler.y"
    { (yyval.node) = new_node_at("Int", NULL, (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column); }
    break;

  case 14:
#line 129 "jucompiler.y"
    { (yyval.node) = new_node_at("Double", NULL, (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column); }
    break;

  case 15:
#line 133 "jucompiler.y"
    {
                (yyval.node) = new_node("MethodHeader", NULL);
                add_child((yyval.node), (yyvsp[(1) - (4)].node));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[(2) - (4)].str), (yylsp[(2) - (4)]).first_line, (yylsp[(2) - (4)]).first_column));
                add_child((yyval.node), new_node("MethodParams", NULL));
            }
    break;

  case 16:
#line 140 "jucompiler.y"
    {
                (yyval.node) = new_node("MethodHeader", NULL);
                add_child((yyval.node), (yyvsp[(1) - (8)].node));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[(2) - (8)].str), (yylsp[(2) - (8)]).first_line, (yylsp[(2) - (8)]).first_column));
                Node *params = new_node("MethodParams", NULL);
                Node *param = new_node("ParamDecl", NULL);
                add_child(param, new_node_at("StringArray", NULL, (yylsp[(4) - (8)]).first_line, (yylsp[(4) - (8)]).first_column));
                add_child(param, new_node_at("Identifier", (yyvsp[(7) - (8)].str), (yylsp[(7) - (8)]).first_line, (yylsp[(7) - (8)]).first_column));
                add_child(params, param);
                add_child((yyval.node), params);
            }
    break;

  case 17:
#line 152 "jucompiler.y"
    {
                (yyval.node) = new_node("MethodHeader", NULL);
                add_child((yyval.node), (yyvsp[(1) - (5)].node));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[(2) - (5)].str), (yylsp[(2) - (5)]).first_line, (yylsp[(2) - (5)]).first_column));
                Node *params = new_node("MethodParams", NULL);
                add_child(params, (yyvsp[(4) - (5)].node));
                add_child((yyval.node), params);
            }
    break;

  case 18:
#line 161 "jucompiler.y"
    {
                (yyval.node) = new_node("MethodHeader", NULL);
                add_child((yyval.node), new_node_at("Void", NULL, (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[(2) - (4)].str), (yylsp[(2) - (4)]).first_line, (yylsp[(2) - (4)]).first_column));
                add_child((yyval.node), new_node("MethodParams", NULL));
            }
    break;

  case 19:
#line 168 "jucompiler.y"
    {
                (yyval.node) = new_node("MethodHeader", NULL);
                add_child((yyval.node), new_node_at("Void", NULL, (yylsp[(1) - (8)]).first_line, (yylsp[(1) - (8)]).first_column));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[(2) - (8)].str), (yylsp[(2) - (8)]).first_line, (yylsp[(2) - (8)]).first_column));
                Node *params = new_node("MethodParams", NULL);
                Node *param = new_node("ParamDecl", NULL);
                add_child(param, new_node_at("StringArray", NULL, (yylsp[(4) - (8)]).first_line, (yylsp[(4) - (8)]).first_column));
                add_child(param, new_node_at("Identifier", (yyvsp[(7) - (8)].str), (yylsp[(7) - (8)]).first_line, (yylsp[(7) - (8)]).first_column));
                add_child(params, param);
                add_child((yyval.node), params);
            }
    break;

  case 20:
#line 180 "jucompiler.y"
    {
                (yyval.node) = new_node("MethodHeader", NULL);
                add_child((yyval.node), new_node_at("Void", NULL, (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[(2) - (5)].str), (yylsp[(2) - (5)]).first_line, (yylsp[(2) - (5)]).first_column));
                Node *params = new_node("MethodParams", NULL);
                add_child(params, (yyvsp[(4) - (5)].node));
                add_child((yyval.node), params);
            }
    break;

  case 21:
#line 191 "jucompiler.y"
    {
                (yyval.node) = new_node("ParamDecl", NULL);
                add_child((yyval.node), (yyvsp[(1) - (2)].node));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[(2) - (2)].str), (yylsp[(2) - (2)]).first_line, (yylsp[(2) - (2)]).first_column));
            }
    break;

  case 22:
#line 197 "jucompiler.y"
    {
                Node *new_param = new_node("ParamDecl", NULL);
                add_child(new_param, (yyvsp[(3) - (4)].node));
                add_child(new_param, new_node_at("Identifier", (yyvsp[(4) - (4)].str), (yylsp[(4) - (4)]).first_line, (yylsp[(4) - (4)]).first_column));
                add_sibling((yyvsp[(1) - (4)].node), new_param);
                (yyval.node) = (yyvsp[(1) - (4)].node);
            }
    break;

  case 23:
#line 207 "jucompiler.y"
    { 
              (yyval.node) = new_node("MethodBody", NULL); 
              add_child((yyval.node), (yyvsp[(2) - (3)].node));
          }
    break;

  case 24:
#line 213 "jucompiler.y"
    { (yyval.node) = NULL; }
    break;

  case 25:
#line 215 "jucompiler.y"
    { 
                   if ((yyvsp[(1) - (2)].node) == NULL) { (yyval.node) = (yyvsp[(2) - (2)].node); }
                   else { add_sibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); (yyval.node) = (yyvsp[(1) - (2)].node); }
               }
    break;

  case 26:
#line 220 "jucompiler.y"
    { 
                   if ((yyvsp[(1) - (2)].node) == NULL) { (yyval.node) = (yyvsp[(2) - (2)].node); }
                   else { add_sibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); (yyval.node) = (yyvsp[(1) - (2)].node); }
               }
    break;

  case 27:
#line 227 "jucompiler.y"
    { 
             (yyval.node) = new_node("VarDecl", NULL);
             add_child((yyval.node), (yyvsp[(1) - (4)].node));
         add_child((yyval.node), new_node_at("Identifier", (yyvsp[(2) - (4)].str), (yylsp[(2) - (4)]).first_line, (yylsp[(2) - (4)]).first_column));
             
             Node *aux = (yyvsp[(3) - (4)].node);
             Node *last_decl = (yyval.node);
             while (aux != NULL) {
                 Node *next_aux = aux->sibling;
                 aux->sibling = NULL; 
                 
                 Node *new_decl = new_node("VarDecl", NULL);
                 add_child(new_decl, new_node((yyvsp[(1) - (4)].node)->type, NULL)); 
                 add_child(new_decl, aux);
                 
                 add_sibling(last_decl, new_decl);
                 last_decl = new_decl;
                 aux = next_aux;
             }
       }
    break;

  case 28:
#line 249 "jucompiler.y"
    { (yyval.node) = NULL; }
    break;

  case 29:
#line 251 "jucompiler.y"
    { 
                 if ((yyvsp[(1) - (2)].node) == NULL) { (yyval.node) = (yyvsp[(2) - (2)].node); }
                 else { add_sibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); (yyval.node) = (yyvsp[(1) - (2)].node); }
             }
    break;

  case 30:
#line 256 "jucompiler.y"
    {
                 if ((yyvsp[(1) - (2)].node) == NULL) { (yyval.node) = (yyvsp[(2) - (2)].node); }
                 else { add_sibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); (yyval.node) = (yyvsp[(1) - (2)].node); }
             }
    break;

  case 31:
#line 263 "jucompiler.y"
    { 
             if ((yyvsp[(2) - (3)].node) != NULL && count_siblings((yyvsp[(2) - (3)].node)) > 1) {
                 (yyval.node) = new_node("Block", NULL);
                 add_child((yyval.node), (yyvsp[(2) - (3)].node));
             } else {
                 (yyval.node) = (yyvsp[(2) - (3)].node); 
             }
         }
    break;

  case 32:
#line 272 "jucompiler.y"
    { 
             (yyval.node) = new_node_at("If", NULL, (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column);
             add_child((yyval.node), (yyvsp[(3) - (5)].node));
             add_child((yyval.node), create_block((yyvsp[(5) - (5)].node)));
             add_child((yyval.node), new_node("Block", NULL));
         }
    break;

  case 33:
#line 279 "jucompiler.y"
    { 
             (yyval.node) = new_node_at("If", NULL, (yylsp[(1) - (7)]).first_line, (yylsp[(1) - (7)]).first_column);
             add_child((yyval.node), (yyvsp[(3) - (7)].node));
             add_child((yyval.node), create_block((yyvsp[(5) - (7)].node)));
             add_child((yyval.node), create_block((yyvsp[(7) - (7)].node)));
         }
    break;

  case 34:
#line 286 "jucompiler.y"
    { 
             (yyval.node) = new_node_at("While", NULL, (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column);
             add_child((yyval.node), (yyvsp[(3) - (5)].node));
             add_child((yyval.node), create_block((yyvsp[(5) - (5)].node)));
         }
    break;

  case 35:
#line 291 "jucompiler.y"
    { (yyval.node) = new_node_at("Return", NULL, (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column); }
    break;

  case 36:
#line 292 "jucompiler.y"
    { (yyval.node) = new_node_at("Return", NULL, (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column); add_child((yyval.node), (yyvsp[(2) - (3)].node)); }
    break;

  case 37:
#line 293 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); }
    break;

  case 38:
#line 295 "jucompiler.y"
    { (yyval.node) = new_node_at("Assign", NULL, (yylsp[(2) - (4)]).first_line, (yylsp[(2) - (4)]).first_column); add_child((yyval.node), new_node_at("Identifier", (yyvsp[(1) - (4)].str), (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column)); add_child((yyval.node), (yyvsp[(3) - (4)].node)); }
    break;

  case 39:
#line 296 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); }
    break;

  case 40:
#line 297 "jucompiler.y"
    { (yyval.node) = NULL; }
    break;

  case 41:
#line 298 "jucompiler.y"
    { (yyval.node) = new_node_at("Print", NULL, (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column); add_child((yyval.node), (yyvsp[(3) - (5)].node)); }
    break;

  case 42:
#line 299 "jucompiler.y"
    { (yyval.node) = new_node_at("Print", NULL, (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column); add_child((yyval.node), new_node_at("StrLit", (yyvsp[(3) - (5)].str), (yylsp[(3) - (5)]).first_line, (yylsp[(3) - (5)]).first_column)); }
    break;

  case 43:
#line 300 "jucompiler.y"
    { (yyval.node) = NULL; }
    break;

  case 44:
#line 304 "jucompiler.y"
    { (yyval.node) = new_node_at("Assign", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), new_node_at("Identifier", (yyvsp[(1) - (3)].str), (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 45:
#line 305 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 46:
#line 308 "jucompiler.y"
    { (yyval.node) = new_node_at("Or", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 47:
#line 309 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 48:
#line 312 "jucompiler.y"
    { (yyval.node) = new_node_at("And", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 49:
#line 313 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 50:
#line 316 "jucompiler.y"
    { (yyval.node) = new_node_at("Xor", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 51:
#line 317 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 52:
#line 320 "jucompiler.y"
    { (yyval.node) = new_node_at("Eq", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 53:
#line 321 "jucompiler.y"
    { (yyval.node) = new_node_at("Ne", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 54:
#line 322 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 55:
#line 325 "jucompiler.y"
    { (yyval.node) = new_node_at("Ge", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 56:
#line 326 "jucompiler.y"
    { (yyval.node) = new_node_at("Gt", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 57:
#line 327 "jucompiler.y"
    { (yyval.node) = new_node_at("Le", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 58:
#line 328 "jucompiler.y"
    { (yyval.node) = new_node_at("Lt", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 59:
#line 329 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 60:
#line 332 "jucompiler.y"
    { (yyval.node) = new_node_at("Lshift", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 61:
#line 333 "jucompiler.y"
    { (yyval.node) = new_node_at("Rshift", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 62:
#line 334 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 63:
#line 337 "jucompiler.y"
    { (yyval.node) = new_node_at("Add", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 64:
#line 338 "jucompiler.y"
    { (yyval.node) = new_node_at("Sub", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 65:
#line 339 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 66:
#line 342 "jucompiler.y"
    { (yyval.node) = new_node_at("Mul", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 67:
#line 343 "jucompiler.y"
    { (yyval.node) = new_node_at("Div", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 68:
#line 344 "jucompiler.y"
    { (yyval.node) = new_node_at("Mod", NULL, (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 69:
#line 345 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 70:
#line 348 "jucompiler.y"
    { (yyval.node) = new_node_at("Minus", NULL, (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column); add_child((yyval.node), (yyvsp[(2) - (2)].node)); }
    break;

  case 71:
#line 349 "jucompiler.y"
    { (yyval.node) = new_node_at("Plus", NULL, (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column); add_child((yyval.node), (yyvsp[(2) - (2)].node)); }
    break;

  case 72:
#line 350 "jucompiler.y"
    { (yyval.node) = new_node_at("Not", NULL, (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column); add_child((yyval.node), (yyvsp[(2) - (2)].node)); }
    break;

  case 73:
#line 351 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 74:
#line 354 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 75:
#line 355 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 76:
#line 356 "jucompiler.y"
    { (yyval.node) = new_node_at("Length", NULL, (yylsp[(2) - (2)]).first_line, (yylsp[(2) - (2)]).first_column); add_child((yyval.node), new_node_at("Identifier", (yyvsp[(1) - (2)].str), (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column)); }
    break;

  case 77:
#line 357 "jucompiler.y"
    { (yyval.node) = new_node_at("Identifier", (yyvsp[(1) - (1)].str), (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column); }
    break;

  case 78:
#line 358 "jucompiler.y"
    { (yyval.node) = new_node_at("Natural", (yyvsp[(1) - (1)].str), (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column); }
    break;

  case 79:
#line 359 "jucompiler.y"
    { (yyval.node) = new_node_at("Decimal", (yyvsp[(1) - (1)].str), (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column); }
    break;

  case 80:
#line 360 "jucompiler.y"
    { (yyval.node) = new_node_at("BoolLit", (yyvsp[(1) - (1)].str), (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column); }
    break;

  case 81:
#line 361 "jucompiler.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 82:
#line 362 "jucompiler.y"
    { (yyval.node) = NULL; }
    break;

  case 83:
#line 366 "jucompiler.y"
    { (yyval.node) = new_node_at("Call", NULL, (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column); add_child((yyval.node), new_node_at("Identifier", (yyvsp[(1) - (3)].str), (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column)); }
    break;

  case 84:
#line 368 "jucompiler.y"
    { (yyval.node) = new_node_at("Call", NULL, (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column); add_child((yyval.node), new_node_at("Identifier", (yyvsp[(1) - (4)].str), (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column)); add_child((yyval.node), (yyvsp[(3) - (4)].node)); }
    break;

  case 85:
#line 369 "jucompiler.y"
    { (yyval.node) = NULL; }
    break;

  case 86:
#line 372 "jucompiler.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 87:
#line 373 "jucompiler.y"
    { add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); (yyval.node) = (yyvsp[(1) - (3)].node); }
    break;

  case 88:
#line 377 "jucompiler.y"
    { (yyval.node) = new_node_at("ParseArgs", NULL, (yylsp[(1) - (7)]).first_line, (yylsp[(1) - (7)]).first_column); add_child((yyval.node), new_node_at("Identifier", (yyvsp[(3) - (7)].str), (yylsp[(3) - (7)]).first_line, (yylsp[(3) - (7)]).first_column)); add_child((yyval.node), (yyvsp[(5) - (7)].node)); }
    break;

  case 89:
#line 378 "jucompiler.y"
    { (yyval.node) = NULL; }
    break;


/* Line 1267 of yacc.c.  */
#line 2239 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 381 "jucompiler.y"




void yyerror(char *s) {
    syntax_error_found = true;
    /* Função de erro simples e infalível, igual à que resultou na perfeição! */
    printf("Line %d, col %d: %s: %s\n", token_line, token_col, s, current_error_yytext);
}

int main(int argc, char **argv) {
    bool parse_syntax = true;
    bool print_ast = false;
    bool run_semantic = true;
    bool print_semantic = false;
    bool errors_only_semantic = false;
    bool emit_llvm = false;
    
    if (argc > 1) {
        if (strcmp(argv[1], "-1") == 0 || strcmp(argv[1], "-l") == 0) {
            emit_tokens = true;
            parse_syntax = false;
            run_semantic = false;
        } else if (strcmp(argv[1], "-e1") == 0) {
            emit_tokens = false;
            parse_syntax = false;
            run_semantic = false;
        } else if (strcmp(argv[1], "-e2") == 0) {
            parse_syntax = true;
            run_semantic = false;
        } else if (strcmp(argv[1], "-t") == 0) {
            parse_syntax = true;
            print_ast = true;
            run_semantic = false;
        } else if (strcmp(argv[1], "-s") == 0) {
            parse_syntax = true;
            run_semantic = true;
            print_semantic = true;
        } else if (strcmp(argv[1], "-e3") == 0) {
            parse_syntax = true;
            run_semantic = true;
            errors_only_semantic = true;
        }
    } else {
        emit_llvm = true;
    }
    
    if (parse_syntax) {
        yyparse();
        if (!syntax_error_found && program_root != NULL) {
            if (run_semantic && !(errors_only_semantic && lexical_error_found)) {
                build_symbol_tables(program_root);
                annotate_program(program_root);
                if (print_semantic) {
                    print_symbol_tables();
                    printf("\n");
                    print_tree_annotated(program_root, 0);
                } else if (errors_only_semantic) {
                    /* errors already printed during analysis */
                }
            }
            if (print_ast) {
                print_tree(program_root, 0); 
            }
            if (emit_llvm && run_semantic && !lexical_error_found && !semantic_error_found) {
                codegen_program(program_root, stdout);
            }
        }
        free_symbol_tables();
        free_tree(program_root);
    } else {
        while (yylex() != 0);
    }
    return 0;
}
