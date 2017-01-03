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

#include "fctncalc.h"

static double arg(std::complex<double> z) {
    double res;
    if(z.real() > 0){res = atan(z.imag()/z.real());}
    else if(z.real()==0.0){
        if (z.imag()<0){res = -PI/2;}
        else {res = PI/2;}
    }
    else{
        if (z.imag() < 0){res = atan(z.imag()/z.real())-PI;}
        else {res = atan(z.imag()/z.real())+PI;}
    }
    return res;
}

bool fctnCalc::functions(std::complex<double> *z, charZeroCalc::fctns FCTN) const {
    bool valid = true;

    if (FCTN == ABS) *z = abs(*z);
    else if (FCTN == COS) *z = cos(*z);
    else if (FCTN == EXP) *z = exp(*z);
    else if (FCTN == LN) *z = log(*z);
    else if (FCTN == SIN) *z = sin(*z);
    else if (FCTN == TAN) *z = tan(*z);
    else if (FCTN == COT){
        std::complex<double> one(1,0);
        *z = one/tan(*z);
    }
    else if (FCTN == RADIC) *z = sqrt(*z);
    else if (FCTN == ARCSIN) *z = boost::math::asin(*z);
    else if (FCTN == ARCCOS) *z = boost::math::acos(*z);
    else if (FCTN == ARCTAN) *z = boost::math::atan(*z);
    else if (FCTN == ARCCOT){
        std::complex<double> res(1.5708,0);
        *z =res-boost::math::atan(*z);
    }
    else if (FCTN == CONJ) *z = conj(*z);
    else if (FCTN == SINH) *z = sinh(*z);
    else if (FCTN == COSH) *z = cosh(*z);
    else if (FCTN == TANH) *z = tanh(*z);
    else if (FCTN == COTH){
        std::complex<double> one(1,0);
        *z = one/tanh(*z);
    }
    else if (FCTN == ARSINH) *z = boost::math::asinh(*z);
    else if (FCTN == ARCOSH) *z = boost::math::acosh(*z);
    else if (FCTN == ARTANH) *z = boost::math::atanh(*z);
    else if (FCTN == ARCOTH){
        std::complex<double> one(1,0);
        *z = boost::math::atanh(one / *z);
    }
    //else if (FCTN == REAL) z->imag() = 0.0;
    //else if (FCTN == IMAG) {z->real() = z->imag(); z->imag() = 0.0;}
    else if (FCTN == MINUS) *z = -(*z);
    else if (FCTN == POLAR) *z = toPolar(*z);
    else valid = false;
    return (*z == *z);
}

void fctnCalc::log_func(numCplx *a, numCplx *b){
    a->val = log(b->val)/log(a->val);
}

std::complex<double> fctnCalc::toPolar(std::complex<double> z) const {
    std::complex<double> res;
    double im, re = abs(z);
    if(z.imag()>= 0){
         im = arg(z);
    }
    else{
         im = arg(z)+2*PI;
    }
    res.real(re); res.imag(im);
    return res;
}

numCplx fctnCalc::polarToSphere(numCplx z){
    numCplx res;
    res.val.imag(z.val.imag());
    res.val.real(2*atan(1/z.val.real()));
    return res;
}
