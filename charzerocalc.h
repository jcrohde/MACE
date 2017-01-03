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

#ifndef CHARZEROCALC_H
#define CHARZEROCALC_H

#include <QString>

class charZeroCalc
{
public:
    enum fctns{
        NONE,ABS,COS,EXP,LN,SIN,TAN,COT,RADIC,ARCSIN, ARCCOS, REAL, IMAG, POLAR,
        ARCTAN, ARCCOT, CONJ, SINH, COSH, TANH, COTH, ARSINH, ARCOSH, ARTANH, ARCOTH,
        MINUS
    };

    charZeroCalc();

    fctns findFunction(std::string *choice);
};

#endif // CHARZEROCALC_H
