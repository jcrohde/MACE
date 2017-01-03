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

#include "differentialcalc.h"

differentialCalc::differentialCalc()
{
}

differentialCalc::func differentialCalc::findCplxFunc(std::string &str) {
    func FCTN = NONE;

    if      (str == "period")   FCTN = PERIOD;
    else if (str == "symmetry") FCTN = SYMMETRY;

    return FCTN;
}

differentialCalc::func differentialCalc::findVectorialFunc(std::string &str) {
    func FCTN = NONE;

    if      (str == "zeroes")    FCTN = ZEROES;
    else if (str == "extrema")   FCTN = EXTREMA;
    else if (str == "inflexion") FCTN = INFLEXION;

    return FCTN;
}

differentialCalc::func differentialCalc::findLineFunc(std::string &str) {
    func FCTN = NONE;

    if      (str == "tangent") FCTN = TANGENT;
    else if (str == "normal")  FCTN = NORMAL;

    return FCTN;
}

bool differentialCalc::cplxFunc(func FCTN, Function &func, std::complex<double> &z) {
    bool valid = true;

    if (FCTN == PERIOD) valid = func.period(z);
    if (FCTN == SYMMETRY) {
        //z.real() = func.symmetry().get();
        //z.imag() = 0.0;
    }
    return valid;
}

bool differentialCalc::vectorialFunc(func FCTN, Function &func, std::vector<numReal> &z) {
    bool foundPoint=false;

    if      (FCTN == ZEROES)    foundPoint = zeroes(func,z);
    else if (FCTN == EXTREMA)   foundPoint = extrema(func,z);
    else if (FCTN == INFLEXION) foundPoint = inflexionPoint(func,z);
    return foundPoint;
}

bool differentialCalc::lineFunc(func FCTN, Function &func, numReal &z) {
    bool valid = true;
    Function line;

    if      (FCTN == TANGENT)   valid = tangent(line,func,z);
    else if (FCTN == NORMAL)    valid = normal(line,func,z);
    func = line;

    return valid;
}
