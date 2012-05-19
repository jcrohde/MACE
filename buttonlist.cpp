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

#include "buttonlist.h"


void buttonList::append(){
    if(next !=0){next->append();}
    else{next = new buttonList();}
}

buttonList::buttonList()
{
    but = new QPushButton;
    next= 0;
}

buttonList::~buttonList(){
    if(next != 0 ){delete next;}
    delete but;
}

void lineEditList::append(QString str){
    if(next !=0){next->append(str);}
    else{next = new lineEditList(str);}
}


lineEditList::lineEditList(QString str)
{
    line = new QLineEdit;
    line->setText(str);
    next= 0;
}

lineEditList::~lineEditList()
{
    if(next != 0 ){delete next;}
    delete line;
}

void hboxList::append(){
    if(next !=0){next->append();}
    else{next = new hboxList();}
}


hboxList::hboxList()
{
    line = new QHBoxLayout;
    next= 0;
}

hboxList::~hboxList()
{
    if(next != 0 ){delete next;}
    delete line;
}
