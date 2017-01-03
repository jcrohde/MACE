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

#include "process.h"
#include "command.h"
#include <iostream>

/*static bool checkArg(QString &arg) {
    bool valid = true;

    killEmptyEnds(arg);
    valid = valid && arg.size() > 0;
    valid = valid && arg.indexOf(' ') == -1;
    valid = valid && arg.indexOf('\n') == -1;
    return valid;
}

static int runTillSign(reader &read, char sign) {
    while (read.text.at(read.pos).toLatin1() != sign) {
        read.pos++;
    }
    return read.pos;
}

static bool interruptEachProcess(process::token curToken) {
    return curToken == process::INPUT || curToken == ERROR;
}

process::process() {
    myScript = 0;
    subScript = 0;
    child = 0;
    initial = true;
}

process::process(script *scr) : myScript(scr)
{
    subScript = 0;
    child = 0;
    initial = true;
}

process::~process() {
    delete child;
    if (subScript != 0) delete subScript;
}

QString process::getErrorString() {
    if (child != 0) return child->getErrorString();
    QString errorString = "Error in script ";
    errorString = errorString.append(myScript->pValid.getScriptName());
    errorString = errorString.append(" in line ");
    QString lineNrStr;
    lineNrStr = lineNrStr.number(myScript->read.getLineNumber(lineBegin));
    errorString = errorString.append(lineNrStr);
    errorString = errorString.append(". ");
    errorString = errorString.append(myScript->pValid.getErrorMessage());
    return errorString;
}

void process::setScript(script *scr) {
    myScript = scr;
}

bool process::executeInput(QString &str) {
    if (child != 0) return child->executeInput(str);
    QString text = inputName;
    text = text.append("=");
    text = text.append(str);
    return underControl->kernel.interface(&text,/*underControl->characteristic,*//*&myScript->Data);
}

static bool findCommand(reader &read, process::token &curToken) {
    bool result = true;

    if      (read.getTokenString("{"))     curToken = process::PROCESSBEGIN;
    else if (read.getTokenString("}"))     curToken = process::PROCESSCLOSE;
    else if (read.getTokenString("if"))    curToken = process::IF;
    else if (read.getTokenString("while")) curToken = process::WHILE;
    else if (read.getTokenString("for"))   curToken = process::FOR;
    else if (read.getTokenString("break")) curToken = process::BREAK;
    else result = false;

    return result;
}

process::token process::execute(MaceForm *mForm) {
    curLoopState = NONE;
    token curToken = EMPTY;
    QString scriptName;

    underControl = mForm;

    do {
        if (curToken != INPUT && curToken != ERROR) killChilds();
        scriptName.clear();
        lineBegin = myScript->read.runOverEmptyLines();

        if (myScript->read.getTokenString("input(")) {
            if (myScript->read.getStringTillBrackClose(inputName,underControl->validC))
                curToken = INPUT;
            else curToken = ERROR;
        }
        else if (myScript->read.getTokenString("execute(")) {
            executefunc(curToken);
        }
        else if (myScript->read.getTokenString("record(")) {
            executeLambda(curToken);
        }
        else if (!getCommandStructure(curToken)) {
            unsigned int curPos = myScript->read.pos;
            if (!executeCommand(*myScript,underControl)) {
                if (curPos < myScript->read.text.size()){
                    myScript->pValid.setInvalid("Cannot enterprete last commands.");
                }
                else curToken = PROCESSEND;
            }
        }
        if (curToken == PROCESSEND && myScript->read.pos < myScript->read.text.size()){
            myScript->pValid.setInvalid("Cannot read last commands.");
        }
        if (!myScript->pValid.getValid()) curToken = ERROR;
    } while (curToken != PROCESSEND && curToken != BREAK && curToken != INPUT
             && curToken != ERROR && curToken != PROCESSCLOSE);
    return curToken;
}

process::token process::conti() {
    if (child != 0) {
        token lastChildToken = child->conti();

        if (!child->myScript->pValid.getValid()) myScript->pValid.setInvalid("");
        if (interruptEachProcess(lastChildToken)) return lastChildToken;
        if (curLoopState == IFLOOP) {
            if (lastChildToken != BREAK) {
                QString str;
                while (getElseIf()) {
                    myScript->read.getStringTillSign(str,'{');
                    myScript->read.jumpToBrackEnd();
                }
                if (getElse()) {
                    myScript->read.jumpToBrackEnd();
                }
                curLoopState = NONE;
            }
            else return lastChildToken;
        }
        if (curLoopState == WHILELOOP) {
            if (lastChildToken == BREAK) {
                myScript->read.pos = loopBegin;
                myScript->read.jumpToBrackEnd();
            }
            else {
                myScript->read.pos = whileIndex;
            }

        }
        if (curLoopState == FORLOOP) {
            if (lastChildToken == BREAK) {
                myScript->read.pos = loopBegin;
                myScript->read.jumpToBrackEnd();
            }
            else {
                myScript->read.pos = forIndex;
                initial = false;
            }
        }
    }
    return execute(underControl);
}

bool process::getCommandStructure(token &curToken) {
    token helpToken = EMPTY;

    if (findCommand(myScript->read,curToken)) {
    switch (curToken) {
        case PROCESSBEGIN:
            helpToken = executeSub();
            break;
        case IF:
            helpToken = runIfCase();
            break;
        case WHILE:
            whileIndex = myScript->read.pos-5;
            runWhileLoop(&curToken);
            break;
        case FOR:
            forIndex = myScript->read.pos-3;
            runForLoop(&curToken);
            break;
        default:
            break;
    }
    if (helpToken == BREAK) curToken = BREAK;
    if (interruptEachProcess(helpToken)) curToken = helpToken;
    return true;
    }
    return false;
}

void process::updateLoopState(token lastChildToken, token *curToken,loopState &curLoopState) {
    if (interruptEachProcess(lastChildToken)) *curToken = lastChildToken;
    else {
        if (lastChildToken != BREAK) {
            myScript->read.jumpToBrackEnd();
        }
        curLoopState = NONE;
    }
}

bool process::getBreakCondition(token lastChildToken, int loopBegin) {
    if (lastChildToken == BREAK) {
        myScript->read.pos = loopBegin;
        myScript->read.jumpToBrackEnd();
    }
    return interruptEachProcess(lastChildToken) || lastChildToken == BREAK;
}

process::token process::runIfCase() {
    token lastChildToken = EMPTY;
    bool  trueCase, run = true, valid = true;
    bool  jump;

    trueCase = getBoolean();
    valid = valid && myScript->pValid.getValid();
    if (trueCase && valid) {
        curLoopState = IFLOOP;
        lastChildToken = executeSub();
    }
    else if (valid) myScript->read.jumpToBrackEnd();

    QString str;
    while (getElseIf() && valid) {
        jump = false;
        if (!trueCase) {
            trueCase = getBoolean();
            if (trueCase) {
                curLoopState = IFLOOP;
                lastChildToken = executeSub();
            } else jump = true;
        } else {
            jump = true;
            myScript->read.getStringTillSign(str,'{');
        }
        if (jump) {
            myScript->read.jumpToBrackEnd();
        }
    }
    if (getElse() && valid) {
        if (trueCase) {
            myScript->read.jumpToBrackEnd();
        }
        else lastChildToken = executeSub();
    }
    if (!valid) lastChildToken = ERROR;
    return lastChildToken;
}

void process::runWhileLoop(token *curToken) {
    posMem = myScript->read.pos;
    token lastChildToken;
    while (getBoolean()) {
        curLoopState = WHILELOOP;
        loopBegin = myScript->read.pos;
        lastChildToken = executeSub();
        if (!interruptEachProcess(lastChildToken)) myScript->read.pos = posMem;
        if (getBreakCondition(lastChildToken,loopBegin)) break;
    }
    updateLoopState(lastChildToken,curToken,curLoopState);
}

void process::runForLoop(token *curToken) {
    token lastChildToken;

    if (initial) {
        getArgs(arg0,arg1,arg2);
        posMem = myScript->read.pos;
        if (!underControl->kernel.interface(&arg0,/*underControl->characteristic,*//*&forVar,&myScript->Data))
            myScript->pValid.setInvalid(underControl->kernel.getErrorString());
    }
    else {
        myScript->read.pos = posMem;
        if (!underControl->kernel.interface(&arg2,/*underControl->characteristic,*//*&forVar,&myScript->Data))
            myScript->pValid.setInvalid(underControl->kernel.getErrorString());
    }
    while (getBoolean(arg1) && myScript->pValid.getValid())
    {
        loopBegin = myScript->read.pos;
        curLoopState = FORLOOP;
        lastChildToken = executeSub();
        if (!interruptEachProcess(lastChildToken)) myScript->read.pos = posMem;
        if (getBreakCondition(lastChildToken,loopBegin)) break;
        if (!underControl->kernel.interface(&arg2,/*underControl->characteristic,*//*&forVar,&myScript->Data)){
            myScript->pValid.setInvalid(underControl->kernel.getErrorString());
            killChilds();
            lineBegin = loopBegin;
        }
    }
    updateLoopState(lastChildToken,curToken,curLoopState);
    initial = true;
}

bool process::getBoolean() {
    QString commandLine;
    bool valid = true;

    valid = valid && myScript->read.getStringTillSign(commandLine, '{');
    if (!valid) myScript->pValid.setInvalid("Missing \"{\".");
    valid = valid && getBoolean(commandLine);
    return valid;
}

bool process::getBoolean(QString &arg) {
    MVar var;
    /*MaceInt mi;

    bool valid = underControl->kernel.interface(&arg,underControl->characteristic,&var,&myScript->Data);
    if (valid) valid = var.getInt(&mi);
    if (valid) return !mi.isZero();
    else myScript->pValid.setInvalid("No boolean found.");*//*
    return false;
}

void process::getArgs(QString &arg0, QString &arg1, QString &arg2) {
    myScript->read.getStringTillSign(arg0,';');
    myScript->read.getStringTillSign(arg1,';');
    myScript->read.getStringTillSign(arg2,'{');
}

bool process::getElse() {
    unsigned int curPos = myScript->read.runOverEmptyChar();
    if (myScript->read.getTokenString("else")) {
        myScript->read.runOverEmptyChar();
        myScript->read.pos++;
        return true;
    }
    myScript->read.pos = curPos;
    return false;
}

bool process::getElseIf() {
    unsigned int curPos = myScript->read.runOverEmptyChar();
    if (myScript->read.getTokenString("elseif")) {
        myScript->read.runOverEmptyChar();
        return true;
    }
    myScript->read.pos = curPos;
    return false;
}

void process::executefunc(process::token &curToken, Lambda *L) {
    QString string, outString;
    if (myScript->read.getStringTillBrackClose(string,underControl->validC)) {
    if (myScript->read.getTokenString("->(")) {
        if (!myScript->read.getStringTillBrackClose(outString,underControl->validC)) curToken = ERROR;
    }
    if (curToken !=ERROR) {
        token lastToken = executeSkript(string,outString,L);
        if (interruptEachProcess(lastToken)) {
            curToken = lastToken;
        }
    }
    }
    else curToken = ERROR;
}

void process::executeLambda(process::token &curToken) {
    Lambda *L = 0;
    QString string;
    std::string str;
    if (myScript->read.getStringTillSign(string,",")) {
        QStrToStdStr(string,str);
        myScript->Data.findLambda(str,L);
        executefunc(curToken,L);
    } else myScript->pValid.setInvalid("Missing the second argument.");

    if (curToken == INPUT) {
        myScript->pValid.setInvalid("A record or a script called by a record is not allowed to perform an input-call");
        curToken = ERROR;
        killChilds();
    }
    else if (myScript->pValid.getValid()){
        QStrToStdStr(string,str);
        myScript->Data.insertLambda(str,&child->myScript->Data);
    }
}

process::token process::runChildProcess() {
    token lastToken = child->execute(underControl);
    if (!child->myScript->pValid.getValid()) myScript->pValid.setInvalid("");
    return lastToken;
}

process::token process::executeSub() {
    killChilds();
    child = new process(myScript);
    token lastChildToken = runChildProcess();
    if (lastChildToken != PROCESSCLOSE && lastChildToken != BREAK && lastChildToken != INPUT) {
        myScript->pValid.setInvalid("Process does not close correctly.");
        lastChildToken = ERROR;
    }
    return lastChildToken;
}

process::token process::executeSkript(QString string, QString outputString, Lambda *L) {
    token lastToken = EMPTY;
    killChilds();
    bool valid = generateSubScript(string,outputString,&myScript->Data,subScript);
    if (!valid) {
        myScript->pValid.setInvalid("Cannot open script.");
        killChilds();
    }
    if (L != 0 && valid) {
        copy(L->vars,subScript->Data.content);
        subScript->Data.copyLambda(L->sub);
    }
    if (valid) child = new process(subScript);
    if (valid) {
        lastToken = runChildProcess();
    }
    else {
        lastToken = ERROR;
    }
    return lastToken;
}

bool generateSubScript(QString &string, QString outputString, DataBase *data, script *&subScript) {
    std::vector<std::string> args, outputArgs;
    QString name;

    bool valid = decompose(string,name,&args);
    MVar var;
    std::string stdstr; QStrToStdStr(name,stdstr);
    if (data->find(stdstr,&var)) {
        MaceString mstr;
        if (var.getString(&mstr)) {
            name=mstr.str;
        }
    }
    QFile file(name);
    if (valid && file.open(QIODevice::ReadOnly|QIODevice::Text)) {

        QString help = QString::fromUtf8(file.readAll());
        if (subScript != 0) {
            delete subScript; subScript = 0;
        }
        subScript = new script;
        subScript->read.init(help);
        subScript->previousScriptData = data;
        subScript->inputNames = args;
        subScript->scriptName = name;

        subScript->pValid.init(name);

        if (outputString.size() > 0) {
            valid = valid && decompose(outputString,outputArgs);

            subScript->outputNames = outputArgs;
        }
    } else valid = false;
    return valid;
}*/
