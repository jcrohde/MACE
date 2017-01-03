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

#ifndef MACEMENUBAR_H
#define MACEMENUBAR_H

#include <QMenuBar>
#include "gui/stringaction.h"

class MaceMenuBar : public QMenuBar
{
    Q_OBJECT
    
public:
    QMenu *fileMenu;
    QMenu *settingMenu;
    QMenu *plotMenu;
    QMenu *scriptMenu;
    QMenu *helpMenu;

    QAction *newAction;
    QAction *closeAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;

    stringAction *charAction;
    stringAction *lineColumnAction;
    stringAction *precisionAction;

    stringAction *plotAction;
    stringAction *plotCplxAction;

    QAction *loadScriptAction;

    stringAction *licenseAction;
    stringAction *hintAction;
    stringAction *authorAction;

    explicit MaceMenuBar(QMenuBar *parent = 0);
    ~MaceMenuBar();
    
private:

};

#endif // MACEMENUBAR_H
