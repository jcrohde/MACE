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

#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H

#include "math/kernel/mvar.h"
#include <boost/math/special_functions/spherical_harmonic.hpp>
#include "math/functiondistributors/analcalc.h"
#include "math/functiondistributors/arithcalc.h"
#include "math/functiondistributors/combicalc.h"
#include "math/functiondistributors/fctncalc.h"
#include "math/functiondistributors/tempcalc.h"
#include "math/functiondistributors/matrixcalc.h"
#include "math/functiondistributors/differentialcalc.h"

class distributor
{
private:

public:
    analCalc         analC;
    //arithCalc        arithC;
    combiCalc        combiC;
    fctnCalc         cplxC;
    tempCalc         tempC;
    //matrixCalc       matrixC;
    differentialCalc diffC;

    //MaceInt *charac;

    validCheck *validC;
    bool *function;

    distributor();

    bool distribute(MVar *arg0, MVar *arg1, MVar *arg2, MVar *arg3, std::string &func, int nr);

private:
    bool intDist    (MVar *arg, std::string &func);
    bool algCplxDist(MVar *arg, std::string &func);
    bool numRealDist(MVar *arg, std::string &func);
    bool numFuncDist(MVar *arg, std::string &func);
    bool calcDist   (MVar *arg, std::string &func);
    bool restDist   (MVar *arg, std::string &func);
    bool matrixDist (MVar *arg, std::string &func);

    bool twoIntDist      (MVar *arg0, MVar *arg1, std::string &func);
    bool tempDist        (MVar *arg0, MVar *arg1, std::string &func);
    bool doubleIntDist   (MVar *arg0, MVar *arg1, std::string &func);
    bool doubleDoubleDist(MVar *arg0, MVar *arg1, std::string &func);
    bool funcDoubleDist  (MVar *arg0, MVar *arg1, std::string &func);
    bool euklidDist      (MVar *arg0, MVar *arg1, std::string &func);
    bool CplxCplxDist    (MVar *arg0, MVar *arg1, std::string &func);
    bool restRestDist    (MVar *arg0, MVar *arg1, std::string &func);
    bool twoRestPolyDist (MVar *arg0, MVar *arg1, std::string &func);
    bool matrixMatrixDist(MVar *arg0, MVar *arg1, std::string &func);

    bool distFunc(DistDat &dd, MVar &var, std::string &fctn);

    bool matrixDist   (MVar *arg0, MVar *arg1, std::string &func);
    bool dbldbldblDist(MVar *arg0, MVar *arg1, MVar *arg2, std::string &func);
    bool      distdist(MVar *arg0, MVar *arg1,MVar *arg2, DistDat &dd,
                       const combiCalc::dist dist, const int nr, const bool withInt);
    bool matrixIntIntDist    (MVar *arg0, MVar *arg1, MVar *arg2, std::string &func);
    bool funcDblDblDist      (MVar *arg0, MVar *arg1, MVar *arg2, std::string &func);
    bool matrixIntIntCplxDist(MVar *arg0, MVar *arg1, MVar *arg2, MVar *arg3, std::string &func);

    //-checks for the variable getters---------------------------------

    /*bool      posCheck  (MaceInt &i);
    bool      bndCheck  (MaceInt &i);
    bool      siBndCheck(MaceInt &i);*/

    //-variable getters------------------------------------------------

    void getInt   (MVar   &var, unsigned int  &i);
    void getDouble(MVar   &var, double        &d);
    //void clInt    (MaceInt &mi, unsigned int &ui);
    //void clSInt   (MaceInt &mi, int          &si);
};

#endif // DISTRIBUTOR_H
