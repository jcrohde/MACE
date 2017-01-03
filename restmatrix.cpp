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

#include "restmatrix.h"

/*restMatrix::restMatrix(): genMatrix(){
    valid = true;
    charac = 2;
    MaceRest zero(2);
    entries.push_back(zero);
}

restMatrix::restMatrix(MaceInt c):genMatrix(){
    valid = true;
    lines =1;
    columns = 1;

    charac = c;
    MaceRest zero(c);
    entries.push_back(zero);
}

restMatrix::restMatrix(int a, int b, MaceInt c): genMatrix(a,b), charac(c){
  valid = true;
  MaceRest zero(c);

  for (int i = 1; i <= a*b; i++){entries.push_back(zero);}
}

void restMatrix::normalize(){
    for(std::list<MaceRest>::iterator iter = entries.begin(); iter != entries.end(); iter++){
      iter->normalize();
    }
}


std::list<MaceRest>::iterator restMatrix::element(int i, int j){
    std::list<MaceRest>::iterator iter = entries.begin();
    for (int m = 1; m <= (((i-1)*columns)+(j-1));m++){
        iter++;
    }
    return iter;
}


restMatrix restMatrix::transpose(){
  int i,j;
  restMatrix res(columns, lines, charac);
  restMatrix help(*this);

  for (i = 1; i <= columns; i++){
    for (j=1; j<= lines; j++){
      *res.element(i,j) = *help.element(j,i);
    }
  }
  return res;
}


void restMatrix::changeLines( int i, int j){
  MaceRest help;
  for (int k=1; k<= columns; k++){
    help = *element(j,k);
    *element(j,k) = *element(i,k);
    *element(i,k) = help;
  }
}

restMatrix restMatrix::cross(restMatrix m) {
    restMatrix res(3,1,charac);

    if (lines= 3 && columns == 1 && m.lines == 3 && m.columns == 1) {
        *res.element(1,1) = (*element(2,1))*(*m.element(3,1))-(*element(3,1))*(*m.element(2,1));
        *res.element(2,1) = (*element(3,1))*(*m.element(1,1))-(*element(1,1))*(*m.element(3,1));
        *res.element(3,1) = (*element(1,1))*(*m.element(2,1))-(*element(2,1))*(*m.element(1,1));
    }

    return res;
}

MaceRest restMatrix::adj(int i, int j) {
    restMatrix help(lines-1,columns-1,charac);
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

    MaceRest res = help.det();
    res.normalize();
    if (((i + j) % 2) != 0)
        mpz_sub(res.val.get_mpz_t(),res.mod.get_mpz_t(),res.val.get_mpz_t());
    return res;
}

void restMatrix::adjoint(restMatrix &ad) {
    MaceRest zero(charac);

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

void restMatrix::addLines( int i, int j, int c){
    MaceRest z = *element(i,c), help;
    z = z-*element(i,c);
    z = z-*element(i,c);
    for (int k=1; k<= columns; k++){
        help = *element(j,k);
        help = help*z;
        help = (*element(i,k))+help;
        *element(i,k) = help;
    }
}

bool restMatrix::elemZero(int i, int j){
    MaceRest z =  *element(i,j);
    return z.isZero();
}

void restMatrix::normLine( int i, int j){
  MaceRest help = *element(i,j);
  help.invert();
  for (int k=1; k<= columns; k++){
      *element(i,k) = (*element(i,k))*help;
  }
}

QString restMatrix::print(int i, int j){
    return element(i,j)->print();
}

bool restMatrix::invert(restMatrix &rm){
    if (rm.lines != rm.columns){
        return false;
    }
    else{
      MaceRest eins(1,charac), zero(0,charac);
      restMatrix help(rm.lines, 2*rm.columns,charac);

      for(int i = 1; i <= rm.lines; i++){
        *help.element(i,i+rm.lines) = eins;
      }

      for(int i = 1; i <= rm.lines; i++){
        for(int j = 1; j <= rm.lines; j++){
          *help.element(i,j) = *rm.element(i,j);
        }
      }

      help.gauss();

      for (int i = 1; i <= rm.lines; i++){
          if(*help.element(i,i) ==zero) return false;
        }

      for(int i = 1; i <= rm.lines; i++){
          for(int j = 1; j <= rm.lines; j++){
            *rm.element(i,j) = *help.element(i,j+rm.lines);
          }
      }
    }
    return true;
}

restMatrix restMatrix::image() {
    restMatrix tmp(*this);
    int rk = tmp.rank();
    if (rk == 0) rk = 1;
    restMatrix res(lines,rk,charac);

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

restMatrix restMatrix::solve(restMatrix b){
    restMatrix tmp(*this);
    MaceRest zero(charac);

    MaceRest null(charac);
    MaceRest minusEins(charac-1,charac);

    ///pose the system//////////////////////////////////////
    restMatrix help(tmp.lines, tmp.columns+b.columns,charac);
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

MaceRest restMatrix::det(){
    int clm= 1;
    int help;
    int i;

    MaceRest div, zero(charac);

    MaceRest minusOne(charac-1, charac);
    MaceRest correct(1, charac);

    if(lines != columns){return zero;}
    else{
      for (int ln = 1; ln <= lines && ln <= columns; ln++){

        //find a pivot
        while(clm <= columns){
          help = ln;
          while(help < lines){
            if (*element(help,clm)!= zero){break;}
            help++;
          }
          if (*element(help,clm)!=zero){break;}
          else{clm++;}
        }

        //if one has found a pivot, take it into the right line and eliminate all other entries of its column.
        if (help <= lines && clm <=columns){

          if (help > ln){
            changeLines(help,ln);
            correct = correct*minusOne;
          }

          div = *element(ln,clm);
          correct = correct*div;
          normLine(ln,clm);
          for (i =ln+1 ; i <= lines; i++){
            if (*element(i,clm) != zero){
              addLines(i,ln,clm);
            }
          }

          clm++;
       }
     }

      for (i=1; i<=columns; i++){
          correct = correct*(*element(i,i));
      }
    return correct;
  }
}

MaceRest restMatrix::trace(){
    restMatrix tmp(*this);
    MaceRest res(charac);
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

restMatrix restMatrix::copy(restMatrix m){
    restMatrix res(*this);
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

//as static func in linADist
restPoly restMatrix::charPoly(){
    restPoly res;
    return res;
}


restPoly restMatrix::miniPoly(){
    int m= 1, diff = 1, rank, oldRank=0, a=1, b;
    MaceRest one(1,charac), test(1,charac), minusOne(charac-1,charac), zero(charac);
    restPoly p(one), q, r(minusOne);
    restMatrix tmp(*this),help;
    restMatrix B(tmp.lines*tmp.lines,1+tmp.columns,charac), I(tmp.lines,tmp.columns,charac);

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
           q= q.mult(*B.element(b-1,a));
           p= p+q;
           b--;
       }

       return p;
}

restMatrix restMatrix::null() {
    int l, rk;
    rk = rank();
    MaceInt mOne;
    mpz_sub_ui(mOne.entry.get_mpz_t(),charac.entry.get_mpz_t(),1);
    if (rk == columns) rk = columns - 1;
    restMatrix tmp(*this);
    restMatrix res(columns,columns,charac);
    restMatrix zeroM(columns,columns-rk,charac);
    MaceRest zero(0,charac), minusOne(mOne,charac), z(charac);

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


QString restMatrix::interpretation(){

    restMatrix tmp(*this);

    ///check for empty set as result///////////////////////////////////////////////////
    int l = tmp.lines+1 ,c;
    MaceRest z(charac), w(charac), zero(charac), minusOne(charac-1,charac);
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
        restMatrix res(tmp.columns-1, tmp.columns,charac);

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
              qres = qres.append(z.print());
              qres = qres.append("</span></th></tr>");
              qres = qres.append("<tr><th><span style=\"font-weight:200\">");
              posMem++;
              z=*tmp.element(i,posMem);
            }
                    qres = qres.append(tmp.element(i,tmp.columns)->print());
                    qres = qres.append("</span></th></tr>");
            posMem++;
          }
              }

          for (int i = posMem; i <tmp.columns; i++){
        qres = qres.append("<tr><th><span style=\"font-weight:200\">");
        qres = qres.append(zero.print());
        qres = qres.append("</span></th></tr>");
          }
          qres= qres.append("</table></th></tr></table></th>");
            }
            else{
          qres= qres.append("<th><table border=1><tr><th><table>");
              for (int i = 1; i< tmp.columns;i++){
        qres = qres.append("<tr><th><span style=\"font-weight:200\">");
        qres = qres.append(zero.print());
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
                                    if (*tmp.element(lns,coln)!= zero){lns++;(*res.element(coln,j))=(*tmp.element(coln-adder,j));}
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
                        qres = qres.append(res.element(i,j)->print());
                        qres = qres.append("</span></th></tr>");
                    }
                    qres= qres.append("</table></th></tr></table></th>");
                }
            }
            qres= qres.append("</tr></table>");
        }
    return qres;
}*/
