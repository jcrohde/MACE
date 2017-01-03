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

#ifndef ALGCPLX_H
#define ALGCPLX_H

/*#include <gmp.h>
#include <gmpxx.h>
#include "math/variables/scalar/numcplx.h"
#include "math/variables/scalar/maceint.h"
#include "math/kernel/datum.h"
#include <QString>

class algCplx : public datum
{
private:
    virtual void invCall();

    mpq_class real;
    mpq_class imag;

public:
    algCplx();
    algCplx(int a, int b);
    algCplx(MaceInt a, MaceInt b);

    ~algCplx();

    void      assign (int a, int b);
    void      assign (MaceInt &mi);
    void      setReal(QString str);
    void      eval   (std::string str, unsigned int dotPos);
    bool      putDown(MaceInt &mi);

    mpq_class getReal();
    void      conj();
    algCplx   norm();
    algCplx   getRealPart();
    algCplx   getImagPart();

    virtual QString print(unsigned int precision);
    virtual bool    isZero();

    bool isReal() {return (mpq_cmp_ui(imag.get_mpq_t(),0,1) == 0);}

    numCplx toNumCplx();
    void    fromNumCplx(numCplx n);

   friend algCplx operator+( algCplx v1, algCplx v2 )
    {
       algCplx tmp;
       tmp.real = v1.real + v2.real;
       tmp.imag = v1.imag + v2.imag;
       return tmp;
    }

    algCplx operator-( algCplx val2 ) const {
       algCplx tmp(*this), res;
       res.real = tmp.real - val2.real;
       res.imag = tmp.imag - val2.imag;
       return res;
   }

    friend algCplx operator*( algCplx v1, algCplx v2 )
       {
          algCplx   tmp;
          mpq_class help;

          //real part
          tmp.real = v1.real*v2.real;
          help = v1.imag*v2.imag;
          tmp.real = tmp.real - help;

          //imag part
          tmp.imag = v1.real * v2.imag;
          help = v1.imag * v2.real;
          tmp.imag = tmp.imag + help;

          mpq_clear(help.get_mpq_t());

          return tmp;
       }

       algCplx operator/( algCplx val2 ) const {
          algCplx   res, norm;
          algCplx   tmp(*this);
          mpq_class help;

          val2.zeroTest();
          norm = val2.norm();

          //real part
          res.real = tmp.real * val2.real;
          help = tmp.imag * val2.imag;
          res.real = res.real + help;
          res.real = res.real/norm.real;

          //imag part
          res.imag = tmp.real*val2.imag;
          help = tmp.imag * val2.real;
          res.imag = help - res.imag;
          res.imag = res.imag/norm.real;

          mpq_clear(help.get_mpq_t());

          return res;
       }

       bool operator==( algCplx r1){
           return (mpq_cmp(real.get_mpq_t(),r1.real.get_mpq_t()) == 0
                   && mpq_cmp(imag.get_mpq_t(),r1.imag.get_mpq_t()) == 0);
       }

       bool operator<( algCplx r1){
           bool res;

           if (mpq_cmp_ui(imag.get_mpq_t(),0,1) == 0
                   && mpq_cmp_ui(r1.imag.get_mpq_t(),0,1) == 0) {
               return (mpq_cmp(real.get_mpq_t(),r1.real.get_mpq_t())<0);
           }
           else {
               mpq_class help,helpr;
               help = real*real + imag*imag;
               helpr = r1.real*r1.real +r1.imag*r1.imag;
               res = (mpq_cmp(help.get_mpq_t(),helpr.get_mpq_t())<0);
               mpq_clear(help.get_mpq_t());
               mpq_clear(helpr.get_mpq_t());
           }
           return res;
       }

       bool operator<=( algCplx r1){
           bool res;

           if (mpq_cmp_ui(imag.get_mpq_t(),0,1) == 0
                   && mpq_cmp_ui(r1.imag.get_mpq_t(),0,1) == 0) {
               return (mpq_cmp(real.get_mpq_t(),r1.real.get_mpq_t())<=0);
           }
           else {
               mpq_class help,helpr;
               help = real*real + imag*imag;
               helpr = r1.real*r1.real +r1.imag*r1.imag;
               res = (mpq_cmp(help.get_mpq_t(),helpr.get_mpq_t())<=0);
               mpq_clear(help.get_mpq_t());
               mpq_clear(helpr.get_mpq_t());
           }
           return res;
       }

       bool operator>=( algCplx r1){
           bool res;

           if (mpq_cmp_ui(imag.get_mpq_t(),0,1) == 0
                   && mpq_cmp_ui(r1.imag.get_mpq_t(),0,1) == 0) {
               return (mpq_cmp(real.get_mpq_t(),r1.real.get_mpq_t())>=0);
           }
           else {
               mpq_class help,helpr;
               help = real*real + imag*imag;
               helpr = r1.real*r1.real +r1.imag*r1.imag;
               res = (mpq_cmp(help.get_mpq_t(),helpr.get_mpq_t())>=0);
               mpq_clear(help.get_mpq_t());
               mpq_clear(helpr.get_mpq_t());
           }
           return res;
       }

       bool operator>( algCplx r1){
           bool res;

           if (mpq_cmp_ui(imag.get_mpq_t(),0,1) == 0
                   && mpq_cmp_ui(r1.imag.get_mpq_t(),0,1) == 0) {
               return (mpq_cmp(real.get_mpq_t(),r1.real.get_mpq_t())>0);
           }
           else {
               mpq_class help,helpr;
               help = real*real + imag*imag;
               helpr = r1.real*r1.real +r1.imag*r1.imag;
               res = (mpq_cmp(help.get_mpq_t(),helpr.get_mpq_t())>0);
               mpq_clear(help.get_mpq_t());
               mpq_clear(helpr.get_mpq_t());
           }
           return res;
       }

       bool operator!=( algCplx r1){
           return (mpq_cmp(real.get_mpq_t(),r1.real.get_mpq_t()) != 0
                   || mpq_cmp(imag.get_mpq_t(),r1.imag.get_mpq_t()) != 0);
       }

};

extern void multAlgC(algCplx *res, algCplx *a, const algCplx *b);*/

#endif // ALGCPLX_H
