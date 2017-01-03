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

#ifndef READER_H
#define READER_H

#include <QString>
#include <iostream>

enum operation{
    NOT, ADD, MINUS, MULT, DIV, POWER, NOOP, BRACKOP, BRACKCL, KOMMA, FCTN, LOG,
    EVAL, SMALLER, LARGER, SMALLEQ, LARGEQ, XOR, OR, NOR, AND, EQUAL, NEQ, KOMQUIT,
    ASSIGN, UNARYMINUS, INCREMENT, DECREMENT, STRINGOP, GET
};

enum errorType{
    CPLX,
    DIVBYZERO, POWERR, INCORRECTINPUT, INCORRECTFCTN,
    ERRINFCTN, ERRDIST, ERRFUNCDIST, ERRPROPDIST,
    INTTOLARGE, INTNEG, SINTTOLARGE,
    NOTBOOL, NOTINT, NOTIR, NOTREAL, NOTCPLX, NOTPOLY, NOTREST,
    KOMMAR, NOTARITH,
    NOTERM, NOBRACKOP, NOBRACKCL, NOTOPEN, NONAMESTRING,
    DONTGETREAL, DONTGETCPLX,
    INCOMPARABLE, NOPREFIX, NOTDIFFBAR, NOTREALFUNC,
    NOERR
};

class validCheck {
private:
    std::string  errStr;
    errorType    error;
    int          brack;
    bool         komma;
    bool         valid;

public:
    void init     ();
    void getOp    (operation op);
    void setErr   (errorType err);
    void setErr   (errorType err, std::string estr);
    bool isValid  ();
    void eval     (bool &val, errorType &err, std::string &eStr);
    void getErrMsg(QString &str);
};

struct reader {
    QString text;
    int     pos;

    ~reader() {;}

    void init(QString str);
    void clear();
    void jumpToBrackEnd();
    int  jumpToBrackClose();

    int  runOverEmptyLines();
    int  runOverEmptyChar();
    int  runOverComment();
    bool getTokenString(QString str);
    int  getLineNumber(int relevantPos);
    bool getStringTillBrackClose(QString &str,validCheck &validC);
    bool getStringTillSign(QString &str, char sign);
    bool getStringTillSign(QString &str, QString sign);
};

extern void removeLastInput(QString &str);

extern void removeSpec(QString &str);
extern void insertSpec(QString &str);

extern void powerCorrect(QString &str);

extern void QStrToStdStr(QString &qstr, std::string &ststr);
extern void StdStrToQStr(std::string &ststr, QString &qstr);

extern bool getArithOp(operation &curOp, char help);

#endif // READER_H
