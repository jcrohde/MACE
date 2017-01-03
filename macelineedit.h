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

#ifndef MACELINEEDIT_H
#define MACELINEEDIT_H

#include <QLineEdit>
#include <QEvent>
#include <QKeyEvent>

namespace Ui {
class MaceLineEdit;
}

class MaceLineEdit : public QLineEdit
{
    Q_OBJECT
    
public:
    bool all;
    explicit MaceLineEdit(QLineEdit *parent = 0);
    ~MaceLineEdit();
    
private:
    bool strictPositive;
    bool complex;
    bool polynomial;



virtual bool event(QEvent *e){
    if (e->type() == QEvent::KeyPress){
        QKeyEvent *ke = static_cast<QKeyEvent *>(e);
        if(ke->key() == Qt::Key_0 || ke->key() == Qt::Key_1 || ke->key() == Qt::Key_2 || ke->key() == Qt::Key_3 ||
           ke->key() == Qt::Key_4 || ke->key() == Qt::Key_5 || ke->key() == Qt::Key_6 || ke->key() == Qt::Key_7 ||
           ke->key() == Qt::Key_8 || ke->key() == Qt::Key_9 || ke->key()== Qt::Key_Backspace || all){
            return QLineEdit::event(e);
        }
        else if(ke->key() == Qt::Key_Return){
            emit entered();
            ke->ignore();
            return true;
        }
        else{
            ke->ignore();
            return true;
        }
    }
    return QLineEdit::event(e);
}

signals:
    void entered();

public slots:

};

#endif // MACELINEEDIT_H
