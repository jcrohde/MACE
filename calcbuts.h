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

#ifndef CALCBUTS_H
#define CALCBUTS_H
#include <QLayout>
#include "gui/stringbutton.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QGridLayout>
#include "gui/macetextedit.h"


class CalcButs : public QGridLayout
{
    Q_OBJECT

private:
    int height, width, fontsize;

    QTextEdit *edit;

public:
    bool field;
    bool complex;

    StringButton *butC;
    StringButton *butReset;

    StringButton *but0;
    StringButton *but1;
    StringButton *but2;
    StringButton *but3;
    StringButton *but4;
    StringButton *but5;
    StringButton *but6;
    StringButton *but7;
    StringButton *but8;
    StringButton *but9;

    StringButton *butPlus;
    StringButton *butMinus;
    StringButton *butTimes;
    StringButton *butDiv;

    StringButton *butEq;
    StringButton *butDot;

    StringButton *butBrackOpen;
    StringButton *butx;
    StringButton *buti;
    StringButton *butBrackClose;
    StringButton *butPower;

    CalcButs(int h, int w, int fs, QTextEdit *e, QWidget *parent = 0 );

public slots:
    void submission(QString str);

signals:
    void emission(QString str);
    void eq();
    void C();
    void reset();
};

#endif // CALCBUTS_H
