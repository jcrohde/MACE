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

#include "macetoolbar.h"


MaceToolBar::MaceToolBar(QToolBar *parent) :
    QToolBar(parent)
{
    selectionBox = new QComboBox();
    selectionBox->addItem("All Functions");
    selectionBox->addItem("Analysis");
    selectionBox->addItem("Complex Functions");
    selectionBox->addItem("Arithmetics");
    selectionBox->addItem("Operators and Commands");
    selectionBox->addItem("Statistics");
    selectionBox->addItem("Linear Algebra");
    selectionBox->addItem("Differential Calculus");

    addWidget(selectionBox);

    connect(selectionBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setSelection(int)));
}

MaceToolBar::~MaceToolBar()
{

}

void MaceToolBar::setSelection(int index) {
    int code = 100;

    if (index == 1)
        code = 160;
    else if (index == 2)
        code = 110;
    else if (index == 3)
        code = 120;
    else if (index == 4)
        code = 150;
    else if (index == 5)
        code = 130;
    else if (index == 6)
        code = 140;
    else if (index == 7)
        code = 170;

    emit selectionCode(code);
}

