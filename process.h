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

#ifndef PROCESS_H
#define PROCESS_H

#include "math/interpreter/processvalid.h"
#include "math/interpreter/script.h"
#include "math/kernel/maceform.h"
#include "math/kernel/database.h"

/*class process {
public:

    process();
    process(script* scr);

    ~process();

    QString getInputName() {if (child != 0) return child->getInputName(); return inputName;}
    QString getErrorString();

    void setScript(script *scr);

    enum token {
        EMPTY, PROCESSBEGIN, PROCESSEND, IF, WHILE, FOR, BREAK, INPUT, ERROR, PROCESSCLOSE
    };

    token execute     (MaceForm *mForm);
    bool  executeInput(QString &str);
    token conti       ();

    void killChilds() {if (child != 0) {delete child; child = 0;}}

    enum loopState {
        NONE, IFLOOP, WHILELOOP, FORLOOP
    };

    script  *myScript;

private:
    loopState curLoopState;
    type myType;
    MaceForm *underControl;

    process *child;
    script  *subScript;

    QString inputName;
    QString arg0, arg1, arg2;
    MVar    forVar;
    int posMem, loopBegin, whileIndex, forIndex, lineBegin;
    bool initial;

    bool getCommandStructure(token &curToken);

    void updateLoopState(token lastChildToken, token *curToken,loopState &curLoopState);
    bool getBreakCondition(token lastChildToken, int loopBegin);

    token runIfCase      ();
    void  runWhileLoop   (token *curToken);
    void  runForLoop     (token *curToken);

    bool getBoolean();
    bool getBoolean(QString &arg);

    void getArgs(QString &arg0, QString &arg1, QString &arg2);

    bool getElse();
    bool getElseIf();

    void executefunc(token &curToken, Lambda *L = 0);
    void executeLambda(token &curToken);

    token runChildProcess();
    token executeSub     ();
    token executeSkript  (QString string, QString outputString, Lambda *L = 0);

};

extern bool generateSubScript(QString &string, QString outputString, DataBase *data, script *&subScript);
*/

#endif // PROCESS_H
