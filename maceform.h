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

#ifndef MACEFORM_H
#define MACEFORM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QErrorMessage>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QSplitter>
#include "math/linearalgebra/algmatrix.h"
#include "gui/macefctnbar.h"
#include "gui/calcbuts.h"
#include "gui/macetextedit.h"
#include "macelistwidget.h"
#include "gui/fctndialog.h"
#include "math/variables/scalar/maceint.h"
#include "math/variables/scalar/macerest.h"
#include "math/variables/scalar/numcplx.h"
#include "math/variables/polynomial/algpoly.h"
#include "math/variables/polynomial/numpoly.h"
#include "math/kernel/parser.h"
#include "gui/plotdialog.h"
#include "math/linearalgebra/restmatrix.h"
#include "math/variables/polynomial/restpoly.h"
#include "math/linearalgebra/linadist.h"
#include "math/linearalgebra/nummatrix.h"
#include "data/stringfactory.h"
#include "gui/inputtextedit.h"
#include "math/kernel/database.h"
#include "gui/matrixenter.h"


class MaceForm : public QDialog
{
   Q_OBJECT
    
public:

    QString fileOpened;
    QString scriptString, scriptOutString;

    int textHeight, textWidth, calcHeight, calcWidth;
    QErrorMessage *error;

    QVBoxLayout *vert;
    MaceFctnBar *fctns;

    QHBoxLayout *mainLayout;
    QVBoxLayout *left, *inputLayout;
    QSplitter *textLayout;
    MaceListWidget *selection;
    MaceTextEdit *texts;
    inputTextEdit *inputEdit;
    QLabel *inputLabel;

    CalcButs *buts;
    FctnDialog *opwindow;
    matrixEnter *mats;

    QFileDialog *files;
    plotDialog *plotter;

    QListWidgetItem *copy, *change, *memory;
    bool nextOperation;

    stringFactory *factory;
    validCheck validC;
    reader read;
    parser kernel;
    //linadist linAlg;

    //MaceInt characteristic;
    int lines, columns, prec;

    explicit MaceForm(QFileDialog *f, int th, int tw, int ch, int cw, QWidget *parent = 0);
    ~MaceForm();

    void precision();

    bool setMatrix(genMatrix *genMat);
    void applyCharacteristic();
    
private:

    //algMatrix amat;
    //restMatrix rmat;

    QString block();
    void linAVisible(QListWidgetItem *i);

    void resetLinesColumns();
    void scalOp();
    void setCharacteristic();

    void sketchingPart(QString command,QString &func);

    void setLinesColumns();

public slots:
    bool calculate(QString str, DataBase *data = 0);
    void getSignal();
    void make_visible(QListWidgetItem *i);
    void matrix(QString str);
    void storeMatrix(QString);
    void linearAlgebra();
    void plotten(QString str);
    void no();

signals:
    void variableValue(QString str);
    void callScript();
    void callAction();
};

#endif // MACEFORM_H
