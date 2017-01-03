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

#include "macerest.h"

/*MaceRest::MaceRest()
{
    mpz_set_ui(mod.get_mpz_t(),2);
}

MaceRest::MaceRest(unsigned int i, unsigned int j){
    mpz_set_ui(val.get_mpz_t(),i);
    mpz_set_ui(mod.get_mpz_t(),j);
    normalize();
}

MaceRest::MaceRest(unsigned int i, MaceInt j){
    mpz_set_ui(val.get_mpz_t(),i);
    mpz_set(mod.get_mpz_t(),j.entry.get_mpz_t());
    normalize();
}

MaceRest::MaceRest(MaceInt i){
    mpz_set(mod.get_mpz_t(),i.entry.get_mpz_t());
    normalize();
}

MaceRest::MaceRest(MaceInt i, MaceInt j){
    mpz_set(val.get_mpz_t(),i.entry.get_mpz_t());
    mpz_set(mod.get_mpz_t(),j.entry.get_mpz_t());
    normalize();
}

MaceRest::~MaceRest() {
    mpz_clear(val.get_mpz_t());
    mpz_clear(mod.get_mpz_t());
}

MaceInt MaceRest::charac(){
    MaceInt res;
    mpz_set(res.entry.get_mpz_t(),mod.get_mpz_t());
    return res;
}

MaceInt MaceRest::IntPret(){
    MaceInt res;
    this->normalize();
    mpz_set(res.entry.get_mpz_t(),val.get_mpz_t());
    return res;
}

MaceRest MaceRest::minusOne(){
    MaceRest res(charac());
    mpz_sub_ui(res.val.get_mpz_t(),res.mod.get_mpz_t(),1);
    return res;
}

MaceRest MaceRest::one(){
    MaceRest res(1,charac());
    return res;
}

void MaceRest::normalize(){
    if (mpz_cmp_si(mod.get_mpz_t(),0) == 0) {zeroError e; throw e;}
    if (mpz_cmp_si(mod.get_mpz_t(),0) < 0)
        mpz_neg(mod.get_mpz_t(),mod.get_mpz_t());

    mpz_tdiv_r(val.get_mpz_t(),val.get_mpz_t(),mod.get_mpz_t());
    if (mpz_cmp_si(val.get_mpz_t(),0) < 0)
        mpz_add(val.get_mpz_t(),val.get_mpz_t(),mod.get_mpz_t());
}

QString MaceRest::print() {
    normalize();
    char *str = new char[mpz_sizeinbase(val.get_mpz_t(), 10) + 2];
    str = mpz_get_str(str,10,val.get_mpz_t());
    QString res(str);
    delete[] str;
    return res;
}

void MaceRest::translate(MaceInt pInt){
    mpz_set(val.get_mpz_t(),pInt.entry.get_mpz_t());
    this->normalize();
}

bool MaceRest::isZero(){
    mpz_tdiv_r(val.get_mpz_t(),val.get_mpz_t(),mod.get_mpz_t());
    return (mpz_cmp_ui(val.get_mpz_t(),0) == 0);
}

void MaceRest::invCall(){
    MaceRest one(1,charac());
    *this = one / *this;
}*/
