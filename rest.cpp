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

#include "rest.h"

rest::rest()
{
    val = 0;
    mod = 2;
}

rest::rest(int i){
    val = 0;
    mod = i;
}

rest::rest(int i, int j){
    i = i%j;
    if (i < 0){i = i+j;}
    val = i;
    mod = j;
}

void rest::normalize(){
    val = val % mod;
    if (val < 0){val += mod;}
}

QString rest::print(){
    QString str;
    int r = val;
    r = r % mod;
    if (r < 0){r += mod;}
    str=str.number(r);
    return str;
}
