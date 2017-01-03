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

#include "math.h"
#include "mvar.h"

//static const algCplx algOne(1,0);

//static routines for MVar

template <class T>
static void powTemp(T *res, T *a, unsigned int i)
{
    if (i > 0) {
        *res = *a;
        for (unsigned int j = 1; j < i; j++) {
            *res = (*res) * (*a);
        }
    }
}

static type getMaxtype(MVar *a, MVar *b){
    type ta = a->getType();
    type tb = b->getType();

    if (ta % tb == 0) return ta;
    if (tb % ta == 0) return tb;
    int h = ta * tb;
    if (h % ALGCPLX == 0 && h % REST == 0) return ERROR;
    if (h > NUMCPLX) return NUMPOLY;
    return NUMCPLX;
}

template <class T>
static bool getOp(T *res, T *a, T *b, char op) {
    bool resb = true;
    try {
      switch (op) {
        case '+': *res = (*a) + (*b); break;
        case '-': *res = (*a) - (*b); break;
        case '*': *res = (*a) * (*b); break;
        case '/':
            if (b->isZero()) {
                resb = false;
            }
            else *res = (*a) / (*b);
        break;
      }
    }
    catch ( ... ) {
        resb = false;
    }
    return resb;
}

/*template <class T>
static void getLogOp(MaceInt *res, T *a, T *b, char op) {
    bool rval = false;
    switch (op) {
        case '>': rval = (*a >  *b);  break;
        case '<': rval = (*a <  *b);  break;
        case 'e': rval = (*a == *b); break;
        case 'n': rval = (*a != *b); break;
        case 's': rval = (*a <= *b); break;
        case 'b': rval = (*a >= *b); break;
    }
    if (rval) *res = res->translate(1);
    else      *res = res->translate(0);
}*/

//definition MVar

MVar::MVar()
{
    obj = new numReal(0);
}

MVar::~MVar()
{
    delete obj;
}

type MVar::getType() const {
    //algCplx *ac;

    //if (dynamic_cast<MaceInt*>(obj)!=0)  return INT;
    /*if ((ac = dynamic_cast<algCplx*>(obj))!=0) {
        if (ac->isReal()) return ALGREAL;
        else            return ALGCPLX;
    }
    if (dynamic_cast<algPoly*>(obj)!=0)  return ALGPOLY;*/
    if (dynamic_cast<numReal*>(obj)!=0)  return NUMREAL;
    if (dynamic_cast<numCplx*>(obj)!=0)  return NUMCPLX;
    if (dynamic_cast<numPoly*>(obj)!=0)  return NUMPOLY;
    if (dynamic_cast<DistDat*>(obj)!=0)  return DISTDAT;
    //if (dynamic_cast<MaceRest*>(obj)!=0) return REST;
    //if (dynamic_cast<restPoly*>(obj)!=0) return RESTPOLY;
    if (dynamic_cast<Function*>(obj)!=0) return FUNCTION;
    if (dynamic_cast<MaceString*>(obj)!=0) return STRING;
    //if (dynamic_cast<algMatrix*>(obj)!=0) return ALGMATRIX;
    //if (dynamic_cast<restMatrix*>(obj)!=0) return RESTMATRIX;
    return ERROR;
}

// getter------------------------------------------------

/*bool MVar::getInt(MaceInt *mi) const {
    MaceInt *help = 0;
    help = dynamic_cast<MaceInt*>(obj);
    if (help != 0) *mi = *help;
    return help!=0;
}

bool MVar::getAlgCplx(algCplx *az) const {
    algCplx *help = 0;
    MaceInt mi;

    if (getInt(&mi)) {

        az->assign(mi);
        return true;
    }
    else if ((help = dynamic_cast<algCplx*>(obj)) != 0) {
        *az = *help;
        return true;
    }
    return false;
}

bool MVar::getAlgPoly(algPoly *ap) const {
    algPoly *help;
    algCplx ac;
    if (getAlgCplx(&ac)) {
        ap->mons.clear();
        ap->mons.push_back(ac);
        return true;
    }
    else if ((help = dynamic_cast<algPoly*>(obj)) != 0) {
        *ap = *help;
        return true;
    }
    return false;

}*/

bool MVar::getNumReal(numReal *nr) const {
    numReal *help;
    /*algCplx ac;
    if (getAlgCplx(&ac)) {
        if (ac.isReal()) {
            nr->set(mpq_get_d(ac.getReal().get_mpq_t()));
            return true;
        }
    }*/
    if ((help = dynamic_cast<numReal*>(obj)) != 0) {
        *nr = *help;
        return true;
    }
    return false;
}

bool MVar::getNumCplx(numCplx *nz) const {
    numCplx *help;
    numReal nr;
    //algCplx ac;
    bool found = true;

    if (getNumReal(&nr)) {
        nz->set(nr.get(),0.0);
        return true;
    }
    /*else if (getAlgCplx(&ac)) {
        *nz = ac.toNumCplx();
        return true;
    }*/
    else if ((help = dynamic_cast<numCplx*>(obj)) != 0) {
        *nz = *help;
        return true;
    }
    else found = false;

    return found;
}

bool MVar::getNumPoly(numPoly *np) const {
    //algPoly ap;
    numPoly *help;
    numCplx nz;
    bool found = true;

    if (getNumCplx(&nz)) {
        np->mons.clear();
        np->mons.push_back(nz);
        return true;
    }
    /*else if (getAlgPoly(&ap)) {
        *np = ap.toNumPoly();
        return true;
    }*/
    else if ((help = dynamic_cast<numPoly*>(obj)) != 0) {
        *np = *help;
    }
    else found = false;

    return found;
}

bool MVar::getDistDat(DistDat *dat) const {
    DistDat *help=0;
    if ((help = dynamic_cast<DistDat*>(obj)) != 0)
        *dat = *help;
    return help!=0;
}

bool MVar::getFunction(Function *head) const {
    Function *help;
    numPoly np;

    if (getNumPoly(&np)) {
        *head = head->translate(np);
        return true;
    }
    else if ((help = dynamic_cast<Function*>(obj)) != 0) {
        *head = *help;
    }
    return help!=0;
}

/*bool MVar::getRest(MaceRest *mr) const {
    MaceRest *help;
    if ((help = dynamic_cast<MaceRest*>(obj)) != 0)
        *mr = *help;
    return help!=0;
}

bool MVar::getRestPoly(restPoly *rp) const {
    restPoly *help;
    MaceRest mr;
    bool found = true;

    if (getRest(&mr)) {
        rp->set(mr);
    }
    else if ((help = dynamic_cast<restPoly*>(obj)) != 0)
        *rp = *help;
    else found = false;
    return found;
}*/

bool MVar::getString(MaceString *str) const {
    MaceString *help;
    if ((help = dynamic_cast<MaceString*>(obj)) != 0) {
        *str = *help;
        return true;
    }
    return false;
}

/*bool MVar::getAlgMatrix(algMatrix *am) const {
    algMatrix *help;
    if ((help = dynamic_cast<algMatrix*>(obj)) != 0) {
        *am = *help;
        return true;
    }
    return false;
}

bool MVar::getRestMatrix(restMatrix *rm) const {
    restMatrix *help;
    if ((help = dynamic_cast<restMatrix*>(obj)) != 0) {
        *rm = *help;
        return true;
    }
    return false;
}*/

// setter-----------------------------------------------

/*void MVar::setInt(MaceInt &mi) {
    delete obj;
    obj = 0;
    obj = new MaceInt(mi);
}

void MVar::setAlgCplx(algCplx &az) {
    MaceInt mi;
    if (az.putDown(mi)) {
        setInt(mi);
    }
    else {
        delete obj;
        obj = 0;
        obj = new algCplx(az);
    }
}

void MVar::setAlgPoly(algPoly &ap) {
    algCplx az;
    if (ap.putDown(az)) {
        setAlgCplx(az);
    }
    else {
        delete obj;
        obj = 0;
        obj = new algPoly(ap);
    }
}*/

void MVar::setNumReal(numReal &nr) {
    delete obj;
    obj = 0;
    obj = new numReal(nr);
}

void MVar::setNumCplx(numCplx &nz) {
    numReal nr;
    if (nz.putDown(nr)) {
        setNumReal(nr);
    }
    else {
        delete obj;
        obj = 0;
        obj = new numCplx(nz);
    }
}

void MVar::setNumPoly(numPoly &np) {
    numCplx nz;
    if (np.putDown(nz)) {
        setNumCplx(nz);
    }
    else {
        delete obj;
        obj = 0;
        obj = new numPoly(np);
    }
}

void MVar::setDistDat(DistDat &dat) {
    delete obj;
    obj = 0;
    obj = new DistDat(dat);
}

void MVar::setFunction(Function &func) {
    delete obj;
    obj = 0;
    obj = new Function(func);
}

/*void MVar::setRest(MaceRest &mr) {
    delete obj;
    obj = 0;
    obj = new MaceRest(mr);
}

void MVar::setRestPoly(restPoly &rp) {
    MaceRest mr;
    if (rp.putDown(mr)) {
        setRest(mr);
    }
    else {
        delete obj;
        obj = 0;
        obj = new restPoly(rp);
    }
}*/

void MVar::setString(MaceString &str) {
    delete obj;
    obj = 0;
    obj = new MaceString(str);
}

/*void MVar::setAlgMatrix(algMatrix &am) {
    delete obj;
    obj = 0;
    obj = new algMatrix(am);
}

void MVar::setRestMatrix(restMatrix &rm) {
    delete obj;
    obj = 0;
    obj = new restMatrix(rm);
}*/

void MVar::copy(const MVar &v) {
    DistDat  vdd;
    numPoly  vpn;
    numCplx  vzn;
    numReal  vd;
    /*algPoly  vp;
    algCplx  vz;
    restPoly rp;
    MaceRest vr;
    MaceInt  vi;*/
    Function fu;
    MaceString str;
    //algMatrix am;
    //restMatrix rm;

    type t = v.getType();
    if /*(t == INT) {
        v.getInt(&vi); this->setInt(vi);
    }
    else if (ALGREAL == t || ALGCPLX == t) {
        v.getAlgCplx(&vz); this->setAlgCplx(vz);
    }
    else if*/ (NUMREAL == t) {
        v.getNumReal(&vd); this->setNumReal(vd);
    }
    /*else if (REST == t){
        v.getRest(&vr); this->setRest(vr);
    }
    else if (RESTPOLY == t){
        v.getRestPoly(&rp); this->setRestPoly(rp);
    }
    else if (ALGPOLY == t) {
        v.getAlgPoly(&vp); this->setAlgPoly(vp);
    }*/
    else if (NUMCPLX == t) {
        v.getNumCplx(&vzn); this->setNumCplx(vzn);
    }
    else if (NUMPOLY == t) {
        v.getNumPoly(&vpn); this->setNumPoly(vpn);
    }
    else if (DISTDAT == t) {
        v.getDistDat(&vdd); this->setDistDat(vdd);
    }
    else if (FUNCTION == t) {
        v.getFunction(&fu); this->setFunction(fu);
    }
    else if (STRING == t) {
        v.getString(&str); this->setString(str);
    }
    /*else if (ALGMATRIX == t) {
        v.getAlgMatrix(&am); this->setAlgMatrix(am);
    }
    else if (RESTMATRIX == t) {
        v.getRestMatrix(&rm); this->setRestMatrix(rm);
    }*/
}

/*void MVar::forceInt(MaceRest &mr) {
    MaceInt i;
    mr.normalize();
    mpz_set(i.entry.get_mpz_t(),mr.val.get_mpz_t());
    setInt(i);
}*/

// arithmetic methods---------------------------------------
bool MVar::power(MVar *res, unsigned int mi) {
    bool valid = true;

    type curType = getType();
    if /*(curType == INT) {
        MaceInt resInt, i;
        getInt(&i);
        mpz_pow_ui(resInt.entry.get_mpz_t(),i.entry.get_mpz_t(),mi);
        res->setInt(resInt);
    }
    else if (curType == ALGCPLX || curType == ALGREAL) {
        algCplx resCplx(1,0), z;
        getAlgCplx(&z);
        powTemp(&resCplx,&z,mi);
        res->setAlgCplx(resCplx);
    }
    else if (curType == ALGPOLY) {
        algCplx resCplx(1,0);
        algPoly resPoly(resCplx), p;
        getAlgPoly(&p);
        powTemp(&resPoly,&p,mi);
        res->setAlgPoly(resPoly);
    }
    else if*/ (curType == NUMREAL) {
        numReal nRe, d;
        getNumReal(&d);
        nRe.set(pow(d.get(),(double) mi));
        res->setNumReal(nRe);
    }
    else if (curType == NUMCPLX) {
        numCplx resNC, a, b, zn;
        getNumCplx(&zn);
        b.set((double) mi,0.0);
        resNC.val = pow(zn.val,b.val);
        res->setNumCplx(resNC);
    }
    else if (curType == NUMPOLY) {
        numCplx resCplx(1,0);
        numPoly resPoly(resCplx), pn;
        getNumPoly(&pn);
        powTemp(&resPoly,&pn,mi);
        res->setNumPoly(resPoly);
    }
    /*else if (curType == REST) {
        MaceRest r;
        getRest(&r);
        MaceRest resr(1,r.charac());
        powTemp(&resr,&r,mi);
        res->setRest(resr);
    }
    else if (curType == RESTPOLY) {
        restPoly pr;
        getRestPoly(&pr);
        MaceRest resr(1,pr.charac());
        restPoly resPoly(resr);
        powTemp(&resPoly,&pr,mi);
        res->setRestPoly(resPoly);
    }
    else if (curType == ALGMATRIX) {
        algMatrix am, resm;
        getAlgMatrix(&am);
        valid = valid && am.lines == am.columns;
        if (valid) powTemp(&resm,&am,mi);
        if (valid) res->setAlgMatrix(resm);
    }
    else if (curType == RESTMATRIX) {
        restMatrix am, resm;
        getRestMatrix(&am);
        valid = valid && am.lines == am.columns;
        if (valid) powTemp(&resm,&am,mi);
        if (valid) res->setRestMatrix(resm);
    }*/
    return valid;
}

// evals----------------------------------------------------

void MVar::evalI(bool cFunction) {
    /*algCplx I(0,1);
    if (cFunction) {
        Function head;
        std::complex<double> IN;
        IN.real() = 0.0;
        IN.imag() = 1.0;
        head.setValue(IN);
        delete obj;
        obj = 0;
        obj = new Function(head);
    }
    else setAlgCplx(I);*/
}

void MVar::evalX(/*MaceInt charac,*/ bool cFunction) {
    //if (charac.isZero()) {
        if (cFunction) {
            Function head;
            head.setX();
            if (obj != 0) {
                delete obj;
                obj = 0;
            }
            obj = new Function(head);
        }
        /*else {
            algPoly hp(algOne); hp.shift(1);
            setAlgPoly(hp);
        }
    }
    else {
        MaceRest mr(1,charac); restPoly hp(mr);
        hp.shift(1);
        setRestPoly(hp);
    }*/
}

void MVar::evalStr(std::string val, unsigned int dotPos, /*MaceInt charac,*/ bool cFunction) {
    if (obj != 0) delete obj;
    obj = 0;
    obj = new numReal(::atof(val.c_str()));
    /*char *str = new char[val.size()+1];
    strcpy(str, val.c_str());
    if (dotPos == 0) {
        //if (charac.isZero()) {
            MaceInt i;
            mpz_set_str(i.entry.get_mpz_t(),str,10);
            setInt(i);
            if (cFunction) {
                numCplx z;
                getNumCplx(&z);
                delete obj;
                obj = 0;
                Function func(z.val);
                obj = new Function(func);
            }
        }
        else {
            MaceRest r;
            mpz_set(r.mod.get_mpz_t(),charac.entry.get_mpz_t());
            mpz_set_str(r.val.get_mpz_t(),str,10);
            r.normalize();
            setRest(r);
        }
    }
    else {
        algCplx z;
        z.eval(val,dotPos);
        delete obj;
        obj = 0;
        if (cFunction) {
            Function func(z.toNumCplx().val);
            obj = new Function(func);
        }
        else obj = new algCplx(z);
    }
    delete[] str;*/
}

//extern routines------------------------------------------

bool operate(MVar *res, MVar *a, MVar *b, char op) {
    bool resb = false;

    try {
    type maxType = getMaxtype(a,b);
    if (op == '^') {
        resb = false;
        Function f,g,h;
        numCplx  ac, bc;
        numReal  ar, br;
        //MaceInt  bInt;

        if (maxType == FUNCTION) {
            resb = true;
            Function f, g, resf;
            if (a->getFunction(&f) && b->getFunction(&g)) {
                setOp(&resf, f, g, op);
                res->setFunction(resf);
            }
        }
        /*else if (b->getInt(&bInt)) {
            resb = true;
            if (mpz_cmp_ui(bInt.entry.get_mpz_t(),4294967295)<=0 && mpz_cmp_ui(bInt.entry.get_mpz_t(),0)>=0) {
                resb = resb && a->power(res,bInt.toInt());
            }
            else if (a->getType() == ALGMATRIX) {
                algMatrix am, m;
                a->getAlgMatrix(&am);
                int i;
                i = bInt.toSInt();
                i = -i;
                resb = resb && am.columns == am.lines;
                m = am;
                if (resb) resb = m.rank() == am.columns;
                if (resb) m.invert(am);
                a->setAlgMatrix(am);
                resb = resb && a->power(res,i);
            }
            else if (a->getType() == RESTMATRIX) {
                restMatrix am, m;
                a->getRestMatrix(&am);
                int i;
                i = bInt.toSInt();
                i = -i;
                resb = resb && am.columns == am.lines;
                m = am;
                if (resb) resb = m.rank() == am.columns;
                if (resb) m.invert(am);
                a->setRestMatrix(am);
                resb = resb && a->power(res,i);
            }
            else if (a->getNumReal(&ar) && b->getNumReal(&br)) {
                double val = pow((-1.0)*ar.get(),br.get());
                if (bInt.toSInt()%2) val = (-1.0)*val;
                numReal nr;
                nr.set(val);
                res->setNumReal(nr);
            }
            else if (a->getFunction(&f) && b->getFunction(&g)) {
                setOp(&h, f, g, op);
                res->setFunction(h);
            }
            else resb = false;
        }*/
        else if (a->getNumReal(&ar) && b->getNumReal(&br)) {
            resb = true;
            numReal resr;
            double val = pow(ar.get(),br.get());
            resr.set(val);
            res->setNumReal(resr);
        }
        else if (a->getNumCplx(&ac) && b->getNumCplx(&bc)) {
            resb = true;
            numCplx resC;
            resC.val = pow(ac.val,bc.val);
            res->setNumCplx(resC);
        }
        else if (a->getFunction(&f) && b->getFunction(&g)) {
            resb = true;
            setOp(&h, f, g, op);
            res->setFunction(h);
        }
    }
    /*else if (op == 'v') {
        if (b->getType() == FUNCTION) {
            Function f, g, r;
            a->getFunction(&f);
            b->getFunction(&g);
            composite(&r,&f,&g);
            res->setFunction(r);
            resb = true;
        }
        else if (b->getType()%ALGPOLY == 0) return operate(res,a,b,'*');
        else {
            Function f; numCplx z,w;
            if (a->getFunction(&f) && b->getNumCplx(&z)) {
                w.val = f.eval(z.val,resb);
                if (resb) res->setNumCplx(w);
            }
        }
    }*/
    else {
        if /*(maxType == INT) {
            if (op == '/') {
                algCplx az, bz, resz;
                a->getAlgCplx(&az); b->getAlgCplx(&bz);
                resb = getOp(&resz, &az, &bz, op);
                res->setAlgCplx(resz);
            } else {
                MaceInt aInt, bInt, resInt;
                if (a->getInt(&aInt) && b->getInt(&bInt)) {
                    resb = getOp(&resInt, &aInt, &bInt, op);
                    res->setInt(resInt);
                }
            }
        }
        else if (maxType == ALGCPLX || maxType == ALGREAL) {
            algCplx az, bz, resz;
            if (a->getAlgCplx(&az) && b->getAlgCplx(&bz)) {
                resb = getOp(&resz, &az, &bz, op);
                res->setAlgCplx(resz);
            }
        }
        else if (maxType == ALGPOLY) {
            algPoly ap, bp, resp;
            if (a->getAlgPoly(&ap) && b->getAlgPoly(&bp)) {
                resb = getOp(&resp, &ap, &bp, op);
                res->setAlgPoly(resp);
            }
        }
        else if */(maxType == NUMREAL) {
            numReal az, bz, resz;
            if (a->getNumReal(&az) && b->getNumReal(&bz)) {
                resb = getOp(&resz, &az, &bz, op);
                res->setNumReal(resz);
            }
        }
        else if (maxType == NUMCPLX) {
            numCplx az, bz, resz;
            if (a->getNumCplx(&az) && b->getNumCplx(&bz)) {
                resb = getOp(&resz, &az, &bz, op);
                res->setNumCplx(resz);
            }
        }
        else if (maxType == NUMPOLY) {
            numPoly ap, bp, resp;
            if (a->getNumPoly(&ap) && b->getNumPoly(&bp)) {
                resb = getOp(&resp, &ap, &bp, op);
                res->setNumPoly(resp);
            }
        }
        /*else if (maxType == REST) {
            MaceRest ar, br, resr;
            if (a->getRest(&ar) && b->getRest(&br)) {
                if (mpz_cmp(ar.mod.get_mpz_t(),br.mod.get_mpz_t()) == 0) {
                    resb = getOp(&resr, &ar, &br, op);
                    res->setRest(resr);
                }
            }
        }
        else if (maxType == ALGMATRIX) {
            algMatrix am, bm, resm;
            if (a->getAlgMatrix(&am) && b->getAlgMatrix(&bm)) {
                resb = (((op == '+' || op == '-') && am.lines == bm.lines && am.columns == bm.columns)
                                || am.columns == bm.lines);
                if (resb) resb = getOp(&resm, &am, &bm, op);
                if (resb) res->setAlgMatrix(resm);
            }
        }
        else if (maxType == RESTMATRIX) {
            restMatrix am, bm, resm;
            if (a->getRestMatrix(&am) && b->getRestMatrix(&bm)) {
                resb = (((op == '+' || op == '-') && am.lines == bm.lines && am.columns == bm.columns)
                                || am.columns == bm.lines);
                if (resb) resb = getOp(&resm, &am, &bm, op);
                if (resb) res->setRestMatrix(resm);
            }
        }*/
        else if (maxType == STRING && (op == '+' || op == '-')) {
            MaceString as, bs, ress;
            if (a->getString(&as) && b->getString(&bs)) {
                if (op == '+') ress = as + bs;
                else           ress = as - bs;
                res->setString(ress);
                resb = true;
            }
        }
        /*else if (maxType == RESTPOLY) {
            restPoly ap, bp, resp;
            if (a->getRestPoly(&ap) && b->getRestPoly(&bp)) {
                if (ap.charac() == bp.charac()) {
                    resb = getOp(&resp, &ap, &bp, op);
                    res->setRestPoly(resp);
                }
            }
        }*/
        else if (maxType == FUNCTION) {
            Function f, g, resf;
            if (a->getFunction(&f) && b->getFunction(&g)) {
                setOp(&resf, f, g, op);
                res->setFunction(resf);
            }
            resb = true;
        }
    }
    }
    catch (...) {
        resb = false;
    }

    return resb;
}


bool logOperate(MVar *res, MVar *a, MVar *b, char op) {
    type maxType = getMaxtype(a,b);
    bool valid = true;

    /*MaceInt resInt;
    if (maxType == INT) {
        MaceInt aInt, bInt;
        if (a->getInt(&aInt) && b->getInt(&bInt)) {
            getLogOp(&resInt, &aInt, &bInt, op);
        }
    }
    else if (maxType == ALGCPLX || maxType == ALGREAL) {
        algCplx az, bz;
        if (a->getAlgCplx(&az) && b->getAlgCplx(&bz)) {
            getLogOp(&resInt, &az, &bz, op);
        }
    }
    else if (maxType == ALGPOLY) {
        algPoly ap, bp;
        if (a->getAlgPoly(&ap) && b->getAlgPoly(&bp)) {
            getLogOp(&resInt, &ap, &bp, op);
        }
    }
    else if (maxType == NUMREAL) {
        numReal az, bz;
        if (a->getNumReal(&az) && b->getNumReal(&bz)) {
            getLogOp(&resInt, &az, &bz, op);
        }
    }
    else if (maxType == NUMCPLX) {
        numCplx az, bz;
        if (a->getNumCplx(&az) && b->getNumCplx(&bz)) {
            getLogOp(&resInt, &az, &bz, op);
        }
    }
    else if (maxType == NUMPOLY) {
        numPoly ap, bp;
        if (a->getNumPoly(&ap) && b->getNumPoly(&bp)) {
            getLogOp(&resInt, &ap, &bp, op);
        }
    }
    else if (maxType == REST) {
        MaceRest ar, br;
        if (a->getRest(&ar) && b->getRest(&br)) {
            if (mpz_cmp(ar.mod.get_mpz_t(),br.mod.get_mpz_t()) == 0)
                getLogOp(&resInt, &ar, &br, op);
            else valid = false;
        }
    }
    else if (maxType == RESTPOLY) {
        restPoly ap, bp;
        if (a->getRestPoly(&ap) && b->getRestPoly(&bp)) {
            if (ap.charac()==bp.charac())
                getLogOp(&resInt, &ap, &bp, op);
            else valid = false;
        }
    }
    else if (maxType == STRING) {
        MaceString as, bs;
        if (a->getString(&as) && b->getString(&bs)) {
            getLogOp(&resInt, &as, &bs, op);
        }
    }
    else if (maxType == FUNCTION) {
        Function f, g, resf;
        valid = true;
        if (a->getFunction(&f) && b->getFunction(&g)) {
            setOp(&resf, f, g, op);
            res->setFunction(resf);
        }
    }
    else valid = false;

    if (maxType != FUNCTION) res->setInt(resInt);*/

    return valid;
}

bool boolOperate(MVar *res, MVar *a, MVar *b, char op) {
    Function resf, f, g;
    /*MaceInt aInt, bInt, rInt;
    if (a->getInt(&aInt) && b->getInt(&bInt)) {
        if (op == 'x') {
            if ((aInt.isZero() && !bInt.isZero()) || (!aInt.isZero() && bInt.isZero()))
                rInt = rInt.translate(1);
            else
                rInt = rInt.translate(0);
        }
        if (op == 'o') {
            if (!aInt.isZero() || !bInt.isZero())
                rInt = rInt.translate(1);
            else
                rInt = rInt.translate(0);
        }
        if (op == 'p') {
            if (!aInt.isZero() || !bInt.isZero())
                rInt = rInt.translate(0);
            else
                rInt = rInt.translate(1);
        }
        if (op == 'a') {
            if (!aInt.isZero() && !bInt.isZero())
                rInt = rInt.translate(1);
            else
                rInt = rInt.translate(0);
        }
        res->setInt(rInt);
        return true;
    }
    else if (a->getFunction(&f) && b->getFunction(&g)) {
        setOp(&resf, f, g, op);
        res->setFunction(resf);
    }*/

    return false;
}

bool notOp(MVar *res, MVar *a) {
    /*MaceInt mi;

    if (a->getInt(&mi)) {
        if (mi.isZero()) mi = mi.translate(1);
        else             mi = mi.translate(0);
        res->setInt(mi);
        return true;
    }*/
    return false;
}

void minus(MVar *var/*, MaceInt charac*/) {
    MVar    help;

    /*if (charac.isZero()) {
        if (var->getType() == FUNCTION) {
            Function f, g, h;
            var->getFunction(&f);
            setFunc(f,g,h,"-",1);
            var->setFunction(f);
        }
        else {
            MaceInt mi(-1);
            help.setInt(mi);
            operate(var,&help,var,'*');
        }
    }
    else {
        MaceRest mi(charac);
        help.setRest(mi);
        operate(var,&help,var,'-');
    }*/

}
