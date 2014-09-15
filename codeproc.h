#ifndef CODEPROC_H
#define CODEPROC_H
#include <vector>
typedef std::vector<char *> argListType;
typedef std::vector<int> dimListType;
typedef std::vector<int *> addressListType;

typedef enum { typeCon, typeVarName, typeOpr, typeBool, typeVarDeclaration, typeFuncDeclaration, typeFuncCall, typeChangeDim, typeSwitch, typeCycle, typeAccessVar } nodeEnum;


/* constants */
typedef struct {
    int value;                  /* value of constant */
} intNodeType;

/* identifiers */
typedef struct {
    char *Name;                      /* subscript to string */
} varNameNodeType;

/* operators */
typedef struct {
    int oper;                   /* operator */
    int nops;                   /* number of operands */
    struct nodeTypeTag *op[1];  /* operands (expandable) */
} oprNodeType;

/* operators */
typedef struct varDeclarationNodeType{
    char *varName;                  /* var Name */
    char *funcName;                 /* owner function name */
    bool local;                     /* visibility of var */
    int defaultType;                /* default value type */
    int defaultValue;               /* default value */
    int ndim;                       /* number of dimensions */
    int *dim;                       /* dimensions (expandable) */
} varDeclarationNodeType;

typedef struct {
    char *funcName;
    std::vector<char *> *args;       /* arguments (expandable) */
    std::vector<struct nodeTypeTag *> *statements;
} funcDeclarationNodeType;

typedef struct {
    bool value;
} boolNodeType;

typedef struct {
    char *Name;
    std::vector<char *> *args;
} funcCallNodeType;

typedef struct {
    char *varName;
    int opId;
    std::vector<int> *dimensions;
} changeDimNodeType;

typedef struct {
    char *varName;
    std::vector<int> *indexes;
} accessVarNodeType;

typedef struct {
    struct nodeTypeTag *conditionStmt;
    bool condition1;
    bool condition2;
    std::vector<struct nodeTypeTag *> *statements1;
    std::vector<struct nodeTypeTag *> *statements2;
} switchNodeType;

typedef struct {
    char *counterName;
    char *boundName;
    char *stepName;
    std::vector<struct nodeTypeTag *> *statements;
} cycleNodeType;

typedef struct nodeTypeTag {
    nodeEnum type;              /* type of node */

    union {
        intNodeType con;        /* constants */
        boolNodeType boolVal;   /* bools */
        varNameNodeType varName;          /* identifiers */
        oprNodeType opr;        /* operators */
        varDeclarationNodeType varDeclaration;      /*var declarations*/
        funcDeclarationNodeType funcDeclaration;
        funcCallNodeType funcCall;
        changeDimNodeType changeDim;
        accessVarNodeType accessVar;
        switchNodeType switchStmt;
        cycleNodeType cycle;
    };
} nodeType;

typedef std::vector<nodeType *> stmtsListType;

extern int sym[26];

#endif // CODEPROC_H
