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

#include "polynomial.h"

polynomial::polynomial()
{
  complex z;
  mons.append(z);
}


polynomial::polynomial(complex d)
{
  mons.append(d);
}


void polynomial::expand(complex d){
  mons.append(d);
}


int polynomial::degree(){
    if (mons.length()>1){return mons.length()-1;}
    else{
        if (mons.begin()->real==0 && mons.begin()->imag==0){return -1;}
        else {return 0;}
    }
}


QString polynomial::print(){
  int i=1;
  QString res, help;
  complex d;
  if (this ->degree() == -1){res ="0";}
  else{
  QList<complex>::Iterator iter = mons.begin();
  d = *iter;
  if (d.real != 0 || d.imag != 0){
     res = d.print();
     if (d.real != 0 && d.imag != 0){
         res.append(")");
         res.prepend("(");
     }
  }

  iter++;

  while(iter != mons.end()){
      if ((d.real >0 && d.imag == 0)  || (d.real==0 && d.imag > 0) || (d.real!=0 && d.imag != 0)){
              res.prepend("+");
          }
    d = *iter;
    if(d.imag == 0){
      if (d.real != 0){
        if (i == 1){res.prepend("x");}
        else{
          help = help.number(i);
          res.prepend(help);
          res.prepend("x^");
        }
        if (d.real == -1){res.prepend("-");}
        else if(d.real !=1){
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
      if(d.real != 0){res.prepend(")");}
      help=d.print();
      res.prepend(help);
      if(d.real != 0){res.prepend("(");}
  }
    iter++;
    i++;
  }
  }
  return res;
}

polynomial polynomial::mult(complex d){
  QList<complex>::Iterator ptr = mons.begin();
  polynomial res((*ptr)*d);

  ptr++;
  while(ptr != mons.end()){
    res.expand((*ptr)*d);
    ptr++;
  }
  return res;
}


void polynomial::shift(int i){
   complex z;

   if (i > 0){
     for (int d =1 ; d<=i;++d){
         mons.push_front(z);
     }
   }
}

complex polynomial::leader(){
  QList<complex>::Iterator ptr = mons.end();
  ptr--;

  return *ptr;
}

void polynomial::rmLeader(){
  mons.pop_back();
}


polynomial polynomial::der(){
   complex z;
  polynomial tmp(*this);
  QList<complex>::Iterator ptr = tmp.mons.begin();
  ptr++;
  polynomial res(z);

  if (ptr != tmp.mons.end()){

    polynomial help(*ptr);
    res=res+help;
    complex i(2,0);
    ptr++;
    while(ptr != tmp.mons.end()){
      res.expand((*ptr)*i);
      i.real = i.real +1;
      ptr++;
    }
  }
  return res;
}

complex polynomial::value(complex z){
    complex res, help;
    QList<complex>::Iterator iter = mons.begin();

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

 complex polynomial::newton(){
     polynomial tmp(*this);
     polynomial deriv = tmp.der();
     complex z, help, test, res, mem, zero;
     z.real= 10;
     z.imag = 10;
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
     if((100*test.real < 1) && (100*test.real > -1) && (100*test.imag < 1) && (100*test.imag > -1)){fine = true;}
     else{
         d++;
         z.real = 10+d;
         z.imag= 10-d;
     }
 }
     return z;
 }

 QString polynomial::factors(){
     bool cplx = false;
     complex eins(1,0);
     complex minusEins(-1,0);
     polynomial tmp(*this);
     tmp = tmp.normalize();
     polynomial help(eins), trx;
     QString res ="";
     if(tmp.degree()==-1){res= "0";}
     else{
     complex z, barz, test;

     //check for real or complex polynomials/////////////////
     QList<complex>::Iterator iter = mons.begin();
     while(iter != mons.end()){
         if (iter->imag != 0){
             cplx = true;
             break;
         }
         iter++;
     }

     while (tmp.degree()> 0){

         z = tmp.newton();

         if((100000*z.real < 1) && (100000*z.real > -1)){z.real =0;}
         if((100000*z.imag < 1) && (100000*z.imag > -1)){z.imag =0;}

         if(cplx || (100000*z.imag < 1) && (100000*z.imag > -1)){
             trx = help.mult(minusEins*z);
             trx.expand(eins);
         }
         else
         {
             barz.real = z.real;
             barz.imag = -z.imag;
             trx = help.mult(z*barz);
             trx.expand(minusEins*(z+barz));
             trx.expand(eins);
         }

         test = tmp.value(z);

         if((100*test.real < 1) && (100*test.real > -1) && (100*test.imag < 1) && (100*test.imag > -1)){
             res.append(trx.print());
         }
         else{res.append("no");}
         res.append(", ");
         tmp = tmp/trx;
     }
     res = res.left(res.size()-2);
     }
     return res;
 }

 polynomial polynomial::normalize(){
     polynomial tmp(*this);
     complex null;
     while((tmp.leader() == null) && (tmp.degree() > 0)){
         tmp.rmLeader();
     }
     return tmp;
 }
