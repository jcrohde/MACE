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

#ifndef MATRIXENTER_H
#define MATRIXENTER_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QListWidgetItem>
#include <QGridLayout>
#include <QTextEdit>
#include <QAction>
#include "macelineedit.h"
#include "math/variables/scalar/maceint.h"
#include <QSpacerItem>
#include <QListWidgetItem>
#include "data/stringfactory.h"

class matrixEnter : public QDialog
{
    Q_OBJECT
    
public:
    int lines, columns;
    QString matInfo, resInfo, title, hText;
    QString op;
    int fctnCode;

    QTextEdit *info;

    QPushButton *changeLinCol;

    QLabel *label, *labHelp;
    QPushButton *but;
    QPushButton *but2;
    QPushButton *help;
    QSpacerItem *horiz;
    MaceLineEdit *dit;
    QList<MaceLineEdit*> edits;
    QList<QLabel*> labels;
    QHBoxLayout *hbox, *topHbox;
    QVBoxLayout *vbox;
    QGridLayout *matrix;
    bool q;

    QListWidgetItem *mercury;

    stringFactory *factory;

    explicit matrixEnter(stringFactory *fac, QWidget *parent = 0);
    ~matrixEnter();

    void give();
    void setOp(QListWidgetItem *i);

private:

    void chooseMode(/*MaceInt charac,*/ MaceLineEdit *edit);

    void closeEvent(QCloseEvent *event){
        emit bye();
        event->accept();
    }

public slots:
    void accept();
    void make_visible(int li, int co, /*MaceInt characteristic,*/ QListWidgetItem *i, bool vec = false, bool quad = false);

private slots:
    void changeWish();
    void clean();
    void show_info();

signals:
    void changeMatrix(QListWidgetItem *item);
    void inserted();
    void bye();
    void hello();

};
#endif // MATRIXENTER_H
