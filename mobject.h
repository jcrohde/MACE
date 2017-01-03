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

#ifndef MOBJECT_H
#define MOBJECT_H

#include <QString>

class MObject
{
public:
    class divByZero {
        //Exception Class: division by zero
    };

    MObject();

    virtual bool isZero() = 0;
    void zeroTest();

    virtual QString print(unsigned int precision)=0;
};

#endif // MOBJECT_H
