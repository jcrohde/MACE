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

#ifndef SCRIPT_H
#define SCRIPT_H

#include "math/kernel/mobject.h"
#include "math/kernel/reader.h"
#include "math/kernel/database.h"
#include "math/interpreter/processvalid.h"

class script : public MObject
{
private:


public:
    QString commandLine;

    enum token {
        NOTHING, SILENT, VISIBLE
    };

    reader read;
    DataBase Data;
    DataBase *previousScriptData;
    processValid pValid;
    std::vector<std::string> inputNames;
    std::vector<std::string> outputNames;
    QString scriptName;

    script();

    bool isZero() {return read.text.size() == 0;}
    QString print(unsigned int precision) {return read.text;}

    token getCommandLine();

private:
    bool findToken(token &curToken);
};

extern bool decompose(const QString &source, QString &name, std::vector<std::string> *args);
extern bool decompose(const QString &source, std::vector<std::string> &args);

#endif // SCRIPT_H
