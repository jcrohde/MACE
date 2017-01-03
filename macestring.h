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

#ifndef MACESTRING_H
#define MACESTRING_H

#include "math/kernel/mobject.h"

class MaceString : public MObject
{
public:
    QString str;

    MaceString();
    bool isZero() {return str.size() == 0;}

    virtual QString print(unsigned int precision) {return str;}

    friend MaceString operator+( MaceString a, MaceString b)
    {
        MaceString res;
        res.str = a.str + b.str;
        return res;
    }

    MaceString operator-(MaceString b ) const
    {
        MaceString res, a(*this);

        res.str = a.str.remove(b.str);

        return res;
    }

    bool operator>=(MaceString b){
        MaceString a(*this);
        return a.str.size() >= b.str.size();
    }

    bool operator<=(MaceString b){
        MaceString a(*this);
        return a.str.size() <= b.str.size();
    }


    bool operator>(MaceString b){
        MaceString a(*this);
        return a.str.size() > b.str.size();
    }

    bool operator<(MaceString b){
        MaceString a(*this);
        return a.str.size() < b.str.size();
    }

    bool operator==(MaceString b){
        MaceString a(*this);
        return a.str.size() == b.str.size();;
    }

    bool operator!=(MaceString b){
        MaceString a(*this);
        return a.str.size() != b.str.size();;
    }
};

#endif // MACESTRING_H
