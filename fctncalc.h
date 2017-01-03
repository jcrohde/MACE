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

#ifndef FCTNCALC_H
#define FCTNCALC_H
#include <boost/math/complex/acosh.hpp>
#include <boost/math/complex/atan.hpp>
#include <boost/math/complex/asin.hpp>
#include <boost/math/complex/acos.hpp>
#include <boost/math/complex/atanh.hpp>
#include <boost/math/complex/asinh.hpp>
#include "math/variables/scalar/numcplx.h"
#include "math/functiondistributors/charzerocalc.h"

class fctnCalc : public charZeroCalc {
public:
    bool findRealFunction(QString *choice);

    bool functions(std::complex<double> *z, charZeroCalc::fctns FCTN) const;

    void log_func(numCplx *a, numCplx *b);
    std::complex<double> toPolar(std::complex<double> z) const;
    numCplx polarToSphere(numCplx z);
};




#endif // FCTNCALC_H
