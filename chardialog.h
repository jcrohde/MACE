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

#ifndef CHARDIALOG_H
#define CHARDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>

class charDialog : public QDialog
{
    Q_OBJECT
public:

    QLabel *label;
    QSpinBox *charBox;

    QPushButton *but;
    QPushButton *but1;

    QHBoxLayout *hbox, *hbox1;
    QVBoxLayout *vbox;

    explicit charDialog(QWidget *parent = 0);
    ~charDialog();

signals:

public slots:

};

#endif // CHARDIALOG_H
