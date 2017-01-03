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

#include "macelistwidget.h"

MaceListWidget::MaceListWidget(stringFactory *factory, QListWidget *parent) :
    QListWidget(parent), itemSource(factory)
{
    posChar = false;

    item_adder_general(100,true);

    field = true;
}

MaceListWidget::~MaceListWidget()
{

}

void MaceListWidget::set_field(bool f){
    field = f;
    this->clear();
    item_adder_general(state,f);
}

void MaceListWidget::setNew(int code){
    this->clear();
    item_adder_general(code,field);
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Adds the QListWidgetItem to a QListWidget in alphabetical order.
//function_type is given by the following code:
//100: general
//110: analytic function
//121: number theoretic function
//125: functions for two variables in Euklidean rings
//126: prime factor decomposition
//128: factorial templates
//130: combinatorics
//141: linear algebra arbitrary precision
//142: linear algebra numerical matrix value
//143: system of linear equations matrix value
//144: linear algebra arbitrary precision skalar value
//145: linear algebra numerical skalar value
/////////////////////////////////////////////////////////////////////////////////////////////

void MaceListWidget::item_adder_general(int code, bool f){
    QString memory, name;
    QListWidgetItem *itm;
    int curCode, counter = 0;

    state = code;

    QMap<QString, fctnData >::iterator iter = itemSource->infos.begin();

    while(iter!=itemSource->infos.end()){

        curCode = iter.value().code;
        if (curCode == 200) {
            iter++;
            continue;
        }

        if (code == 100 || ((curCode-code >= 0) && (curCode-code < 10))){
            memory = iter.key();
            name = iter.value().name;

            itm = new QListWidgetItem(name);

            if(posChar){
                if(f){
                    if(curCode != 110 && curCode != 122 && curCode !=131 && curCode !=160 && curCode != 147 && !(curCode >= 170 && curCode < 180)){
                        itm->setData(100,memory);
                    }
                    else{
                        itm->setFlags(Qt::NoItemFlags);
                        itm->setData(100,"No");
                    }
                }
                else{
                    if(curCode == 121 || curCode == 140 || curCode == 130 || curCode>= 150 && curCode < 160){
                        itm->setData(100,memory);
                    }
                    else{
                        itm->setFlags(Qt::NoItemFlags);
                        itm->setData(100,"No");
                    }
                }
            }
            else{
                itm->setData(100,memory);
            }

            if(counter%2 == 0){itm->setBackgroundColor(QColor(235, 242, 233));}
            if (name!="No" || curCode >= 200) {counter++;}
            if(curCode > 0){this->addItem(itm);}

        }

        iter++;
    }
}
