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

#ifndef NUMCPLX_H
#define NUMCPLX_H

#include <QString>
#include <math.h>
#include <complex>
#include "math/kernel/datum.h"
#include "math/variables/scalar/numreal.h"
#define PI 3.141592

class numCplx : public datum
{
private:
    virtual void invCall();
public:
    std::complex<double> val;

    double real(){return val.real();}
    double imag(){return val.imag();}
    void multReal(double r){std::complex<double> help(r,0.0); val *= help;}
    void set(double real, double imag){numCplx help(real,imag); *this = help;}

    numCplx();
    numCplx(double a, double b);

    virtual bool isZero();

    bool putDown(numReal &r);

    double arg(); // range from -pi to pi
    double norm(); //square of the norm
    QString print() {return print(6);}
    QString print(unsigned int precision);

    friend numCplx operator+( numCplx v1, numCplx v2 )
    {
        numCplx res;
        res.val = v1.val + v2.val;
        return res;
    }

    numCplx operator-( numCplx val2 ) const {

       numCplx tmp(*this);
       tmp.val -= val2.val;
       return tmp;
   }

    friend numCplx operator*( numCplx v1, numCplx v2 )
       {
          numCplx tmp;
          tmp.val = v1.val*v2.val;
          return tmp;
       }

       numCplx operator/( numCplx val2 ) const {
          numCplx help;
          numCplx tmp(*this);
          val2.zeroTest();
          help.val = tmp.val/val2.val;
          return help;
       }

       bool operator==( numCplx r1){
         return (val== r1.val);
       }

       bool operator!=( numCplx r1){
         return (val!= r1.val);
       }

       bool operator<( numCplx r1){
           double help, help1;
           if (val.imag() == 0 && r1.val.imag() == 0) {
               return (val.real() < r1.val.real());
           }
           help = val.real()*val.real() + val.imag()*val.imag();
           help1 = r1.val.real()*r1.val.real() + r1.val.imag()*r1.val.imag();
           return (help < help1);
       }

       bool operator>( numCplx r1){
           double help, help1;
           if (val.imag() == 0 && r1.val.imag() == 0) {
               return (val.real() > r1.val.real());
           }
           help = val.real()*val.real() + val.imag()*val.imag();
           help1 = r1.val.real()*r1.val.real() + r1.val.imag()*r1.val.imag();
           return (help > help1);
       }

       bool operator<=( numCplx r1){
           double help, help1;
           if (val.imag() == 0 && r1.val.imag() == 0) {
               return (val.real() <= r1.val.real());
           }
           help = val.real()*val.real() + val.imag()*val.imag();
           help1 = r1.val.real()*r1.val.real() + r1.val.imag()*r1.val.imag();
           return (help <= help1);
       }

       bool operator>=( numCplx r1){
           double help, help1;
           if (val.imag() == 0 && r1.val.imag() == 0) {
               return (val.real() >= r1.val.real());
           }
           help = val.real()*val.real() + val.imag()*val.imag();
           help1 = r1.val.real()*r1.val.real() + r1.val.imag()*r1.val.imag();
           return (help >= help1);
       }

};

#endif // NUMCPLX_H
