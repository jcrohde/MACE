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

#include "nummatrix.h"

numMatrix::numMatrix(): genMatrix(){

    numCplx zero;
    entries.append(zero);
}

numMatrix::numMatrix(int a, int b): genMatrix(a,b){

  numCplx zero;

  for (int i = 1; i <= a*b; i++){entries.append(zero);}
}


QList<numCplx> numMatrix::line(unsigned int i){
    QList<numCplx> res;
    QList<numCplx>::Iterator iter = entries.begin();
    for (int j = 1; j < (i-1)*columns; j++){
        iter++;
    }
    for (int j = 0; j < lines; j++){
        iter++;
        res.append(*iter);
    }
    return res;
}


QList<numCplx> numMatrix::column(unsigned int i){
    QList<numCplx> res;
    QList<numCplx>::Iterator iter = entries.begin();
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


QList<numCplx>::Iterator numMatrix::element(int i, int j){
    QList<numCplx>::Iterator iter = entries.begin();
    for (int m = 1; m <= (((i-1)*columns)+(j-1));m++){
        iter++;
    }
    return iter;
}

QString numMatrix::print(int i, int j){
    return element(i,j)->print(6);
}

numMatrix numMatrix::transpose(){
  int i,j;
  numMatrix res(columns, lines);
  numMatrix help(*this);

  for (i = 1; i <= columns; i++){
    for (j=1; j<= lines; j++){
      *res.element(i,j) = *help.element(j,i);
    }
  }
  return res;
}

void numMatrix::changeLines( int i, int j){
    numCplx help;
    for (int k=1; k<= columns; k++){
      help = *element(i,k);
      *element(i,k) = *element(j,k);
      *element(j,k) = help;
     }
}

void numMatrix::addLines( int i, int j, int c){
    numCplx z, help;
    z = z-*element(i,c);
    for (int k=1; k<= columns; k++){
        help = *element(j,k);
        help = help*z;
        help = (*element(i,k))+help;
        *element(i,k) = help;
    }
}

bool numMatrix::elemZero(int i, int j){
    numCplx z =  *element(i,j);
    return z.isZero();
}

void numMatrix::normLine( int i, int j){
  numCplx help = *element(i,j);
  if (!help.isZero()) {
      help.invert();
      for (int k=1; k<= columns; k++){
          *element(i,k) = (*element(i,k))*help;
      }
  }
}

numCplx numMatrix::det(){
    int clm= 1;
    int help;
    int i;

    numCplx factor, div, zero;

    numCplx minusOne(-1,0);
    numCplx correct(1,0);

    numMatrix m(*this);
    if(m.lines!= m.columns){return zero;}
    else{
      numMatrix res(m.lines, m.columns);

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
            res.changeLines(help,ln);
            correct = correct*minusOne;
          }

          div = *res.element(ln,clm);
          correct = correct*div;
          res.normLine(ln,clm);

          for (i =ln+1 ; i <= lines; i++){
            if (*res.element(i,clm)!= zero){
              res.addLines(i,ln,clm);
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

numCplx numMatrix::trace(){
    numMatrix tmp(*this);
    numCplx res;
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

numMatrix numMatrix::copy(numMatrix m){
    numMatrix res(*this);
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
