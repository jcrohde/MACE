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

#ifndef MVAR_H
#define MVAR_H

#include "math/variables/polynomial/algpoly.h"
#include "math/variables/scalar/algcplx.h"
#include "math/variables/scalar/maceint.h"
#include "math/variables/scalar/macerest.h"
#include "math/variables/polynomial/restpoly.h"
#include "math/variables/scalar/numreal.h"
#include "math/functiondistributors/combicalc.h"
#include "math/variables/function.h"
#include "math/variables/scalar/macestring.h"
#include "math/linearalgebra/algmatrix.h"
#include "math/linearalgebra/restmatrix.h"

enum type {
     ALGREAL = 2, ALGCPLX = 4,  ALGPOLY  = 16,
                 NUMREAL = 6, NUMCPLX = 24, NUMPOLY  = 96,
                 DISTDAT = 7,
                 FUNCTION = 192,
                 STRING = 13,
                 ALGMATRIX = 17,
                 REST    = 5, RESTPOLY = 25,
                 RESTMATRIX = 19,
    ERROR = -1
};

class MVar
{
private:

    MObject *obj;

    void copy(const MVar &v);

public:
    MVar();
    ~MVar();

    QString print(unsigned int prec) {return obj->print(prec);}
    type    getType() const;

    void    evalStr(std::string val, unsigned int dotPos, /*MaceInt charac,*/ bool cFunction);
    void    evalI  (bool cFunction);
    void    evalX  (/*MaceInt charac,*/ bool cFunction);

    /*bool    getInt       (MaceInt  *mi) const;
    bool    getAlgCplx   (algCplx  *az) const;
    bool    getAlgPoly   (algPoly  *ap) const;*/
    bool    getNumReal   (numReal  *nr) const;
    bool    getNumCplx   (numCplx  *nz) const;
    bool    getNumPoly   (numPoly  *np) const;
    bool    getDistDat   (DistDat  *dat) const;
    bool    getFunction  (Function *func) const;
    //bool    getRest      (MaceRest *mr) const;
    //bool    getRestPoly  (restPoly *rp) const;
    bool    getString    (MaceString *str) const;
    //bool    getAlgMatrix (algMatrix *am) const;
    //bool    getRestMatrix(restMatrix *rm) const;

    /*void    setInt       (MaceInt  &mi);
    void    setAlgCplx   (algCplx  &az);
    void    setAlgPoly   (algPoly  &ap);*/
    void    setNumReal   (numReal  &nr);
    void    setNumCplx   (numCplx  &nz);
    void    setNumPoly   (numPoly  &np);
    void    setDistDat   (DistDat  &dat);
    void    setFunction  (Function &func);
    //void    setRest      (MaceRest &mr);
    //void    setRestPoly  (restPoly &rp);
    void    setString    (MaceString &str);
    //void    setAlgMatrix (algMatrix &am);
    //void    setRestMatrix(restMatrix &rm);

    //void    forceInt(MaceRest &mr);

    bool    power(MVar *res, unsigned int i);

    MVar& operator=(const MVar& var) {
        if (this == &var) return *this;
        copy(var);
        return *this;
    }
};

extern bool     operate(MVar *res, MVar *a, MVar *b, char op);
extern bool  logOperate(MVar *res, MVar *a, MVar *b, char op);
extern bool boolOperate(MVar *res, MVar *a, MVar *b, char op);
extern bool       notOp(MVar *res, MVar *a);
extern void       minus(MVar *var/*, MaceInt charac*/);

#endif // MVAR_H
