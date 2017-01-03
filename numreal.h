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

#ifndef NUMREAL_H
#define NUMREAL_H

#include <QString>
#include "math/kernel/datum.h"

class numReal : public datum
{
private:
    double val;

public:
    numReal();
    numReal(double d) {val = d;}

    void   set(double d) {val = d;}
    double get()         const {return val;}

    virtual QString print  (unsigned int precision);
    bool    isZero () {return (val==0);}
    virtual void    invCall() {val = 1.0/val;}

    friend numReal operator+( numReal v1, numReal v2 )
    {
        numReal tmp;
        tmp.val = v1.val + v2.val;
        return tmp;
    }

    numReal operator-( numReal val2 ) const {
        numReal tmp(*this), res;
        res.val = tmp.val - val2.val;
        return res;
    }

     friend numReal operator*( numReal v1, numReal v2 )
     {
         numReal tmp;
         tmp.val = v1.val * v2.val;
         return tmp;
     }

     numReal operator/( numReal val2 ) const {
         numReal tmp(*this), res;
         res.val = tmp.val / val2.val;
         return res;
     }

     bool operator<( numReal r1){
         return (val < r1.val);
     }

     bool operator>( numReal r1){
         return (val > r1.val);
     }

     bool operator<=( numReal r1){
         return (val <= r1.val);
     }

     bool operator>=( numReal r1){
         return (val >= r1.val);
     }

     bool operator==( numReal r1){
         return (val == r1.val);
     }

     bool operator!=( numReal r1){
         return (val != r1.val);
     }
};

extern QString dblPrint(double d, int precision);

#endif // NUMREAL_H
