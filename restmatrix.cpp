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

#include "restmatrix.h"

restMatrix::restMatrix(){
    lines =1;
    columns = 1;

    charac = 2;
    rest zero(2);
    entries.append(zero);
}

restMatrix::restMatrix(int c){
    lines =1;
    columns = 1;

    charac = c;
    rest zero(c);
    entries.append(zero);
}

restMatrix::restMatrix(int a, int b, int c){
  lines =a;
  columns = b;

  charac = c;
  rest zero(c);

  for (int i = 1; i <= a*b; i++){entries.append(zero);}
}

void restMatrix::normalize(){
    for(QList<rest>::Iterator iter = entries.begin(); iter != entries.end(); iter++){
      iter->normalize();
    }
}


QList<rest>::Iterator restMatrix::element(int i, int j){
    QList<rest>::Iterator iter = entries.begin();
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


restMatrix restMatrix::changeLines( int i, int j){
  restMatrix tmp(*this), res(lines,columns,charac);
  res = res.copy(tmp);
  for (int k=1; k<= columns; k++){
    *res.element(i,k) = *tmp.element(j,k);
    *res.element(j,k) = *tmp.element(i,k);
  }
  return res;
}


restMatrix restMatrix::addLines( int i, int j, rest lambda){
  restMatrix tmp(*this), res(lines,columns,charac);
  res = res.copy(tmp);
  for (int k=1; k<= columns; k++){
    *res.element(i,k) = *tmp.element(i,k)+((*tmp.element(j,k))*lambda);
  }
  return res;
}


restMatrix restMatrix::multLine( int i, rest lambda){
  restMatrix tmp(*this), res(lines,columns,charac);
  rest help(charac);
  res = res.copy(tmp);
  for (int k=1; k<= columns; k++){
    help = *tmp.element(i,k);
    *res.element(i,k) = help*lambda;
  }
  return res;
}


restMatrix restMatrix::gauss(){
  int clm= 1;
  int help;
  int i;

  rest factor(charac), div(charac), zero(charac), mem;

  restMatrix m(*this);
  restMatrix res(m.lines, m.columns,m.charac);

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
        mem = *res.element(help,clm);
        if (mem!= zero){break;}
        help++;
      }
      mem = *res.element(help,clm);
      if (mem!=zero){break;}
      else{clm++;}
    }

    //if one has found a pivot, take it into the right line and eliminate all other entries of its column.
    if (help <= lines && clm <=columns){

      if (help > ln){
        res = res.changeLines(help,ln);
      }
      mem = *res.element(ln,clm);
      if (!(mem + mem == mem)){
        div = *res.element(ln,clm);
        div = div/(div*div);
        res=res.multLine(ln,div);
      }

      for (i =1 ; i < ln; i++){
        mem = *res.element(i,clm);
        if (!(mem + mem == mem)){
          factor = *res.element(i,clm);
          factor = (factor-factor)-factor;
          res=res.addLines(i,ln,factor);
        }
      }

      for (i =ln+1 ; i <= lines; i++){
        mem = *res.element(i,clm);
        if (!(mem+ mem == mem)){
          factor = *res.element(i,clm);
          factor = (factor-factor)-factor;
          res=res.addLines(i,ln,factor);
        }
      }

      clm++;
    }
  }

  return res;
}

restMatrix restMatrix::invert(){
    restMatrix tmp(*this);
    if (tmp.lines != tmp.columns){
        restMatrix res(1,1,charac);
        return res;
    }
    else{
      rest eins(charac), zero(0,charac);
      eins.val = 1;
      restMatrix help(tmp.lines, 2*tmp.columns,charac);
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

      if(maxRk){
        restMatrix res(tmp.lines,tmp.columns,charac);

        for(int i = 1; i <= tmp.lines; i++){
          for(int j = 1; j <= tmp.lines; j++){
            *res.element(i,j) = *help.element(i,j+tmp.lines);
          }
        }
        return res;
      }
      else{
          restMatrix res(1,1,charac);
          return res;
      }
    }

}

restMatrix restMatrix::solve(restMatrix b){
    restMatrix tmp(*this);
    rest zero(charac);
    int adder;

    rest null(charac);
    rest minusEins(charac-1,charac);

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
    help = help.gauss();

    return help;
}

int restMatrix::rank(){
    rest zero(charac);

    restMatrix tmp(*this);
    restMatrix help(tmp.lines,tmp.columns,tmp.charac);

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

rest restMatrix::det(){
    int clm= 1;
    int help;
    int i;

    rest factor, div, zero(charac);

    rest minusOne(charac-1, charac);
    rest correct(1, charac);

    restMatrix m(*this);
    if(m.lines!= m.columns){return zero;}
    else{
      restMatrix res(m.lines, m.columns, m.charac);

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
            correct = correct*minusOne;
          }


          div = *res.element(ln,clm);
          correct = correct*div;
          div = div/(div*div);
          res=res.multLine(ln,div);




          for (i =ln+1 ; i <= lines; i++){
            if (*res.element(i,clm) != zero){
              factor = *res.element(i,clm);
              factor = (factor-factor)-factor;
              res=res.addLines(i,ln,factor);
            }
          }

          clm++;
       }
     }

      for (i=1; i<=res.columns; i++){
          correct = correct*(*res.element(i,i));
      }
    return correct;
  }
}

rest restMatrix::trace(){
    restMatrix tmp(*this);
    rest res(charac);
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

restpolynomial restMatrix::charPoly(){
    rest one(1,charac), q(charac), help(charac), minusOne(charac-1,charac);
    restpolynomial res, b, a(one);
    restMatrix tmp(*this);
    int trx;
    int memo;
    algCplx algMemo;
    
    algMatrix red(tmp.lines,tmp.columns);
    
    for (int i =1; i <= tmp.lines; i++){
      for (int j =1; j <= tmp.lines; j++){
        memo = tmp.element(i,j)->val;
        algMemo.real.count = algMemo.real.count.translate(memo);
        *red.element(i,j)=algMemo;
      }
    }
    
    algPoly trick = red.charPoly();

   QList<algCplx>::Iterator ptr = trick.mons.begin();
    memo = ptr->real.count.toInt();
    if(!(ptr->real.positiv)){memo = -memo;}
    q.val = memo;
    b= a;
    b= b.mult(q);
    res = b;

    ptr++;
    while (ptr != trick.mons.end()){
        a.shift(1);

        memo = ptr->real.count.toInt();
        if(!(ptr->real.positiv)){memo = -memo;}
        q.val = memo;
        b= a;
        b= b.mult(q);
        res = res+b;

        ptr++;
    }

    return res;
}


restpolynomial restMatrix::miniPoly(){
    int m= 1, diff = 1, rank, oldRank=0, a=1, b;
    rest one(1,charac), test(1,charac), minusOne(charac-1,charac), zero(charac);
    restpolynomial p(one), q, r(minusOne);
    restMatrix tmp(*this);
    restMatrix B(tmp.lines*tmp.lines,1+tmp.columns,charac), I(tmp.lines,tmp.columns,charac);

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

QString restMatrix::interpretation(){

    restMatrix tmp(*this);

    ///check for empty set as result///////////////////////////////////////////////////
    int l = tmp.lines+1 ,c;
    rest z(charac), w(charac), zero(charac), minusOne(charac-1,charac);
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
}
