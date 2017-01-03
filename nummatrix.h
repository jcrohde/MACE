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

#ifndef NUMMATRIX_H
#define NUMMATRIX_H
#include <QList>
#include <QString>
#include "math/variables/scalar/numcplx.h"
#include "genmatrix.h"

class numMatrix :public genMatrix
{
public:

QList<numCplx> entries;

numMatrix();
numMatrix(int a, int b);

~numMatrix(){entries.clear();}

virtual void addLines( int i, int j, int c);
virtual void changeLines( int i, int j);
virtual void normLine(int i, int j);
virtual bool elemZero( int i, int j);

QList<numCplx> column(unsigned int i);
numMatrix copy(numMatrix m);
QList<numCplx>::Iterator element(int i, int j);
numCplx det();
QList<numCplx> line(unsigned int i);
virtual QString print(int i, int j);
numCplx trace();
numMatrix transpose();

friend numMatrix operator*( numMatrix m1, numMatrix m2 ){
  if (m1.columns != m2.lines){
    numMatrix res(1, 1);
    return res;
  }
  else{
    numMatrix res(m1.lines, m2.columns);
    for(int i= 1; i<= m1.lines; i++){
      for (int j =1; j<= m2.columns;j++){
          for (int k=1; k<= m1.columns; k++){
              *res.element(i,j) = (*res.element(i,j)) +((*m1.element(i,k))*(*m2.element(k,j)));
          }
      }
    }
    return res;
  }
}

friend numMatrix operator+( numMatrix m1, numMatrix m2 ){
    if (m1.columns != m2.columns || m1.lines != m2.lines){
      numMatrix res(1, 1);
      return res;
    }
    else{
        numMatrix res(m1.lines, m1.columns);
        for(int i= 1; i<= m1.lines; i++){
          for (int j =1; j<= m2.columns;j++){
              *res.element(i,j) = (*m1.element(i,j)) +(*m2.element(i,j));
          }
        }
        return res;
    }
}

numMatrix operator-( numMatrix m2 ) const {
 numMatrix m1(*this);
 if (m1.columns != m2.columns || m1.lines != m2.lines){
   numMatrix res(1, 1);
   return res;
 }
 else{
     numMatrix res(m1.lines, m1.columns);
     for(int i= 1; i<= m1.lines; i++){
       for (int j =1; j<= m2.columns;j++){
           *res.element(i,j) = (*m1.element(i,j)) -(*m2.element(i,j));
       }
     }
     return res;
 }
}

};

#endif // NUMMATRIX_H
