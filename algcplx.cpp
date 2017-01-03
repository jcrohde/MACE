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

#include "math/variables/scalar/algcplx.h"

/*algCplx::algCplx()
{

}

algCplx::algCplx(int a, int b)
{
    mpq_set_si(real.get_mpq_t(),a,1);
    mpq_set_si(imag.get_mpq_t(),b,1);
}

algCplx::algCplx(MaceInt a, MaceInt b)
{

    mpq_set_z(real.get_mpq_t(),a.entry.get_mpz_t());
    mpq_set_z(imag.get_mpq_t(),b.entry.get_mpz_t());
}

algCplx::~algCplx() {
    mpq_clear(real.get_mpq_t());
    mpq_clear(imag.get_mpq_t());
}

void algCplx::assign(int a, int b){
    real = a;
    imag = b;
}

void algCplx::assign(MaceInt &mi) {
    mpq_set_z(real.get_mpq_t(),mi.entry.get_mpz_t());
    mpq_set_ui(imag.get_mpq_t(),0,1);
}

algCplx algCplx::norm(){
    algCplx res;

    mpq_class help;
    res.real = real*real;
    help = imag*imag;
    res.real = res.real + help;

    mpq_clear(help.get_mpq_t());

    return res;
}

algCplx algCplx::getRealPart() {
    algCplx res(0,0);
    mpq_set(res.real.get_mpq_t(),real.get_mpq_t());
    return res;
}

algCplx algCplx::getImagPart() {
    algCplx res(0,0);
    mpq_set(res.real.get_mpq_t(),imag.get_mpq_t());
    return res;
}

QString algCplx::print(unsigned int precision){
  numCplx help = this->toNumCplx();

  QString res = help.print(precision);
  return res;
}

void algCplx::setReal(QString str){
    if (str.indexOf(".")>-1) {
        int pos = str.indexOf(".");
        QString help = str.left(pos);
        pos=str.size()-pos-1;
        help = help.append(str.right(pos));
        help = help.append("/1");
        for (int i = 0; i < pos; i++)
            help = help.append("0");
        str = help;
    }
    std::string ba = str.toUtf8().constData();
    char *help = new char[ba.length() + 1];
    strcpy(help, ba.c_str());

    mpq_set_str(real.get_mpq_t(),help,10);

    delete[] help;
}

void algCplx::eval(std::string str, unsigned int dotPos) {
    mpq_set_ui(imag.get_mpq_t(),0,1);

    unsigned int denom = 1;
    for (unsigned int i=0; i<str.size()-dotPos-1; i++) {
        denom *= 10;
    }

    mpq_t den;
    mpq_init(den);
    mpq_set_ui(den,denom,1);

    str.erase(dotPos,1);
    char *cstr = new char[str.size()+1];
    strcpy(cstr,str.c_str());
    mpq_set_str(real.get_mpq_t(),cstr,10);
    mpq_div(real.get_mpq_t(),real.get_mpq_t(),den);
    mpq_clear(den);
    delete[] cstr;
}

bool algCplx::putDown(MaceInt &mi) {
    mpq_class h;

    if (mpq_cmp_ui(imag.get_mpq_t(),0,1) == 0) {
        mpz_set_q(mi.entry.get_mpz_t(),real.get_mpq_t());
        mpq_set_z(h.get_mpq_t(),mi.entry.get_mpz_t());
        return (mpq_cmp(h.get_mpq_t(),real.get_mpq_t()) == 0);
    }
    mpq_clear(h.get_mpq_t());
    return false;
}

mpq_class algCplx::getReal() {
    return real;
}

void algCplx::conj() {
    mpq_neg(imag.get_mpq_t(),imag.get_mpq_t());
}

numCplx algCplx::toNumCplx(){

    numCplx res(mpq_get_d(real.get_mpq_t()),mpq_get_d(imag.get_mpq_t()));

    return res;
}

void algCplx::fromNumCplx(numCplx n) {
    mpq_set_d(real.get_mpq_t(),n.real());
    mpq_set_d(imag.get_mpq_t(),n.imag());
}

bool algCplx::isZero(){
    return (mpq_sgn(real.get_mpq_t()) == 0 &&mpq_sgn(imag.get_mpq_t()) == 0);
}

void algCplx::invCall(){
    algCplx one(1,0);
    *this = one / *this;
}

void multAlgC(algCplx *res, algCplx *a, const algCplx *b)
{
    *res = (*a) * (*b);
}*/
