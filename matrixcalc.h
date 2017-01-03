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

#ifndef MATRIXCALC_H
#define MATRIXCALC_H

/*#include "math/linearalgebra/algmatrix.h"
#include "math/linearalgebra/restmatrix.h"

class matrixCalc
{
public:
    matrixCalc();

    enum fctn {
        ZEROMATRIX, DIAGMATRIX, SETENTRY, GETENTRY, NONE
    };

    enum matMatFctn {
        CONJ, CROSS, NOMATMAT
    };

    enum matrixFctn {
        GAUSS, ADJOINT, GRAMSCHMIDT, IMAGE, INVERSE, NULLSPACE, TRANSPOSE, EIGENVALUE, NOMATRIX
    };

    enum genMatrixFctn {
        ROWS, COLUMNS, NOGEN
    };

    enum scalarFctn {
        CHARPOLY, MINIPOLY, DET, TRACE, RANK, NOSCALAR, ROW, COLUMN
    };

    fctn          findFunc      (std::string &str);
    matrixFctn    findMatrixFunc(std::string &str);
    scalarFctn    findScalarFunc(std::string &str);
    matMatFctn    findMatMatFunc(std::string &str);
    genMatrixFctn findGenFunc   (std::string &str);

    void intIntFunc(algMatrix *am,  unsigned int i, unsigned int j, fctn func);
    void intCplxFunc(algMatrix *am, unsigned int i, algCplx &z, fctn func);
    void intIntFunc(restMatrix *rm, unsigned int i, unsigned int j, MaceInt charac, fctn func);
    void intRestFunc(restMatrix *rm, unsigned int i, MaceRest &z, fctn func);

    void intIntCplxFunc(algMatrix *am, unsigned int i, unsigned int j, algCplx &z, fctn func);
    void intIntRestFunc(restMatrix *am, unsigned int i, unsigned int j, MaceRest &z, fctn func);
    bool matrixFunc(algMatrix &am, matrixFctn func);
    bool matrixFunc(restMatrix &rm, matrixFctn func);
    bool scalarFunc(algMatrix &am, scalarFctn func, algPoly &p);
    bool scalarFunc(restMatrix &rm, scalarFctn func, restPoly &p);
    bool matMatFunc(algMatrix &am, algMatrix &bm, matMatFctn func);
    bool matMatFunc(restMatrix &am, restMatrix &bm, matMatFctn func);
    void genMatFunc(genMatrix *m, MaceInt &i, genMatrixFctn func);
};*/

#endif // MATRIXCALC_H
