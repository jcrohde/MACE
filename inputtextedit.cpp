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

#include "inputtextedit.h"

inputTextEdit::inputTextEdit(QTextEdit *parent) :
    QTextEdit(parent)
{
    scrollbar = this->verticalScrollBar();
    this->setReadOnly(false);
    this->setMaximumHeight(150);
    this->setMinimumHeight(30);
}

inputTextEdit::~inputTextEdit()
{

}

void inputTextEdit::eq() {
    QString text = this->toPlainText();
    this->clear();
    calculate(text);
}
