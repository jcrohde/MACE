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

#ifndef DATABASE_H
#define DATABASE_H

#include <QMap>
#include <QString>
#include "math/kernel/mvar.h"

class chain {
public:
    std::string varName;
    chain       *next;
    MVar        var;

    chain (std::string name, MVar *val);

    void insert(std::string name, MVar *val);
    bool find  (std::string name, MVar *val);

    ~chain () {delete next;}
};

extern void copy(chain *source, chain *&dest);

class Lambda {
public:
    std::string lambdaName;
    Lambda *next;
    Lambda *sub;
    chain *vars;

    Lambda(std::string name, chain *v) : lambdaName(name) {
        next = 0; sub = 0; vars = 0; copy(v,vars);
    }

    ~Lambda() {delete next; delete sub; delete vars;}

    void insert(std::string name, chain *c, Lambda *s);
};

class DataBase
{
public:
    chain *content;
    Lambda *lambda;


    DataBase();
    ~DataBase() {delete content; delete lambda; }

    DataBase& operator=(const DataBase& base) {
        if (this == &base) return *this;
        copy(base.content,content);
        return *this;
    }

    void copyLambda(Lambda *L);
    void insertLambda(std::string name, DataBase *L);
    bool findLambda(std::vector<std::string> args, MVar *&val);
    void findLambda(std::string LambdaName, Lambda *&L);
    void insert(std::string name, MVar *val);
    bool find  (std::string name, MVar *val);
    void remove(std::string name);
    void clear ();
    void deleteRecord(std::string name);
};

#endif // DATABASE_H
