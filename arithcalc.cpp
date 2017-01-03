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

#include "arithcalc.h"

/*arithCalc::twoPolyFctn arithCalc::find2polyFctn(std::string *str){
    curPFctn = NO;

    if (*str == "mod") curPFctn = MOD;
    else if (*str == "gcd") curPFctn = GCD;
    else if (*str == "lcm") curPFctn = LCM;

    return curPFctn;
}

arithCalc::intFctn arithCalc::find2intFctn(std::string *str){
    iFctn = NOI;

    if (*str == "chs") iFctn = BINO;
    else if (*str == "mset") iFctn = MULTI;
    else if (*str == "jac") iFctn = JACO;
    else if (*str == "legSym") iFctn = LEGS;

    return iFctn;
}

arithCalc::intFctn arithCalc::findIntFctn(const std::string *str){
    iFctn = NOI;

    if (*str == "fac") iFctn = FAC;
    else if (*str == "facSum") iFctn = FACSUM;
    else if (*str == "fib") iFctn = FIBO;
    else if (*str == "prime") iFctn = PRIMS;
    else if (*str  == "lambda") iFctn = LAMBDA;
    else if (*str == "luc") iFctn = LUC;
    else if (*str == "nextPrime") iFctn = NEXT;
    else if (*str == "numFac") iFctn = NUMFAC;
    else if (*str == "sumFac") iFctn = FACSUM;
    else if (*str == "pi") iFctn = PIF;
    else if (*str == "phi") iFctn = PHI;
    else if (*str == "psi") iFctn = PSI;
    else if (*str == "smPrm") iFctn = SMPRIM;

    return iFctn;
}

void arithCalc::twoRPFctn(restPoly *a, restPoly *b, twoPolyFctn pFctn){
    if (pFctn == MOD) {
        if (b->degree()>=0) *a = *a%*b;
    }
    else if (pFctn == GCD) pgcd(*a,*a,*b);
    else if (pFctn == LCM) plcm(*a,*a,*b);
}

void arithCalc::twoPFctn(algPoly *res, algPoly &a, algPoly &b, twoPolyFctn pFctn){
    if (pFctn == MOD) {
        if (b.degree()>=0) *res = a%b; else *res = a;
    }
    else if (pFctn == GCD) {
        pgcd(*res,a,b);
    }
    else if (pFctn == LCM) plcm(*res,a,b);
}

void arithCalc::twoIFctn(MaceInt *a, MaceInt *b, twoPolyFctn pFctn){
    if (pFctn == MOD) {
        if (mpz_cmp_si(b->entry.get_mpz_t(),0) != 0) {
            *a = *a%*b;
            if (mpz_cmp_si(a->entry.get_mpz_t(),0) < 0) {
                if (mpz_cmp_si(b->entry.get_mpz_t(),0) < 0)
                    mpz_sub(a->entry.get_mpz_t(),a->entry.get_mpz_t(),b->entry.get_mpz_t());
                else mpz_add(a->entry.get_mpz_t(),a->entry.get_mpz_t(),b->entry.get_mpz_t());
            }
        }
    }
    else if (pFctn == GCD) {
        mpz_gcd(a->entry.get_mpz_t(),a->entry.get_mpz_t(),b->entry.get_mpz_t());
    }
    else if (pFctn == LCM) {
        mpz_lcm(a->entry.get_mpz_t(),a->entry.get_mpz_t(),b->entry.get_mpz_t());
    }
}

bool arithCalc::twoIntFctn(MaceInt *a, MaceInt *b, intFctn iFunc){
        bool valid = true;
        if (iFunc == BINO)
            if ((mpz_cmp_ui(b->entry.get_mpz_t(),4294967294)<=0) && (mpz_cmp_ui(b->entry.get_mpz_t(),0)>=0)
                    && (mpz_cmp_ui(a->entry.get_mpz_t(),0)>=0))
            mpz_bin_ui(a->entry.get_mpz_t(),a->entry.get_mpz_t(),b->toInt());
            else valid = false;
        else if (iFunc == MULTI){
            mpz_t help;
            mpz_init(help);
            mpz_set_si(help,-1);
            mpz_add(help,help,a->entry.get_mpz_t());
            mpz_add(help,help,b->entry.get_mpz_t());
            if ((mpz_cmp_ui(b->entry.get_mpz_t(),4294967295)<0) && (mpz_cmp_ui(b->entry.get_mpz_t(),0)>=0)
                    && (mpz_cmp_ui(a->entry.get_mpz_t(),0)>=0) )
            mpz_bin_ui(a->entry.get_mpz_t(),help,b->toInt());
            else valid = false;
            mpz_clear(help);
        }
        else if (iFunc  == JACO){
            int help = mpz_jacobi(a->entry.get_mpz_t(),b->entry.get_mpz_t());
            mpz_set_si(a->entry.get_mpz_t(),help);
        }
        else if (iFunc  == LEGS){
            int help = mpz_legendre(a->entry.get_mpz_t(),b->entry.get_mpz_t());
            mpz_set_si(a->entry.get_mpz_t(),help);
        }
        return valid;
}

void arithCalc::intFunc(MaceInt *a, unsigned int help, intFctn iFunc){
        if (iFunc  == FAC) mpz_fac_ui(a->entry.get_mpz_t(),help);
        else if (iFunc  == FACSUM) *a=facsum(*a);
        else if (iFunc  == FIBO) mpz_fib_ui(a->entry.get_mpz_t(),help);
        else if (iFunc  == LAMBDA) {
            int i = lambda(*a);
            mpz_set_si(a->entry.get_mpz_t(),i);
        }
        else if (iFunc  == NUMFAC) *a=facnum(*a);
        else if (iFunc  == PHI) *a = phi(*a);
        else if (iFunc  == PIF) *a = pi(*a);
        else if (iFunc  == PRIMS) {
            int help = mpz_probab_prime_p(a->entry.get_mpz_t(),25);
            mpz_set_si(a->entry.get_mpz_t(),help);
        }
        else if (iFunc  == LUC) {
            unsigned int help = mpz_get_ui(a->entry.get_mpz_t());
            mpz_lucnum_ui(a->entry.get_mpz_t(),help);
        }
        else if (iFunc  == PSI) *a = psi(*a);
        else if (iFunc  == NEXT) mpz_nextprime(a->entry.get_mpz_t(),a->entry.get_mpz_t());
        else if (iFunc  == SMPRIM) *a = prime(*a);
}

MaceInt arithCalc::pi(MaceInt i){
    MaceInt primes(2), count(0);

    if (i<two){return zero;}
    else{
        do {
            count = count + one;
            mpz_nextprime(primes.entry.get_mpz_t(),primes.entry.get_mpz_t());
        } while (i >= primes);
    }

    return count;
}

MaceInt arithCalc::prime (MaceInt i){
    MaceInt res(i), j(1);
    const MaceInt zero(0);

    while (i >= j* j ){
        mpz_nextprime(j.entry.get_mpz_t(),j.entry.get_mpz_t());
        if (i%j == zero){
            res = j;
            break;
        }
    }

    return res;
}

QString arithCalc::factors(MaceInt j){
    QString res="";
    MaceInt primo, help;
    if (mpz_cmp_ui(j.entry.get_mpz_t(),0)==0) res = "0";
    else if (mpz_cmp_ui(j.entry.get_mpz_t(),1)==0) res = "1";
    else {
        help = help.translate(1);

        while (j.larger(1)) {
            mpz_nextprime(help.entry.get_mpz_t(),help.entry.get_mpz_t());
            do {
                primo = j%help;
                if (!primo.larger(0)) {
                    j = j/help;
                    res = res.append(help.print());
                    res = res.append(", ");
                }
            } while(!primo.larger(0));
        }
    }
    return res;
}

QString arithCalc::factors(numPoly p){
    return p.factors();
}

QString arithCalc::factors(restPoly p){
    return p.factors(one);
}

MaceInt arithCalc::facnum(MaceInt i) {
    const MaceInt one(1);
    const MaceInt two(2);
    MaceInt help, primo;
    MaceInt fac(1);
    MaceInt res(1);
    MaceInt mem(1);
    if (i < two){return one;}
    else {
        while (i.larger(1)) {
            mpz_nextprime(help.entry.get_mpz_t(),help.entry.get_mpz_t());
            do {
                primo = i%help;
                if (!primo.larger(0)) {
                    i = i/help;
                    if (mem != help){
                        res = fac*res;
                        fac = one;
                    }
                    fac = fac + one;
                    mem = help;
                }
            } while(!primo.larger(0));
        }

        res = fac*res;

        return res;
    }
}

MaceInt arithCalc::facsum(MaceInt i){
    unsigned int m = mpz_get_ui(i.entry.get_mpz_t());
    unsigned int helpI, primo, blub = 1, mem = 1, res=1;
    MaceInt fac;
    MaceInt help(1);
    if (m < 2){return i;}
    else {
        while (m>1) {
            mpz_nextprime(help.entry.get_mpz_t(),help.entry.get_mpz_t());
            helpI = mpz_get_ui(help.entry.get_mpz_t());
            do {
                primo =m%helpI;
                if (primo == 0) {
                    m = m/helpI;

                    blub*=helpI;
                    mem = mem + blub;
                }
            } while(primo==0);
            res = res*mem;
            blub = 1;
            mem = 1;
        }
        mpz_set_ui(fac.entry.get_mpz_t(),res);
        return fac;
    }
}

int arithCalc::lambda (MaceInt i){
    MaceInt help, primo;
    int res=1;
    if (mpz_cmp_ui(i.entry.get_mpz_t(),0)==0) res = 0;
    else {
        help = help.translate(1);
        while (i.larger(1)) {
            mpz_nextprime(help.entry.get_mpz_t(),help.entry.get_mpz_t());
            do {
                primo = i%help;
                if (!primo.larger(0)) {
                    i = i/help;
                    res = -res;
                }
            } while(!primo.larger(0));
        }
    }
    return res;
}

MaceInt arithCalc::phi(MaceInt i){
    MaceInt help(1), primo, fac(0), res(1), help2;
    if (mpz_cmp_ui(i.entry.get_mpz_t(),0)==0) res = zero;
    if (mpz_cmp_ui(i.entry.get_mpz_t(),1)==0) res = one;
    else {
        while (i.larger(1)) {
            mpz_nextprime(help.entry.get_mpz_t(),help.entry.get_mpz_t());
            do {
                primo = i%help;
                if (!primo.larger(0)) {
                    i = i/help;
                    if (fac !=help) {
                        fac = help;
                        help2 = res;
                        res = help2*(fac-one);
                    }
                    else {help2 = res; res = help2*fac;}
                }
            } while(!primo.larger(0));
        }
    }
    return res;
}

MaceInt arithCalc::psi(MaceInt i){
    MaceInt help(1), primo, fac, res(1);
    if (mpz_cmp_ui(i.entry.get_mpz_t(),0)==0) res = zero;
    if (mpz_cmp_ui(i.entry.get_mpz_t(),1)==0) res = one;
    else {
        while (i.larger(1)) {
            mpz_nextprime(help.entry.get_mpz_t(),help.entry.get_mpz_t());
            do {
                primo = i%help;
                if (!primo.larger(0)) {
                    i = i/help;
                    if (fac !=help) {fac = help; res = res*(fac+one);}
                    else res = res*fac;
                }
            } while(!primo.larger(0));
        }
    }
    return res;
}

template <class T>
T arithCalc::max(T a, T b){
  if(a<b){return b;}
  else{return a;}
}

template <class T>
T arithCalc::min(T a, T b){
  if(a<b){return a;}
  else{return b;}
}

template <class T>
void arithCalc::pgcd(T &res, const T &a, const T &b) {
    T hilf, p;
    res = a;
    hilf = b;
    if (res < hilf) {
        std::swap(res,hilf);
    }

    while(hilf.degree() >= 0){
      p = res%hilf;
      res = hilf;
      hilf = p;
    }
}

template <class T>
void arithCalc::plcm(T &res, const T &a, const T &b) {
    T hilf;

    pgcd(hilf,a,b);
    res = a*b/hilf;
}

template <class T>
void arithCalc::exEu(T &res, const T &a, T &b, T &s, T &t) {
    T q, r, s2, t2, zero, c, d;
    c = a; d = b;
    if (c < d) std::swap(c,d);
    if (!(d > zero)){
        res = c;
        s.set(1);
        t.set(0);
    }
    else{
        r=c%d;
        q=c/d;
        exEu(res, b, r, s2, t2);
        s = t2;
        q = q*t2;
        t=s2-q;
    }
}

QString arithCalc::intExEu(MaceInt a, MaceInt b, MaceInt characteristic){
    QString res;
    MaceInt g, s, t;

    extEuk(g,s,t,a,b);

    res = res.append(g.print());
    res = res.append(" = ");
    res = res.append(s.print());
    res = res.append(" * ");
    res = res.append(a.print());
    res = res.append(" + ");
    res = res.append(t.print());
    res = res.append(" * ");
    res = res.append(b.print());

    return res;
}

template <class T> QString arithCalc::ExEu(T a, T b, MaceInt characteristic){
    QString res;
    T rp, s, t;

    exEu(rp,a,b,s,t);
    res = res.append(rp.print());
    res = res.append(" = ");
    res = res.append(s.print());
    res = res.append(" * ");
    res = res.append(a.print());
    res = res.append(" + ");
    res = res.append(t.print());
    res = res.append(" * ");
    res = res.append(b.print());

    return res;
}

QString arithCalc::iExEu(algPoly a, algPoly b, MaceInt characteristic){
    return ExEu(a,b,characteristic);
}

QString arithCalc::iExEu(restPoly a, restPoly b, MaceInt characteristic){
    return ExEu(a,b,characteristic);
}

int arithCalc::smallPrimeTest(MaceInt n){
    return mpz_probab_prime_p(n.entry.get_mpz_t(),25);
}*/
