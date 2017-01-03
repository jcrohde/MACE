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

#ifndef STRINGBUTTON_H
#define STRINGBUTTON_H

#include <QPushButton>
#include <QString>


class StringButton : public QPushButton
{
    Q_OBJECT
    
protected:
    QString str;

public:

    explicit StringButton(QWidget *parent = 0);
    StringButton(const QString string, int height, int width, int fontsize, QWidget *parent = 0);
    StringButton(const QString string, int height, int width, int fontsize, int c, QWidget *parent = 0);
    ~StringButton();

    void setString(QString string);
    
private slots:
        void set_signal();

signals:
        void sig_string(QString str);


};

#endif // STRINGBUTTON_H
