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

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <QString>
#include <QList>
#include "complex.h"


class polynomial
{
public:
    QList<complex> mons;
    polynomial();
    polynomial(complex d);
    void expand(complex d);
    int degree();
    QString print();
    polynomial mult(complex d);
    void shift(int i);
    complex leader();
    void rmLeader();
    polynomial der();
    complex newton();
    QString factors();
    polynomial normalize();
    complex value(complex z);

    friend bool operator<( polynomial p1, polynomial p2 ){
      if(p1.degree()<p2.degree()){return true;}
      else {return false;}
    }
    
    friend polynomial operator+( polynomial p1, polynomial p2 )
    {


       if(p1.degree()< p2.degree()){
           complex z;
           polynomial help(z);
           help = p1;
           p1=p2;
           p2=help;
       }

       QList<complex>::Iterator iter1 = p1.mons.begin();
       QList<complex>::Iterator iter2 = p2.mons.begin();
       polynomial res((*iter1)+(*iter2));
       iter1++;
       iter2++;

       while(iter2 != p2.mons.end()){
         res.expand((*iter1)+(*iter2));
         iter1++;
         iter2++;
       }

       while(iter1 != p1.mons.end()){
         res.expand(*iter1);
         iter1++;
       }
       return res;
    }

    polynomial operator-( polynomial p2 ) const {
       complex d;
       complex z(-1,0);
       polynomial tmp(*this);

       QList<complex>::Iterator iter2 = p2.mons.begin();
       d= *iter2;

       polynomial q2(z*d);
       iter2++;

       while(iter2 != p2.mons.end())
       {
           d = *iter2;
           q2.expand(z*d);
           iter2++;
       }

       polynomial res = tmp+q2;
       return res;
   }

   friend polynomial operator*( polynomial p1, polynomial p2 )
       {
          complex z;
          polynomial help(z), res(z);
          complex d;
          int count=0;
          QList<complex>::Iterator iter2 = p2.mons.begin();

          while (iter2 != p2.mons.end()){
             help =p1;
             d= *iter2;
             help = help.mult(d);

             if(count > 0){help.shift(count);}
             res=res+help;

             count++;
             iter2++;
          }
          return res;
       }
     
       polynomial operator/( polynomial p2 ) const {
          complex z;
          complex eins(1,0);
          polynomial res(z), t(eins), help(z);
          polynomial tmp(*this);
          complex quot;

          int test, i;
          p2 = p2.normalize();
          if (p2.degree() !=-1){
          while(tmp.degree()>=p2.degree()){
            quot=tmp.leader()/p2.leader();
            

            //compute the res//////////////////////////////
            help=t;
            help = help.mult(quot);

            if(tmp.degree()>p2.degree()){help.shift(tmp.degree()-p2.degree());}
            res =res+help;
            //////////////////////////////////////////////

            //modify tmp//////////////////////////////////
            test=tmp.degree();
            help =help*p2;
            tmp = tmp-help;
            if(tmp.degree() > 0){tmp.rmLeader();}
            else{complex w; tmp.mult(w);}
            //////////////////////////////////////////////
          }

          res = res.normalize();
          }
          return res;
       }

       polynomial operator%( polynomial p2 ) const {
          complex z;
          complex eins(1,0);
          polynomial res(eins), t(eins), help(z), h(z);
          polynomial tmp(*this);
          complex w;
          int i = 0;

          h = tmp/p2;
          help = h*p2;
          help = tmp-help;

          help = help.normalize();
          return help;
        }

       bool operator>(int k ) const {
           polynomial tmp(*this);
           if((tmp.degree()+1)>k){return true;}
           else {return false;}
       }
       
       bool operator<(polynomial p2 ) const {
           polynomial tmp(*this);
           if(tmp.degree()<p2.degree()){return true;}
           else {return false;}
       }

       polynomial operator-() const {
           complex z(-1,0);
           polynomial tmp(*this);
           tmp.mult(z);
           return tmp;
       }
};


#endif // POLYNOMIAL_H
