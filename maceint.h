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

#ifndef MACEINT_H
#define MACEINT_H

/*#include <QList>
#include <QString>
#include <string>
#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include "math/kernel/mobject.h"

class MaceInt : public MObject
{
public:
    mpz_class entry;

    MaceInt();
    MaceInt(unsigned int a);
    MaceInt(int a);
    MaceInt(char* str);

    ~MaceInt();

    void abs();
    MaceInt divi(unsigned int i);
    MaceInt gcd(MaceInt a, MaceInt b);
    bool geq(unsigned int i);
    bool larger(unsigned int i);
    MaceInt mult(unsigned int i);
    MaceInt power(MaceInt b);
    QString print(unsigned int precision) {return print();}
    QString print();
    virtual bool isZero() {return (mpz_cmp_si(entry.get_mpz_t(),0) == 0);}
    bool smaller(unsigned int i);
    void set(QString str);
    MaceInt sub(unsigned int i);
    double toDouble();
    unsigned int toInt();
    int toSInt();
    MaceInt translate(unsigned int i);
    MaceInt translate(int i);

    MaceInt& operator=( const MaceInt& b ) {
        if (this != &b){
            mpz_set(entry.get_mpz_t(),b.entry.get_mpz_t());
        }
        return *this;
    }

    friend MaceInt operator+( MaceInt a, MaceInt b)
    {
        MaceInt res;
        res.entry = a.entry + b.entry;
        return res;
    }

    MaceInt operator-(MaceInt b ) const
    {
        MaceInt res, a(*this);

        res.entry = a.entry - b.entry;

        return res;
    }

     friend MaceInt operator*( MaceInt a, MaceInt b)
     {
        MaceInt res;
        res.entry = a.entry * b.entry;
        return res;
    }

    MaceInt operator/(MaceInt b ) const {
        MaceInt res;
        mpz_tdiv_q(res.entry.get_mpz_t(),entry.get_mpz_t(),b.entry.get_mpz_t());
        return res;
    }

    MaceInt operator%(MaceInt b ) const {
        MaceInt res, tmp(*this);
        mpz_tdiv_r(res.entry.get_mpz_t(),tmp.entry.get_mpz_t(),b.entry.get_mpz_t());
        return res;
    }

    bool operator>=(MaceInt b){
        MaceInt a(*this);
        return (mpz_cmp(a.entry.get_mpz_t(),b.entry.get_mpz_t())>=0);
    }

    bool operator<=(MaceInt b){
        MaceInt a(*this);
        return (mpz_cmp(a.entry.get_mpz_t(),b.entry.get_mpz_t())<=0);
    }


    bool operator>(MaceInt b){
        MaceInt a(*this);
        return (mpz_cmp(a.entry.get_mpz_t(),b.entry.get_mpz_t())>0);
    }

    bool operator<(MaceInt b){
        MaceInt a(*this);
        return (mpz_cmp(a.entry.get_mpz_t(),b.entry.get_mpz_t())<0);
    }

    bool operator==(MaceInt b){
        MaceInt a(*this);
        return (mpz_cmp(a.entry.get_mpz_t(),b.entry.get_mpz_t())==0);
    }

    bool operator!=(MaceInt b){
        MaceInt a(*this);
        return (mpz_cmp(a.entry.get_mpz_t(),b.entry.get_mpz_t())!=0);
    }

    MaceInt operator++(int){
        MaceInt help(1);
        *this = *this+help;
        return *this;
    }

    MaceInt operator-(){
        return *this;
    }

};

extern void gcd(MaceInt &res, MaceInt &a, MaceInt &b);
extern void lcm(MaceInt &res, MaceInt &a, MaceInt &b);
extern void extEuk(MaceInt &res, MaceInt &s, MaceInt &t, MaceInt &a, MaceInt &b);*/

#endif // MACEINT_H
