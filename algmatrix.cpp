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

#include "algmatrix.h"

/*static const algCplx one(1,0);
static const algCplx minusOne(-1,0);
static const algCplx zero(0,0);

static void conj(algCplx *ic, algCplx *oc) {
    *ic = *oc;
    ic->conj();
}

algMatrix::algMatrix(): genMatrix(){
    algCplx zero;
    entries.append(zero);
}

algMatrix::algMatrix(int a, int b): genMatrix(a, b){
  algCplx zero;

  for (int i = 1; i <= a*b; i++){entries.append(zero);}
}

algMatrix algMatrix::cross(algMatrix m) {
    algMatrix res(3,1);

    if (lines= 3 && columns == 1 && m.lines == 3 && m.columns == 1) {
        *res.element(1,1) = (*element(2,1))*(*m.element(3,1))-(*element(3,1))*(*m.element(2,1));
        *res.element(2,1) = (*element(3,1))*(*m.element(1,1))-(*element(1,1))*(*m.element(3,1));
        *res.element(3,1) = (*element(1,1))*(*m.element(2,1))-(*element(2,1))*(*m.element(1,1));
    }

    return res;
}

algMatrix algMatrix::image() {
    algMatrix tmp(*this);
    int rk = tmp.rank();
    if (rk == 0) rk = 1;
    algMatrix res(lines,rk);

    int lin = 1, col = 1, rcol = 1, i;
    while(lin <= lines && col <= columns){
        if(!tmp.elemZero(lin,col)){
            for (i = 1; i <= lines; i++) {
                *res.element(i,rcol) = *element(i,col);
            }
            lin++;
            rcol++;
        }
        else{
            col++;
        }
    }
    return res;
}

QList<algCplx>::Iterator algMatrix::element(int i, int j){
    QList<algCplx>::Iterator iter = entries.begin();
    for (int m = 1; m <= (((i-1)*columns)+(j-1));m++){
        iter++;
    }
    return iter;
}

void algMatrix::changeLines( int i, int j){
  algCplx help;
  for (int k=1; k<= columns; k++){
    help = *element(i,k);
    *element(i,k) = *element(j,k);
    *element(j,k) = help;
  }
}


void algMatrix::addLines( int i, int j, int c){
  algCplx z, help;
  z = z-*element(i,c);
  for (int k=1; k<= columns; k++){
      help = *element(j,k);
      help = help*z;
      help = (*element(i,k))+help;
      *element(i,k) = help;
  }
}

bool algMatrix::elemZero(int i, int j){
    algCplx z =  *element(i,j);
    return z.isZero();
}

void algMatrix::normLine( int i, int j){
  algCplx help = *element(i,j);
  help.invert();
  for (int k=1; k<= columns; k++){
      *element(i,k) = (*element(i,k))*help;
  }
}

algCplx algMatrix::adj(int i, int j) {
    algMatrix help(lines-1,columns-1);
    int ih, jh;

    for (int lin = 1; lin <=lines; lin++) {
        for (int col = 1; col <= columns; col++) {
            if (lin != i && col != j) {
                if (lin< i) ih = lin;
                else ih = lin-1;
                if (col < j) jh = col;
                else jh = col - 1;
                *help.element(ih,jh) = *element(lin,col);
            }
        }
    }

    numMatrix nHelp = help.toNumMatrix();
    numCplx nres = nHelp.det();
    algCplx res;
    res.fromNumCplx(nres);
    if (((i + j) % 2) != 0) res = res* minusOne;
    return res;
}

void algMatrix::adjoint(algMatrix &ad) {
    ad.lines = lines;
    ad.columns  = columns;
    ad.entries.clear();
    for (int i = 1; i <= lines; i++) {
        for (int j = 1; j <= columns; j++) {
            ad.entries.push_back(zero);
        }
    }
    for (int i = 1; i <= lines; i++) {
        for (int j = 1; j <= columns; j++) {
            *ad.element(i,j) = adj(i,j);
        }
    }
}

void algMatrix::subSkaProd(int i, int j) {
    algCplx sum, help, h2;
    for (int l = 1; l <= lines; l++) {
        help = *element(l,i);
        if (!help.isZero()) {
            h2 = help.norm()/help;
            sum = sum + (h2*(*element(l,j)));
        }
    }
    conj(&sum,&sum);
    for (int l = 1; l <= lines; l++) {
        *element(l,i) = *element(l,i) - sum*(*element(l,j));
    }
}

void algMatrix::norm(int i) {
    numCplx nSum;
    algCplx sum, help;
    for (int l = 1; l <= lines; l++) {
        help = *element(l,i);
        help = help.norm();
        sum = sum + help;
    }
    nSum = sum.toNumCplx();
    nSum.val = sqrt(nSum.val);
    sum.fromNumCplx(nSum);
    if (nSum.norm() > 0.000001) {
        for (int l = 1; l <= lines; l++) {
            *element(l,i) = *element(l,i)/sum;
        }
    } else {
        for (int l = 1; l <= lines; l++) {
            *element(l,i) = zero;
        }
    }
}

void algMatrix::gramSchmidt() {
    for (int i = 1; i <= columns; i++){
        for (int j = 1; j < i; j++) {
            subSkaProd(i,j);
        }
        norm(i);
    }
}

bool algMatrix::invert(algMatrix &am){
    if (am.lines != am.columns){
        return false;
    }
    else{
      algMatrix help(am.lines, 2*am.columns);

      for(int i = 1; i <= am.lines; i++){
        *help.element(i,i+am.lines) = one;
      }

      for(int i = 1; i <= am.lines; i++){
        for(int j = 1; j <= am.lines; j++){
          *help.element(i,j) = *am.element(i,j);
        }
      }

      help.gauss();

      for (int i = 1; i <= am.lines; i++){
          if(*help.element(i,i) ==zero) return false;
      }

      for (int i = 1; i <= am.lines; i++){
          for (int j = 1; j <= am.lines; j++){
              *am.element(i,j) = *help.element(i,j+am.lines);
          }
      }

    }
    return true;
}

QString algMatrix::print(int i, int j) {
    return element(i,j)->print(6);
}

algMatrix algMatrix::solve(algMatrix b) {
    algMatrix tmp(*this);
    algCplx zero;

    algCplx null;
    algCplx minusEins(-1,0);

    ///pose the system of equations//////////////////////////////////////
    algMatrix help(tmp.lines, tmp.columns+b.columns);
    for (int i = 1; i<= tmp.lines; i++){
      for (int j = 1; j <= tmp.columns; j++){
        *help.element(i,j) = *tmp.element(i,j);
      }
      for (int j = 1; j <= b.columns; j++){
        *help.element(i,tmp.columns+j) = *b.element(i,j);
      }
    }

    ///apply Gauss///////////
    help.gauss();

    return help;
}

algCplx algMatrix::trace(){
    algMatrix tmp(*this);
    algCplx res;
    if (tmp.lines != tmp.columns){
        return res;
    }
    else{
        for (int i=1;i<= tmp.columns; i++){
            res = res+(*tmp.element(i,i));
        }
        return res;
    }
}

algMatrix algMatrix::copy(algMatrix m){
    algMatrix res(*this);
    if (res.lines !=m.lines || res.lines !=m.lines){return res;}
    else{
    for (int x =1; x <= lines; x++){
        for (int y =1; y <= columns; y++){
            *res.element(x,y) = *m.element(x,y);
        }
    }
    return res;
    }
}


algPoly algMatrix::charPoly(){
    algCplx one(1,0), q, minusOne(-1,0), myI;
    algPoly res, b, a(one);
    algMatrix tmp(*this);
    if (lines==columns){
        algMatrix A(tmp.lines,tmp.columns), B(tmp.lines,tmp.columns), C(tmp.lines,tmp.columns),  I(tmp.lines,tmp.columns);

        for (int i = 1; i<= tmp.lines; i++){
            *I.element(i,i)=one;
        }

        A= A.copy(tmp);
        B= B.copy(I);

        res= a;

        for (int i = 1;i<=tmp.lines;i++){
            res.shift(1);
            C=A*B;
            q= C.trace();
            myI.assign(-i,0);
            q= q/myI;
            b= a;
            b.mult(q);
            res = res+b;
            for (int k = 1; k<= tmp.lines; k++){
                for (int j=1; j<=tmp.columns;j++){
                *B.element(k,j)=(*C.element(k,j))+(q*(*I.element(k,j)));
            }
            }
        }
    }
    return res;
}


algPoly algMatrix::miniPoly(){
    int m= 1, diff = 1, rank, oldRank=0, a=1, b;
    algCplx one(1,0), test(1,0), minusOne(-1,0), zero;
    algPoly p(one), q, r(minusOne);
    algMatrix tmp(*this),help;
    algMatrix B(lines*lines,1+columns), I(lines,columns);

    for (int i = 1; i<= tmp.lines; i++){
        *I.element(i,i)=one;
    }

    while(diff > 0 && m <= lines+1){
      for (int k= 1;k<= lines; k++){
          for (int j=1;j<=lines; j++){
              *B.element((lines)*(k-1)+j,m) = *I.element(k,j);
          }
      }
      help = B;
      rank = help.rank();
      diff = rank-oldRank;

      rank=oldRank;
      I=I*tmp;
      m++;
   }

   B.gauss();
   B.debugPrint();

   a=0;
   while (test != zero && a<lines+1){
       a++;
       test = *B.element(a,a);
   }

   b=a;
   while(b>1){
       p.shift(1);
       q= r;
       q.mult(*B.element(b-1,a));
       p= p+q;
       b--;
   }

   return p;
}

QString algMatrix::interpretation(){

    algMatrix tmp(*this);

    ///check for empty set as result///////////////////////////////////////////////////
    int l = tmp.lines+1 ,c;
    algCplx mem, z, w, zero, minusOne(-1,0);
    QString qres, help;
    bool checker;

    while (z== zero && l>1){
        l--;
        z = *tmp.element(l,tmp.columns);
    }

    w = z;

    c=tmp.columns-1;
    z = *tmp.element(l,c);

    while ((z == zero) && c>1){
        c--;
        z = *tmp.element(l,c);
    }

    if(w != zero && (z == zero)){qres = " the empty set";}
    else{
        algMatrix res(tmp.columns-1, tmp.columns);

    int posMem = 1;
        qres= "<table><tr>";
            if (w != zero){
              qres= qres.append("<th><table border=1><tr><th><table>");
              for (int i = 1; i<= tmp.lines;i++){
          if (*tmp.element(i,tmp.columns) ==zero){
          }
          else{
            qres = qres.append("<tr><th><span style=\"font-weight:200\">");
            z = *tmp.element(i,posMem);
            while(z == zero){
              qres = qres.append(z.print(6));
              qres = qres.append("</span></th></tr>");
              qres = qres.append("<tr><th><span style=\"font-weight:200\">");
              posMem++;
              z=*tmp.element(i,posMem);
            }
                    qres = qres.append(tmp.element(i,tmp.columns)->print(6));
                    qres = qres.append("</span></th></tr>");
            posMem++;
          }
              }

          for (int i = posMem; i <tmp.columns; i++){
        qres = qres.append("<tr><th><span style=\"font-weight:200\">");
        qres = qres.append(zero.print(6));
        qres = qres.append("</span></th></tr>");
          }
          qres= qres.append("</table></th></tr></table></th>");
            }
            else{
          qres= qres.append("<th><table border=1><tr><th><table>");
              for (int i = 1; i< tmp.columns;i++){
        qres = qres.append("<tr><th><span style=\"font-weight:200\">");
        qres = qres.append(zero.print(6));
            qres = qres.append("</span></th></tr>");
          }
          qres= qres.append("</table></th></tr></table></th>");
            }

    /////fill diagonal with -1/////////////////////////////////////////////////////////////////////
        int lns, adder;
        int merker = 0;

        for (int j = 1; j < tmp.columns; j++){

            if (merker+1>tmp.lines){checker = true;}
            else{
                if(*tmp.element(merker+1,j)==zero){checker = true;}
                else {checker = false;}
            }

                if(checker){
                            adder =0;
                            lns = 1;
                            for (int coln = 1; coln <= j; coln++)
                            {
                                if (coln == j) {*res.element(j,j)=minusOne;}
                                else if (lns > tmp.lines) {
                                    if (coln-adder >tmp.lines){*res.element(coln,j)=zero;}
                                    else {(*res.element(coln,j))=(*tmp.element(coln-adder,j));}
                                }
                                else {
                                    if (*tmp.element(lns,coln)!= zero){
                                        lns++;
                                        (*res.element(coln,j))=(*tmp.element(coln-adder,j));
                                    }
                                    else {adder++;*res.element(coln,j)=zero;}
                                }
                            }
                        }
                        else {
                            if(merker+1<=tmp.lines){
                                *res.element(merker+1,res.columns)=*tmp.element(merker+1,j);
                                merker++;
                            }
                        }
        }


            int count =1;

            for (int j= 1; j<res.columns; j++){


                l = res.lines;
                z = *res.element(l,j);

                while (z == zero && l>1){
                    l--;
                    z = *res.element(l,j);
                }

                if(z != zero){
                    qres = qres.append("<th><table><tr><th>");
                    for (int i= 0; i < (res.lines)/2; i++){
                        qres = qres.append("</th></tr><tr><th>");
                    }
                    qres = qres.append("<span style=\"font-weight:200\">");
                    qres= qres.append("+");
                    qres= qres.append("a_");
                    help=help.number(count);
                    qres = qres.append(help);
                    count++;
                    qres = qres.append("</span></th></tr>");
                    qres = qres.append("</table></th>");

                    qres= qres.append("<th><table border=1><tr><th><table>");
                    for (int i = 1; i<= res.lines;i++){
                        qres = qres.append("<tr><th><span style=\"font-weight:200\">");
                        mem = *res.element(i,j);
                        qres = qres.append(mem.print(6));
                        qres = qres.append("</span></th></tr>");
                    }
                    qres= qres.append("</table></th></tr></table></th>");
                }
            }
            qres= qres.append("</tr></table>");
        }


    return qres;
}

algMatrix algMatrix::null() {

    int l, rk = rank();
    if (rk == columns) rk = columns - 1;
    algMatrix tmp(*this);
    algMatrix res(columns,columns), zeroM(columns,columns-rk);
    algCplx zero(0,0), minusOne(-1,0), z;

    tmp.gauss();

    /////fill diagonal with -1/////////////////////////////////////////////////////////////////////
    int lns, adder;
    int merker = 0;
    bool checker;

    for (int j = 1; j <= tmp.columns; j++){

        if (merker+1>tmp.lines){checker = true;}
        else{
            if(*tmp.element(merker+1,j)==zero){checker = true;}
            else {checker = false;}
        }

        if(checker){
            adder =0;
            lns = 1;
            for (int coln = 1; coln <= j; coln++) {
                if (coln == j) {*res.element(j,j)=minusOne;}
                else if (lns > tmp.lines) {
                    if (coln-adder >tmp.lines){*res.element(coln,j)=zero;}
                    else {(*res.element(coln,j))=(*tmp.element(coln-adder,j));}
                }
                else {
                    if (*tmp.element(lns,coln)!= zero){
                        lns++;
                        (*res.element(coln,j))=(*tmp.element(coln-adder,j));
                    }
                    else {adder++;*res.element(coln,j)=zero;}
                }
            }
        }
        else {
            if(merker+1<=tmp.lines){
                *res.element(merker+1,res.columns)=*tmp.element(merker+1,j);
                merker++;
            }
        }
    }

    //copy the kernel into zeroM/////////////////////////////////////////////
    int col=1;

    for (int j= 1; j<=res.columns; j++){

        l = res.lines;
        z = *res.element(l,j);

        while (z == zero && l>1){
            l--;
            z = *res.element(l,j);
        }

        if(z == minusOne){
            for (int m = 1; m <= columns; m++) {
                *zeroM.element(m,col) = *res.element(m,j);
            }
            col++;
        }
    }
    return zeroM;
}

algMatrix algMatrix::transpose(){
  int i,j;
  algMatrix res(columns, lines);
  algMatrix help(*this);

  for (i = 1; i <= columns; i++){
    for (j=1; j<= lines; j++){
      *res.element(i,j) = *help.element(j,i);
    }
  }
  return res;
}

numMatrix algMatrix::toNumMatrix(){
    numMatrix res(lines,columns);
    algCplx help;
    for (int i = 1; i <= lines; i++){
        for (int j = 1; j <= columns; j++){
            help = *this->element(i,j);
            *res.element(i,j) = help.toNumCplx();
        }
    }
    return res;
}

void unitMatrix(unsigned int n, algMatrix &am) {
    am = algMatrix(n,n);

    algCplx one(1,0);
    for (int i = 1; i <= n; i++) {
        *am.element(i,i) = one;
    }
}*/
