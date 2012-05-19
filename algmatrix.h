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

#ifndef ALGMATRIX_H
#define ALGMATRIX_H

#include <QList>
#include "algpoly.h"
#include <algcplx.h>

class algMatrix{
public:
    int lines;
    int columns;
    QList<algCplx> entries;

    algMatrix();
    algMatrix(int a, int b);
    
    ~algMatrix(){entries.clear();}

    algMatrix addLines( int i, int j, algCplx lambda);
    algMatrix changeLines( int i, int j);
    algPoly charPoly();
    algMatrix copy(algMatrix m);
    QList<algCplx>::Iterator element(int i, int j);
    algMatrix gauss();
    QString interpretation();
    algMatrix invert();
    algPoly miniPoly();
    algMatrix multLine( int i, algCplx lambda);
    int rank();
    algMatrix solve(algMatrix b);
    algCplx trace();
    
    friend algMatrix operator*( algMatrix m1, algMatrix m2 ){
      if (m1.columns != m2.lines){
        algMatrix res(1, 1);
        return res;
      }
      else{
        algMatrix res(m1.lines, m2.columns);
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

};

#endif // ALGalgMatrix_H
