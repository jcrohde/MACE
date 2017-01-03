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

#ifndef PARSER_H
#define PARSER_H
#include <cmath>
#include "math/functiondistributors/distributor.h"
#include "math.h"
#include "math/linearalgebra/algmatrix.h"
#include "math/linearalgebra/restmatrix.h"
#include "data/stringfactory.h"
#include "math/kernel/mvar.h"
#include "math/kernel/reader.h"
#include "math/linearalgebra/nummatrix.h"
#include "math/interpreter/script.h"
#include "database.h"

class parser{
private:   
    DataBase *curBase;

    bool hasScript;

    operation curOp;

    std::string errStr, globMem;
    errorType errTyp;

    numReal   currentRVal;
    //MaceInt   currentIVal;

    //MaceInt   charac;

    //-states for function parsing-------------------------------------
    bool      function, real, discrete, cplxFunc, atBegin;

    bool findOp(char ch);

    void setSpecialVariable(char ch, MVar *ptr);

    void getOp(MVar *ptr, std::string &val, bool &modi, bool &fine);

    void prim         (MVar *ptr, std::string & val);
    void powerLayer   (MVar *ptr);
    void term         (MVar *ptr);
    void sumLayer     (MVar *ptr);
    void compareLayer (MVar *ptr);
    void identityLayer(MVar *ptr);
    void andLayer     (MVar *ptr);
    void orLayer      (MVar *ptr);
    void xorLayer     (MVar *ptr);
    void parse        (MVar *ptr);

    void multiParse(MVar *arg0, MVar *arg1, MVar *arg2, MVar *arg3, int &nr, std::string &val);

public:
    DataBase  variableData;

    reader     *read;
    validCheck *validC;

    bool valid;

    stringFactory *factory;

    distributor distC;

    parser();
    ~parser();

    //-interfaces------------------------------------------------------

    double  rFctnInterface(bool *help, bool *dis, QString str, MObject *x, DataBase *Data = 0);

    bool    cplxFuncInterface(QString &str, Function &fctn, QString &errorString, DataBase *data = 0);
    QString interface(QString *str, /*MaceInt characteristic,*/ int precision, DataBase *data = 0);
    bool    interface(QString *str, /*MaceInt characteristic,*/ DataBase *data = 0);
    bool    interface(QString *str, /*MaceInt characteristic,*/ MVar *var, DataBase *data = 0);

    QString getErrorString() {QString msg; validC->getErrMsg(msg); return msg;}
    void    generateNoNameError(MVar *ptr);

    //-parse methods for matrices---------------------------------------

    //algMatrix strToAlgMatrix(QString str, QString &error);
    numMatrix strToNumMatrix(QString str);
    //restMatrix strToRestMatrix(QString str, MaceInt charac, QString &error);
};

#endif // PARSER_H
