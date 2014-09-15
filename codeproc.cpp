#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "codeproc.h"
#include "robotParser.h"
#include "codecontext.h"

codeContext context;

/* PROCESSING CODE CONTEXT
 * DOMAIN - visibility of variable: 1 - local, 0 - global
 * CODECONTEXT - current program context
*/
int addFunction(const funcDeclarationNodeType *func);



int addFunction(const funcDeclarationNodeType *func){
    Function *newFunction=new Function();
    int argsSize=func->args->size();
    for(int i=0;i<argsSize;++i){
        Value *newValue=new Value(0,0);
        newFunction->args.insert(std::pair<string,Value *>(func->args->at(i),newValue));
    }
    int stmtsSize=func->statements->size();
    for(int i=0;i<stmtsSize;++i){
        newFunction->stmts.push_back(func->statements->at(i));
    }
    newFunction->Name=func->funcName;
    context.FunctionsList.insert(std::pair<string, Function*>(func->funcName,newFunction));

    //test view
    int ndim=func->args->size();
    printf("\ntest view of arguments\n");
    for (int i = 0; i < ndim; i++){
        printf("%s ",func->args->at(i));
    }
}
