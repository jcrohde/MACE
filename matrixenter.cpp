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

#include "gui/matrixenter.h"

matrixEnter::matrixEnter(stringFactory *fac, QWidget *parent) :
    QDialog(parent), factory(fac)
{
    setWindowTitle("linear Algebra");
    setWindowIcon(QIcon("icons/MaceLogo.png"));

    labHelp = 0;
    but = new QPushButton("Ok");
    but->setMaximumWidth(40);
    but->setMinimumHeight(25);
    but2 = new QPushButton("No");
    but2->setMaximumWidth(40);
    but2->setMinimumHeight(25);
    help = new QPushButton("help");
    help->setMaximumWidth(40);
    help->setMinimumHeight(25);
    changeLinCol = new QPushButton("change rows / columns");
    changeLinCol->setMinimumWidth(125);
    changeLinCol->setMinimumHeight(25);

    horiz = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    label = new QLabel;
    topHbox = new QHBoxLayout;
    hbox = new QHBoxLayout;
    vbox = new QVBoxLayout;
    mercury = new QListWidgetItem;

    lines = 2;
    columns = 1;
    matInfo = "No";
    matrix = new QGridLayout;

    info = new QTextEdit;
    info->setMaximumHeight(100);
    info->setReadOnly(true);

    vbox->addWidget(label);

    vbox->addLayout(matrix);

    vbox->addWidget(info);

    hbox->addWidget(changeLinCol);
    hbox->addItem(horiz);
    hbox->addWidget(but);
    hbox->addWidget(but2);
    hbox->addWidget(help);

    vbox->addLayout(hbox);

    setLayout(vbox);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QWidget::connect(help,SIGNAL(clicked()),this,SLOT(show_info()));
    QWidget::connect(changeLinCol,SIGNAL(clicked()),this,SLOT(changeWish()));

    QWidget::connect(but,SIGNAL(clicked()),this,SLOT(accept()));
    QWidget::connect(but2,SIGNAL(clicked()),this,SLOT(close()));
}

matrixEnter::~matrixEnter(){
    
}

void matrixEnter::changeWish(){
    this->close();

    QVariant func_type;

    func_type = mercury->data(100);
    QString str = func_type.toString();

    if(str == "determinant of a matrix" || str == "inverse matrix" || str == "trace of a matrix" ||
            str == "minimal polynomial of a matrix" || str == "characteristic polynomial of a matrix"
            || str == "eigenvalues of a matrix" || str == "adjoint matrix" || q){
        mercury->setText("rows / columns");
    }
    else if(str == "solve a system of linear equations"){
        mercury->setText("variables and equations");
    }
    else if(str == "* for matrices"){
        mercury->setText("columns");
    }
    else{
        mercury->setText("rows and columns");
    }

    emit changeMatrix(mercury);
}

void matrixEnter::setOp(QListWidgetItem *i){
    QVariant func_type;
    func_type = i->data(100);
    op = func_type.toString();
    fctnCode = factory->getCode(op);
}

void matrixEnter::make_visible(int li, int co, /*MaceInt characteristic,*/ QListWidgetItem *i, bool vec, bool quad){

    q = quad;
    this->clean();

    mercury->setData(100,i->data(100));
    setOp(i);

    if (vec && op == "write a matrix") label->setText("write a vector");
    else label->setText(factory->get_info(op));

    lines = li;
    columns = co;

    matInfo = "No";

    if (fctnCode == 143){
        for(int i = 0; i < lines; i++){
            for(int j = 0; j <= columns; j++){
                dit = new MaceLineEdit;
                chooseMode(/*characteristic,*/dit);
                dit->setText("0");
                matrix->addWidget(dit,i,2*j,1, 1);
                edits.append(dit);
                if (j<columns){
                    hText = hText.number(j);
                    hText = hText.prepend("<font size=\"4\">&middot; X<sub>");
                    if(j < columns-1){
                        hText = hText.append("</sub>&nbsp;  + </font>");
                    }
                    else{
                        hText = hText.append("</sub> &nbsp; = </font>");
                    }
                    labHelp = new QLabel;
                    labHelp->setText(hText);
                    matrix->addWidget(labHelp,i,2*j+1,1, 1);
                    labels.append(labHelp);
                }
            }
        }
    }
    else{
        for(int i = 0; i < lines; i++){
            for(int j = 0; j < columns; j++){
                dit = new MaceLineEdit;
                chooseMode(/*characteristic,*/dit);
                dit->setText("0");
                matrix->addWidget(dit,i,j,1, 1);
                edits.append(dit);
            }
        }
    }

    info->setHtml(factory->help_info(op,fctnCode));

    if (op == "+ for matrices" || op =="- for matrices" || op == "cross product"
            || op == "change of basis" || op == "/ for matrices" || vec){
        changeLinCol->setHidden(true);
    }
    else{
        changeLinCol->setHidden(false);
    }

    info->setHidden(true);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    but->setFocus();
    emit hello();
    show();
}

void matrixEnter::chooseMode(/*MaceInt charac,*/ MaceLineEdit *edit){
    edit->all = true;
}

void matrixEnter::accept(){
    QString help;
    int count=0;

    matInfo = matInfo.number(lines);
    matInfo = matInfo.append(",");
    help = help.number(columns);
    matInfo = matInfo.append(help);

    resInfo = resInfo.number(lines);
    resInfo = resInfo.append(",1");

    QList<MaceLineEdit*>::iterator iter = edits.begin();
    while (iter != edits.end()){
        if (fctnCode == 143 && (count%(columns+1) == columns)){
            resInfo = resInfo.append(",");
            dit = *iter;
            resInfo = resInfo.append(dit->text());
        }
        else{
            matInfo = matInfo.append(",");
            dit = *iter;
            matInfo = matInfo.append(dit->text());
        }
        iter++;
        count++;
    }

    this->close();

    emit inserted();
}

void matrixEnter::clean(){

    QList<MaceLineEdit*>::iterator iter = edits.begin();
    while (iter != edits.end()){
        dit = *iter;
        matrix->removeWidget(dit);
        delete dit;
        iter++;
    }

    QList<QLabel*>::iterator iter2 = labels.begin();
    while (iter2 != labels.end()){
        labHelp = *iter2;
        delete labHelp;
        matrix->removeWidget(labHelp);
        iter2++;
    }

    labels.clear();
    edits.clear();
}

void matrixEnter::show_info(){
    if(info->isHidden())
        info->setHidden(false);
    else{
        info->setHidden(true);
        layout()->setSizeConstraint(QLayout::SetFixedSize);
    }
}

void matrixEnter::give(){
    this->exec();
}
