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

#ifndef TEMPCALC_H
#define TEMPCALC_H

#include <QString>
#include <boost/math/special_functions/factorials.hpp>
#include "math/variables/scalar/numcplx.h"
#include "math/variables/scalar/maceint.h"

class tempCalc
{
public:
    enum tempFctn{NO, RISFAC, FALFAC};
    tempFctn curFctn;

    tempFctn findXIntFctn(std::string &str);
    template <class T> bool xIntFctn( T &a, int &b, tempFctn fctn);
    bool doubleIntFctn(double &a, int &b, tempFctn fctn);
    bool intIntFctn(int &a, int &b, tempFctn fctn);

    tempCalc();
};

#endif // TEMPCALC_H
