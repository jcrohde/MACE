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

#include "restpolynomial.h"

restpolynomial::restpolynomial()
{
  rest z;
  mons.append(z);
}


restpolynomial::restpolynomial(rest d)
{
  mons.append(d);
}


void restpolynomial::expand(rest d){
  mons.append(d);
}


int restpolynomial::degree(){
    if (mons.length()>1){return mons.length()-1;}
    else{
        restpolynomial tmp(*this);
        int charac = tmp.charac();
        rest zero(charac);
        if (*mons.begin()==zero){return -1;}
        else {return 0;}
    }
}


QString restpolynomial::print(){
  int i=1;
  QString res, help;
  rest d;
  restpolynomial tmp(*this);
  tmp = tmp.normalize();
  if (tmp.degree() == -1){ res = "0";}
  else{
  QList<rest>::Iterator iter = mons.begin();
  d = *iter;
  d.val = d.val % d.mod;
  if (d.val < 0){d.val = d.val+d.mod;}
  if (d.val != 0){
     res = d.print();
  }

  iter++;

  while(iter != mons.end()){
   if (d.val != 0){
        res.prepend("+");
    }
    d = *iter;
    d.val = d.val % d.mod;
    if (d.val < 0){d.val = d.val+d.mod;}
    if (d.val != 0){
        if (i == 1){res.prepend("x");}
        else{
          help = help.number(i);
          res.prepend(help);
          res.prepend("x^");
        }
        if(d.val !=1){
          help=help.number(d.val);
          res.prepend(help);
        }
      }


    iter++;
    i++;
  }
  }
  return res;
}

restpolynomial restpolynomial::mult(rest d){
  QList<rest>::Iterator ptr = mons.begin();
  restpolynomial res((*ptr)*d);

  ptr++;
  while(ptr != mons.end()){
    res.expand((*ptr)*d);
    ptr++;
  }
  return res;
}


void restpolynomial::shift(int i){
    rest z(leader().mod);

   if (i > 0){
     for (int d =1 ; d<=i;++d){
         mons.push_front(z);
     }
   }
}


rest restpolynomial::leader(){
    QList<rest>::Iterator ptr = mons.end();
    ptr--;

    return *ptr;
}

int restpolynomial::charac(){
    QList<rest>::Iterator ptr = mons.end();
    ptr--;
    rest r = *ptr;
    return r.mod;
}


void restpolynomial::rmLeader(){
  mons.pop_back();
}


restpolynomial restpolynomial::killZero(){
    restpolynomial tmp(*this);
    int i = 1;
    int m = tmp.charac();
    QList<rest>::Iterator iter = tmp.mons.begin();
    restpolynomial res(*iter);
    iter++;
    if (iter != tmp.mons.end()){

        while(iter !=tmp.mons.end()){
            i = i%m;
            if (i == 0){res.expand(*iter);}
            iter++;
            i++;
        }
    }
    return res;
}

restpolynomial rgcd(restpolynomial a, restpolynomial b){
    restpolynomial help;
    if (a.degree()<b.degree()){
        help = a;
        a=b;
        b= help;
    }
    while(b.degree() > -1){
        help = a%b;
        a=b;
        b = help;
    }
    return a;
}


restpolynomial restpolynomial::normalize(){
    restpolynomial tmp(*this);
    rest null = tmp.leader();
    null.val = 0;
    int v;
    int mod = null.mod;
    v = tmp.leader().val;
    while((v%mod == 0) && (tmp.degree() > 0)){
        tmp.rmLeader();
        v = tmp.leader().val;
    }
    return tmp;
}

