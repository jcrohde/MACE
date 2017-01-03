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

#ifndef FCTNDIALOG_H
#define FCTNDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QTabWidget>
#include <QLabel>
#include <QTextEdit>
#include <QListWidgetItem>
#include <QSpacerItem>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QGridLayout>
#include <QRadioButton>
#include <QGroupBox>
#include "gui/macelineedit.h"
#include "math/variables/scalar/maceint.h"
#include "data/stringfactory.h"
#include "math/kernel/reader.h"

class FctnDialog : public QDialog
{
    Q_OBJECT
    
public:

    bool ok;

    QString a, b, c, d, labelStr;

    QLabel *label, *label1, *label2, *label3, *label4, *pLabel, *pLabel2;

    MaceLineEdit *line1;
    MaceLineEdit *line2;
    MaceLineEdit *line3;
    MaceLineEdit *line4;

    QSpinBox *pBox, *pBox2;

    QTextEdit *info;

    QSpacerItem *vertic;
    stringFactory *factory;

    QPushButton *help;
    QPushButton *but;
    QPushButton *but2;

    QTabWidget *tab;

    QRadioButton *pdf, *cdf, *hazard, *quantile;
    QRadioButton *kurt, *kurtex, *mean, *median, *mode, *skewness, *standdev, *variance;
    QGroupBox *statFunc;
    QGroupBox *statVars;

    QGridLayout *grid, *radioGrid;
    QHBoxLayout *hbox, *hbox15;
    QVBoxLayout *vbox, *radioBox, *funcVars;
    QHBoxLayout *mlay;

    explicit FctnDialog(stringFactory *fac, QWidget *parent = 0);
    ~FctnDialog();
    
    int getFctnCode();
    QString getOption();

private:
    int fctnCode;
    QString op;

    void closeEvent(QCloseEvent *event){
        if (ok || fctnCode !=200) {
            emit bye();
            event->accept();
        }
        else event->ignore();
    }

    void QContextMenuEvent(QContextMenuEvent *event){
        emit bye();
        event->accept();
    }

    void labelFormat(bool fctns);
    void linesFormat(int i, int code, int index);
    void selectLabels();

private slots:
    void agree();
    void show_info();
    void statSwitch(int i);
    void nextLine();

public slots:
        void change_linesColumns(QListWidgetItem *i);
        void make_visible(/*MaceInt characteristic, */QListWidgetItem *i);
        void make_settings(QString str);

signals:
    void inserted();
    void newFctnCode(int i);
    void rejected();
    void hello();
    void bye();

};

#endif // FCTNDIALOG_H
