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

#include "genmatrix.h"
#include "math/kernel/reader.h"

genMatrix::genMatrix()
{
    valid = true;
    lines =1;
    columns = 1;
}

genMatrix::genMatrix(int a, int b): lines(a), columns(b){

}

QString genMatrix::print(unsigned int precision) {
    if (precision == 0) return printMatrix();
    else return "matrix";
}

QString genMatrix::printMatrix() {
    QString help, str = "matrix(";
    help = help.number(lines);
    str = str.append(help);
    str = str.append(",");
    help = help.number(columns);
    str = str.append(help);
    str = str.append("(");
    for (int i = 1; i <= lines; i++) {
        for (int j = 1; j <= columns; j++) {
            str = str.append(print(i,j));
            if (i < lines || j < columns) str = str.append(",");
        }
    }
    str = str.append("))");
    return str;
}

QString genMatrix::toHtml(){
    QString res, secret, str;
    secret = secret.number(lines);
    secret = secret.append(",");
    res = res.number(columns);
    secret = secret.append(res);
    secret = secret.append(",");

    res= "<table border=1><tr><th><table>";
    for (int i= 1; i<= lines; i++){
        res= res.append("<tr>");
        for (int j= 1; j<= columns; j++){

              res= res.append("<th><span style=\"font-weight:200\">");
              str = print(i,j);
              powerCorrect(str);
              res = res.append(str);
              res= res.append("</span></th>");

              secret = secret.append(str);
              secret = secret.append(",");
        }
        res= res.append("</tr>");
    }

    res= res.append("</table></th></tr></table>");

    secret = secret.prepend("<!--");
    secret = secret.append("-->");

    res = res.append(secret);

    return res;
}

void genMatrix::gauss(){
  int clm= 1;
  int help;
  int i;

  for (int ln = 1; ln <= lines && ln <= columns; ln++){

    //find a pivot
    while(clm <= columns){
      help = ln;
      while(help < lines){
        if (!elemZero(help,clm)){break;}
        help++;
      }
      if (!elemZero(help,clm)){break;}
      else{clm++;}
    }
    //if one has found a pivot, take it into the right line and eliminate all other entries of its column.
    if (help <= lines && clm <=columns){

      if (help > ln){
        changeLines(help,ln);
      }

      normLine(ln,clm);

      for (i =1 ; i < ln; i++){
          if (!elemZero(i,clm)) addLines(i,ln,clm);
      }

      for (i =ln+1 ; i <= lines; i++){
        if (!elemZero(i,clm)) addLines(i,ln,clm);
      }

      clm++;
    }
  }

}

int genMatrix::rank(){
    gauss();

    int lin = 1, col = 1;

    while(lin <= lines && col <= columns){
        if(!elemZero(lin,col)){
            lin++;
        }
        else{
            col++;
        }
    }

    lin--;
    return lin;
}

void genMatrix::debugPrint(){
    QString res;
    for (int i = 1; i <=lines; i++) {
        res = "";
        for (int j = 1; j <= columns; j++) {
            res=res.append(print(i,j));
            res=res.append(" ");
        }
    }
}
