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

#include "complex.h"

complex::complex()
{
    real =0, imag =0;
}

complex::complex(double a, double b)
{
    real =a, imag =b;
}

double complex::norm(){
    return (real*real)+(imag*imag);
}

QString complex::print(){
  QString res, help;
  if (real == 0 && imag == 0){ return "0";}
  else{
      if (real != 0){
          res = res.number(real);
          if (imag != 0){
              if (imag > 0) {res.append("+");}

              if (imag == -1) {res.append("-");}
              else if (imag != 1){
                  help = help.number(imag);
                  res.append(help);
              }

              res.append("i");
          }
      }
      else{
          if (imag == -1) {res.append("-");}
          else if (imag != 1){res = res.number(imag);}
          res.append("i");
      }
      return res;
  }
}
