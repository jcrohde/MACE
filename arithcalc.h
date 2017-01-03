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

#ifndef ARITHCALC_H
#define ARITHCALC_H

/*#include <gmp.h>
#include "math.h"
#include "math/variables/scalar/maceint.h"
#include "math/variables/polynomial/numpoly.h"
#include "math/variables/scalar/macerest.h"
#include "math/variables/polynomial/restpoly.h"
#include "math/variables/polynomial/algpoly.h"


#ifndef INTCONSTS
#define INTCONSTS
const MaceInt two(2);
const MaceInt one(1);
const MaceInt zero(0);
#endif


class arithCalc{
public:
    enum twoPolyFctn{NO, MOD, GCD, LCM};
    twoPolyFctn curPFctn;

    enum intFctn{NOI, BINO, MULTI, FAC, FACNUM, FACSUM, FIBO, LAMBDA, NUMFAC, PHI, PIF, PRIMS,
                 PSI, JACO, LEGS, LUC, NEXT, SMPRIM};
    intFctn iFctn;

    twoPolyFctn find2polyFctn(std::string *str);
    intFctn find2intFctn(std::string *str);
    intFctn findIntFctn(const std::string *str);

    void twoRPFctn(restPoly *a, restPoly *b, twoPolyFctn pFctn);
    void twoPFctn(algPoly *res, algPoly &a, algPoly &b, twoPolyFctn pFctn);
    void twoIFctn(MaceInt *a, MaceInt *b, twoPolyFctn pFctn);

    bool twoIntFctn( MaceInt *a, MaceInt *b, intFctn iFunc);
    void intFunc(MaceInt *a, unsigned int help, intFctn iFunc);

    QString factors(MaceInt j);
    QString factors(numPoly p);
    QString factors(restPoly p);
    MaceInt facnum(MaceInt i);
    MaceInt facsum(MaceInt i);

    MaceInt pi(MaceInt i);
    int lambda (MaceInt i);
    MaceInt phi(MaceInt i);
    MaceInt psi(MaceInt i);

    template <class T> T max(T a, T b);
    template <class T> T min(T a, T b);

    template <class T>
    void pgcd(T &res, const T &a, const T &b);
    template <class T>
    void plcm(T &res, const T &a, const T &b);
    template <class T> void exEu(T &res, const T &a, T &b, T &s, T &t);

    QString intExEu(MaceInt a, MaceInt b, MaceInt characteristic);
    template <class T>
    QString ExEu(T a, T b, MaceInt characteristic);
    QString iExEu(algPoly  a, algPoly  b, MaceInt characteristic);
    QString iExEu(restPoly a, restPoly b, MaceInt characteristic);

    MaceInt prime(MaceInt i);
    MaceInt numberOfPrimes(MaceInt i);
    int smallPrimeTest(MaceInt n);
};*/


#endif // ARITHCALC_H

