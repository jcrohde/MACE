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

#include "rat.h"

rat::rat()
{
  unboundInt one(1);
  positiv = true;
  count = count.translate(0);
  denom = one;
}

rat::rat(unboundInt i){
  unboundInt one(1);
  positiv = true;
  count = i;
  denom = one;
}

rat::rat(unboundInt i, unboundInt j){
  positiv = true;
  count = i;
  denom = j;
}

QString rat::print(){
    QString res;
    double help = denom.toDouble(), b = count.toDouble();
    help = b/help;
    if (!positiv){help = -help;}
    res = res.number(help);
    return res;
}

rat rat::normalize(){
    QList<int>::iterator iter;
    rat tmp(*this), res;
    unboundInt help, q, c= tmp.count, d = tmp.denom, zero;

    iter = c.entries.end();
    iter--;
    while (*iter == 0 && c.entries.length()>1){
        c = c.cut();
        iter = c.entries.end();
        iter--;
    }

    iter = d.entries.end();
    iter--;
    while (*iter == 0 && d.entries.length()>1){
        d = d.cut();
        iter = d.entries.end();
        iter--;
    }

    if (c!=zero){
        if (d>c){help = c; c = d; d = help;}

        while (d> zero){
                    q = c/d;
                    help = c-(q*d);

                    iter = help.entries.end();
                    iter--;
                    while (*iter == 0 && help.entries.length()>1){
                        help = help.cut();
                        iter = help.entries.end();
                        iter--;
                    }
                    c = d;
                    d = help;
                }
        help = c;
        c = tmp.count;
        d = tmp.denom;

        c = c/help;
        d = d/help;

        res.count = c;
        res.denom = d;
   }
   res.positiv = tmp.positiv;
   return res;
}
