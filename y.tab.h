/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 27 "jucompiler.y"
{
    char *str;
    struct node *node; 
}
/* Line 1529 of yacc.c.  */
#line 160 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;
