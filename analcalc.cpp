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

#include "analcalc.h"

analCalc::analCalc()
{
}

analCalc::fctn analCalc::findRealFctn(std::string *str){
    fctn curFctn =NONE;

    if (*str == "Ai") curFctn == AI;
    else if (*str == "&Gamma;") curFctn = GAMMA;
    else if (*str == "zeta" || *str == "&zeta;") curFctn = ZETA;
    else if (*str == "K") curFctn = K;
    else if (*str == "gamma") curFctn = GAMMA;
    else if (*str == "lgamma") curFctn = LGAMMA;
    else if (*str == "digamma") curFctn = DIGAMMA;
    else if (*str == "E") curFctn = E;
    else if (*str == "Ei") curFctn = EI;
    else if (*str == "erf") curFctn = ERF;

    return curFctn;
}

analCalc::fctn analCalc::findIntDoubleFctn(std::string str){
    fctn curFctn =NONE;

    if (str =="legPol") curFctn = LEGENDRE;
    else if(str =="lagPol") curFctn = LAGUERRE;
    else if (str == "herPol") curFctn = HERMIT;
    else if (str == "En") curFctn = EN;

    return curFctn;
}

analCalc::fctn analCalc::findDoubleDoubleDoubleFctn(std::string str){
    fctn curFctn = NONE;

    if (str =="PI") curFctn = E3;
    if (str =="betai") curFctn = BETAI;

    return curFctn;
}

analCalc::fctn analCalc::findDoubleDoubleFctn(std::string str){
    fctn curFctn = NONE;

    if (str =="J") curFctn = BESSEL;
    else if(str =="Y") curFctn = NEUMANN;
    else if (str == "F") curFctn = E1;
    else if (str == "E2") curFctn = E2;
    else if (str == "B") curFctn = BETA;
    //else if (str == "gammai") curFctn = GAMMAI;
    else if (str == "gammap") curFctn = GAMMAP;
    else if (str == "dgammai") curFctn = DERGAMMAP;

    return curFctn;
}

void analCalc::log_func(double *a, double *b){
    *a = log(*b)/log(*a);
}

bool analCalc::doubleFctn(double *d, fctn curFctn){
    try{
        if (curFctn == K) *d = boost::math::ellint_1(*d);
        else if (curFctn == GAMMA) *d = boost::math::tgamma(*d);
        else if (curFctn == LGAMMA) *d = boost::math::lgamma(*d);
        else if (curFctn == DIGAMMA) *d = boost::math::digamma(*d);
        else if (curFctn == ZETA) *d = boost::math::zeta(*d);
        else if (curFctn == E) *d = boost::math::ellint_2(*d);
        else if (curFctn == EI) *d = boost::math::expint(*d);
        else if (curFctn == ERF) *d = boost::math::erf(*d);
    }
    catch ( ... ){
        return false;
    }
    return (*d == *d);
}

bool analCalc::intDoubleFctn(int i, double &d, fctn curFctn){
    double res = 0.0;
    try{
        if (curFctn == LEGENDRE) res = boost::math::legendre_p(i,d);
        else if (curFctn == LAGUERRE) res = boost::math::laguerre(i,d);
        else if (curFctn == HERMIT) res = boost::math::hermite(i,d);
        else if (curFctn == EN) res = boost::math::expint(i,d);
    }
    catch ( ... ){
        return false;
    }
    d = res;
    return (d == d);
}

bool analCalc::doubleDoubleFctn(double &a, double b, fctn curFctn){
    double res = 0.0;
    try{
       if (curFctn == BESSEL) res = boost::math::cyl_bessel_j(a,b);
       else if (curFctn == NEUMANN) res = boost::math::cyl_neumann(a,b);
       else if (curFctn == E1) res = boost::math::ellint_1(b,a);
       else if (curFctn == BETA) res = boost::math::beta(a,b);
       else if (curFctn == E2) res = boost::math::ellint_2(b,a);
       else if (curFctn == GAMMAP) res = boost::math::gamma_p(a,b);
       else if (curFctn == DERGAMMAP) res = boost::math::gamma_p_derivative(a,b);
    }
    catch ( ... ){
        return false;
    }
    a = res;
    return (a == a);
}

bool analCalc::doubleDoubleDoubleFctn(double &a, double b, double c, fctn curFctn){
    double res = 0.0;

    try{
       if (curFctn == E3) res = boost::math::ellint_3(c,a,b);
       else if (curFctn == BETAI) res = boost::math::beta(a,b,c);
    }
    catch ( ... ){
        return false;
    }
    a = res;
    return (a == a);
}

bool analCalc::analFctn(double *z, charZeroCalc::fctns FCTN){
    try{
        if (FCTN == ABS) *z = fabs(*z);
        else if (FCTN == COS) *z = cos(*z);
        else if (FCTN == EXP) *z = exp(*z);
        else if (FCTN == LN) *z = log(*z);
        else if (FCTN == SIN) *z = sin(*z);
        else if (FCTN == TAN) *z = tan(*z);
        else if (FCTN == COT) *z = 1/tan(*z);
        else if (FCTN == RADIC) *z = sqrt(*z);
        else if (FCTN == ARCSIN) *z = asin(*z);
        else if (FCTN == ARCCOS) *z = acos(*z);
        else if (FCTN == ARCTAN) *z = atan(*z);
        else if (FCTN == ARCCOT){
            double d = 1.5708;
            *z = d-atan(*z);
        }
        else if (FCTN == CONJ) *z = *z;
        else if (FCTN == SINH) *z = sinh(*z);
        else if (FCTN == COSH) *z = cosh(*z);
        else if (FCTN == TANH) *z = tanh(*z);
        else if (FCTN == COTH) *z = 1/tanh(*z);
        else if (FCTN == ARSINH) *z = asinh(*z);
        else if (FCTN == ARCOSH) *z = acosh(*z);
        else if (FCTN == ARTANH) *z = atanh(*z);
        else if (FCTN == ARCOTH) *z = atanh(1 / *z);
        else if (FCTN == IMAG) { double d = 0.0; *z = d; }
    }
    catch ( ... ){
        return false;
    }
    return (*z == *z);
}
