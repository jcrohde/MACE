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

#ifndef MYMENUBAR_H
#define MYMENUBAR_H
#include <QMenuBar>
#include <QMenu>

class myMenuBar : public QMenuBar
{
public:
    QMenu *fileMenu;
    QMenu *helpMenu;

    myMenuBar(QWidget *parent);
    myMenuBar();
    ~myMenuBar();

    QAction *closeAction;
    QAction *licenseAction;
    QAction *hintAction;
    QAction *authorAction;

};

#endif // MYMENUBAR_H
