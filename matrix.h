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

#ifndef MATRIX_H
#define MATRIX_H
#include <QString>
#include <QList>
#include "polynomial.h"
#include <QSharedPointer>

class matrix
{
public:

int lines;
int columns;
QList<complex> entries;

matrix();
matrix(int a, int b);

~matrix(){entries.clear();}

matrix addLines( int i, int j, complex lambda);
matrix changeLines( int i, int j);
polynomial charPoly();
QList<complex> column(unsigned int i);
matrix copy(matrix m);
QList<complex>::Iterator element(int i, int j);
complex det();
QList<complex> line(unsigned int i);
matrix multLine( int i, complex lambda);
complex trace();
matrix transpose();

friend matrix operator*( matrix m1, matrix m2 ){
  if (m1.columns != m2.lines){
    matrix res(1, 1);
    return res;
  }
  else{
    matrix res(m1.lines, m2.columns);
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

friend matrix operator+( matrix m1, matrix m2 ){
    if (m1.columns != m2.columns || m1.lines != m2.lines){
      matrix res(1, 1);
      return res;
    }
    else{
        matrix res(m1.lines, m1.columns);
        for(int i= 1; i<= m1.lines; i++){
          for (int j =1; j<= m2.columns;j++){
              *res.element(i,j) = (*m1.element(i,j)) +(*m2.element(i,j));
          }
        }
        return res;
    }
}

matrix operator-( matrix m2 ) const {
 matrix m1(*this);
 if (m1.columns != m2.columns || m1.lines != m2.lines){
   matrix res(1, 1);
   return res;
 }
 else{
     matrix res(m1.lines, m1.columns);
     for(int i= 1; i<= m1.lines; i++){
       for (int j =1; j<= m2.columns;j++){
           *res.element(i,j) = (*m1.element(i,j)) -(*m2.element(i,j));
       }
     }
     return res;
 }
}

};

#endif // MATRIX_H
