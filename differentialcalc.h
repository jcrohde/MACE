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

#ifndef DIFFERENTIALCALC_H
#define DIFFERENTIALCALC_H

#include "math/variables/function.h"

class differentialCalc
{
public:
    enum func {
        DERIVATIVE, TANGENT, NORMAL, EXTREMA, INFLEXION, ZEROES, SYMMETRY, PERIOD, NONE
    };

    func findCplxFunc(std::string &str);
    func findVectorialFunc(std::string &str);
    func findLineFunc(std::string &str);

    bool cplxFunc(func FCTN, Function &func, std::complex<double> &z);
    bool vectorialFunc(func FCTN, Function &func, std::vector<numReal> &z);
    bool lineFunc(func FCTN, Function &func, numReal &z);

    differentialCalc();
};

#endif // DIFFERENTIALCALC_H
