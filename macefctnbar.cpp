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

#include "macefctnbar.h"

MaceFctnBar::MaceFctnBar(QWidget *parent) :
    QHBoxLayout(parent)
{
    field = true;
    posChar = false;

    this->setSpacing(0);

    FBut = new ItemButton("F (ell int 1.)",30,100,10,160);
    FBut->setString("elliptic integral of first kind");
    FBut->setNewString("f");
    GammaBut = new ItemButton(QString((QChar)0x0393),30,25,10,160);
    GammaBut->setString("Gamma function");
    GammaBut->setNewString("gamma");
    JBut = new ItemButton("J (Bessel)",30,80,10,160);
    JBut->setString("Bessel function");
    JBut->setNewString("j");
    LagBut = new ItemButton("Legendre polynomial",30,155,10,160);
    LagBut->setString("Legendre polynomial");
    LagBut->setNewString("legendre");
    PIBut = new ItemButton("PI (ell int 3.)",30,100,10,160);
    PIBut->setString("elliptic integral of third kind");
    PIBut->setNewString("pi3");

    facBut = new ItemButton("a!",30,35,10,121);
    facBut->setString("a!");

    aChooseBBut = new ItemButton("a choose b",30,80,10,121);
    aChooseBBut->setString("a choose b");

    detBut = new ItemButton("det",30,50,10,142);
    detBut->setString("determinant of a matrix");

    modBut = new ItemButton("%",30,50,10,125);
    modBut->setString("% (modulo)");
    gcdBut = new ItemButton("gcd",30,50,10,125);
    gcdBut->setString("greatest common divisor");

    bindBut = new ItemButton("binomial dist",30,100,10,131);
    bindBut->setString("binomial distribution");

    expdBut = new ItemButton("exponential dist",30,120,10,131);
    expdBut->setString("exponential distribution");

    nordBut = new ItemButton("normal dist",30,90,10,131);
    nordBut->setString("normal distribution");

    paretoBut = new ItemButton("Pareto dist",30,100,10,131);
    paretoBut->setString("Pareto distribution");
    paretoBut->setNewString("pareto distribution");
    poissonBut = new ItemButton("Poisson dist",30,110,10,131);
    poissonBut->setString("Poisson distribution");
    poissonBut->setNewString("poisson distribution");
    primeBut = new ItemButton("primality test",30,110,10,126);
    primeBut->setString("primality test");

    inverseBut = new ItemButton("inverse",30,70,10,141);
    inverseBut->setString("inverse matrix");
    rankBut = new ItemButton("rank",30,40,10,141);
    rankBut->setString("rank of a matrix");
    miniPolyBut = new ItemButton("minimal polynomial",30,140,10,141);
    miniPolyBut->setString("minimal polynomial of a matrix");


    cosBut = new ItemButton("cos",30,50,10,110);
    cosBut->setString("cos");
    sinBut = new ItemButton("sin",30,50,10,110);
    sinBut->setString("sin");
    expBut = new ItemButton("exp",30,50,10,110);
    expBut->setString("exp");

    tanBut  = new ItemButton("tan",30,50,10,110);
    tanBut->setString("tan");

    logBut = new ItemButton("log_a(b)",30,70,10,110);
    logBut->setString("log_a(b)");

    SLEBut = new ItemButton("system of linear equations",30,180,10,143);
    SLEBut->setString("solve a system of linear equations");

    variableBut = new ItemButton("execute",30,100,10,151);
    variableBut->setString("execute");
    andBut = new ItemButton("AND",30,70,10,150);
    andBut->setString("and");
    orBut = new ItemButton("OR",30,50,10,150);
    orBut->setString("or");
    smallBut = new ItemButton("<",30,50,10,150);
    smallBut->setString("<");
    largBut = new ItemButton(">",30,50,10,150);
    largBut->setString(">");
    sketchBut = new ItemButton("curve sketching",30,120,10,150);
    sketchBut->setString("curve sketching");

    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    addWidget(FBut);
    addWidget(GammaBut);
    addWidget(JBut);
    addWidget(LagBut);
    addWidget(PIBut);

    addWidget(detBut);

    addWidget(modBut);

    addWidget(aChooseBBut);
    addWidget(facBut);

    addWidget(gcdBut);
    addWidget(primeBut);

    addWidget(cosBut);
    addWidget(sinBut);
    addWidget(tanBut);
    addWidget(expBut);
    addWidget(logBut);

    addWidget(inverseBut);
    addWidget(miniPolyBut);
    addWidget(rankBut);
    addWidget(SLEBut);

    addWidget(bindBut);
    addWidget(expdBut);
    addWidget(nordBut);
    addWidget(paretoBut);
    addWidget(poissonBut);

    addWidget(variableBut);
    addWidget(andBut);
    addWidget(orBut);
    addWidget(smallBut);
    addWidget(largBut);

    addWidget(sketchBut);

    addItem(spacer);

    buttons.append(FBut);
    buttons.append(GammaBut);
    buttons.append(JBut);
    buttons.append(LagBut);
    buttons.append(PIBut);

    buttons.append(facBut);
    buttons.append(aChooseBBut);
    buttons.append(detBut);
    buttons.append(gcdBut);
    buttons.append(logBut);
    buttons.append(SLEBut);

    buttons.append(bindBut);
    buttons.append(expdBut);
    buttons.append(nordBut);

    buttons.append(cosBut);
    buttons.append(sinBut);
    buttons.append(expBut);
    buttons.append(tanBut);

    buttons.append(modBut);
    buttons.append(paretoBut);
    buttons.append(poissonBut);
    buttons.append(primeBut);

    buttons.append(inverseBut);
    buttons.append(rankBut);
    buttons.append(miniPolyBut);

    buttons.append(variableBut);
    buttons.append(andBut);
    buttons.append(orBut);
    buttons.append(smallBut);
    buttons.append(largBut);
    buttons.append(sketchBut);

    item = new QListWidgetItem;

    field = true;

    setNew(100);

    QObject::connect(FBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(GammaBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(JBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(LagBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(PIBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));

    QObject::connect(facBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(aChooseBBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(detBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(gcdBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(logBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(SLEBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(bindBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(expdBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(nordBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(cosBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(sinBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(expBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(tanBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(modBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(paretoBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(poissonBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(primeBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(inverseBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(rankBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(miniPolyBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(variableBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(andBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(orBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(smallBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(largBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));
    QObject::connect(sketchBut,SIGNAL(sig_string(QPair<QString,int>)),this,SLOT(setItem(QPair<QString,int>)));

}

MaceFctnBar::~MaceFctnBar()
{

}

void MaceFctnBar::setItem(QPair<QString, int> pair){
    item->setData(100,pair.first);
    emit sendItem(item);
}

void MaceFctnBar::setNew(int code){
    ItemButton *ptr;

    if(code == 100 || code == 170){
        for (QList<ItemButton*>::iterator iter = buttons.begin(); iter != buttons.end(); iter++){
            ptr = *iter;
            ptr->setHidden(true);
        }

        gcdBut->setVisible(true);
        gcdBut->setEnabled(field);
        logBut->setVisible(true);
        logBut->setDisabled(posChar);
        SLEBut->setVisible(true);
        SLEBut->setEnabled(field);
        nordBut->setVisible(true);
        nordBut->setDisabled(posChar);
        sketchBut->setVisible(true);
        sketchBut->setDisabled(posChar);
    }
    else{
        for (QList<ItemButton*>::iterator iter = buttons.begin(); iter != buttons.end(); iter++){
            ptr = *iter;
            ptr->setVisible(code<=ptr->pair.second && code+10 > ptr->pair.second);
            ptr->setDisabled((ptr->pair.second == 110 && posChar)  || (ptr->pair.second == 131 && posChar) ||
                ((ptr->pair.second == 125 || ptr->pair.second == 126 ||
                ptr->pair.second == 141 || ptr->pair.second == 142 || ptr->pair.second == 143) && !field) ||
                (ptr->pair.second == 160 && posChar));
        }
    }
    codeMem = code;
}

void MaceFctnBar::set_field(bool f){
    field = f;
    setNew(codeMem);
}
