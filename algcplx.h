/*
Copyright (C) 2012 Jan Christian Rohde

This file is part of MACE.

MACE is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MACE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with MACE. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ALGCPLX_H
#define ALGCPLX_H
#include <QString>
#include <rat.h>


class algCplx
{
public:
    rat real;
    rat imag;

    algCplx();
    algCplx(int a, int b);
    algCplx(unboundInt a, unboundInt b);
    algCplx(rat a, rat b);
    rat norm();
    QString print();

   friend algCplx operator+( algCplx v1, algCplx v2 )
    {
       algCplx tmp;
       tmp.real = v1.real + v2.real;
       tmp.imag = v1.imag + v2.imag;
       return tmp;
    }

    algCplx operator-( algCplx val2 ) const {
       algCplx tmp(*this), res;
       res.real = tmp.real-val2.real;
       res.imag = tmp.imag-val2.imag;
       return res;
   }

    friend algCplx operator*( algCplx v1, algCplx v2 )
       {
          algCplx tmp;
          tmp.real = (v1.real*v2.real)- (v1.imag * v2.imag);
          tmp.imag = (v1.real*v2.imag)+(v1.imag * v2.real);
          return tmp;
       }

       algCplx operator/( algCplx val2 ) const {
          algCplx res;
          algCplx tmp(*this);
          res.real = ((tmp.real*val2.real)+(tmp.imag*val2.imag))/val2.norm();
          res.imag  = ((tmp.imag*val2.real)-(tmp.real*val2.imag))/val2.norm();;
          return res;
       }

       bool operator==( algCplx r1){
         if(real== r1.real && imag == r1.imag){return true;}
         else {return false;}
       }

       bool operator!=( algCplx r1){
         if(real== r1.real && imag == r1.imag){return false;}
         else {return true;}
       }

};

#endif // ALGCPLX_H
