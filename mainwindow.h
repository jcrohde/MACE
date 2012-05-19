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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define PI 3.141592
#include <QMainWindow>
#include <QPair>
#include <QScrollBar>
#include <QMessageBox>
#include <rat.h>
#include "complex.h"
#include "polynomial.h"
#include "rest.h"
#include "restpolynomial.h"
#include "matrix.h"
#include "mydialog.h"
#include "helpdialog.h"
#include <mymenubar.h>
#include <opwindow.h>
#include <secmenubar.h>
#include <chardialog.h>
#include <unboundint.h>
#include <restmatrix.h>
#include <polynomial.h>
#include <algpoly.h>
#include <algcplx.h>
#include <algmatrix.h>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);//(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QString str;
    QString memory;
    QString str1;
    QString ch;
    QString strResult;
    QString text1;

    myMenuBar *test;
    SecMenuBar *secBar;

public:

    QScrollBar *sb;
    opWindow *nthWindow;
    charDialog *chDia;
    helpDialog *infos;

        double dans;
        double dans1;

        float num;
        float num1;
        float ans;

        int charac;

        int lines;
        int columns;

        int inum;
        int inum1;
        int ians;
        QList<int> ints;
	int help;

        //complex double numbers
        complex cnum;
        complex cnum1;
        complex cans;

        //arbitrary precision rationals
        rat arat;
        rat brat;

        //arbitrary precision integers
        unboundInt ubinum;
        unboundInt ubinum1;
        unboundInt ubians;

        //arbitrary precision elements of QQ(i)
        algCplx acnum;
        algCplx acnum1;
        algCplx acans;

        //rest class in ZZ/n
        rest rans;

        //polynomials with complex double coefficients
        polynomial pol;
        polynomial pol1;
        polynomial anspol;

        //polynomials with arbitrary precision coefficients in QQ(i)
        algPoly apol;
        algPoly apol1;
        algPoly aanspol;

        //polynomials with coefficients in ZZ/n
        restpolynomial rpol;
        restpolynomial rpol1;
        restpolynomial ranspol;

        //matrices with complex double coefficients
        matrix mat;
        matrix mat1;
        matrix rmat;

        //matrices with arbitrary precision coefficients in QQ(i)
        algMatrix amat;
        algMatrix amat1;
        algMatrix armat;

        //matrices with coefficients in ZZ/n
        restMatrix rtmat;
        restMatrix rtmat1;
        restMatrix rrtmat;
	
        //for the extended Euklidian algorithm:
        QPair<int,int> res;
        QPair<algPoly ,algPoly> arespol;
        QPair<restpolynomial ,restpolynomial> rrespol;

        bool ganz;
        bool cplx;
        bool poly;
        bool alg;
        bool linAlg;
        bool nth;

        void showNThDialog(QString op);
        void showDialog(QString text);
        void standardWrite();
        void linAWrite();
        void err(QString errMsg);
        void linASwitch();

        void createActions();
        void correctMemory();

private slots:
        void addi();
        void subs();
        void mult();
        void divi();
        void em();
        void mone();
        void mtwo();
        void mthree();
        void mfour();
        void mfive();
        void msix();
        void mseven();
        void meight();
        void mnine();
        void mzero();
	void mi();
        void mkla();
        void mklz();
        void mx();
        void mpower();
	
        void mreset();
        void mdot();

        void mC();
	
	void mod();
	void mgcd();
	void mlcm();
	void mExEu();

        void mPrime();
        void mPrimeDec();
        void mphi();
        void mfibo();
        void mfacnum();
        void mlambda();
        void mpsi();
        void mpi();
        void mfacsum();
        void mfac();

        void setChar();
        void setChar2();
        void setLine(int);
        void setColumn(int);

        void mWriteMatrix();


        void mtranspose();
        void mgauss();
        void mmatMult();
        void mmatAdd();
        void mmatSub();
        void mmatInv();
        void mSLESolve();
        void mrank();
        void mdet();
        void mcharPoly();
        void mminiPoly();

        void msin();
        void marcsin();
        void mcos();
        void marccos();
        void mtan();
        void marctan();
        void mcot();
        void marccot();
        void mexp();
        void mlog();
        void minv();
        void mPower();
        void mlogA();
        void msqrt();
        void mbino();

        void showHints();
        void showInfo();
        void showAuthor();

};

#endif // MAINWINDOW_H
