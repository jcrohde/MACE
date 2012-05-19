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

#ifndef BUTTONLIST_H
#define BUTTONLIST_H
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QString>


class buttonList
{
public:
    buttonList *next;
    QPushButton *but;

    buttonList();
    ~buttonList();
    void append();
};

class lineEditList
{
public:
    lineEditList *next;
    QLineEdit *line;

    lineEditList(QString str);
    ~lineEditList();
    void append(QString str);
};

class hboxList
{
public:
    hboxList *next;
    QHBoxLayout *line;

    hboxList();
    ~hboxList();
    void append();
};

#endif // BUTTONLIST_H
