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

#include "helpdialog.h"

helpDialog::helpDialog(stringFactory *fac): factory(fac){
    setWindowIcon(QIcon("icons/MaceLogo.png"));

    vbox = new QVBoxLayout;
    hbox = new QHBoxLayout;
    but = new QPushButton("Close");
    browser = new QTextBrowser;

    vbox->addWidget(browser);

    hbox->addStretch();
    hbox->addWidget(but);

    vbox->addLayout(hbox);

    this->browser->setOpenLinks(false);

    datType = false;

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setLayout(vbox);
    QObject::connect(this->but,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(this->browser,SIGNAL(anchorClicked(QUrl)),this,SLOT(load(QUrl)));
}

helpDialog::~helpDialog(){

}

void helpDialog::setBrowser(QString str, int h, int w){
    this->browser->setGeometry(0,0,w,h);
    this->browser->setHtml(str);
}

void helpDialog::load(QUrl url){

    if(url.path() == "functions"){
        QString fctn = factory->fctnText();
        this->browser->setHtml(fctn);
    }
    else if(url.path() == "grammar"){
        QString fctn = factory->grammarText();
        this->browser->setHtml(fctn);
    }
    else if(url.path() == "plots"){
        QString fctn = factory->plotText();
        this->browser->setHtml(fctn);
    }
    else if(url.path() == "settings"){
        QString fctn = factory->settingText();
        this->browser->setHtml(fctn);
    }
    else if(url.path() == "datatypes"){
        QString fctn = factory->dataText();
        this->browser->setHtml(fctn);
        datType = true;
    }
    else if(url.path() == "hint"){
        QString fctn = factory->hint();
        this->browser->setHtml(fctn);
        datType = false;
    }
    else if(url.path() == "distributions"){
        QString fctn = factory->distributions();
        this->browser->setHtml(fctn);
        datType = false;
    }
    else if(url.path() == "residues"){
        QString fctn = factory->residues();
        this->browser->setHtml(fctn);
        datType = false;
    }
    else if(url.path() == "script"){
        QString fctn = factory->script();
        this->browser->setHtml(fctn);
        datType = false;
    }
    else{
        if(datType){
            QString fctn = factory->displayData(url.path());
            this->browser->setHtml(fctn);
            datType = false;
        }
        else{
            int i = factory->generalTypes.key(url.path());
            QString fctn = factory->fctnList(i, url.path());
            this->browser->setHtml(fctn);
        }
    }
}
