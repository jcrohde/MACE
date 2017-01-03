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

#ifndef ALGMATRIX_H
#define ALGMATRIX_H

/*#include <QList>
#include "math/variables/polynomial/algpoly.h"
#include "math/variables/scalar/algcplx.h"
#include "math/linearalgebra/nummatrix.h"
#include <QString>
#include "math/linearalgebra/genmatrix.h"

class algMatrix : public genMatrix {
public:
    QList<algCplx> entries;

    algMatrix();
    algMatrix(int a, int b);

    ~algMatrix(){entries.clear();}

    virtual void addLines( int i, int j, int c);
    virtual void changeLines( int i, int j);
    virtual void normLine( int i, int j);

    virtual bool elemZero( int i, int j);

    algPoly charPoly();
    algMatrix copy(algMatrix m);
    QList<algCplx>::Iterator element(int i, int j);

    algCplx adj (int i, int j);
    void adjoint(algMatrix &ad);

    algMatrix cross(algMatrix m);

    void subSkaProd(int i,int j);
    void norm(int i);
    void gramSchmidt();

    algMatrix image();
    QString interpretation();
    bool invert(algMatrix &am);
    algPoly miniPoly();
    algMatrix null();
    QString print(int i, int j);
    algMatrix solve(algMatrix b);

    algMatrix transpose();
    algCplx trace();

    numMatrix toNumMatrix();

    algMatrix zeroes(numPoly p);

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

    algMatrix operator/( algMatrix m2 ) const {
     algMatrix m1(*this);
     if (m1.columns != m2.lines || m2.columns != m2.lines){
       algMatrix res(1, 1);
       res.valid = false;
       return res;
     }
     else{
         algMatrix res(m1.lines, m1.columns);
         res.valid = m2.invert(m2);
         if (res.valid) {
             for(int i= 1; i<= m1.lines; i++){
                 for (int j =1; j<= m2.columns;j++){
                     for (int k=1; k<= m1.columns; k++){
                         *res.element(i,j) = (*res.element(i,j)) +((*m1.element(i,k))*(*m2.element(k,j)));
                     }
                }
             }
         }
         else {
             res = m1;
             res.valid = false;
         }
         return res;
     }
    }

    friend algMatrix operator+( algMatrix m1, algMatrix m2 ){
        if (m1.columns != m2.columns || m1.lines != m2.lines){
          algMatrix res(1, 1);
          return res;
        }
        else{
            algMatrix res(m1.lines, m1.columns);
            for(int i= 1; i<= m1.lines; i++){
              for (int j =1; j<= m2.columns;j++){
                  *res.element(i,j) = (*m1.element(i,j)) +(*m2.element(i,j));
              }
            }
            return res;
        }
    }

    algMatrix operator-( algMatrix m2 ) const {
     algMatrix m1(*this);
     if (m1.columns != m2.columns || m1.lines != m2.lines){
       algMatrix res(1, 1);
       return res;
     }
     else{
         algMatrix res(m1.lines, m1.columns);
         for(int i= 1; i<= m1.lines; i++){
           for (int j =1; j<= m2.columns;j++){
               *res.element(i,j) = (*m1.element(i,j)) -(*m2.element(i,j));
           }
         }
         return res;
     }
    }

};

extern void unitMatrix(unsigned int n, algMatrix &am);*/

#endif // ALGMATRIX_H
