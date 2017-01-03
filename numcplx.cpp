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

#include "numcplx.h"

numCplx::numCplx()
{

}

numCplx::numCplx(double a, double b)
{
    std::complex<double> help(a,b);
    val = help;
}

double numCplx::arg(){
    double res;
    if(val.real() > 0){res = atan(val.imag()/val.real());}
    else if(val.real()==0){
        if (val.imag()<0){res = -PI/2;}
        else {res = PI/2;}
    }
    else{
        if (val.imag() < 0){res = atan(val.imag()/val.real())-PI;}
        else {res = atan(val.imag()/val.real())+PI;}
    }
    return res;
}

double numCplx::norm(){
    double res;
    res = std::norm(val);
    return res;
}

QString numCplx::print(unsigned int precision){
  QString res, help;
  if (val.real() == 0 && val.imag() == 0){ return "0";}
  else{
      if (val.real() != 0){

          res = dblPrint(val.real(),precision);
          if (val.imag() != 0){
              if (val.imag() > 0) {res.append("+");}

              if (val.imag() == -1) {res.append("-");}
              else if (val.imag() != 1){
                  help = dblPrint(val.imag(),precision);
                  res.append(help);
              }

              res.append("i");
          }
      }
      else{
          if (val.imag() == -1) {res.append("-");}
          else if (val.imag() != 1){res = dblPrint(val.imag(),precision);}
          res.append("i");
      }
      return res;
  }
}

bool numCplx::isZero(){
    return (real()==0.0 && imag() == 0.0);
}

void numCplx::invCall(){
    numCplx one(1,0);
    *this = one / *this;
}

bool numCplx::putDown(numReal &r) {
    if (imag() == 0.0) {
        r.set(real());
        return true;
    }
    return false;
}
