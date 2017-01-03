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

#ifndef MaceRestPOLY_H
#define MaceRestPOLY_H
/*#include <QString>
#include <list>
#include <gmp.h>
#include "math/variables/scalar/macerest.h"
#include "math/kernel/genpoly.h"


class restPoly : public GenPoly
{
public:
    std::list<MaceRest> mons;

    restPoly();
    restPoly(int c);
    restPoly(MaceInt charac);
    restPoly(MaceRest d);

    MaceInt charac();
    int degree();
    restPoly der();
    void expand(MaceRest d);
    restPoly killZero();
    MaceRest leader();
    restPoly mult(MaceRest d);
    restPoly normalize();
    virtual QString print(unsigned int precision) {return print();}
    QString print();
    void rmLeader();
    void set(MaceRest mr);
    void set(int i);
    void shift(int i);

    bool putDown(MaceRest &mr);

    QString CanZas(int d, MaceInt k);
    QString EqDegFactor(MaceInt d);
    QString factors(MaceInt i);

    MaceRest value(MaceRest z);
    QString zeroes();
    std::list<MaceRest> zeroList();

    friend restPoly operator+( restPoly p1, restPoly p2 )
    {


       if(p1.degree()< p2.degree()){
           MaceRest z;
           restPoly help(z);
           help = p1;
           p1=p2;
           p2=help;
       }

       std::list<MaceRest>::iterator iter1 = p1.mons.begin();
       std::list<MaceRest>::iterator iter2 = p2.mons.begin();
       restPoly res((*iter1)+(*iter2));
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
       res = res.normalize();
       return res;
    }

    restPoly operator-( restPoly p2 ) const {
       MaceRest d(p2.charac());
       restPoly tmp(*this);
       MaceRest z = p2.leader().minusOne();

       std::list<MaceRest>::iterator iter2 = p2.mons.begin();
       d= *iter2;

       restPoly q2(z*d);
       iter2++;

       while(iter2 != p2.mons.end())
       {
           d = *iter2;
           q2.expand(z*d);
           iter2++;
       }

       restPoly res = tmp+q2;
       res = res.normalize();
       return res;
   }

   friend restPoly operator*( restPoly p1, restPoly p2 )
       {
          MaceRest z(p1.charac());
          restPoly help(z), res(z);
          MaceRest d;
          int count=0;
          std::list<MaceRest>::iterator iter2 = p2.mons.begin();

          while (iter2 != p2.mons.end()){
             help =p1;
             d= *iter2;
             help = help.mult(d);

             if(count > 0){help.shift(count);}
             res=res+help;

             count++;
             iter2++;
          }
          res = res.normalize();
          return res;
       }

       restPoly operator/( restPoly p2 ) const {
          MaceRest z(p2.charac());
          MaceRest eins=p2.leader().one();
          restPoly res(z), t(eins), help(z);
          restPoly tmp(*this);
          MaceRest quot, w,lt,lp;
          p2 = p2.normalize();
          p2.zeroTest();
          if (p2.degree() !=-1){


          while(tmp.degree()>=p2.degree()){

            lt=tmp.leader();
            lp=p2.leader();
            quot = lt/lp;

            //compute the res//////////////////////////////
            help=t;
            help = help.mult(quot);

            if(tmp.degree()>p2.degree()){help.shift(tmp.degree()-p2.degree());}
            res =res+help;

            //modify tmp///////////////////////////////////
            help =help*p2;
            tmp = tmp-help;
            tmp = tmp.normalize();
          }
          }
          res = res.normalize();
          return res;
       }

       restPoly operator%( restPoly p2 ) const {
          MaceRest z(p2.charac());
          MaceRest eins = p2.leader().one();
          restPoly res(eins), t(eins), help(z), h(z);
          restPoly tmp(*this);
          MaceRest w(p2.charac());

          h = tmp/p2;
          help = h*p2;
          help = tmp-help;

          help = help.normalize();
          return help;
       }

       bool operator==(restPoly b){
           restPoly a(*this);
           bool answer = true;
           if (a.degree() != b.degree()){answer = false;}
           else{
               std::list<MaceRest>::iterator iter1 = a.mons.begin();
               std::list<MaceRest>::iterator iter2 = b.mons.begin();

               while (answer && iter1 != a.mons.end()){
                   if (*iter1 != *iter2) answer = false;
                   iter1++;
                   iter2++;
               }
           }
           return answer;
       }

       bool operator>(restPoly p2 ) const {
           restPoly tmp(*this);
           if(tmp.degree()>p2.degree()){return true;}
           else {return false;}
       }

       bool operator>=(restPoly p2 ) const {
           restPoly tmp(*this);
           if(tmp.degree()>=p2.degree()){return true;}
           else {return false;}
       }

       bool operator!=(restPoly p2 ) const {
           restPoly tmp(*this);
           if(tmp.degree()!=p2.degree()){return true;}
           else {
               bool yes = false;
               std::list<MaceRest>::iterator iter1 = tmp.mons.begin();
               std::list<MaceRest>::iterator iter2 = p2.mons.begin();

               while (iter1 != tmp.mons.end()){
                   if(*iter1 != *iter2){
                       yes = true;
                       break;
                   }
                   iter1++;
                   iter2++;
               }
               return yes;
           }
       }

       bool operator<(restPoly p2 ) const {
           restPoly tmp(*this);
           if(tmp.degree()<p2.degree()){return true;}
           else {return false;}
       }

       bool operator<=(restPoly p2 ) const {
           restPoly tmp(*this);
           if(tmp.degree()<=p2.degree()){return true;}
           else {return false;}
       }

       restPoly operator-() const {

           restPoly tmp(*this);
           MaceRest z = tmp.leader();
           tmp.mult(z);
           return tmp;
       }
};*/

#endif // MaceRestPOLY_H
