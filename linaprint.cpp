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

#include "linaprint.h"

QString linAPrint::writeMatOp(genMatrix *left, QString Op, genMatrix *right){
    QString res = "<table><tr><th>";
    res = res.append(left->toHtml());
    res = res.append("</th><th><table><tr><th>");
    for (int i= 0; i < (left->lines)/2; i++){
        res = res.append("</th></tr><tr><th>");
    }
    res = res.append("<span style=\"font-weight:200\">");
    res = res.append(Op);
    res = res.append("</span>");
    res = res.append("</th></tr>");
    res = res.append("</table></th><th>");
    res = res.append(right->toHtml());
    res = res.append("</th></tr></table>");
    return res;
}

QString linAPrint::writeMatSingOp(genMatrix *left, QString Op, QString right){
   QString res = "<table><tr><th>";
   res = res.append(left->toHtml());
   res = res.append("</th><th><table><tr><th>");
   for (int i= 0; i < (left->lines)/2; i++){
       res = res.append("</th></tr><tr><th><span style=\"font-weight:200\">");
   }
   res = res.append(Op);
   res = res.append(right);
   res = res.append("</span></th></tr>");
   res = res.append("</table></th><th>");
   res = res.append("</th></tr></table>");
   return res;
}

QString linAPrint::writeScalarMatOp(QString Op, genMatrix *right){
    QString res = "<table><tr><th><table><tr><th>";
    for (int i= 0; i < (right->lines)/2; i++){
        res = res.append("</th></tr><tr><th>");
    }
    res = res.append("<span style=\"font-weight:200\">");
    res = res.append(Op);
    res = res.append("</span>");
    res = res.append("</th></tr>");
    res = res.append("</table></th><th>");
    res = res.append(right->toHtml());
    res = res.append("</th></tr></table>");
    return res;
}

QString linAPrint::writeGauss(genMatrix *left, genMatrix *vector, genMatrix *result){
    QString res = "<table><tr><th><table border=1><tr><th><table>";


        for (int i= 1; i<= left->lines; i++){
            res= res.append("<tr>");
            for (int j= 1; j<= left->columns; j++){
                  res= res.append("<th><span style=\"font-weight:200\">");

                  res=res.append(left->print(i,j));
                  res= res.append("</span></th>");
            }
            res= res.append("</tr>");
        }

        res= res.append("</table></th><th><table>");
                      for (int i= 1; i<= vector->lines; i++){
                            res= res.append("<tr>");
                            for (int j= 1; j<= vector->columns; j++){
                                  res= res.append("<th><span style=\"font-weight:200\">");

                                  res=res.append(vector->print(i,j));
                                  res= res.append("</span></th>");
                            }
                            res= res.append("</tr>");
                        }

        res = res.append("</table></th></tr></table></th>");
        res = res.append("<th><table><tr><th>");
        for (int i= 0; i < (left->lines)/2; i++){
            res = res.append("</th></tr><tr><th>");
        }

        res = res.append("<span style=\"font-weight:200\">after Gauss algorithm</span></th></tr>");
        res = res.append("</table></th><th>");

        res = res.append("<table border=1><tr><th><table>");

        for (int i= 1; i<= result->lines; i++){
            res= res.append("<tr>");
            for (int j= 1; j< result->columns; j++){
                  res= res.append("<th><span style=\"font-weight:200\">");
                  //z= *result.element(i,j);
                  res=res.append(result->print(i,j));
                  res= res.append("</span></th>");
            }
            res= res.append("</tr>");
        }

        res= res.append("</table></th><th><table>");
                            int k = result->columns;
                            for (int i= 1; i<= result->lines; i++){
                                  res= res.append("<tr><th><span style=\"font-weight:200\">");
                                  //z= *result.element(i,result.columns);
                                  res=res.append(result->print(i, k));
                                  res= res.append("</span></th></tr>");
                            }
         res= res.append("</table></th></tr></table></th></tr></table>");

    return res;
}
