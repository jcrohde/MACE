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

#include "math/variables/polynomial/restpoly.h"
#include "math/functiondistributors/arithcalc.h"


/*restPoly::restPoly()
{
    MaceRest z(2);
    mons.push_back(z);
}

restPoly::restPoly(int c)
{
    MaceInt charac;
    charac.translate(c);
    MaceRest z(charac);
    mons.push_back(z);
}

restPoly::restPoly(MaceInt charac)
{
    MaceRest z(charac);
    mons.push_back(z);
}


restPoly::restPoly(MaceRest d)
{
  mons.push_back(d);
}


void restPoly::expand(MaceRest d){
  mons.push_back(d);
}


int restPoly::degree(){
    if (mons.size()>1){return mons.size()-1;}
    else{
        restPoly tmp(*this);
        MaceInt charac = tmp.charac();
        MaceRest zero(charac);
        MaceRest help = *mons.begin();
        help.normalize();
        if (help==zero){return -1;}
        else {return 0;}
    }
}


QString restPoly::print(){
  int i=1;
  QString res, help;
  MaceRest d;
  *this = this->normalize();
  restPoly tmp(*this);

  if (tmp.degree() == -1){ res = "0";}
  else{
  std::list<MaceRest>::iterator iter = tmp.mons.begin();
  d = *iter;
  d.normalize();
  if (mpz_cmp_si(d.val.get_mpz_t(),0) != 0){
     res = d.print();
  }

  iter++;

  while(iter != tmp.mons.end()){
    if (mpz_cmp_si(d.val.get_mpz_t(),0) != 0){
        res.prepend("+");
    }
    d = *iter;

    if (mpz_cmp_si(d.val.get_mpz_t(),0) != 0){
        if (i == 1){res.prepend("x");}
        else{
          help = help.number(i);
          res.prepend(help);
          res.prepend("x^");
        }
        if(mpz_cmp_si(d.val.get_mpz_t(),1) != 0){
          help=d.print();
          res.prepend(help);
        }
      }


    iter++;
    i++;
  }
  }
  return res;
}

restPoly restPoly::mult(MaceRest d){
  std::list<MaceRest>::iterator ptr = mons.begin();
  restPoly res((*ptr)*d);

  ptr++;
  while(ptr != mons.end()){
    res.expand((*ptr)*d);
    ptr++;
  }
  return res;
}

void restPoly::set(MaceRest mr) {
    mons.clear();
    mons.push_back(mr);
}

void restPoly::set(int i) {
    MaceRest mr(i,charac());
    mons.clear();
    mons.push_back(mr);
}

void restPoly::shift(int i){
    MaceRest z(charac());

   if (i > 0){
     for (int d =1 ; d<=i;d++){
         mons.push_front(z);
     }
   }
}

bool restPoly::putDown(MaceRest &mr) {
    restPoly rp = normalize();
    if (rp.mons.size() == 1) {
        mr = *mons.begin();
        return true;
    }
    return false;
}

MaceRest restPoly::leader(){
    std::list<MaceRest>::iterator ptr = mons.end();
    ptr--;

    return *ptr;
}

MaceInt restPoly::charac(){
    std::list<MaceRest>::iterator ptr = mons.end();
    ptr--;
    MaceRest r = *ptr;
    MaceInt res;
    mpz_set(res.entry.get_mpz_t(),r.mod.get_mpz_t());
    return res;
}


void restPoly::rmLeader(){
  mons.pop_back();
}


restPoly restPoly::killZero(){
    restPoly tmp(*this);
    MaceInt i(1);
    MaceInt m = tmp.charac();
    std::list<MaceRest>::iterator iter = tmp.mons.begin();
    restPoly res(*iter);
    iter++;
    if (iter != tmp.mons.end()){

        while(iter !=tmp.mons.end()){
            i = i%m;
            if (i == 0){res.expand(*iter);}
            iter++;
            i++;
        }
    }
    return res;
}

static void rgcd(restPoly &res, const restPoly &a, const restPoly &b) {
        restPoly hilf, p;
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

restPoly restPoly::normalize(){
    restPoly tmp(*this);
    std::list<MaceRest>::iterator ptr = tmp.mons.end();
    ptr--;
    MaceRest help = *ptr;

    help.normalize();

    while((mpz_cmp_si(help.val.get_mpz_t(),0) == 0) && (tmp.degree() > 0)){
        tmp.mons.pop_back();
        ptr = tmp.mons.end();
        ptr--;
        help = *ptr;
        mpz_tdiv_r(help.val.get_mpz_t(),help.val.get_mpz_t(),help.mod.get_mpz_t());
    }

    return tmp;
}

restPoly restPoly::der(){
  MaceRest z(this->charac());

  std::list<MaceRest>::iterator ptr = mons.begin();
  ptr++;
  restPoly res(this->charac());

  if (ptr != mons.end()){
    restPoly help(*ptr);
    res=res+help;
    MaceRest i(2,this->charac());
    ptr++;
    while(ptr != mons.end()){
      res.expand((*ptr)*i);
      ptr++;
    }
  }
  res = res.normalize();
  return res;
}

QString restPoly::CanZas(int d, MaceInt k){//d degree, k times
    restPoly f(*this);
    MaceInt chara= f.charac();

    const restPoly zero(chara);
    QString res = "     ", hehe;

    MaceInt r, charac, facNum, ff;
    int count, kar;
    kar = k.toInt();
    bool more = true;

    r = f.degree()/d;

    MaceRest one(1,chara), mem, nihil(chara), minusOne(chara);
    minusOne = minusOne-one;

    restPoly h(one);
    h.shift(d);

    std::list<MaceRest>::iterator iter = h.mons.begin();
    std::list<MaceRest>::iterator eraser = h.mons.begin();
    count = 0;

    while (facNum< r && more){

        eraser = h.mons.begin();
        iter = h.mons.begin();
        //if one has found a divisor h, print h and divide f/h
        if (f%h == zero){
            hehe = h.print();
            for (int i=0; i < kar; i++){
                res = res.append(hehe);
                res = res.append(", ");
            }
            facNum++;
            f = f/h;
        }

        while ((count < d) && ((*iter) == minusOne)){
            iter++;
            count++;
        }
        if (count >= d){more = false;}
        else{
            while (eraser != iter){
                *eraser = nihil;
                eraser++;
            }
            *iter = (*iter) + one;
            eraser = h.mons.begin();
            iter = h.mons.begin();
            count = 0;
        }
    }

    return res;
}


QString restPoly::EqDegFactor(MaceInt d){
    restPoly f, tmp(*this);
    f = tmp;

    MaceInt chara= f.charac();
    MaceInt one(1), count;
    MaceInt clara = chara;

    MaceRest eins(one,chara);
    const MaceRest zero(chara);

    MaceRest minusOne(chara-one,chara);

    restPoly n(chara), m(chara), hilf(eins), master(zero), g(eins);
    QString res, hehe;
    MaceInt j(1);
    int i=1;

    master = hilf;
    master = master.mult(minusOne);
    master.shift(j.toInt());

    while(clara > j){
        mpz_add_ui(j.entry.get_mpz_t(),j.entry.get_mpz_t(),1);
        if (clara > j){master.expand(zero);}
        else{master.expand(eins);}
    }

    while (f.degree() >= (2*i)){
        rgcd(g,f,master);
        if (g.degree()> 0){
            hehe = g.CanZas(i,d);
            res.append(hehe);
        }
        f = f/g;
        i++;

        clara = chara*clara;

        mpz_set_ui(j.entry.get_mpz_t(),1);
        master = hilf;
        master = master.mult(minusOne);
        master.shift(j.toInt());

        while(clara > j){
            mpz_add_ui(j.entry.get_mpz_t(),j.entry.get_mpz_t(),1);
            if (clara > j){master.expand(zero);}
            else{master.expand(eins);}
        }
        f = f.normalize();
    }

    if (f.degree()>0){
        hehe = f.CanZas(f.degree(),d);
        res.append(hehe);
    }
    return res;
}


QString restPoly::factors(MaceInt k){
    MaceInt i(1), j, nb, chara = this->charac();
    const MaceInt one(1);
    QString res, help;

    restPoly f(*this);
    f = f.normalize();
    if (f.degree()>0){

    restPoly g(chara), c(chara), w(chara), y(chara), z(chara), m(chara), n(chara), hilf(chara);
    g = f.der();

    if (g.degree()>-1){

        rgcd(c,f,g);
        w = f/c;

        while(w.degree()>0){

            rgcd(y,w,c);
            z = w/y;

            if(z.degree()>0){
              j= one;
              nb = i*k;
              help = z.EqDegFactor(nb);
              res.append(help);
            }
            i++;
            w = y;
            c = c/y;
        }

        c=c.normalize();
        if(c.degree()>0){
            c = c.killZero();

            help = c.factors(chara*k);
            res.append(help);
        }
        else{
            res = res.left(res.size()-2);
        }
    }
    else{
        f = f.killZero();
        help = f.factors(chara*k);
        res.append(help);
    }
    }
    else{
        res = f.print();
    }
    return res;
}

MaceRest restPoly::value(MaceRest z){
    MaceRest res, help;
    std::list<MaceRest>::iterator iter = mons.begin();

    int i= 0;

    while(iter != mons.end()){
        help = *iter;
        if (i == 0){res = help;}
        else{
            for (int m = 0; m<i; m++){help = help*z;}
            res = res+help;
        }
        i++;
        iter++;
    }

    return res;
}

QString restPoly::zeroes() {
    QString res = "";
    std::list<MaceRest> zeroes = zeroList();

    if (zeroes.size() == 0) return "no";
    for (std::list<MaceRest>::iterator i = zeroes.begin(); i != zeroes.end(); i++) {
        res = res.append(i->print());
        res = res.append(", ");
    }

    return res;
}

std::list<MaceRest> restPoly::zeroList(){
    MaceInt charac = this->charac();
    int deg = degree(), count = 0;
    MaceRest candi(0,charac), one(1,charac);
    std::list<MaceRest> zeroes;

    do {
        if (value(candi).isZero()) {
            zeroes.push_back(candi);
        }
        candi = candi + one;
    } while (mpz_cmp_ui(candi.val.get_mpz_t(),0) > 0 && count < deg);
    return zeroes;
}*/







