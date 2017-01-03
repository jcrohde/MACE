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

#ifndef ANALCALC_H
#define ANALCALC_H

#include <cmath>
#include <boost/math/special_functions/laguerre.hpp>
#include <boost/math/special_functions/legendre.hpp>
#include <boost/math/special_functions/hermite.hpp>
#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/ellint_1.hpp>
#include <boost/math/special_functions/ellint_2.hpp>
#include <boost/math/special_functions/ellint_3.hpp>
#include <boost/math/special_functions/zeta.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/beta.hpp>
#include <boost/math/special_functions/expint.hpp>
#include <boost/math/special_functions/erf.hpp>
#include <QString>
#include "math/variables/scalar/numcplx.h"
#include "charzerocalc.h"

class analCalc : public charZeroCalc
{
public:
    enum fctn{
        NONE, AI, LEGENDRE, LAGUERRE, HERMIT, NEUMANN, BESSEL, E1, E2, LGAMMA, DIGAMMA,
        K, E, E3, ZETA, GAMMA, BETA, EN, EI, ERF, GAMMAI, GAMMAP, BETAI, DERGAMMAP
    };

    analCalc();

    fctn findRealFctn(std::string *str);
    fctn findIntDoubleFctn(std::string str);
    fctn findDoubleDoubleFctn(std::string str);
    fctn findDoubleDoubleDoubleFctn(std::string str);

    void log_func(double *a, double *b);
    bool doubleFctn(double *d, fctn curFunc);
    bool intDoubleFctn(int i, double &d, fctn curFunc);
    bool doubleDoubleFctn(double &a, double b, fctn curFunc);
    bool doubleDoubleDoubleFctn(double &a, double b, double c, fctn curFunc);

    bool analFctn(double *d, charZeroCalc::fctns FCTN);
};

#endif // ANALCALC_H
