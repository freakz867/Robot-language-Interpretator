/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 2 "../robotInterpreter/robotParser.y"

#include "field/qgameplace.h"
#include <QApplication>
#include "codeproc.h"
#include "codecontext.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <vector>
#include <string>

extern int yylineno;
extern int yylex(void);
extern codeContext context;
extern QGamePlace w;
extern int yyparse(void);
void yyerror(const char *s, ...);
void emitText(char *s, ...);

nodeType *opr(int oper, int nops, ...);
nodeType *con(int value);   /* needed for integer numbers */
nodeType *varName(char *value);
nodeType *boolType(bool value);   /* needed for booleans */
nodeType *varDeclaration(char *varName, int defaultType, int defaultValue, dimListType *tempDimList);
nodeType *funcDeclaration(char *funcName, argListType *tempArgList,stmtsListType *stmtsList);
nodeType *funcCall(char *funcName, argListType *tempArgList);
nodeType *changeDim(char *funcName, int opId, dimListType *tempDimList);
nodeType *accessVar(char *varName, dimListType *tempIndexesList);
nodeType *switchStmt(nodeType *condStmt, bool cond1, bool cond2, stmtsListType *stmts1, stmtsListType *stmts2);
nodeType *cycle(char *counterName, char *boundName, char *stepName, stmtsListType *stmtsList);
void freeNode(nodeType *p);
int ex(nodeType *p);
int viewTree(nodeType *p);

extern int createVar(int domain,const varDeclarationNodeType *varInfo);
extern int addFunction(const funcDeclarationNodeType *func);

std::vector<int> dimList1;
std::vector<char *> argList1;
std::vector<nodeType *> stmtsList1;
std::string currentFunc;
bool local=false;
extern nodeType *root;


/* Line 268 of yacc.c  */
#line 118 "/home/z/robot/robotInterpreter/robotParser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 293 of yacc.c  */
#line 49 "../robotInterpreter/robotParser.y"

    int intval;
    double floatval;
    char *strval;
    int subtok;
    nodeType *Node;
    std::vector<char *> *argList;
    std::vector<int> *dimList;
    std::vector<nodeType *> *stmtsList;



/* Line 293 of yacc.c  */
#line 200 "/home/z/robot/robotInterpreter/robotParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 212 "/home/z/robot/robotInterpreter/robotParser.cpp"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   240

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNRULES -- Number of states.  */
#define YYNSTATES  158

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      39,    40,    10,     8,    38,     9,     2,    11,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    42,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    12,    15,    20,    25,    27,
      29,    32,    34,    38,    43,    47,    50,    54,    56,    59,
      63,    66,    68,    70,    72,    74,    76,    78,    80,    82,
      84,    86,    88,    93,    98,   103,   109,   117,   126,   134,
     142,   147,   152,   154,   158,   160,   164,   168,   170,   172,
     174,   176,   178,   180,   182,   184,   186,   190,   194,   198,
     202,   205,   209,   211,   214,   217,   221,   224,   228,   230,
     232,   237,   243,   251,   260,   263,   268,   274,   282,   290,
     299,   306,   310,   313
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,    45,    46,    -1,    45,    -1,    44,    45,
      46,    -1,    44,    45,    -1,    30,     3,    47,    48,    -1,
      30,    31,    47,    48,    -1,    54,    -1,    35,    -1,    46,
      35,    -1,     3,    -1,    47,    38,     3,    -1,    39,    35,
      49,    40,    -1,    39,    49,    40,    -1,    50,    35,    -1,
      49,    50,    35,    -1,    51,    -1,    18,    51,    -1,    18,
      51,    19,    -1,    51,    19,    -1,    54,    -1,    52,    -1,
      59,    -1,    48,    -1,    58,    -1,    63,    -1,    65,    -1,
      66,    -1,    67,    -1,    68,    -1,    56,    -1,     3,    41,
      55,    42,    -1,     3,    41,    53,    42,    -1,    20,     3,
       7,     5,    -1,    20,     3,     7,     9,     5,    -1,    20,
       3,    41,    55,    42,     7,     5,    -1,    20,     3,    41,
      55,    42,     7,     9,     5,    -1,    20,     3,    41,    55,
      42,     7,     4,    -1,    20,     3,    41,    55,    42,     7,
       6,    -1,    20,     3,     7,     4,    -1,    20,     3,     7,
       6,    -1,     5,    -1,    55,    38,     5,    -1,     1,    -1,
       3,     7,    57,    -1,    53,     7,    57,    -1,     4,    -1,
       5,    -1,     3,    -1,    53,    -1,    68,    -1,    64,    -1,
      62,    -1,    61,    -1,    60,    -1,    57,     8,    57,    -1,
      57,     9,    57,    -1,    57,    10,    57,    -1,    57,    11,
      57,    -1,     9,    57,    -1,    39,    57,    40,    -1,     1,
      -1,    16,     3,    -1,    14,    58,    -1,    58,    13,    58,
      -1,    17,     3,    -1,    39,    58,    40,    -1,    28,    -1,
      29,    -1,    21,    39,     3,    40,    -1,    23,     3,    41,
      55,    42,    -1,    24,     3,    25,     3,    26,     3,    48,
      -1,    24,     3,    25,     3,    26,     3,    35,    48,    -1,
      15,     3,    -1,    27,    58,     6,    48,    -1,    27,    58,
       6,    35,    48,    -1,    27,    58,     6,    35,    48,     6,
      48,    -1,    27,    58,     6,    48,     6,    35,    48,    -1,
      27,    58,     6,    35,    48,     6,    35,    48,    -1,    27,
      58,     6,    48,     6,    48,    -1,    33,     3,    47,    -1,
      32,     3,    -1,    34,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   110,   110,   111,   112,   113,   116,   117,   118,   121,
     122,   126,   127,   130,   131,   135,   136,   140,   141,   142,
     143,   146,   147,   150,   151,   152,   153,   155,   156,   157,
     158,   159,   162,   163,   166,   167,   168,   169,   170,   171,
     172,   173,   176,   177,   178,   181,   182,   186,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   206,   207,   208,   209,   210,   214,   217,
     220,   226,   229,   230,   233,   236,   237,   238,   239,   240,
     241,   247,   250,   253
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VARNAME", "STRING", "INTNUM", "BOOL",
  "ASSIGN", "'+'", "'-'", "'*'", "'/'", "UMINUS", "AND", "NOT",
  "ELEMNULLCOMPARE", "NULLCOMPARE", "MXLOGIC", "PLEASE", "THANKS", "VAR",
  "FSIZE", "TYPECONVERSION", "CHANGEDIMENSION", "FOR", "BOUNDARY", "STEP",
  "SWITCH", "MOVEOP", "GETENVIRONMENT", "TASK", "FINDEXIT", "RESULT", "DO",
  "GET", "ENDLINE", "WATCH", "INT", "','", "'('", "')'", "'['", "']'",
  "$accept", "func_list", "func_stmt", "endline_list", "arguments",
  "stmt_group", "stmt_group_list", "fullstmt", "sentence", "stmt",
  "access_expr", "declaration", "dimension_list", "assignment", "expr",
  "bool_expr", "ctrl_expr", "get_env_expr", "size_expr", "changedim_expr",
  "for_expr", "elemnullcmp_expr", "open_switch_expr", "func_call",
  "return_call", "get_func_res", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,    43,    45,
      42,    47,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,    44,    40,
      41,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    44,    44,    44,    45,    45,    45,    46,
      46,    47,    47,    48,    48,    49,    49,    50,    50,    50,
      50,    51,    51,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    53,    53,    54,    54,    54,    54,    54,    54,
      54,    54,    55,    55,    55,    56,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    58,    58,    58,    58,    58,    59,    60,
      61,    62,    63,    63,    64,    65,    65,    65,    65,    65,
      65,    66,    67,    68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     3,     2,     4,     4,     1,     1,
       2,     1,     3,     4,     3,     2,     3,     1,     2,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     4,     5,     7,     8,     7,     7,
       4,     4,     1,     3,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       2,     3,     1,     2,     2,     3,     2,     3,     1,     1,
       4,     5,     7,     8,     2,     4,     5,     7,     7,     8,
       6,     3,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     3,     8,     0,     0,     0,     1,
       5,     9,     2,     0,     0,    11,     0,     0,     4,    10,
      40,    34,    41,     0,    44,    42,     0,     0,     0,     6,
       7,    35,     0,     0,    12,     0,     0,     0,     0,     0,
       0,     0,    68,     0,     0,     0,     0,     0,    24,     0,
       0,    17,    22,     0,    21,    31,    25,    23,    26,    27,
      28,    29,    30,    43,     0,     0,     0,     0,    64,    63,
      66,    18,     0,     0,    82,     0,    83,     0,    25,    14,
       0,    15,    20,     0,     0,    38,    36,    39,     0,    62,
      49,    47,    48,     0,     0,     0,     0,    69,     0,    50,
      45,    55,    54,    53,    52,    51,     0,     0,     0,     0,
      19,     0,     0,    81,    13,    67,    16,    46,    65,    37,
      60,    74,     0,     0,     0,     0,     0,     0,     0,    33,
      32,     0,     0,    75,     0,     0,    61,    56,    57,    58,
      59,     0,    76,     0,    70,     0,     0,     0,     0,    80,
      71,     0,    72,     0,    77,    78,    73,    79
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,    12,    16,    48,    49,    50,    51,    52,
      99,    54,    26,    55,   100,    56,    57,   101,   102,   103,
      58,   104,    59,    60,    61,   105
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -66
static const yytype_int16 yypact[] =
{
      45,    11,    18,    80,    32,   -66,     0,    27,    27,   -66,
      32,   -66,    38,    82,    15,   -66,    83,    83,    38,   -66,
     -66,   -66,   -66,    90,   -66,   -66,    13,    81,   149,   -66,
     -66,   -66,   110,    71,   -66,     2,    -4,   117,   121,   201,
     123,    -4,   -66,   130,   131,   138,   175,   149,   -66,    65,
     108,   125,   -66,   140,   -66,   -66,   132,   -66,   -66,   -66,
     -66,   -66,   -66,   -66,    97,    35,   106,    -4,   -66,   -66,
     -66,   129,   126,    53,   -66,    27,   -66,   122,    -8,   -66,
     124,   -66,   -66,    35,    -4,   -66,   -66,   -66,   148,   -66,
     116,   -66,   -66,    35,   155,   133,   157,   -66,    35,   -66,
     202,   -66,   -66,   -66,   -66,   -66,   116,   128,    34,    -8,
     -66,   161,    55,   136,   -66,   -66,   -66,   202,   -66,   -66,
     -66,   -66,   165,   134,    37,    35,    35,    35,    35,   -66,
     -66,   145,   141,   173,   146,    15,   -66,   118,   118,   -66,
     -66,   182,   181,    73,   -66,    75,    79,    84,   141,   -66,
     -66,   141,   -66,   141,   -66,   -66,   -66,   -66
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -66,   -66,   187,   184,    -5,   -16,   150,   -25,   158,   -66,
     -24,    31,   -64,   -66,   -65,   -30,   -66,   -66,   -66,   -66,
     -66,   -66,   -66,   -66,   -66,   -20
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      29,    30,   108,    17,    53,    84,    68,    13,    62,    65,
      36,    73,    37,    38,     6,    53,    24,    78,   117,    62,
      25,     7,    53,    53,    80,    53,    62,    62,   120,    62,
      15,     5,   115,   124,     5,    67,    89,   109,    90,    91,
      92,    14,   107,    66,    93,   125,   126,   127,   128,     8,
      94,    32,    80,    53,   118,    33,    95,    62,    96,   112,
     137,   138,   139,   140,    97,     1,    84,    11,    35,    45,
     113,   145,    32,    19,    98,     2,   130,   136,    64,    36,
       9,    37,    38,    39,    34,     1,    20,    21,    22,    40,
     132,    23,    41,    42,    28,    31,   133,    43,    44,    45,
       1,    85,    86,    87,    47,    79,    88,    24,   148,   106,
       2,    25,    28,    32,   151,    63,   142,   150,    28,   153,
      69,    27,    28,    28,    70,    35,    72,   149,   127,   128,
     152,   154,   155,    74,    75,   156,    36,   157,    37,    38,
      39,    76,     1,    81,    82,    84,    40,    83,   110,    41,
      42,   111,    35,   119,    43,    44,    45,    66,   121,   116,
     123,    47,   114,    36,   131,    37,    38,    39,   134,     1,
     129,   141,   122,    40,    27,   135,    41,    42,    35,   143,
      28,    43,    44,    45,    46,   146,   144,   147,    47,    36,
      10,    37,    38,    39,    18,     1,    77,    71,     0,    40,
       0,     0,    41,    42,    35,     0,     0,    43,    44,    45,
     125,   126,   127,   128,    47,    36,     0,    37,    38,     0,
       0,     1,     0,     0,     0,    40,     0,     0,    41,    42,
       0,     0,     0,    43,    44,    45,     0,     0,     0,     0,
      47
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-66))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      16,    17,    66,     8,    28,    13,    36,     7,    28,     7,
      14,    41,    16,    17,     3,    39,     1,    47,    83,    39,
       5,     3,    46,    47,    49,    49,    46,    47,    93,    49,
       3,     0,    40,    98,     3,    39,     1,    67,     3,     4,
       5,    41,    66,    41,     9,     8,     9,    10,    11,    31,
      15,    38,    77,    77,    84,    42,    21,    77,    23,     6,
     125,   126,   127,   128,    29,    20,    13,    35,     3,    34,
      75,   135,    38,    35,    39,    30,    42,    40,     7,    14,
       0,    16,    17,    18,     3,    20,     4,     5,     6,    24,
      35,     9,    27,    28,    39,     5,   112,    32,    33,    34,
      20,     4,     5,     6,    39,    40,     9,     1,    35,     3,
      30,     5,    39,    38,    35,     5,   132,    42,    39,    35,
       3,    38,    39,    39,     3,     3,     3,   143,    10,    11,
     146,   147,   148,     3,     3,   151,    14,   153,    16,    17,
      18,     3,    20,    35,    19,    13,    24,     7,    19,    27,
      28,    25,     3,     5,    32,    33,    34,    41,     3,    35,
       3,    39,    40,    14,     3,    16,    17,    18,     3,    20,
      42,    26,    39,    24,    38,    41,    27,    28,     3,     6,
      39,    32,    33,    34,    35,     3,    40,     6,    39,    14,
       3,    16,    17,    18,    10,    20,    46,    39,    -1,    24,
      -1,    -1,    27,    28,     3,    -1,    -1,    32,    33,    34,
       8,     9,    10,    11,    39,    14,    -1,    16,    17,    -1,
      -1,    20,    -1,    -1,    -1,    24,    -1,    -1,    27,    28,
      -1,    -1,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,
      39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    20,    30,    44,    45,    54,     3,     3,    31,     0,
      45,    35,    46,     7,    41,     3,    47,    47,    46,    35,
       4,     5,     6,     9,     1,     5,    55,    38,    39,    48,
      48,     5,    38,    42,     3,     3,    14,    16,    17,    18,
      24,    27,    28,    32,    33,    34,    35,    39,    48,    49,
      50,    51,    52,    53,    54,    56,    58,    59,    63,    65,
      66,    67,    68,     5,     7,     7,    41,    39,    58,     3,
       3,    51,     3,    58,     3,     3,     3,    49,    58,    40,
      50,    35,    19,     7,    13,     4,     5,     6,     9,     1,
       3,     4,     5,     9,    15,    21,    23,    29,    39,    53,
      57,    60,    61,    62,    64,    68,     3,    53,    55,    58,
      19,    25,     6,    47,    40,    40,    35,    57,    58,     5,
      57,     3,    39,     3,    57,     8,     9,    10,    11,    42,
      42,     3,    35,    48,     3,    41,    40,    57,    57,    57,
      57,    26,    48,     6,    40,    55,     3,     6,    35,    48,
      42,    35,    48,    35,    48,    48,    48,    48
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
  *++yyvsp = yylval;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 110 "../robotInterpreter/robotParser.y"
    {/*ex($1); freeNode($1);*/}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 111 "../robotInterpreter/robotParser.y"
    {/*ex($1); freeNode($1);*/}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 112 "../robotInterpreter/robotParser.y"
    {/*ex($2); freeNode($2);*/}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 113 "../robotInterpreter/robotParser.y"
    { /*ex($2); freeNode($2);*/}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 116 "../robotInterpreter/robotParser.y"
    {emitText("function %s\n",(yyvsp[(2) - (4)].strval)); currentFunc=(yyvsp[(2) - (4)].strval); ; root=funcDeclaration((yyvsp[(2) - (4)].strval),(yyvsp[(3) - (4)].argList),(yyvsp[(4) - (4)].stmtsList)); (yyval.Node)=root; addFunction(&(root->funcDeclaration));}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 117 "../robotInterpreter/robotParser.y"
    {emitText("function FINDEXIT\n"); currentFunc="FINDEXIT"; (yyval.Node)=funcDeclaration("FINDEXIT",(yyvsp[(3) - (4)].argList),(yyvsp[(4) - (4)].stmtsList));root=(yyval.Node); addFunction(&(root->funcDeclaration));}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 118 "../robotInterpreter/robotParser.y"
    {emitText("global declaration\n"); context.createGlobalVar(&((yyval.Node)->varDeclaration));}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 126 "../robotInterpreter/robotParser.y"
    {emitText("%s ",(yyvsp[(1) - (1)].strval)); (yyval.argList)=new argListType(); (yyval.argList)->push_back((yyvsp[(1) - (1)].strval));}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 127 "../robotInterpreter/robotParser.y"
    {emitText("%s ",(yyvsp[(3) - (3)].strval)); (yyvsp[(1) - (3)].argList)->push_back((yyvsp[(3) - (3)].strval));}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 130 "../robotInterpreter/robotParser.y"
    {emitText("statements group"); (yyval.stmtsList)=(yyvsp[(3) - (4)].stmtsList);}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 131 "../robotInterpreter/robotParser.y"
    {emitText("statements group"); (yyval.stmtsList)=(yyvsp[(2) - (3)].stmtsList);}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 135 "../robotInterpreter/robotParser.y"
    {(yyval.stmtsList)=new stmtsListType(); (yyval.stmtsList)->push_back((yyvsp[(1) - (2)].Node));}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 136 "../robotInterpreter/robotParser.y"
    {(yyvsp[(1) - (3)].stmtsList)->push_back((yyvsp[(2) - (3)].Node));}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 140 "../robotInterpreter/robotParser.y"
    {(yyval.Node)=(yyvsp[(1) - (1)].Node);}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 141 "../robotInterpreter/robotParser.y"
    {++context.politeness; (yyval.Node)=(yyvsp[(2) - (2)].Node);}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 142 "../robotInterpreter/robotParser.y"
    {context.politeness+=2; (yyval.Node)=(yyvsp[(2) - (3)].Node);}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 143 "../robotInterpreter/robotParser.y"
    {++context.politeness; (yyval.Node)=(yyvsp[(1) - (2)].Node);}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 146 "../robotInterpreter/robotParser.y"
    {(yyval.Node)=(yyvsp[(1) - (1)].Node);}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 147 "../robotInterpreter/robotParser.y"
    {(yyval.Node)=(yyvsp[(1) - (1)].Node);}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 162 "../robotInterpreter/robotParser.y"
    {emitText("ACCESS %s",(yyvsp[(1) - (4)].strval)); (yyval.Node) = opr(ACCESS,2,NULL,accessVar((yyvsp[(1) - (4)].strval),(yyvsp[(3) - (4)].dimList)));}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 163 "../robotInterpreter/robotParser.y"
    {emitText("ACCESS test %s",(yyvsp[(1) - (4)].strval));(yyval.Node) = opr(ACCESS,2,varName((yyvsp[(1) - (4)].strval)),(yyvsp[(3) - (4)].Node));}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 166 "../robotInterpreter/robotParser.y"
    {emitText("DECLARATION INT %s = %d",(yyvsp[(2) - (4)].strval),(yyvsp[(4) - (4)].intval)); (yyval.Node) = varDeclaration((yyvsp[(2) - (4)].strval),1,(yyvsp[(4) - (4)].intval),NULL);}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 167 "../robotInterpreter/robotParser.y"
    {emitText("DECLARATION INT %s = %d",(yyvsp[(2) - (5)].strval),-(yyvsp[(5) - (5)].intval)); (yyval.Node) = varDeclaration((yyvsp[(2) - (5)].strval),1,-(yyvsp[(5) - (5)].intval),NULL);}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 168 "../robotInterpreter/robotParser.y"
    {emitText("DECLARATION %s",(yyvsp[(2) - (7)].strval)); (yyval.Node) = varDeclaration((yyvsp[(2) - (7)].strval),1,(yyvsp[(7) - (7)].intval),(yyvsp[(4) - (7)].dimList));}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 169 "../robotInterpreter/robotParser.y"
    {emitText("DECLARATION %s",(yyvsp[(2) - (8)].strval)); (yyval.Node) = varDeclaration((yyvsp[(2) - (8)].strval),1,-(yyvsp[(8) - (8)].intval),(yyvsp[(4) - (8)].dimList));}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 170 "../robotInterpreter/robotParser.y"
    {emitText("DECLARATION %s",(yyvsp[(2) - (7)].strval)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 171 "../robotInterpreter/robotParser.y"
    {emitText("DECLARATION %s",(yyvsp[(2) - (7)].strval)); (yyval.Node) = varDeclaration((yyvsp[(2) - (7)].strval),0,(yyvsp[(7) - (7)].intval),(yyvsp[(4) - (7)].dimList));}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 172 "../robotInterpreter/robotParser.y"
    {emitText("DECLARATION %s = %s",(yyvsp[(2) - (4)].strval),(yyvsp[(4) - (4)].strval));}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 173 "../robotInterpreter/robotParser.y"
    {emitText("DECLARATION %s = %d",(yyvsp[(2) - (4)].strval),(yyvsp[(4) - (4)].intval)); (yyval.Node) = varDeclaration((yyvsp[(2) - (4)].strval),0,(yyvsp[(4) - (4)].intval),NULL);}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 176 "../robotInterpreter/robotParser.y"
    { (yyval.dimList)=new dimListType(); (yyval.dimList)->push_back((yyvsp[(1) - (1)].intval));}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 177 "../robotInterpreter/robotParser.y"
    {(yyvsp[(1) - (3)].dimList)->push_back((yyvsp[(3) - (3)].intval));}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 181 "../robotInterpreter/robotParser.y"
    {emitText("VAR %s=",(yyvsp[(1) - (3)].strval)); (yyval.Node)=opr(ASSIGNACCESS,2,varName((yyvsp[(1) - (3)].strval)),(yyvsp[(3) - (3)].Node));}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 182 "../robotInterpreter/robotParser.y"
    {(yyval.Node)=opr(ASSIGNACCESS,2,(yyvsp[(1) - (3)].Node),(yyvsp[(3) - (3)].Node));}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 186 "../robotInterpreter/robotParser.y"
    { emitText("STRING %s", (yyvsp[(1) - (1)].strval)); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 189 "../robotInterpreter/robotParser.y"
    { emitText("NUMBER %d", (yyvsp[(1) - (1)].intval)); (yyval.Node) = con((yyvsp[(1) - (1)].intval)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 190 "../robotInterpreter/robotParser.y"
    {(yyval.Node)=varName((yyvsp[(1) - (1)].strval));}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 191 "../robotInterpreter/robotParser.y"
    {(yyval.Node) = (yyvsp[(1) - (1)].Node);}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 197 "../robotInterpreter/robotParser.y"
    { emitText("ADD\n"); (yyval.Node) = opr('+', 2, (yyvsp[(1) - (3)].Node), (yyvsp[(3) - (3)].Node)); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 198 "../robotInterpreter/robotParser.y"
    { emitText("SUB: %d - %d\n",(yyvsp[(1) - (3)].Node),(yyvsp[(3) - (3)].Node)); (yyval.Node) = opr('-', 2, (yyvsp[(1) - (3)].Node), (yyvsp[(3) - (3)].Node)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 199 "../robotInterpreter/robotParser.y"
    { emitText("MULTIPLY: %d * %d\n",(yyvsp[(1) - (3)].Node),(yyvsp[(3) - (3)].Node)); (yyval.Node) = opr('*', 2, (yyvsp[(1) - (3)].Node), (yyvsp[(3) - (3)].Node)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 200 "../robotInterpreter/robotParser.y"
    { emitText("DIVIDE: %d / %d\n",(yyvsp[(1) - (3)].Node),(yyvsp[(3) - (3)].Node)); (yyval.Node) = opr('/', 2, (yyvsp[(1) - (3)].Node), (yyvsp[(3) - (3)].Node));}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 201 "../robotInterpreter/robotParser.y"
    { emitText("NEG"); (yyval.Node) = opr(UMINUS, 1, (yyvsp[(2) - (2)].Node));  }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 202 "../robotInterpreter/robotParser.y"
    {emitText("arithm expression in brackets"); (yyval.Node) = (yyvsp[(2) - (3)].Node);}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 206 "../robotInterpreter/robotParser.y"
    { emitText("ELEMNULLCOMPARE %d", (yyvsp[(2) - (2)].strval)); (yyval.Node) = opr(NULLCOMPARE, 2, con((yyvsp[(1) - (2)].subtok)),varName((yyvsp[(2) - (2)].strval)));}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 207 "../robotInterpreter/robotParser.y"
    { emitText("NOT %d", (yyvsp[(2) - (2)].Node)); (yyval.Node) = opr(NOT, 1, (yyvsp[(2) - (2)].Node)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 208 "../robotInterpreter/robotParser.y"
    { emitText("%d AND %d", (yyvsp[(1) - (3)].Node), (yyvsp[(3) - (3)].Node)); (yyval.Node) = opr(AND, 2, (yyvsp[(1) - (3)].Node), (yyvsp[(3) - (3)].Node));}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 209 "../robotInterpreter/robotParser.y"
    { emitText("MXLOGIC %d", (yyvsp[(2) - (2)].strval)); (yyval.Node) = opr(MXLOGIC,2,con((yyvsp[(1) - (2)].subtok)),varName((yyvsp[(2) - (2)].strval)));}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 210 "../robotInterpreter/robotParser.y"
    {emitText("boolean expression in brackets"); (yyval.Node) = (yyvsp[(2) - (3)].Node);}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 214 "../robotInterpreter/robotParser.y"
    { emitText("MOVEOP"); (yyval.Node)=opr(MOVEOP,1,con((yyvsp[(1) - (1)].subtok)));}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 217 "../robotInterpreter/robotParser.y"
    { emitText("GETENVIRONMENT"); (yyval.Node)=opr(GETENVIRONMENT,0);}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 220 "../robotInterpreter/robotParser.y"
    { emitText("operator SIZE (%s)", (yyvsp[(3) - (4)].strval)); (yyval.Node) = opr(FSIZE, 1, varName((yyvsp[(3) - (4)].strval)));}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 226 "../robotInterpreter/robotParser.y"
    { emitText("CHANGEDIMENSION %s", (yyvsp[(2) - (5)].strval)); (yyval.Node) = changeDim((yyvsp[(2) - (5)].strval),con((yyvsp[(1) - (5)].subtok))->con.value,(yyvsp[(4) - (5)].dimList));}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 229 "../robotInterpreter/robotParser.y"
    {emitText("FOR %s BOUNDARY %s STEP %s do statement", (yyvsp[(2) - (7)].strval), (yyvsp[(4) - (7)].strval), (yyvsp[(6) - (7)].strval));(yyval.Node) = cycle((yyvsp[(2) - (7)].strval),(yyvsp[(4) - (7)].strval),(yyvsp[(6) - (7)].strval),(yyvsp[(7) - (7)].stmtsList));}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 230 "../robotInterpreter/robotParser.y"
    {emitText("FOR %s BOUNDARY %s STEP %s do statement", (yyvsp[(2) - (8)].strval), (yyvsp[(4) - (8)].strval), (yyvsp[(6) - (8)].strval)); (yyval.Node) = cycle((yyvsp[(2) - (8)].strval),(yyvsp[(4) - (8)].strval),(yyvsp[(6) - (8)].strval),(yyvsp[(8) - (8)].stmtsList));}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 233 "../robotInterpreter/robotParser.y"
    { emitText("NULLCOMPARE %d", (yyvsp[(2) - (2)].strval)); (yyval.Node) = opr(ELEMNULLCOMPARE,2,con((yyvsp[(1) - (2)].subtok)),varName((yyvsp[(2) - (2)].strval)));}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 236 "../robotInterpreter/robotParser.y"
    {emitText("SWITCH bool_expr %d statement group",(yyvsp[(3) - (4)].intval)); (yyval.Node) = switchStmt((yyvsp[(2) - (4)].Node),(yyvsp[(3) - (4)].intval),(yyvsp[(3) - (4)].intval),(yyvsp[(4) - (4)].stmtsList),NULL);}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 237 "../robotInterpreter/robotParser.y"
    {emitText("SWITCH bool_expr %d statement group",(yyvsp[(3) - (5)].intval)); (yyval.Node) = switchStmt((yyvsp[(2) - (5)].Node),(yyvsp[(3) - (5)].intval),(yyvsp[(3) - (5)].intval),(yyvsp[(5) - (5)].stmtsList),NULL);}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 238 "../robotInterpreter/robotParser.y"
    {if((yyvsp[(3) - (7)].intval)==(yyvsp[(6) - (7)].intval)) yyerror("Error SWITCH statement"); else {emitText("SWITCH bool_expr %d statement %d statement",(yyvsp[(3) - (7)].intval),(yyvsp[(5) - (7)].stmtsList)); (yyval.Node) = switchStmt((yyvsp[(2) - (7)].Node),(yyvsp[(3) - (7)].intval),(yyvsp[(6) - (7)].intval),(yyvsp[(5) - (7)].stmtsList),(yyvsp[(7) - (7)].stmtsList));};}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 239 "../robotInterpreter/robotParser.y"
    {if((yyvsp[(3) - (7)].intval)==(yyvsp[(5) - (7)].intval)) yyerror("Error SWITCH statement"); else {emitText("SWITCH bool_expr %d statement %d statement",(yyvsp[(3) - (7)].intval),(yyvsp[(5) - (7)].intval)); (yyval.Node) = switchStmt((yyvsp[(2) - (7)].Node),(yyvsp[(3) - (7)].intval),(yyvsp[(5) - (7)].intval),(yyvsp[(4) - (7)].stmtsList),(yyvsp[(7) - (7)].stmtsList));};}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 240 "../robotInterpreter/robotParser.y"
    {if((yyvsp[(3) - (8)].intval)==(yyvsp[(6) - (8)].intval)) yyerror("Error SWITCH statement"); else {emitText("SWITCH bool_expr %d statement %d statement",(yyvsp[(3) - (8)].intval),(yyvsp[(5) - (8)].stmtsList)); (yyval.Node) = switchStmt((yyvsp[(2) - (8)].Node),(yyvsp[(3) - (8)].intval),(yyvsp[(6) - (8)].intval),(yyvsp[(5) - (8)].stmtsList),(yyvsp[(8) - (8)].stmtsList));};}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 241 "../robotInterpreter/robotParser.y"
    {if((yyvsp[(3) - (6)].intval)==(yyvsp[(5) - (6)].intval)) yyerror("Error SWITCH statement"); else {emitText("SWITCH bool_expr %d statement %d statement",(yyvsp[(3) - (6)].intval),(yyvsp[(5) - (6)].intval)); (yyval.Node) = switchStmt((yyvsp[(2) - (6)].Node),(yyvsp[(3) - (6)].intval),(yyvsp[(5) - (6)].intval),(yyvsp[(4) - (6)].stmtsList),(yyvsp[(6) - (6)].stmtsList));};}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 247 "../robotInterpreter/robotParser.y"
    {emitText("DO %s ",(yyvsp[(2) - (3)].strval)); (yyval.Node) = funcCall((yyvsp[(2) - (3)].strval),(yyvsp[(3) - (3)].argList));}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 250 "../robotInterpreter/robotParser.y"
    {emitText("RESULT %s",(yyvsp[(2) - (2)].strval)); (yyval.Node)=opr(RESULT,1,varName((yyvsp[(2) - (2)].strval)));}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 253 "../robotInterpreter/robotParser.y"
    {emitText("GET %s",(yyvsp[(2) - (2)].strval)); (yyval.Node)=opr(GET,1,varName((yyvsp[(2) - (2)].strval)));}
    break;



/* Line 1806 of yacc.c  */
#line 2046 "/home/z/robot/robotInterpreter/robotParser.cpp"
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
		      yytoken, &yylval);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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



/* Line 2067 of yacc.c  */
#line 255 "../robotInterpreter/robotParser.y"


#define SIZEOF_NODETYPE ((char *)&p->con - (char *)p)

nodeType *con(int value) {
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(intNodeType);
    if ((p = (nodeType*)malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeCon;
    p->con.value = value;

    return p;
}

nodeType *boolType(bool value) {
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(intNodeType);
    if ((p = (nodeType*)malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeBool;
    p->boolVal.value = value;

    return p;
}

nodeType *funcDeclaration(char *funcName, argListType *tempArgList, stmtsListType *stmtsList){
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(funcDeclarationNodeType) + (strlen(funcName))*sizeof(nodeType*);
    if ((p = (nodeType*)malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeFuncDeclaration;
    p->funcDeclaration.funcName=(char *) malloc(strlen(funcName)+1);
    strcpy(p->funcDeclaration.funcName,funcName);

    p->funcDeclaration.args=new argListType(*tempArgList);
    /*int ndim=tempArgList->size();
    for (int i = 0; i < ndim; i++){
        printf("%s ",&(p->funcDeclaration.args)[i]);
        printf("%s ",argList[i]);
        }*/
    tempArgList->clear();

    p->funcDeclaration.statements=new stmtsListType(*stmtsList);

    int nstmts=stmtsList->size();
    printf("statements in function: %d\n",nstmts);
    stmtsList->clear();
return p;
}

nodeType *cycle(char *counterName, char *boundName, char *stepName, stmtsListType *stmtsList){
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(cycleNodeType) + (strlen(counterName)+strlen(boundName)+strlen(stepName))*sizeof(nodeType*);
    if ((p = (nodeType*)malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeCycle;
    p->cycle.counterName=(char *) malloc(strlen(counterName)+1);
    strcpy(p->cycle.counterName,counterName);

    p->cycle.boundName=(char *) malloc(strlen(boundName)+1);
    strcpy(p->cycle.boundName,boundName);

    p->cycle.stepName=(char *) malloc(strlen(stepName)+1);
    strcpy(p->cycle.stepName,stepName);

    p->cycle.statements=new stmtsListType(*stmtsList);

    stmtsList->clear();
return p;
}

nodeType *switchStmt(nodeType *condStmt, bool cond1, bool cond2, stmtsListType *stmts1, stmtsListType *stmts2){
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(switchNodeType);
    if ((p = (nodeType*)malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeSwitch;
    p->switchStmt.conditionStmt=condStmt;
    p->switchStmt.condition1=cond1;
    p->switchStmt.condition2=cond2;

    p->switchStmt.statements1=new stmtsListType(*stmts1);
    if(stmts2!=NULL)
        p->switchStmt.statements2=new stmtsListType(*stmts2);
    else
        p->switchStmt.statements2=NULL;
    /*int ndim=tempArgList->size();
    for (int i = 0; i < ndim; i++){
    printf("%s ",&(p->funcDeclaration.args)[i]);
    printf("%s ",argList[i]);
    }*/
    stmts1->clear();
    if(stmts2!=NULL)
        stmts2->clear();

return p;
}

nodeType *funcCall(char *funcName, argListType *tempArgList){
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(funcCallNodeType) + (strlen(funcName))*sizeof(nodeType*);
    if ((p = (nodeType*)malloc(nodeSize)) == NULL)
    yyerror("out of memory");

    /* copy information */
    p->type = typeFuncCall;
    p->funcCall.Name=(char *) malloc(strlen(funcName)+1);
    strcpy(p->funcCall.Name,funcName);

    p->funcCall.args=new argListType(*tempArgList);

    printf("test funccall arguments\n");
    int ndim=tempArgList->size();
    for (int i = 0; i < ndim; i++){
    //printf("%s ",&(p->funcCall.args)[i]);
    printf("%s ",(*tempArgList)[i]);
    }
    tempArgList->clear();
return p;
}

nodeType *changeDim(char *funcName, int opId, dimListType *tempDimList){
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(changeDimNodeType) + (strlen(funcName))*sizeof(nodeType*);
    if ((p = (nodeType*)malloc(nodeSize)) == NULL)
    yyerror("out of memory");

    /* copy information */
    p->type = typeChangeDim;
    p->changeDim.opId=opId;
    p->changeDim.varName=(char *) malloc(strlen(funcName)+1);
    strcpy(p->changeDim.varName,funcName);

    p->changeDim.dimensions=new dimListType(*tempDimList);

    tempDimList->clear();
return p;
}

nodeType *accessVar(char *varName, dimListType *tempIndexesList){
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(changeDimNodeType) + (strlen(varName))*sizeof(nodeType*);
    if ((p = (nodeType*)malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeAccessVar;
    p->accessVar.varName=(char *) malloc(strlen(varName)+1);
    strcpy(p->accessVar.varName,varName);

    p->accessVar.indexes=new dimListType(*tempIndexesList);

    tempIndexesList->clear();
return p;
}

nodeType *varName(char *value){
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(varNameNodeType) + (strlen(value))*sizeof(nodeType*);
    if ((p = (nodeType*)malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeVarName;
    p->varName.Name=(char *) malloc(strlen(value)+1);
    strcpy(p->varName.Name,value);
    printf("test: %s",p->varName.Name);

return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    size_t nodeSize;
    int i;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(oprNodeType) +
        (nops - 1) * sizeof(nodeType*);
    if ((p = (nodeType*)malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++){
        p->opr.op[i] = va_arg(ap, nodeType*);
    }
    va_end(ap);
    return p;
}

nodeType *varDeclaration(char *varName, int defaultType, int defaultValue, dimListType *tempDimList){
    int ndim;
    if(tempDimList!=NULL)
        ndim=tempDimList->size();
    else
        ndim=0;
    nodeType *p;
    size_t nodeSize;
    int i;
    /*printf("\n");
    for(int i=0;i<dimList.size();++i)
    {
        printf("%d ",dimList[i]);
    }
    printf("\n");*/
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(varDeclarationNodeType) + (ndim - 1) * sizeof(nodeType*);
    if ((p = (nodeType*)malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeVarDeclaration;
    p->varDeclaration.varName=(char *) malloc(strlen(varName)+1);
    strcpy(p->varDeclaration.varName,varName);
    p->varDeclaration.funcName=(char *) malloc(currentFunc.length()+1);
    strcpy(p->varDeclaration.funcName,currentFunc.c_str());
    p->varDeclaration.ndim = ndim;
    p->varDeclaration.defaultType = defaultType;
    p->varDeclaration.defaultValue = defaultValue;
    p->varDeclaration.dim = new int [ndim];
    for (i = 0; i < ndim; i++)
        p->varDeclaration.dim[i] = (*tempDimList)[i];
    if(tempDimList!=NULL)
        tempDimList->clear();
    return p;

}

void freeNode(nodeType *p) {
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void emitText(char *s, ...)
{
  //extern yylineno;

  va_list ap;
  va_start(ap, s);

  printf("rpn: ");
  vfprintf(stdout, s, ap);
  printf("\n");
}

void yyerror(const char *s, ...)
{
  //extern yylineno;

  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "%d: error: ", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
  exit(0);
}

nodeType *root;
int main(int ac, char **av)
{

    extern nodeType *root;
    int res=0;
    extern FILE *yyin;
    yyin = fopen("source.txt", "r");
    res=yyparse();
    printf("yyparse: %d\n",res);
        context.viewFunctions();
        QApplication a(ac, av);
        QGamePlace w;
        context.initializeRobot(w.labyrinth);
        w.show();
    context.executeMainCode();
    printf("politeness: %d\n",context.politeness);
    return a.exec();
}

