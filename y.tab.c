/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
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


#line 97 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CLASS = 258,                   /* CLASS  */
    PUBLIC = 259,                  /* PUBLIC  */
    STATIC = 260,                  /* STATIC  */
    INT = 261,                     /* INT  */
    BOOL = 262,                    /* BOOL  */
    DOUBLE = 263,                  /* DOUBLE  */
    VOID = 264,                    /* VOID  */
    STRING = 265,                  /* STRING  */
    LBRACE = 266,                  /* LBRACE  */
    RBRACE = 267,                  /* RBRACE  */
    LPAR = 268,                    /* LPAR  */
    RPAR = 269,                    /* RPAR  */
    LSQ = 270,                     /* LSQ  */
    RSQ = 271,                     /* RSQ  */
    COMMA = 272,                   /* COMMA  */
    SEMICOLON = 273,               /* SEMICOLON  */
    ASSIGN = 274,                  /* ASSIGN  */
    PLUS = 275,                    /* PLUS  */
    MINUS = 276,                   /* MINUS  */
    STAR = 277,                    /* STAR  */
    DIV = 278,                     /* DIV  */
    MOD = 279,                     /* MOD  */
    AND = 280,                     /* AND  */
    OR = 281,                      /* OR  */
    NOT = 282,                     /* NOT  */
    XOR = 283,                     /* XOR  */
    LSHIFT = 284,                  /* LSHIFT  */
    RSHIFT = 285,                  /* RSHIFT  */
    EQ = 286,                      /* EQ  */
    NE = 287,                      /* NE  */
    GE = 288,                      /* GE  */
    LE = 289,                      /* LE  */
    GT = 290,                      /* GT  */
    LT = 291,                      /* LT  */
    IF = 292,                      /* IF  */
    ELSE = 293,                    /* ELSE  */
    WHILE = 294,                   /* WHILE  */
    RETURN = 295,                  /* RETURN  */
    PRINT = 296,                   /* PRINT  */
    PARSEINT = 297,                /* PARSEINT  */
    DOTLENGTH = 298,               /* DOTLENGTH  */
    ARROW = 299,                   /* ARROW  */
    RESERVED = 300,                /* RESERVED  */
    IDENTIFIER = 301,              /* IDENTIFIER  */
    NATURAL = 302,                 /* NATURAL  */
    DECIMAL = 303,                 /* DECIMAL  */
    STRLIT = 304,                  /* STRLIT  */
    BOOLLIT = 305,                 /* BOOLLIT  */
    LOWER_THAN_ELSE = 306,         /* LOWER_THAN_ELSE  */
    UNARY_PLUS = 307,              /* UNARY_PLUS  */
    UNARY_MINUS = 308              /* UNARY_MINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
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
#define UNARY_PLUS 307
#define UNARY_MINUS 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "jucompiler.y"

    char *str;
    struct node *node; 

#line 261 "y.tab.c"

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


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CLASS = 3,                      /* CLASS  */
  YYSYMBOL_PUBLIC = 4,                     /* PUBLIC  */
  YYSYMBOL_STATIC = 5,                     /* STATIC  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_BOOL = 7,                       /* BOOL  */
  YYSYMBOL_DOUBLE = 8,                     /* DOUBLE  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_STRING = 10,                    /* STRING  */
  YYSYMBOL_LBRACE = 11,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 12,                    /* RBRACE  */
  YYSYMBOL_LPAR = 13,                      /* LPAR  */
  YYSYMBOL_RPAR = 14,                      /* RPAR  */
  YYSYMBOL_LSQ = 15,                       /* LSQ  */
  YYSYMBOL_RSQ = 16,                       /* RSQ  */
  YYSYMBOL_COMMA = 17,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 18,                 /* SEMICOLON  */
  YYSYMBOL_ASSIGN = 19,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 20,                      /* PLUS  */
  YYSYMBOL_MINUS = 21,                     /* MINUS  */
  YYSYMBOL_STAR = 22,                      /* STAR  */
  YYSYMBOL_DIV = 23,                       /* DIV  */
  YYSYMBOL_MOD = 24,                       /* MOD  */
  YYSYMBOL_AND = 25,                       /* AND  */
  YYSYMBOL_OR = 26,                        /* OR  */
  YYSYMBOL_NOT = 27,                       /* NOT  */
  YYSYMBOL_XOR = 28,                       /* XOR  */
  YYSYMBOL_LSHIFT = 29,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 30,                    /* RSHIFT  */
  YYSYMBOL_EQ = 31,                        /* EQ  */
  YYSYMBOL_NE = 32,                        /* NE  */
  YYSYMBOL_GE = 33,                        /* GE  */
  YYSYMBOL_LE = 34,                        /* LE  */
  YYSYMBOL_GT = 35,                        /* GT  */
  YYSYMBOL_LT = 36,                        /* LT  */
  YYSYMBOL_IF = 37,                        /* IF  */
  YYSYMBOL_ELSE = 38,                      /* ELSE  */
  YYSYMBOL_WHILE = 39,                     /* WHILE  */
  YYSYMBOL_RETURN = 40,                    /* RETURN  */
  YYSYMBOL_PRINT = 41,                     /* PRINT  */
  YYSYMBOL_PARSEINT = 42,                  /* PARSEINT  */
  YYSYMBOL_DOTLENGTH = 43,                 /* DOTLENGTH  */
  YYSYMBOL_ARROW = 44,                     /* ARROW  */
  YYSYMBOL_RESERVED = 45,                  /* RESERVED  */
  YYSYMBOL_IDENTIFIER = 46,                /* IDENTIFIER  */
  YYSYMBOL_NATURAL = 47,                   /* NATURAL  */
  YYSYMBOL_DECIMAL = 48,                   /* DECIMAL  */
  YYSYMBOL_STRLIT = 49,                    /* STRLIT  */
  YYSYMBOL_BOOLLIT = 50,                   /* BOOLLIT  */
  YYSYMBOL_LOWER_THAN_ELSE = 51,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_UNARY_PLUS = 52,                /* UNARY_PLUS  */
  YYSYMBOL_UNARY_MINUS = 53,               /* UNARY_MINUS  */
  YYSYMBOL_YYACCEPT = 54,                  /* $accept  */
  YYSYMBOL_Program = 55,                   /* Program  */
  YYSYMBOL_DeclList = 56,                  /* DeclList  */
  YYSYMBOL_MethodDecl = 57,                /* MethodDecl  */
  YYSYMBOL_FieldDecl = 58,                 /* FieldDecl  */
  YYSYMBOL_AuxIdList = 59,                 /* AuxIdList  */
  YYSYMBOL_Type = 60,                      /* Type  */
  YYSYMBOL_MethodHeader = 61,              /* MethodHeader  */
  YYSYMBOL_FormalParams = 62,              /* FormalParams  */
  YYSYMBOL_MethodBody = 63,                /* MethodBody  */
  YYSYMBOL_MethodBodyDecls = 64,           /* MethodBodyDecls  */
  YYSYMBOL_VarDecl = 65,                   /* VarDecl  */
  YYSYMBOL_StatementList = 66,             /* StatementList  */
  YYSYMBOL_Statement = 67,                 /* Statement  */
  YYSYMBOL_Expr = 68,                      /* Expr  */
  YYSYMBOL_OrExpr = 69,                    /* OrExpr  */
  YYSYMBOL_AndExpr = 70,                   /* AndExpr  */
  YYSYMBOL_XorExpr = 71,                   /* XorExpr  */
  YYSYMBOL_EqExpr = 72,                    /* EqExpr  */
  YYSYMBOL_RelExpr = 73,                   /* RelExpr  */
  YYSYMBOL_ShiftExpr = 74,                 /* ShiftExpr  */
  YYSYMBOL_AddExpr = 75,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 76,                   /* MulExpr  */
  YYSYMBOL_UnaryExpr = 77,                 /* UnaryExpr  */
  YYSYMBOL_Primary = 78,                   /* Primary  */
  YYSYMBOL_MethodInvocation = 79,          /* MethodInvocation  */
  YYSYMBOL_ExprList = 80,                  /* ExprList  */
  YYSYMBOL_ParseArgs = 81                  /* ParseArgs  */
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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_uint8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   240

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  180

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   308


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
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    63,    63,    72,    73,    78,    83,    86,    94,   115,
     118,   119,   127,   128,   129,   132,   139,   151,   160,   167,
     179,   190,   196,   206,   213,   214,   219,   226,   249,   250,
     257,   266,   273,   280,   286,   287,   288,   289,   291,   292,
     293,   294,   295,   298,   300,   303,   304,   307,   308,   311,
     312,   315,   316,   317,   320,   321,   322,   323,   324,   327,
     328,   329,   332,   333,   334,   337,   338,   339,   340,   343,
     344,   345,   346,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   360,   362,   364,   367,   368,   371,   373
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CLASS", "PUBLIC",
  "STATIC", "INT", "BOOL", "DOUBLE", "VOID", "STRING", "LBRACE", "RBRACE",
  "LPAR", "RPAR", "LSQ", "RSQ", "COMMA", "SEMICOLON", "ASSIGN", "PLUS",
  "MINUS", "STAR", "DIV", "MOD", "AND", "OR", "NOT", "XOR", "LSHIFT",
  "RSHIFT", "EQ", "NE", "GE", "LE", "GT", "LT", "IF", "ELSE", "WHILE",
  "RETURN", "PRINT", "PARSEINT", "DOTLENGTH", "ARROW", "RESERVED",
  "IDENTIFIER", "NATURAL", "DECIMAL", "STRLIT", "BOOLLIT",
  "LOWER_THAN_ELSE", "UNARY_PLUS", "UNARY_MINUS", "$accept", "Program",
  "DeclList", "MethodDecl", "FieldDecl", "AuxIdList", "Type",
  "MethodHeader", "FormalParams", "MethodBody", "MethodBodyDecls",
  "VarDecl", "StatementList", "Statement", "Expr", "OrExpr", "AndExpr",
  "XorExpr", "EqExpr", "RelExpr", "ShiftExpr", "AddExpr", "MulExpr",
  "UnaryExpr", "Primary", "MethodInvocation", "ExprList", "ParseArgs", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-61)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       3,   -30,    18,    15,   -61,   -61,    76,    10,    41,   -61,
     -61,   -61,   -61,   -61,    66,   -61,   -61,   -61,     8,    24,
      65,    74,    85,   -61,   -61,    94,   118,    78,    44,    90,
     -61,    43,     6,   100,   -61,    22,    45,   -61,    91,   -61,
     -61,   -61,   104,   106,   126,   121,   130,    -2,    99,   -61,
     -61,   144,   157,   161,   -61,   -61,   123,   163,   -61,   -61,
     -61,    81,   167,   167,    21,   -61,   176,   176,   176,     0,
     -61,   -61,   -61,   177,   155,   174,   170,   109,   125,   122,
     134,   147,   -61,   -61,   -61,   -61,   136,    14,    11,   167,
     -61,   -61,   -61,   156,   160,   162,   -61,   -61,   193,   196,
     197,   198,     1,   -61,   -61,   -61,   167,   -61,   -61,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   202,   205,   206,   210,   207,
     -61,   -61,    23,   209,   173,   214,   -61,   215,    96,    96,
     -61,   -61,   -61,   174,   170,   109,   125,   125,   122,   122,
     122,   122,   134,   134,   147,   147,   -61,   -61,   -61,   212,
     213,   -61,   167,   -61,   -61,   167,   -61,   -61,   -61,   -61,
     194,   -61,   -61,   -61,   217,   -61,    96,   220,   -61,   -61
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     0,     0,     2,
       6,     4,     5,     9,     0,    13,    12,    14,     0,     0,
       0,     0,    10,    24,     7,     0,     0,     0,     0,     0,
      18,     0,     0,     0,    15,     0,     0,     8,     0,    28,
      23,    39,     0,     0,     0,     0,     0,     0,     0,    26,
      25,     0,     0,     0,    21,    20,     0,     0,    17,    11,
      42,     0,     0,     0,     0,    34,     0,     0,     0,    76,
      77,    78,    79,     0,    44,    46,    48,    50,    53,    58,
      61,    64,    68,    72,    73,    74,     0,     0,     0,     0,
      10,    36,    38,     0,     0,     0,    30,    29,     0,     0,
       0,     0,    76,    70,    69,    71,     0,    75,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,    85,     0,     0,     0,     0,    22,     0,     0,     0,
      81,    80,    43,    45,    47,    49,    51,    52,    54,    56,
      55,    57,    59,    60,    62,    63,    65,    66,    67,     0,
       0,    88,     0,    84,    83,     0,    37,    27,    19,    16,
      31,    33,    41,    40,     0,    86,     0,     0,    32,    87
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -61,   -61,   -61,   -61,   -61,   145,    -7,   -61,   211,   -61,
     -61,   -61,   -61,   -60,   -59,   -61,   127,   128,   129,    80,
      50,    82,    84,   -58,   -61,   -28,   -61,   -26
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,    11,    12,    27,    31,    20,    32,    24,
      28,    49,    61,    50,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,   132,    85
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      51,    97,    52,    98,    99,   101,     1,    19,   103,   104,
     105,    88,   129,    88,    88,   127,     3,    89,     4,   106,
      55,    48,   100,    56,    64,   130,     5,   126,    13,   131,
     133,    66,    67,    51,    64,    52,    58,   164,    68,    56,
     165,    66,    67,   107,   107,    38,    14,   142,    68,    94,
      15,    16,    17,    46,    21,    39,    40,    69,    70,    71,
     128,    72,    41,    46,   156,   157,   158,    69,    70,    71,
      22,    72,    15,    16,    17,    18,    23,     7,   170,   171,
       8,    42,    38,    43,    44,    45,    46,    25,     9,    54,
      47,    59,    39,    96,    10,    36,    37,    38,    26,    41,
      15,    16,    17,   174,    29,    53,   175,    39,    30,    60,
      51,    51,    52,    52,    41,    57,   178,    62,    42,    63,
      43,    44,    45,    46,    15,    16,    17,    47,    33,    15,
      16,    17,    34,    42,    86,    43,    44,    45,    46,    64,
     112,   113,    47,    87,    65,    90,    66,    67,    51,    64,
      52,   118,   119,    68,   120,   121,    66,    67,   114,   115,
     116,   117,    91,    68,   148,   149,   150,   151,    46,   122,
     123,   124,    69,    70,    71,    92,    72,    93,    46,    95,
      64,   109,    69,    70,    71,   125,    72,    66,    67,    64,
      36,   167,   146,   147,    68,   108,    66,    67,   111,   110,
     152,   153,   135,    68,   154,   155,   136,   138,   137,    46,
     139,   140,   141,    69,    70,    71,   159,    72,    46,   160,
     161,   163,   102,    70,    71,   162,    72,   166,   168,   169,
     172,   173,   176,   177,   179,   134,   143,    35,   144,     0,
     145
};

static const yytype_int16 yycheck[] =
{
      28,    61,    28,    62,    63,    64,     3,    14,    66,    67,
      68,    13,     1,    13,    13,     1,    46,    19,     0,    19,
      14,    28,     1,    17,    13,    14,    11,    86,    18,    88,
      89,    20,    21,    61,    13,    61,    14,    14,    27,    17,
      17,    20,    21,    43,    43,     1,     5,   106,    27,    56,
       6,     7,     8,    42,    46,    11,    12,    46,    47,    48,
      46,    50,    18,    42,   122,   123,   124,    46,    47,    48,
      46,    50,     6,     7,     8,     9,    11,     1,   138,   139,
       4,    37,     1,    39,    40,    41,    42,    13,    12,    46,
      46,    46,    11,    12,    18,    17,    18,     1,    13,    18,
       6,     7,     8,   162,    10,    15,   165,    11,    14,    18,
     138,   139,   138,   139,    18,    15,   176,    13,    37,    13,
      39,    40,    41,    42,     6,     7,     8,    46,    10,     6,
       7,     8,    14,    37,    13,    39,    40,    41,    42,    13,
      31,    32,    46,    13,    18,    46,    20,    21,   176,    13,
     176,    29,    30,    27,    20,    21,    20,    21,    33,    34,
      35,    36,    18,    27,   114,   115,   116,   117,    42,    22,
      23,    24,    46,    47,    48,    18,    50,    16,    42,    16,
      13,    26,    46,    47,    48,    49,    50,    20,    21,    13,
      17,    18,   112,   113,    27,    18,    20,    21,    28,    25,
     118,   119,    46,    27,   120,   121,    46,    14,    46,    42,
      14,    14,    14,    46,    47,    48,    14,    50,    42,    14,
      14,    14,    46,    47,    48,    15,    50,    18,    14,    14,
      18,    18,    38,    16,    14,    90,   109,    26,   110,    -1,
     111
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
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
      46,    18,    18,    16,    60,    16,    12,    67,    68,    68,
       1,    68,    46,    77,    77,    77,    19,    43,    18,    26,
      25,    28,    31,    32,    33,    34,    35,    36,    29,    30,
      20,    21,    22,    23,    24,    49,    68,     1,    46,     1,
      14,    68,    80,    68,    59,    46,    46,    46,    14,    14,
      14,    14,    68,    70,    71,    72,    73,    73,    74,    74,
      74,    74,    75,    75,    76,    76,    77,    77,    77,    14,
      14,    14,    15,    14,    14,    17,    18,    18,    14,    14,
      67,    67,    18,    18,    68,    68,    38,    16,    67,    14
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    56,    56,    56,    56,    57,    58,    58,
      59,    59,    60,    60,    60,    61,    61,    61,    61,    61,
      61,    62,    62,    63,    64,    64,    64,    65,    66,    66,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    68,    68,    69,    69,    70,    70,    71,
      71,    72,    72,    72,    73,    73,    73,    73,    73,    74,
      74,    74,    75,    75,    75,    76,    76,    76,    76,    77,
      77,    77,    77,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    79,    79,    79,    80,    80,    81,    81
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     0,     2,     2,     2,     4,     6,     2,
       0,     3,     1,     1,     1,     4,     8,     5,     4,     8,
       5,     2,     4,     3,     0,     2,     2,     4,     0,     2,
       3,     5,     7,     5,     2,     3,     2,     4,     2,     1,
       5,     5,     2,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       3,     3,     3,     4,     4,     1,     3,     7,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


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
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
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

  YYLOCATION_PRINT (yyo, yylocationp);
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
  case 2: /* Program: CLASS IDENTIFIER LBRACE DeclList RBRACE  */
#line 64 "jucompiler.y"
       {
           (yyval.node) = new_node_at("Program", NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column);
           add_child((yyval.node), new_node_at("Identifier", (yyvsp[-3].str), (yylsp[-3]).first_line, (yylsp[-3]).first_column));
           if ((yyvsp[-1].node) != NULL) { add_child((yyval.node), (yyvsp[-1].node)); }
           program_root = (yyval.node); 
       }
#line 1585 "y.tab.c"
    break;

  case 3: /* DeclList: %empty  */
#line 72 "jucompiler.y"
                      { (yyval.node) = NULL; }
#line 1591 "y.tab.c"
    break;

  case 4: /* DeclList: DeclList MethodDecl  */
#line 74 "jucompiler.y"
        {
            if ((yyvsp[-1].node) == NULL) { (yyval.node) = (yyvsp[0].node); }
            else { add_sibling((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
        }
#line 1600 "y.tab.c"
    break;

  case 5: /* DeclList: DeclList FieldDecl  */
#line 79 "jucompiler.y"
        {
            if ((yyvsp[-1].node) == NULL) { (yyval.node) = (yyvsp[0].node); }
            else { add_sibling((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
        }
#line 1609 "y.tab.c"
    break;

  case 6: /* DeclList: DeclList SEMICOLON  */
#line 83 "jucompiler.y"
                             { (yyval.node) = (yyvsp[-1].node); }
#line 1615 "y.tab.c"
    break;

  case 7: /* MethodDecl: PUBLIC STATIC MethodHeader MethodBody  */
#line 87 "jucompiler.y"
          {
              (yyval.node) = new_node("MethodDecl", NULL);
              add_child((yyval.node), (yyvsp[-1].node));
              add_child((yyval.node), (yyvsp[0].node));
          }
#line 1625 "y.tab.c"
    break;

  case 8: /* FieldDecl: PUBLIC STATIC Type IDENTIFIER AuxIdList SEMICOLON  */
#line 95 "jucompiler.y"
         {
             (yyval.node) = new_node("FieldDecl", NULL);
             add_child((yyval.node), (yyvsp[-3].node));
             add_child((yyval.node), new_node_at("Identifier", (yyvsp[-2].str), (yylsp[-2]).first_line, (yylsp[-2]).first_column));
             
             Node *aux = (yyvsp[-1].node);
             Node *last_decl = (yyval.node);
             while (aux != NULL) {
                 Node *next_aux = aux->sibling;
                 aux->sibling = NULL; 
                 
                 Node *new_decl = new_node("FieldDecl", NULL);
                 add_child(new_decl, new_node((yyvsp[-3].node)->type, NULL)); 
                 add_child(new_decl, aux);
                 
                 add_sibling(last_decl, new_decl);
                 last_decl = new_decl;
                 aux = next_aux;
             }
         }
#line 1650 "y.tab.c"
    break;

  case 9: /* FieldDecl: error SEMICOLON  */
#line 115 "jucompiler.y"
                           { (yyval.node) = NULL; }
#line 1656 "y.tab.c"
    break;

  case 10: /* AuxIdList: %empty  */
#line 118 "jucompiler.y"
                       { (yyval.node) = NULL; }
#line 1662 "y.tab.c"
    break;

  case 11: /* AuxIdList: AuxIdList COMMA IDENTIFIER  */
#line 120 "jucompiler.y"
         {
             Node *id_node = new_node_at("Identifier", (yyvsp[0].str), (yylsp[0]).first_line, (yylsp[0]).first_column);
             if ((yyvsp[-2].node) == NULL) { (yyval.node) = id_node; }
             else { add_sibling((yyvsp[-2].node), id_node); (yyval.node) = (yyvsp[-2].node); }
         }
#line 1672 "y.tab.c"
    break;

  case 12: /* Type: BOOL  */
#line 127 "jucompiler.y"
             { (yyval.node) = new_node_at("Bool", NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 1678 "y.tab.c"
    break;

  case 13: /* Type: INT  */
#line 128 "jucompiler.y"
             { (yyval.node) = new_node_at("Int", NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 1684 "y.tab.c"
    break;

  case 14: /* Type: DOUBLE  */
#line 129 "jucompiler.y"
             { (yyval.node) = new_node_at("Double", NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 1690 "y.tab.c"
    break;

  case 15: /* MethodHeader: Type IDENTIFIER LPAR RPAR  */
#line 133 "jucompiler.y"
            {
                (yyval.node) = new_node("MethodHeader", NULL);
                add_child((yyval.node), (yyvsp[-3].node));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[-2].str), (yylsp[-2]).first_line, (yylsp[-2]).first_column));
                add_child((yyval.node), new_node("MethodParams", NULL));
            }
#line 1701 "y.tab.c"
    break;

  case 16: /* MethodHeader: Type IDENTIFIER LPAR STRING LSQ RSQ IDENTIFIER RPAR  */
#line 140 "jucompiler.y"
            {
                (yyval.node) = new_node("MethodHeader", NULL);
                add_child((yyval.node), (yyvsp[-7].node));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[-6].str), (yylsp[-6]).first_line, (yylsp[-6]).first_column));
                Node *params = new_node("MethodParams", NULL);
                Node *param = new_node("ParamDecl", NULL);
                add_child(param, new_node_at("StringArray", NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column));
                add_child(param, new_node_at("Identifier", (yyvsp[-1].str), (yylsp[-1]).first_line, (yylsp[-1]).first_column));
                add_child(params, param);
                add_child((yyval.node), params);
            }
#line 1717 "y.tab.c"
    break;

  case 17: /* MethodHeader: Type IDENTIFIER LPAR FormalParams RPAR  */
#line 152 "jucompiler.y"
            {
                (yyval.node) = new_node("MethodHeader", NULL);
                add_child((yyval.node), (yyvsp[-4].node));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[-3].str), (yylsp[-3]).first_line, (yylsp[-3]).first_column));
                Node *params = new_node("MethodParams", NULL);
                add_child(params, (yyvsp[-1].node));
                add_child((yyval.node), params);
            }
#line 1730 "y.tab.c"
    break;

  case 18: /* MethodHeader: VOID IDENTIFIER LPAR RPAR  */
#line 161 "jucompiler.y"
            {
                (yyval.node) = new_node("MethodHeader", NULL);
                add_child((yyval.node), new_node_at("Void", NULL, (yylsp[-3]).first_line, (yylsp[-3]).first_column));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[-2].str), (yylsp[-2]).first_line, (yylsp[-2]).first_column));
                add_child((yyval.node), new_node("MethodParams", NULL));
            }
#line 1741 "y.tab.c"
    break;

  case 19: /* MethodHeader: VOID IDENTIFIER LPAR STRING LSQ RSQ IDENTIFIER RPAR  */
#line 168 "jucompiler.y"
            {
                (yyval.node) = new_node("MethodHeader", NULL);
                add_child((yyval.node), new_node_at("Void", NULL, (yylsp[-7]).first_line, (yylsp[-7]).first_column));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[-6].str), (yylsp[-6]).first_line, (yylsp[-6]).first_column));
                Node *params = new_node("MethodParams", NULL);
                Node *param = new_node("ParamDecl", NULL);
                add_child(param, new_node_at("StringArray", NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column));
                add_child(param, new_node_at("Identifier", (yyvsp[-1].str), (yylsp[-1]).first_line, (yylsp[-1]).first_column));
                add_child(params, param);
                add_child((yyval.node), params);
            }
#line 1757 "y.tab.c"
    break;

  case 20: /* MethodHeader: VOID IDENTIFIER LPAR FormalParams RPAR  */
#line 180 "jucompiler.y"
            {
                (yyval.node) = new_node("MethodHeader", NULL);
                add_child((yyval.node), new_node_at("Void", NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[-3].str), (yylsp[-3]).first_line, (yylsp[-3]).first_column));
                Node *params = new_node("MethodParams", NULL);
                add_child(params, (yyvsp[-1].node));
                add_child((yyval.node), params);
            }
#line 1770 "y.tab.c"
    break;

  case 21: /* FormalParams: Type IDENTIFIER  */
#line 191 "jucompiler.y"
            {
                (yyval.node) = new_node("ParamDecl", NULL);
                add_child((yyval.node), (yyvsp[-1].node));
                add_child((yyval.node), new_node_at("Identifier", (yyvsp[0].str), (yylsp[0]).first_line, (yylsp[0]).first_column));
            }
#line 1780 "y.tab.c"
    break;

  case 22: /* FormalParams: FormalParams COMMA Type IDENTIFIER  */
#line 197 "jucompiler.y"
            {
                Node *new_param = new_node("ParamDecl", NULL);
                add_child(new_param, (yyvsp[-1].node));
                add_child(new_param, new_node_at("Identifier", (yyvsp[0].str), (yylsp[0]).first_line, (yylsp[0]).first_column));
                add_sibling((yyvsp[-3].node), new_param);
                (yyval.node) = (yyvsp[-3].node);
            }
#line 1792 "y.tab.c"
    break;

  case 23: /* MethodBody: LBRACE MethodBodyDecls RBRACE  */
#line 207 "jucompiler.y"
          { 
              (yyval.node) = new_node("MethodBody", NULL); 
              add_child((yyval.node), (yyvsp[-1].node));
          }
#line 1801 "y.tab.c"
    break;

  case 24: /* MethodBodyDecls: %empty  */
#line 213 "jucompiler.y"
                             { (yyval.node) = NULL; }
#line 1807 "y.tab.c"
    break;

  case 25: /* MethodBodyDecls: MethodBodyDecls Statement  */
#line 215 "jucompiler.y"
               { 
                   if ((yyvsp[-1].node) == NULL) { (yyval.node) = (yyvsp[0].node); }
                   else { add_sibling((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
               }
#line 1816 "y.tab.c"
    break;

  case 26: /* MethodBodyDecls: MethodBodyDecls VarDecl  */
#line 220 "jucompiler.y"
               { 
                   if ((yyvsp[-1].node) == NULL) { (yyval.node) = (yyvsp[0].node); }
                   else { add_sibling((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
               }
#line 1825 "y.tab.c"
    break;

  case 27: /* VarDecl: Type IDENTIFIER AuxIdList SEMICOLON  */
#line 227 "jucompiler.y"
       { 
             (yyval.node) = new_node("VarDecl", NULL);
             add_child((yyval.node), (yyvsp[-3].node));
         add_child((yyval.node), new_node_at("Identifier", (yyvsp[-2].str), (yylsp[-2]).first_line, (yylsp[-2]).first_column));
             
             Node *aux = (yyvsp[-1].node);
             Node *last_decl = (yyval.node);
             while (aux != NULL) {
                 Node *next_aux = aux->sibling;
                 aux->sibling = NULL; 
                 
                 Node *new_decl = new_node("VarDecl", NULL);
                 add_child(new_decl, new_node((yyvsp[-3].node)->type, NULL)); 
                 add_child(new_decl, aux);
                 
                 add_sibling(last_decl, new_decl);
                 last_decl = new_decl;
                 aux = next_aux;
             }
       }
#line 1850 "y.tab.c"
    break;

  case 28: /* StatementList: %empty  */
#line 249 "jucompiler.y"
                           { (yyval.node) = NULL; }
#line 1856 "y.tab.c"
    break;

  case 29: /* StatementList: StatementList Statement  */
#line 251 "jucompiler.y"
             { 
                 if ((yyvsp[-1].node) == NULL) { (yyval.node) = (yyvsp[0].node); }
                 else { add_sibling((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
             }
#line 1865 "y.tab.c"
    break;

  case 30: /* Statement: LBRACE StatementList RBRACE  */
#line 258 "jucompiler.y"
         { 
             if ((yyvsp[-1].node) != NULL && count_siblings((yyvsp[-1].node)) > 1) {
                 (yyval.node) = new_node("Block", NULL);
                 add_child((yyval.node), (yyvsp[-1].node));
             } else {
                 (yyval.node) = (yyvsp[-1].node); 
             }
         }
#line 1878 "y.tab.c"
    break;

  case 31: /* Statement: IF LPAR Expr RPAR Statement  */
#line 267 "jucompiler.y"
         { 
             (yyval.node) = new_node_at("If", NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column);
             add_child((yyval.node), (yyvsp[-2].node));
             add_child((yyval.node), create_block((yyvsp[0].node)));
             add_child((yyval.node), new_node("Block", NULL));
         }
#line 1889 "y.tab.c"
    break;

  case 32: /* Statement: IF LPAR Expr RPAR Statement ELSE Statement  */
#line 274 "jucompiler.y"
         { 
             (yyval.node) = new_node_at("If", NULL, (yylsp[-6]).first_line, (yylsp[-6]).first_column);
             add_child((yyval.node), (yyvsp[-4].node));
             add_child((yyval.node), create_block((yyvsp[-2].node)));
             add_child((yyval.node), create_block((yyvsp[0].node)));
         }
#line 1900 "y.tab.c"
    break;

  case 33: /* Statement: WHILE LPAR Expr RPAR Statement  */
#line 281 "jucompiler.y"
         { 
             (yyval.node) = new_node_at("While", NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column);
             add_child((yyval.node), (yyvsp[-2].node));
             add_child((yyval.node), create_block((yyvsp[0].node)));
         }
#line 1910 "y.tab.c"
    break;

  case 34: /* Statement: RETURN SEMICOLON  */
#line 286 "jucompiler.y"
                            { (yyval.node) = new_node_at("Return", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1916 "y.tab.c"
    break;

  case 35: /* Statement: RETURN Expr SEMICOLON  */
#line 287 "jucompiler.y"
                                 { (yyval.node) = new_node_at("Return", NULL, (yylsp[-2]).first_line, (yylsp[-2]).first_column); add_child((yyval.node), (yyvsp[-1].node)); }
#line 1922 "y.tab.c"
    break;

  case 36: /* Statement: MethodInvocation SEMICOLON  */
#line 288 "jucompiler.y"
                                      { (yyval.node) = (yyvsp[-1].node); }
#line 1928 "y.tab.c"
    break;

  case 37: /* Statement: IDENTIFIER ASSIGN Expr SEMICOLON  */
#line 290 "jucompiler.y"
         { (yyval.node) = new_node_at("Assign", NULL, (yylsp[-2]).first_line, (yylsp[-2]).first_column); add_child((yyval.node), new_node_at("Identifier", (yyvsp[-3].str), (yylsp[-3]).first_line, (yylsp[-3]).first_column)); add_child((yyval.node), (yyvsp[-1].node)); }
#line 1934 "y.tab.c"
    break;

  case 38: /* Statement: ParseArgs SEMICOLON  */
#line 291 "jucompiler.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 1940 "y.tab.c"
    break;

  case 39: /* Statement: SEMICOLON  */
#line 292 "jucompiler.y"
                     { (yyval.node) = NULL; }
#line 1946 "y.tab.c"
    break;

  case 40: /* Statement: PRINT LPAR Expr RPAR SEMICOLON  */
#line 293 "jucompiler.y"
                                          { (yyval.node) = new_node_at("Print", NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column); add_child((yyval.node), (yyvsp[-2].node)); }
#line 1952 "y.tab.c"
    break;

  case 41: /* Statement: PRINT LPAR STRLIT RPAR SEMICOLON  */
#line 294 "jucompiler.y"
                                            { (yyval.node) = new_node_at("Print", NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column); add_child((yyval.node), new_node_at("StrLit", (yyvsp[-2].str), (yylsp[-2]).first_line, (yylsp[-2]).first_column)); }
#line 1958 "y.tab.c"
    break;

  case 42: /* Statement: error SEMICOLON  */
#line 295 "jucompiler.y"
                           { (yyval.node) = NULL; }
#line 1964 "y.tab.c"
    break;

  case 43: /* Expr: IDENTIFIER ASSIGN Expr  */
#line 299 "jucompiler.y"
    { (yyval.node) = new_node_at("Assign", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), new_node_at("Identifier", (yyvsp[-2].str), (yylsp[-2]).first_line, (yylsp[-2]).first_column)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1970 "y.tab.c"
    break;

  case 44: /* Expr: OrExpr  */
#line 300 "jucompiler.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1976 "y.tab.c"
    break;

  case 45: /* OrExpr: OrExpr OR AndExpr  */
#line 303 "jucompiler.y"
                          { (yyval.node) = new_node_at("Or", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1982 "y.tab.c"
    break;

  case 46: /* OrExpr: AndExpr  */
#line 304 "jucompiler.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1988 "y.tab.c"
    break;

  case 47: /* AndExpr: AndExpr AND XorExpr  */
#line 307 "jucompiler.y"
                             { (yyval.node) = new_node_at("And", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 1994 "y.tab.c"
    break;

  case 48: /* AndExpr: XorExpr  */
#line 308 "jucompiler.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2000 "y.tab.c"
    break;

  case 49: /* XorExpr: XorExpr XOR EqExpr  */
#line 311 "jucompiler.y"
                            { (yyval.node) = new_node_at("Xor", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2006 "y.tab.c"
    break;

  case 50: /* XorExpr: EqExpr  */
#line 312 "jucompiler.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2012 "y.tab.c"
    break;

  case 51: /* EqExpr: EqExpr EQ RelExpr  */
#line 315 "jucompiler.y"
                          { (yyval.node) = new_node_at("Eq", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2018 "y.tab.c"
    break;

  case 52: /* EqExpr: EqExpr NE RelExpr  */
#line 316 "jucompiler.y"
                          { (yyval.node) = new_node_at("Ne", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2024 "y.tab.c"
    break;

  case 53: /* EqExpr: RelExpr  */
#line 317 "jucompiler.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2030 "y.tab.c"
    break;

  case 54: /* RelExpr: RelExpr GE ShiftExpr  */
#line 320 "jucompiler.y"
                              { (yyval.node) = new_node_at("Ge", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2036 "y.tab.c"
    break;

  case 55: /* RelExpr: RelExpr GT ShiftExpr  */
#line 321 "jucompiler.y"
                              { (yyval.node) = new_node_at("Gt", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2042 "y.tab.c"
    break;

  case 56: /* RelExpr: RelExpr LE ShiftExpr  */
#line 322 "jucompiler.y"
                              { (yyval.node) = new_node_at("Le", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2048 "y.tab.c"
    break;

  case 57: /* RelExpr: RelExpr LT ShiftExpr  */
#line 323 "jucompiler.y"
                              { (yyval.node) = new_node_at("Lt", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2054 "y.tab.c"
    break;

  case 58: /* RelExpr: ShiftExpr  */
#line 324 "jucompiler.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2060 "y.tab.c"
    break;

  case 59: /* ShiftExpr: ShiftExpr LSHIFT AddExpr  */
#line 327 "jucompiler.y"
                                    { (yyval.node) = new_node_at("Lshift", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2066 "y.tab.c"
    break;

  case 60: /* ShiftExpr: ShiftExpr RSHIFT AddExpr  */
#line 328 "jucompiler.y"
                                    { (yyval.node) = new_node_at("Rshift", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2072 "y.tab.c"
    break;

  case 61: /* ShiftExpr: AddExpr  */
#line 329 "jucompiler.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2078 "y.tab.c"
    break;

  case 62: /* AddExpr: AddExpr PLUS MulExpr  */
#line 332 "jucompiler.y"
                              { (yyval.node) = new_node_at("Add", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2084 "y.tab.c"
    break;

  case 63: /* AddExpr: AddExpr MINUS MulExpr  */
#line 333 "jucompiler.y"
                               { (yyval.node) = new_node_at("Sub", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2090 "y.tab.c"
    break;

  case 64: /* AddExpr: MulExpr  */
#line 334 "jucompiler.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2096 "y.tab.c"
    break;

  case 65: /* MulExpr: MulExpr STAR UnaryExpr  */
#line 337 "jucompiler.y"
                                { (yyval.node) = new_node_at("Mul", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2102 "y.tab.c"
    break;

  case 66: /* MulExpr: MulExpr DIV UnaryExpr  */
#line 338 "jucompiler.y"
                               { (yyval.node) = new_node_at("Div", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2108 "y.tab.c"
    break;

  case 67: /* MulExpr: MulExpr MOD UnaryExpr  */
#line 339 "jucompiler.y"
                               { (yyval.node) = new_node_at("Mod", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[-2].node)); add_child((yyval.node), (yyvsp[0].node)); }
#line 2114 "y.tab.c"
    break;

  case 68: /* MulExpr: UnaryExpr  */
#line 340 "jucompiler.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2120 "y.tab.c"
    break;

  case 69: /* UnaryExpr: MINUS UnaryExpr  */
#line 343 "jucompiler.y"
                                             { (yyval.node) = new_node_at("Minus", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[0].node)); }
#line 2126 "y.tab.c"
    break;

  case 70: /* UnaryExpr: PLUS UnaryExpr  */
#line 344 "jucompiler.y"
                                           { (yyval.node) = new_node_at("Plus", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[0].node)); }
#line 2132 "y.tab.c"
    break;

  case 71: /* UnaryExpr: NOT UnaryExpr  */
#line 345 "jucompiler.y"
                         { (yyval.node) = new_node_at("Not", NULL, (yylsp[-1]).first_line, (yylsp[-1]).first_column); add_child((yyval.node), (yyvsp[0].node)); }
#line 2138 "y.tab.c"
    break;

  case 72: /* UnaryExpr: Primary  */
#line 346 "jucompiler.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2144 "y.tab.c"
    break;

  case 73: /* Primary: MethodInvocation  */
#line 349 "jucompiler.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2150 "y.tab.c"
    break;

  case 74: /* Primary: ParseArgs  */
#line 350 "jucompiler.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2156 "y.tab.c"
    break;

  case 75: /* Primary: IDENTIFIER DOTLENGTH  */
#line 351 "jucompiler.y"
                              { (yyval.node) = new_node_at("Length", NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); add_child((yyval.node), new_node_at("Identifier", (yyvsp[-1].str), (yylsp[-1]).first_line, (yylsp[-1]).first_column)); }
#line 2162 "y.tab.c"
    break;

  case 76: /* Primary: IDENTIFIER  */
#line 352 "jucompiler.y"
                    { (yyval.node) = new_node_at("Identifier", (yyvsp[0].str), (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2168 "y.tab.c"
    break;

  case 77: /* Primary: NATURAL  */
#line 353 "jucompiler.y"
                 { (yyval.node) = new_node_at("Natural", (yyvsp[0].str), (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2174 "y.tab.c"
    break;

  case 78: /* Primary: DECIMAL  */
#line 354 "jucompiler.y"
                 { (yyval.node) = new_node_at("Decimal", (yyvsp[0].str), (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2180 "y.tab.c"
    break;

  case 79: /* Primary: BOOLLIT  */
#line 355 "jucompiler.y"
                 { (yyval.node) = new_node_at("BoolLit", (yyvsp[0].str), (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2186 "y.tab.c"
    break;

  case 80: /* Primary: LPAR Expr RPAR  */
#line 356 "jucompiler.y"
                        { (yyval.node) = (yyvsp[-1].node); }
#line 2192 "y.tab.c"
    break;

  case 81: /* Primary: LPAR error RPAR  */
#line 357 "jucompiler.y"
                         { (yyval.node) = NULL; }
#line 2198 "y.tab.c"
    break;

  case 82: /* MethodInvocation: IDENTIFIER LPAR RPAR  */
#line 361 "jucompiler.y"
                { (yyval.node) = new_node_at("Call", NULL, (yylsp[-2]).first_line, (yylsp[-2]).first_column); add_child((yyval.node), new_node_at("Identifier", (yyvsp[-2].str), (yylsp[-2]).first_line, (yylsp[-2]).first_column)); }
#line 2204 "y.tab.c"
    break;

  case 83: /* MethodInvocation: IDENTIFIER LPAR ExprList RPAR  */
#line 363 "jucompiler.y"
                { (yyval.node) = new_node_at("Call", NULL, (yylsp[-3]).first_line, (yylsp[-3]).first_column); add_child((yyval.node), new_node_at("Identifier", (yyvsp[-3].str), (yylsp[-3]).first_line, (yylsp[-3]).first_column)); add_child((yyval.node), (yyvsp[-1].node)); }
#line 2210 "y.tab.c"
    break;

  case 84: /* MethodInvocation: IDENTIFIER LPAR error RPAR  */
#line 364 "jucompiler.y"
                                             { (yyval.node) = NULL; }
#line 2216 "y.tab.c"
    break;

  case 85: /* ExprList: Expr  */
#line 367 "jucompiler.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2222 "y.tab.c"
    break;

  case 86: /* ExprList: ExprList COMMA Expr  */
#line 368 "jucompiler.y"
                              { add_sibling((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2228 "y.tab.c"
    break;

  case 87: /* ParseArgs: PARSEINT LPAR IDENTIFIER LSQ Expr RSQ RPAR  */
#line 372 "jucompiler.y"
         { (yyval.node) = new_node_at("ParseArgs", NULL, (yylsp[-6]).first_line, (yylsp[-6]).first_column); add_child((yyval.node), new_node_at("Identifier", (yyvsp[-4].str), (yylsp[-4]).first_line, (yylsp[-4]).first_column)); add_child((yyval.node), (yyvsp[-2].node)); }
#line 2234 "y.tab.c"
    break;

  case 88: /* ParseArgs: PARSEINT LPAR error RPAR  */
#line 373 "jucompiler.y"
                                    { (yyval.node) = NULL; }
#line 2240 "y.tab.c"
    break;


#line 2244 "y.tab.c"

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
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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

  return yyresult;
}

#line 376 "jucompiler.y"




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
