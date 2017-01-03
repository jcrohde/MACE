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

#include "function.h"
#include "math/variables/scalar/numcplx.h"
#include <iostream>

static const std::complex<double> cplxOne(1.0,0.0);
static const std::complex<double> cplxZero(0.0,0.0);
static const double zeroBound = 0.000001;
static const double PIC = 3.14159265358;

static void printFunc(const std::vector<FunctionKnot> &f) {
    Function fu;
    fu.Knots =f;
    std::cout << fu.print(6).toUtf8().constData() << std::endl;
}

static bool compare(const std::vector<FunctionKnot> &f,
                    const std::vector<FunctionKnot> &g,
                    int indexF, int indexG) {
    bool coincide = true;

    coincide = coincide && f[indexF].myType == g[indexG].myType;
    if (coincide) {
        if (f[indexF].myType == FunctionKnot::NUMBER) {
            coincide = coincide && fabs(f[indexF].value.real() - g[indexG].value.real()) < 0.000001;
            coincide = coincide && fabs(f[indexG].value.imag() - g[indexG].value.imag()) < 0.000001;
        }
        if (f[indexF].myType == FunctionKnot::UNARY) {
            coincide = coincide && f[indexF].FCTN == g[indexG].FCTN;
            coincide = coincide && compare(f,g,f[indexF].first,g[indexG].first);
        }
        if (f[indexF].myType == FunctionKnot::BINARY) {
            coincide = coincide && f[indexF].myOperation == g[indexG].myOperation;
            coincide = coincide &&
                    ((compare(f,g,f[indexF].first,g[indexG].first) && compare(f,g,f[indexF].second,g[indexG].second))
                  || (compare(f,g,f[indexF].first,g[indexG].second) && compare(f,g,f[indexF].second,g[indexG].first)));
        }
    }
    return coincide;
}

static bool isFactor(const std::vector<FunctionKnot> &func, int index, const std::vector<FunctionKnot> &factor) {
    if (compare(func,factor,index,0)) return true;
    if (func[index].myType == FunctionKnot::BINARY) {
        if (func[index].myOperation == MULT) {
            return isFactor(func,func[index].first,factor) || isFactor(func,func[index].second,factor);
        }
    }
    return false;
}

static void normalizedAppend(std::vector<FunctionKnot> &dest, const std::vector<FunctionKnot> &source) {
    int size = dest.size();
    dest.insert(dest.begin() + size,source.begin(),source.end());
    int newSize = dest.size();
    for (int i = size; i < newSize; i++) {
        if (dest[i].myType == FunctionKnot::BINARY) {
            dest[i].first = dest[i].first + size;
            dest[i].second = dest[i].second + size;
        }
        else if (dest[i].myType == FunctionKnot::UNARY) {
            dest[i].first = dest[i].first + size;
        }
    }
}

static void getBrackets(QString &str) {
    str = str.prepend("(");
    str = str.append(")");
}

static void normalizedCombi(const FunctionKnot &Knot,
                            const std::vector<FunctionKnot> &Compo1,
                            const std::vector<FunctionKnot> &Compo2,
                            std::vector<FunctionKnot> &combi) {
    FunctionKnot KnotC = Knot;

    combi.clear();
    KnotC.first = 1;
    KnotC.second = Compo1.size()+1;
    combi.push_back(KnotC);
    normalizedAppend(combi,Compo1);
    normalizedAppend(combi,Compo2);
}


static void getComponent(const std::vector<FunctionKnot> fKnots, int i, std::vector<FunctionKnot> &component) {
    component.clear();
    FunctionKnot Knot = fKnots[i];
    if (Knot.myType == FunctionKnot::BINARY) {
        std::vector<FunctionKnot> compo1, compo2;
        getComponent(fKnots,fKnots[i].first,compo1);
        getComponent(fKnots,fKnots[i].second,compo2);
        normalizedCombi(Knot,compo1,compo2,component);
    }
    else if (Knot.myType == FunctionKnot::UNARY) {
        std::vector<FunctionKnot> compo1;
        getComponent(fKnots,fKnots[i].first,compo1);
        Knot.first = 1;
        component.push_back(Knot);
        normalizedAppend(component,compo1);
    }
    else component.push_back(Knot);
}

static bool findCommonFactor(const std::vector<FunctionKnot> &simple1,
                             const std::vector<FunctionKnot> &simple2,
                             std::vector<FunctionKnot> &factor)
{
    if (isFactor(simple1,0,simple2)) {
        factor = simple2;
        return true;
    }
    else if (simple2[0].myType == FunctionKnot::BINARY) {
        if (simple2[0].myOperation == MULT) {
            std::vector<FunctionKnot> compo;
            bool found = false;
            getComponent(simple2,simple2[0].first,compo);
            if (!found) found = findCommonFactor(simple1,compo,factor);
            getComponent(simple2,simple2[0].second,compo);
            if (!found) found = findCommonFactor(simple1,compo,factor);
            return found;
        }
    }
    return false;
}

static bool divide(std::vector<FunctionKnot> &func, const std::vector<FunctionKnot> &factor) {
    bool divided = false;

    if (factor[0].myType == FunctionKnot::NUMBER && factor[0].value.real() == 0.0 && factor[0].value.imag() == 0.0) return false;
    else if (compare(func,factor,0,0)) {
        FunctionKnot K(1.0);
        func.clear();
        func.push_back(K);
        divided = true;
    }
    else if (func[0].myType == FunctionKnot::BINARY) {
        if (func[0].myOperation == MULT) {
            std::vector<FunctionKnot> compo1,compo2;
            FunctionKnot K=func[0];
            getComponent(func,func[0].first,compo1);
            getComponent(func,func[0].second,compo2);
            if (!divided) divided = divide(compo1,factor);
            if (!divided) divided = divide(compo2,factor);
            if (divided)  normalizedCombi(K,compo1,compo2,func);
        }
    }

    return divided;
}

static bool getOuterDerivative(const std::vector<FunctionKnot> fKnots, int i, std::vector<FunctionKnot> &component) {
    bool valid = true;
    std::vector<FunctionKnot> innerFunc;
    getComponent(fKnots,fKnots[i].first,innerFunc);
    FunctionKnot Knot=fKnots[i];
    component.clear();
    Knot.first = 1;
    if (Knot.FCTN == charZeroCalc::SIN) {
        Knot.FCTN = charZeroCalc::COS;
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::COS) {
        Knot.FCTN = charZeroCalc::MINUS;
        component.push_back(Knot);
        Knot.first = 2;
        Knot.FCTN = charZeroCalc::SIN;
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::EXP) {
        Knot.FCTN = charZeroCalc::EXP;
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::LN) {
        Knot = FunctionKnot(DIV);
        Knot.first = 1;
        Knot.second = 2;
        component.push_back(Knot);
        std::complex<double> one(1.0,0.0);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::RADIC) {
        Knot = FunctionKnot(DIV);
        Knot.first = 1;
        Knot.second = 2;
        component.push_back(Knot);
        std::complex<double> one(1.0,0.0);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot = FunctionKnot(MULT);
        Knot.first = 3;
        Knot.second = 4;
        component.push_back(Knot);
        std::complex<double> two(2.0,0.0);
        Knot = FunctionKnot(two);
        component.push_back(Knot);
        Knot.myType = FunctionKnot::UNARY;
        Knot.first = 5;
        Knot.FCTN = charZeroCalc::RADIC;
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::TAN) {
        Knot = FunctionKnot(DIV);
        Knot.first = 1;
        Knot.second = 2;
        component.push_back(Knot);
        std::complex<double> one(1.0,0.0);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot = FunctionKnot(POWER);
        Knot.first = 3;
        Knot.second = 4;
        component.push_back(Knot);
        Knot.myType = FunctionKnot::UNARY;
        Knot.first = 5;
        Knot.FCTN = charZeroCalc::COS;
        component.push_back(Knot);
        std::complex<double> two(2.0,0.0);
        Knot = FunctionKnot(two);
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::COT) {
        Knot = FunctionKnot(DIV);
        Knot.first = 1;
        Knot.second = 2;
        component.push_back(Knot);
        std::complex<double> minusOne(-1.0,0.0);
        Knot = FunctionKnot(minusOne);
        component.push_back(Knot);
        Knot = FunctionKnot(POWER);
        Knot.first = 3;
        Knot.second = 4;
        component.push_back(Knot);
        Knot.myType = FunctionKnot::UNARY;
        Knot.first = 5;
        Knot.FCTN = charZeroCalc::SIN;
        component.push_back(Knot);
        std::complex<double> two(2.0,0.0);
        Knot = FunctionKnot(two);
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::ARCSIN) {
        Knot = FunctionKnot(DIV);
        Knot.first = 1;
        Knot.second = 2;
        component.push_back(Knot);
        std::complex<double> one(1.0,0.0);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot.myType = FunctionKnot::UNARY;
        Knot.FCTN = charZeroCalc::RADIC;
        Knot.first = 3;
        component.push_back(Knot);
        Knot = FunctionKnot(MINUS);
        Knot.first = 4;
        Knot.second = 5;
        component.push_back(Knot);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot = FunctionKnot(POWER);
        Knot.first = 7;
        Knot.second = 6;
        component.push_back(Knot);
        std::complex<double> two(2.0,0.0);
        Knot = FunctionKnot(two);
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::ARCCOS) {
        Knot = FunctionKnot(DIV);
        Knot.first = 1;
        Knot.second = 2;
        component.push_back(Knot);
        std::complex<double> minusOne(-1.0,0.0);
        Knot = FunctionKnot(minusOne);
        component.push_back(Knot);
        Knot.myType = FunctionKnot::UNARY;
        Knot.FCTN = charZeroCalc::RADIC;
        Knot.first = 3;
        component.push_back(Knot);
        Knot = FunctionKnot(MINUS);
        Knot.first = 4;
        Knot.second = 5;
        component.push_back(Knot);
        std::complex<double> one(1.0,0.0);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot = FunctionKnot(POWER);
        Knot.first = 7;
        Knot.second = 6;
        component.push_back(Knot);
        std::complex<double> two(2.0,0.0);
        Knot = FunctionKnot(two);
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::ARCTAN) {
        Knot = FunctionKnot(DIV);
        Knot.first = 1;
        Knot.second = 2;
        component.push_back(Knot);
        std::complex<double> one(1.0,0.0);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot.myType = FunctionKnot::UNARY;
        Knot.FCTN = charZeroCalc::RADIC;
        Knot.first = 3;
        component.push_back(Knot);
        Knot = FunctionKnot(ADD);
        Knot.first = 4;
        Knot.second = 5;
        component.push_back(Knot);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot = FunctionKnot(POWER);
        Knot.first = 7;
        Knot.second = 6;
        component.push_back(Knot);
        std::complex<double> two(2.0,0.0);
        Knot = FunctionKnot(two);
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::ARCCOT) {
        Knot = FunctionKnot(DIV);
        Knot.first = 1;
        Knot.second = 2;
        component.push_back(Knot);
        std::complex<double> minusOne(-1.0,0.0);
        Knot = FunctionKnot(minusOne);
        component.push_back(Knot);
        Knot.myType = FunctionKnot::UNARY;
        Knot.FCTN = charZeroCalc::RADIC;
        Knot.first = 3;
        component.push_back(Knot);
        Knot = FunctionKnot(ADD);
        Knot.first = 4;
        Knot.second = 5;
        component.push_back(Knot);
        std::complex<double> one(1.0,0.0);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot = FunctionKnot(POWER);
        Knot.first = 7;
        Knot.second = 6;
        component.push_back(Knot);
        std::complex<double> two(2.0,0.0);
        Knot = FunctionKnot(two);
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::SINH) {
        Knot.FCTN = charZeroCalc::COSH;
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::COSH) {
        Knot.FCTN = charZeroCalc::SINH;
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::TANH) {
        Knot = FunctionKnot(MINUS);
        Knot.first = 1;
        Knot.second = 2;
        component.push_back(Knot);
        std::complex<double> one(1.0,0.0);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot = FunctionKnot(POWER);
        Knot.first = 4;
        Knot.second = 3;
        component.push_back(Knot);
        std::complex<double> two(2.0,0.0);
        Knot = FunctionKnot(two);
        component.push_back(Knot);
        Knot.myType = FunctionKnot::UNARY;
        Knot.first = 5;
        Knot.FCTN = charZeroCalc::TANH;
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::COTH) {
        Knot = FunctionKnot(MINUS);
        Knot.first = 1;
        Knot.second = 2;
        component.push_back(Knot);
        std::complex<double> one(1.0,0.0);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot = FunctionKnot(POWER);
        Knot.first = 4;
        Knot.second = 3;
        component.push_back(Knot);
        std::complex<double> two(2.0,0.0);
        Knot = FunctionKnot(two);
        component.push_back(Knot);
        Knot.myType = FunctionKnot::UNARY;
        Knot.first = 5;
        Knot.FCTN = charZeroCalc::COTH;
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::ARSINH) {
        Knot = FunctionKnot(DIV);
        Knot.first = 1;
        Knot.second = 2;
        component.push_back(Knot);
        std::complex<double> one(1.0,0.0);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot.myType = FunctionKnot::UNARY;
        Knot.FCTN = charZeroCalc::RADIC;
        Knot.first = 3;
        component.push_back(Knot);
        Knot = FunctionKnot(ADD);
        Knot.first = 4;
        Knot.second = 5;
        component.push_back(Knot);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot = FunctionKnot(POWER);
        Knot.first = 7;
        Knot.second = 6;
        component.push_back(Knot);
        std::complex<double> two(2.0,0.0);
        Knot = FunctionKnot(two);
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::ARCOSH) {
        Knot = FunctionKnot(DIV);
        Knot.first = 1;
        Knot.second = 2;
        component.push_back(Knot);
        std::complex<double> one(1.0,0.0);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot.myType = FunctionKnot::UNARY;
        Knot.FCTN = charZeroCalc::RADIC;
        Knot.first = 3;
        component.push_back(Knot);
        Knot = FunctionKnot(MINUS);
        Knot.first = 4;
        Knot.second = 6;
        component.push_back(Knot);
        Knot = FunctionKnot(POWER);
        Knot.first = 7;
        Knot.second = 5;
        component.push_back(Knot);
        std::complex<double> two(2.0,0.0);
        Knot = FunctionKnot(two);
        component.push_back(Knot);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
    }
    else if (Knot.FCTN == charZeroCalc::ARTANH || Knot.FCTN == charZeroCalc::ARCOTH) {
        Knot = FunctionKnot(DIV);
        Knot.first = 1;
        Knot.second = 2;
        component.push_back(Knot);
        std::complex<double> one(1.0,0.0);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot = FunctionKnot(MINUS);
        Knot.first = 3;
        Knot.second = 4;
        component.push_back(Knot);
        Knot = FunctionKnot(one);
        component.push_back(Knot);
        Knot = FunctionKnot(POWER);
        Knot.first = 6;
        Knot.second = 5;
        component.push_back(Knot);
        std::complex<double> two(2.0,0.0);
        Knot = FunctionKnot(two);
        component.push_back(Knot);
    }
    else valid = false;
    normalizedAppend(component,innerFunc);
    return valid;
}

static bool derivateKnot(const std::vector<FunctionKnot> &fKnots,
                         int i,
                         std::vector<FunctionKnot> &derKnots) {
    bool valid = true;

    if (fKnots[i].myType == FunctionKnot::X) {
        FunctionKnot K(1.0);
        derKnots.push_back(K);
    }
    else if (fKnots[i].myType == FunctionKnot::NUMBER) {
        FunctionKnot K(0.0);
        derKnots.push_back(K);
    }
    else if (fKnots[i].myType == FunctionKnot::UNARY) {
        if (fKnots[i].FCTN == charZeroCalc::MINUS) {
            std::vector<FunctionKnot> innerDer,outerDer;
            valid = valid && derivateKnot(fKnots,fKnots[i].first,innerDer);
            FunctionKnot Knot = fKnots[i];
            Knot.first = 1;
            outerDer.push_back(Knot);
            normalizedAppend(outerDer,innerDer);
            derKnots = outerDer;
        }
        else {
            std::vector<FunctionKnot> innerDer, outerDer;
            valid = valid && derivateKnot(fKnots,fKnots[i].first,innerDer);
            valid = valid && getOuterDerivative(fKnots,i,outerDer);
            FunctionKnot Knot;
            Knot.myType = FunctionKnot::BINARY;
            Knot.myOperation = MULT;
            normalizedCombi(Knot,outerDer,innerDer,derKnots);
        }
    }
    else if (fKnots[i].myType == FunctionKnot::BINARY) {
        std::vector<FunctionKnot> derCompo1, derCompo2, origCompo1, origCompo2;
        FunctionKnot Knot;

        valid = valid && derivateKnot(fKnots,fKnots[i].first,derCompo1);
        valid = valid && derivateKnot(fKnots,fKnots[i].second,derCompo2);
        getComponent(fKnots,fKnots[i].first,origCompo1);
        getComponent(fKnots,fKnots[i].second,origCompo2);
        Knot = fKnots[i];

        if (Knot.myOperation == MULT) {
            std::vector<FunctionKnot> product1, product2;
            normalizedCombi(Knot,derCompo1,origCompo2,product1);
            normalizedCombi(Knot,derCompo2,origCompo1,product2);
            Knot.myOperation = ADD;
            normalizedCombi(Knot,product1,product2,derKnots);
        }
        else if (Knot.myOperation == DIV) {
            std::vector<FunctionKnot> product1, product2, numerator, divisor;
            Knot.myOperation = MULT;
            normalizedCombi(Knot,origCompo2,origCompo2,divisor);
            normalizedCombi(Knot,derCompo1,origCompo2,product1);
            normalizedCombi(Knot,derCompo2,origCompo1,product2);
            Knot.myOperation = MINUS;
            normalizedCombi(Knot,product1,product2,numerator);
            Knot.myOperation = DIV;
            normalizedCombi(Knot,numerator,divisor,derKnots);
        }
        else if (Knot.myOperation == POWER) {
            std::vector<FunctionKnot> product1, p1, product2, origPower, OneF, gMinOne, newPower, logf, gDerfOrig;
            Knot.myOperation = MULT;

            FunctionKnot One(1.0);
            OneF.push_back(One);
            Knot.myOperation = MINUS;
            normalizedCombi(Knot,origCompo2,OneF,gMinOne);

            Knot.myOperation = POWER;
            normalizedCombi(Knot,origCompo1,gMinOne,newPower);

            Knot.myOperation = MULT;
            normalizedCombi(Knot,derCompo1,origCompo2,p1);
            normalizedCombi(Knot,newPower,p1,product1);

            Knot.myOperation = POWER;
            normalizedCombi(Knot,origCompo1,origCompo2,origPower);

            FunctionKnot UK;
            UK.myType = FunctionKnot::UNARY;
            UK.FCTN = charZeroCalc::LN;
            UK.first = 1;
            logf.push_back(UK);
            normalizedAppend(logf,origCompo1);

            Knot.myOperation = MULT;
            normalizedCombi(Knot,derCompo2,logf,gDerfOrig);

            normalizedCombi(Knot,origPower,gDerfOrig,product2);

            Knot.myOperation = ADD;
            normalizedCombi(Knot,product1,product2,derKnots);
        }
        else {
            Knot.first = 1;
            Knot.second = derCompo1.size()+1;
            derKnots.push_back(Knot);
            normalizedAppend(derKnots,derCompo1);
            normalizedAppend(derKnots,derCompo2);
        }
    }
    else {
        derKnots = fKnots;
        valid = false;
    }
    return valid;
}

static int symmet(const std::vector<FunctionKnot> &Knots, int index) {
    int res = 0;

    if (Knots[index].myType == FunctionKnot::NUMBER) res = 1;
    if (Knots[index].myType == FunctionKnot::X) res = -1;
    if (Knots[index].myType == FunctionKnot::UNARY) {
        if (symmet(Knots,Knots[index].first) == 1) res = 1;
        if (symmet(Knots,Knots[index].first) == -1 && (
                   Knots[index].FCTN == charZeroCalc::SIN
                || Knots[index].FCTN == charZeroCalc::TAN
                || Knots[index].FCTN == charZeroCalc::COT
                || Knots[index].FCTN == charZeroCalc::ARCSIN
                || Knots[index].FCTN == charZeroCalc::ARCTAN
                || Knots[index].FCTN == charZeroCalc::SINH
                || Knots[index].FCTN == charZeroCalc::TANH
                || Knots[index].FCTN == charZeroCalc::COTH
                || Knots[index].FCTN == charZeroCalc::ARSINH
                || Knots[index].FCTN == charZeroCalc::ARTANH
                || Knots[index].FCTN == charZeroCalc::ARCOTH
                || Knots[index].FCTN == charZeroCalc::MINUS))
            res = -1;
        if (symmet(Knots,Knots[index].first) == -1 && (
                   Knots[index].FCTN == charZeroCalc::COS
                || Knots[index].FCTN == charZeroCalc::COSH
                || Knots[index].FCTN == charZeroCalc::ABS
                ))
            res = 1;
    }
    if (Knots[index].myType == FunctionKnot::BINARY) {
        if (symmet(Knots,Knots[index].first) == 1 && symmet(Knots,Knots[index].second) == 1) {
            res = 1;
        }
        else if ((Knots[index].myOperation == ADD || Knots[index].myOperation == MINUS)
               && symmet(Knots,Knots[index].first) == -1
               && symmet(Knots,Knots[index].second) == -1)
            res = -1;
        else if (Knots[index].myOperation == MULT || Knots[index].myOperation == DIV) {
            res = symmet(Knots,Knots[index].first) * symmet(Knots,Knots[index].second);
        }
        else if (Knots[index].myOperation == POWER && symmet(Knots,Knots[index].first) == -1) {
            if (Knots[Knots[index].second].myType == FunctionKnot::NUMBER) {
                double pow = Knots[Knots[index].second].value.real();
                if (pow >= 0.0) {
                    int powI = (int) pow;
                    bool integerValue = true;

                    if (pow-powI > 1.0 -zeroBound) powI++;
                    else if (pow-powI> zeroBound) integerValue = false;
                    if (integerValue) {
                        if (powI % 2 == 0) res = 1;
                        else res = -1;
                    }
                }
            }
        }
    }
    return res;
}



int FunctionKnot::getPrecedense() {
    int precedense = 1;

    if (myType == BINARY) {
        if (myOperation == POWER) precedense = 2;
        if (myOperation == MULT) precedense = 3;
        if (myOperation == DIV) precedense = 3;
        if (myOperation == ADD) precedense = 4;
        if (myOperation == MINUS) precedense = 4;
        if (myOperation == LARGER) precedense = 5;
        if (myOperation == LARGEQ) precedense = 5;
        if (myOperation == SMALLER) precedense = 5;
        if (myOperation == SMALLEQ) precedense = 5;
        if (myOperation == EQUAL) precedense = 6;
        if (myOperation == NEQ) precedense = 6;
        if (myOperation == AND) precedense = 7;
        if (myOperation == OR) precedense = 8;
        if (myOperation == NOR) precedense = 8;
        if (myOperation == XOR) precedense = 9;
    }
    return precedense;
}

numReal Function::symmetry() {
    numReal res;
    int i = symmet(Knots,0);

    res.set(i);
    return res;
}

bool constant(const std::vector<FunctionKnot> &Knots, int i) {
    if (Knots[i].myType == FunctionKnot::NUMBER) return true;
    else if (Knots[i].myType == FunctionKnot::UNARY) {
        return constant(Knots,Knots[i].first);
    }
    else if (Knots[i].myType == FunctionKnot::BINARY) {
        return constant(Knots,Knots[i].first) && constant(Knots,Knots[i].second);
    }
    else if (Knots[i].myType == FunctionKnot::THREE) {
        return constant(Knots,Knots[i].first) && constant(Knots,Knots[i].second) && constant(Knots,Knots[i].third);
    }
    else return false;
}

bool Function::isConstant() const{
    return constant(Knots,0);
}

bool linear(const std::vector<FunctionKnot> &Knots, int i) {
    if (constant(Knots,i)) return true;
    else if (Knots[i].myType == FunctionKnot::X) return true;
    else if (Knots[i].myType == FunctionKnot::UNARY) {
        if (Knots[i].FCTN == charZeroCalc::MINUS) {
            return linear(Knots,Knots[i].first);
        }
    }
    else if (Knots[i].myType == FunctionKnot::BINARY) {
        if (Knots[i].myOperation == ADD
         || Knots[i].myOperation == MINUS) {
            return linear(Knots,Knots[i].first) && linear(Knots,Knots[i].second);
        }
        else if (Knots[i].myOperation == MULT) {
            return (constant(Knots,Knots[i].first) && linear(Knots,Knots[i].second))
                || (linear(Knots,Knots[i].first) && constant(Knots,Knots[i].second));
        }
        else if (Knots[i].myOperation == DIV) {
            return linear(Knots,Knots[i].first) && constant(Knots,Knots[i].second);
        }
        else return (constant(Knots,Knots[i].first) && constant(Knots,Knots[i].second));
    }
    return (constant(Knots,Knots[i].first) && constant(Knots,Knots[i].second));
}

bool Function::isLinear() const{
    return linear(Knots,0);
}

std::complex<double> slope(const std::vector<FunctionKnot> &Knots, int i) {
    std::complex<double> a,b;
    bool valid;
    Function component;

    getComponent(Knots,i,component.Knots);
    b = component.eval(cplxOne,valid);
    a = component.eval(cplxZero,valid);
    return b-a;
}

static bool roughtlyInteger(std::complex<double> z) {
    double rz;
    int iz;
    bool valid = true;

    valid = valid && fabs(z.imag()) < zeroBound;
    if (valid) {
        rz = fabs(z.real());
        iz = (int) rz;
        rz = rz - iz;
        valid = rz < zeroBound || rz > 1.0-zeroBound;
    }
    return valid;
}

static bool periodFunc(const std::vector<FunctionKnot> &Knots,
                int i,
                std::complex<double> &z) {
    std::complex<double> factor(0.0,0.0);
    bool periodic = true;

    if (constant(Knots,i)) return false;
    if (linear(Knots,i)) return false;
    if (Knots[i].myType == FunctionKnot::UNARY) {
        if (periodFunc(Knots,Knots[i].first,z)) return true;
        if (Knots[i].FCTN == charZeroCalc::COS
         || Knots[i].FCTN == charZeroCalc::SIN
         || Knots[i].FCTN == charZeroCalc::TAN
         || Knots[i].FCTN == charZeroCalc::COT) {
            //factor.real() = 2*PIC;
        }
        else if (Knots[i].FCTN == charZeroCalc::COS
         || Knots[i].FCTN == charZeroCalc::SIN
         || Knots[i].FCTN == charZeroCalc::TAN
         || Knots[i].FCTN == charZeroCalc::COT) {
            //factor.imag() = 2*PIC;
        }
        else periodic = false;
        periodic = periodic && linear(Knots,Knots[i].first);
        if (periodic) {
            std::complex<double> m = slope(Knots,Knots[i].first);
            periodic = abs(m) > zeroBound;
            if (periodic) z = factor / m;
        }
    }
    else if (Knots[i].myType == FunctionKnot::BINARY) {
        if (constant(Knots,Knots[i].first)) return periodFunc(Knots,Knots[i].second,z);
        if (constant(Knots,Knots[i].second)) return periodFunc(Knots,Knots[i].first,z);
        std::complex<double> a, b, c, d;
        if (periodFunc(Knots,Knots[i].first,a) && periodFunc(Knots,Knots[i].second,b)) {
            c = a/b; d = b/a;
            if (roughtlyInteger(c)) z = a;
            else if (roughtlyInteger(d)) z = b;
            else periodic = false;
        }
        else periodic = false;
    }
    else periodic = false;
    return periodic;
}

bool Function::period(std::complex<double> &z) const {
    return periodFunc(Knots,0,z);
}

static bool realFunc(const std::vector<FunctionKnot> &Knots,int i) {
    bool real = true;

    if (Knots[i].myType == FunctionKnot::X) real = true;
    else if (Knots[i].myType == FunctionKnot::NUMBER) {
        real = fabs(Knots[i].value.imag())<zeroBound;
    }
    else if (Knots[i].myType == FunctionKnot::UNARY) {
        real = realFunc(Knots,Knots[i].first);
    }
    else if (Knots[i].myType == FunctionKnot::BINARY) {
        real = realFunc(Knots,Knots[i].first) && realFunc(Knots,Knots[i].second);
    }
    else if (Knots[i].myType == FunctionKnot::UNARY) {
        real = realFunc(Knots,Knots[i].first) && realFunc(Knots,Knots[i].second) && realFunc(Knots,Knots[i].third);
    }
    return real;
}

bool Function::real() const {
    return realFunc(Knots,0);
}

std::complex<double> Function::eval(FunctionKnot Knot, std::complex<double> point,bool &valid) const {
    valid = true;
    if (Knot.myType == FunctionKnot::NUMBER) return Knot.value;
    else if (Knot.myType == FunctionKnot::UNARY) {
        std::complex<double> z = eval(Knots[Knot.first],point,valid);
        calc.functions(&z, Knot.FCTN);
        double real = z.real(), imag = z.imag();
        valid = valid && ((real == real) && (imag == imag));
        return z;
    }
    else if (Knot.myType == FunctionKnot::BINARY) {
        std::complex<double> l, r;
        l = eval(Knots[Knot.first],point,valid);
        r = eval(Knots[Knot.second],point,valid);
        if      (Knot.myOperation ==   ADD) return l + r;
        else if (Knot.myOperation == MINUS) return l - r;
        else if (Knot.myOperation ==  MULT) return l * r;
        else if (Knot.myOperation ==   DIV) {
            valid = valid && ((r.real() != 0.0) || (r.imag() != 0.0));
            return l / r;
        }
        else if (Knot.myOperation == POWER) {
            if (l.real() == 0.0 && l.imag() == 0.0) {
                //if (r.real() == 0.0 && r.imag() == 0.0) l.real() = 1.0;
                return l;
            }
            else return exp(r*log(l));
        }
        else if (Knot.myOperation == LOG) return log(r)/log(l);
        else if (Knot.myOperation == LARGER) {
            if (fabs(l.imag())<zeroBound && fabs(r.imag()) < zeroBound) {
                if (l.real() > r.real()) return cplxOne;
                else return cplxZero;
            }
            if (abs(l) > abs(r)) return cplxOne;
            else       return cplxZero;
        }
        else if (Knot.myOperation == SMALLER) {
            if (fabs(l.imag())<zeroBound && fabs(r.imag()) < zeroBound) {
                if (l.real() < r.real()) return cplxOne;
                else return cplxZero;
            }
            if (abs(l) < abs(r)) return cplxOne;
            else       return cplxZero;
        }
        else if (Knot.myOperation == SMALLEQ) {
            if (fabs(l.imag()) < zeroBound && fabs(r.imag()) < zeroBound) {
                if (l.real() <= r.real()) return cplxOne;
                else return cplxZero;
            }
            if (abs(l) <= abs(r)) return cplxOne;
            else                  return cplxZero;
        }
        else if (Knot.myOperation == LARGEQ) {
            if (fabs(l.imag()) < zeroBound && fabs(r.imag()) < zeroBound) {
                if (l.real() >= r.real()) return cplxOne;
                else return cplxZero;
            }
            if (abs(l) >= abs(r)) return cplxOne;
            else                  return cplxZero;
        }
        else if (Knot.myOperation == EQUAL) {
            if (l == r) return cplxOne;
            else        return cplxZero;
        }
        else if (Knot.myOperation == NEQ) {
            if (l != r) return cplxOne;
            else        return cplxZero;
        }
        else if (Knot.myOperation == XOR) {
            if ((abs(l) < zeroBound  && abs(r) >= zeroBound) || (abs(l) >= zeroBound  && abs(r) < zeroBound))
                return cplxOne;
            else
                return cplxZero;
        }
        else if (Knot.myOperation == OR) {
            if ((abs(r) >= zeroBound) || (abs(l) >= zeroBound))
                return cplxOne;
            else
                return cplxZero;
        }
        else if (Knot.myOperation == NOR) {
            if ((abs(r) < zeroBound) && (abs(l) < zeroBound))
                return cplxOne;
            else
                return cplxZero;
        }
        else if (Knot.myOperation == AND) {
            if ((abs(r) >= zeroBound) && (abs(l) >= zeroBound))
                return cplxOne;
            else
                return cplxZero;
        }
    }
    else if (Knot.myType == FunctionKnot::THREE) {
        std::complex<double> l, r;
        l = eval(Knots[Knot.first],point,valid);
        if (abs(l) >= zeroBound) r = eval(Knots[Knot.second],point,valid);
        else                     r = eval(Knots[Knot.third ],point,valid);
        return r;
    }
    double real = point.real(), imag = point.imag();
    valid = valid && ((real == real) && (imag == imag));
    return point;
}

QString Function::print(FunctionKnot Knot, unsigned int &depth) {
    QString str;
    if (Knot.myType == FunctionKnot::X) {
        depth = 0;
        return "x";
    }
    else if (Knot.myType == FunctionKnot::NUMBER) {
        depth = 0;
        numCplx z; z.val = Knot.value;
        str = z.print(6);
        if (z.val.real() != 0.0 && z.val.imag() != 0.0) {
            getBrackets(str);
        }
    }
    else if (Knot.myType == FunctionKnot::BINARY) {
        unsigned int depthFirst = 0, depthSecond = 0;

        str = str.append(print(Knots[Knot.first],depthFirst));
        if (Knots[Knot.first].getPrecedense()>Knot.getPrecedense()) getBrackets(str);
        if      (Knot.myOperation == ADD)   str = str.append("+");
        else if (Knot.myOperation == MINUS) str = str.append("-");
        else if (Knot.myOperation == MULT)  str = str.append("*");
        else if (Knot.myOperation == DIV)   str = str.append("/");
        else if (Knot.myOperation == POWER)  str = str.append("^");
        else if (Knot.myOperation == LOG) {
            str = str.append(",");
            str = str.prepend("log(");
        }
        else if (Knot.myOperation == LARGER) str = str.append("&gt;");
        else if (Knot.myOperation == SMALLER) str = str.append("&lt;");
        else if (Knot.myOperation == EQUAL) str = str.append("==");
        else if (Knot.myOperation == NEQ) str = str.append("!=");
        else if (Knot.myOperation == SMALLEQ) str = str.append("&lt;=");
        else if (Knot.myOperation == LARGEQ) str = str.append("&gt;=");
        else if (Knot.myOperation == XOR) str = str.append("XOR");
        else if (Knot.myOperation == OR) str = str.append("OR");
        else if (Knot.myOperation == NOR) str = str.append("NOR");
        else if (Knot.myOperation == AND) str = str.append("AND");
        QString help = print(Knots[Knot.second],depthSecond);
        if (Knots[Knot.second].getPrecedense()>Knot.getPrecedense()) getBrackets(help);
        str+=help;
        if (Knot.myOperation == LOG) str = str.append(")");
        depth = 1;
    }
    else if (Knot.myType == FunctionKnot::UNARY) {
        str = functionTypeToQString(Knot.FCTN);
        str = str.append("(");
        str = str.append(print(Knots[Knot.first],depth));
        str = str.append(")");
        depth = 0;
    }
    else if (Knot.myType == FunctionKnot::THREE) {
        str = "IF(";
        str = str.append(print(Knots[Knot.first],depth));
        str = str.append(",");
        str = str.append(print(Knots[Knot.second],depth));
        str = str.append(",");
        str = str.append(print(Knots[Knot.third],depth));
        str = str.append(")");
    }
    return str;
}

Function Function::translate(numPoly &np) {
    Function xFunc,res,help,factor,power;
    std::complex<double> value;
    bool firstMonomial = true;
    res.setValue(std::complex<double>(0,0));

    for (int i = 0; i< np.mons.size(); i++) {
        if (np.mons[i].real() != 0.0 || np.mons[i].imag() != 0.0) {
            if (i == 0) help.setValue(np.mons[i].val);
            else {
                if (i > 1) {
                    //value.real() = i; value.imag() = 0;
                    power.setValue(value);
                    setOp(&help,xFunc,power,'^');
                }
                else if (i == 1) help.setX();
                if (np.mons[i].val.real() != 1.0 || np.mons[i].val.imag() != 0.0) {
                    factor.setValue(np.mons[i].val);
                    setOp(&help,factor,help,'*');
                }
            }
            if (firstMonomial) {
                res = help;
                firstMonomial = false;
            }
            else setOp(&res,help,res,'+');
        }
    }
    return res;
}

bool setIf(Function *res, Function f, Function g, Function h) {
    res->Knots.clear();
    FunctionKnot Knot;

    Knot.myType = FunctionKnot::THREE;
    Knot.first = 1;
    Knot.second = f.Knots.size()+1;
    Knot.third = f.Knots.size()+g.Knots.size()+1;
    res->Knots.push_back(Knot);
    normalizedAppend(res->Knots,f.Knots);
    normalizedAppend(res->Knots,g.Knots);
    normalizedAppend(res->Knots,h.Knots);
}

bool setOp(Function *res, Function f, Function g, char op) {
    res->Knots.clear();
    FunctionKnot Knot;

    if      (op == '+') Knot.myOperation = ADD;
    else if (op == '-') Knot.myOperation = MINUS;
    else if (op == '*') Knot.myOperation = MULT;
    else if (op == '/') Knot.myOperation = DIV;
    else if (op == '^') Knot.myOperation = POWER;
    else if (op == 'l') Knot.myOperation = LOG;
    else if (op == '>') Knot.myOperation = LARGER;
    else if (op == '<') Knot.myOperation = SMALLER;
    else if (op == 'e') Knot.myOperation = EQUAL;
    else if (op == 'n') Knot.myOperation = NEQ;
    else if (op == 's') Knot.myOperation = SMALLEQ;
    else if (op == 'b') Knot.myOperation = LARGEQ;
    else if (op == 'x') Knot.myOperation = XOR;
    else if (op == 'o') Knot.myOperation = OR;
    else if (op == 'p') Knot.myOperation = NOR;
    else if (op == 'a') Knot.myOperation = AND;
    else return false;
    Knot.myType = FunctionKnot::BINARY;
    Knot.first = 1;
    Knot.second = f.Knots.size()+1;
    res->Knots.push_back(Knot);
    normalizedAppend(res->Knots,f.Knots);
    normalizedAppend(res->Knots,g.Knots);
    return true;
}

bool setFunc(Function &f, Function &g, Function &h, std::string val, int nr) {
    Function res;

    if (nr == 1) {
        charZeroCalc::fctns FCTN = res.calc.findFunction(&val);
        if (FCTN == charZeroCalc::NONE) return false;
        else {
            res.Knots[0].myType = FunctionKnot::UNARY;
            res.Knots[0].first = 1;
            res.Knots[0].FCTN = res.calc.findFunction(&val);
            normalizedAppend(res.Knots,f.Knots);
        }
    }
    else if (nr == 2 && val == "log")
        setOp(&res,f,g,'l');
    else if (nr == 3 && val == "IF")
        setIf(&res,f,g,h);
    else return false;
    f = res;
    return true;
}

QString functionTypeToQString(charZeroCalc::fctns FCTN) {
    QString str;

    if (FCTN == charZeroCalc::ABS) str = "abs";
    else if (FCTN == charZeroCalc::COS) str = "cos";
    else if (FCTN == charZeroCalc::EXP) str = "exp";
    else if (FCTN == charZeroCalc::LN) str = "ln";
    else if (FCTN == charZeroCalc::SIN) str = "sin";
    else if (FCTN == charZeroCalc::TAN) str = "tan";
    else if (FCTN == charZeroCalc::COT) str = "cot";
    else if (FCTN == charZeroCalc::RADIC) str ="radic";
    else if (FCTN == charZeroCalc::ARCSIN) str = "arcsin";
    else if (FCTN == charZeroCalc::ARCCOS) str = "arccos";
    else if (FCTN == charZeroCalc::ARCTAN) str = "arctan";
    else if (FCTN == charZeroCalc::ARCCOT) str = "arccot";
    else if (FCTN == charZeroCalc::CONJ) str = "conj";
    else if (FCTN == charZeroCalc::SINH) str = "sinh";
    else if (FCTN == charZeroCalc::COSH) str = "cosh";
    else if (FCTN == charZeroCalc::TANH) str = "tanh";
    else if (FCTN == charZeroCalc::COTH) str = "coth";
    else if (FCTN == charZeroCalc::ARSINH) str = "arsinh";
    else if (FCTN == charZeroCalc::ARCOSH) str = "arcosh";
    else if (FCTN == charZeroCalc::ARTANH) str = "artanh";
    else if (FCTN == charZeroCalc::ARCOTH) str = "arcoth";
    else if (FCTN == charZeroCalc::REAL) str = "real";
    else if (FCTN == charZeroCalc::IMAG) str = "imag";
    else if (FCTN == charZeroCalc::MINUS) str = "-";
    else if (FCTN == charZeroCalc::POLAR) str = "polar";

    return str;
}

void composite(Function *res, Function *f, Function *g) {
    Function funcLoc;
    funcLoc.Knots = f->Knots;

    FunctionKnot ref = g->Knots[0];
    unsigned int size = funcLoc.Knots.size();
    ref.first += size - 1;
    ref.second += size - 1;
    ref.third += size -1;

    for (unsigned int i; i < size; i++) {
        if (funcLoc.Knots[i].myType == FunctionKnot::X) {
            funcLoc.Knots[i] = ref;
        }
    }
    std::vector<FunctionKnot> copy = g->Knots;
    copy.erase(copy.begin());
    normalizedAppend(funcLoc.Knots,copy);

    *res = funcLoc;
}

static bool applyMultiplicativeSimplification(const std::vector<FunctionKnot> &simple1,
                                              const std::vector<FunctionKnot> &simple2,
                                              std::vector<FunctionKnot> &simplified)
{
    bool executed = true;

    if (simple1[0].myType == FunctionKnot::NUMBER
     && simple1[0].value.imag() == 0.0
     && simple1[0].value.real() == 0.0) {
        simplified = simple1;
    }
    else if (simple2[0].myType == FunctionKnot::NUMBER
     && simple2[0].value.imag() == 0.0
     && simple2[0].value.real() == 0.0) {
        simplified = simple2;
    }
    else if (simple1[0].myType == FunctionKnot::NUMBER
     && simple1[0].value.imag() == 0.0
     && simple1[0].value.real() == 1.0) {
        simplified = simple2;
    }
    else if (simple2[0].myType == FunctionKnot::NUMBER
     && simple2[0].value.imag() == 0.0
     && simple2[0].value.real() == 1.0) {
        simplified = simple1;
    }
    else executed = false;
    return executed;
}

static bool findSummandsWithSameFactor(const std::vector<FunctionKnot> &s1,
                                       const std::vector<FunctionKnot> &s2,
                                       std::vector<FunctionKnot> &factor)
{
    bool found = false;

    if (s1[0].isSum() || s1[0].isBinaryMinus()) {
        std::vector<FunctionKnot> c1, c2;
        getComponent(s1,s1[0].first,c1);
        getComponent(s1,s1[0].second,c2);
        if (!found) found = findSummandsWithSameFactor(c1, c2, factor);
        if (!found) found = findSummandsWithSameFactor(c1, s2, factor);
        if (!found) found = findSummandsWithSameFactor(c2, s2, factor);
    }
    else if (s2[0].isSum() || s1[0].isBinaryMinus()) {
        std::vector<FunctionKnot> c1, c2;
        getComponent(s2,s2[0].first,c1);
        getComponent(s2,s2[0].second,c2);
        if (!found) found = findSummandsWithSameFactor(c1, c2, factor);
        if (!found) found = findSummandsWithSameFactor(c1, s1, factor);
        if (!found) found = findSummandsWithSameFactor(c2, s1, factor);
    }
    else {
        found = findCommonFactor(s1,s2,factor);
    }
    return found;
}

static void executeDistributiveLaw(std::vector<FunctionKnot> &s1,
                                   std::vector<FunctionKnot> &s2,
                                   std::vector<FunctionKnot> &factor,
                                   std::vector<FunctionKnot> &remain,
                                   std::vector<FunctionKnot> &divided,
                                   bool                       sumOp)
{
    if (s1[0].isSum()  || s1[0].isBinaryMinus()) {
        std::vector<FunctionKnot> c1, c2;
        getComponent(s1,s1[0].first,c1);
        getComponent(s1,s1[0].second,c2);
        executeDistributiveLaw(c1, c2, factor, s1, divided,s1[0].isSum());
    }
    else if (divide(s1,factor)) {

        FunctionKnot S(ADD), Z(0.0);

        if (divided.size() == 0) divided = s1;
        else {
            std::vector<FunctionKnot> div = divided;
            normalizedCombi(S,s1,div,divided);
        }
        s1.clear();
        s1.push_back(Z);
    }
    if (s2[0].isSum() || s2[0].isBinaryMinus()) {
        std::vector<FunctionKnot> c1, c2;
        getComponent(s2,s2[0].first,c1);
        getComponent(s2,s2[0].second,c2);
        executeDistributiveLaw(c1, c2, factor, s2, divided, s2[0].isSum());
    }
    else if (divide(s2,factor)) {
        FunctionKnot S(ADD), Z(0.0);

        if (divided.size() == 0) divided = s2;
        else {
            std::vector<FunctionKnot> div = divided;
            normalizedCombi(S,s2,div,divided);
        }
        s2.clear();
        s2.push_back(Z);
    }
    FunctionKnot S(ADD);
    if (!sumOp) S.myOperation = MINUS;
    normalizedCombi(S,s1,s2,remain);
}

static bool applyDistributiveLaw(std::vector<FunctionKnot> &simple1,
                                 std::vector<FunctionKnot> &simple2,
                                 std::vector<FunctionKnot> &simplified,
                                 bool                       sumOp)
{
    std::vector<FunctionKnot> factor, remain, quot, prod;

    if (findSummandsWithSameFactor(simple1,simple2,factor)){
        executeDistributiveLaw(simple1,simple2,factor,remain,quot,sumOp);

        FunctionKnot A(ADD), M(MULT);
        normalizedCombi(M,factor,quot,prod);
        normalizedCombi(A,remain,prod,simplified);
        return true;
    }
    return false;
}

static bool applyAdditiveSimplification(std::vector<FunctionKnot> &simple1,
                                        std::vector<FunctionKnot> &simple2,
                                        std::vector<FunctionKnot> &simplified)
{
    bool executed = false;

    if (simple1[0].myType == FunctionKnot::NUMBER
     && simple1[0].value.imag() == 0.0
     && simple1[0].value.real() == 0.0) {
        executed = true;
        simplified = simple2;
    }
    else if (simple2[0].myType == FunctionKnot::NUMBER
          && simple2[0].value.imag() == 0.0
          && simple2[0].value.real() == 0.0) {
        executed = true;
        simplified = simple1;
    }
    else if (compare(simple1,simple2,0,0)) {
        executed = true;

        FunctionKnot K, Two(2.0);
        K.myType = FunctionKnot::BINARY;
        K.myOperation = MULT;
        K.first = 1;
        K.second = 2;
        simplified.clear();
        simplified.push_back(K);
        simplified.push_back(Two);
        normalizedAppend(simplified,simple1);
    }
    else if (simple2[0].isUnaryMinus()) {
        executed = true;
        std::vector<FunctionKnot> s2;
        FunctionKnot K(MINUS);
        K.first = 1;
        K.second = 2;
        getComponent(simple2,simple2[0].first,s2);
        normalizedCombi(K,simple1,s2,simplified);
    }
    else if (simple1[0].isUnaryMinus()) {
        executed = true;
        std::vector<FunctionKnot> s1;
        FunctionKnot K(MINUS);
        K.first = 1;
        K.second = 2;
        getComponent(simple1,simple1[0].first,s1);
        normalizedCombi(K,simple2,s1,simplified);
    }
    else executed = applyDistributiveLaw(simple1,simple2,simplified,true);
    return executed;
}

static bool applySubtractiveSimplification(std::vector<FunctionKnot> &simple1,
                                           std::vector<FunctionKnot> &simple2,
                                           std::vector<FunctionKnot> &simplified)
{
    bool executed = false;

    if (simple1[0].myType == FunctionKnot::NUMBER
     && simple1[0].value.imag() == 0.0
     && simple1[0].value.real() == 0.0) {
        executed = true;
        FunctionKnot K;
        K.myType = FunctionKnot::UNARY;
        K.FCTN = charZeroCalc::MINUS;
        K.first = 1;
        simplified.push_back(K);
        normalizedAppend(simplified,simple2);
    }
    else if (simple2[0].myType == FunctionKnot::NUMBER
          && simple2[0].value.imag() == 0.0
          && simple2[0].value.real() == 0.0) {
        executed = true;
        simplified = simple1;
    }
    else if (compare(simple1,simple2,0,0)) {
        executed = true;

        FunctionKnot K(0.0);
        simplified.push_back(K);
    }
    else if (simple2[0].isUnaryMinus()) {
        executed = true;
        std::vector<FunctionKnot> s2;
        FunctionKnot K(ADD);
        K.first = 1;
        K.second = 2;
        getComponent(simple2,simple2[0].first,s2);
        normalizedCombi(K,simple1,s2,simplified);
    }
    else executed = applyDistributiveLaw(simple1,simple2,simplified,false);
    return executed;
}

static bool applyPowerSimplification(const std::vector<FunctionKnot> &simple1,
                                     const std::vector<FunctionKnot> &simple2,
                                     std::vector<FunctionKnot> &simplified)
{
    bool executed = true;

    if (simple2[0].myType == FunctionKnot::NUMBER
     && simple2[0].value.imag() == 0.0
     && simple2[0].value.real() == 1.0) {
        simplified = simple1;
    }
    else if (simple2[0].myType == FunctionKnot::NUMBER
          && simple2[0].value.imag() == 0.0
          && simple2[0].value.real() == 0.0) {
        FunctionKnot K(1.0);
        simplified.clear();
        simplified.push_back(K);
    }
    else if (simple1[0].myType == FunctionKnot::NUMBER
          && simple1[0].value.imag() == 0.0
         && (simple1[0].value.real() == 0.0 || simple1[0].value.real() == 1.0)) {
        simplified = simple1;
    }
    else executed = false;
    return executed;
}

static bool combineSimplification(const FunctionKnot &Knot,
                                  std::vector<FunctionKnot> &simple1,
                                  std::vector<FunctionKnot> &simple2,
                                  std::vector<FunctionKnot> &simplified)
{
    bool executed = false;

    if (simple1[0].myType == FunctionKnot::NUMBER && simple2[0].myType == FunctionKnot::NUMBER) {
        Function f;
        bool valid;
        normalizedCombi(Knot,simple1,simple2,f.Knots);
        FunctionKnot K(f.eval(0.0,valid));
        simplified.clear();
        simplified.push_back(K);
        executed = true;
    }
    else if (Knot.myOperation == MULT) {
        if (!executed) executed = applyMultiplicativeSimplification(simple1,simple2,simplified);
        if (!executed) executed = applyMultiplicativeSimplification(simple2,simple1,simplified);
    }
    else if (Knot.myOperation == ADD) {
        if (!executed) executed = applyAdditiveSimplification(simple1,simple2,simplified);
        if (!executed) executed = applyAdditiveSimplification(simple2,simple1,simplified);
    }
    else if (Knot.myOperation == MINUS) {
        if (!executed) executed = applySubtractiveSimplification(simple1,simple2,simplified);
    }
    else if (Knot.myOperation == POWER) {
        executed = applyPowerSimplification(simple1,simple2,simplified);
    }
    if (!executed) normalizedCombi(Knot,simple1,simple2,simplified);
    return executed;
}

static bool simplify(const std::vector<FunctionKnot> &Knots,
                     int index,
                     std::vector<FunctionKnot> &simplified) {
    bool exe, executed = false;

    if (Knots[index].myType == FunctionKnot::BINARY) {
        std::vector<FunctionKnot> simple1, simple2;
        exe = simplify(Knots,Knots[index].first,simple1);
        executed = executed || exe;
        exe =  simplify(Knots,Knots[index].second,simple2);
        executed = executed || exe;
        exe = combineSimplification(Knots[index],simple1,simple2,simplified);
        executed = executed || exe;
    }
    else if (Knots[index].myType == FunctionKnot::UNARY) {
        if (Knots[index].FCTN == charZeroCalc::MINUS
         && Knots[Knots[index].first].FCTN == charZeroCalc::MINUS) {
            getComponent(Knots,Knots[Knots[index].first].first,simplified);
            executed = true;
        }
        else if (Knots[index].FCTN == charZeroCalc::MINUS
              && Knots[Knots[index].first].myType == FunctionKnot::NUMBER
              && fabs(Knots[Knots[index].first].value.real()) < zeroBound
              && fabs(Knots[Knots[index].first].value.imag()) < zeroBound) {
            FunctionKnot K(std::complex<double>(0.0,0.0));
            simplified.clear();
            simplified.push_back(K);
            executed = true;
        }
        else {
            std::vector<FunctionKnot> simple1;
            executed = simplify(Knots,Knots[index].first,simple1);
            FunctionKnot K = Knots[index];
            K.first = 1;
            simplified.clear();
            simplified.push_back(K);
            normalizedAppend(simplified,simple1);
        }
    }
    else getComponent(Knots,index,simplified);
    return executed;
}

bool derivative(Function &der, const Function &f) {
    std::vector<FunctionKnot> res;
    bool valid = true;

    der.Knots.clear();
    valid = valid && derivateKnot(f.Knots,0,der.Knots);

    while (simplify(der.Knots,0,res)) {
        der.Knots = res;
        res.clear();
    }
    return valid;
}

void line(Function &f, std::complex<double> m, std::complex<double> b) {
    FunctionKnot mKnot(m), xKnot, opKnot(ADD), bKnot(b);

    f.Knots.clear();
    opKnot.first = 1;
    opKnot.second = 4;
    f.Knots.push_back(opKnot);
    opKnot.myOperation=MULT;
    opKnot.first = 2;
    opKnot.second = 3;
    f.Knots.push_back(opKnot);
    f.Knots.push_back(mKnot);
    f.Knots.push_back(xKnot);
    f.Knots.push_back(bKnot);
}

bool tangent (Function &t, const Function &f, const numReal &z)
{
    Function der;
    bool valid;
    std::complex<double> point, m, b;
    //point.real() = z.get();
    //point.imag() = 0.0;

    if (derivative(der,f)) {
        m = der.eval(point,valid);
        b = f.eval(point,valid)-m*point;
        line(t,m,b);
        return true;
    }
    return false;
}

bool normal (Function &t, const Function &f, const numReal &z)
{
    Function der;
    bool valid;
    std::complex<double> point, m, b;
    //point.real() = z.get();
    //point.imag() = 0.0;

    if (derivative(der,f)) {
        m = (-1.0)/(der.eval(point,valid));
        b = f.eval(point,valid)-m*point;
        FunctionKnot mKnot(m), xKnot, opKnot(ADD), bKnot(b);
        t.Knots.clear();
        opKnot.first = 1;
        opKnot.second = 4;
        t.Knots.push_back(opKnot);
        opKnot.myOperation=MULT;
        opKnot.first = 2;
        opKnot.second = 3;
        t.Knots.push_back(opKnot);
        t.Knots.push_back(mKnot);
        t.Knots.push_back(xKnot);
        t.Knots.push_back(bKnot);
        return true;
    }
    return false;
}

static void getLineZero(const Function &L, numReal &z) {
    if (L.Knots[2].value.real() == 0.0) {
        double d = z.get();
        d+=1.0;
        z.set(d);
    }
    else {
        std::complex<double> w = -L.Knots[4].value/L.Knots[2].value;
        z.set(w.real());
    }
}

static bool isRealPeriodic(const Function &f, double &p) {
    std::complex<double> z;
    bool isPeriodic = f.period(z);
    isPeriodic = isPeriodic && fabs(z.imag()) < zeroBound;
    if (isPeriodic = true) {
        p = z.real();
        if (p < 0.0) p = -p;
    }
    return isPeriodic;
}

static bool getStartingPoint(const Function &f,numReal &z) {
    std::complex<double> x(z.get(),0.0),w;
    bool valid = false;
    unsigned int count = 0;

    do {
        w = f.eval(x,valid);
        //if (!valid) x.real() = x.real() + 0.1;
        count++;
    } while (!valid && count < 10);
    if (valid) z.set(x.real());

    return valid;
}

static bool getZero(const Function &f, numReal &z, double period) {
    Function t;
    numCplx w(1.0,0.0);
    double zval, zOld, diff;
    bool valid = true;

    z.set(0.0);
    valid = valid && getStartingPoint(f,z);

    for (int i = 0; i < 50 && valid; i++) {
        tangent(t,f,z);
        zOld = z.get();
        getLineZero(t,z);
        diff = fabs(zOld-z.get());
        zval = z.get();
        if (fabs(period) > zeroBound) {
            if (fabs(zval) > 100*period) break;
            while (zval >= period) zval = zval - period;
            while (zval <0.0) zval = zval + period;
        }
        z.set(zval);
        //w.val.real() = z.get();
        //w.val.imag() = 0.0;
        w.val=f.eval(w.val,valid);  
    }
    if (zOld != zOld || fabs(w.val.real()) > zeroBound || diff > 0.001) {
        Function secant;
        numReal as, bs;
        as.set(0.0); bs.set(1.0);
        valid = getStartingPoint(f,as);
        valid = valid && getStartingPoint(f,bs);
        std::complex<double> a(as.get(),0.0), b(bs.get(),0.0), c, fa, fb, m, bl;

        for (int i = 0 ; i < 100; i++) {
            fa = f.eval(a,valid);
            fb = f.eval(b,valid);
            m = (fb-fa)/(b-a);
            bl = fa-m*a;
            line(secant,m,bl);
            getLineZero(secant,z);
            //b.imag() = 0.0;
            a = b;
            zval = z.get();
            if (fabs(period) > zeroBound) {
                if (fabs(zval) > 100*period) break;
                while (zval >= period) zval = zval - period;
                while (zval <0.0) zval = zval + period;
            }
            z.set(zval);
            //b.real() = z.get();
            diff = fabs(a.real() - b.real());
            if (fabs(f.eval(b,valid).real()) < zeroBound) break;
        }
        w.val = f.eval(b,valid);
    }
    return fabs(w.val.real()) < zeroBound && diff < 0.001;
}

bool zeroes(Function f, std::vector<numReal> &z) {
    Function factor;
    std::vector<FunctionKnot> Knots;
    FunctionKnot Knot(DIV);
    std::complex<double> m(1.0,0.0), b;
    numReal zEntry;
    double p,period = 0.0;
    bool isPeriodic = isRealPeriodic(f,p);
    if (isPeriodic) period = p;


    z.clear();
    for (int i = 0; i < 10; i++) {
        if (getZero(f,zEntry,period)) {
            //z.push_back(zEntry);
            //b.real() = -zEntry.get();
            //b.imag() = 0.0;
            line(factor,m,b);
            normalizedCombi(Knot,f.Knots,factor.Knots,Knots);
            f.Knots = Knots;
        }
        else break;
    }
}

bool extrema(Function &f, std::vector<numReal> &extreme) {
    Function der, nextDer;
    numCplx w;
    std::vector<numReal> z;
    int  order=1;
    bool valid = true;

    valid = valid && derivative(der,f);

    valid = valid && zeroes(der,z);
    if (valid) {
        for (int i = 0; i < z.size(); i++) {
            order = 1;
            derivative(der,f);
            do {
                derivative(nextDer,der);
                der = nextDer;
                order++;

                //w.val.real() = z[i].get(); w.val.imag() = 0.0;
                w.val = der.eval(w.val,valid);
            } while (fabs(w.val.real()) < zeroBound);
            if (order % 2 == 0) {
                extreme.push_back(z[i]);
            }
        }
    }
    return extreme.size() > 0;
}

bool inflexionPoint(Function &f, std::vector<numReal> &inflexion) {
    Function der;

    derivative(der,f);
    return extrema(der,inflexion);
}

double simpson(const Function &f, const double a, const double b) {
    std::complex<double> z(0.0,0.0), s, four(4.0,0), factor((b-a)/6.0,0.0);
    bool valid;

    /*z.real() = a;
    s = f.eval(z,valid);
    z.real() = (a+b)/2;
    s = s + four*f.eval(z,valid);
    z.real() = b;*/
    s = s + f.eval(z,valid);
    s = s * factor;
    return s.real();
}

double integral(const Function &f, numReal a, numReal b) {
    const double stepSize = 0.1;
    double leftBorder, rightEnd, s = 0.0;

    leftBorder = a.get();
    rightEnd = b.get();

    while (leftBorder + stepSize < rightEnd) {
        s += simpson(f,leftBorder,leftBorder+stepSize);
        leftBorder += stepSize;
    }
    s += simpson(f,leftBorder,rightEnd);
    return s;
}
