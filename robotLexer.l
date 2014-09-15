%option noyywrap nodefault yylineno
%{
#include "robotParser.h"
#include "codeproc.h"
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

//#define YY_DECL extern "C" int yylex()
//#define YYSTYPE int
//extern "C" int yylex();
//extern int yylineno;
//extern YYSTYPE yylval;
void yyerror(char *s, ...);
extern int yyparse(void);

%}

%s FORMODE STEPMODE
%%
 /* keywords*/
PLEASE  {return PLEASE;}
THANKS  {return THANKS;}
VAR     {return VAR;}



 /* booleans*/
TRUE    {yylval.intval=1; return BOOL;}
FALSE   {yylval.intval=0; return BOOL;}
[-+*/()]    {return yytext[0];}

 /* signed integers*/
0[0-7]+           {yylval.strval=strdup(yytext); /*yylval.subtok=8;*/ return INTNUM;}  //oct ДОПИСАТЬ КОНВЕРТ В ДЕСЯТИЧНЫЕ
[1-7]+            {yylval.intval=atoi(yytext); /*yylval.subtok=10;*/ return INTNUM;}    //dec
[0-9]+            {yylval.intval=atoi(yytext); /*yylval.subtok=10;*/ return INTNUM;}    //dec
0x[0-9]+          {yylval.strval=strdup(yytext); /*yylval.subtok=16;*/ return STRING;}  //hex
0x[A-F][0-9A-F]*  {yylval.strval=strdup(yytext);  /*yylval.subtok=16;*/ return STRING;}  //hex
[0-9][0-9A-F]+         {yylval.strval=strdup(yytext);  /*yylval.subtok=16;*/ return STRING;}  //hex

 /* operators*/

"["     {return yytext[0];}
"]"     {return yytext[0];}
SIZE    {return FSIZE;}
LOGITIZE    {yylval.subtok=1; return TYPECONVERSION;}   //преобразование типа
DIGITIZE    {yylval.subtok=2; return TYPECONVERSION;}   //преобразование типа

REDUCE      {yylval.subtok=1; return CHANGEDIMENSION;}  //изменение размерности
EXTEND      {yylval.subtok=2; return CHANGEDIMENSION;}  //изменение размерности

"="         {return ASSIGN;}
                                                    /*сравнение с нулем:*/
MXEQ        {yylval.subtok=1; return NULLCOMPARE;}  //                   равен нулю
MXLT        {yylval.subtok=2; return NULLCOMPARE;}  //                   меньше нуля
MXGT        {yylval.subtok=3; return NULLCOMPARE;}  //                   больше нуля
MXLTE       {yylval.subtok=4; return NULLCOMPARE;}  //                   меньше или равен нулю
MXGTE       {yylval.subtok=5; return NULLCOMPARE;}  //                   больше или равен нулю

                                                        /*поэлементное сравнение с нулем:*/
ELEQ        {yylval.subtok=1; return ELEMNULLCOMPARE;}  //                                  равен нулю
ELLT        {yylval.subtok=2; return ELEMNULLCOMPARE;}  //                                  меньше нуля
ELGT        {yylval.subtok=3; return ELEMNULLCOMPARE;}  //                                  больше нуля
ELLTE       {yylval.subtok=4; return ELEMNULLCOMPARE;}  //                                  меньше или равен нулю
ELGTE       {yylval.subtok=5; return ELEMNULLCOMPARE;}  //                                  больше или равен нулю

NOT         {return NOT;}
AND         {return AND;}
MXTRUE      {yylval.subtok=1; return MXLOGIC;}  //TRUE, если большинство TRUE
MXFALSE     {yylval.subtok=2; return MXLOGIC;}  //FALSE, если большинство FALSE

FOR         {BEGIN FORMODE; return FOR;}
<FORMODE>BOUNDARY   {BEGIN STEPMODE; return BOUNDARY;}
<STEPMODE>STEP      {BEGIN INITIAL; return STEP;}

SWITCH      {return SWITCH;}

 /*move operators*/
MOVE        {yylval.subtok=1; return MOVEOP;}
ROTATE[ \t]+LEFT   {yylval.subtok=2; return MOVEOP;}
ROTATE[ \t]+RIGHT  {yylval.subtok=3; return MOVEOP;}
GET[ \t]+ENVIRONMENT   {return GETENVIRONMENT;}

 /*functions operators*/
TASK        {return TASK;}
FINDEXIT    {return FINDEXIT;}
RESULT      {return RESULT;}
DO          {return DO;}
GET         {return GET;}
WATCH       {return WATCH;}

 /*names*/
[A-Za-z][A-Za-z0-9_]*  { yylval.strval = strdup(yytext);  return VARNAME;}

[,]         {return yytext[0];}
[ \t]
[\n]        { return ENDLINE;}
.           {  }
%%
