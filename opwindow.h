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

#ifndef OPWINDOW_H
#define OPWINDOW_H
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialog>

class opWindow : public QDialog
{
public:

    bool ok;

    QString a, b, labelStr;

    QLabel *label, *label1, *label2;

    QLineEdit *line1;
    QLineEdit *line2;

    QPushButton *but;
    QPushButton *but2;

    QHBoxLayout *hbox, *hbox1, *hbox2;
    QVBoxLayout *vbox;

    opWindow(QString op);
    ~opWindow();

public slots:
    void accept();
};

#endif // OPWINDOW_H
