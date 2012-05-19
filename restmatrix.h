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

#ifndef RESTrestMatrix_H
#define RESTrestMatrix_H
#include <QString>
#include <QList>
#include "restpolynomial.h"
#include "algmatrix.h"

class restMatrix{
    public:

    int lines;
    int columns;
    int charac;
    QList<rest> entries;

    restMatrix();
    restMatrix(int c);
    restMatrix(int a, int b, int c);

    ~restMatrix(){entries.clear();}

    restMatrix addLines( int i, int j, rest lambda);
    restMatrix changeLines( int i, int j);
    restpolynomial charPoly();
    restMatrix copy(restMatrix m);
    rest det();
    QList<rest>::Iterator element(int i, int j);
    restMatrix gauss();
    QString interpretation();
    restMatrix invert();
    restMatrix multLine( int i, rest lambda);
    restpolynomial miniPoly();
    void normalize();
    int rank();
    restMatrix solve(restMatrix b);
    rest trace();
    restMatrix transpose();
    
    friend restMatrix operator*( restMatrix m1, restMatrix m2 ){
      if (m1.columns != m2.lines){
        restMatrix res(1, 1, m1.charac);
        return res;
      }
      else{
        restMatrix res(m1.lines, m2.columns, m1.charac);
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

    friend restMatrix operator+( restMatrix m1, restMatrix m2 ){
        if (m1.columns != m2.columns || m1.lines != m2.lines){
          restMatrix res(1, 1, m1.charac);
          return res;
        }
        else{
            restMatrix res(m1.lines, m1.columns,m1.charac);
            for(int i= 1; i<= m1.lines; i++){
              for (int j =1; j<= m2.columns;j++){
                  *res.element(i,j) = (*m1.element(i,j)) +(*m2.element(i,j));
              }
            }
            return res;
        }
    }

    restMatrix operator-( restMatrix m2 ) const {
     restMatrix m1(*this);
     if (m1.columns != m2.columns || m1.lines != m2.lines){
       restMatrix res(1, 1, m1.charac);
       return res;
     }
     else{
         restMatrix res(m1.lines, m1.columns, m1.charac);
         for(int i= 1; i<= m1.lines; i++){
           for (int j =1; j<= m2.columns;j++){
               *res.element(i,j) = (*m1.element(i,j)) -(*m2.element(i,j));
           }
         }
         return res;
     }
     }

    };

#endif // RESTrestMatrix_H
