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

#include "algpoly.h"

/*algPoly::algPoly(void){
  algCplx z;
  mons.push_back(z);
}


algPoly::algPoly(algCplx d)
{
  mons.push_back(d);
}


void algPoly::expand(algCplx d){
  mons.push_back(d);
}


int algPoly::degree(){
    algCplx zero;
    if (mons.size()>1){return mons.size()-1;}
    else{
        if (*mons.begin()==zero){return -1;}
        else {return 0;}
    }
}

QString algPoly::print() {

  numPoly help = this->toNumPoly();
  QString res = help.print(6);

  return res;
}

QString algPoly::print(unsigned int precision){

  numPoly help = this->toNumPoly();
  QString res = help.print(precision);

  return res;
}

void algPoly::mult(algCplx d){
  std::list<algCplx>::iterator ptr = mons.begin();
  algCplx help,h2;
  while(ptr != mons.end()){
    help = *ptr;
    multAlgC(&h2,&help,&d);
    *ptr = h2;
    ptr++;
  }
}

void algPoly::set(int i) {
    mons.clear();
    algCplx z(i,0);
    mons.push_back(z);
}

void algPoly::shift(int i){
    algCplx z;
    int j;

    for (j = 0; j < i; j++)
         mons.push_front(z);
}

algCplx algPoly::leader(){
    std::list<algCplx>::iterator ptr = mons.end();
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

 bool algPoly::putDown(algCplx &ac) {
     algPoly tmp = normalize();
     if (tmp.mons.size() == 1) {
         ac = *mons.begin();
         return true;
     }
     return false;
 }

 bool algPoly::putDown(MaceInt &mi) {
     algCplx help;
     if (this->putDown(help)) {
         return (help.putDown(mi));
     }
     return false;
 }

 numPoly algPoly::toNumPoly(){
     std::list<algCplx>::iterator ptr = mons.begin();
     algCplx help = *ptr;
     numCplx n = help.toNumCplx();
     numPoly res(n);

     ptr++;

     while(ptr != mons.end()){
         help = *ptr;
         res.mons.push_back(help.toNumCplx());
         ptr++;
     }
     return res;
 }*/


