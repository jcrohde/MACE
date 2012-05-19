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

#ifndef ALGPOLY_H
#define ALGPOLY_H
#include <QString>
#include <QList>
#include <algcplx.h>

class algPoly
{
public:
    QList<algCplx> mons;

    algPoly();
    algPoly(algCplx d);

    int degree();
    void expand(algCplx d);
    algCplx leader();
    algPoly mult(algCplx d);
    algPoly normalize();
    QString print();
    void shift(int i);
    void rmLeader();

    friend bool operator<( algPoly p1, algPoly p2 ){
      if(p1.degree()<p2.degree()){return true;}
      else {return false;}
    }

    friend algPoly operator+( algPoly p1, algPoly p2 )
    {


       if(p1.degree()< p2.degree()){
           algCplx z;
           algPoly help(z);
           help = p1;
           p1=p2;
           p2=help;
       }

       QList<algCplx>::Iterator iter1 = p1.mons.begin();
       QList<algCplx>::Iterator iter2 = p2.mons.begin();
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
       algCplx z(1,0);
       z.real.positiv = false;
       algPoly tmp(*this);


       QList<algCplx>::Iterator iter2 = p2.mons.begin();
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
          QList<algCplx>::Iterator iter2 = p2.mons.begin();

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

       algPoly operator/( algPoly p2 ) const {
          algCplx z;
          algCplx eins(1,0);
          algPoly res(z), t(eins), help(z);
          algPoly tmp(*this);
          algCplx quot;
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

          h = tmp/p2;
          help = h*p2;
          help = tmp-help;

          help = help.normalize();
          return help;
       }

       bool operator>(int k ) const {
           algPoly tmp(*this);
           if((tmp.degree()+1)>k){return true;}
           else {return false;}
       }


       algPoly operator-() const {
           algCplx z(1,0);
           z.real.positiv = false;
           algPoly tmp(*this);
           tmp.mult(z);
           return tmp;
       }
};
#endif // algPoly_H
