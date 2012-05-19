/*
Copyright (C) 2012 Jan Christian Rohde

This file is part of MACE.

MACE is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MACE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with MACE. If not, see <http://www.gnu.org/licenses/>.
*/

#include "algmatrix.h"

algMatrix::algMatrix(){
    lines =1;
    columns = 1;
    algCplx zero;
    entries.append(zero);
}

algMatrix::algMatrix(int a, int b){
  lines =a;
  columns = b;
  algCplx zero;

  for (int i = 1; i <= a*b; i++){entries.append(zero);}
}


QList<algCplx>::Iterator algMatrix::element(int i, int j){
    QList<algCplx>::Iterator iter = entries.begin();
    for (int m = 1; m <= (((i-1)*columns)+(j-1));m++){
        iter++;
    }
    return iter;
}



algMatrix algMatrix::changeLines( int i, int j){
  algMatrix tmp(*this), res(lines,columns);
  res = res.copy(tmp);
  for (int k=1; k<= columns; k++){
    *res.element(i,k) = *tmp.element(j,k);
    *res.element(j,k) = *tmp.element(i,k);
  }
  return res;
}


algMatrix algMatrix::addLines( int i, int j, algCplx lambda){
  algMatrix tmp(*this), res(lines,columns);
  algCplx help;
  res = res.copy(tmp);
  for (int k=1; k<= columns; k++){
      help = *tmp.element(j,k);
      help = help*lambda;
      help = (*tmp.element(i,k))+help;
    *res.element(i,k) = help;
  }
  return res;
}


algMatrix algMatrix::multLine( int i, algCplx lambda){
  algMatrix tmp(*this), res(lines,columns);
  algCplx help;
  res = res.copy(tmp);
  for (int k=1; k<= columns; k++){
    help = *tmp.element(i,k);
    help = help*lambda;
    *res.element(i,k) = help;
  }
  return res;
}


algMatrix algMatrix::gauss(){
  int clm= 1;
  int help;
  int i;

  algCplx factor, div, zero, mem;

  algMatrix m(*this);
  algMatrix res(m.lines, m.columns);

  for (int x =1; x <= lines; x++){
      for (int y =1; y <= columns; y++){
          *res.element(x,y) = *m.element(x,y);
      }
  }

  for (int ln = 1; ln <= lines && ln <= columns; ln++){

    //find a pivot
    while(clm <= columns){
      help = ln;
      while(help < lines){
        if (*res.element(help,clm)!= zero){break;}
        help++;
      }
      if (*res.element(help,clm)!=zero){break;}
      else{clm++;}
    }

    //if one has found a pivot, take it into the right line and eliminate all other entries of its column.
    if (help <= lines && clm <=columns){

      if (help > ln){
        res = res.changeLines(help,ln);
      }
      
      div = *res.element(ln,clm);
      div = div/(div*div);
      res = res.multLine(ln,div);

      for (i =1 ; i < ln; i++){
        if (*res.element(i,clm) != zero){
          factor = *res.element(i,clm);
          factor = (factor-factor)-factor;
          res = res.addLines(i,ln,factor);
        }
      }

      for (i =ln+1 ; i <= lines; i++){
        if (*res.element(i,clm) != zero){
          factor = *res.element(i,clm);
          factor = (factor-factor)-factor;
          res = res.addLines(i,ln,factor);
        }
      }

      clm++;
    }
  }

  return res;
}

algMatrix algMatrix::invert(){
    algMatrix tmp(*this);
    if (tmp.lines != tmp.columns){
        algMatrix res(1,1);
        return res;
    }
    else{
      algCplx eins(1,0), zero(0,0);
      algMatrix help(tmp.lines, 2*tmp.columns);
      bool maxRk = true;

      for(int i = 1; i <= tmp.lines; i++){
        *help.element(i,i+tmp.lines) = eins;
      }

      for(int i = 1; i <= tmp.lines; i++){
        for(int j = 1; j <= tmp.lines; j++){
          *help.element(i,j) = *tmp.element(i,j);
        }
      }

      help = help.gauss();

      for (int i = 1; i <= tmp.lines; i++){
          if(*help.element(i,i) ==zero){maxRk = false; break;}
        }

      if (maxRk){
          algMatrix res(tmp.lines,tmp.columns);

          for(int i = 1; i <= tmp.lines; i++){
             for(int j = 1; j <= tmp.lines; j++){
                *res.element(i,j) = *help.element(i,j+tmp.lines);
             }
          }
          return res;
      }
      else{
          algMatrix res(1,1);
          return res;
      }

    }

}

algMatrix algMatrix::solve(algMatrix b){
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
    help = help.gauss();

    return help;
}

int algMatrix::rank(){
    algCplx zero;

    algMatrix tmp(*this);
    algMatrix help(tmp.lines,tmp.columns);

    for (int i=1; i<= tmp.lines; i++){
        for(int j = 1; j<= tmp.columns; j++){
            *help.element(i,j)=*tmp.element(i,j);
        }
    }

    help = help.gauss();

    int res=1;

    for(int coln = 1; coln <= tmp.columns; coln++){
        if (*help.element(res,coln)!=zero){res++;}
    }
    res--;
    return res;
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

    if (tmp.lines!=tmp.columns){return res;}
    else{
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
            myI.real.count = myI.real.count.translate(i);
            myI.real.positiv=false;
            q= q/myI;
            b= a;
            b= b.mult(q);
            res = res+b;
            for (int k = 1; k<= tmp.lines; k++){
                for (int j=1; j<=tmp.columns;j++){
                *B.element(k,j)=(*C.element(k,j))+(q*(*I.element(k,j)));
            }
            }

        }

        return res;
    }
}


algPoly algMatrix::miniPoly(){
    int m= 1, diff = 1, rank, oldRank=0, a=1, b;
    algCplx one(1,0), test(1,0), minusOne(-1,0), zero;
    algPoly p(one), q, r(minusOne);
    algMatrix tmp(*this);
    algMatrix B(tmp.lines*tmp.lines,1+tmp.columns), I(tmp.lines,tmp.columns);

    for (int i = 1; i<= tmp.lines; i++){
        *I.element(i,i)=one;
    }

    while(diff > 0 && m <= tmp.lines+1){
      for (int k= 1;k<= tmp.lines; k++){
          for (int j=1;j<=tmp.lines; j++){
              *B.element((tmp.lines)*(k-1)+j,m) = *I.element(k,j);
          }
      }

      rank = B.rank();
      diff = rank-oldRank;

      rank=oldRank;
      I=I*tmp;
      m++;
   }

   B = B.gauss();

   a=0;
   while (test != zero && a<=tmp.lines+1){
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
                        qres = qres.append(mem.print());
                        qres = qres.append("</span></th></tr>");
                    }
                    qres= qres.append("</table></th></tr></table></th>");
                }
            }
            qres= qres.append("</tr></table>");
        }


    return qres;
}

