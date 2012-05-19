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

#ifndef NTH_H
#define NTH_H
#include "math.h"
#include "unboundint.h"

unboundInt fac(int i){
    unboundInt res(1), help;
    for(int j =1; j<= i; j++){
        help = help.translate(j);
        res=help*res;
    }
    return res;
}

unboundInt bino(int n, int k){
    unboundInt res("1"), kar;
    if (n>0 && k > 0 && n> k){
        if (k> n/2 ){k = n-k;}
    for(int i =n-k+1; i<= n; i++){
        res=res.mult(i);
        res=res.divi(i+k-n);
    }
    }

    return res;
}

int pi(int i){
    QList<int> primes;
    if (i<2){return 0;}
    else{

        for (int j =2; j<= i;j++){
            primes.push_back(j);
        }

        int k;

        QList<int>::iterator kill;


        QList<int>::iterator pes = primes.begin();

        while(!(pes == primes.end())){

        kill = pes;

        k =2;
        while ((*pes) * k <= i){

            while (*kill <= (*pes) * k && kill != primes.end()){
                kill++;
                if (kill == primes.end()){break;}
                if (*kill==(*pes) * k){
                    primes.erase(kill);
                }   
            }

            k++;
        }

        pes++;
        }

        int res = 0;
        for(QList<int>::iterator iter = primes.begin(); iter != primes.end(); iter++){
            res++;
        }

        return res;
    }

}

template <class T>
T power(T a, int n){
    T res = a;
    for (int i = 1; i < n; i++){
        res = res*a;
    }
    return res;
}

template <class T>
T abs(T a){
  if (a >0){return a;}
  else{return -a;}
}

int prime (int i){
    i = abs(i);
    int res = i;

    for (int j = 2; j <= sqrt(i); j++){
        if (i%j == 0){
            res = j;
            break;
        }
    }

    return res;
}


unboundInt fibo(int i){

    unboundInt res, a(1), b;
    if (i<=0) {return b;}
    else if (i==1){return a;}
    else{
        for (int k= 2; k<= i;k++){
            res = a+b;
            b= a;
            a= res;
        }
        return res;
    }
}

QList<int> primeFac(int i){
    QList<int> res;
    i = abs(i);
    if (i < 2){
        res.push_back(i);
    }
    else{
        int help;

        while (i > 1){
            help = prime(i);
            res.push_back(help);
            i = i/help;
        }
    }
    return res;
}

int facnum(int i){
    if (i < 2){return 1;}
    int fac = 1;
    int res =1;
    int mem =1;
    QList<int> help=primeFac(i);
    if (i < 2){return 1;}
    else {
        for(QList<int>::iterator iter = help.begin(); iter != help.end(); iter++){

            if (mem != *iter){
                res *= fac;
                fac = 1;
            }
            fac++;
            mem = *iter;
        }

        res *= fac;

        return res;
    }
}

int facsum(int i){
    int fac = 1;
    int res =1;
    int mem =1;
    int blub;
    QList<int> help=primeFac(i);
    if (i < 1){return 0;}
    else if (i == 1){return 1;}
    else {
        for(QList<int>::iterator iter = help.begin(); iter != help.end(); iter++){

            if (mem != *iter){

                if (mem == 1){blub = 1;}
                else {blub = (power(mem,fac)-1)/(mem-1);}
                res *= blub;
                fac = 1;
            }
            fac++;
            mem = *iter;
        }

        res *= (power(mem,fac)-1)/(mem-1);

        return res;
    }
}

int numberOfPrimes(int i){
    int res =0;
    i = abs(i);
    if (i==0){return 0;}
    else if (i==1){return 0;}
    else{
      QList<int> help=primeFac(i);
      for(QList<int>::iterator iter = help.begin(); iter != help.end(); iter++){
          res++;
      }
      return res;
    }
}

int lambda (int i){
    i = abs(i);
    if (i==0){return 0;}
    else if (i==1){return 1;}
    else{
      int k = numberOfPrimes(i);
      return power(-1, k);
    }
}

int phi(int i){
    int res=1;
    int help =1;
    if (i != 0){
      QList<int> primes = primeFac(i);

      for(QList<int>::iterator iter = primes.begin(); iter != primes.end(); iter++){
          if (help== *iter){res *= *iter;}
          else {res *= *iter-1;}
          help=*iter;
      }
    }
    return res;
}

int psi(int i){
    int res=1;
    int help =1;
    if (i != 0){
      QList<int> primes = primeFac(i);

      for(QList<int>::iterator iter = primes.begin(); iter != primes.end(); iter++){
          if (help== *iter){res *= *iter;}
          else {res *= *iter+1;}
          help=*iter;
      }
    }
    return res;
}

template <class T>
T max(T a, T b){
  if(a<b){return b;}
  else{return a;}
}

template <class T>
T min(T a, T b){
  if(a<b){return a;}
  else{return b;}
}

template <class T>
T gcd(T n, T m){
  T hilf;
  m=abs(m);
  n=abs(n);
  hilf =max(n,m);
  n = min(n,m);
  m = hilf;
  
  while(n > 0){
    hilf = m%n;
    m=n;
    n = hilf;
  }
  
 return m; 
}

template <class T>
T lcm(T n, T m){
  T a;
  a = n*m;

  T hilf;

  m=abs(m);
  n=abs(n);
  hilf =max(n,m);
  n = min(n,m);
  m = hilf;

  while(n > 0){
    hilf = m%n;
    m=n;
    n = hilf;
  }

  a=a/m;
  return a;
}


template <class T>
QPair<T,T> extendedgcd(T a, T b, int charac){
    QPair<T,T> res, info;
    T q, r;
    if (!(b > 0)){myStrToClass("1",&res.first,charac);myStrToClass("0", &res.second, charac);}
    else{
        r=a%b;
        q=(a-r)/b;
        info= extendedgcd(b, r, charac);
        res.first=info.second;
        res.second=info.first-(q*info.second);
    }
    return res;
}

template <class T>
QPair<T,T> exEu(T a, T b, int charac){
    QPair<T,T> res;
    T hilf, m, n;
    
    m=abs(a);
    n=abs(b);
    hilf =max(n,m);
    n = min(n,m);
    m = hilf; 
    
    res=extendedgcd(a, b, charac);
    return res;
}

#endif // NTH_H
