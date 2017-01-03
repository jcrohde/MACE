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

#ifndef MACETEXTEDIT_H
#define MACETEXTEDIT_H

#include <QTextEdit>
#include <QScrollBar>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTextCursor>
#include "math/variables/scalar/maceint.h"
#include "math/kernel/reader.h"

//cases for characteristics
class Characteristic{
public:
    virtual void color(QString *str) = 0;
};

class Zero : public Characteristic{
public:
    virtual void color(QString *str);
};

class Positive : public Characteristic{
public:
    virtual void color(QString *str);
};

//in/out states

enum Formats{NO=0, SCALAR=1, MATRIX=2, REPLACE=3, RESTOREMAT=4};

class IOstate{

public:

    Formats curForm;

    virtual void format(QString *text, QString str, Formats newForm)=0;
    virtual void insert(QString *text, QString str, QTextEdit *e, Formats newForm)=0;
    virtual void stuff(QString str, QTextEdit *e, QScrollBar *bar, Formats newForm)=0;

    void write(QString *text, QString str, QTextEdit *e, QScrollBar *bar, Formats newForm);

    virtual bool scalarInput()=0;
    virtual bool matrixInput()=0;

    virtual void left(QTextEdit *e)=0;
    virtual void right(QTextEdit *e)=0;
    virtual bool up(QString *text, QString *memory, QTextEdit *e, QScrollBar *bar)=0;

    virtual QString matStr()=0;
};

class In : public IOstate{
protected:

    QString MatMem;

    int cursorPos;

    Formats restore;

    virtual void format(QString *text, QString str, Formats newForm);
    virtual void insert(QString *text, QString str, QTextEdit *e, Formats newForm);
    virtual void stuff(QString str, QTextEdit *e, QScrollBar *bar, Formats newForm);

public:
    bool high;
    int inputPos;
    int inputSize;

    In();

    virtual bool scalarInput();
    virtual bool matrixInput();

    virtual void left(QTextEdit *e);
    virtual void right(QTextEdit *e);
    virtual bool up(QString *text, QString *memory, QTextEdit *e, QScrollBar *bar);

    virtual QString matStr();

    QString getStr(QString *text);
    void giveComment(QString *text);
};

class Out : public IOstate{
protected:
    Characteristic *charac;

    virtual void format(QString *text, QString str, Formats newForm);
    virtual void insert(QString *text, QString str, QTextEdit *e, Formats newForm);
    virtual void stuff(QString str, QTextEdit *e, QScrollBar *bar, Formats newForm);

public:
    int lines;
    In *in;

    Out();
    ~Out();

    void setChar(/*MaceInt i*/);

    virtual bool scalarInput();
    virtual bool matrixInput();

    virtual void left(QTextEdit *e);
    virtual void right(QTextEdit *e);
    virtual bool up(QString *text, QString *memory, QTextEdit *e, QScrollBar *bar);

    virtual QString matStr();
};

//main class
class MaceTextEdit : public QTextEdit
{
    Q_OBJECT

private:
    Characteristic *charac;

    In in;
    Out out;
    IOstate *inOut;

    QString result, text, help;

    bool singMatrix;

    void callWrite(QString str, Formats newForm);

    void stuff(); //stuff to do after each write operation

    void mySetCursor();

public:
    bool usesPrevResult;
    bool posChar;
    bool changed;

    QScrollBar *scrollbar;

    void charWrite(QString str);

    bool getSingMatrix();
    bool matrixInput();

    QString getText();
    void load(QString);

    void left();
    void right();

    void setChar(/*MaceInt characteristic*/);

    explicit MaceTextEdit(QTextEdit *parent = 0);
    ~MaceTextEdit();

public slots:

    void up(bool h);

    void displayResult(QString str);
    void displayMatrixResult(QString str, int lines);
    void displaySLEResult(QString str);

    void zeroWrite(QString str);
    void standardWrite(QString str);
    void singleMatrix(QString str);
    void restoreMatrix(QString str);

    void reset();
    QString getLastResult();

    void keyPressEvent(QKeyEvent *event){
        if (event->key() == Qt::Key_Left){
            event->ignore();
            left();
        }
        else if(event->key() == Qt::Key_Right){
            event->ignore();
            right();
        }
        else if(event->key() == Qt::Key_Up){
            event->ignore();
            up(true);
        }
        else if(event->key() == Qt::Key_Down){
            event->ignore();
            up(false);
        }
        else {
            standardWrite(event->text());
            event->accept();
        }
    }

    void mousePressEvent(QMouseEvent *e){
        e->ignore();
        mySetCursor();
    }

    void mouseReleaseEvent(QMouseEvent *e){
        e->ignore();
    }

    void mouseDoubleClickEvent(QMouseEvent *e){
        e->ignore();
    }

    void mouseMoveEvent(QMouseEvent *e){
        e->ignore();
    }

signals:
    void inputText(QString str);
    void pleaseCalculate(QString str);
    void pleaseMatrix(QString str);
    void storeMatrix(QString str);
};

#endif // MACETEXTEDIT_H
