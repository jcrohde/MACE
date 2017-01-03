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

#ifndef LINAPRINT_H
#define LINAPRINT_H

#include <QString>
#include "genmatrix.h"


class linAPrint{

public:

    QString writeMatOp(genMatrix *left, QString Op, genMatrix *right);
    QString writeMatSingOp(genMatrix *left, QString Op, QString right);
    QString writeScalarMatOp(QString Op, genMatrix *right);
    QString writeGauss(genMatrix *left, genMatrix *vector, genMatrix *result);

};

#endif // LINAPRINT_H
