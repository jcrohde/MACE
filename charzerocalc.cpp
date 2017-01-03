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

#include "charzerocalc.h"

charZeroCalc::charZeroCalc()
{
}

charZeroCalc::fctns charZeroCalc::findFunction(std::string *choice){
    fctns curFunc = NONE;

    if (*choice == "abs") curFunc = ABS;
    else if (*choice == "cos") curFunc = COS;
    else if (*choice == "exp") curFunc = EXP;
    else if (*choice == "ln") curFunc = LN;
    else if (*choice == "sin") curFunc = SIN;
    else if (*choice == "tan") curFunc = TAN;
    else if (*choice == "cot") curFunc = COT;
    else if (*choice =="radic") curFunc = RADIC;
    else if (*choice == "arcsin") curFunc = ARCSIN;
    else if (*choice == "arccos") curFunc = ARCCOS;
    else if (*choice == "arctan") curFunc = ARCTAN;
    else if (*choice == "arccot") curFunc = ARCCOT;
    else if (*choice == "conj") curFunc = CONJ;
    else if (*choice == "sinh") curFunc = SINH;
    else if (*choice == "cosh") curFunc = COSH;
    else if (*choice == "tanh") curFunc = TANH;
    else if (*choice == "coth") curFunc = COTH;
    else if (*choice == "arsinh") curFunc = ARSINH;
    else if (*choice == "arcosh") curFunc = ARCOSH;
    else if (*choice == "artanh") curFunc = ARTANH;
    else if (*choice == "arcoth") curFunc = ARCOTH;
    else if (*choice == "real") curFunc = REAL;
    else if (*choice == "imag") curFunc = IMAG;
    else if (*choice == "-") curFunc = MINUS;
    else if (*choice == "polar") curFunc = POLAR;

    return curFunc;
}
