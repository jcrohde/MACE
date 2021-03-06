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

#ifndef HELPDIALOG_H
#define HELPDIALOG_H
#include <QDialog>
#include <QTextBrowser>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "data/stringfactory.h"

class helpDialog : public QDialog
{
    Q_OBJECT

private:
    bool datType;

public:

    QPushButton *but;
    QTextBrowser *browser;
    QHBoxLayout *hbox;
    QVBoxLayout *vbox;
    stringFactory *factory;

    helpDialog(stringFactory *fac);
    ~helpDialog();
    void setBrowser(QString str, int h, int w);


signals:


public slots:
    void load(QUrl url);

};

#endif // HELPDIALOG_H
