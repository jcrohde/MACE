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

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>
#include "math/kernel/maceform.h"
#include "math/kernel/reader.h"
#include "math/interpreter/process.h"

class interpreter : public QObject
{
    Q_OBJECT

public:
    MaceForm *underControl;
    //process start;

    void interprete(QString &str, script *strategy);
    void interprete(QString &str, QString &scriptName);

private:
    script  startScript;

    void callWriteInput(QString str);
    //void afterMath(process::token lastToken);

signals:

public slots:
    void getInput(QString str);
};

#endif // INTERPRETER_H
