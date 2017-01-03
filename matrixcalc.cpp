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

#include "matrixcalc.h"

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

matrixCalc::matrixCalc()
{
}

matrixCalc::fctn matrixCalc::findFunc(std::string &str) {
    fctn func = NONE;

    if      (str == "zeroMatrix") func = ZEROMATRIX;
    else if (str == "diagMatrix") func = DIAGMATRIX;
    else if (str == "getEntry")   func = GETENTRY;
    else if (str == "setEntry")   func = SETENTRY;

    return func;
}

matrixCalc::matrixFctn matrixCalc::findMatrixFunc(std::string &str) {
    matrixFctn func = NOMATRIX;

    if      (str == "gauss")      func = GAUSS;
    else if (str == "adjoint")    func = ADJOINT;
    else if (str == "ortho")      func = GRAMSCHMIDT;
    else if (str == "image")      func = IMAGE;
    else if (str == "inverse")    func = INVERSE;
    else if (str == "nullspace")  func = NULLSPACE;
    else if (str == "transpose")  func = TRANSPOSE;
    else if (str == "eigenvalue") func = EIGENVALUE;

    return func;
}

matrixCalc::scalarFctn matrixCalc::findScalarFunc(std::string &str) {
    scalarFctn func = NOSCALAR;

    if      (str == "charPoly") func = CHARPOLY;
    else if (str == "miniPoly") func = MINIPOLY;
    else if (str == "det")      func = DET;
    else if (str == "trace")    func = TRACE;
    else if (str == "rank")     func = RANK;
    else if (str == "rows")     func = ROW;
    else if (str == "columns")  func = COLUMN;

    return func;
}

matrixCalc::matMatFctn matrixCalc::findMatMatFunc(std::string &str) {
    matMatFctn func = NOMATMAT;

    if      (str == "conj") func = CONJ;
    else if (str == "cross") func = CROSS;

    return func;
}

matrixCalc::genMatrixFctn matrixCalc::findGenFunc(std::string &str) {
    genMatrixFctn func = NOGEN;

    if      (str == "rows") func = ROWS;
    else if (str == "columns") func = COLUMNS;

    return func;
}

void matrixCalc::intCplxFunc(algMatrix *am, unsigned int i, algCplx &z, fctn func) {
    if (func == DIAGMATRIX) *am = algMatrix(i,i);
    for (int j = 1; j<=i; j++) {
        *am->element(j,j) = z;
    }
}

void matrixCalc::intIntFunc(algMatrix *am, unsigned int i, unsigned int j, fctn func) {
    if (func == ZEROMATRIX) *am = algMatrix(i,j);
}

void matrixCalc::intRestFunc(restMatrix *rm, unsigned int i, MaceRest &z, fctn func) {
    if (func == DIAGMATRIX) *rm = restMatrix(i,i,z.charac());
    for (int j = 1; j<=i; j++) {
        *rm->element(j,j) = z;
    }
}

void matrixCalc::intIntFunc(restMatrix *rm, unsigned int i, unsigned int j, MaceInt charac, fctn func) {
    if (func == ZEROMATRIX) *rm = restMatrix(i,j,charac);
}

void matrixCalc::intIntCplxFunc(algMatrix *am, unsigned int i, unsigned int j, algCplx &z, fctn func) {
    if (func == SETENTRY) *am->element(i,j) = z;
    if (func == GETENTRY) z = *am->element(i,j);
}

void matrixCalc::intIntRestFunc(restMatrix *rm, unsigned int i, unsigned int j, MaceRest &r, fctn func) {
    if (func == SETENTRY) *rm->element(i,j) = r;
    if (func == GETENTRY) r = *rm->element(i,j);
}

bool matrixCalc::matrixFunc(algMatrix &am, matrixFctn func) {
    bool valid = true;

    if      (func == GAUSS) am.gauss();
    else if (func == GRAMSCHMIDT) am.gramSchmidt();
    else if (func == IMAGE) am = am.image();
    else if (func == NULLSPACE) am = am.null();
    else if (func == TRANSPOSE) am = am.transpose();
    else {
        valid = valid && am.lines == am.columns;
        if      (valid && func == INVERSE) {
            algMatrix bm = am;
            valid = valid && bm.rank() == am.lines;
            if (valid) {
                algMatrix m;
                bm.invert(am);
            }
        }
        else if (valid && func == ADJOINT) {
            algMatrix m; am.adjoint(m); am = m;
        }
        else if (valid && func == EIGENVALUE) {
            algPoly p = am.miniPoly();
            numPoly n = p.toNumPoly();
            am.entries = n.zeroList();
            am.lines = am.entries.size();
            am.columns = 1;
        }
    }
    return valid;
}

bool matrixCalc::matrixFunc(restMatrix &rm, matrixFctn func) {
    bool valid = true;

    if      (func == GAUSS) rm.gauss();
    else if (func == IMAGE) rm = rm.image();
    else if (func == NULLSPACE) rm = rm.null();
    else if (func == TRANSPOSE) rm = rm.transpose();
    else {
        valid = valid && rm.lines == rm.columns;
        if      (valid && func == INVERSE) {
            restMatrix bm = rm;
            valid = valid && bm.rank() == rm.lines;
            if (valid) {
                bm.invert(rm);
            }
        }
        else if (valid && func == ADJOINT) {
            restMatrix m; rm.adjoint(m); rm = m;
        }
        else if (valid && func == EIGENVALUE) {
            restPoly p = rm.miniPoly();
            rm.entries = p.zeroList();
            rm.lines = rm.entries.size();
            rm.columns = 1;
        }
        else valid = false;
    }
    return valid;
}

bool matrixCalc::scalarFunc(algMatrix &am, scalarFctn func, algPoly &p) {
    bool valid = true;

    if      (func == RANK) p = algPoly(algCplx(am.rank(),0));
    else if (func == ROW) p = algPoly(algCplx(am.lines,0));
    else if (func == COLUMN) p = algPoly(algCplx(am.columns,0));
    else {
        valid = valid && am.lines == am.columns;
        if      (valid && func == CHARPOLY) p = am.charPoly();
        else if (valid && func == MINIPOLY) p = am.miniPoly();
        else if (valid && func == DET) {
            numMatrix n = am.toNumMatrix();
            numCplx nz = n.det();
            algCplx z;
            z.fromNumCplx(nz);
            p = algPoly(z);
        }
        else if (valid && func == TRACE) p = algPoly(am.trace());
    }
    return valid;
}

bool matrixCalc::scalarFunc(restMatrix &rm, scalarFctn func, restPoly &p) {
    bool valid = true;

    if (func == RANK) p = restPoly(MaceRest(rm.rank(),rm.charac));
    else {
        valid = valid && rm.lines == rm.columns;
        if      (valid && func == CHARPOLY) p = charPoly(rm);
        else if (valid && func == MINIPOLY) p = rm.miniPoly();
        else if (valid && func == DET) p = restPoly(rm.det());
        else if (valid && func == TRACE) p = restPoly(rm.trace());
    }
    return valid;
}

bool matrixCalc::matMatFunc(algMatrix &am, algMatrix &bm, matMatFctn func) {
    bool valid = true;

    if (func == CONJ) {
        valid = valid && am.lines == am.columns;
        valid = valid && am.lines == bm.columns;
        valid = valid && bm.lines == bm.columns;
        algMatrix amat2 = bm;
        valid = valid && amat2.rank() == bm.lines;
        if (valid) {
            amat2 = am*bm;
            am.invert(bm);
            am = bm*amat2;
        }
    }
    else if (func == CROSS) {
        valid = valid && am.lines == 3;
        valid = valid && am.columns == 1;
        valid = valid && bm.lines == 3;
        valid = valid && bm.columns == 1;
        if (valid) am = am.cross(bm);
    }
    else valid = false;
    return valid;
}

bool matrixCalc::matMatFunc(restMatrix &am, restMatrix &bm, matMatFctn func) {
    bool valid = true;

    if (func == CONJ) {
        valid = valid && am.lines == am.columns;
        valid = valid && am.lines == bm.columns;
        valid = valid && bm.lines == bm.columns;
        restMatrix amat2 = bm;
        valid = valid && amat2.rank() == bm.lines;
        if (valid) {
            amat2 = am*bm;
            am.invert(bm);
            am = bm*amat2;
        }
    }
    else if (func == CROSS) {
        valid = valid && am.lines == 3;
        valid = valid && am.columns == 1;
        valid = valid && bm.lines == 3;
        valid = valid && bm.columns == 1;
        if (valid) am = am.cross(bm);
    }
    else valid = false;
    return valid;
}

void matrixCalc::genMatFunc(genMatrix *m, MaceInt &i, genMatrixFctn func) {
    if (func == ROWS) i = i.translate(m->lines);
    if (func == COLUMNS)i = i.translate(m->columns);
}*/
