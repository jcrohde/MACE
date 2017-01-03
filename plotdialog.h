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

#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPixmap>
#include <QPainter>
#include <QLineEdit>
#include <QIcon>
#include <QPushButton>
#include <QRadioButton>
#include <QTextEdit>
#include <QLabel>
#include <QFileDialog>
#include <QString>
#include <QGroupBox>
#include <QPen>
#include <QColor>
#include <QErrorMessage>
#include "math/variables/scalar/numcplx.h"
#include "math/kernel/parser.h"
#include "math/variables/scalar/numcplx.h"
#include "math.h"

//#include "GL/glu.h"
//#include <QtOpenGL/QGLWidget>

namespace Ui {
class plotDialog;
}

class plotDialog : public QDialog
{
    Q_OBJECT
    
private:
    DataBase *plotData;

    double pMin, pMax, vMin, vMax, xSize, ySize;

    void plot();
    int countFctn();

    void writeErrMsg(QString &errMsg, const QString color);

public:
    bool cplx;
    QString memory;

    QFileDialog *files;
    QPushButton *closeBut, *saveBut, *helpBut, *newBut;
    QRadioButton *small, *medium, *large;
    QPainter *paint, *sPaint;
    QTextEdit *helpInfo;
    QLabel *xfrom, *yfrom, *xto, *yto;
    QLabel *f, *g, *h, *i, *j, *k, *l;

    QErrorMessage *errorM;

    QHBoxLayout *mainbox, *hbox, *fBox, *xbox, *ybox, *cbox;
    QLineEdit *xMin, *xMax, *yMin, *yMax;
    QLineEdit *fl, *gl, *hl, *il, *jl, *kl, *ll;
    QVBoxLayout *lbox, *sBox, *vbox;
    QGridLayout *grid;
    QPixmap *pm, *sPic;
    QGroupBox *fctnFrame, *sizeFrame, *xFrame, *yFrame;
    QLabel *lb, *info;
    parser *kernel;

    explicit plotDialog(QFileDialog *fi, bool b, parser *pars, QWidget *parent = 0);
    ~plotDialog();

    void makeVisible();

    void cplxPlot(QString str);

    void plotting(QString str);

    void drawFctn(QString str, QString &ErrMsg, const  QString color);

    void doSave();

public slots:
    void replot(DataBase *Data=0);
    
private slots:
    void smallPlot();
    void medPlot();
    void largePlot();
    void show_info();
    void save();
    void finish();

    void closeEvent(QCloseEvent *e) {
        QDialog::closeEvent(e);
        delete this;
    }
};

#endif // PLOTDIALOG_H
