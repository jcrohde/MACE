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

#include "matrix.h"

matrix::matrix(){
    lines =1;
    columns = 1;
    complex zero;
    entries.append(zero);
}

matrix::matrix(int a, int b){
  lines =a;
  columns = b;
  complex zero;

  for (int i = 1; i <= a*b; i++){entries.append(zero);}
}


QList<complex> matrix::line(unsigned int i){
    QList<complex> res;
    QList<complex>::Iterator iter = entries.begin();
    for (int j = 1; j < (i-1)*columns; j++){
        iter++;
    }
    for (int j = 0; j < lines; j++){
        iter++;
        res.append(*iter);
    }
    return res;
}


QList<complex> matrix::column(unsigned int i){
    QList<complex> res;
    QList<complex>::Iterator iter = entries.begin();
    for (int j = 1; j < i;j++){
        iter++;
    }
    res.append(*iter);
    for(int k = 1; k <= lines; k++){
        for (int j = 1; j < columns; j++){
            iter++;
        }
        res.append(*iter);
    }
  return res;
}


QList<complex>::Iterator matrix::element(int i, int j){
    QList<complex>::Iterator iter = entries.begin();
    for (int m = 1; m <= (((i-1)*columns)+(j-1));m++){
        iter++;
    }
    return iter;
}


matrix matrix::transpose(){
  int i,j;
  matrix res(columns, lines);
  matrix help(*this);

  for (i = 1; i <= columns; i++){
    for (j=1; j<= lines; j++){
      *res.element(i,j) = *help.element(j,i);
    }
  }
  return res;
}

matrix matrix::changeLines( int i, int j){
  matrix tmp(*this), res(lines,columns);
  res = res.copy(tmp);
  for (int k=1; k<= columns; k++){
    *res.element(i,k) = *tmp.element(j,k);
    *res.element(j,k) = *tmp.element(i,k);
  }
  return res;
}

matrix matrix::addLines( int i, int j, complex lambda){
  matrix tmp(*this), res(lines,columns);
  res = res.copy(tmp);
  for (int k=1; k<= columns; k++){
    *res.element(i,k) = *tmp.element(i,k)+((*tmp.element(j,k))*lambda);
  }
  return res;
}

matrix matrix::multLine( int i, complex lambda){
  matrix tmp(*this), res(lines,columns);
  complex help;
  res = res.copy(tmp);
  for (int k=1; k<= columns; k++){
    help = *tmp.element(i,k);
    *res.element(i,k) = help*lambda;
  }
  return res;
}


complex matrix::det(){
    int clm= 1;
    int help;
    int i;

    complex factor, div, zero;

    complex minusOne;
    minusOne.real = -1;
    complex correct;
    correct.real = 1;

    matrix m(*this);
    if(m.lines!= m.columns){return zero;}
    else{
      matrix res(m.lines, m.columns);

      for (int x =1; x <= lines; x++){
          for (int y =1; y <= columns; y++){
              *res.element(x,y) = *m.element(x,y);
          }
      }

      for (int ln = 1; ln <= lines && ln <= columns; ln++){

        //find a pivot
        while(clm <= columns){
          help = ln;
          while(help < lines){
            if (*res.element(help,clm)!= zero){break;}
            help++;
          }
          if (*res.element(help,clm)!=zero){break;}
          else{clm++;}
        }

        //if one has found a pivot, take it into the right line and eliminate all other entries of its column.
        if (help <= lines && clm <=columns){

          if (help > ln){
            res = res.changeLines(help,ln);
            correct = correct*minusOne;
          }

          div = *res.element(ln,clm);
          correct = correct*div;
          div = div/(div*div);
          res = res.multLine(ln,div);

          for (i =ln+1 ; i <= lines; i++){
            if (*res.element(i,clm)!= zero){
              factor = *res.element(i,clm);
              factor = (factor-factor)-factor;
              res = res.addLines(i,ln,factor);
            }
          }

          clm++;
       }
     }

     for (i=1; i<=res.columns; i++){
         correct = correct*(*res.element(i,i));
     }
     return correct;
  }
}

complex matrix::trace(){
    matrix tmp(*this);
    complex res;
    if (tmp.lines != tmp.columns){
        return res;
    }
    else{
        for (int i=1;i<= tmp.columns; i++){
            res = res+(*tmp.element(i,i));
        }
        return res;
    }
}

matrix matrix::copy(matrix m){
    matrix res(*this);
    if (res.lines !=m.lines || res.lines !=m.lines){return res;}
    else{
    for (int x =1; x <= lines; x++){
        for (int y =1; y <= columns; y++){
            *res.element(x,y) = *m.element(x,y);
        }
    }
    return res;
    }
}

polynomial matrix::charPoly(){
    complex one(1,0), q, minusOne(-1,0);
    polynomial res, b, a(one);
    matrix tmp(*this);

    if (tmp.lines!=tmp.columns){return res;}
    else{
        matrix A(tmp.lines,tmp.columns), B(tmp.lines,tmp.columns), C(tmp.lines,tmp.columns),  I(tmp.lines,tmp.columns);

        for (int i = 1; i<= tmp.lines; i++){
            *I.element(i,i)=one;
        }

        A= A.copy(tmp);
        B= B.copy(I);
        res= a;

        for (int i = 1;i<=tmp.lines;i++){
            res.shift(1);
            C=A*B;
            q= C.trace();
            q.real= -q.real/i;
            q.imag= -q.imag/i;
            b= a;
            b= b.mult(q);
            res = res+b;
            for (int k = 1; k<= tmp.lines; k++){
                for (int j=1; j<=tmp.columns;j++){
                *B.element(k,j)=(*C.element(k,j))+(q*(*I.element(k,j)));
            }
            }

        }

        return res;
    }
}
