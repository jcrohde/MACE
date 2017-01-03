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

#include "macemenubar.h"

MaceMenuBar::MaceMenuBar(QMenuBar *parent) :
    QMenuBar(parent)
{
    closeAction = new QAction("Quit",this);
    newAction = new QAction("New",this);
    openAction = new QAction("Open",this);
    saveAction = new QAction("Save",this);
    saveAsAction = new QAction("Save As",this);

    charAction = new stringAction("Characteristics", this);
    lineColumnAction = new stringAction("Rows and Columns of Matrices", this);
    precisionAction = new stringAction("Precision", this);

    plotAction = new stringAction("Plot a real function", this);
    plotCplxAction = new stringAction("Plot a complex function", this);

    loadScriptAction = new QAction("Execute a Script", this);

    licenseAction = new stringAction("License", this);
    hintAction = new stringAction("Help", this);
    authorAction = new stringAction("About", this);

    fileMenu = new QMenu("File");
    settingMenu = new QMenu("Settings");
    plotMenu = new QMenu("Plot");
    scriptMenu = new QMenu("Scripts");
    helpMenu = new QMenu("Help");

    newAction->setIcon(QIcon("icons/new.png"));
    openAction->setIcon(QIcon("icons/open.png"));
    saveAction->setIcon(QIcon("icons/save.png"));
    saveAsAction->setIcon(QIcon("icons/saveAs.png"));
    plotAction->setIcon(QIcon("icons/plot.png"));
    plotCplxAction->setIcon(QIcon("icons/cplxPlot.png"));
    hintAction->setIcon(QIcon("icons/help.png"));

    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAction);

    settingMenu->addAction(charAction);
    settingMenu->addAction(precisionAction);
    settingMenu->addAction(lineColumnAction);

    plotMenu->addAction(plotAction);
    plotMenu->addAction(plotCplxAction);

    scriptMenu->addAction(loadScriptAction);

    helpMenu->addAction(hintAction);
    helpMenu->addSeparator();
    helpMenu->addAction(licenseAction);
    helpMenu->addAction(authorAction);

    addMenu(fileMenu);
    addMenu(settingMenu);
    addMenu(plotMenu);
    addMenu(scriptMenu);
    addMenu(helpMenu);
}

MaceMenuBar::~MaceMenuBar()
{

}
