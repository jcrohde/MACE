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

#ifndef MACEREST_H
#define MACEREST_H

/*#include "maceint.h"
#include <gmp.h>
#include <QPair>
#include "math/kernel/datum.h"


class MaceRest : public datum
{
private:
    virtual void invCall();

public:
    mpz_class val;
    mpz_class mod;

    class zeroError{
        //exception class for mod = 0
    };

    MaceRest();
    MaceRest(unsigned int i, unsigned int j);
    MaceRest(unsigned int i, MaceInt j);
    MaceRest(MaceInt i); //0 mod i
    MaceRest(MaceInt i, MaceInt j); //i mod j

    ~MaceRest();

    MaceInt  charac();
    MaceInt  IntPret();
    MaceRest minusOne();

    void normalize();
    MaceRest one();
    virtual QString print(unsigned int precision) {return print();}
    QString print();

    virtual bool isZero();

    void translate(MaceInt pInt);

    friend MaceRest operator+( MaceRest r1, MaceRest r2 ){
        MaceRest res;
        res.val = r1.val + r2.val ;
        mpz_set(res.mod.get_mpz_t(),r1.mod.get_mpz_t());
        res.normalize();
        return res;
    }

    MaceRest operator-( MaceRest r2 ) const {
        MaceRest res, tmp(*this);
        res.val = tmp.val - r2.val;
        mpz_set(res.mod.get_mpz_t(),tmp.mod.get_mpz_t());
        res.normalize();
        return res;
    }

    friend MaceRest operator*( MaceRest r1, MaceRest r2 ){
        MaceRest res;
        res.val = r1.val * r2.val;
        mpz_set(res.mod.get_mpz_t(),r1.mod.get_mpz_t());
        res.normalize();
        return res;
    }

    MaceRest operator/( MaceRest val2 ) const {
        MaceRest res;
        val2.zeroTest();
        mpz_invert(res.val.get_mpz_t(),val2.val.get_mpz_t(),mod.get_mpz_t());
        mpz_mul(res.val.get_mpz_t(),res.val.get_mpz_t(),val.get_mpz_t());
        mpz_set(res.mod.get_mpz_t(),mod.get_mpz_t());
        res.normalize();
        return res;
    }

    bool operator==( MaceRest r1){
        return ((mpz_cmp(val.get_mpz_t(),r1.val.get_mpz_t()) == 0)
                && (mpz_cmp(mod.get_mpz_t(),r1.mod.get_mpz_t()) == 0));
    }

    bool operator!=( MaceRest r1){
        return ((mpz_cmp(val.get_mpz_t(),r1.val.get_mpz_t()) != 0)
                || (mpz_cmp(mod.get_mpz_t(),r1.mod.get_mpz_t()) != 0));
    }

    bool operator<( MaceRest r1){
        normalize(); r1.normalize();
        return (val < r1.val);
    }

    bool operator>( MaceRest r1){
        normalize(); r1.normalize();
        return (val > r1.val);
    }

    bool operator<=( MaceRest r1){
        normalize(); r1.normalize();
        return (val <= r1.val);
    }

    bool operator>=( MaceRest r1){
        normalize(); r1.normalize();
        return (val >= r1.val);
    }

};*/

#endif // MACEREST_H

