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

#include "interpreter.h"

void interpreter::interprete(QString &str, script *strategy) {
    startScript.pValid.init(strategy->scriptName);
    startScript.read.init(str);
    startScript.inputNames = strategy->inputNames;
    startScript.outputNames = strategy->outputNames;
    startScript.previousScriptData = strategy->previousScriptData;
    copy(strategy->Data.content,startScript.Data.content);
    startScript.Data.copyLambda(strategy->Data.lambda);
    //start.setScript(&startScript);
    //process::token lastToken = start.execute(underControl);

    //afterMath(lastToken);
}

void interpreter::interprete(QString &str, QString &scriptName) {
    startScript.pValid.init(scriptName);
    startScript.read.init(str);
    startScript.Data.clear();
    /*start.setScript(&startScript);
    process::token lastToken = start.execute(underControl);
    afterMath(lastToken);*/
}

/*void interpreter::afterMath(process::token lastToken) {
    //if (lastToken == process::ERROR) underControl->error->showMessage(start.getErrorString());
    if (lastToken == process::INPUT) callWriteInput(start.getInputName());
    else start.killChilds();
}*/

void interpreter::callWriteInput(QString str) {
    QListWidgetItem item;
    item.setData(100,"callWriteInput");
    item.setData(101,str);
    underControl->opwindow->make_visible(/*underControl->characteristic,*/&item);
}

void interpreter::getInput(QString str) {
    /*if (start.executeInput(str)) {
        process::token lastToken = start.conti();
        afterMath(lastToken);
    }
    else {
        underControl->error->showMessage("Error in input.");
        afterMath(process::ERROR);
    }*/
}
