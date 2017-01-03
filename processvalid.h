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

#ifndef PROCESSVALID_H
#define PROCESSVALID_H

#include <QString>
#include "math/kernel/reader.h"

class processValid
{
public:
    processValid() {scriptName = ""; valid = true;}

    void init(QString &sName) {scriptName = sName; valid = true;}
    void incrementLine() {lineNumber++;}
    bool getValid() {return valid;}
    void setInvalid(QString str) {if (valid) {valid = false; errorString = str;}}

    QString getScriptName() {return scriptName;}
    QString getErrorMessage() {return errorString;}

private:
    QString scriptName;
    QString errorString;
    int     lineNumber;
    bool    valid;
};

#endif // PROCESSVALID_H
