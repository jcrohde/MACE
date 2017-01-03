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

#ifndef LINADIST_H
#define LINADIST_H

#include "gui/macetextedit.h"
#include "math/kernel/parser.h"
#include "math/linearalgebra/algmatrix.h"
#include "math/variables/polynomial/algpoly.h"
#include "math/linearalgebra/nummatrix.h"
#include "math/linearalgebra/restmatrix.h"
#include "math/linearalgebra/linaprint.h"


class linadist
{
public:
    linAPrint LAP;

    linadist();

    QString matLinADist(genMatrix *M, QString op);

    //for complex matrices
    /*QString matLinADist(algMatrix *M, QString op);
    QString scalarLinADist(QString *str, algMatrix M, QString op);
    QString SLE_dist(algMatrix a, algMatrix b);

    //for char p matrices
    QString matLinADist(restMatrix *M, QString op);
    QString scalarLinADist(QString *str, restMatrix M, QString op);
    QString SLE_dist(restMatrix a, restMatrix b);*/

};

#endif // LINADIST_H
