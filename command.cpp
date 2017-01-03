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

#include "command.h"
#include <fstream>

static const QString signature = "<br><br><br><i>This file has been edited with MACE 1.4.0.</i></body>";

/*static bool getPositiveInt(MaceForm *underControl, QString &string, DataBase *scriptData, MaceInt *mi) {
    MVar var;
    MaceInt zeroInt(0);
    bool valid = underControl->kernel.interface(&string,zeroInt,&var,scriptData);
    valid = valid && var.getInt(mi);
    if (!valid) underControl->validC.setErr(NOTINT);
    valid = valid && *mi >= zeroInt;
    if (!valid) underControl->validC.setErr(INTNEG);
    return valid;
}*/

static bool decompose(const QString source, QString *string) {
    int count = 0;
    int pos = 0, begin = 0, end;
    int brackCount = 0;
    while (pos < source.size() && count < 7) {
        if (source.at(pos).toLatin1() == '(') brackCount++;
        else if (source.at(pos).toLatin1() == ')') brackCount--;
        else if (source.at(pos).toLatin1() == ',' && brackCount == 0) {
            end = pos - begin;
            string[count] = source.mid(begin,end);
            count++;
            begin = pos + 1;
        }
        pos++;
    }
    if (count < 7) {
        end = source.size()-begin;
        string[count] = source.mid(begin,end);
        return true;
    }
    else return false;
}

static bool isName(const QString &str) {
    int i = 0;
    char c;
    bool name = false;

    while (!name && i<str.size()) {
        c = str.at(i).toLatin1();
        switch (c) {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case 'i': case 'x': case '.':
            break;
            default: name = true;
            break;
        }
        i++;
    }
    return name;
}

static bool CheckNoNameError(QString &string,MaceForm *underControl,DataBase *Data)
{
    bool valid = isName(string);
    if (!valid) {
        MVar var;
        //underControl->kernel.interface(&string,/*underControl->characteristic,*/&var,Data);
        underControl->kernel.generateNoNameError(&var);
    }
    return valid;
}

bool plot(MaceForm *underControl, DataBase *scriptData, QString &string) {
    QString strArr[7];
    bool valid = false;
    if (decompose(string,strArr)) {
        valid = true;
        underControl->plotter = new plotDialog(underControl->files, false, &underControl->kernel);
        underControl->plotter->show();
        underControl->plotter->fl->setText(strArr[0]);
        underControl->plotter->gl->setText(strArr[1]);
        underControl->plotter->hl->setText(strArr[2]);
        underControl->plotter->il->setText(strArr[3]);
        underControl->plotter->jl->setText(strArr[4]);
        underControl->plotter->kl->setText(strArr[5]);
        underControl->plotter->ll->setText(strArr[6]);
        if (scriptData == 0) scriptData = &underControl->kernel.variableData;
        underControl->plotter->replot(scriptData);
    }
    if (!valid) underControl->validC.setErr(ERRINFCTN,"plot");
    return valid;
}

void cplxPlot(reader &read, MaceForm *underControl, DataBase *Data, QString &string) {
    underControl->plotter = new plotDialog(underControl->files, true, &underControl->kernel);
    underControl->plotter->show();
    underControl->plotter->fl->setText(string);
    if (Data == 0) Data = &underControl->kernel.variableData;
    underControl->plotter->replot(Data);
}

bool setCharacteristic(MaceForm *underControl, QString &string, DataBase *scriptData) {
    /*MaceInt mi;
    if (getPositiveInt(underControl,string,scriptData,&mi)) {
        underControl->characteristic = mi;
        underControl->applyCharacteristic();
        return true;
    }*/
    return false;
}

bool setPrecision(MaceForm *underControl, QString &string, DataBase *scriptData) {
   /* MaceInt mi;
    if (getPositiveInt(underControl,string,scriptData,&mi)) {
        unsigned int i = mi.toInt();
        if (i>=2 && i <= 16) {
            underControl->opwindow->pBox->setValue(i);
            underControl->precision();
            return true;
        } else underControl->validC.setErr(ERRINFCTN,"setPrecision");
    }*/
    return false;
}

bool open(MaceForm *underControl, QString &string) {
    QFile file(string);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QString help = QString::fromUtf8(file.readAll());
        help = help.left(help.lastIndexOf("</body>"));
        help = help.right(help.size()-help.lastIndexOf("<body>")-6);
        help = help.left(help.size()-signature.size()+7);
        underControl->texts->load(help);
        underControl->texts->changed = false;
        underControl->fileOpened = string;
        return true;
    }
    underControl->validC.setErr(NOTOPEN,string.toUtf8().constData());
    return false;
}

bool saveAs(MaceForm *underControl, QString &fileName) {
    std::ofstream sFile(fileName.toUtf8().constData());

    if (sFile.is_open()){
        QString content = "<head><title>";
        QString help = underControl->fileOpened;
        help = help.right(help.size()-help.lastIndexOf("/")-1);
        content = content.append(help);
        content = content.append("</title></head><body>");
        content = content.append(underControl->texts->getText());
        content = content.append(signature);
        sFile << content.toUtf8().constData();
        sFile.close();
        return true;
    }
    return false;
}

bool printMatrix(MaceForm *underControl, DataBase *Base, QString &string) {
    std::string str;
    MVar var;
    //algMatrix am;
    //restMatrix rm;
    bool valid = true;

    /*QStrToStdStr(string,str);
    Base->find(str,&var);
    if (var.getAlgMatrix(&am)) valid = underControl->setMatrix(&am);
    else if (var.getRestMatrix(&rm)) valid = underControl->setMatrix(&rm);
    else valid = false;
    if (!valid) underControl->validC.setErr(ERRINFCTN,"printMatrix");*/
    return valid;
}

void killEmptyEnds(QString &arg) {
    while(arg.at(0) == ' ' || arg.at(0) == '\n') {
        arg = arg.right(arg.size()-1);
    }
    while(arg.at(arg.size()-1) == ' ' || arg.at(arg.size()-1) == '\n') {
        arg.chop(1);
    }
}

bool executeSpecialCommand(reader &read, DataBase &Data, MaceForm *underControl, bool &valid) {
    bool gotOperation = true;
    valid = true;
    underControl->validC.init();

    if (read.getTokenString("saveAs(")) {
        QString string;
        valid = valid && read.getStringTillBrackClose(string,underControl->validC);
        killEmptyEnds(string);
        valid = valid && saveAs(underControl,string);
    }
    else if (read.getTokenString("open(")) {
        QString string;
        valid = valid && read.getStringTillBrackClose(string,underControl->validC);
        killEmptyEnds(string);
        if (valid) valid = open(underControl,string);
    }
    else if (read.getTokenString("reset")) {
        underControl->texts->reset();
    }
    else if (read.getTokenString("plot(")) {
        QString string;
        valid = valid && read.getStringTillBrackClose(string,underControl->validC);
        if (valid) valid = plot(underControl,&Data,string);
    }
    else if (read.getTokenString("cplxPlot(")) {
        QString string;
        valid = valid && read.getStringTillBrackClose(string,underControl->validC);
        if (valid) cplxPlot(read,underControl,&Data,string);
    }
    else if (read.getTokenString("deleteRecord(")) {
        QString string;
        valid = valid && read.getStringTillBrackClose(string,underControl->validC);
        if (valid) {
            Data.deleteRecord(string.toUtf8().constData());
        }
    }
    else if (read.getTokenString("init(")) {
        QString string, string2;
        read.getStringTillBrackClose(string2,underControl->validC);
        if (string2.indexOf(',') > -1)
            string = string2.left(string2.indexOf(','));
        else valid = false;
        if (valid) string2 = string2.remove(0,string.size()+1);
        if (valid) valid = string.size() > 0 && string2.size() > 0;
        if (valid) {
            valid = CheckNoNameError(string,underControl,&Data);
        }
        std::string name; QStrToStdStr(string,name);
        MVar var;
        if (!Data.find(name,&var) && valid) {
            /*if (underControl->kernel.interface(&string2,/*underControl->characteristic,*//*&var,&Data))
                Data.insert(name,&var);
            else valid = false;*/
        }
    }
    else if (read.getTokenString("delete(")) {
        QString string;
        valid = valid && read.getStringTillBrackClose(string,underControl->validC);
        if (valid) {
            std::string name; QStrToStdStr(string,name);
            Data.remove(name);
        }
    }
    else if (read.getTokenString("setCharacteristic(")) {
        QString string;
        valid = valid && read.getStringTillBrackClose(string,underControl->validC);
        if (valid) valid = setCharacteristic(underControl,string,&Data);
    }
    else if (read.getTokenString("setPrecision(")) {
        QString string;
        valid = valid && read.getStringTillBrackClose(string,underControl->validC);
        if (valid) valid = setPrecision(underControl,string,&Data);
    }
    else if (read.getTokenString("writeMatrix(")) {
        QString string;
        valid = valid && read.getStringTillBrackClose(string,underControl->validC);
        if (valid) valid = printMatrix(underControl,&Data,string);
    }
    else gotOperation = false;
    return gotOperation;
}

bool executeCommand(script &scr,MaceForm *underControl) {
    bool exe = true, valid = true;

    if (executeSpecialCommand(scr.read,scr.Data,underControl,valid)) {
        if (!valid) {
            QString estr;
            underControl->validC.getErrMsg(estr),
            scr.pValid.setInvalid(estr);
        }
    }
    else if (scr.read.getTokenString("get(")) {
        QString string,istr;
        MVar arg;
        std::vector<std::string> argNames;

        scr.read.getStringTillBrackClose(string,underControl->validC);
        valid = decompose(string,argNames);
        valid = valid && argNames.size() == scr.inputNames.size();
        for (int i = 0; i < argNames.size() && valid; i++) {
            StdStrToQStr(argNames[i],string);
            if (valid) {
                valid = CheckNoNameError(string,underControl,&scr.Data);
                if (!valid) scr.pValid.setInvalid(underControl->kernel.getErrorString());
            }
            StdStrToQStr(scr.inputNames[i],istr);
            //valid = valid && underControl->kernel.interface(&istr,/*underControl->characteristic,*/&arg,scr.previousScriptData);
            scr.Data.insert(argNames[i],&arg);
        }

        if (!valid) scr.pValid.setInvalid("Cannot get arguments");
    }
    else if (scr.read.getTokenString("give(")) {
        QString string, ostr;
        MVar arg;
        std::vector<std::string> argNames;

        scr.read.getStringTillBrackClose(string,underControl->validC);
        valid = decompose(string,argNames);
        valid = valid && argNames.size() == scr.outputNames.size();
        for (int i = 0; i < argNames.size() && valid; i++) {
            StdStrToQStr(argNames[i],ostr);
            //valid = valid && underControl->kernel.interface(&ostr,/*underControl->characteristic,*/&arg,&scr.Data);
            scr.previousScriptData->insert(scr.outputNames[i],&arg);
        }

        if (!valid) scr.pValid.setInvalid("");
    }
    else {
        MVar    var;
        script::token curToken = scr.getCommandLine();
        switch (curToken) {
            case script::SILENT:
                /*if (!underControl->kernel.interface(&scr.commandLine,/*underControl->characteristic,*//*&var,&scr.Data))
                    scr.pValid.setInvalid(underControl->kernel.getErrorString());*/
                break;
            case script::VISIBLE:
                if (!underControl->calculate(scr.commandLine,&scr.Data)) {
                    scr.pValid.setInvalid(underControl->kernel.getErrorString());
                }
                break;
        case script::NOTHING:
            exe = false;
            default:
                break;
        }
    }
    return exe;
}
