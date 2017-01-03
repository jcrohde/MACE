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
#include "script.h"

static bool checkArg(QString &arg) {
    bool valid = true;

    killEmptyEnds(arg);
    valid = valid && arg.size() > 0;
    valid = valid && arg.indexOf(' ') == -1;
    valid = valid && arg.indexOf('\n') == -1;
    return valid;
}

bool decompose(const QString &source, QString &name, std::vector<std::string> *args) {
    QString arg;
    int count = 0;
    int pos = 0, begin = 0, end;
    int brack = 0;
    bool valid = true;

    args->clear();
    while (pos < source.size() && valid) {
        if (source.at(pos).toLatin1() == '(') brack++;
        if (source.at(pos).toLatin1() == ')') brack--;
        if (source.at(pos).toLatin1() == ',' && brack == 0) {
            end = pos - begin;
            if (count == 0) {
                name = source.left(end);
                killEmptyEnds(name);
            }
            else {
                arg = source.mid(begin,end);
                valid = valid && checkArg(arg);
                args->push_back(arg.toUtf8().constData());
            }
            count++;
            begin = pos + 1;
        }
        pos++;
    }
    if (count == 0) name = source.left(end);
    else {
        arg = source.mid(begin,end);
        valid = valid && checkArg(arg);
        args->push_back(arg.toUtf8().constData());
    }
    return valid;
}

bool decompose(const QString &source, std::vector<std::string> &args) {
    QString midString;
    int pos = 0, begin = 0, end;
    int brack = 0;
    bool valid = true;

    args.clear();
    while (pos < source.size() && valid) {
        if (source.at(pos).toLatin1() == '(') brack++;
        if (source.at(pos).toLatin1() == ')') brack--;
        if (source.at(pos).toLatin1() == ',' && brack == 0) {
            end = pos - begin;
            midString = source.mid(begin,end);
            valid = valid && checkArg(midString);
            args.push_back(midString.toUtf8().constData());
            begin = pos + 1;
        }
        pos++;
    }
    midString = source.mid(begin,end);
    valid = valid && checkArg(midString);
    args.push_back(midString.toUtf8().constData());
    return valid;
}

bool script::findToken(token &curToken) {
    bool result = true;

    if      (read.getTokenString(";"))     curToken = SILENT;
    else if (read.getTokenString(":"))     curToken = VISIBLE;
    else result = false;

    return result;
}

script::script()
{
}

script::token script::getCommandLine() {
    bool  tokenFound = false;
    script::token curToken = NOTHING;
    commandLine.clear();
    while (read.pos < read.text.size() && !tokenFound) {
        if (read.text.at(read.pos).toLatin1() == ' ') commandLine.append(' ');
        tokenFound = findToken(curToken);
        if (!tokenFound) {
            if (read.text.at(read.pos).toLatin1() == '%') {
                read.runOverComment();
            }
            else {
                commandLine.append(read.text.at(read.pos));
            }
            read.pos++;
        }
    }
    return curToken;
}
