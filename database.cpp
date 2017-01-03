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

#include "database.h"
#include <iostream>

chain::chain(std::string name, MVar *val) {
    varName = name;
    var = *val;
    next = 0;
}

void chain::insert(std::string name, MVar *val) {
    if (varName == name) {
        var = *val;
    }
    else if (next == 0) {
        next = new chain(name,val);
    }
    else next->insert(name,val);
}

bool chain::find(std::string name, MVar *val) {
    if (varName == name) {
        *val = var;
        return true;
    }
    else if (next != 0) return next->find(name,val);
    else return false;
}

void copy(chain *source, chain *&dest) {
    if (dest != 0) {delete dest; dest = 0;}
    if (source !=0) {
        dest = new chain(source->varName,&source->var);
        if (source->next != 0) copy(source->next,dest->next);
    }
}

static void copy(Lambda *source, Lambda *&dest) {
    if (dest != 0) {delete dest; dest = 0;}
    if (source !=0) {
        dest = new Lambda(source->lambdaName,source->vars);
        if (source->sub != 0) copy(source->sub,dest->sub);
        if (source->next != 0) copy(source->next,dest->next);
    }
}

void Lambda::insert(std::string name, chain *c, Lambda *s) {
    if (lambdaName == name) {
        copy(c,vars);
        copy(s,sub);
     }
     else if (next == 0) {
         next = new Lambda(name,c);
         copy(s,next->sub);
     }
     else next->insert(name,c,s);
}

DataBase::DataBase()
{
    content = 0;
    lambda = 0;
}

void DataBase::copyLambda(Lambda *L) {
    copy(L,lambda);
}

void DataBase::insertLambda(std::string name, DataBase *B) {
    if (lambda == 0) {
        lambda = new Lambda(name,B->content);
        copy(B->lambda,lambda->sub);
    }
    else lambda->insert(name,B->content,B->lambda);
}

void DataBase::insert(std::string name, MVar *val) {
    if (content == 0) {
        content = new chain(name,val);
    }
    else content->insert(name,val);
}

bool DataBase::findLambda(std::vector<std::string> args, MVar *&val) {
    Lambda *L = lambda;
    while (L != 0) {
        if (L->lambdaName == args[0] && L->vars != 0) {
            args.erase(args.begin());
            if (args.size() == 1) {
                return L->vars->find(args[0],val);
            }
            else L = L->sub;
        }
        else L = L->next;
    }
    return false;
}

void DataBase::findLambda(std::string LambdaName, Lambda *&L) {
    L = lambda;
    while (L != 0 && L->lambdaName != LambdaName) {
        L = L->next;
    }
}

bool DataBase::find(std::string name, MVar *val) {
    if (content !=0) {
        return content->find(name,val);
    }

    return false;
}

void DataBase::remove(std::string name) {
    chain *d, *f, *c = content;
    bool found = false;
    f = content;
    while (c != 0 && !found) {
        if (c->varName == name) {
            d = c->next;
            c->next = 0;
            delete c;
            c = 0;
            if (f == content) content = d;
            else f->next = d;
            found = true;
        }
        else {
            f = c;
            c = c->next;
        }
    }
}

void DataBase::deleteRecord(std::string name) {
    Lambda *d, *f, *c = lambda;
    bool found = false;
    f = lambda;
    while (c != 0 && !found) {
        if (c->lambdaName == name) {
            d = c->next;
            c->next = 0;
            delete c;
            c = 0;
            if (f == lambda) lambda = d;
            else f->next = d;
            found = true;
        }
        else {
            f = c;
            c = c->next;
        }
    }
}

void DataBase::clear() {
    delete content;
    content = 0;
    delete lambda;
    lambda = 0;
}
