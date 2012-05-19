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

#include "helpdialog.h"

helpDialog::helpDialog(){
    vbox = new QVBoxLayout;
    hbox = new QHBoxLayout;
    but = new QPushButton("Ok");
    edit = new QTextEdit;

    vbox->addWidget(edit);

    hbox->addStretch();
    hbox->addWidget(but);

    vbox->addLayout(hbox);

    setLayout(vbox);
}

helpDialog::~helpDialog(){

}

void helpDialog::setEdit(QString str, int h, int w){
    this->edit->setFixedHeight(h);
    this->edit->setFixedWidth(w);
    this->edit->setHtml(str);
}
