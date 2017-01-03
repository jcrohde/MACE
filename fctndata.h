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

#ifndef FCTNDATA_H
#define FCTNDATA_H

#include <QString>
#include <QMap>

struct fctnData{
    QString name;
    int code;
    int variables;
    QString help;
    QString html;
};

class genFunctions{

public:
    genFunctions();
    virtual QMap<QString,fctnData> get_map()=0;
};

class analFunctions: public genFunctions{
public:
    virtual QMap<QString,fctnData> get_map();
};

class complexFunctions: public genFunctions{
public:
    virtual QMap<QString,fctnData> get_map();
};

class arithmetics: public genFunctions{
public:
    virtual QMap<QString,fctnData> get_map();
};

class combinatorics: public genFunctions{
public:
    virtual QMap<QString,fctnData> get_map();
};

class logics: public genFunctions{
public:
    virtual QMap<QString,fctnData> get_map();
};

class linearAlgebra: public genFunctions{
public:
    virtual QMap<QString,fctnData> get_map();
};

class calculus: public genFunctions{
public:
    virtual QMap<QString,fctnData> get_map();
};

class controlFctn: public genFunctions{
public:
    virtual QMap<QString,fctnData> get_map();
};

#endif // FCTNDATA_H
