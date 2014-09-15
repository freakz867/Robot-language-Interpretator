
%{
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
%}
%error-verbose

%union {
    int intval;
    double floatval;
    char *strval;
    int subtok;
    nodeType *Node;
    std::vector<char *> *argList;
    std::vector<int> *dimList;
    std::vector<nodeType *> *stmtsList;
};

/* names and literal values */

%token <strval> VARNAME
%token <strval> STRING
%token <intval> INTNUM
%token <intval> BOOL


/*operators and precedence*/
%right ASSIGN
%left '+' '-'
%left '*' '/'
%left UMINUS
%left AND
%left NOT
%left <subtok> MXLOGIC NULLCOMPARE ELEMNULLCOMPARE

/* operators and special */
%token NOT AND
%token PLEASE
%token THANKS
%token VAR
%token FSIZE
%token <subtok> TYPECONVERSION
%token <subtok> CHANGEDIMENSION
%token FOR
%token BOUNDARY
%token STEP
%token SWITCH
%token <subtok> MOVEOP
%token GETENVIRONMENT
%token TASK
%token FINDEXIT
%token RESULT
%token DO
%token GET
%token ENDLINE
%token WATCH
%token INT


%type <Node> expr bool_expr stmt declaration func_stmt func_list size_expr fullstmt sentence get_func_res
%type <Node> return_call func_call typeconversion_expr assignment changedim_expr elemnullcmp_expr open_switch_expr
%type <Node> matched_switch_expr for_expr access_expr ctrl_expr get_env_expr
%type <argList> arguments
%type <dimList> dimension_list
%type <stmtsList> stmt_group_list stmt_group
%start func_list
%%

func_list: func_stmt endline_list   {/*ex($1); freeNode($1);*/}
         | func_stmt    {/*ex($1); freeNode($1);*/}
         | func_list func_stmt endline_list {/*ex($2); freeNode($2);*/}
         | func_list func_stmt  { /*ex($2); freeNode($2);*/}
         ;

func_stmt: TASK VARNAME arguments stmt_group    {emitText("function %s\n",$2); currentFunc=$2; ; root=funcDeclaration($2,$3,$4); $$=root; addFunction(&(root->funcDeclaration));}
        | TASK FINDEXIT arguments stmt_group    {emitText("function FINDEXIT\n"); currentFunc="FINDEXIT"; $$=funcDeclaration("FINDEXIT",$3,$4);root=$$; addFunction(&(root->funcDeclaration));}
        | declaration                           {emitText("global declaration\n"); context.createGlobalVar(&($$->varDeclaration));}
        ;

endline_list: ENDLINE
            | endline_list ENDLINE
            ;


arguments: VARNAME      {emitText("%s ",$1); $$=new argListType(); $$->push_back($1);}
    | arguments ',' VARNAME     {emitText("%s ",$3); $1->push_back($3);}
    ;

stmt_group: '(' ENDLINE stmt_group_list ')' {emitText("statements group"); $$=$3;}
        | '(' stmt_group_list ')' {emitText("statements group"); $$=$2;}
        ;


stmt_group_list: fullstmt ENDLINE   {$$=new stmtsListType(); $$->push_back($1);}
  | stmt_group_list fullstmt ENDLINE    {$1->push_back($2);}
  ;


fullstmt: sentence              {$$=$1;}
    | PLEASE sentence           {++context.politeness; $$=$2;}
    | PLEASE sentence THANKS    {context.politeness+=2; $$=$2;}
    | sentence THANKS           {++context.politeness; $$=$1;}
    ;

sentence: declaration   {$$=$1;}
        | stmt      {$$=$1;}
        ;

stmt: ctrl_expr
   | stmt_group
   | bool_expr
   | for_expr
   | matched_switch_expr
   | open_switch_expr
   | func_call
   | return_call
   | get_func_res
   | assignment
   ;

access_expr: VARNAME  '[' dimension_list ']'    {emitText("ACCESS %s",$1); $$ = opr(ACCESS,2,NULL,accessVar($1,$3));}
           | VARNAME '[' access_expr ']'       {emitText("ACCESS test %s",$1);$$ = opr(ACCESS,2,varName($1),$3);}
           ;

declaration: VAR VARNAME ASSIGN INTNUM      {emitText("DECLARATION INT %s = %d",$2,$4); $$ = varDeclaration($2,1,$4,NULL);}
           | VAR VARNAME ASSIGN '-' INTNUM      {emitText("DECLARATION INT %s = %d",$2,-$5); $$ = varDeclaration($2,1,-$5,NULL);}
           | VAR VARNAME '[' dimension_list ']' ASSIGN INTNUM       {emitText("DECLARATION %s",$2); $$ = varDeclaration($2,1,$7,$4);}
           | VAR VARNAME '[' dimension_list ']' ASSIGN '-' INTNUM       {emitText("DECLARATION %s",$2); $$ = varDeclaration($2,1,-$8,$4);}
           | VAR VARNAME '[' dimension_list ']' ASSIGN STRING       {emitText("DECLARATION %s",$2); }
           | VAR VARNAME '[' dimension_list ']' ASSIGN BOOL       {emitText("DECLARATION %s",$2); $$ = varDeclaration($2,0,$7,$4);}
           | VAR VARNAME ASSIGN STRING      {emitText("DECLARATION %s = %s",$2,$4);}
           | VAR VARNAME ASSIGN BOOL      {emitText("DECLARATION %s = %d",$2,$4); $$ = varDeclaration($2,0,$4,NULL);}
           ;

dimension_list: INTNUM          { $$=new dimListType(); $$->push_back($1);}
              | dimension_list ',' INTNUM       {$1->push_back($3);}
              | error
              ;

assignment: VARNAME ASSIGN expr   {emitText("VAR %s=",$1); $$=opr(ASSIGNACCESS,2,varName($1),$3);}
    | access_expr ASSIGN expr   {$$=opr(ASSIGNACCESS,2,$1,$3);}

    ;

expr: STRING { emitText("STRING %s", $1); }
   ;

expr: INTNUM { emitText("NUMBER %d", $1); $$ = con($1); }       /*   | WATCH expr {$$ = opr(WATCH, 1, $2);}*/
   | VARNAME    {$$=varName($1);}
   | access_expr                 {$$ = $1;}
   | get_func_res
   | elemnullcmp_expr
   | changedim_expr
   | size_expr
   | get_env_expr
   | expr '+' expr { emitText("ADD\n"); $$ = opr('+', 2, $1, $3); }
   | expr '-' expr { emitText("SUB: %d - %d\n",$1,$3); $$ = opr('-', 2, $1, $3); }
   | expr '*' expr { emitText("MULTIPLY: %d * %d\n",$1,$3); $$ = opr('*', 2, $1, $3); }
   | expr '/' expr { emitText("DIVIDE: %d / %d\n",$1,$3); $$ = opr('/', 2, $1, $3);}
   | '-' expr %prec UMINUS { emitText("NEG"); $$ = opr(UMINUS, 1, $2);  }
   | '(' expr ')'   {emitText("arithm expression in brackets"); $$ = $2;}
   | error
   ;

bool_expr: NULLCOMPARE VARNAME    { emitText("ELEMNULLCOMPARE %d", $2); $$ = opr(NULLCOMPARE, 2, con($1),varName($2));}
    | NOT bool_expr  { emitText("NOT %d", $2); $$ = opr(NOT, 1, $2); }
    | bool_expr AND bool_expr { emitText("%d AND %d", $1, $3); $$ = opr(AND, 2, $1, $3);}
    | MXLOGIC VARNAME  { emitText("MXLOGIC %d", $2); $$ = opr(MXLOGIC,2,con($1),varName($2));}
    | '(' bool_expr ')'   {emitText("boolean expression in brackets"); $$ = $2;}
    ;


ctrl_expr: MOVEOP    { emitText("MOVEOP"); $$=opr(MOVEOP,1,con($1));}
    ;

get_env_expr: GETENVIRONMENT    { emitText("GETENVIRONMENT"); $$=opr(GETENVIRONMENT,0);}
        ;

size_expr: FSIZE '(' VARNAME ')' { emitText("operator SIZE (%s)", $3); $$ = opr(FSIZE, 1, varName($3));}
    ;

typeconversion_expr: TYPECONVERSION VARNAME { emitText("TYPECONVERSION %s: type %d", $2,$1); $$ = opr(TYPECONVERSION,2,con($1),varName($2));}
    ;

changedim_expr: CHANGEDIMENSION VARNAME '[' dimension_list ']'  { emitText("CHANGEDIMENSION %s", $2); $$ = changeDim($2,con($1)->con.value,$4);}
    ;

for_expr: FOR VARNAME BOUNDARY VARNAME STEP VARNAME stmt_group  {emitText("FOR %s BOUNDARY %s STEP %s do statement", $2, $4, $6);$$ = cycle($2,$4,$6,$7);}
        | FOR VARNAME BOUNDARY VARNAME STEP VARNAME ENDLINE stmt_group  {emitText("FOR %s BOUNDARY %s STEP %s do statement", $2, $4, $6); $$ = cycle($2,$4,$6,$8);}
        ;

elemnullcmp_expr: ELEMNULLCOMPARE VARNAME   { emitText("NULLCOMPARE %d", $2); $$ = opr(ELEMNULLCOMPARE,2,con($1),varName($2));}
    ;

open_switch_expr: SWITCH bool_expr BOOL stmt_group               {emitText("SWITCH bool_expr %d statement group",$3); $$ = switchStmt($2,$3,$3,$4,NULL);}
        | SWITCH bool_expr BOOL ENDLINE stmt_group               {emitText("SWITCH bool_expr %d statement group",$3); $$ = switchStmt($2,$3,$3,$5,NULL);}
        | SWITCH bool_expr BOOL ENDLINE stmt_group BOOL stmt_group  {if($3==$6) yyerror("Error SWITCH statement"); else {emitText("SWITCH bool_expr %d statement %d statement",$3,$5); $$ = switchStmt($2,$3,$6,$5,$7);};}
        | SWITCH bool_expr BOOL stmt_group BOOL ENDLINE stmt_group  {if($3==$5) yyerror("Error SWITCH statement"); else {emitText("SWITCH bool_expr %d statement %d statement",$3,$5); $$ = switchStmt($2,$3,$5,$4,$7);};}
        | SWITCH bool_expr BOOL ENDLINE stmt_group BOOL ENDLINE stmt_group  {if($3==$6) yyerror("Error SWITCH statement"); else {emitText("SWITCH bool_expr %d statement %d statement",$3,$5); $$ = switchStmt($2,$3,$6,$5,$8);};}
        | SWITCH bool_expr BOOL stmt_group BOOL stmt_group  {if($3==$5) yyerror("Error SWITCH statement"); else {emitText("SWITCH bool_expr %d statement %d statement",$3,$5); $$ = switchStmt($2,$3,$5,$4,$6);};}
;

matched_switch_expr: SWITCH bool_expr BOOL matched_switch_expr BOOL matched_switch_expr
        ;

func_call: DO VARNAME arguments     {emitText("DO %s ",$2); $$ = funcCall($2,$3);}
        ;

return_call: RESULT VARNAME     {emitText("RESULT %s",$2); $$=opr(RESULT,1,varName($2));}
        ;

get_func_res: GET VARNAME       {emitText("GET %s",$2); $$=opr(GET,1,varName($2));}
        ;
%%

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
