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

#include "distributor.h"

distributor::distributor()
{
}

bool distributor::distribute(MVar *arg0, MVar *arg1, MVar *arg2, MVar *arg3, std::string &func, int nr) {
    numCplx z;
    numReal d;
    bool res = false;

    if (nr == 1) {
        //if (charac->isZero()) {
            res = intDist(arg0,func);
            if (!res) {
                res = algCplxDist(arg0,func);
            }
            if (!res) {
                res = numRealDist(arg0,func);
            }
            if (!res) {
                res = numFuncDist(arg0,func);
            }
            if(arg0->getType()==DISTDAT) {
                DistDat dd;
                numReal nr;
                arg0->getDistDat(&dd);
                res = dd.prop(combiC,nr,func);
                if (res) {
                    arg0->setNumReal(nr);
                }
                else {
                    validC->setErr(ERRPROPDIST,dd.name);
                }
            }
            if (!res && func == "derivative") {
                Function f,g;
                if (arg0->getFunction(&f)){
                    if (derivative(g,f)) {
                        arg0->setFunction(g);
                        res = true;
                    }
                    else validC->setErr(NOTDIFFBAR);
                }
            }
            if (!res) {
                res = calcDist(arg0,func);
            }
        /*} else {
            if (!res && !charac->isZero()) {
                res = restDist(arg0,func);
            }
        }*/
        if (!res) {
            res = matrixDist(arg0,func);
        }
    }
    else if (nr == 2) {
        //if (charac->isZero()) {
            res = twoIntDist(arg0,arg1,func);
            if (!res) {
                res = doubleIntDist(arg0,arg1,func);
            }
            if (!res) {
                res = tempDist(arg0,arg1,func);
            }
            if (!res) {
                res = doubleDoubleDist(arg0,arg1,func);
            }
            if (!res) {
                res = funcDoubleDist(arg0,arg1,func);
            }
            if (!res) {
                res = CplxCplxDist(arg0,arg1,func);
            }
            if (!res) {
                res = euklidDist(arg0,arg1,func);
            }
            if(arg0->getType()==DISTDAT) {
                DistDat dd;
                arg0->getDistDat(&dd);
                res = distFunc(dd,*arg1,func);
                *arg0 = *arg1;
            }
        /*}
        else {
            if (!res && (arg0->getType()==RESTPOLY || arg1->getType()==RESTPOLY)) {
                res = twoRestPolyDist(arg0,arg1,func);
            }
            if (!res) {
                res = restRestDist(arg0,arg1,func);
            }
        }*/
        if (!res) {
            res = matrixDist(arg0,arg1,func);
        }
        if (!res) {
            res = matrixMatrixDist(arg0,arg1,func);
        }
    }
    else if (nr == 3) {
        /*MaceInt mi;
        if (func == "IF") {
            if (arg0->getInt(&mi)) {
                res = true;
                if (!mi.isZero()) *arg0 = *arg1;
                else *arg0 = *arg2;
            }
            else {
                validC->setErr(NOTBOOL,"IF");
            }
        }
        if (!res) {
            res = dbldbldblDist(arg0,arg1,arg2,func);
        }
        if (!res) {
            res = matrixIntIntDist(arg0,arg1,arg2,func);
        }
        if (!res) {
            res = funcDblDblDist(arg0,arg1,arg2,func);
        }*/
    }
    if (nr == 4) {
        /*res = matrixIntIntCplxDist(arg0,arg1,arg2,arg3,func);
        if (func == "spHarm") {
            if (*function) validC->setErr(CPLX,func);
            MaceInt      mi0,   mi1;
            numCplx      resC;
            numReal      nr0,   nr1;
            double       theta, phi;
            unsigned int m,     n;
            if (arg0->getNumReal(&nr0) && arg1->getNumReal(&nr1)) {
                phi = nr0.get(); theta = nr1.get();
                if (arg2->getInt(&mi0) && arg3->getInt(&mi1)) {
                    clInt(mi0,m); clInt(mi1,n);
                    resC.val.real() = boost::math::spherical_harmonic_r(n,m,theta,phi);
                    resC.val.imag() = boost::math::spherical_harmonic_i(n,m,theta,phi);
                    arg0->setNumCplx(resC);
                } else validC->setErr(NOTIR,"spHarm");
            } else validC->setErr(NOTIR,"spHarm");
            res = true;
        }*/
    }
    if (!res) {
        combiCalc::dist dist;
        bool            withInt;
        int             vars;
        combiC.findDist(&withInt, func, dist, vars);
        if (dist != combiCalc::NONE && vars == nr) {
            DistDat dd;
            dd.name = func;
            if (distdist(arg0,arg1,arg2,dd,dist,nr,withInt)) {
                arg0->setDistDat(dd);
            }
            else {
                validC->setErr(ERRDIST,dd.name);
            }
            res = true;
        }
    }
    return res;
}

bool distributor::intDist(MVar *arg, std::string &func) {
    /*MaceInt i;
    unsigned int j;
    arithCalc::intFctn iFctn = arithC.findIntFctn(&func);

    if (iFctn != arithCalc::NOI) {
        if (arg->getInt(&i)) {
            clInt(i,j);
            if (validC->isValid()) {
                arithC.intFunc(&i,j,iFctn);
            }
            arg->setInt(i);
            return true;
        } else {
            validC->setErr(NOTINT,func);
        }
    }*/
    return false;
}

bool distributor::algCplxDist(MVar *arg, std::string &func) {
    /*if (func == "imag" || func == "real") {
        algCplx aCplx;
        if (arg->getAlgCplx(&aCplx)) {
            if (func == "real") aCplx = aCplx.getRealPart();
            else                aCplx = aCplx.getImagPart();
            arg->setAlgCplx(aCplx);
            return true;
        }
    }*/
    return false;
}

bool distributor::numRealDist(MVar *arg, std::string &func) {
    numReal d;
    double dbl;
    analCalc::fctn rFctn = analC.findRealFctn(&func);

    if (rFctn != analCalc::NONE) {
        if (arg->getNumReal(&d)) {
            dbl = d.get();
            if (validC->isValid()) {
                if (!analC.doubleFctn(&dbl,rFctn)) {
                    validC->setErr(ERRINFCTN,func);
                }
            }
            d.set(dbl);
            arg->setNumReal(d);
            return true;
        } else {
            validC->setErr(NOTREAL,func);
        }
    }
    return false;
}

bool distributor::numFuncDist(MVar *arg, std::string &func) {
    numCplx nz;
    numReal nr;
    double  d;
    Function f;
    analCalc::fctns fctn = cplxC.findFunction(&func);

    if (fctn != charZeroCalc::NONE) {
        if (arg->getNumReal(&nr)) {
            d=nr.get();
            if (validC->isValid()) {
                if (!analC.analFctn(&d,fctn)) {
                    validC->setErr(ERRINFCTN,func);
                }
            }
            nr.set(d);
            arg->setNumReal(nr);
            return true;
        }
        else if (arg->getNumCplx(&nz)) {
            if (!cplxC.functions(&nz.val,fctn)) {
                validC->setErr(ERRINFCTN,func);
            }
            arg->setNumCplx(nz);
            return true;
        }
        else if (arg->getFunction(&f)) {
            setFunc(f,f,f,func,1);
            arg->setFunction(f);
            return true;
        }
        else {
            validC->setErr(NOTCPLX,func);
        }
    }
    else if (func == "polar") {
        if (arg->getNumCplx(&nz)) {
            if (*function) validC->setErr(CPLX,func);
             nz.val=cplxC.toPolar(nz.val);
             arg->setNumCplx(nz);
             return true;
        }
        else {
            validC->setErr(NOTCPLX,func);
        }
    }
    return false;
}

bool distributor::calcDist(MVar *arg, std::string &func) {
    differentialCalc::func FCTN = diffC.findVectorialFunc(func);
    if (FCTN != differentialCalc::NONE) {
        Function function;
        if (arg->getFunction(&function)) {
            MaceString MStr;
            std::vector<numReal> z;
            if (function.real()) {
                if (diffC.vectorialFunc(FCTN,function,z)) {
                    std::complex<double> p;
                    bool periodic = false;
                    if (FCTN == differentialCalc::ZEROES) periodic = function.period(p);
                    else if (FCTN == differentialCalc::EXTREMA) {
                        Function der;
                        derivative(der,function);
                        periodic = der.period(p);
                    }
                    else if (FCTN == differentialCalc::INFLEXION) {
                        Function der,der2;
                        derivative(der,function);
                        derivative(der2,der);
                        periodic = der2.period(p);
                    }
                    periodic = periodic && p.imag() < 0.000001;
                    for (int i = 0; i < z.size(); i++) {
                        MStr.str = MStr.str.append(z[i].print(6));
                        if (periodic) {
                            QString help;
                            help = help.setNum(p.real());
                            MStr.str = MStr.str.append(" + k*");
                            MStr.str = MStr.str.append(help);
                        }
                        MStr.str = MStr.str.append(", ");
                    }
                    if (z.size() == 0) MStr.str = "No points found  ";
                    MStr.str.chop(2);
                }
                else {
                    Function der;
                    if (derivative(der,function))
                        MStr.str = "No points found.";
                    else
                        validC->setErr(NOTDIFFBAR);
                }
                arg->setString(MStr);
                return true;
            }
            else validC->setErr(NOTREALFUNC);


        }
    }
    else {
        FCTN = diffC.findCplxFunc(func);
        if (FCTN != differentialCalc::NONE) {
            std::complex<double> z;
            Function function;
            if (arg->getFunction(&function)) {
                if (diffC.cplxFunc(FCTN,function,z)) {
                    numCplx nz;
                    nz.val = z;
                    arg->setNumCplx(nz);

                }
                else {
                    MaceString MStr;
                    MStr.str = "No period has been found.";
                    arg->setString(MStr);
                }
                return true;
            }
        }
    }
    return false;
}

bool distributor::restDist(MVar *arg, std::string &func) {
    /*MaceRest     r;
    MaceInt      mi;
    unsigned int j;
    arithCalc::intFctn iFctn = arithC.findIntFctn(&func);

    if (iFctn != arithCalc::NOI) {
        if (arg->getRest(&r)) {
            mi = r.IntPret();
            if (iFctn == arithCalc::FAC || iFctn == arithCalc::FIBO)
                clInt(mi,j);
            if (validC->isValid()) arithC.intFunc(&mi,j,iFctn);
            r.translate(mi);
            arg->setRest(r);
            return true;
        } else {
            validC->setErr(NOTREST,func);
        }
    }*/
    return false;
}

bool distributor::matrixDist(MVar *arg, std::string &func) {
    /*algMatrix    m;
    restMatrix   rm;
    MaceInt      mi;
    unsigned int j;
    matrixCalc::matrixFctn fctn = matrixC.findMatrixFunc(func);
    matrixCalc::scalarFctn sfctn = matrixC.findScalarFunc(func);
    matrixCalc::genMatrixFctn gfctn = matrixC.findGenFunc(func);

    if (fctn != matrixCalc::NOMATRIX) {
        bool valid = true;
        if (charac->isZero()) {
            valid = valid && arg->getAlgMatrix(&m);
            if (valid) valid = matrixC.matrixFunc(m,fctn);
            if (valid) arg->setAlgMatrix(m);
        }
        else {
            valid = valid && arg->getRestMatrix(&rm);
            if (valid) valid = matrixC.matrixFunc(rm,fctn);
            if (valid) arg->setRestMatrix(rm);
        }
        if (valid) return true;
    }
    else if (gfctn != matrixCalc::NOGEN) {
        if (arg->getAlgMatrix(&m)) matrixC.genMatFunc(&m,mi,gfctn);
        if (arg->getRestMatrix(&rm)) matrixC.genMatFunc(&rm,mi,gfctn);
        arg->setInt(mi);
        return true;
    }
    else if (func == "printMatrix") {
        if (arg->getType() == ALGMATRIX || arg->getType() == RESTMATRIX) {
            QString str = arg->print(0);
            MaceString mstr;
            mstr.str = str;
            arg->setString(mstr);
            return true;
        }
        else return false;
    }
    else if (sfctn != matrixCalc::NOSCALAR) {
        bool valid = true;
        if (charac->isZero()) {
            valid = valid && arg->getAlgMatrix(&m);
            algPoly p;
            valid = valid && matrixC.scalarFunc(m,sfctn,p);
            if (valid) arg->setAlgPoly(p);
        }
        else {
            valid = valid && arg->getRestMatrix(&rm);
            restPoly p;
            valid = valid && matrixC.scalarFunc(rm,sfctn,p);
            if (valid) arg->setRestPoly(p);
        }
        if (valid) return true;
    }*/
    return false;
}

bool distributor::twoIntDist(MVar *arg0, MVar *arg1, std::string &func) {
    /*MaceInt i, j;

    arithCalc::intFctn     iFctn = arithC.find2intFctn(&func);

    if (iFctn != arithCalc::NOI) {
        if (arg0->getInt(&i) && arg1->getInt(&j)) {
            unsigned int ui;
            clInt(i,ui); clInt (j,ui);
            if (!arithC.twoIntFctn(&i,&j,iFctn)) {
                validC->setErr(ERRINFCTN,func);
            }
            arg0->setInt(i);
            return true;
        } else {
            validC->setErr(NOTINT,func);
        }
    }*/
    return false;
}

bool distributor::tempDist(MVar *arg0, MVar *arg1, std::string &func) {
    /*tempCalc::tempFctn     cFctn = tempC.findXIntFctn(func);
    numReal nr;
    MaceInt i,j;
    double  d;
    int     ii;

    if (cFctn != tempCalc::NO) {
        if (arg0->getInt(&i) && arg1->getInt(&j)) {
            int si, sj; clSInt(i,si); clSInt(j,sj);
            if (!tempC.intIntFctn(si,sj,cFctn)) {
                validC->setErr(ERRINFCTN,func);
            }
            i = i.translate(si);
            arg0->setInt(i);
            return true;
        }
        else if (arg1->getInt(&i) && arg0->getNumReal(&nr) && charac->isZero()) {
            clSInt(i,ii); d = nr.get();
            if (!tempC.doubleIntFctn(d,ii,cFctn)) {
                validC->setErr(ERRINFCTN,func);
            }
            nr.set(d);
            arg0->setNumReal(nr);
            return true;
        }
        else {
            validC->setErr(NOTIR,func);
        }
    }*/
    return false;
}

bool distributor::doubleIntDist(MVar *arg0, MVar *arg1, std::string &func) {
    /*numReal      nr;
    MaceInt      i;
    double       d;
    unsigned int ii;

    analCalc::fctn     aFctn = analC.findIntDoubleFctn(func);
    if (aFctn !=analCalc::NONE) {
        if (arg0->getInt(&i) && arg1->getNumReal(&nr)) {
            clInt(i,ii);
            d = nr.get();
            if (!analC.intDoubleFctn(ii,d,aFctn)) {
                validC->setErr(ERRINFCTN,func);
            }
            nr.set(d); arg0->setNumReal(nr);
            return true;
        }
        else {
            validC->setErr(NOTIR,func);
        }
    }*/

    return false;
}

bool distributor::doubleDoubleDist(MVar *arg0, MVar *arg1, std::string &func) {
    numReal nr0, nr1;
    double  d0,  d1;
    bool    dd = true;

    analCalc::fctn aFctn = analC.findDoubleDoubleFctn(func);
    if (aFctn != analCalc::NONE) {
        if (arg0->getNumReal(&nr0) && arg1->getNumReal(&nr1)) {
            d0 = nr0.get(); d1 = nr1.get();
            if (!analC.doubleDoubleFctn(d0,d1,aFctn)) {
                validC->setErr(ERRINFCTN,func);
            }
            nr0.set(d0); arg0->setNumReal(nr0);
            return true;
        } else dd = false;
    }
    if (!dd) {
        {
            validC->setErr(NOTREAL,func);
        }
    }
    return false;
}

bool distributor::funcDoubleDist(MVar *arg0, MVar *arg1, std::string &func) {
    Function f;
    numReal  nr;

    differentialCalc::func FCTN = diffC.findLineFunc(func);
    if (FCTN != differentialCalc::NONE) {
        if (arg0->getFunction(&f) && arg1->getNumReal(&nr)) {
            if (!diffC.lineFunc(FCTN,f,nr)) {
                validC->setErr(NOTDIFFBAR);
            }
            arg0->setFunction(f);
            return true;
        }
    }
    return false;
}

bool distributor::euklidDist(MVar *arg0, MVar *arg1, std::string &func) {
    /*algPoly p, q, r;
    MaceInt i, j;

    arithCalc::twoPolyFctn pfctn = arithC.find2polyFctn(&func);

    if (pfctn != arithCalc::NO) {
        if (arg0->getInt(&i) && arg1->getInt(&j)) {
            arithC.twoIFctn(&i,&j,pfctn);
            arg0->setInt(i);
            return true;
        }
        else if (arg0->getAlgPoly(&p) && arg1->getAlgPoly(&q)) {
            if (p.degree() > 0 || q.degree() > 0) {
                arithC.twoPFctn(&r,p,q,pfctn);
                arg0->setAlgPoly(r);
                return true;
            }
        }
        validC->setErr(NOTPOLY,func);
    }*/
    return false;
}

bool distributor::CplxCplxDist(MVar *arg0, MVar *arg1, std::string &func) {
    numCplx z0,  z1;
    numReal nr0, nr1;
    Function func0, func1;

    if (func == "log") {
        if (arg0->getNumReal(&nr0) && arg1->getNumReal(&nr1)) {
            double d0 = nr0.get();
            double d1 = nr1.get();
            if (d0 > 0.0 && d1 >0.0) {
                d0= log(d1) / log(d0);
                nr0.set(d0); arg0->setNumReal(nr0);
                return true;
            } else {
                validC->setErr(ERRINFCTN,func);
            }
        }
        else if (arg0->getNumCplx(&z0) && arg1->getNumCplx(&z1)) {
            arg0->getNumCplx(&z0);
            arg1->getNumCplx(&z1);
            cplxC.log_func(&z0,&z1);
            arg0->setNumCplx(z0);
            return true;
        }
        else if (arg0->getFunction(&func0) && arg1->getFunction(&func1)) {
            Function f;
            bool valid = setFunc(f,func0,func1,func,2);
            if (valid) arg0->setFunction(f);
            return valid;
        } else {
            validC->setErr(NOTCPLX,func);
        }
    }
    return false;
}

bool distributor::restRestDist(MVar *arg0, MVar *arg1, std::string &func) {
    /*MVar     cpy0, cpy1;
    MaceRest r0,   r1;

    MaceInt i, j;
    bool intb = true;

    arithCalc::twoPolyFctn pfctn = arithC.find2polyFctn(&func);
    arithCalc::intFctn     iFctn = arithC.find2intFctn(&func);
    tempCalc::tempFctn     cFctn = tempC.findXIntFctn(func);

    if (pfctn != arithCalc::NO) {
        if (arg0->getRest(&r0) && arg1->getRest(&r1)) {
            i = r0.IntPret(); j = r1.IntPret();
            arithC.twoIFctn(&i,&j,pfctn);
            r0.translate(i);
            arg0->setRest(r0);
            return true;
        } else intb = false;
    }
    else if (iFctn != arithCalc::NOI) {
        if (arg0->getRest(&r0) && arg1->getRest(&r1)) {
            i = r0.IntPret(); j = r1.IntPret();
            if (!arithC.twoIntFctn(&i,&j,iFctn)) {
                validC->setErr(ERRINFCTN,func);
            }
            r0.translate(i);
            arg0->setRest(r0);
            return true;
        } else intb = false;
    }
    else if (cFctn != tempCalc::NO) {
        if (arg0->getRest(&r0) && arg1->getRest(&r1)) {
            i = r0.IntPret(); j = r1.IntPret();
            int si, sj; clSInt(i,si); clSInt(j,sj);
            if (!tempC.intIntFctn(si,sj,cFctn)) {
                validC->setErr(ERRINFCTN,func);
            }
            i = i.translate(si);
            r0.translate(i);
            arg0->setRest(r0);
            return true;
        } else intb = false;
    }
    if (!intb) {
        validC->setErr(NOTREST,func);
    }
    return false;

    if (twoIntDist(&cpy0,&cpy1,func)) {
        if (arg0->getRest(&r0) && arg1->getRest(&r1)) {
            cpy0.forceInt(r0);
            cpy1.forceInt(r1);
            cpy0.getRest(&r0);
            arg0->setRest(r0);
            return true;
        }

    }*/
    return false;
}

bool distributor::twoRestPolyDist(MVar *arg0, MVar *arg1, std::string &func) {
    /*restPoly r, p, q;
    arithCalc::twoPolyFctn pfctn = arithC.find2polyFctn(&func);

    arg0->getRestPoly(&p); arg1->getRestPoly(&q);
    if (pfctn != arithCalc::NO) {
        arithC.twoRPFctn(&p,&q,pfctn);
        arg0->setRestPoly(p);
        return true;
    }*/
    return false;
}

bool distributor::distFunc(DistDat &dd, MVar &var, std::string &fctn) {
    numReal      nr;
    double       d;
    unsigned int i;
    bool         res = false;

    /*combiCalc::fctn fu = combiC.findFunc(fctn);
    if (fu != combiCalc::NONE) {
        if(dd.iDat.size() == 0) {
            if (dd.dDat.size() == 1) {
                if (dd.dist == combiCalc::BERNOULLI || dd.dist == combiCalc::POISSON) {
                    getInt(var,i);
                    d = combiC.func1intDist(&res,dd.dDat[0],i,fu,dd.dist);
                }
                else {
                    getDouble(var,d);
                    d = combiC.func1dist(&res,dd.dDat[0],d,fu,dd.dist);
                }
            }
            if (dd.dDat.size() == 2) {
                getDouble(var,d);
                d = combiC.func2dist(&res,dd.dDat[0],dd.dDat[1],d,fu,dd.dist);
            }
            if (dd.dDat.size() == 3) {
                getDouble(var,d);
                d = combiC.func3dist(&res,dd.dDat[0],dd.dDat[1],dd.dDat[2],d,fu,dd.dist);
            }
        } else {
            if (dd.iDat.size() == 1 && dd.dDat.size() == 1) {
                getInt(var,i);
                d = combiC.func2intDist(&res,dd.iDat[0],dd.dDat[0],i,fu,dd.dist);
            }
            if (dd.iDat.size() == 3) {
                getInt(var,i);
                d = combiC.func3intDist(&res,dd.iDat[0],dd.iDat[1],dd.iDat[2],i,fu,dd.dist);
            }
        }
    }
    else return res = false;
    res = res || d != d;
    nr.set(d);
    var.setNumReal(nr);
    if (res) validC->setErr(ERRFUNCDIST,dd.name);*/
    return !res;
}

bool distributor::matrixDist(MVar *arg0, MVar *arg1, std::string &func) {
    /*algMatrix am;
    restMatrix rm;
    algCplx z;
    MaceRest r;
    unsigned int i, j;

    matrixCalc::fctn fun = matrixC.findFunc(func);
    if (fun != matrixCalc::NONE) {
        getInt(*arg0,i);
        if (charac->isZero()) {
            if (fun == matrixCalc::DIAGMATRIX) {
                if (arg1->getAlgCplx(&z)) {
                    matrixC.intCplxFunc(&am,i,z,fun);
                }
            }
            else {
                getInt(*arg1,j);
                matrixC.intIntFunc(&am,i,j,fun);
            }
            arg0->setAlgMatrix(am);
        }
        else {
            if (fun == matrixCalc::DIAGMATRIX) {
                if (arg1->getRest(&r)) {
                    matrixC.intRestFunc(&rm,i,r,fun);
                }
            }
            else {
                getInt(*arg1,j);
                matrixC.intIntFunc(&rm,i,j,*charac,fun);
            }
            arg0->setRestMatrix(rm);
        }
        return true;
    }*/
    return false;
}

bool distributor::matrixMatrixDist(MVar *arg0, MVar *arg1, std::string &func) {
    /*algMatrix am, bm;
    restMatrix rm, sm;*/
    bool valid = true;

    /*matrixCalc::matMatFctn fun = matrixC.findMatMatFunc(func);
    valid = valid && fun != matrixCalc::NOMATMAT;
    if (charac->isZero()) {
        valid = valid && arg0->getAlgMatrix(&am) && arg1->getAlgMatrix(&bm);
        valid = valid && matrixC.matMatFunc(am,bm,fun);
        if (valid) arg0->setAlgMatrix(am);
    }
    else {
        valid = valid && arg0->getRestMatrix(&rm) && arg1->getRestMatrix(&sm);
        valid = valid && matrixC.matMatFunc(rm,sm,fun);
        if (valid) arg0->setRestMatrix(rm);
    }*/
    return valid;
}

bool distributor::dbldbldblDist(MVar *arg0, MVar *arg1, MVar *arg2, std::string &func) {
    numReal nr0, nr1, nr2;
    double  d0,  d1,  d2;

    analCalc::fctn aFctn = analC.findDoubleDoubleDoubleFctn(func);
    if (aFctn != analCalc::NONE) {
        if (arg0->getNumReal(&nr0) && arg1->getNumReal(&nr1) && arg2->getNumReal(&nr2)) {
            d0 = nr0.get(); d1 = nr1.get(); d2 = nr2.get();
            if (!analC.doubleDoubleDoubleFctn(d0,d1,d2,aFctn)) {
                validC->setErr(ERRINFCTN,func);
            }
            nr0.set(d0); arg0->setNumReal(nr0);
            return true;
        }
        else {
            validC->setErr(NOTREAL,func);
        }
    }
    return false;
}

bool distributor::matrixIntIntDist(MVar *arg0, MVar *arg1, MVar *arg2, std::string &func) {
    /*algMatrix    am;
    restMatrix   rm;
    algCplx      z;
    MaceRest     r;
    unsigned int i, j;

    matrixCalc::fctn fun = matrixC.findFunc(func);
    if (fun != matrixCalc::NONE) {
        bool valid = true;
        if (charac->isZero()) valid = valid && arg0->getAlgMatrix(&am);
        else                  valid = valid && arg0->getRestMatrix(&rm);
        getInt(*arg1,i); getInt(*arg2,j);
        if (valid) {
            if (charac->isZero()) {
                matrixC.intIntCplxFunc(&am,i,j,z,fun);
                arg0->setAlgCplx(z);
            }
            else {
                matrixC.intIntRestFunc(&rm,i,j,r,fun);
                arg0->setRest(r);
            }
            return true;
        }
    }*/
    return false;
}

bool distributor::funcDblDblDist(MVar *arg0, MVar *arg1, MVar *arg2, std::string &func) {
    Function f;
    numReal  a, b;
    if (func == "integral") {
        if (arg0->getFunction(&f) && arg1->getNumReal(&a) && arg2->getNumReal(&b)) {
            if (f.real() && a.get() <= b.get()) {
                double i = integral(f,a,b);
                a.set(i);
                arg0->setNumReal(a);
                return true;
            }
        }
    }
    return false;
}

bool distributor::distdist(MVar *arg0, MVar *arg1, MVar *arg2, DistDat &dd,
                      const combiCalc::dist dist, const int nr, const bool withInt)
{
    /*numReal      nur;
    MaceInt      mi;
    unsigned int ui;
    bool         res=false;

    dd.dDat.clear(); dd.iDat.clear();
    dd.dist = dist;
    if (nr == 1) {
        arg0->getNumReal(&nur);
        dd.dDat.push_back(nur.get());
        res = true;
    }
    if (nr == 2) {
        if (withInt) {
            res = arg0->getInt(&mi);
            clInt(mi,ui);
            dd.iDat.push_back(ui);
        }
        else {
            res = arg0->getNumReal(&nur);
            dd.dDat.push_back(nur.get());
        }
        res = res && arg1->getNumReal(&nur);
        dd.dDat.push_back(nur.get());
    }
    if (nr == 3) {
        if (withInt) {
            res = arg0->getInt(&mi);
            clInt(mi,ui);
            dd.iDat.push_back(ui);
            res = res && arg1->getInt(&mi);
            clInt(mi,ui);
            dd.iDat.push_back(ui);
            res = res && arg2->getInt(&mi);
            clInt(mi,ui);
            dd.iDat.push_back(ui);
        }
        else {
            res = arg0->getNumReal(&nur);
            dd.dDat.push_back(nur.get());
            res = res && arg1->getNumReal(&nur);
            dd.dDat.push_back(nur.get());
            res = res && arg2->getNumReal(&nur);
            dd.dDat.push_back(nur.get());
        }
    }*/
    return true;//res;
}

bool distributor::matrixIntIntCplxDist(MVar *arg0,
                                       MVar *arg1,
                                       MVar *arg2,
                                       MVar *arg3,
                                       std::string &func)
{
    /*algMatrix    am;
    restMatrix   rm;
    algCplx      z;
    MaceRest     r;
    unsigned int i, j;

    matrixCalc::fctn fun = matrixC.findFunc(func);
    if (fun != matrixCalc::NONE) {
        bool valid = true;
        if (charac->isZero()) valid = valid && arg0->getAlgMatrix(&am);
        else                  valid = valid && arg0->getRestMatrix(&rm);
        getInt(*arg1,i); getInt(*arg2,j);
        if (charac->isZero()) valid = valid && arg3->getAlgCplx(&z);
        else                  valid = valid && arg3->getRest(&r);
        if (valid) {
            if (charac->isZero()) {
                matrixC.intIntCplxFunc(&am,i,j,z,fun);
                arg0->setAlgMatrix(am);
            }
            else {
                matrixC.intIntRestFunc(&rm,i,j,r,fun);
                arg0->setRestMatrix(rm);
            }
            return true;
        }
    }*/
    return false;
}

/*bool distributor::posCheck(MaceInt &i) {
    if (mpz_cmp_ui(i.entry.get_mpz_t(),0)<0) {
        validC->setErr(INTNEG,i.print().toUtf8().constData());
        return false;
    }
    return true;
}*/

/*bool distributor::bndCheck(MaceInt &i) {
    if (mpz_cmp_ui(i.entry.get_mpz_t(),4294967295)>0) {
        validC->setErr(INTTOLARGE,i.print().toUtf8().constData());
        return false;
    }
    return true;
}*/

/*bool distributor::siBndCheck(MaceInt &i) {
    if (mpz_cmp_si(i.entry.get_mpz_t(),2147483648)>0 || mpz_cmp_si(i.entry.get_mpz_t(),-2147483647)<0) {
        validC->setErr(SINTTOLARGE,i.print().toUtf8().constData());
        return false;
    }
    return true;
}

void distributor::getInt   (MVar &var, unsigned int &i) {
    MaceInt mi;
    if (var.getInt(&mi)) {
        clInt(mi,i);
    }
    else validC->setErr(NOTINT);
}*/

void distributor::getDouble(MVar &var, double &d) {
    numReal nr;

    if (var.getNumReal(&nr)) {
        d=nr.get();
    }
    else validC->setErr(NOTREAL);
}

/*void distributor::clInt(MaceInt &mi, unsigned int &ui) {
    if (posCheck(mi) && bndCheck(mi)) ui = mi.toInt();
    else ui = 0;
}

void distributor::clSInt(MaceInt &mi, int &si) {
    if (siBndCheck(mi)) si = mi.toSInt();
    else si = 0;
}*/
