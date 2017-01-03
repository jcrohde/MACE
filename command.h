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

#ifndef COMMAND_H
#define COMMAND_H

#include "math/kernel/maceform.h"
#include "math/kernel/reader.h"

extern bool plot             (MaceForm *underControl, DataBase *scriptData, QString &string);
extern void cplxPlot         (reader &read, MaceForm *underControl, QString &string);
extern bool setCharacteristic(MaceForm *underControl, QString &string, DataBase *scriptData);
extern bool setPrecision     (MaceForm *underControl, QString &string, DataBase *scriptData);
extern bool open             (MaceForm *underControl, QString &string);
extern void execute          (MaceForm *underControl, QString &string);
extern bool saveAs           (MaceForm *underControl, QString &fileName);
extern bool printMatrix      (MaceForm *underControl, DataBase *Base, QString &string);

extern void killEmptyEnds        (QString &arg);
extern bool executeSpecialCommand(reader &read, DataBase &Data, MaceForm *underControl, bool &valid);

extern bool executeCommand(script &scr,MaceForm *underControl);

#endif // COMMAND_H
