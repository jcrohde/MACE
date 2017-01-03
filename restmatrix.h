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

#ifndef RESTMATRIX_H
#define RESTMATRIX_H

/*#include <QString>
#include <list>
#include <gmp.h>
#include "math/variables/polynomial/restpoly.h"
#include "math/linearalgebra/genMatrix.h"

class restMatrix : public genMatrix{
    public:
    bool valid;
    MaceInt charac;
    std::list<MaceRest> entries;

    class lineColumnError{
        //exception class for non compatible numbers of lines for arithmetic matrix operations (+,-,*,...)
    };

    restMatrix();
    restMatrix(MaceInt c);
    restMatrix(int a, int b, MaceInt c);

    ~restMatrix(){entries.clear();}

    virtual void addLines( int i, int j, int c);
    virtual void changeLines( int i, int j);
    virtual void normLine(int i, int j);

    virtual bool elemZero( int i, int j);

    MaceRest adj(int i, int j);
    void adjoint(restMatrix &ad);
    restMatrix cross(restMatrix m);
    restPoly charPoly();
    restMatrix copy(restMatrix m);
    MaceRest det();
    std::list<MaceRest>::iterator element(int i, int j);
    restMatrix image();
    QString interpretation();
    bool invert(restMatrix &rm);
    restPoly miniPoly();
    void normalize();
    restMatrix null();
    virtual QString print(int i, int j);
    restMatrix solve(restMatrix b);
    MaceRest trace();
    restMatrix transpose();

    friend restMatrix operator*( restMatrix m1, restMatrix m2 ){
      if (m1.columns != m2.lines){
        lineColumnError e;
        throw e;
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

    restMatrix operator/( restMatrix m2 ) const {
     restMatrix m1(*this);
     if (m1.columns != m2.lines || m2.columns != m2.lines){
       restMatrix res(1, 1, charac);
       res.valid = false;
       return res;
     }
     else{
         restMatrix res(m1.lines, m1.columns, charac);
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

    friend restMatrix operator+( restMatrix m1, restMatrix m2 ){
        if (m1.columns != m2.columns || m1.lines != m2.lines){
            lineColumnError e;
            throw e;
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
         lineColumnError e;
         throw e;
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

    };*/

#endif // RESTMATRIX_H
