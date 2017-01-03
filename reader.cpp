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

#include <iostream>
#include "reader.h"

void reader::init(QString str) {
    pos = 0;
    text = str;
}

void reader::clear() {
    pos = -1;
    text.clear();
}

void reader::jumpToBrackEnd() {
    char help;
    int brackCl=0;
    bool valid = true;

    while (brackCl<1 && valid) {
        help = text.at(pos).toLatin1();
        if (help == '{') brackCl--;
        if (help == '}') brackCl++;
        pos++;
    }
}

int reader::jumpToBrackClose() {
    char help;
    int brackCl=0;
    while (brackCl<1 && pos < text.size()) {
        help = text.at(pos).toLatin1();
        if (help == '(') brackCl--;
        if (help == ')') brackCl++;
        pos++;
    }
    pos--;
    if (brackCl < 1) pos = -1;

    return pos;
}

int reader::runOverEmptyLines() {
    while (pos < text.size()) {
        if (text.at(pos).toLatin1() == ' ' || text.at(pos).toLatin1() == '\n')
            runOverEmptyChar();
        else if (text.at(pos).toLatin1() == '%')
            runOverComment();
        else break;
    }
    return pos;
}

int reader::runOverEmptyChar() {
    if (pos < text.size()) {
        while (text.at(pos).toLatin1() == ' ' || text.at(pos).toLatin1() == '\n') {
            pos++;
            if (pos == text.size()) break;
        }
    }
    return pos;
}

int reader::runOverComment() {
    while (pos < text.size() && text.at(pos).toLatin1() != '\n') {
        pos++;
    }
    return pos;
}

bool reader::getTokenString(QString str) {
    runOverEmptyChar();
    if (text.indexOf(str,pos) == pos) {
        pos += str.size();
        return true;
    }
    return false;
}

int reader::getLineNumber(int relevantPos) {
    QString leftOfPos = text.left(relevantPos);
    return leftOfPos.count('\n') + 1;
}

bool reader::getStringTillSign(QString &string, char sign) {
    unsigned int stringBeg, stringEnd, size;

    stringBeg = pos;
    stringEnd = text.indexOf(sign,pos);
    if (stringEnd > 0) {
        size = stringEnd - stringBeg;
        string = text.mid(stringBeg,size);
        pos = stringEnd + 1;
        return true;
    }
    return false;
}

bool reader::getStringTillSign(QString &string, QString sign) {
    unsigned int stringBeg, stringEnd, size;

    stringBeg = pos;
    stringEnd = text.indexOf(sign,pos);
    if (stringEnd > 0) {
        size = stringEnd - stringBeg;
        string = text.mid(stringBeg,size);
        pos = stringEnd + 1;
        return true;
    }
    return false;
}

bool reader::getStringTillBrackClose(QString &string,validCheck &validC) {
    int stringBeg, stringEnd;
    bool valid = true;

    stringBeg = pos;
    stringEnd = jumpToBrackClose()-stringBeg;
    valid = valid && stringEnd > 0;
    if (valid) {
        string = text.mid(stringBeg,stringEnd);
        pos++;
    }
    if (!valid) validC.setErr(NOBRACKCL);
    return valid;
}

void removeLastInput(QString &str) {
    unsigned int lastInputIndex = str.lastIndexOf("Input: ");
    int newEnd = lastInputIndex+7;
    str = str.left(newEnd);
}

void removeSpec(QString &str) {
    int pos;
    pos = str.indexOf("&lt;");
    while(pos > -1) {
        str = str.replace(pos,4,"<");
        pos = str.indexOf("&lt;");
    }
    pos = str.indexOf("&gt;");
    while(pos > -1) {
        str = str.replace(pos,4,">");
        pos = str.indexOf("&gt;");
    }
}

void insertSpec(QString &str) {
    int pos;

    pos = str.indexOf("<");
    while(-1 < pos) {
        str = str.replace(pos,1,"&lt;");
        pos = str.indexOf("<");
    }
    pos = str.indexOf(">");
    while(pos > -1) {
        str = str.replace(pos,1,"&gt;");
        pos = str.indexOf(">");
    }
}

void powerCorrect(QString &str) {
    QString left, right, copy = "";
    int indexE = str.indexOf("e");

    while (indexE > -1) {
        left = str.left(str.indexOf("e"));
        right = str.right(str.size()-str.indexOf("e") -1);
        if (right.indexOf("-") == 0) {
            right = right.right(right.size()-1);
            str = left;
            str = str.append("*0.1^");
            str = str.append(right);
        }
        else if (right.indexOf("+") == 0){
            right = right.right(right.size()-1);
            str = left;
            str = str.append("*10^");
            str = str.append(right);
        }
        else {
            copy = copy.append(str.left(indexE+1));
            str = right;
        }
        indexE = str.indexOf("e");
    }
    str = str.prepend(copy);
}

void QStrToStdStr(QString &qstr, std::string &ststr) {
    ststr = qstr.toUtf8().constData();
}

void StdStrToQStr(std::string &ststr, QString &qstr) {
    char *c = new char[ststr.size()+1];
    strcpy(c, ststr.c_str());
    qstr = QString::fromLatin1(c);
    delete[] c;
}

void validCheck::init() {
    komma = false;
    valid = true;
    error = NOERR;
    brack = 0;
    errStr.clear();
}

void validCheck::getOp(operation op) {
    if (komma) {
        if (op == KOMQUIT) komma = false;
        else setErr(KOMMAR);
    }
    if (op == KOMMA) komma = true;
    else if (op == BRACKCL) {
        brack++;
    }
    else if (op == BRACKOP) {
        brack --;
    }
    if (brack > 0) {
        setErr(NOBRACKOP);
    }
}

void validCheck::setErr(errorType err) {
    if (valid) {
        valid = false;
        error = err;
    }
}

void validCheck::setErr(errorType err, std::string estr) {
    if (valid) {
        valid = false;
        error = err;
        errStr = estr;
    }
}

bool validCheck::isValid() {
    return valid;
}

void validCheck::eval(bool &val, errorType &err, std::string &eStr) {
    if (valid && brack < 0) {
        val = false; err = NOBRACKCL;  error = NOBRACKCL; valid = false;
    }
    if (valid && komma) {
        val = false; err = KOMMAR; error = KOMMAR; valid = false;
    }
    else {
        val = valid; err = error; eStr = errStr;
    }
}

void validCheck::getErrMsg(QString &str) {
    QString c;

    if (valid) str.clear();
    else {
    StdStrToQStr(errStr,c);
    str = "Error: ";
    if (error == DIVBYZERO) {
        str = str.append("Division by zero.");
    }
    else if (error == POWERR) {
        str = str.append("The power can not be computed for the given base and exponent.");
    }
    else if (error == INCORRECTFCTN) {
        str = str.append("The string \"");
        str = str.append(c);
        str = str.append("\" cannot be parsed as the name of a function for the given arguments.");
    }
    else if (error == INCORRECTINPUT) {
        str = str.append("The string \"");
        str = str.append(c);
        str = str.append("\" cannot be parsed as a suitable data type.");
    }
    else if (error == NOPREFIX) {
        str = str.append("The increment and decrement operators are only defined as prefix operators directly before a variable or some data type.");
    }
    else if (error == ERRINFCTN) {
        str = str.append("In the function ");
        str = str.append(c);
        str = str.append(" an error appeared. Maybe your arguments are outside of the range of definition.");
    }
    else if (error == ERRDIST) {
        str = str.append("The distribution ");
        str = str.append(c);
        str = str.append(" is not defined for the selected arguments.");
    }
    else if (error == ERRFUNCDIST) {
        str = str.append("The function of the distribution ");
        str = str.append(c);
        str = str.append(" is not defined for the selected arguments..");
    }
    else if (error == ERRPROPDIST) {
        str = str.append("The property of the distribution ");
        str = str.append(c);
        str = str.append(" is not defined for the selected arguments.");
    }
    else if (error == INTTOLARGE) {
        str = str.append("The integer ");
        str = str.append(c);
        str = str.append(" is to large for the given function. The function takes only arguments smaller or equal to 4294967295.");
    }
    else if (error == INTNEG) {
        str = str.append("The integer ");
        str = str.append(c);
        str = str.append(" is negative. The given function takes only positive arguments.");
    }
    else if (error == SINTTOLARGE) {
        str = str.append("The integer ");
        str = str.append(c);
        str = str.append(" is outside the range of definition for the given function. The function takes only arguments between 2147483648 and -2147483647.");
    }
    else if (error == NOTBOOL) {
        str = str.append("The operation ");
        str = str.append(c);
        str = str.append(" is only defined for booleans.");
    }
    if (error == NOTINT) {
        str = str.append("The function ");
        str = str.append(c);
        str = str.append(" is only defined for integers.");
    }
    else if (error == NOTIR) {
        str = str.append("The function ");
        str = str.append(c);
        str = str.append(" is only defined for real numbers in one argument and for integers in the other one.");
    }
    else if (error == NOTREAL) {
        str = str.append("The function ");
        str = str.append(c);
        str = str.append(" is only defined for real numbers.");
    }
    else if (error == NOTCPLX) {
        str = str.append("The function ");
        str = str.append(c);
        str = str.append(" is only defined for complex numbers.");
    }
    else if (error == NOTPOLY) {
        str = str.append("The function ");
        str = str.append(c);
        str = str.append(" is only defined for integers and arbitrary precision polynomials of positive degree.");
    }
    else if (error == NOTREST) {
        str = str.append("The function ");
        str = str.append(c);
        str = str.append(" can only be applied to integers and integral residue classes.");
    }
    else if (error == KOMMAR) {
        str = str.append("Too often used \",\".");
    }
    else if (error == NOTERM) {
        str = str.append("Missing term between two operations.");
    }
    else if (error == NOBRACKOP) {
        str = str.append("Missing \"(\".");
    }
    else if (error == NOBRACKCL) {
        str = str.append("Missing \")\".");
    }
    else if (error == CPLX) {
        str = str.append("The function \"");
        str = str.append(c);
        str = str.append("\" does not return a real number in general.");
    }
    else if (error == NONAMESTRING) {
        str = str.append("No suitable name-string found at the left hand side of the assignment operator.");
        str = str.append(c);
    }
    else if (error == DONTGETREAL) {
        str = str.append("The return value is not a real number.");
    }
    else if (error == DONTGETCPLX) {
        str = str.append("The return value is not a complex number.");
    }
    else if (error == NOTARITH) {
        str = str.append("An arithmetic operation between the given variables is not possible.");
    }
    else if (error == INCOMPARABLE) {
        str = str.append("Variables can not be compared.");
    }
    else if (error == NOTDIFFBAR) {
        str = str.append("The function is not differentiable.");
    }
    else if (error == NOTREALFUNC) {
        str = str.append("The inserted function is not real.");
    }
    else if (error == NOTOPEN) {
        str = str.append("Cannot open the file \"");
        str = str.append(c);
        str = str.append(".");
    }
    }
}

bool getArithOp(operation &curOp, char help) {
    bool opFound = false;

    switch (help) {
    case '+': curOp =     ADD; opFound = true; break;
    case '-': curOp =   MINUS; opFound = true; break;
    case '*': curOp =    MULT; opFound = true; break;
    case '/': curOp =     DIV; opFound = true; break;
    case '^': curOp =   POWER; opFound = true; break;
    case '(': curOp = BRACKOP; opFound = true; break;
    case ')': curOp = BRACKCL; opFound = true; break;
    case ',': curOp =   KOMMA; opFound = true; break;
    case '<': curOp = SMALLER; opFound = true; break;
    case '>': curOp =  LARGER; opFound = true; break;
    case '=': curOp =  ASSIGN; opFound = true; break;
    case '"': curOp =  STRINGOP; opFound = true; break;
    default: break;
    }

    return opFound;
}
