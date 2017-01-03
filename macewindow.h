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

#pragma once

#ifndef MACEWINDOW_H
#define MACEWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>
#include "QDialog"
#include "gui/macemenubar.h"
#include "gui/macetoolbar.h"
#include "math/kernel/maceform.h"
#include "math/interpreter/interpreter.h"
#include "gui/helpdialog.h"



class MaceWindow : public QMainWindow
{
    Q_OBJECT

private:
    QString signature;

public:
    QVBoxLayout *vert;
    MaceMenuBar *menu;
    MaceToolBar *tools;
    QFileDialog *files;
    MaceForm *center;
    interpreter scriptLanguage;
    QIcon *test;
    helpDialog *help;

    explicit MaceWindow(QWidget *parent = 0);
    ~MaceWindow();

public slots:

private slots:
    void give_info(QString str);

    void newFile();
    void load();
    void save();
    void saveFileAs();

    void loadScript();
    void executeScript();
    void executeAction();

signals:
    void emission(QString str);
    
private:

};

#endif // MACEWINDOW_H
