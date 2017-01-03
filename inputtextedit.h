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

#ifndef INPUTTEXTEDIT_H
#define INPUTTEXTEDIT_H

#include <QTextEdit>
#include <QKeyEvent>

class inputTextEdit: public QTextEdit
{
    Q_OBJECT
private:

public:
    explicit inputTextEdit(QTextEdit *parent = 0);
    ~inputTextEdit();

    QScrollBar *scrollbar;

public slots:

    void C() {
        textCursor().deletePreviousChar();
    }

    void eq();

    void keyPressEvent(QKeyEvent *event){
        if(event->key()== Qt::Key_Return){
            event->ignore();
            eq();
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
            QTextEdit::keyPressEvent(event);
        }
    }

signals:
    void calculate(QString str);
    void up       (bool    b);
};

#endif // INPUTTEXTEDIT_H
