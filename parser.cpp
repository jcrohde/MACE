/*
Copyright (C) 2012-2014 Jan Christian Rohde

This file is part of MACE.

MACE is free software; you can redistribute it and/or modify it under the terms of the
GNU General Public License as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

MACE is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MACE; if not, see http://www.gnu.org/licenses.
*/

#include "math/interpreter/script.h"
#include "parser.h"

static bool getLogicOp(reader &read, operation &curOp) {
    bool found = true;

    if      (read.getTokenString("OR"))  curOp = OR;
    else if (read.getTokenString("NOR")) curOp = NOR;
    else if (read.getTokenString("XOR")) curOp = XOR;
    else if (read.getTokenString("NOT")) curOp = NOT;
    else if (read.getTokenString("AND")) curOp = AND;
    else if (read.getTokenString("=="))  curOp = EQUAL;
    else if (read.getTokenString("!="))  curOp = NEQ;
    else if (read.getTokenString(">="))  curOp = LARGEQ;
    else if (read.getTokenString("<="))  curOp = SMALLEQ;
    else if (read.getTokenString("++"))  curOp = INCREMENT;
    else if (read.getTokenString("--"))  curOp = DECREMENT;
    else if (read.getTokenString("->"))  curOp = GET;
    else found = false;
    if (found) read.pos--;
    return found;
}

static bool isNumber(QString text,const unsigned int pos) {
    bool number = true;
    reader read;
    operation op;
    char c;

    read.init(text);
    read.pos = pos;
    while (read.pos < text.size() && number) {
        if (getLogicOp(read,op)) break;
        c=read.text.at(read.pos).toLatin1();
        if (getArithOp(op,c)) break;
        if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' &&
            c != '6' && c != '7' && c != '8' && c != '9' && c != '.' && c != 'i' && c != 'x') {
            number = false;
        }
        read.pos++;
    }
    return number;
}

parser::parser() {
    factory = 0;
    function = false;
    valid = true;
    real = false;
    cplxFunc = false;
    curBase = &variableData;

    //distC.charac = &charac;
    distC.function = &function;
}

parser::~parser(){

}

bool parser::cplxFuncInterface(QString &str, Function &fctn, QString &errorString, DataBase *data) {
    std::string eStr;
    errorType err;
    bool valid = true;

    if (data != 0) curBase = data;
    cplxFunc = true;
    MVar var;
    read->init(str);
    validC->init();
    parse(&var);
    validC->eval(valid,err,eStr);
    if (valid) {
        if (!var.getFunction(&fctn)) {
            validC->setErr(DONTGETCPLX);
            valid = false;
        }
    }
    if (!valid) validC->getErrMsg(errorString);
    cplxFunc = false;
    return valid;
}

QString parser::interface(QString *str, /*MaceInt characteristic,*/ int precision, DataBase *data){
    QString res;
    if (data != 0) curBase = data;
    read->init(*str);
    //charac = characteristic;
    MVar var;
    validC->init();
    parse(&var);
    validC->eval(valid,errTyp,errStr);
    if (!valid) validC->getErrMsg(res);
    else res = var.print(precision);
    read->clear();
    curBase = &variableData;
    return res;
}

bool parser::interface(QString *str, /*MaceInt characteristic,*/ DataBase *data) {
    MVar var;
    return interface(str,/*characteristic,*/&var,data);
}

bool parser::interface(QString *str, /*MaceInt characteristic,*/ MVar *var, DataBase *data) {
    if (data != 0) curBase = data;
    read->init(*str);
    //charac = characteristic;
    validC->init();
    parse(var);
    validC->eval(valid,errTyp,errStr);
    if (curOp == KOMMA) valid = false;
    read->clear();
    curBase = &variableData;
    return valid;
}

double parser::rFctnInterface(bool *help, bool *dis, QString str, MObject *x, DataBase *Data){
    numReal *NR = dynamic_cast<numReal*>(x);
    //MaceInt *I  = dynamic_cast<MaceInt*>(x);
    double  res;

    if (Data != 0) curBase = Data;
    /*if (I != 0) {
        currentIVal = *I;
        discrete = true;
        valid = true;
    }
    else*/ if (NR != 0) {
        currentRVal = *NR;
        discrete = false;
        valid = true;
    }
    else valid = false;

    real = true;
    function = true;
    read->init(str);
    errTyp = NOERR;
    try{

       //charac = charac.translate(0);
       MVar var;
       if (valid) {
           validC->init();
           parse(&var);
           validC->eval(valid,errTyp,errStr);
       }
       *help = !validC->isValid();
       if (!valid) *dis = (errTyp == NOTINT || errTyp ==NOTPOLY);
       if (valid) {
           if (!var.getNumReal(&currentRVal)) {
               validC->setErr(DONTGETREAL);
               *help = true;
           }
       }
       res = currentRVal.get();
    }
    catch( ... ){
        *help = true;
    }
    discrete = false;
    real = false;
    valid = true;
    function = false;
    return res;
}

bool parser::findOp(char ch) {
    if (getLogicOp(*read,curOp)) return true;
    else if (getArithOp(curOp,ch)) return true;
    return false;
}

void parser::setSpecialVariable(char ch, MVar *ptr) {
    if (function) {
        if (ch == 'x') {
            /*if (discrete) ptr->setInt    (currentIVal);
            else*/          ptr->setNumReal(currentRVal);
        }
        else validC->setErr(NOTREAL);
    }
    else if (ch == 'x') {
        ptr->evalX(/*charac,*/cplxFunc);
    }
    else if (ch == 'i') ptr->evalI(cplxFunc);
    read->pos++;
    if (read->pos<read->text.size()) {
        if (read->text.at(read->pos).toLatin1() == ' ' || read->text.at(read->pos).toLatin1() == '\n') {
            read->runOverEmptyChar();
        }
    }
    if (read->pos<read->text.size()) {
        if (!findOp(read->text.at(read->pos).toLatin1())) {
            curOp=MULT;
            read->pos--;
        }
    }
}

void parser::getOp(MVar *ptr, std::string &variableStr, bool &modi, bool &number) {
    curOp = NOOP;
    modi = false;
    number = true;
    variableStr.clear();
    bool opFound = false;
    bool addChar;
    unsigned int dotPos = 0;
    char help;
    while (read->pos < read->text.size() && !opFound) {
        help = read->text.at(read->pos).toLatin1();
        addChar = true;
        switch (help) {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            break;
            case ' ': case '\n':
            addChar = false;
            break;
            case '.':
            dotPos = variableStr.size();
            break;
            case 'i': case 'x':
            if (number) number = isNumber(read->text,read->pos);
            if (number) {
                if (variableStr.size() > 0) {
                    read->pos--;
                    curOp = MULT;
                }
                else {
                    setSpecialVariable(help,ptr);
                    modi = true;
                }
                opFound=true;
            }
            break;
            default:
                opFound = findOp(help);
                if (!opFound) number = false;
            break;
        }
        if (!opFound && addChar) variableStr = variableStr + help;
        read->pos++;
    }
    if (number && variableStr.size() > 0) {
        ptr->evalStr(variableStr,dotPos,/*charac,*/cplxFunc);
    }
    if (!number) {
        if (curOp == ASSIGN) {
            number = true;
            if (atBegin) globMem=variableStr;
        }
        else if (curBase->find(variableStr,ptr)) {
            number = true;
        }
    }
    if (number && variableStr.size()>0) modi = true;

    if (function && (ptr->getType() == ALGPOLY || ptr->getType() == NUMPOLY || ptr->getType() == FUNCTION)) {
        Function f;
        numCplx z;

        ptr->getFunction(&f);
        /*if (discrete) ptr->setInt    (currentIVal);
        else*/          ptr->setNumReal(currentRVal);
        ptr->getNumCplx(&z);
        z.val = f.eval(z.val,valid);
        if (fabs(z.val.imag()) < 0.00000001) {
            numReal nr;
            nr.set(z.val.real());
            ptr->setNumReal(nr);
        } else validC->setErr(DONTGETREAL);
    }
    if (modi && curOp == BRACKOP) {
        if (!function && (ptr->getType() == ALGPOLY || ptr->getType() == NUMPOLY || ptr->getType() == FUNCTION)) {
            curOp = EVAL; read->pos--;
        }
        else if (number) {curOp = MULT; read->pos--;}
    }
    atBegin = false;

    validC->getOp(curOp);
}

void parser::prim(MVar *ptr, std::string &val){
    bool fine = true, modi;

    getOp(ptr,val,modi,fine);

    if (curOp == GET && !fine && val.size()>0) {
        std::vector<std::string> args;
        while (curOp == GET  && !fine && val.size()>0) {
            args.push_back(val);
            getOp(ptr,val,modi,fine);
        }
        args.push_back(val);
        fine = !fine && val.size()>0;
        if (fine) fine = curBase->findLambda(args,ptr);
        if (!fine) validC->setErr(INCORRECTINPUT,val);
    }
    else if (curOp == BRACKOP) {
        MVar arg1, arg2, arg3;
        int nr;
        bool funcMem = cplxFunc;
        cplxFunc = cplxFunc || val == "func";
        multiParse(ptr, &arg1, &arg2, &arg3, nr, val);
        cplxFunc = funcMem;
        if (!fine) {
            if (cplxFunc) {
                Function f, g, h;
                ptr->getFunction(&f);
                arg1.getFunction(&g);
                arg2.getFunction(&h);
                fine = setFunc(f,g,h,val,nr);
                ptr->setFunction(f);
            }
            else if (val == "func" && nr == 1) fine = true;
            else {
                fine = distC.distribute(ptr,&arg1,&arg2,&arg3,val,nr);
            }
            if (!fine) validC->setErr(INCORRECTFCTN,val);
        }
        if (read->pos < read->text.size()) {
            if (findOp(read->text.at(read->pos).toLatin1())) {
                if (curOp == BRACKOP) curOp = MULT;
                else if (curOp == NOT) {
                    curOp =MULT; read->pos-=2;
                }
                else read->pos++;
                validC->getOp(curOp);
            }
            else curOp = MULT;
        } else curOp = NOOP;
    }
    else if (curOp == MINUS && !modi) {
        prim(ptr,val);
        minus(ptr/*,charac*/);
    }
    else if (curOp == NOT) {
        prim(ptr,val);
        notOp(ptr,ptr);
    }
    else if (curOp == STRINGOP) {
        QString valStr;
        if (read->getStringTillSign(valStr,'"')) {
            MaceString MStr;
            MStr.str = valStr;
            ptr->setString(MStr);
            if (findOp(read->text.at(read->pos).toLatin1())) {
                read->pos++;
                validC->getOp(curOp);
            }
        } else validC->setErr(INCORRECTINPUT);
    }
    else if (!fine) validC->setErr(INCORRECTINPUT,val);
    if (curOp == INCREMENT || curOp == DECREMENT) {
        //MaceInt one(1);
        numReal one(1.0);
        MVar var;
        //var.setInt(one);
        var.setNumReal(one);
        operation opMem = curOp;

        if (val.size() > 0) validC->setErr(NOPREFIX);
        else {
            prim(ptr,val);
            if (opMem == INCREMENT) {
                if (!operate(ptr,ptr,&var,'+')) validC->setErr(NOTARITH);
            }
            else {
                if (!operate(ptr,ptr,&var,'-')) validC->setErr(NOTARITH);
            }
            if (curBase->find(val,&var)) curBase->insert(val,ptr);
        }
    }
}

void parser::powerLayer(MVar *ptr){
    //MaceInt charMem = charac;
    MVar left;
    std::string val;
    prim(ptr,val);
    //charac = charac.translate(0);
    while (1) {
        if(curOp == POWER){
            prim(&left,val);
            if (!operate(ptr,ptr,&left,'^')) {
                validC->setErr(POWERR);
            }
        }
        else break;
    }
    //charac = charMem;
}

void parser::term(MVar *ptr){
    MVar right;

    powerLayer(ptr);
    while (1) {
        if(curOp == MULT){
            powerLayer(&right);
            if (!operate(ptr,ptr,&right,'*'))
                validC->setErr(NOTARITH);
        }
        else if(curOp == DIV){
            powerLayer(&right);
            if (!operate(ptr,ptr,&right,'/'))
            {
                validC->setErr(DIVBYZERO);
            }
        }
        else if(curOp == EVAL){
            powerLayer(&right);
            if (!operate(ptr,ptr,&right,'v'))
            {
                validC->setErr(NOTARITH);
            }
        }
        else break;
    }
}


void parser::sumLayer(MVar *ptr){
    MVar right;
    term(ptr);
    while (1) {
        if(curOp == ADD){
            term(&right);
            Function g;
            if (!operate(ptr,ptr,&right,'+'))
                validC->setErr(NOTARITH);
        }
        else if(curOp == MINUS){
            term(&right);
            if (!operate(ptr,ptr,&right,'-'))
                validC->setErr(NOTARITH);
        }
        else break;
    }
}

void parser::compareLayer(MVar *ptr){
    sumLayer(ptr);
    if(curOp == SMALLER){
        MVar right;
        compareLayer(&right);
        if (!logOperate(ptr,ptr,&right,'<'))
            validC->setErr(INCOMPARABLE);
    }
    else if(curOp == LARGER){
        MVar right;
        compareLayer(&right);
        if (!logOperate(ptr,ptr,&right,'>'))
            validC->setErr(INCOMPARABLE);
    }
    else if(curOp == SMALLEQ){
        MVar right;
        compareLayer(&right);
        if (!logOperate(ptr,ptr,&right,'s'))
            validC->setErr(INCOMPARABLE);
    }
    else if(curOp == LARGEQ){
        MVar right;
        compareLayer(&right);
        if (!logOperate(ptr,ptr,&right,'b'))
            validC->setErr(INCOMPARABLE);
    }
}

void parser::identityLayer(MVar *ptr){
    compareLayer(ptr);
    if(curOp == EQUAL){
        MVar right;
        identityLayer(&right);
        if (!logOperate(ptr,ptr,&right,'e'))
            validC->setErr(INCOMPARABLE);
    }
    else if(curOp == NEQ){
        MVar right;
        identityLayer(&right);
        if (!logOperate(ptr,ptr,&right,'n'))
            validC->setErr(INCOMPARABLE);
    }
}

void parser::andLayer(MVar *ptr){
    identityLayer(ptr);
    if (curOp == AND){
        MVar right;
        andLayer(&right);
        if (!boolOperate(ptr,ptr,&right,'a')) {
            validC->setErr(NOTBOOL,"AND");
        }
    }
}

void parser::orLayer(MVar *ptr){
    andLayer(ptr);
    if (curOp == OR){
        MVar right;
        orLayer(&right);
        if (!boolOperate(ptr,ptr,&right,'o'))
            validC->setErr(NOTBOOL,"OR");
    }
    else if(curOp == NOR){
        MVar right;
        orLayer(&right);
        if (!boolOperate(ptr,ptr,&right,'p'))
            validC->setErr(NOTBOOL,"NOR");
    }
}

void parser::xorLayer(MVar *ptr){
    orLayer(ptr);
    if(curOp == XOR){
        MVar right;
        xorLayer(&right);
        if (!boolOperate(ptr,ptr,&right,'x')) {
            validC->setErr(NOTBOOL,"XOR");
        }
    }
}

void parser::parse(MVar *ptr){
    distC.validC = validC;
    hasScript = false;
    globMem.clear();
    atBegin = true;
    xorLayer(ptr);
    if(curOp == ASSIGN){
        std::string name = globMem;
        globMem.clear();
        if (name.size() > 0) {
            parse(ptr);
            curBase->insert(name,ptr);
        }
        else generateNoNameError(ptr);/**/
    }
}

void parser::multiParse(MVar *arg0, MVar *arg1, MVar *arg2, MVar *arg3, int &nr, std::string &val) {
    //MaceInt charMem = charac;
    nr = 1;
    //if (val == "zeroMatrix" || val == "diagMatrix") charac = charac.translate(0);
    parse(arg0);
    //if (val == "diagMatrix") charac = charMem;
    if (curOp == KOMMA) {
        //if (val == "setEntry" || val == "getEntry") charac = charac.translate(0);
        validC->getOp(KOMQUIT); parse(arg1); nr++;
        //if (val == "zeroMatrix") charac = charMem;
        if (curOp == KOMMA) {
            validC->getOp(KOMQUIT); parse(arg2); nr++;
            if (curOp == KOMMA) {
                //charac = charMem;
                validC->getOp(KOMQUIT); parse(arg3); nr++;
            }
        }
    }
    //charac = charMem;
}

void parser::generateNoNameError(MVar *ptr) {
    std::string msg;
    if (ptr->getType() == ALGPOLY || ptr->getType() == NUMPOLY) {
        msg = " Instead there is a polynomial on the left hand side.";
    }
    else if (ptr->getType() == ALGCPLX || ptr->getType() == NUMCPLX) {
        msg = " Instead there is a complex number on the left hand side.";
    }
    else msg.clear();
    validC->setErr(NONAMESTRING,msg);
}

/*algMatrix parser::strToAlgMatrix(QString str, QString &error){
    QString help= str.left(str.indexOf(","));
    MVar    var;
    algCplx z;
    int     a, b;

    error.clear();
    a=help.toInt();
    str = str.right(str.size()-1-str.indexOf(","));

    help= str.left(str.indexOf(","));
    b = help.toInt();
    str = str.right(str.size()-1-str.indexOf(","));

    algMatrix res(a,b);

    for (int i= 1; i<= a && error.size() == 0 ;i++){
        for (int j = 1; j<=b && error.size() == 0 ; j++){
            if (str.indexOf(",")== -1){help= str;}
            else{
                help = str.left(str.indexOf(","));
                str = str.right(str.size()-1-str.indexOf(","));
            }
            if (interface(&help,charac,&var)) {
                if (var.getAlgCplx(&z)) {
                    *res.element(i,j) = z;
                } else {
                    validC->setErr(INCORRECTINPUT);
                    error = "Error: Entry ";
                    error = error.append(help);
                    error = error.append(" is not a complex number.");
                }
            } else validC->getErrMsg(error);
        }
    }
    return res;
}*/

numMatrix parser::strToNumMatrix(QString str){
    int a, b;
    numCplx z;
    QString help= str.left(str.indexOf(","));

    a = help.toInt();
    str = str.right(str.size()-1-str.indexOf(","));

    help= str.left(str.indexOf(","));
    b = help.toInt();
    str = str.right(str.size()-1-str.indexOf(","));

    numMatrix res(a,b);

    for (int i= 1; i<= a;i++){
        for (int j = 1; j<=b; j++){
            if (str.indexOf(",")== -1){help= str;}
            else{
                help = str.left(str.indexOf(","));
                str = str.right(str.size()-1-str.indexOf(","));
            }
            *res.element(i,j) = z;
        }
    }
    return res;
}

/*restMatrix parser::strToRestMatrix(QString str, MaceInt charac, QString &error){
    MVar     var;
    MaceRest z;
    QString  help= str.left(str.indexOf(","));
    int      a, b;

    error.clear();
    a = help.toInt();
    str = str.right(str.size()-1-str.indexOf(","));

    help= str.left(str.indexOf(","));
    b = help.toInt();
    str = str.right(str.size()-1-str.indexOf(","));

    restMatrix res(a,b,charac);

    for (int i= 1; i<= a && error.size() == 0; i++){
        for (int j = 1; j<=b && error.size() == 0; j++){
            if (str.indexOf(",")== -1){help= str;}
            else{
                help = str.left(str.indexOf(","));
                str = str.right(str.size()-1-str.indexOf(","));
            }
            if (interface(&help,charac,&var)) {
                if (var.getRest(&z)) {
                    *res.element(i,j) = z;
                } else {
                    validC->setErr(INCORRECTINPUT);
                    error = "Error: Entry ";
                    error = error.append(help);
                    error = error.append(" is not an integral residue class.");
                }
            } else validC->getErrMsg(error);
        }
    }
    res.normalize();
    return res;
}*/
