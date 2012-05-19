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

#include "mydialog.h"

myDialog::myDialog(QWidget *parent)
{

    edits= 0;
    but = new QPushButton("Ok");
    but2 = new QPushButton("No");
    hboxes = 0;
    hbox = 0;
    vbox = 0;
    lines = 2;
    columns = 1;
    matInfo = "No";


}

myDialog::myDialog(int i,  int j, QString text)
{
    edits= 0;
    label = new QLabel(text);
    but = new QPushButton("Ok");
    but2 = new QPushButton("No");
    hboxes = 0;


    lines = i;
    columns = j;

    matInfo = "No";

    vbox = new QVBoxLayout;

        vbox->addWidget(label);

        hboxes = new hboxList();
        int k, h = 1;

        for (k = 1; k < lines; k++){
            hboxes->append();
        }

        edits = new lineEditList("0");

        for (k= 0; k<lines; k++){
           while (h<columns){
           edits->append("0");
           h++;
           }
           h = 0;
        }

        lineEditList *edIter = edits;
        hboxList *boxIter = hboxes;
        h= 0;

        while (boxIter != 0){
            while(h<columns){
                boxIter->line->addWidget(edIter->line);
                h++;
                edIter= edIter ->next;
            }
            h = 0;
            hbox= boxIter->line;
            vbox->addLayout(hbox);
            boxIter = boxIter->next;
        }

        hbox = new QHBoxLayout;

        hbox->addStretch();
        hbox->addWidget(but);
        hbox->addWidget(but2);

        vbox->addLayout(hbox);
        setLayout(vbox);

}



void myDialog::accept(){
    QString help;
    lineEditList *iter = this->edits;

    matInfo = matInfo.number(lines);
    matInfo = matInfo.append(",");
    help = help.number(columns);
    matInfo = matInfo.append(help);

    help = iter->line->text();

    matInfo = matInfo.append(",");
    matInfo = matInfo.append(help);

    iter = iter->next;
    while(iter!= 0){
        matInfo = matInfo.append(",");
        matInfo = matInfo.append(iter->line->text());
        iter = iter ->next;
    }

    this->close();
}

myDialog::~myDialog(){
    delete edits;
    delete hboxes;
}

void myDialog::give(){
    this->exec();
}

