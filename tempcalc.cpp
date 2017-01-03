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

#include "tempcalc.h"

tempCalc::tempCalc()
{
}

tempCalc::tempFctn tempCalc::findXIntFctn(std::string &str){
    curFctn = NO;

    if (str == "risFac") curFctn = RISFAC;
    else if (str == "falFac") curFctn = FALFAC;

    return curFctn;
}

template <class T>
bool tempCalc::xIntFctn(T &a, int &b, tempFctn fctn) {
    try {
       if (fctn==RISFAC) a = boost::math::rising_factorial(a,b);
       else if (fctn==FALFAC) a = boost::math::falling_factorial(a,b);
    }
    catch ( ... ){
        return false;
    }
    return a == a;
}

bool tempCalc::doubleIntFctn(double &a, int &b, tempFctn fctn) {
    return xIntFctn(a,b,fctn);
}

bool tempCalc::intIntFctn(int &a, int &b, tempFctn fctn) {
    return xIntFctn(a,b,fctn);
}
