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

#ifndef INTACTION_H
#define INTACTION_H

#include <QAction>
#include <QString>


class intAction : public QAction
{
    Q_OBJECT

private:
    QString string;
    int code;

public:
    explicit intAction(QString str, QObject *base);
    ~intAction();

    void setCode(int i);

private:

private slots:
    void codeSignal();

signals:
    void sigCode(int code);
};

#endif // INTACTION_H
