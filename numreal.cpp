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

#include "numreal.h"
#include <stdio.h>

QString dPrint(double d, int precision) {
    QString str;
    str = str.setNum(d,'g',precision);
    return str;
}


numReal::numReal()
{

}

QString numReal::print(unsigned int precision)
{
     return dPrint(val,precision);
}

QString dblPrint(double d, int precision) {
    return dPrint(d,precision);
}
