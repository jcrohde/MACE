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

#ifndef PARSER_H
#define PARSER_H
#include "math.h"
#include "polynomial.h"
#include "matrix.h"
#include "algcplx.h"


QString intsToString(QList<int> ints){
    QString res ="";
    QString help;
    for(QList<int>::iterator iter = ints.begin(); iter != ints.end(); iter++){
        help=help.number(*iter);
        res.append(help);
        res.append(",");
    }
    res = res.left(res.size()-1);
    return res;
}

void myStrToClass(QString str, int *ptr, int c){
    *ptr = str.toInt();
}

void myStrToClass(QString str, float *ptr, int c){
    *ptr = str.toFloat();
}



void myStrToClass(QString str, complex *ptr, int c){
    int count = 0, pos;
    complex coeff(1,0);
    if(str.size()== 0){
        complex zero;
        *ptr = zero;
    }
    else{
      QString help;
      while (str.size()>0){
          pos = str.indexOf("i");
          if (pos == -1) {
              coeff.real *= str.toDouble();
              str ="";
          }
          else {
              count++;
              if (pos > 0){
                  help = str.left(pos);
                  coeff.real *= help.toDouble();
              }
              str = str.right(str.size()-pos -1);
          }
      }
      complex z;
      z.real = coeff.real;
      if (count > 0){
          complex c;
          if (count % 4 == 0){c.real =1;}
          else if (count % 4 == 1){c.imag =1;}
          else if (count % 4 == 2){c.real =-1;}
          else{c.imag =-1;}
          z = c*z;
      }
      *ptr = z;
  }
}

void myStrToClass(QString str, polynomial *ptr, int c){
    int count = 0, pos;
    complex coeff(1,0);
    complex chelp;
    if(str.size()== 0){
        polynomial p(chelp);
        *ptr = p;
    }
    else{
      QString help;
      while (str.size()>0){
          pos = str.indexOf("x");
          if (pos == -1) {
              myStrToClass(str, &chelp,10);
              coeff = coeff*chelp;
              str ="";
          }
          else {
              count++;
              if (pos > 0){
                  help = str.left(pos);
                  myStrToClass(help, &chelp,10);
                  coeff = coeff*chelp;
              }
              str = str.right(str.size()-pos -1);
          }
      }

      polynomial p(coeff);
      p.shift(count);
      *ptr = p;
    }
}

void myStrToClass(QString str, double *ptr, int c){
*ptr = str.toDouble();
}

void myStrToClass(QString str, rat *ptr, int c){
    QString help("1"), left, right;
    if (str.indexOf(".")>-1){
        int index = str.size()-str.indexOf(".") -1;
        left = str.left(str.indexOf("."));
        right = str.right(str.size()-str.indexOf(".") -1);
        str = left.append(right);
        for (int i = 0; i <index; i++){
            help = help.append("0");
        }
        rat res(str,help);
        res = res.normalize();
        *ptr = res;
    }
    else{
        unboundInt ubint(str);
        rat res(ubint);
        *ptr = res;
    }
}



void myStrToClass(QString str, rest *ptr, int c){
    rest res(c);
    res.val = str.toInt();
    res.val = res.val;
    if(res.val < 0){res.val += res.mod;}
    *ptr=res;
}

void myStrToClass(QString str, restpolynomial *ptr, int c){
    int count = 0, pos;
    rest re(c);
    if(str.size()== 0){
        restpolynomial p(re);
        *ptr = p;
    }
    else{
      re.val = 1;
      int coeff = 1, chelp;
      QString help;
      while (str.size()>0){
          pos = str.indexOf("x");
          if (pos == -1) {
              myStrToClass(str, &chelp,c);
              coeff = coeff*chelp;
              str ="";
          }
          else {
              count++;
              if (pos > 0){
                  help = str.left(pos);
                  myStrToClass(help, &chelp,c);
                  coeff = coeff*chelp;
              }
              str = str.right(str.size()-pos -1);
          }
      }
      re.val = coeff;
      restpolynomial p(re);
      p.shift(count);
      *ptr = p;
  }
}

void myStrToClass(QString str, algCplx *ptr, int c){
    int count = 0, pos;
    unboundInt one("1"), null;
    algCplx coeff(one,null);
    if(str.size()== 0){
        algCplx zero;
        *ptr = zero;
    }
    else{
      QString help;
      while (str.size()>0){
          pos = str.indexOf("i");
          if (pos == -1) {
              myStrToClass(str, &coeff.real,0);
              str ="";
          }
          else {
              count++;
              if (pos > 0){
                  help = str.left(pos);
                  myStrToClass(help, &coeff.real,0);
              }
              str = str.right(str.size()-pos -1);
          }
      }
      algCplx z;
      z.real = coeff.real;
      if (count > 0){
          algCplx c;
          if (count % 4 == 0){c.real =one;}
          else if (count % 4 == 1){c.imag =one;}
          else if (count % 4 == 2){c.real.count =one; c.real.positiv = false;}
          else{c.imag.count =one; c.real.positiv = false;}
          z = c*z;
      }
      *ptr = z;
  }
}

void myStrToClass(QString str, algPoly *ptr, int c){
    int count = 0, pos;
    algCplx coeff(1,0);
    algCplx chelp;
    if(str.size()== 0){
        algPoly p(chelp);
        *ptr = p;
    }
    else{
      QString help;
      while (str.size()>0){
          pos = str.indexOf("x");
          if (pos == -1) {
              myStrToClass(str, &chelp,10);
              coeff = coeff*chelp;
              str ="";
          }
          else {
              count++;
              if (pos > 0){
                  help = str.left(pos);
                  myStrToClass(help, &chelp,10);
                  coeff = coeff*chelp;
              }
              str = str.right(str.size()-pos -1);
          }
      }

      algPoly p(coeff);
      p.shift(count);
      *ptr = p;
    }
}


double power(double a, double x, QString ing){
    return exp(x*log(a));
}

complex power(complex p1, complex n, QString ing){
    int i  = n.real+ 0.0001;
    complex res(1,0);
    for ( int k = 1; k <= i; k++){ res = res* p1;}
    return res;
}

algCplx power(algCplx p1, algCplx n, QString ing){
    return p1;
}


polynomial power(polynomial p1, polynomial n, QString ing){
    complex h(0.0001,0);
    h = h+n.leader();
    int i  = h.real;
    if (ing.right(1)== "x"){p1.shift(i-1);}
    else{p1 = power(p1,i);}
    return p1;
}

algPoly power(algPoly p1, algPoly n, QString ing){
    algCplx h=n.leader();
    int i  = *h.real.count.entries.begin();
    if (ing.right(1)== "x"){p1.shift(i-1);}
    else{p1 = power(p1,i);}
    return p1;
}

rest power(rest p1, rest n, QString ing){
    int i  = n.val;
    return power(p1,i);
}
rat power(rat p1, rat n, QString ing){
    return p1;
}

restpolynomial power(restpolynomial p1, restpolynomial n, QString ing){
    rest h = n.leader();
    int i  = h.val;
    if (ing.right(1)== "x"){p1.shift(i-1);}
    else{p1 = power(p1,i);}
    return p1;
}

template <class T>  void realParsNComp(QString str, T *ptr, int c){
    QString ch="blub", help, sign, tester;
    bool noBrack = true;
    int index =-1, count = 0, brack = 0;
    T num, num1, ans;

        help = str;

        while (help.size() > 0){
            sign = help.left(1);
            help = help.right(help.size()-1);

            if (sign.indexOf("(")> -1){
                tester = str.left(count);
                tester = tester.right(1);
                if (count > 0 && tester != "(" && tester != "+" && tester != "-" && tester != "*" && tester != "/" && tester != "^"){
                    tester = str.left(count);
                    str = str.right(str.size()-count);
                    tester.append("*");
                    str.prepend(tester);
                    count++;
                }
            }
            if (sign.indexOf(")")> -1){
                tester = str.left(count+2);
                tester = tester.right(1);
                if (count < str.size() && tester != ")" && tester != "+" && tester != "-" && tester != "*" && tester != "/" && tester != "^"){
                    tester = str.left(count+1);
                    str = str.right(str.size()-count-1);
                    tester.append("*");
                    str.prepend(tester);
                    count++;
                }
            }
           count++;
        }

        count = 0;

        help = str;

        while (help.size() > 0){
            sign = help.left(1);
            help = help.right(help.size()-1);

            if (sign.indexOf("(")> -1){brack++; noBrack = false;}
            if (sign.indexOf(")")> -1){brack--;}

            if (brack == 0){
                if(sign.indexOf("+")>-1){index = count;ch="+";}
                if(ch.indexOf("+")==-1 && sign.indexOf("-")>-1){index = count;ch="-";}
                if(ch.indexOf("+")==-1 && ch.indexOf("-")==-1 && sign.indexOf("*")>-1){index = count;ch="*";}
                if(ch.indexOf("+")==-1 && ch.indexOf("-")==-1 && ch.indexOf("*")==-1 && sign.indexOf("/")>-1){index = count;ch="/";}
                if(ch.indexOf("+")==-1 && ch.indexOf("-")==-1 && ch.indexOf("*")==-1 && ch.indexOf("/")==-1 && sign.indexOf("^")>-1){index = count;ch="^";}
            }

            count++;
        }

        if (index ==-1){
            if (noBrack){myStrToClass(str,ptr,c);}
            else{
                str = str.right(str.size()-1);
                str = str.left(str.size()-1);
                realParsNComp(str,ptr, c);
            }
        }
        else{
            QString str2;
            str2=str.left(index);
            realParsNComp(str2,&num, c);
            index=str.length()-index-1;
            str=str.right(index);
            realParsNComp(str,&num1,c);
            if(ch=="^"){*ptr = power(num,num1,str2);}
            if(ch=="+"){*ptr = num+num1;}
            if(ch=="-"){*ptr = num-num1;}
            if(ch=="*"){*ptr = num*num1;}
            if(ch=="/"){*ptr = num/num1;}
        }
}


matrix strToMatrix(QString str){
    int a, b;
    complex z;
    QString help= str.left(str.indexOf(","));
    a = help.toInt();
    str = str.right(str.size()-1-str.indexOf(","));

    help= str.left(str.indexOf(","));
    b = help.toInt();
    str = str.right(str.size()-1-str.indexOf(","));

    matrix res(a,b);

    for (int i= 1; i<= a;i++){
        for (int j = 1; j<=b; j++){
            if (str.indexOf(",")== -1){help= str;}
            else{
                help = str.left(str.indexOf(","));
                str = str.right(str.size()-1-str.indexOf(","));
            }
            realParsNComp(help, &z, 10);
            *res.element(i,j) = z;
        }
    }
    return res;
}


algMatrix strToAlgMatrix(QString str){
    int a, b;
    algCplx z;
    QString help= str.left(str.indexOf(","));
    a = help.toInt();
    str = str.right(str.size()-1-str.indexOf(","));

    help= str.left(str.indexOf(","));
    b = help.toInt();
    str = str.right(str.size()-1-str.indexOf(","));

    algMatrix res(a,b);

    for (int i= 1; i<= a;i++){
        for (int j = 1; j<=b; j++){
            if (str.indexOf(",")== -1){help= str;}
            else{
                help = str.left(str.indexOf(","));
                str = str.right(str.size()-1-str.indexOf(","));
            }
            realParsNComp(help, &z, 10);
            *res.element(i,j) = z;
        }
    }
    return res;
}

QString matrixToHtml(matrix mat){
    QString res= "<table border=1><tr><th><table>";
    complex z;

    for (int i= 1; i<= mat.lines; i++){
        res= res.append("<tr>");
        for (int j= 1; j<= mat.columns; j++){
              res= res.append("<th><span style=\"font-weight:200\">");
              z= *mat.element(i,j);
              res=res.append(z.print());
              res= res.append("</span></th>");
        }
        res= res.append("</tr>");
    }

    res= res.append("</table></th></tr></table>");
    return res;
}

QString algMatrixToHtml(algMatrix mat){
    QString res= "<table border=1><tr><th><table>";
    algCplx z;

    for (int i= 1; i<= mat.lines; i++){
        res= res.append("<tr>");
        for (int j= 1; j<= mat.columns; j++){
              res= res.append("<th><span style=\"font-weight:200\">");
              z= *mat.element(i,j);
              res=res.append(z.print());
              res= res.append("</span></th>");
        }
        res= res.append("</tr>");
    }

    res= res.append("</table></th></tr></table>");
    return res;
}


restMatrix strToRestMatrix(QString str, int charac){
    int a, b;
    int z;
    QString help= str.left(str.indexOf(","));
    a = help.toInt();
    str = str.right(str.size()-1-str.indexOf(","));

    help= str.left(str.indexOf(","));
    b = help.toInt();
    str = str.right(str.size()-1-str.indexOf(","));

    restMatrix res(a,b,charac);

    for (int i= 1; i<= a;i++){
        for (int j = 1; j<=b; j++){
            if (str.indexOf(",")== -1){help= str;}
            else{
                help = str.left(str.indexOf(","));
                str = str.right(str.size()-1-str.indexOf(","));
            }
            realParsNComp(help, &z, 10);
            res.element(i,j)->val = z;
        }
    }
    res.normalize();
    return res;
}

QString restMatrixToHtml(restMatrix mat){
    QString help, res= "<table border=1><tr><th><table>";
    int z;

    for (int i= 1; i<= mat.lines; i++){
        res= res.append("<tr>");
        for (int j= 1; j<= mat.columns; j++){
              res= res.append("<th><span style=\"font-weight:200\">");
              z= mat.element(i,j)->val;
              help = help.number(z);
              res=res.append(help);
              res= res.append("</span></th>");
        }
        res= res.append("</tr>");
    }

    res= res.append("</table></th></tr></table>");
    return res;
}


QString writeMatOp(matrix left, QString Op, matrix right){
    QString res = "<table><tr><th>";
    res = res.append(matrixToHtml(left));
    res = res.append("</th><th><table><tr><th>");
    for (int i= 0; i < (left.lines)/2; i++){
        res = res.append("</th></tr><tr><th>");
    }
    res = res.append("<span style=\"font-weight:200\">");
    res = res.append(Op);
    res = res.append("</span>");
    res = res.append("</th></tr>");
    res = res.append("</table></th><th>");
    res = res.append(matrixToHtml(right));
    res = res.append("</th></tr></table>");
    return res;
}

QString writeAlgMatOp(algMatrix left, QString Op, algMatrix right){
    QString res = "<table><tr><th>";
    res = res.append(algMatrixToHtml(left));
    res = res.append("</th><th><table><tr><th>");
    for (int i= 0; i < (left.lines)/2; i++){
        res = res.append("</th></tr><tr><th>");
    }
    res = res.append("<span style=\"font-weight:200\">");
    res = res.append(Op);
    res = res.append("</span>");
    res = res.append("</th></tr>");
    res = res.append("</table></th><th>");
    res = res.append(algMatrixToHtml(right));
    res = res.append("</th></tr></table>");
    return res;
}

QString writeRestMatOp(restMatrix left, QString Op, restMatrix right){
    QString res = "<table><tr><th>";
    res = res.append(restMatrixToHtml(left));
    res = res.append("</th><th><table><tr><th>");
    for (int i= 0; i < (left.lines)/2; i++){
        res = res.append("</th></tr><tr><th>");
    }
    res = res.append("<span style=\"font-weight:200\">");
    res = res.append(Op);
    res = res.append("</span>");
    res = res.append("</th></tr>");
    res = res.append("</table></th><th>");
    res = res.append(restMatrixToHtml(right));
    res = res.append("</th></tr></table>");
    return res;
}

 QString writeMatSingOp(matrix left, QString Op, QString right){
    QString res = "<table><tr><th>";
    res = res.append(matrixToHtml(left));
    res = res.append("</th><th><table><tr><th>");
    for (int i= 0; i < (left.lines)/2; i++){
        res = res.append("</th></tr><tr><th><span style=\"font-weight:200\">");
    }
    res = res.append(Op);
    res = res.append(right);
    res = res.append("</span></th></tr>");
    res = res.append("</table></th><th>");
    res = res.append("</th></tr></table>");
    return res;
}

 QString writeAlgMatSingOp(algMatrix left, QString Op, QString right){
    QString res = "<table><tr><th>";
    res = res.append(algMatrixToHtml(left));
    res = res.append("</th><th><table><tr><th>");
    for (int i= 0; i < (left.lines)/2; i++){
        res = res.append("</th></tr><tr><th><span style=\"font-weight:200\">");
    }
    res = res.append(Op);
    res = res.append(right);
    res = res.append("</span></th></tr>");
    res = res.append("</table></th><th>");
    res = res.append("</th></tr></table>");
    return res;
}

 QString writeRestMatSingOp(restMatrix left, QString Op, QString right){
    QString res = "<table><tr><th>";
    res = res.append(restMatrixToHtml(left));
    res = res.append("</th><th><table><tr><th>");
    for (int i= 0; i < (left.lines)/2; i++){
        res = res.append("</th></tr><tr><th><span style=\"font-weight:200\">");
    }
    res = res.append(Op);
    res = res.append(right);
    res = res.append("</span></th></tr>");
    res = res.append("</table></th><th>");
    res = res.append("</th></tr></table>");
    return res;
}


QString writeGauss(matrix left, matrix vector, matrix result){
    complex z;
    QString res = "<table><tr><th><table border=1><tr><th><table>";


        for (int i= 1; i<= left.lines; i++){
            res= res.append("<tr>");
            for (int j= 1; j<= left.columns; j++){
                  res= res.append("<th><span style=\"font-weight:200\">");
                  z= *left.element(i,j);
                  res=res.append(z.print());
                  res= res.append("</span></th>");
            }
            res= res.append("</tr>");
        }

        res= res.append("</table></th><th><table>");
                      for (int i= 1; i<= vector.lines; i++){
                            res= res.append("<tr>");
                            for (int j= 1; j<= vector.columns; j++){
                                  res= res.append("<th><span style=\"font-weight:200\">");
                                  z= *vector.element(i,j);
                                  res=res.append(z.print());
                                  res= res.append("</span></th>");
                            }
                            res= res.append("</tr>");
                        }

        res = res.append("</table></th></tr></table></th><th><table><tr><th>");
        for (int i= 0; i < (left.lines)/2; i++){
            res = res.append("</th></tr><tr><th>");
        }

        res = res.append("<span style=\"font-weight:200\">after Gauss algorithm</span></th></tr>");
        res = res.append("</table></th><th>");

        res = res.append("<table border=1><tr><th><table>");

        for (int i= 1; i<= result.lines; i++){
            res= res.append("<tr>");
            for (int j= 1; j< result.columns; j++){
                  res= res.append("<th><span style=\"font-weight:200\">");
                  z= *result.element(i,j);
                  res=res.append(z.print());
                  res= res.append("</span></th>");
            }
            res= res.append("</tr>");
        }

        res= res.append("</table></th><th><table>");
                            for (int i= 1; i<= result.lines; i++){
                                  res= res.append("<tr><th><span style=\"font-weight:200\">");
                                  z= *result.element(i,result.columns);
                                  res=res.append(z.print());
                                  res= res.append("</span></th></tr>");
                            }
         res= res.append("</table></th></tr></table></th></tr></table>");

    return res;
}


QString writeRestGauss(restMatrix left, restMatrix vector, restMatrix result, int charac){
    rest z(charac);
    QString res = "<table><tr><th><table border=1><tr><th><table>";


        for (int i= 1; i<= left.lines; i++){
            res= res.append("<tr>");
            for (int j= 1; j<= left.columns; j++){
                  res= res.append("<th><span style=\"font-weight:200\">");
                  z= *left.element(i,j);
                  res=res.append(z.print());
                  res= res.append("</span></th>");
            }
            res= res.append("</tr>");
        }

        res= res.append("</table></th><th><table>");
                      for (int i= 1; i<= vector.lines; i++){
                            res= res.append("<tr>");
                            for (int j= 1; j<= vector.columns; j++){
                                  res= res.append("<th><span style=\"font-weight:200\">");
                                  z= *vector.element(i,j);
                                  res=res.append(z.print());
                                  res= res.append("</span></th>");
                            }
                            res= res.append("</tr>");
                        }

        res = res.append("</table></th></tr></table></th><th><table><tr><th>");
        for (int i= 0; i < (left.lines)/2; i++){
            res = res.append("</th></tr><tr><th>");
        }

        res = res.append("<span style=\"font-weight:200\">after Gauss algorithm</span></th></tr>");
        res = res.append("</table></th><th>");

        res = res.append("<table border=1><tr><th><table>");

        for (int i= 1; i<= result.lines; i++){
            res= res.append("<tr>");
            for (int j= 1; j< result.columns; j++){
                  res= res.append("<th><span style=\"font-weight:200\">");
                  z= *result.element(i,j);
                  res=res.append(z.print());
                  res= res.append("</span></th>");
            }
            res= res.append("</tr>");
        }

        res= res.append("</table></th><th><table>");
                            for (int i= 1; i<= result.lines; i++){
                                  res= res.append("<tr><th><span style=\"font-weight:200\">");
                                  z= *result.element(i,result.columns);
                                  res=res.append(z.print());
                                  res= res.append("</span></th></tr>");
                            }
         res= res.append("</table></th></tr></table></th></tr></table>");

    return res;
}

QString writeAlgGauss(algMatrix left, algMatrix vector, algMatrix result){
    algCplx z;
    QString res = "<table><tr><th><table border=1><tr><th><table>";


        for (int i= 1; i<= left.lines; i++){
            res= res.append("<tr>");
            for (int j= 1; j<= left.columns; j++){
                  res= res.append("<th><span style=\"font-weight:200\">");
                  z= *left.element(i,j);
                  res=res.append(z.print());
                  res= res.append("</span></th>");
            }
            res= res.append("</tr>");
        }

        res= res.append("</table></th><th><table>");
                      for (int i= 1; i<= vector.lines; i++){
                            res= res.append("<tr>");
                            for (int j= 1; j<= vector.columns; j++){
                                  res= res.append("<th><span style=\"font-weight:200\">");
                                  z= *vector.element(i,j);
                                  res=res.append(z.print());
                                  res= res.append("</span></th>");
                            }
                            res= res.append("</tr>");
                        }

        res = res.append("</table></th></tr></table></th><th><table><tr><th>");
        for (int i= 0; i < (left.lines)/2; i++){
            res = res.append("</th></tr><tr><th>");
        }

        res = res.append("<span style=\"font-weight:200\">after Gauss algorithm</span></th></tr>");
        res = res.append("</table></th><th>");

        res = res.append("<table border=1><tr><th><table>");

        for (int i= 1; i<= result.lines; i++){
            res= res.append("<tr>");
            for (int j= 1; j< result.columns; j++){
                  res= res.append("<th><span style=\"font-weight:200\">");
                  z= *result.element(i,j);
                  res=res.append(z.print());
                  res= res.append("</span></th>");
            }
            res= res.append("</tr>");
        }

        res= res.append("</table></th><th><table>");
                            for (int i= 1; i<= result.lines; i++){
                                  res= res.append("<tr><th><span style=\"font-weight:200\">");
                                  z= *result.element(i,result.columns);
                                  res=res.append(z.print());
                                  res= res.append("</span></th></tr>");
                            }
         res= res.append("</table></th></tr></table></th></tr></table>");

    return res;
}

#endif // PARSER_H
