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

#include "opwindow.h"

opWindow::opWindow(QString op)
{

    ok = false;

    vbox = new QVBoxLayout;

    hbox = new QHBoxLayout;
    hbox1 = new QHBoxLayout;
    hbox2 = new QHBoxLayout;

    but = new QPushButton("Ok");
    but2 = new QPushButton("No");

    line1 = new QLineEdit;
    line2 = new QLineEdit;

    if (op == "^"){
      labelStr = "Compute a";
      labelStr = labelStr.append(op);
      labelStr = labelStr.append("b for");
    }
    else if (op == "%" || op == "choose"){
      labelStr = "Compute a ";
      labelStr = labelStr.append(op);
      labelStr = labelStr.append(" b for");
    }
    else if (op == "!"){
      labelStr = "Compute a! for";
    }
    else if (op == "1/"){
      labelStr = "Compute 1/a for";
    }
    else if(op == "exp_" || op == "log_"){
        labelStr = "Compute ";
        labelStr = labelStr.append(op);
        labelStr = labelStr.append("a(b) for");
    }
    else if(op == "gcd" || op == "lcm" || op == "extended Euklid"){
        labelStr = "Compute ";
        labelStr = labelStr.append(op);
        labelStr = labelStr.append("(a,b) for");
    }
    else {
        labelStr = "Compute ";
        labelStr = labelStr.append(op);
        labelStr = labelStr.append("(a) for");
    }

    //label = new QLabel("Compute a % b for");
    label = new QLabel(labelStr);

    label1 = new QLabel("a  = ");
    label2 = new QLabel("b  = ");

    vbox->addWidget(label);

    hbox1->addWidget(label1);
    hbox1->addWidget(line1);
    vbox->addLayout(hbox1);

    if(op == "%" || op == "gcd" || op == "lcm" || op == "extended Euklid" || op == "^" || op == "exp_" || op == "log_" || op == "choose"){
      hbox2->addWidget(label2);
      hbox2->addWidget(line2);
      vbox->addLayout(hbox2);
    }

    hbox->addWidget(but);
    hbox->addWidget(but2);
    vbox->addLayout(hbox);
    setLayout(vbox);

    QWidget::connect(but2,SIGNAL(clicked()),this,SLOT(close()));
}

opWindow::~opWindow(){

}

void opWindow::accept(){
    ok = true;
    a = line1->text();
    b = line2->text();
    this->close();
}
