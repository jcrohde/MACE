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

#include "chardialog.h"

charDialog::charDialog(QWidget *parent) :
    QDialog(parent)
{
    vbox = new QVBoxLayout;



    hbox = new QHBoxLayout;
    hbox1 = new QHBoxLayout;

    label = new QLabel("Choose characteristics:");
    charBox = new QSpinBox;
    charBox->setMinimum(0);
    charBox->setMaximum(32767);

    but = new QPushButton("Ok");
    but1 = new QPushButton("No");

    hbox->addWidget(label);
    hbox->addWidget(charBox);
    vbox->addLayout(hbox);

    hbox1->addWidget(but);
    hbox1->addWidget(but1);
    vbox->addLayout(hbox1);
    setLayout(vbox);

    QObject::connect(but1,SIGNAL(clicked()),this,SLOT(close()));
}

charDialog::~charDialog(){

}
