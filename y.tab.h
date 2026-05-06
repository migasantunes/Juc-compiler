/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
#line 25 "jucompiler.y"

    char *str;
    struct node *node; 

#line 178 "y.tab.h"

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
