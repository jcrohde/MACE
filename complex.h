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

#ifndef COMPLEX_H
#define COMPLEX_H
#include <QString>

class complex
{
public:
    double real;
    double imag;

    complex();
    complex(double a, double b);

    double norm();
    QString print();

    friend complex operator+( complex v1, complex v2 )
    {
       complex tmp;
       tmp.real = v1.real + v2.real;
       tmp.imag = v1.imag + v2.imag;
       return tmp;
    }

    complex operator-( complex val2 ) const {

       complex tmp(*this);
       tmp.real -= val2.real;
       tmp.imag -= val2.imag;
       return tmp;
   }

    friend complex operator*( complex v1, complex v2 )
       {
          complex tmp;
          tmp.real = (v1.real*v2.real)-(v1.imag * v2.imag);
          tmp.imag = (v1.real*v2.imag)+(v1.imag * v2.real);
          return tmp;
       }

       complex operator/( complex val2 ) const {
          complex help;
          complex tmp(*this);
          help.real = ((tmp.real*val2.real)+(tmp.imag*val2.imag))/val2.norm();
          help.imag  = ((tmp.imag*val2.real)-(tmp.real*val2.imag))/val2.norm();;
          return help;
       }

       bool operator==( complex r1){
         if(real== r1.real && imag == r1.imag){return true;}
         else {return false;}
       }

       bool operator!=( complex r1){
         if(real== r1.real && imag == r1.imag){return false;}
         else {return true;}
       }

};

#endif // COMPLEX_H
