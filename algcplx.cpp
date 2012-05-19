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

#include "algcplx.h"

algCplx::algCplx()
{
    unboundInt zero, one("1");
    real.count =zero; imag.count =zero;
    real.denom =one; imag.denom =one;
}

algCplx::algCplx(int a, int b)
{
    if (a < 0){real.positiv = false; a = -a;}
    if (b < 0){imag.positiv = false; b = -b;}
    unboundInt c(a), d(b);
    real.count =c, imag.count =d;
    real.denom =1; imag.denom =1;
}

algCplx::algCplx(unboundInt a, unboundInt b)
{
    real.count =a, imag.count =b;
    real.denom =1; imag.denom =1;
}

algCplx::algCplx(rat a, rat b)
{
    real =a, imag =b;
}

rat algCplx::norm(){
    return (real*real)+(imag*imag);
}

QString algCplx::print(){
  QString res, help;
  rat zero;
  if (real == zero && imag == zero){ return "0";}
  else{
      if (real != zero){
          res = res.append(real.print());
          if (imag != zero){
              if (imag.positiv) {res.append("+");}

              if (imag.count == zero.denom && imag.denom == zero.denom && !imag.positiv){res.append("-");}
              else if (imag.count != zero.denom || imag.denom != zero.denom){
                  res=res.append(imag.print());
              }
              res.append("i");
          }
      }
      else{
          if (imag.count == zero.denom && imag.denom == zero.denom && !imag.positiv){res.append("-");}
          else if (imag.count != zero.denom || imag.denom != zero.denom){
              res=res.append(imag.print());
          }
          res.append("i");
      }
      return res;
  }
}
