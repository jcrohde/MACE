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

#ifndef REST_H
#define REST_H

#include <QPair>

template <class S>
S mmax(S a, S b){
  if(a<b){return b;}
  else{return a;}
}

template <class S>
S mmin(S a, S b){
  if(a<b){return a;}
  else{return b;}
}

template <class S>
S mabs(S a){
  if (a >0){return a;}
  else{return -a;}
}

template <class S>
QPair<S,S> mextendedgcd(S a, S b){
    QPair<S,S> res, info;
    if (!(b > 0)){res.first=1;res.second=0;}
    else{
        S q, r;
        r=a%b;
        q=(a-r)/b;
        info= mextendedgcd(b, r);
        res.first=info.second;
        res.second=info.first-(q*info.second);
    }
    return res;
}

template <class S>
QPair<S,S> mexEu(S a, S b){
    QPair<S,S> res;
    S hilf, m, n;

    m=mabs(a);
    n=mabs(b);
    hilf =mmax(n,m);
    n = mmin(n,m);
    m = hilf;

    res=mextendedgcd(a, b);
    return res;
}


class rest
{
public:
    long int val;
    long int mod;

    rest();
    rest(int i); //0 mod i
    rest(int i, int j); //i mod j

    void normalize();
    QString print();

    friend rest operator+( rest r1, rest r2 ){
     int r = r1.val+r2.val;
     rest res(0);
     res.mod = r1.mod;
     res.val = r % r1.mod;
     return res;
    }

    rest operator-( rest r2 ) const {
     rest r1(*this);
     int r = r1.val-r2.val;
     rest res(r1.mod);
     res.val = r % res.mod;
     if (res.val < 0){res.val += res.mod;}
     return res;
    }

    friend rest operator*( rest r1, rest r2 ){
     int r = r1.val*r2.val;
     rest res(0);
     res.mod = r1.mod;
     res.val = r % r1.mod;
     return res;
    }

    rest operator/( rest val2 ) const {
       QPair<long int,long int> help = mexEu(val2.val, val2.mod);
       rest tmp(*this);
       rest res(tmp.mod);
       res.val = (tmp.val*help.first)%tmp.mod;
       if (res.val < 0){res.val += res.mod;}
       return res;
    }

    bool operator==( rest r1){
      if((val == r1.val) && (mod == r1.mod)){return true;}
      else {return false;}
    }

    bool operator!=( rest r1){
      if((val == r1.val) && (mod == r1.mod)){return false;}
      else {return true;}
    }
};

#endif // REST_H
