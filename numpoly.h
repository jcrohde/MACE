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

#ifndef NUMPOLY_H
#define NUMPOLY_H

#include <QString>
#include <QList>
#include "math/variables/scalar/numcplx.h"
#include "math/kernel/genpoly.h"
#include "math/variables/scalar/algcplx.h"


class numPoly : public GenPoly{
public:
    QList<numCplx> mons;
    numPoly();
    numPoly(numCplx d);

    bool putDown(numCplx &nc);
    bool putDown(numReal &nr);

    void expand(numCplx d);
    int degree();
    QString print() {return print(6);}
    QString print(unsigned int precision);
    numPoly mult(numCplx d);
    void shift(int i);
    numCplx leader();
    void rmLeader();
    numPoly der();
    numCplx newton();
    QString factors();
    numPoly normalize();
    numCplx value(numCplx z);
    QString zeroes();
    //QList<algCplx> zeroList();

    friend numPoly operator+( numPoly p1, numPoly p2 )
    {


       if(p1.degree()< p2.degree()){
           numCplx z;
           numPoly help(z);
           help = p1;
           p1=p2;
           p2=help;
       }

       QList<numCplx>::Iterator iter1 = p1.mons.begin();
       QList<numCplx>::Iterator iter2 = p2.mons.begin();
       numPoly res((*iter1)+(*iter2));
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

    numPoly operator-( numPoly p2 ) const {
       numCplx d;
       numCplx z(-1,0);
       numPoly tmp(*this);

       QList<numCplx>::Iterator iter2 = p2.mons.begin();
       d= *iter2;

       numPoly q2(z*d);
       iter2++;

       while(iter2 != p2.mons.end())
       {
           d = *iter2;
           q2.expand(z*d);
           iter2++;
       }

       numPoly res = tmp+q2;
       return res;
   }

   friend numPoly operator*( numPoly p1, numPoly p2 )
       {
          numCplx z;
          numPoly help(z), res(z);
          numCplx d;
          int count=0;
          QList<numCplx>::Iterator iter2 = p2.mons.begin();

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

       numPoly operator/( numPoly p2 ) const {
          numCplx z;
          numCplx eins(1,0);
          numPoly res(z), t(eins), help(z);
          numPoly tmp(*this);
          numCplx quot;

          p2 = p2.normalize();
          p2.zeroTest();
          int test;
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
            else{numCplx w; tmp.mult(w);}
            //////////////////////////////////////////////
          }

          res = res.normalize();
          }
          return res;
       }

       numPoly operator%( numPoly p2 ) const {
          numCplx z;
          numCplx eins(1,0);
          numPoly res(eins), t(eins), help(z), h(z);
          numPoly tmp(*this);
          numCplx w;

          h = tmp/p2;
          help = h*p2;
          help = tmp-help;

          help = help.normalize();
          return help;
        }

       bool operator>(numPoly p2) const {
           numPoly tmp(*this);
           return (tmp.degree() > p2.degree());
       }

       bool operator<(numPoly p2 ) const {
           numPoly tmp(*this);
           return (tmp.degree()<p2.degree());
       }

       bool operator>=(numPoly p2 ) const {
           numPoly tmp(*this);
           return (tmp.degree()>=p2.degree());
       }

       bool operator<=(numPoly p2 ) const {
           numPoly tmp(*this);
           return (tmp.degree()<=p2.degree());
       }

       bool operator==(numPoly b){
           numPoly a(*this);
           bool answer = true;
           if (a.degree() != b.degree()){answer = false;}
           else{
               QList<numCplx>::Iterator iter1 = a.mons.begin();
               QList<numCplx>::Iterator iter2 = b.mons.begin();

               while (answer && iter1 != a.mons.end()){
                   if (*iter1 != *iter2) answer = false;
                   iter1++;
                   iter2++;
               }
           }
           return answer;
       }

       bool operator!=(numPoly b){
           numPoly a(*this);
           return !(a==b);
       }

       numPoly operator-() const {
           numCplx z(-1,0);
           numPoly tmp(*this);
           tmp.mult(z);
           return tmp;
       }
};

#endif // NUMPOLY_H
