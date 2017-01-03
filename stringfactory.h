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

#ifndef STRINGFACTORY_H
#define STRINGFACTORY_H

#include <QString>
#include <QList>
#include <QMap>
#include <QPair>
#include "fctndata.h"
#include "math/kernel/reader.h"

class stringFactory
{
public:
    QMap<QString, fctnData> infos; //maps names of functions to the infos about the functions
    QMap<int,QString> typeNames; //maps the code of a function to the name of its type
    QMap<int,QString> funcTypes; //maps the code of a function to infos about it
    QMap<int, QString> typenotes;
    QMap<int, QString> generalTypes;
    QMap<QString, QList<int> > dataTypes;
    QMap<QString, fctnData> settingInfo;
    QMap<QString, QString> plotInfo;

    stringFactory();

    int getCode(QString key);
    int getVariables(QString key);
    QString getHtml(QString key);
    QString get_info(QString str); //returns name of the function for the key
    QString gen_info(QString str);
    QString help_info(QString str, int code);
    QString func_info(int code);
    QString get_typeName(int code);
    QString get_plotInfo(QString plot);
    QString get_settingInfo(QString setting);

    QString auth();
    QString license();
    QString hint();

    QString residues();
    QString script();

    QString dataText(); //displays html for datatypes;
    QString displayData(QString type); //displays html with infos about datatypes
    QString fctnText(); //displays html for a list of function types
    QString grammarText(); //displays html with infos about the grammar
    QString fctnList(int code, QString str); //displays html for a list of functions for a given code or the infos about a function
    QString plotText();
    QString settingText();
    QString distributions();

};

#endif // STRINGFACTORY_H
