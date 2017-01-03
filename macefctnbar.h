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

#ifndef MACEFCTNBAR_H
#define MACEFCTNBAR_H

#include <QHBoxLayout>
#include <QSpacerItem>
#include <QListWidgetItem>
#include "gui/itembutton.h"


class MaceFctnBar : public QHBoxLayout
{
    Q_OBJECT

private:
    bool field;
    int codeMem;

public:
    bool posChar;

    ItemButton *FBut;
    ItemButton *GammaBut;
    ItemButton *JBut;
    ItemButton *LagBut;
    ItemButton *PIBut;

    ItemButton *facBut;

    ItemButton *aChooseBBut;
    ItemButton *SLEBut;
    ItemButton *gcdBut;

    ItemButton *bindBut;
    ItemButton *expdBut;
    ItemButton *nordBut;

    ItemButton *cosBut;
    ItemButton *sinBut;
    ItemButton *expBut;
    ItemButton *tanBut;
    ItemButton *logBut;
    ItemButton *detBut;
    ItemButton *paretoBut;
    ItemButton *modBut;
    ItemButton *poissonBut;
    ItemButton *primeBut;

    ItemButton *inverseBut;
    ItemButton *rankBut;
    ItemButton *miniPolyBut;

    ItemButton *variableBut;
    ItemButton *andBut;
    ItemButton *orBut;
    ItemButton *smallBut;
    ItemButton *largBut;
    ItemButton *sketchBut;

    QSpacerItem *spacer;

    QListWidgetItem *item;

    QList<ItemButton*> buttons;

    explicit MaceFctnBar(QWidget *parent = 0);
    ~MaceFctnBar();

private:

private slots:
    void setItem(QPair<QString,int> pair);

public slots:
    void setNew(int code);
    void set_field(bool f);

signals:
    void sendItem(QListWidgetItem *item);

};

#endif // MACEFCTNBAR_H
