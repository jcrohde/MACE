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

#include "calcbuts.h"


CalcButs::CalcButs(int h, int w, int fs, QTextEdit *e, QWidget *parent):
    width(w), height(h), fontsize(fs), edit(e), QGridLayout(parent)
{

    this->setHorizontalSpacing(0);
    this->setVerticalSpacing(0);

    butC = new StringButton("C",height, 2*width+1, fontsize);
    butReset = new StringButton("Reset",height, 2*width+1, fontsize);

    but0 = new StringButton("0", height, width, fontsize);
    but1 = new StringButton("1", height, width, fontsize);
    but2 = new StringButton("2", height, width, fontsize);
    but3 = new StringButton("3", height, width, fontsize);
    but4 = new StringButton("4", height, width, fontsize);
    but5 = new StringButton("5", height, width, fontsize);
    but6 = new StringButton("6", height, width, fontsize);
    but7 = new StringButton("7", height, width, fontsize);
    but8 = new StringButton("8", height, width, fontsize);
    but9 = new StringButton("9", height, width, fontsize);

    butPlus = new StringButton("+",height, width, fontsize);
    butMinus = new StringButton("-", height, width, fontsize);
    butTimes = new StringButton("*", height, width, fontsize);
    butDiv = new StringButton("/", height, width, fontsize);

    butDot = new StringButton(".", height, width, fontsize);
    butEq = new StringButton("=", height, width, fontsize);

    butBrackOpen = new StringButton("(", height, width, fontsize);
    butx = new StringButton("x", height, width, fontsize);
    buti = new StringButton("i", height, width, fontsize);
    butBrackClose = new StringButton(")", height, width, fontsize);
    butPower = new StringButton("^", height, width, fontsize);

    this->addWidget(butC,0,0,1, 2);
    this->addWidget(butReset,0,2,1, 2);

    this->addWidget(but7,1,0,1, 1);
    this->addWidget(but8,1,1,1, 1);
    this->addWidget(but9,1,2,1, 1);
    this->addWidget(butDiv,1,3,1, 1);

    this->addWidget(but4,2,0,1, 1);
    this->addWidget(but5,2,1,1, 1);
    this->addWidget(but6,2,2,1, 1);
    this->addWidget(butTimes,2,3,1, 1);

    this->addWidget(but1,3,0,1, 1);
    this->addWidget(but2,3,1,1, 1);
    this->addWidget(but3,3,2,1, 1);
    this->addWidget(butMinus,3,3,1, 1);

    this->addWidget(but0,4,0,1, 1);
    this->addWidget(butDot,4,1,1, 1);
    this->addWidget(butEq,4,2,1, 1);
    this->addWidget(butPlus,4,3,1, 1);

    this->addWidget(butPower,0,5,1, 1);
    this->addWidget(butBrackOpen,1,5,1, 1);
    this->addWidget(butBrackClose,2,5,1, 1);
    this->addWidget(butx,3,5,1, 1);
    this->addWidget(buti,4,5,1, 1);

    field = true;
    complex = true;

    QObject::connect(this->but0,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->but1,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->but2,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->but3,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->but4,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->but5,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->but6,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->but7,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->but8,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->but9,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));

    QObject::connect(this->butPlus,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->butMinus,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->butTimes,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->butDiv,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));

    QObject::connect(this->butDot,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->butEq,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));

    QObject::connect(this->butBrackOpen,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->butx,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->buti,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->butBrackClose,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->butPower,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));

    QObject::connect(this->butC,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));
    QObject::connect(this->butReset,SIGNAL(sig_string(QString)),this,SLOT(submission(QString)));

    QObject::connect(this,SIGNAL(emission(QString)),edit,SLOT(insertPlainText(QString)));
    QObject::connect(this,SIGNAL(C()),edit,SLOT(C()));
    QObject::connect(this,SIGNAL(eq()),edit,SLOT(eq()));
}

void CalcButs::submission(QString str){

    if (str == "Reset"){
        emit reset();
    }
    else if (str == "C"){
        emit C();
    }
    else if (str == "="){
        emit eq();
    }
    else if (str == "0" || str == "1" || str == "2" || str == "3" || str == "4" ||str == "5" || str == "6" ||
             str == "7" || str == "8" || str == "9" || (complex && str == ".") || str == "+" || str == "-" || str == "*" ||
             (field && str == "/") || str == "^" || str == "(" || (complex && str == "i") ||
             str == "x" || str == ")"){

        emit emission(str);
    }
}










