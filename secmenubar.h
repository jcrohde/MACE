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

#ifndef SECMENUBAR_H
#define SECMENUBAR_H

#include <QToolBar>
#include <QMenu>

class SecMenuBar : public QToolBar
{
    Q_OBJECT


public:
    QAction *charAction;
    explicit SecMenuBar(QWidget *parent = 0);
    ~SecMenuBar();

signals:

public slots:

};

#endif // SECMENUBAR_H
