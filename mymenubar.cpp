/*
Copyright (C) 2012 Jan Christian Rohde

This file is part of MACE.

MACE is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MACE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with MACE. If not, see <http://www.gnu.org/licenses/>.
*/

#include "mymenubar.h"

myMenuBar::myMenuBar(QWidget *parent)
{
    closeAction = new QAction("Quit",this);
    licenseAction = new QAction("License",this);
    hintAction = new QAction("Hints",this);
    authorAction = new QAction("About",this);

    fileMenu = new QMenu("File");
    helpMenu = new QMenu("Help");

    fileMenu->addAction(closeAction);

    helpMenu->addAction(licenseAction);
    helpMenu->addAction(hintAction);
    helpMenu->addAction(authorAction);

    addMenu(fileMenu);
    addMenu(helpMenu);
}

myMenuBar::myMenuBar()
{
    closeAction = new QAction("Close",this);
    licenseAction = new QAction("License",this);
    hintAction = new QAction("Hints",this);
    authorAction = new QAction("About",this);

    fileMenu = new QMenu("File");
    helpMenu = new QMenu("Help");

    fileMenu->addAction(closeAction);
    helpMenu->addAction(hintAction);
    helpMenu->addAction(licenseAction);
    helpMenu->addAction(authorAction);

    addMenu(fileMenu);
    addMenu(helpMenu);
}

myMenuBar::~myMenuBar(){

}
