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

#ifndef MACELISTWIDGET_H
#define MACELISTWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QList>
#include "data/stringfactory.h"


class MaceListWidget : public QListWidget
{
    Q_OBJECT
private:
    int state;
    bool field;
    
public:
    bool posChar;

    explicit MaceListWidget(stringFactory *factory, QListWidget *parent = 0);
    ~MaceListWidget();


    
private:
    stringFactory *itemSource;

    void item_adder_general(int code, bool f);

public slots:
    void set_field(bool f);
    void setNew(int code);

signals:
    void call_function(QString fctn);
};

#endif // MACELISTWIDGET_H
