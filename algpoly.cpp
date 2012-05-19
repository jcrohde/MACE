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

#include "algpoly.h"


algPoly::algPoly(void){
  algCplx z;
  mons.append(z);
}


algPoly::algPoly(algCplx d)
{
  mons.append(d);
}


void algPoly::expand(algCplx d){
  mons.append(d);
}


int algPoly::degree(){
    algCplx zero;
    if (mons.length()>1){return mons.length()-1;}
    else{
        if (*mons.begin()==zero){return -1;}
        else {return 0;}
    }
}


QString algPoly::print(){
  int i=1;
  QString res, help;
  algCplx d, zero;
  rat ratZero, minusOne, one;
  minusOne.count = minusOne.count.translate(1);
  minusOne.positiv = false;
  one.count = one.count.translate(1);
  if (this ->degree() == -1){res = "0";}
  else{
  QList<algCplx>::Iterator iter = mons.begin();
  d = *iter;
  if (d!=zero){
     res = d.print();
     if (d.real != ratZero && d.imag != ratZero){
         res.append(")");
         res.prepend("(");
     }
  }

  iter++;

  while(iter != mons.end()){
      if ((d.real !=zero.real && d.imag == zero.imag && d.real.positiv)  ||
          (d.real==zero.real && d.imag != zero.imag && d.imag.positiv) ||
          (d.real!=zero.real && d.imag != zero.real)){
              res.prepend("+");
          }
    d = *iter;
    if(d.imag == zero.imag){
      if (d.real != zero.real){
        if (i == 1){res.prepend("x");}
        else{
          help = help.number(i);
          res.prepend(help);
          res.prepend("x^");
        }
        if ((d.real.count == zero.real.denom) && (d.real.denom == zero.real.denom) && !d.real.positiv){res.prepend("-");}
        else if(d.real !=one){
          help=d.print();
          res.prepend(help);
        }
      }
  }
  else{
      if (i == 1){res.prepend("x");}
      else{
        help = help.number(i);
        res.prepend(help);
        res.prepend("x^");
      }
      res.prepend(")");
      help=d.print();
      res.prepend(help);
      res.prepend("(");
  }
    iter++;
    i++;
  }
  }
  return res;
}

algPoly algPoly::mult(algCplx d){
  QList<algCplx>::Iterator ptr = mons.begin();
  algPoly res((*ptr)*d);

  ptr++;
  while(ptr != mons.end()){
    res.expand((*ptr)*d);
    ptr++;
  }
  return res;
}


void algPoly::shift(int i){
    algCplx z;

    if (i > 0){
      for (int d =1 ; d<=i;++d){
          mons.push_front(z);
      }
    }
}

algCplx algPoly::leader(){
    QList<algCplx>::Iterator ptr = mons.end();
    ptr--;

    return *ptr;
}

void algPoly::rmLeader(){
  mons.pop_back();
}

 algPoly algPoly::normalize(){
     algPoly tmp(*this);
     algCplx null;
     while((tmp.leader() == null) && (tmp.degree() > 0)){
         tmp.rmLeader();
     }
     return tmp;
 }

