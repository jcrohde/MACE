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

#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H

#include <QPushButton>
#include <QString>
#include <QPair>

class ItemButton : public QPushButton
{
    Q_OBJECT

protected:

    QString str;

public:

    QPair<QString,int> pair;

    ItemButton(const QString string, int height, int width, int fontsize, int c, QWidget *parent=0);
    ~ItemButton();

    void setString(QString string);
    void setNewString(QString string);

private slots:
        void set_signal();

signals:
        void sig_string(QPair<QString,int> pair);


};

#endif // ITEMBUTTON_H
