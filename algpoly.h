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

#ifndef ALGPOLY_H
#define ALGPOLY_H

/*#include <QString>
#include <list>
#include "math/variables/polynomial/numpoly.h"
#include "math/variables/scalar/algcplx.h"
#include "math/kernel/genpoly.h"

class algPoly : public GenPoly
{
public:
    std::list<algCplx> mons;

    algPoly();
    algPoly(algCplx d);

    int degree();
    void expand(algCplx d);
    algCplx leader();
    void mult(algCplx d);
    algPoly normalize();
    QString print();
    QString print(unsigned int precision);
    void set(int i);
    void shift(int i);
    void rmLeader();

    bool putDown(algCplx &ac);
    bool putDown(MaceInt &mi);

    numPoly toNumPoly();

    friend algPoly operator+( algPoly p1, algPoly p2 )
    {


       if(p1.degree()< p2.degree()){
           algCplx z;
           algPoly help(z);
           help = p1;
           p1=p2;
           p2=help;
       }

       std::list<algCplx>::iterator iter1 = p1.mons.begin();
       std::list<algCplx>::iterator iter2 = p2.mons.begin();
       algPoly res((*iter1)+(*iter2));
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

    algPoly operator-( algPoly p2 ) const {
       algCplx d;
       algCplx z(-1,0);
       algPoly tmp(*this);


       std::list<algCplx>::iterator iter2 = p2.mons.begin();
       d= *iter2;
       d = d*z;
       algPoly q2(d);
       iter2++;

       while(iter2 != p2.mons.end())
       {
           d = *iter2;
           d = d*z;
           q2.expand(d);
           iter2++;
       }

       algPoly res = tmp+q2;

       return res;
   }

   friend algPoly operator*( algPoly p1, algPoly p2 )
       {
          algCplx z;
          algPoly help(z), res(z);
          algCplx d;
          int count=0;
          std::list<algCplx>::iterator iter2 = p2.mons.begin();

          while (iter2 != p2.mons.end()){
             help =p1;
             d= *iter2;
             help.mult(d);

             if(count > 0){help.shift(count);}
             res=res+help;

             count++;
             iter2++;
          }

          return res;
       }

       algPoly operator/( algPoly p2 ) const {
          algCplx z;
          algCplx eins(1,0);
          algPoly res(z), t(eins), help(z);
          algPoly tmp(*this);
          algCplx quot;
          p2 = p2.normalize();
          p2.zeroTest();
          if (p2.degree() !=-1){
          int test;

          while(tmp.degree()>=p2.degree()){
            quot=tmp.leader()/p2.leader();

            //compute the res//////////////////////////////
            help=t;
            help.mult(quot);

            if(tmp.degree()>p2.degree()){help.shift(tmp.degree()-p2.degree());}
            res =res+help;

            //modify tmp//////////////////////////////////
            test=tmp.degree();
            help =help*p2;
            tmp = tmp-help;
            if(tmp.degree() > 0){tmp.rmLeader();}
            else{algCplx w; tmp.mult(w);}
          }
          }
          return res;
       }

       algPoly operator%( algPoly p2 ) const {
          algCplx z;
          algCplx eins(1,0);
          algPoly res(eins), t(eins), help(z), h(z);
          algPoly tmp(*this);
          algCplx w;

          help = tmp/p2;
          help = help*p2;
          help = tmp-help;

          help = help.normalize();
          return help;
       }


       friend bool operator<( algPoly p1, algPoly p2 ){
           if(p1.degree()<p2.degree()){return true;}
           else {return false;}
       }

       bool operator>(algPoly p2 ) const {
           algPoly tmp(*this);
           if(tmp.degree()>p2.degree()){return true;}
           else {return false;}
       }

       bool operator==(algPoly b){
           algPoly a(*this);
           bool answer = true;
           if (a.degree() != b.degree()){answer = false;}
           else{
               std::list<algCplx>::iterator iter1 = a.mons.begin();
               std::list<algCplx>::iterator iter2 = b.mons.begin();

               while (answer && iter1 != a.mons.end()){
                   if (*iter1 != *iter2) answer = false;
                   iter1++;
                   iter2++;
               }
           }
           return answer;
       }

       bool operator!=(algPoly b){
           algPoly a(*this);
           return !(a == b);
       }

       bool operator<=(algPoly b){
           algPoly a(*this);
           return (a.degree()<=b.degree());
       }

       bool operator>=(algPoly b){
           algPoly a(*this);
           return (a.degree()>=b.degree());
       }

       algPoly operator-() const {
           algCplx z(-1,0);
           algPoly tmp(*this);
           tmp.mult(z);
           return tmp;
       }
};*/

#endif // ALGPOLY_H
