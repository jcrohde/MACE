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

#ifndef restpolynomial_H
#define restpolynomial_H
#include <QString>
#include <QList>
#include "rest.h"


class restpolynomial
{
public:
    QList<rest> mons;

    restpolynomial();
    restpolynomial(rest d);

    int charac();
    int degree();
    void expand(rest d);
    restpolynomial killZero();
    rest leader();
    restpolynomial mult(rest d);
    restpolynomial normalize();
    QString print();
    void rmLeader();
    void shift(int i);
    
    friend bool operator<( restpolynomial p1, restpolynomial p2 ){
      if(p1.degree()<p2.degree()){return true;}
      else {return false;}
    }

    friend restpolynomial operator+( restpolynomial p1, restpolynomial p2 )
    {


       if(p1.degree()< p2.degree()){
           rest z;
           restpolynomial help(z);
           help = p1;
           p1=p2;
           p2=help;
       }

       QList<rest>::Iterator iter1 = p1.mons.begin();
       QList<rest>::Iterator iter2 = p2.mons.begin();
       restpolynomial res((*iter1)+(*iter2));
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

    restpolynomial operator-( restpolynomial p2 ) const {
       rest d = p2.leader();
       d.val = 0;
       restpolynomial tmp(*this);
       rest z = tmp.leader();
       z.val = z.mod-1;

       QList<rest>::Iterator iter2 = p2.mons.begin();
       d= *iter2;

       restpolynomial q2(z*d);
       iter2++;

       while(iter2 != p2.mons.end())
       {
           d = *iter2;
           q2.expand(z*d);
           iter2++;
       }

       restpolynomial res = tmp+q2;
       return res;
   }

   friend restpolynomial operator*( restpolynomial p1, restpolynomial p2 )
       {
          rest z = p1.leader();
          z.val = 0;
          restpolynomial help(z), res(z);
          rest d;
          int count=0;
          QList<rest>::Iterator iter2 = p2.mons.begin();

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

       restpolynomial operator/( restpolynomial p2 ) const {
          rest z=p2.leader();
          rest eins=p2.leader();
          eins.val = 1;
          z.val = 0;
          restpolynomial res(z), t(eins), help(z);
          restpolynomial tmp(*this);
          rest quot, w;
          p2 = p2.normalize();
          if (p2.degree() !=-1){
          int test;

          while(tmp.degree()>=p2.degree()){
            quot=tmp.leader()/p2.leader();

            //compute the res//////////////////////////////
            help=t;
            help = help.mult(quot);

            if(tmp.degree()>p2.degree()){help.shift(tmp.degree()-p2.degree());}
            res =res+help;

            //modify tmp//////////////////////////////////
            test=tmp.degree();
            help =help*p2;
            tmp = tmp-help;
            if(tmp.degree() > 0){tmp.rmLeader();}
            else{rest w = p2.leader(); w.val = 0; tmp.mult(w);}
          }
          }
          return res;
       }

       restpolynomial operator%( restpolynomial p2 ) const {
          rest z = p2.leader();
          rest eins = p2.leader();
          eins.val = 1;
          z.val = 0;
          restpolynomial res(eins), t(eins), help(z), h(z);
          restpolynomial tmp(*this);
          rest w = p2.leader();
          w.val = 0;

          h = tmp/p2;
          help = h*p2;
          help = tmp-help;


          while (help.leader() == z && help.degree() > 0){
            help.rmLeader();
          }


          return help;
        }


       bool operator>(int k ) const {
           restpolynomial tmp(*this);
           if((tmp.degree()+1)>k){return true;}
           else {return false;}
       }

       bool operator!=(restpolynomial p2 ) const {
           restpolynomial tmp(*this);
           if(tmp.degree()!=p2.degree()){return true;}
           else {
               bool yes = false;
               QList<rest>::Iterator iter1 = tmp.mons.begin();
               QList<rest>::Iterator iter2 = p2.mons.begin();

               while (iter1 != tmp.mons.end()){
                   if(*iter1 != *iter2){
                       yes = true;
                       break;
                   }
               }
               return yes;
           }
       }

       bool operator<(restpolynomial p2 ) const {
           restpolynomial tmp(*this);
           if(tmp.degree()<p2.degree()){return true;}
           else {return false;}
       }

       restpolynomial operator-() const {

           restpolynomial tmp(*this);
           rest z = tmp.leader();
           z.val = z.mod-1;
           tmp.mult(z);
           return tmp;
       }
};

#endif // restpolynomial_H
