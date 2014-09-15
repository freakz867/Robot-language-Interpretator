/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VARNAME = 258,
     STRING = 259,
     INTNUM = 260,
     BOOL = 261,
     ASSIGN = 262,
     UMINUS = 263,
     AND = 264,
     NOT = 265,
     ELEMNULLCOMPARE = 266,
     NULLCOMPARE = 267,
     MXLOGIC = 268,
     PLEASE = 269,
     THANKS = 270,
     VAR = 271,
     FSIZE = 272,
     TYPECONVERSION = 273,
     CHANGEDIMENSION = 274,
     FOR = 275,
     BOUNDARY = 276,
     STEP = 277,
     SWITCH = 278,
     MOVEOP = 279,
     GETENVIRONMENT = 280,
     TASK = 281,
     FINDEXIT = 282,
     RESULT = 283,
     DO = 284,
     GET = 285,
     ENDLINE = 286,
     WATCH = 287,
     INT = 288
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 49 "../robotInterpreter/robotParser.y"

    int intval;
    double floatval;
    char *strval;
    int subtok;
    nodeType *Node;
    std::vector<char *> *argList;
    std::vector<int> *dimList;
    std::vector<nodeType *> *stmtsList;



/* Line 2068 of yacc.c  */
#line 96 "/home/z/robot/robotInterpreter/robotParser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


