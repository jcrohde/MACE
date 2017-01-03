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

#ifndef MACETOOLBAR_H
#define MACETOOLBAR_H

#include <QToolBar>
#include <QMenu>
#include <QToolButton>
#include <QComboBox>
#include "gui/intaction.h"

class MaceToolBar : public QToolBar
{
    Q_OBJECT
    
public:
    QComboBox *selectionBox;

    explicit MaceToolBar(QToolBar *parent = 0);
    ~MaceToolBar();
    
private slots:
    void setSelection(int index);

signals:
    void selectionCode(int code);

};

#endif // MACETOOLBAR_H
