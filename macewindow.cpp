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

#include "gui/macewindow.h"

void scriptError(QErrorMessage *error, QString &inString, QString &outString) {
    QString str = "Cannot generate a script for the given data ";
    str = str.append(inString);
    if (outString.size() > 0) {
        str = str.append(",");
        str = str.append(outString);
    }
    str = str.append(".");
    error->showMessage(str);
}

MaceWindow::MaceWindow(QWidget *parent) :
    QMainWindow(parent)
{
    signature = "<br><br><br><i>This file has been edited with MACE 1.4.0.</i></body>";
    vert = new QVBoxLayout;
    menu = new MaceMenuBar;
    tools = new MaceToolBar;
    files = new QFileDialog;
    center = new MaceForm(files,440,450,40,45);

    files->setWindowIcon(QIcon("icons/MaceLogo.png")); // color: red 47, green 255, blue 83 oder 68 221 53
    files->setWindowTitle("Files");

    this->setWindowIcon(QIcon("icons/MaceLogo.png"));
    setWindowTitle("MACE");

    setMenuBar(menu);
    addToolBar(tools);
    setCentralWidget(center);
    scriptLanguage.underControl = center;


    help = new helpDialog(center->factory);

    QObject::connect(this->menu->closeAction,SIGNAL(triggered()),this,SLOT(close()));
    QObject::connect(this->menu->newAction,SIGNAL(triggered()),this,SLOT(newFile()));
    QObject::connect(this->menu->openAction,SIGNAL(triggered()),this,SLOT(load()));
    QObject::connect(this->menu->saveAsAction,SIGNAL(triggered()),this,SLOT(saveFileAs()));

    QObject::connect(this->menu->saveAction,SIGNAL(triggered()),this,SLOT(save()));

    QObject::connect(this->menu->charAction,SIGNAL(sig_string(QString)),center->opwindow,SLOT(make_settings(QString)));
    QObject::connect(this->menu->precisionAction,SIGNAL(sig_string(QString)),center->opwindow,SLOT(make_settings(QString)));
    QObject::connect(this->menu->lineColumnAction,SIGNAL(sig_string(QString)),center->opwindow,SLOT(make_settings(QString)));

    QObject::connect(this->menu->plotAction,SIGNAL(sig_string(QString)),center,SLOT(plotten(QString)));
    QObject::connect(this->menu->plotCplxAction,SIGNAL(sig_string(QString)),center,SLOT(plotten(QString)));

    QObject::connect(this->menu->loadScriptAction,SIGNAL(triggered()),this,SLOT(loadScript()));

    QObject::connect(this->menu->authorAction,SIGNAL(sig_string(QString)),this,SLOT(give_info(QString)));
    QObject::connect(this->menu->licenseAction,SIGNAL(sig_string(QString)),this,SLOT(give_info(QString)));
    QObject::connect(this->menu->hintAction,SIGNAL(sig_string(QString)),this,SLOT(give_info(QString)));

    QObject::connect(this,SIGNAL(emission(QString)), this->center->buts, SLOT(submission(QString)));

    QObject::connect(this->tools,SIGNAL(selectionCode(int)),this->center->selection,SLOT(setNew(int)));
    QObject::connect(this->tools,SIGNAL(selectionCode(int)),this->center->fctns,SLOT(setNew(int)));

    QObject::connect(this->center,SIGNAL(variableValue(QString)),&this->scriptLanguage,SLOT(getInput(QString)));
    QObject::connect(this->center,SIGNAL(callScript()),this,SLOT(executeScript()));
    QObject::connect(this->center,SIGNAL(callAction()),this,SLOT(executeAction()));

    center->inputEdit->setFocus();
}

MaceWindow::~MaceWindow()
{
    newFile();
    delete center;
    delete files;
    delete help;
}

void MaceWindow::newFile()
{
    if(this->center->texts->changed){
        if(QMessageBox::question(this,"Mace","Do you like to save changes?",QMessageBox::Yes,QMessageBox::No,QMessageBox::NoButton) == QMessageBox::Yes ){
            save();
        }
    }
    this->center->texts->reset();
    center->fileOpened = "";
}

void MaceWindow::give_info(QString str){
    help->setWindowTitle(str);
    if (str == "About"){
        help->setBrowser(center->factory->auth(),200,300);
        help->show();
    }
    else if (str == "License"){
        help->setBrowser(center->factory->license(),200,300);
        help->show();
    }
    else if(str == "Help"){
        help->setBrowser(center->factory->hint(),200,310);
        help->show();
    }
}

void MaceWindow::load(){
    QString filename = QFileDialog::getOpenFileName(
            this,
            tr("Open Document"),
            QDir::currentPath(),
            tr("HTML (*.html)") );
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly|QIODevice::Text)){

        if(center->fileOpened != filename){
            QString help = QString::fromUtf8(file.readAll());
            help = help.left(help.lastIndexOf("</body>"));
            help = help.right(help.size()-help.lastIndexOf("<body>")-6);
            help = help.left(help.size()-signature.size()+7);
            this->center->texts->load(help);
            this->center->texts->changed = false;
            center->fileOpened = filename;
        }
    }
}

void MaceWindow::save() //save the existing file
{
    if(center->fileOpened != ""){
        QFile file(center->fileOpened);

        if (file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QString content = "<head><title>";
            QString help = center->fileOpened;
            help = help.right(help.size()-help.lastIndexOf("/")-1);
            content = content.append(help);
            content = content.append("</title></head><body>");
            content = content.append(this->center->texts->getText());
            content = content.append(signature);
            file.write(content.toUtf8());
            this->center->texts->changed = false;
        }
    }
    else{
        saveFileAs();
    }
}

void MaceWindow::saveFileAs() //save as a new file
{
    center->fileOpened = files->getSaveFileName(this,tr("Save"),"Computations",tr("HTML (*.html)"));
    if(center->fileOpened != ""){save();}
}

void MaceWindow::loadScript(){
    QString filename = QFileDialog::getOpenFileName(
            this,
            tr("Open Document"),
            QDir::currentPath(),
                tr("Text files (*.txt);;All files (*.*)") );
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly|QIODevice::Text)){

        if(center->fileOpened != filename){
            QString help = QString::fromUtf8(file.readAll());
            scriptLanguage.interprete(help,filename);
        }
    }
}

void MaceWindow::executeScript() {
    script *scr = 0;
    bool valid = true;//generateSubScript(center->scriptString,center->scriptOutString,&center->kernel.variableData,scr);
    if (valid) scriptLanguage.interprete(scr->read.text,scr);
    else scriptError(center->error,center->scriptString,center->scriptOutString);
    if (scr != 0) delete scr;
}

void MaceWindow::executeAction() {
    script *scr = 0;
    Lambda *L;
    QString LName;
    std::string Lstr;
    unsigned int commaIndex;

    commaIndex = center->scriptString.indexOf(',');
    bool valid = commaIndex > 0;
    LName = center->scriptString.left(commaIndex);
    center->scriptString = center->scriptString.remove(0,commaIndex+1);
    valid = valid && center->scriptString.size() > 0;
    QStrToStdStr(LName,Lstr);
    center->kernel.variableData.findLambda(Lstr,L);
    //valid = valid && generateSubScript(center->scriptString,center->scriptOutString,&center->kernel.variableData,scr);
    if (L != 0 && valid) {
        copy(L->vars,scr->Data.content);
        scr->Data.copyLambda(L->sub);
    }
    if (valid) {
        scriptLanguage.interprete(scr->read.text,scr);
        //center->kernel.variableData.insertLambda(Lstr,&scriptLanguage.start.myScript->Data);
    }
    else {
        if (LName.size()>0) {
            center->scriptString = center->scriptString.prepend(",");
            center->scriptString = center->scriptString.prepend(LName);
        }
        scriptError(center->error,center->scriptString,center->scriptOutString);
    }
    delete scr;
}

