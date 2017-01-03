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

#ifndef FUNCTION_H
#define FUNCTION_H
#include <complex>
#include <vector>
#include "math/functiondistributors/fctncalc.h"
#include "math/kernel/mobject.h"
#include "math/kernel/reader.h"
#include "math/variables/polynomial/numpoly.h"

class FunctionKnot {
public:
    enum type {X, NUMBER, UNARY, BINARY, THREE};

    FunctionKnot() { myType = X; first = -1; second = -1; }
    FunctionKnot(std::complex<double> number): value(number) {myType = NUMBER; first = -1; second = -1; }
    FunctionKnot(operation op) {myType = BINARY; myOperation = op; }

    bool isSum() const { bool sum = true; sum = sum && myType == BINARY; sum = sum && myOperation == ADD; return sum;}
    bool isBinaryMinus() const { bool minus = true; minus = minus && myType == BINARY; minus = minus && myOperation == MINUS; return minus;}

    bool isUnaryMinus() const { bool minus = true;
                           minus = minus && myType == UNARY;
                           minus = minus && FCTN == charZeroCalc::MINUS;
                           return minus;}

    void setX() {myType = X; first = -1; second = -1; }
    void setValue(std::complex<double> val) {
        myType = NUMBER;
        value = val;
        first = -1; second = -1;
    }

    std::complex<double> value;
    charZeroCalc::fctns FCTN;
    type myType;

    operation myOperation;

    int first;
    int second;
    int third;

    int getPrecedense();

};

class Function : public MObject{
public:
    fctnCalc calc;
    std::vector<FunctionKnot> Knots;

    Function() {FunctionKnot Knot; Knots.clear(); Knots.push_back(Knot);}
    Function(std::complex<double> number) {FunctionKnot Knot(number); Knots.clear(); Knots.push_back(Knot);}

    void setX() {FunctionKnot Knot; Knots.clear(); Knots.push_back(Knot);}
    void setValue(std::complex<double> val) {FunctionKnot Knot(val); Knots.clear(); Knots.push_back(Knot);}

    QString print(FunctionKnot Knot, unsigned int &depth);
    QString print(unsigned int precision) {unsigned int d=0; QString str = print(Knots[0],d); str = str.prepend("func("); return str.append(")");}
    bool isZero() {return false;}
    Function translate(numPoly &np);

    numReal symmetry();

    bool isLinear() const;
    bool isConstant() const;
    bool period(std::complex<double> &z) const;
    bool real() const;

    std::complex<double> eval(FunctionKnot Knot,std::complex<double> point,bool &valid) const;
    std::complex<double> eval(std::complex<double> point,bool &valid) const {return eval(Knots[0],point,valid);}
};

extern bool setIf(Function *res, Function f, Function g, Function h);

extern bool setOp(Function *res, Function f, Function g, char op);

extern bool setFunc(Function &f, Function &g, Function &h, std::string val, int nr);

extern QString functionTypeToQString(charZeroCalc::fctns FCTN);

extern void composite(Function *res, Function *f, Function *g);

extern bool derivative (Function &der, const Function &f);

extern bool tangent (Function &t, const Function &f, const numReal &z);

extern bool normal (Function &n, const Function &f, const numReal &z);

extern bool zeroes(Function f, std::vector<numReal> &z);

extern bool extrema(Function &f, std::vector<numReal> &extreme);

extern bool inflexionPoint(Function &f, std::vector<numReal> &inflexion);

extern double integral(const Function &f, numReal a, numReal b);

#endif // FUNCTION_H
