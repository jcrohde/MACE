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

#include "itembutton.h"


ItemButton::ItemButton(const QString string, int height, int width, int fontsize, int c, QWidget *parent)
{
    pair.second = c;
    str = string;
    QString help = help.number(fontsize);
    help = help.append("pt");
    help = help.prepend("font-size: ");

    this->setText(string);
    this->setMinimumHeight(height);
    this->setMinimumWidth(width);
    this->setStyleSheet(help);
    QObject::connect(this,SIGNAL(clicked()),this,SLOT(set_signal()));

}

ItemButton::~ItemButton()
{

}

void ItemButton::setString(QString string){
    pair.first = string;
    this->setToolTip(string);
}

void ItemButton::setNewString(QString string){
    pair.first = string;
}

void ItemButton::set_signal(){
    emit sig_string(pair);
}

