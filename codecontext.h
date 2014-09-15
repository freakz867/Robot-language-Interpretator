#ifndef CODECONTEXT_H
#define CODECONTEXT_H
#include <map>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include "codeproc.h"
#include "robotParser.h"
#include "field/qgameplace.h"
#define ASSIGNSIZE 1004
#define ACCESS 1005
#define ASSIGNACCESS 1006
using namespace std;
/* Type: BOOL:0 ; INT:1 */
class QRobot;
class QLabyrinth;
class Value{
public:
    int type;                               /* type of variable */
    int **data;                             /* data */
    int ndim;                               /* number of dimensions */
    int *dim;                               /* dimensions (expandable) */
    Value();
    Value(int newType, int newDefault);
    Value(int newType, int newDefault, int ndim, int *dim);
    Value(int newType, int newDefault, int ndim, dimListType *dim);
    Value(int ndim);                    //for access type
    Value(const Value&);
    void printValue();
    Value& operator=(const Value& right);
    addressListType *index(dimListType *indexes);
    ~Value();
};

class Function{
public:
    Function();
    ~Function();
    Function(const Function &);
    int createLocalVar(const varDeclarationNodeType *varInfo);
    bool checkResultOper()const;                                    // return true if RESULT statement there
    Value *findArgs(string);
    Value *findLocals(string);
    string Name;
    map<string, Value*> locals;     //local variables
    map<string, Value*> args;       //arguments
    vector<nodeType*> stmts;        //statements
    int numOfArgs;                  //number of arguments
    nodeType *entryPoint;           //first statement in function
    Value *lastCallResult;          //variable that contain result from last call
};

class codeContext
{
public:
    codeContext();
    ~codeContext();
    codeContext(const codeContext &);
    int createGlobalVar(const varDeclarationNodeType *varInfo);
    Value *findGlobals(string varInfo);
    Value *isDefined(string);
    Value *getValue(char *);

    map<string, Value*> globals;            //global variables
    map<string, Function*> FunctionsList;   //list of functions
    void viewFunctions();                   //test view
    Function *find(string);
    int politeness;                         //politeness indicator
    int mood;
    QRobot *robot;
    int executeMainCode();
    int initializeRobot(QLabyrinth *labyrinth);
    int ex(nodeType *p);
    Value *exReturn(nodeType *p);
    Function *currentExecFunction;

    /* operators section */
    int returnOperator(char *varName);
    Value *sizeOperator(char *varName);
    Function *callFunction(const funcCallNodeType *callInfo);
    Value *getOperator(char *funcName);
    int logitizeOperator(char *varName);
    int digitizeOperator(char *varName);
    int assignOperator(char *varName,nodeType *p);
    int assignOperator(nodeType *p1,nodeType *p2);
    Value *reduceOperator(char *varName, dimListType *dimList);
    Value *extendOperator(char *varName, dimListType *dimList);
    bool mxeqOperator(char *varName);
    bool mxltOperator(char *varName);
    bool mxgtOperator(char *varName);
    bool mxlteOperator(char *varName);
    bool mxgteOperator(char *varName);
    bool mxtrueOperator(char *varName);
    bool mxfalseOperator(char *varName);
    Value *eleqOperator(char *varName);
    Value *elltOperator(char *varName);
    Value *elgtOperator(char *varName);
    Value *ellteOperator(char *varName);
    Value *elgteOperator(char *varName);
    int switchOperator(const switchNodeType *switchInfo);
    int cycleOperator(const cycleNodeType *switchInfo);
    Value *accessOperator(char *varName, dimListType *indexesList);
    Value *doubleAccessOperator(char *varName, Value *addressesValue);
    Value *plusOperator(Value *left, Value *right);
    Value *minusOperator(Value *left, Value *right);
    Value *multiplyOperator(Value *left, Value *right);
    Value *divideOperator(Value *left, Value *right);
    Value *unaryMinusOperator(Value *right);
    int leftRotateOperator();
    int rightRotateOperator();
    Value *getEnvOperator();
};

extern codeContext context;

#endif // CODECONTEXT_H
