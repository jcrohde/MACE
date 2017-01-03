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

#include "numpoly.h"


numPoly::numPoly()
{
  numCplx z;
  mons.append(z);
}

numPoly::numPoly(numCplx d){
    mons.append(d);
}

void numPoly::expand(numCplx d){
  mons.append(d);
}


int numPoly::degree(){
    if (mons.length()>1){return mons.length()-1;}
    else{
        if (mons.begin()->val.real()==0 && mons.begin()->val.imag()==0){return -1;}
        else {return 0;}
    }
}


QString numPoly::print(unsigned int precision){
  int i=1;
  QString res, help;
  numCplx d;

  *this = this->normalize();

  if (this ->degree() == -1){res ="0";}
  else{
  QList<numCplx>::Iterator iter = mons.begin();
  d = *iter;
  if (d.val.real() != 0 || d.val.imag() != 0){
     res = d.print(precision);
     if (d.val.real() != 0 && d.val.imag() != 0){
         res.append(")");
         res.prepend("(");
     }
  }

  iter++;

  while(iter != mons.end()){
      if ((d.val.real() >0 && d.val.imag() == 0)  || (d.val.real()==0 && d.val.imag() > 0) || (d.val.real()!=0 && d.val.imag() != 0)){
              res.prepend("+");
          }
    d = *iter;
    if(d.val.imag() == 0){
        if (d.val.real() != 0){
        if (i == 1){res.prepend("x");}
        else{
          help = help.number(i);
          res.prepend(help);
          res.prepend("x^");
        }
        if (d.val.real() == -1){res.prepend("-");}
        else if(d.val.real() !=1){
          help=d.print(precision);
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
      if(d.val.real() != 0){res.prepend(")");}
      help=d.print(precision);
      res.prepend(help);
      if(d.val.real() != 0){res.prepend("(");}
  }
    iter++;
    i++;
  }
  }
  return res;
}

numPoly numPoly::mult(numCplx d){
  QList<numCplx>::Iterator ptr = mons.begin();
  numPoly res((*ptr)*d);

  ptr++;
  while(ptr != mons.end()){
    res.expand((*ptr)*d);
    ptr++;
  }
  return res;
}


void numPoly::shift(int i){
   numCplx z;

   if (i > 0){
     for (int d =1 ; d<=i;++d){
         mons.push_front(z);
     }
   }
}

numCplx numPoly::leader(){
  QList<numCplx>::Iterator ptr = mons.end();
  ptr--;

  return *ptr;
}

void numPoly::rmLeader(){
  mons.pop_back();
}

bool numPoly::putDown(numCplx &nc) {
    numPoly tmp = normalize();
    if (tmp.mons.size() == 1) {
        nc = *mons.begin();
        return true;
    }
    return false;
}

bool numPoly::putDown(numReal &nr) {
    numCplx help;
    if (this->putDown(help)) {
        return (help.putDown(nr));
    }
    return false;
}

numPoly numPoly::der(){
   numCplx z;
  numPoly tmp(*this);
  QList<numCplx>::Iterator ptr = tmp.mons.begin();
  ptr++;
  numPoly res(z);

  if (ptr != tmp.mons.end()){

    numPoly help(*ptr);
    res=res+help;
    numCplx i(2,0);
    ptr++;
    while(ptr != tmp.mons.end()){
      res.expand((*ptr)*i);
      //i.val.real() = i.val.real() +1;
      ptr++;
    }
  }
  return res;
}

numCplx numPoly::value(numCplx z){
    numCplx res, help;
    QList<numCplx>::Iterator iter = mons.begin();

    int i= 0;

    while(iter != mons.end()){
        help = *iter;
        if (i == 0){res = help;}
        else{
            for (int m = 0; m<i; m++){help = help*z;}
            res = res+help;
        }
        i++;
        iter++;
    }

    return res;
}

 numCplx numPoly::newton(){
     numPoly tmp(*this);
     numPoly deriv = tmp.der();
     numCplx z(10,10), help, test, res, mem, zero(0,0);
     int i;
     int d=0;
     bool fine = false;


     while(!fine && d < 5){

     for(int k = 0; k < 50; k++){
       mem = tmp.value(z);
       res = deriv.value(z);

       z = z-(mem/res);
     }

     test = tmp.value(z);
     if((100*test.val.real() < 1) && (100*test.val.real() > -1) && (100*test.val.imag() < 1) && (100*test.val.imag() > -1)){fine = true;}
     else{
         d++;
         //z.val.real() = 10+d;
         //z.val.imag() = 10-d;
     }
 }
     return z;
 }

 QString numPoly::factors(){
     bool cplx = false;
     numCplx eins(1,0);
     numCplx minusEins(-1,0);
     numPoly tmp(*this);
     tmp = tmp.normalize();
     numPoly help(eins), trx;
     QString res ="";
     if(tmp.degree()==-1){res= "0";}
     else{
     numCplx z, barz, test;

     //check for real or numCplx numPolys/////////////////
     QList<numCplx>::Iterator iter = mons.begin();
     while(iter != mons.end()){
         if (iter->val.imag() != 0){
             cplx = true;
             break;
         }
         iter++;
     }

     while (tmp.degree()> 0){

         z = tmp.newton();

         //if((100000*z.val.real() < 1) && (100000*z.val.real() > -1)){z.val.real() =0;}
         //if((100000*z.val.imag() < 1) && (100000*z.val.imag() > -1)){z.val.imag() =0;}

         if(cplx || (100000*z.val.imag() < 1) && (100000*z.val.imag() > -1)){
             trx = help.mult(minusEins*z);
             trx.expand(eins);
         }
         else
         {
             barz.val = conj(z.val);
             trx = help.mult(z*barz);
             trx.expand(minusEins*(z+barz));
             trx.expand(eins);
         }

         test = tmp.value(z);

         if((100*test.real() < 1) && (100*test.real() > -1) && (100*test.imag() < 1) && (100*test.imag() > -1)){
             res.append(trx.print(6));
         }
         else{res.append("no");}
         res.append(", ");
         tmp = tmp/trx;
     }
     res = res.left(res.size()-2);
     }
     return res;
 }

 numPoly numPoly::normalize(){
     numPoly tmp(*this);
     numCplx null;
     while((tmp.leader() == null) && (tmp.degree() > 0)){
         tmp.rmLeader();
     }
     return tmp;
 }

 QString numPoly::zeroes() {
     QString res;
     /*QList<algCplx> list = zeroList();
     int size = list.size();
     for (int i = 0; i < size; i++) {
         res = res.append(list[i].print(6));
         if (i < size-1) res = res.append(", ");
     }*/
     return res;
 }

 /*QList<algCplx> numPoly::zeroList() {
     bool cplx = false;
     numCplx eins(1,0);
     numCplx minusEins(-1,0);
     numPoly tmp(*this);
     tmp = tmp.normalize();
     numPoly help(eins), trx;
     QList<algCplx> res;
     if(tmp.degree()==-1) {res.push_back(algCplx(0,0));}
     else{

     numCplx z, test;

     //check for real or numCplx numPolys/////////////////
     QList<numCplx>::Iterator iter = mons.begin();
     while(iter != mons.end()){
         if (iter->val.imag() != 0){
             cplx = true;
             break;
         }
         iter++;
     }

     while (tmp.degree()> 0){

         z = tmp.newton();

         if((100000*z.val.real() < 1) && (100000*z.val.real() > -1)){z.val.real() =0;}
         if((100000*z.val.imag() < 1) && (100000*z.val.imag() > -1)){z.val.imag() =0;}

         trx = help.mult(minusEins*z);
         trx.expand(eins);

         test = tmp.value(z);

         if((100*test.real() < 1) && (100*test.real() > -1) && (100*test.imag() < 1) && (100*test.imag() > -1)){
             algCplx w(0,0);
             w.fromNumCplx(z);
             res.append(w);
         }
         tmp = tmp/trx;
         test = tmp.value(z);
         while ((100*test.real() < 1) && (100*test.real() > -1) && (100*test.imag() < 1) && (100*test.imag() > -1)){
             tmp = tmp/trx;
             test = tmp.value(z);
         }
     }
     }
     return res;
 }*/
