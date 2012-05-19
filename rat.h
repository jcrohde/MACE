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

#ifndef RAT_H
#define RAT_H
#include <QString>
#include <unboundint.h>


class rat{
public:
bool positiv;
unboundInt count;
unboundInt denom;

rat();
rat(unboundInt i);
rat(unboundInt i, unboundInt j);

rat normalize();
QString print();

friend rat operator+( rat r1, rat r2 ){
    rat res;
    res.denom = r1.denom*r2.denom;
    if (r1.positiv==r2.positiv){
        res.count = (r1.count*r2.denom)+(r2.count*r1.denom);
        res.positiv = r1.positiv;
    }
    else{
        unboundInt a= r1.count*r2.denom, b=r2.count*r1.denom;
        if (a>b){
            res.count = a-b;
            res.positiv = r1.positiv;
        }
        else{
            res.count = b-a;
            res.positiv = r2.positiv;
        }
    }

    res = res.normalize();
    return res;
}


rat operator-( rat r2 ) const {
    rat res, r1(*this);

    res.denom = r1.denom*r2.denom;
    if (r1.positiv!=r2.positiv){
        res.count = (r1.count*r2.denom)+(r2.count*r1.denom);
        res.positiv = r1.positiv;
    }
    else{
        unboundInt a= r1.count*r2.denom, b=r2.count*r1.denom;
        if (a>b){
            res.count = a-b;
            res.positiv = r1.positiv;
        }
        else{
            res.count = b-a;
            if (r2.positiv){res.positiv = false;}
            else{res.positiv = true;}
        }
    }

    res = res.normalize();

    return res;
}

friend rat operator*( rat r1, rat r2 ){
 rat res;
 res.count = r1.count*r2.count;
 res.denom = r1.denom*r2.denom;
 
 if (r1.positiv == r2.positiv){res.positiv = true;}
 else{res.positiv = false;}
 res = res.normalize();
 return res;
}

rat operator/( rat r2 ) const {
       rat res, r1(*this);
       r2 = r2.normalize();
       if(r2 != res){
       res.count = r1.count*r2.denom;
       res.denom = r1.denom*r2.count;

       if (r1.positiv == r2.positiv){res.positiv = true;}
       else{res.positiv = false;}
       res = res.normalize();
       }
       return res;
}

bool operator==( rat r1){
  if(count== r1.count && denom == r1.denom){return true;}
  else {return false;}
}

bool operator!=( rat r1){
  if(count== r1.count && denom == r1.denom){return false;}
  else {return true;}
}

rat operator-(){
  rat res, tmp(*this);
  res = tmp;
  if (res.positiv){res.positiv= false;}
  else {res.positiv = true;}
  return res;
}

};

#endif // RAT_H
