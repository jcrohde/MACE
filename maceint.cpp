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

/*#include "maceint.h"

MaceInt::MaceInt()
{

}

MaceInt::MaceInt(unsigned int i)
{
    mpz_set_ui(entry.get_mpz_t(), i);
}

MaceInt::MaceInt(int i)
{
    mpz_set_si(entry.get_mpz_t(),i);
}

MaceInt::MaceInt(char* str){
    mpz_set_str(entry.get_mpz_t(),str,10);
}

MaceInt::~MaceInt(){
    mpz_clear(entry.get_mpz_t());
}

void MaceInt::abs(){
    if (mpz_cmp_ui(entry.get_mpz_t(),0) < 0)
        mpz_neg(entry.get_mpz_t(),entry.get_mpz_t());
}

MaceInt MaceInt::translate(unsigned int i){
    MaceInt res(i);
    return res;
}

MaceInt MaceInt::translate(int i){
    MaceInt res(i);
    return res;
}

int MaceInt::toSInt(){
    return mpz_get_si(entry.get_mpz_t());
}

unsigned int MaceInt::toInt(){
    return mpz_get_ui(entry.get_mpz_t());
}


    QString MaceInt::print(){
        char *str = new char[mpz_sizeinbase(entry.get_mpz_t(), 10) + 2];
        str = mpz_get_str(str,10,entry.get_mpz_t());
        QString res(str);
        delete[] str;
        return res;
    }

    MaceInt MaceInt::mult(unsigned int i){
        MaceInt res, tmp(*this);

        mpz_mul_ui(res.entry.get_mpz_t(),tmp.entry.get_mpz_t(),i);
        return res;
    }

    bool MaceInt::geq(unsigned int i){
        MaceInt help(i);
        return *this >= help;
    }

    bool MaceInt::larger(unsigned int i){
        MaceInt help(i), tmp(*this);
        bool res;
        res = tmp > help;
        return res;
    }

    bool MaceInt::smaller(unsigned int i){
        MaceInt help(i), tmp(*this);
        bool res;
        res = tmp < help;
        return res;
    }

    void MaceInt::set(QString str) {
        std::string ba = str.toUtf8().constData();
        char *help = new char[ba.length() + 1];
        strcpy(help, ba.c_str());
        mpz_set_str(entry.get_mpz_t(),help,10);
        delete[] help;
    }

    MaceInt MaceInt::divi(unsigned int i){
        MaceInt res;
        mpz_tdiv_q_ui(res.entry.get_mpz_t(),entry.get_mpz_t(),i);
        return res;
    }

    MaceInt MaceInt::sub(unsigned int i){
        MaceInt res;
        if (mpz_cmp_ui(entry.get_mpz_t(),i)>0)
            mpz_sub_ui(res.entry.get_mpz_t(),entry.get_mpz_t(),i);

        return res;
    }

    double MaceInt::toDouble(){
        return mpz_get_d(entry.get_mpz_t());
    }

    MaceInt MaceInt::power(MaceInt b){
        MaceInt tmp(*this), res("1"), count("0"), zero("0");
        while(count < b){
            res = res*tmp;
            count++;
        }
        return res;
    }

    MaceInt MaceInt::gcd(MaceInt a, MaceInt b){
        MaceInt help, zero(0);
        if(b>a){
            help = a;
            a=b;
            b=help;
        }

        help = b;
        while (help != zero){
            help = a%b;
            a = b;
            b = help;
        }

        return a;
    }

    void gcd(MaceInt &res, MaceInt &a, MaceInt &b) {
        mpz_gcd(res.entry.get_mpz_t(),a.entry.get_mpz_t(),b.entry.get_mpz_t());
    }

    void lcm(MaceInt &res, MaceInt &a, MaceInt &b) {
        mpz_lcm(res.entry.get_mpz_t(),a.entry.get_mpz_t(),b.entry.get_mpz_t());
    }

    void extEuk(MaceInt &res, MaceInt &s, MaceInt &t, MaceInt &a, MaceInt &b) {
        mpz_gcdext(res.entry.get_mpz_t(),s.entry.get_mpz_t(),t.entry.get_mpz_t(),
                   a.entry.get_mpz_t(),b.entry.get_mpz_t());
    }*/
