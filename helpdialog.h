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

#ifndef HELPDIALOG_H
#define HELPDIALOG_H
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include <QPushButton>
#include <QString>

class helpDialog : public QDialog
{
    Q_OBJECT
public:

    QPushButton *but;
    QTextEdit *edit;
    QHBoxLayout *hbox;
    QVBoxLayout *vbox;

    helpDialog();
    ~helpDialog();
    void setEdit(QString str, int h, int w);

signals:

public slots:

};

#endif // HELPDIALOG_H
