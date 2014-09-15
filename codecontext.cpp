#include "codecontext.h"

codeContext::codeContext()
{
}

codeContext::~codeContext(){
    for(map<string,Value *>::iterator itr=globals.begin();itr!=globals.end();++itr)
    {
        delete (*itr).second;
        globals.erase(itr);
    }
    /*for(map<string,Function *>::iterator itr=FunctionsList.begin();itr!=FunctionsList.end();++itr)
    {
        delete (*itr).second;
        FunctionsList.erase(itr);
    }*/
}

//test view
void codeContext::viewFunctions(){
    for(map<string,Function*>::iterator itr = FunctionsList.begin(); itr!=FunctionsList.end(); ++itr){
            cout<<" Function name: "<<(*itr).first<<endl;
        }
}

int codeContext::createGlobalVar(const varDeclarationNodeType *varInfo){
    if(varInfo->ndim==0){
        //printf("enter to creation of var %s",varInfo->varName);             //test view
        Value *newVar = new Value(varInfo->defaultType,varInfo->defaultValue);
        globals.insert(std::pair<string,Value *>(varInfo->varName,newVar));
        //newVar->printValue();
    }
    else{
        Value *newVar = new Value(varInfo->defaultType,varInfo->defaultValue,varInfo->ndim,varInfo->dim);
        globals.insert(std::pair<string,Value *>(varInfo->varName,newVar));
        //newVar->printValue();
    }
}

Value *codeContext::findGlobals(string key){
    map<string,Value *>::const_iterator search = globals.find(key);
    if(search != globals.end()) {
            return search->second;
    }
        else return NULL;
}

Value *codeContext::isDefined(string varName){
    Value *temp=currentExecFunction->findLocals(varName);
    if(temp!=NULL){
        return temp;
    }
    else{
        temp=currentExecFunction->findArgs(varName);
        if(temp!=NULL){
            return temp;
        }
        else{
            temp=findGlobals(varName);
            if(temp!=NULL)
                return temp;
            else
                return NULL;
        }
    }
}

Value *codeContext::getValue(char *varName){
    Value *result=isDefined(varName);
    if(result!=NULL){
        return result;
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

int codeContext::executeMainCode(){
    Function *findExit=find("FINDEXIT");
    if(findExit==NULL){
        fprintf(stderr, "Error: You have not defined FINDEXIT function\n" );
        return -1;
    }
    else{
        currentExecFunction=findExit;
        if(!currentExecFunction->checkResultOper()){
            fprintf(stderr, "In function %s:\nError: missing RESULT statement\n", currentExecFunction->Name.c_str());
            exit(0);
        }
        else{
            int stmtsSize=findExit->stmts.size();
            for(int i=0;i<stmtsSize;++i){
                //printf("\n\ntesting executing: \n\n\n\n\n");                //test view
                ex(findExit->stmts.at(i));
                //printf("\n\n");
            }
        }
    }
}

int codeContext::initializeRobot(QLabyrinth *labyrinth){
    ifstream file;
    file.open("labyrinth.map", ios::in);
    int newx,newy;
    file >> newx >> newy;
    file.close();
    QPoint *robotPos=new QPoint;
    robotPos->setX(newx);
    robotPos->setY(newy);
    robot = new QRobot(*robotPos,labyrinth);
}

/* LOGITIZE = 1
 * DIGITIZE = 2
*/

int codeContext::ex(nodeType *p){
    if (!p) return 0;
    switch(p->type) {
    case typeBool:      return p->boolVal.value;
    //case typeVarName:        printf("View var name: %s\n",p->varName.Name); return 0;            //test view
    case typeVarDeclaration: currentExecFunction->createLocalVar(&(p->varDeclaration)); return 0;
    case typeFuncDeclaration: return 0;
    case typeFuncCall:  currentExecFunction=callFunction(&(p->funcCall)); return 0;
    case typeSwitch:    switchOperator(&(p->switchStmt)); return 0;
    case typeCycle:     cycleOperator(&(p->cycle)); return 0;
    case typeOpr:
        switch(p->opr.oper) {
        //case GETENVIRONMENT: getEnvOperator()->printValue(); return 0;
        case WATCH:     printf("\n\nTEST watch %d\n\n", ex(p->opr.op[0])); return 0;        //test view
        case MOVEOP:    {
            if(p->opr.op[0]->con.value==1) return robot->moveRobot();
            if(p->opr.op[0]->con.value==2) return leftRotateOperator();
            if(p->opr.op[0]->con.value==3) return rightRotateOperator();
        }
        //case FSIZE:     sizeOperator(p->opr.op[0]->varName.Name); return 0;
        case NOT:       return !ex(p->opr.op[0]);
        case AND:       return ex(p->opr.op[0]) & ex(p->opr.op[1]);
        case RESULT:    returnOperator(p->opr.op[0]->varName.Name); break; return 0;
        case TYPECONVERSION: {
            if(p->opr.op[0]->con.value==1) return logitizeOperator(p->opr.op[1]->varName.Name);
            if(p->opr.op[0]->con.value==2) return digitizeOperator(p->opr.op[1]->varName.Name);
        }
        case MXLOGIC:   {
            if(p->opr.op[0]->con.value==1) return mxtrueOperator(p->opr.op[1]->varName.Name);
            if(p->opr.op[0]->con.value==2) return mxfalseOperator(p->opr.op[1]->varName.Name);
        }
        case NULLCOMPARE: {
            switch(p->opr.op[0]->con.value){
            case 1: return mxeqOperator(p->opr.op[1]->varName.Name);
            case 2: return mxltOperator(p->opr.op[1]->varName.Name);
            case 3: return mxgtOperator(p->opr.op[1]->varName.Name);
            case 4: return mxlteOperator(p->opr.op[1]->varName.Name);
            case 5: return mxgteOperator(p->opr.op[1]->varName.Name);
            }
        }
        case ASSIGNSIZE: assignOperator(p->opr.op[0]->varName.Name, p->opr.op[1]); return 0;
        case ASSIGNACCESS: assignOperator(p->opr.op[0], p->opr.op[1]); return 0;
        }
    }
    return 0;
}

Value *codeContext::exReturn(nodeType *p){
    if (!p) {
        fprintf(stderr, "In function %s:\nError: invalid action\n",currentExecFunction->Name.c_str());
        exit(0);
    }

    switch(p->type) {
    case typeCon:       return new Value (1,p->con.value);
    case typeVarName:   return getValue(p->varName.Name);
        //case typeAccessVar: return accessOperator(p->accessVar.varName,p->accessVar.indexes);
    case typeChangeDim: {
        if(p->changeDim.opId==1) return reduceOperator(p->changeDim.varName,p->changeDim.dimensions);
        if(p->changeDim.opId==2) return extendOperator(p->changeDim.varName,p->changeDim.dimensions);
    }
    case typeOpr:
        switch(p->opr.oper) {
        case ACCESS:    {
            if(p->opr.op[0]==NULL) return accessOperator(p->opr.op[1]->accessVar.varName, p->opr.op[1]->accessVar.indexes);
            else return doubleAccessOperator(p->opr.op[0]->varName.Name,exReturn(p->opr.op[1]));
        }
        case GETENVIRONMENT: return getEnvOperator();
        case UMINUS:    return unaryMinusOperator(exReturn(p->opr.op[0]));
        case '+':       return plusOperator(exReturn(p->opr.op[0]),exReturn(p->opr.op[1]));
        case '-':       return minusOperator(exReturn(p->opr.op[0]),exReturn(p->opr.op[1]));
        case '*':       return multiplyOperator(exReturn(p->opr.op[0]),exReturn(p->opr.op[1]));
        case '/':       return divideOperator(exReturn(p->opr.op[0]),exReturn(p->opr.op[1]));
        case FSIZE:     return sizeOperator(p->opr.op[0]->varName.Name);
        case GET:       return getOperator(p->opr.op[0]->varName.Name);
        case ELEMNULLCOMPARE: {
            switch(p->opr.op[0]->con.value){
            case 1: printf("testing eleq: "); return eleqOperator(p->opr.op[1]->varName.Name);
            case 2: printf("testing ellt: "); return elltOperator(p->opr.op[1]->varName.Name);
            case 3: printf("testing elgt: "); return elgtOperator(p->opr.op[1]->varName.Name);
            case 4: printf("testing ellte: "); return ellteOperator(p->opr.op[1]->varName.Name);
            case 5: printf("testing elgte: "); return elgteOperator(p->opr.op[1]->varName.Name);
            }
        }
        }
    }
}

Function *codeContext::find(string key){
    map<string,Function *>::const_iterator search = FunctionsList.find(key);
    if(search != FunctionsList.end()) {
            return search->second;
    }
        else return NULL;
}

Function::Function(){
    entryPoint=NULL;
    Value *lastCallResult=new Value;
}

Function::~Function(){
    delete lastCallResult;
    entryPoint=NULL;
    for(map<string,Value *>::iterator itr=locals.begin();itr!=locals.end();++itr)
    {
        delete (*itr).second;
        locals.erase(itr);
    }
    for(map<string,Value *>::iterator itr=args.begin();itr!=args.end();++itr)
    {
        delete (*itr).second;
        args.erase(itr);
    }
    stmts.clear();
}

Function::Function(const Function &orig):locals(orig.locals), args(orig.args), stmts(orig.stmts), numOfArgs(orig.numOfArgs), Name(orig.Name){
    entryPoint=new nodeType;
    entryPoint=orig.entryPoint;
    if(orig.lastCallResult!=NULL)
        lastCallResult=new Value(*(orig.lastCallResult));
    else
        lastCallResult=NULL;
}

Value *Function::findArgs(string key){
    map<string,Value *>::const_iterator search = args.find(key);
    if(search != args.end()) {
            return search->second;
    }
        else return NULL;
}

Value *Function::findLocals(string key){
    map<string,Value *>::const_iterator search = locals.find(key);
    if(search != locals.end()) {
            return search->second;
    }
        else return NULL;
}


int Function::createLocalVar(const varDeclarationNodeType *varInfo){

    //printf("enter to creation of var %s\n", varInfo->varName);         //test view
    if(findLocals(varInfo->varName)!=NULL){
        fprintf(stderr, "In function %s:\nError: redeclaration of %s\n", Name.c_str(), varInfo->varName);
        exit(0);
    }
    else
        if(findArgs(varInfo->varName)!=NULL){
            fprintf(stderr, "In function %s:\nError: declaration of %s shadows a parameter\n", Name.c_str(), varInfo->varName);
            exit(0);
        }
        else{
            if(varInfo->ndim==0){
                Value *newVar = new Value(varInfo->defaultType, varInfo->defaultValue);
                locals.insert(std::pair<string,Value *>(varInfo->varName, newVar));
                //newVar->printValue();       //test view
                return 0;
            }
            else{
                Value *newVar = new Value(varInfo->defaultType, varInfo->defaultValue, varInfo->ndim, varInfo->dim);
                locals.insert(std::pair<string,Value *>(varInfo->varName, newVar));
                //newVar->printValue();       //test view
                return 0;
            }
        }
}

bool Function::checkResultOper()const{
    int stmtsSize=stmts.size();
    for(int i=0;i<stmtsSize;++i){
        if(stmts.at(i)->type==typeOpr)
            if(stmts.at(i)->opr.oper==RESULT)
                return true;
    }
    return false;
}


Value::Value(){
    dim=NULL;
    data=NULL;
}

Value::Value(int newType, int newDefault){
        //printf("creating value\n");         //test view
       type=newType;
            ndim=1;
            dim = new int [ndim];
            dim[0]=1;
            data = new int *[1];
            data[0] = new int [1];
            data[0][0]=newDefault;
}

Value::Value(int newType, int newDefault, int ndim, int *dim){
    type=newType;
    (*this).ndim=ndim;
    (*this).dim = new int [ndim];
    data = new int *[ndim];
    for(int count = 0; count < ndim; count++){
        (*this).dim[count]=dim[count];              //copying dimensions array
        data[count]= new int [dim[count]];
    }
    int count_row=0;
    for (count_row; count_row < ndim; count_row++)
        for (int count_column = 0; count_column < dim[count_row]; count_column++)
                data[count_row][count_column] = newDefault;
}

Value::Value(int newType, int newDefault, int ndim, dimListType *dim){
    type=newType;
    (*this).ndim=ndim;
    (*this).dim = new int [ndim];
    data = new int *[ndim];
    for(int count = 0; count < ndim; count++){
        (*this).dim[count]=(*dim)[count];              //copying dimensions array
        data[count]= new int [(*dim)[count]];
    }
    int count_row=0;
    for (count_row; count_row < ndim; count_row++)
        for (int count_column = 0; count_column < (*dim)[count_row]; count_column++)
                data[count_row][count_column] = newDefault;
}

void Value::printValue(){
    int count_row=0;
    cout<<endl;
    for (count_row; count_row < ndim; count_row++)
        {
        for (int count_column = 0; count_column < dim[count_row]; count_column++)
                cout<<data[count_row][count_column] << "   ";
            cout << endl;
        }
}

Value::Value(const Value &orig):type(orig.type), ndim(orig.ndim){
    dim=new int [orig.ndim];
    data = new int *[ndim];
    for(int count = 0; count < ndim; count++){
        dim[count]=orig.dim[count];
        data[count]= new int [dim[count]];
    }

    int count_row=0;
    for (count_row; count_row < ndim; count_row++)
        for (int count_column = 0; count_column < dim[count_row]; count_column++)
                data[count_row][count_column] = orig.data[count_row][count_column];

}

Value& Value::operator =(const Value& right){
    if (this == &right) {
        return *this;
    }
    if(type!=right.type){
        fprintf(stderr, "In function %s:\nError: mismatch types in assignment operands\n",context.currentExecFunction->Name.c_str());
        exit(0);
    }
    if(ndim!=right.ndim){
        fprintf(stderr, "In function %s:\nError: mismatch dimension number in assignment operands\n",context.currentExecFunction->Name.c_str());
        exit(0);
    }
    for(int count = 0; count < ndim; count++){
        if(dim[count]!=right.dim[count]){
            fprintf(stderr, "In function %s:\nError: mismatch dimensions in assignment operands\n",context.currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    int count_row=0;
    for (count_row; count_row < ndim; count_row++)
        for (int count_column = 0; count_column < dim[count_row]; count_column++)
                data[count_row][count_column] = right.data[count_row][count_column];
    return *this;
}

Value::Value(int ndim){
        data = new int *[ndim];
        (*this).ndim=ndim;
        dim=NULL;
        type=2;     //accessVary
}

addressListType *Value::index(dimListType *indexes){
    if(ndim<indexes->size()){
        fprintf(stderr, "In function %s:\nError: number of indexes more than number of var dimensions\n",context.currentExecFunction->Name.c_str());
        exit(0);
    }
    addressListType *newValues=new addressListType();
    for(int count = 0; count < indexes->size(); count++){
        if(dim[count]<indexes->at(count)){
            fprintf(stderr, "In function %s:\nError: index %d more than var dimension\n",context.currentExecFunction->Name.c_str(), indexes->at(count));
            exit(0);
        }
        newValues->push_back(&data[count][indexes->at(count)-1]);
    }
    for(int count=indexes->size();count <ndim;++count)
        newValues->push_back(&data[count][0]);
    return newValues;

}

Value::~Value(){
    for (int count = 0; count < ndim; count++)
            delete []data[count];
}


int codeContext::returnOperator(char *varName){
    Value *result=currentExecFunction->findLocals(varName);
    if(result!=NULL){
        find(currentExecFunction->Name)->lastCallResult=new Value(*result);
        currentExecFunction->lastCallResult=new Value(*result);
        //printf("testing result operator\n");                //test view
        currentExecFunction->lastCallResult->printValue();
        return 0;
    }
    else{
        result=currentExecFunction->findArgs(varName);
        if(result!=NULL){
            find(currentExecFunction->Name)->lastCallResult=new Value(*result);
            currentExecFunction->lastCallResult=new Value(*result);
            //printf("testing result operator\n");                //test view
            currentExecFunction->lastCallResult->printValue();
            return 0;
        }
        else{
            fprintf(stderr, "In function %s:\nError: %s was not declared in this scope\n",currentExecFunction->Name.c_str(), varName);
            exit(0);
        }
    }
}

Value *codeContext::sizeOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        int ndim=temp->ndim;
        Value *result=new Value(1,0,1,&ndim);
        for (int count_column = 0; count_column < ndim; count_column++)
                result->data[0][count_column] = temp->dim[count_column];
        result->printValue();                   //test view
        return result;
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }

}

Function *codeContext::callFunction(const funcCallNodeType *callInfo){
    Function *temp=currentExecFunction;

    Function *newFunction=find(callInfo->Name);
    if(newFunction==NULL){
        fprintf(stderr, "Error: You have not defined %s function\n", callInfo->Name );
        exit(0);
    }
    else{
        int argsSize=callInfo->args->size();
        if(newFunction->args.size()!=argsSize){
            fprintf(stderr, "In function %s:\nError: wrong number of arguments in calling function %s\n",currentExecFunction->Name.c_str(), newFunction->Name.c_str());
            exit(0);
        }
        else{
            Function *currentFunction=new Function(*newFunction);
            int argsSize=callInfo->args->size();
            map<string,Value *>::iterator index = currentFunction->args.begin();
            for(int i=0;i<argsSize;++i){
                Value *tempArg=isDefined(callInfo->args->at(i));
                if(tempArg==NULL){
                    fprintf(stderr, "In function %s:\nError:%s was not declared in  this scope\n",currentExecFunction->Name.c_str(), callInfo->args->at(i));
                    exit(0);
                }
                else{
                    (*index).second=tempArg;
                    ++index;
                }
            }

            currentExecFunction=currentFunction;
            int stmtsSize=newFunction->stmts.size();
            for(int i=0;i<stmtsSize;++i){
                //printf("\n\ntesting executing: \n\n");                //test view
                ex(newFunction->stmts.at(i));
                //printf("\n\n");
            }
            return temp;
        }
    }
}

Value *codeContext::getOperator(char *funcName){
    Function *temp=find(funcName);
    if(temp==NULL){
        fprintf(stderr, "In function %s:\nError: %s was not declared as function\n",currentExecFunction->Name.c_str(), funcName);
        exit(0);
    }
    else{
        if(temp->lastCallResult==NULL){
            fprintf(stderr, "In function %s:\nError: function %s not yet been called, there is no result\n",currentExecFunction->Name.c_str(), funcName);
            exit(0);
        }
        else return temp->lastCallResult;
    }
}

int codeContext::logitizeOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        if(temp->type==1){
            int count_row=0;
            for (count_row; count_row < temp->ndim; count_row++)
                for (int count_column = 0; count_column < temp->dim[count_row]; count_column++){
                    if(temp->data[count_row][count_column]!=0)
                        temp->data[count_row][count_column] = 1;
                    else
                        temp->data[count_row][count_column] = 0;
                }
            temp->type=0;
            printf("test LOGITIZE\n");      //test view
            temp->printValue();
            return 0;
        }
        else{
            fprintf(stderr, "In function \"%s\":\nError: type of var \"%s\" is not integer\n",currentExecFunction->Name.c_str(), varName);
            exit(0);
        }
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

int codeContext::digitizeOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        if(temp->type==0){
            temp->type=1;
            printf("test DIGITIZE\n");      //test view
            temp->printValue();
            return 0;
        }
        else{
            fprintf(stderr, "In function \"%s\":\nError: type of var \"%s\" is not boolean\n",currentExecFunction->Name.c_str(), varName);
            exit(0);
        }
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

int codeContext::assignOperator(char *varName, nodeType *p){
    Value *left=isDefined(varName);
    if(left!=NULL){
        //printf("test assign\n");
        Value *right=exReturn(p);
        (*left)=(*right);
        left->printValue();
        return 0;
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

int codeContext::assignOperator(nodeType *p1, nodeType *p2){
    Value *left=exReturn(p1);
    //printf("test assign\n");
    Value *right=exReturn(p2);
    if(left->type==2 && right->type==1){
        if(left->ndim==right->dim[0] && right->ndim==1){
            for (int count_column = 0; count_column < left->ndim; count_column++)
                *(left->data[count_column])=right->data[0][count_column];
            //left->printValue();
            return 0;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==1 && right->type==1){
        (*left)=(*right);
        return 0;
    }
    if(left->type==1 && right->type==2 ){
        if(left->dim[0]==right->ndim && left->ndim==1){
            for (int count_column = 0; count_column < left->dim[0]; count_column++)
                left->data[0][count_column]=*(right->data[count_column]);
            //left->printValue();
            //isDefined("res1")->printValue();
            return 0;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==2 && right->type==2){
        if(left->ndim==right->ndim){
            for (int count_column = 0; count_column < left->ndim; count_column++)
                *(left->data[count_column])=*(right->data[count_column]);
            //left->printValue();
            return 0;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
}


Value *codeContext::reduceOperator(char *varName, dimListType *dimList){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        int ndim=dimList->size();
        if(temp->ndim>ndim){
            for(int count=0;count<ndim;++count){
                if((*dimList)[count] > temp->dim[count]){
                    fprintf(stderr, "In function \"%s\":\nError: dimension of var \"%s\" less than reduce value\n",currentExecFunction->Name.c_str(), varName);
                    exit(0);
                }
            }
            Value *result=new Value(temp->type,0,ndim,dimList);
            int count_row=0;
            for (count_row; count_row < result->ndim; count_row++)
                for (int count_column = 0; count_column < result->dim[count_row]; count_column++)
                    result->data[count_row][count_column] = temp->data[count_row][count_column];
            result->printValue();                   //test view
            return result;
        }
        else{
            fprintf(stderr, "In function \"%s\":\nError: number of dimensions of var \"%s\" less than reduce value\n",currentExecFunction->Name.c_str(), varName);
            exit(0);
        }
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

Value *codeContext::extendOperator(char *varName, dimListType *dimList){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        int ndim=dimList->size();
        for(int count=0;count<ndim;++count){
            if((*dimList)[count] < temp->dim[count]){
                fprintf(stderr, "In function \"%s\":\nError: dimension of var \"%s\" more than extend value\n",currentExecFunction->Name.c_str(), varName);
                exit(0);
            }
        }
        Value *result=new Value(temp->type,0,ndim,dimList);
        int count_row=0;
        for (count_row; count_row < result->ndim; count_row++)
            for (int count_column = 0; count_column < result->dim[count_row]; count_column++){
                if(count_row<temp->ndim)
                    if(count_column<temp->dim[count_row])
                        result->data[count_row][count_column] = temp->data[count_row][count_column];
                    else{
                        if(result->type==0)
                            result->data[count_row][count_column]=true;
                        if(result->type==1)
                            result->data[count_row][count_column]=0;
                    }
            }
        result->printValue();                   //test view
        return result;
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}


bool codeContext::mxeqOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        if(temp->type==1){
        int numElems=0, numRes=0;
        int ndim=temp->ndim;
        for (int count_column = 0; count_column < ndim; count_column++)
            numElems+=temp->dim[count_column];
        int count_row=0;
        for (count_row; count_row < temp->ndim; count_row++)
            for (int count_column = 0; count_column < temp->dim[count_row]; count_column++){
                    if(temp->data[count_row][count_column]==0){
                        ++numRes;
                    }
            }
        if(((numElems/2)+1)>numRes)
            return false;
        else
            return true;
        }
        else{
            fprintf(stderr, "In function \"%s\":\nError: \"%s\" is not integer value\n",currentExecFunction->Name.c_str(), varName);
            exit(0);
        }
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

bool codeContext::mxltOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        if(temp->type==1){
        int numElems=0, numRes=0;
        int ndim=temp->ndim;
        for (int count_column = 0; count_column < ndim; count_column++)
            numElems+=temp->dim[count_column];
        int count_row=0;
        for (count_row; count_row < temp->ndim; count_row++)
            for (int count_column = 0; count_column < temp->dim[count_row]; count_column++){
                    if(temp->data[count_row][count_column]<0){
                        ++numRes;
                    }
            }
        if(((numElems/2)+1)>numRes)
            return false;
        else
            return true;
        }
        else{
            fprintf(stderr, "In function %s:\nError: %s is not integer value\n",currentExecFunction->Name.c_str(), varName);
            exit(0);
        }
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

bool codeContext::mxgtOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        if(temp->type==1){
        int numElems=0, numRes=0;
        int ndim=temp->ndim;
        for (int count_column = 0; count_column < ndim; count_column++)
            numElems+=temp->dim[count_column];
        int count_row=0;
        for (count_row; count_row < temp->ndim; count_row++)
            for (int count_column = 0; count_column < temp->dim[count_row]; count_column++){
                    if(temp->data[count_row][count_column]>0){
                        ++numRes;
                    }
            }
        if(((numElems/2)+1)>numRes)
            return false;
        else
            return true;
        }
        else{
            fprintf(stderr, "In function %s:\nError: %s is not integer value\n",currentExecFunction->Name.c_str(), varName);
            exit(0);
        }
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

bool codeContext::mxlteOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        if(temp->type==1){
        int numElems=0, numRes=0;
        int ndim=temp->ndim;
        for (int count_column = 0; count_column < ndim; count_column++)
            numElems+=temp->dim[count_column];
        int count_row=0;
        for (count_row; count_row < temp->ndim; count_row++)
            for (int count_column = 0; count_column < temp->dim[count_row]; count_column++){
                    if(temp->data[count_row][count_column]==0 || temp->data[count_row][count_column]<0){
                        ++numRes;
                    }
            }
        if(((numElems/2)+1)>numRes)
            return false;
        else
            return true;
        }
        else{
            fprintf(stderr, "In function %s:\nError: %s is not integer value\n",currentExecFunction->Name.c_str(), varName);
            exit(0);
        }
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

bool codeContext::mxgteOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        if(temp->type==1){
        int numElems=0, numRes=0;
        int ndim=temp->ndim;
        for (int count_column = 0; count_column < ndim; count_column++)
            numElems+=temp->dim[count_column];
        int count_row=0;
        for (count_row; count_row < temp->ndim; count_row++)
            for (int count_column = 0; count_column < temp->dim[count_row]; count_column++){
                    if(temp->data[count_row][count_column]==0 || temp->data[count_row][count_column]>0){
                        ++numRes;
                    }
            }
        if(((numElems/2)+1)>numRes)
            return false;
        else
            return true;
        }
        else{
            fprintf(stderr, "In function %s:\nError: %s is not integer value\n",currentExecFunction->Name.c_str(), varName);
            exit(0);
        }
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

Value *codeContext::eleqOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        Value *result=new Value(*temp);
        result->type=0;
        int count_row=0;
        for (count_row; count_row < temp->ndim; count_row++)
            for (int count_column = 0; count_column < temp->dim[count_row]; count_column++){
                if(temp->data[count_row][count_column]==0)
                    result->data[count_row][count_column]=true;
                else
                    result->data[count_row][count_column]=false;
            }
        return result;
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

Value *codeContext::elltOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        Value *result=new Value(*temp);
        result->type=0;
        int count_row=0;
        for (count_row; count_row < temp->ndim; count_row++)
            for (int count_column = 0; count_column < temp->dim[count_row]; count_column++){
                if(temp->data[count_row][count_column]<0)
                    result->data[count_row][count_column]=true;
                else
                    result->data[count_row][count_column]=false;
            }
        return result;
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

Value *codeContext::elgtOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        Value *result=new Value(*temp);
        result->type=0;
        int count_row=0;
        for (count_row; count_row < temp->ndim; count_row++)
            for (int count_column = 0; count_column < temp->dim[count_row]; count_column++){
                if(temp->data[count_row][count_column]>0)
                    result->data[count_row][count_column]=true;
                else
                    result->data[count_row][count_column]=false;
            }
        return result;
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

Value *codeContext::ellteOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        Value *result=new Value(*temp);
        result->type=0;
        int count_row=0;
        for (count_row; count_row < temp->ndim; count_row++)
            for (int count_column = 0; count_column < temp->dim[count_row]; count_column++){
                if(temp->data[count_row][count_column]==0 || temp->data[count_row][count_column]<0)
                    result->data[count_row][count_column]=true;
                else
                    result->data[count_row][count_column]=false;
            }
        return result;
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

Value *codeContext::elgteOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        Value *result=new Value(*temp);
        result->type=0;
        int count_row=0;
        for (count_row; count_row < temp->ndim; count_row++)
            for (int count_column = 0; count_column < temp->dim[count_row]; count_column++){
                if(temp->data[count_row][count_column]==0 || temp->data[count_row][count_column]>0)
                    result->data[count_row][count_column]=true;
                else
                    result->data[count_row][count_column]=false;
            }
        return result;
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

int codeContext::switchOperator(const switchNodeType *switchInfo){
    if(switchInfo->statements2==NULL){          //without "else" statement
        if(ex(switchInfo->conditionStmt)==switchInfo->condition1){
            int stmtsSize=switchInfo->statements1->size();
            for(int i=0;i<stmtsSize;++i){
                ex(switchInfo->statements1->at(i));
            }
            return 0;
        }
    }
    else{
        if(ex(switchInfo->conditionStmt)==switchInfo->condition1){
            int stmtsSize=switchInfo->statements1->size();
            for(int i=0;i<stmtsSize;++i){
                ex(switchInfo->statements1->at(i));
            }
            return 0;
        }
        else{
            if(ex(switchInfo->conditionStmt)==switchInfo->condition2){
                int stmtsSize=switchInfo->statements2->size();
                for(int i=0;i<stmtsSize;++i){
                    ex(switchInfo->statements2->at(i));
                }
                return 0;
            }
            else{
                fprintf(stderr, "In function %s:\nError: switch condition is not boolean\n",currentExecFunction->Name.c_str());
                exit(0);
            }
        }
    }
}

int codeContext::cycleOperator(const cycleNodeType *switchInfo){
    int localHysteriaFactor=500+rand() %10000;
    int hysteriaCounter=0;
    Value *counter=isDefined(switchInfo->counterName);
    Value *bound=isDefined(switchInfo->boundName);
    Value *step=isDefined(switchInfo->stepName);
    if(counter!=NULL && bound!=NULL && step!=NULL){
        int count_row=0;
        for (count_row; count_row < counter->ndim; count_row++)
            for (int count_column = 0; count_column < counter->dim[count_row]; count_column++){

                for(int i=counter->data[count_row][count_column]; i<bound->data[count_row][count_column]; i+=step->data[count_row][count_column]){
                    int stmtsSize=switchInfo->statements->size();

                    for(int i=0;i<stmtsSize;++i){
                        if(hysteriaCounter<localHysteriaFactor)
                            ex(switchInfo->statements->at(i));
                        else
                            exit(0);
                        ++hysteriaCounter;
                    }
                    counter->data[count_row][count_column]+=step->data[count_row][count_column];
                }
            }
    }
    else{
        fprintf(stderr, "In function %s:\nError: something was not declared in  this scope\n",currentExecFunction->Name.c_str());
        exit(0);
    }
}


bool codeContext::mxfalseOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        if(temp->type==0){
        int numElems=0, numRes=0;
        int ndim=temp->ndim;
        for (int count_column = 0; count_column < ndim; count_column++)
            numElems+=temp->dim[count_column];
        int count_row=0;
        for (count_row; count_row < temp->ndim; count_row++)
            for (int count_column = 0; count_column < temp->dim[count_row]; count_column++){
                    if(temp->data[count_row][count_column]==false){
                        ++numRes;
                    }
            }
        if(((numElems/2)+1)>numRes)
            return false;
        else
            return true;
        }
        else{
            fprintf(stderr, "In function \"%s\":\nError: \"%s\" is not boolean value\n",currentExecFunction->Name.c_str(), varName);
            exit(0);
        }
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

bool codeContext::mxtrueOperator(char *varName){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
        if(temp->type==0){
        int numElems=0, numRes=0;
        int ndim=temp->ndim;
        for (int count_column = 0; count_column < ndim; count_column++)
            numElems+=temp->dim[count_column];
        int count_row=0;
        for (count_row; count_row < temp->ndim; count_row++)
            for (int count_column = 0; count_column < temp->dim[count_row]; count_column++){
                    if(temp->data[count_row][count_column]==true){
                        ++numRes;
                    }
            }
        if(((numElems/2)+1)>numRes)
            return false;
        else
            return true;
        }
        else{
            fprintf(stderr, "In function \"%s\":\nError: \"%s\" is not boolean value\n",currentExecFunction->Name.c_str(), varName);
            exit(0);
        }
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

Value *codeContext::accessOperator(char *varName, dimListType *indexesList){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
            addressListType *newValuesAddresses=temp->index(indexesList);
            Value *result=new Value(newValuesAddresses->size());
                for (int count = 0; count < temp->ndim; count++)
                    result->data[count]=newValuesAddresses->at(count);
            return result;
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}

Value *codeContext::doubleAccessOperator(char *varName, Value *addressesValue){
    Value *temp=isDefined(varName);
    if(temp!=NULL){
            dimListType *indexesList=new dimListType;
            int ndim = addressesValue->ndim;
            for (int count = 0; count < ndim; count++){
                indexesList->push_back(*(addressesValue->data[count]));
                printf("%d ",indexesList->at(count));
            }
            addressListType *newValuesAddresses=temp->index(indexesList);

            Value *result=new Value(newValuesAddresses->size());
                for (int count = 0; count < temp->ndim; count++)
                    result->data[count]=newValuesAddresses->at(count);
            return result;
    }
    else{
        fprintf(stderr, "In function %s:\nError: %s was not declared in  this scope\n",currentExecFunction->Name.c_str(), varName);
        exit(0);
    }
}


Value *codeContext::plusOperator(Value *left, Value *right){
    if(left->type==2 && right->type==2){
        if(left->ndim==right->ndim){
            Value *result=new Value(1,0,1,&left->ndim);
            for (int count_column = 0; count_column < left->ndim; count_column++){
                result->data[0][count_column]=(*(left->data[count_column]))+(*(right->data[count_column]));
            }
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==2 && right->type==1){
        if(left->ndim==right->dim[0]){
            Value *result=new Value(1,0,1,&left->ndim);
            for (int count_column = 0; count_column < left->ndim; count_column++){
                result->data[0][count_column]=(*(left->data[count_column]))+right->data[0][count_column];
            }
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==1 && right->type==2){
        if(left->dim[0]==right->ndim){
            Value *result=new Value(1,0,1,&right->ndim);
            for (int count_column = 0; count_column < right->ndim; count_column++){
                result->data[0][count_column]=left->data[0][count_column]+(*(right->data[count_column]));
            }
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==1 && right->type==1){
        if(left->ndim==right->ndim){
            Value *result=new Value(1,0,left->ndim,left->dim);

            if(left->type!=right->type){
                fprintf(stderr, "In function %s:\nError: mismatch types in assignment operands\n",context.currentExecFunction->Name.c_str());
                exit(0);
            }
            for(int count = 0; count < left->ndim; count++){
                if(left->dim[count]!=right->dim[count]){
                    fprintf(stderr, "In function %s:\nError: mismatch dimensions in assignment operands\n",context.currentExecFunction->Name.c_str());
                    exit(0);
                }
            }
            int count_row=0;
            for (count_row; count_row < left->ndim; count_row++)
                for (int count_column = 0; count_column < left->dim[count_row]; count_column++)
                    result->data[count_row][count_column] = left->data[count_row][count_column]+right->data[count_row][count_column];
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimension number in assignment operands\n",context.currentExecFunction->Name.c_str());
            exit(0);
        }
    }
}

Value *codeContext::minusOperator(Value *left, Value *right){
    if(left->type==2 && right->type==2){
        if(left->ndim==right->ndim){
            Value *result=new Value(1,0,1,&left->ndim);
            for (int count_column = 0; count_column < left->ndim; count_column++){
                result->data[0][count_column]=(*(left->data[count_column]))-(*(right->data[count_column]));
            }
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==2 && right->type==1){
        if(left->ndim==right->dim[0]){
            Value *result=new Value(1,0,1,&left->ndim);
            for (int count_column = 0; count_column < left->ndim; count_column++){
                result->data[0][count_column]=(*(left->data[count_column]))-right->data[0][count_column];
            }
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==1 && right->type==2){
        if(left->dim[0]==right->ndim){
            Value *result=new Value(1,0,1,&right->ndim);
            for (int count_column = 0; count_column < right->ndim; count_column++){
                result->data[0][count_column]=left->data[0][count_column]-(*(right->data[count_column]));
            }
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==1 && right->type==1){
        if(left->ndim==right->ndim){
            Value *result=new Value(1,0,left->ndim,left->dim);

            if(left->type!=right->type){
                fprintf(stderr, "In function %s:\nError: mismatch types in assignment operands\n",context.currentExecFunction->Name.c_str());
                exit(0);
            }
            for(int count = 0; count < left->ndim; count++){
                if(left->dim[count]!=right->dim[count]){
                    fprintf(stderr, "In function %s:\nError: mismatch dimensions in assignment operands\n",context.currentExecFunction->Name.c_str());
                    exit(0);
                }
            }
            int count_row=0;
            for (count_row; count_row < left->ndim; count_row++)
                for (int count_column = 0; count_column < left->dim[count_row]; count_column++)
                    result->data[count_row][count_column] = left->data[count_row][count_column]-right->data[count_row][count_column];
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimension number in assignment operands\n",context.currentExecFunction->Name.c_str());
            exit(0);
        }
    }
}

Value *codeContext::multiplyOperator(Value *left, Value *right){
    if(left->type==2 && right->type==2){
        if(left->ndim==right->ndim){
            Value *result=new Value(1,0,1,&left->ndim);
            for (int count_column = 0; count_column < left->ndim; count_column++){
                result->data[0][count_column]=(*(left->data[count_column]))*(*(right->data[count_column]));
            }
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==2 && right->type==1){
        if(left->ndim==right->dim[0]){
            Value *result=new Value(1,0,1,&left->ndim);
            for (int count_column = 0; count_column < left->ndim; count_column++){
                result->data[0][count_column]=(*(left->data[count_column]))*right->data[0][count_column];
            }
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==1 && right->type==2){
        if(left->dim[0]==right->ndim){
            Value *result=new Value(1,0,1,&right->ndim);
            for (int count_column = 0; count_column < right->ndim; count_column++){
                result->data[0][count_column]=left->data[0][count_column]*(*(right->data[count_column]));
            }
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==1 && right->type==1){
        if(left->ndim==right->ndim){
            Value *result=new Value(1,0,left->ndim,left->dim);

            if(left->type!=right->type){
                fprintf(stderr, "In function %s:\nError: mismatch types in assignment operands\n",context.currentExecFunction->Name.c_str());
                exit(0);
            }
            for(int count = 0; count < left->ndim; count++){
                if(left->dim[count]!=right->dim[count]){
                    fprintf(stderr, "In function %s:\nError: mismatch dimensions in assignment operands\n",context.currentExecFunction->Name.c_str());
                    exit(0);
                }
            }
            int count_row=0;
            for (count_row; count_row < left->ndim; count_row++)
                for (int count_column = 0; count_column < left->dim[count_row]; count_column++)
                    result->data[count_row][count_column] = left->data[count_row][count_column]*right->data[count_row][count_column];
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimension number in assignment operands\n",context.currentExecFunction->Name.c_str());
            exit(0);
        }
    }
}

Value *codeContext::divideOperator(Value *left, Value *right){
    if(left->type==2 && right->type==2){
        if(left->ndim==right->ndim){
            Value *result=new Value(1,0,1,&left->ndim);
            for (int count_column = 0; count_column < left->ndim; count_column++){
                result->data[0][count_column]=(*(left->data[count_column]))/(*(right->data[count_column]));
            }
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==2 && right->type==1){
        if(left->ndim==right->dim[0]){
            Value *result=new Value(1,0,1,&left->ndim);
            for (int count_column = 0; count_column < left->ndim; count_column++){
                result->data[0][count_column]=(*(left->data[count_column]))/right->data[0][count_column];
            }
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==1 && right->type==2){
        if(left->dim[0]==right->ndim){
            Value *result=new Value(1,0,1,&right->ndim);
            for (int count_column = 0; count_column < right->ndim; count_column++){
                result->data[0][count_column]=left->data[0][count_column]/(*(right->data[count_column]));
            }
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimensions\n",currentExecFunction->Name.c_str());
            exit(0);
        }
    }
    if(left->type==1 && right->type==1){
        if(left->ndim==right->ndim){
            Value *result=new Value(1,0,left->ndim,left->dim);

            if(left->type!=right->type){
                fprintf(stderr, "In function %s:\nError: mismatch types in assignment operands\n",context.currentExecFunction->Name.c_str());
                exit(0);
            }
            for(int count = 0; count < left->ndim; count++){
                if(left->dim[count]!=right->dim[count]){
                    fprintf(stderr, "In function %s:\nError: mismatch dimensions in assignment operands\n",context.currentExecFunction->Name.c_str());
                    exit(0);
                }
            }
            int count_row=0;
            for (count_row; count_row < left->ndim; count_row++)
                for (int count_column = 0; count_column < left->dim[count_row]; count_column++)
                    result->data[count_row][count_column] = left->data[count_row][count_column]/right->data[count_row][count_column];
            return result;
        }
        else{
            fprintf(stderr, "In function %s:\nError: mismatch dimension number in assignment operands\n",context.currentExecFunction->Name.c_str());
            exit(0);
        }
    }
}

Value *codeContext::unaryMinusOperator(Value *right){
    if(right->type==2){
        Value *result=new Value(1,0,1,&right->ndim);
        for (int count_column = 0; count_column < right->ndim; count_column++){
            result->data[0][count_column]=-(*(right->data[count_column]));
        }
        return result;
    }
    if(right->type==1){
        Value *result=new Value(1,0,right->ndim,right->dim);
        int count_row=0;
        for (count_row; count_row < right->ndim; count_row++)
            for (int count_column = 0; count_column < right->dim[count_row]; count_column++)
                result->data[count_row][count_column] = - right->data[count_row][count_column];
        return result;
    }
}

int codeContext::leftRotateOperator(){
    int oldDirection=robot->direction;
    if(oldDirection==2)
        robot->direction=6;
    if(oldDirection==6)
        robot->direction=8;
    if(oldDirection==8)
        robot->direction=4;
    if(oldDirection==4)
        robot->direction=2;
    cout<<"New direction after LEFT: "<<robot->direction<<endl;
}

int codeContext::rightRotateOperator(){
    int oldDirection=robot->direction;
    if(oldDirection==2)
        robot->direction=4;
    if(oldDirection==6)
        robot->direction=2;
    if(oldDirection==8)
        robot->direction=6;
    if(oldDirection==4)
        robot->direction=8;
    cout<<"New direction after RIGHT: "<<robot->direction<<endl;
}

Value *codeContext::getEnvOperator(){
        mood=1;
        Value *result=robot->getPan(mood);
        //result->printValue();
        return result;
}
