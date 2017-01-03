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

#include "math/linearalgebra/linadist.h"
#include "math/kernel/parser.h"

/*static void translate(MaceRest *rest, algCplx *ac) {
    int i = mpz_get_si(rest->val.get_mpz_t());
    algCplx help(i,0);
    *ac = help;
}

static void translateBack(MaceRest *rest, algCplx *ac) {
    MaceRest help;
    mpz_set(help.mod.get_mpz_t(),rest->mod.get_mpz_t());
    mpq_get_num(help.val.get_mpz_t(),ac->getReal().get_mpq_t());
    *rest = help;
}

static restPoly charPoly(restMatrix &rm){
    algMatrix cp(rm.lines,rm.lines);
    MaceRest rest;
    restPoly res;
    algCplx cplx(0,0);
    for (int i = 1; i <= rm.lines; i++) {
        for (int j = 1; j <= rm.lines; j++) {
            rest = *rm.element(i,j);
            translate(&rest,&cplx);
            *cp.element(i,j) = cplx;
        }
    }

    algPoly ap = cp.charPoly();
    res.mons.clear();

    for (std::list<algCplx>::iterator iter = ap.mons.begin(); iter != ap.mons.end(); iter++) {
        cplx = *iter;
        translateBack(&rest,&cplx);
        rest.normalize();
        res.mons.push_back(rest);
    }

    algPoly aM = cp.charPoly();

    return res;
}

linadist::linadist()
{
}

// Char = 0 ////////////////////////////////////////////////////////////

QString linadist::matLinADist(algMatrix *M, QString op){
    QString res;
    algMatrix N;

    if(op == "inverse matrix"){
        const algCplx zero(0,0);
        N = *M;
        if (!M->invert(N)){
            res = "Error: The matrix does not have an inverse matrix.";
        }
        else{
           res = LAP.writeScalarMatOp("invert",M);
           *M = N;
        }  
    }
    if(op == "adjoint matrix"){
        if (M->lines == M->columns){
            M->adjoint(N);
            res = LAP.writeScalarMatOp("adjoint:",M);
            *M = N;
        }
        else {
            res = "Error: The number of rows and the number of columns do not coincide";
        }
    }
    if(op == "transposed matrix"){
        N = M->transpose();
        res = LAP.writeScalarMatOp("transpose",M);
        *M = N;

    }
    if(op == "gram schmidt"){
        res = LAP.writeScalarMatOp("Gram-Schmidt:",M);
        M->gramSchmidt();

    }
    else if(op == "gauss algorithm for a matrix"){
        N = *M;
        N.gauss();
        res = LAP.writeScalarMatOp("Gauss algorithm",M);
        *M = N;
    }
    else if(op == "image of a matrix"){
        N = *M;
        N=N.image();
        res = LAP.writeScalarMatOp("image of",M);
        *M = N;
    }
    else if(op == "nullspace of a matrix"){
        N = *M;
        N.gauss();
        N = N.null();
        res = LAP.writeScalarMatOp("nullspace of",M);
        *M = N;
    }

    return res;
}

QString linadist::scalarLinADist(QString *str, algMatrix M, QString op){
    QString res;

    if(op == "rank of a matrix"){
        algMatrix N=M;
        int i = N.rank();
        res = str->number(i);
        *str = LAP.writeScalarMatOp("rank",&M);
    }
    else if(op == "rows"){
        int i = M.lines;
        res = str->number(i);
        *str = LAP.writeScalarMatOp("rows",&M);
    }
    else if(op == "columns"){
        int i = M.columns;
        res = str->number(i);
        *str = LAP.writeScalarMatOp("columns",&M);
    }
    else if(op == "minimal polynomial of a matrix"){
        if (M.lines == M.columns) {
            algPoly p = M.miniPoly();
            res = p.print();
            *str = LAP.writeScalarMatOp("minimal polynomial",&M);
        }
        else {
            res = "Error: The number of rows and the number of columns do not coincide";
        }
    }
    else if(op == "characteristic polynomial of a matrix"){
        if (M.lines == M.columns) {
            algPoly p = M.charPoly();
            res = p.print();
            *str = LAP.writeScalarMatOp("characteristic polynomial",&M);
        }
        else {
            res = "Error: The number of rows and the number of columns do not coincide";
        }
    }
    else if(op == "eigenvalues of a matrix"){
        if (M.lines == M.columns) {
            algMatrix N=M;
            algPoly p = N.miniPoly();
            numPoly n = p.toNumPoly();
            res = n.zeroes();
            *str = LAP.writeScalarMatOp("eigenvalues of",&M);
        }
        else {
            res = "Error: The number of rows and the number of columns do not coincide";
        }
    }
    else if(op == "determinant of a matrix"){
        if (M.lines == M.columns) {
            numMatrix N = M.toNumMatrix();
            numCplx nC = N.det();
            res = nC.print(6);
            *str = LAP.writeScalarMatOp("det",&M);
        }
        else {
            res = "Error: The number of rows and the number of columns do not coincide";
        }
    }
    else if(op == "trace of a matrix"){
        if (M.lines == M.columns) {
            numMatrix N = M.toNumMatrix();
            numCplx nC = N.trace();
            res = nC.print(6);
            *str = LAP.writeScalarMatOp("trace",&M);
        }
        else {
            res = "Error: The number of rows and the number of columns do not coincide";
        }
    }

    return res;
}

QString linadist::SLE_dist(algMatrix a, algMatrix b){
    algMatrix c = a.solve(b);
    QString res=LAP.writeGauss(&a,&b,&c);
    res = res.append("interpretation: the set of solutions is given by");
    res = res.append(c.interpretation());
    return res;
}

// Char > 0 //////////////////////////////////////////////////////////////

QString linadist::matLinADist(restMatrix *M, QString op){
    QString res;
    restMatrix N(M->charac);

    if (op == "transposed matrix"){

        N = M->transpose();
        res = LAP.writeScalarMatOp("transpose",M);
        *M = N;
    }
    else if(op == "gauss algorithm for a matrix"){
        N = *M;
        N.gauss();
        res = LAP.writeScalarMatOp("Gauss algorithm",M);
        *M = N;
    }
    else if(op == "inverse matrix"){
        N = *M;
        if (!M->invert(N)) {
            res = "Error: The matrix does not have an inverse matrix.";
        }
        else{
            res = LAP.writeScalarMatOp("invert",M);
            *M = N;
        }

    }
    if(op == "adjoint matrix"){
        if (M->lines == M->columns){
            M->adjoint(N);
            res = LAP.writeScalarMatOp("adjoint:",M);
            *M = N;
        }
        else {
            res = "Error: The number of rows and the number of columns do not coincide";
        }
    }
    else if(op == "image of a matrix"){
        N = *M;
        N=N.image();
        res = LAP.writeScalarMatOp("image of",M);
        *M = N;
    }
    else if(op == "nullspace of a matrix"){
        N = *M;
        N = N.null();
        res = LAP.writeScalarMatOp("nullspace of",M);
        *M = N;
    }
    return res;
}

QString linadist::scalarLinADist(QString *str, restMatrix M, QString op){
    QString res;
    restMatrix N;

    if(op == "determinant of a matrix"){
        if (M.lines == M.columns) {
            N=M;
            MaceRest c = N.det();
            res = c.print();
            *str = LAP.writeScalarMatOp("det",&M);
        }
        else {
            res = "Error: The number of rows and the number of columns do not coincide";
        }
    }
    if(op == "rank of a matrix"){
        N = M;
        int i = N.rank();
        res = str->number(i);
        *str = LAP.writeScalarMatOp("rank",&M);
    }
    else if(op == "rows"){
        int i = M.lines;
        res = str->number(i);
        *str = LAP.writeScalarMatOp("rows",&M);
    }
    else if(op == "columns"){
        int i = M.columns;
        res = str->number(i);
        *str = LAP.writeScalarMatOp("columns",&M);
    }
    else if(op == "eigenvalues of a matrix"){
        if (M.lines == M.columns) {
            restPoly p = M.miniPoly();
            res = p.zeroes();
            *str = LAP.writeScalarMatOp("eigenvalues of",&M);
        }
        else {
            res = "Error: The number of rows and the number of columns do not coincide";
        }
    }
    else if(op == "characteristic polynomial of a matrix"){
        if (M.lines == M.columns) {
            restPoly p = charPoly(M);
            res = p.print();
            *str =LAP.writeScalarMatOp("characteristic polynomial",&M);
        }
        else {
            res = "Error: The number of rows and the number of columns do not coincide";
        }
    }
    else if(op == "minimal polynomial of a matrix"){
        if (M.lines == M.columns) {
            restPoly p = M.miniPoly();
            res = p.print();
            *str =LAP.writeScalarMatOp("minimal polynomial",&M);
        }
        else {
            res = "Error: The number of rows and the number of columns do not coincide";
        }
    }
    else if(op == "trace of a matrix"){
        if (M.lines == M.columns) {
            MaceRest p = M.trace();
            res = p.print();
            *str = LAP.writeScalarMatOp("trace",&M);
        }
        else {
            res = "Error: The number of rows and the number of columns do not coincide";
        }
    }
    return res;
}

QString linadist::SLE_dist(restMatrix a, restMatrix b){
    restMatrix c = a.solve(b);
    QString res=LAP.writeGauss(&a,&b,&c);
    res = res.append("interpretation: the set of solutions is given by");
    res = res.append(c.interpretation());
    return res;
}*/






