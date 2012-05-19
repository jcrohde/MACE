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

#include "unboundint.h"

unboundInt::unboundInt()
{

    entries.append(0);
}

unboundInt::unboundInt(int a)
{
    a = a%BASE;
    if(a < 0){a = a+BASE;}
    entries.append(a);
}

unboundInt::unboundInt(QString str){
    QString help;
    int a;
    help = str.right(4);
    a = help.toInt();
    entries.append(a);
    if (str.length()>4){str = str.left(str.size()-4);}
    else { str = "";}

    while(str.length()>0){
        help = str.right(4);
        a = help.toInt();
        entries.append(a);
        if (str.length()>4){str = str.left(str.size()-4);}
        else { str = "";}
    }
}

unboundInt unboundInt::translate(long int i){
    int j = i%BASE;
    int k = (i -j)/BASE;
    unboundInt res(j);
    if (k > 0){
        j = k%BASE;
        res.entries.append(j);
        k = (i -j)/BASE;
        if (k > 0){
           j = k%BASE;
           res.entries.append(j);
        }
    }
    return res;
}

int unboundInt::toInt(){
    QList<int>::iterator iter = entries.begin();
    int res = *iter;
    return res;
}

    QString unboundInt::print(){
        QString res = "", help;
        QList<int>::iterator iter = entries.begin();
        QList<int>::iterator iter2 = entries.begin();

        while (iter !=entries.end()){
            iter2++;
            help = help.number(*iter);
            res = res.prepend(help);
            if(iter2 != entries.end()){
                if(*iter<10){res.prepend("000");}
                else if(*iter<100){res.prepend("00");}
                else if(*iter<1000){res.prepend("0");}
            }
            iter++;
        }

        return res;
    }

    unboundInt unboundInt::mult(int i){

        unboundInt res, tmp(*this);
        res.entries.pop_front();

        int j, over;
        QList<int>::iterator iter = tmp.entries.begin();

        j= i*(*iter);


        over =j%BASE;
        res.entries.append(over);
        over =j-over;
        over = over/BASE;

        iter++;
        while(iter !=tmp.entries.end()){
            j= i*(*iter);
            j = j+over;

            over =j%BASE;
            res.entries.append(over);
            over =j-over;
            over = over/BASE;
            iter++;
        }

        if (over >0){
            res.entries.append(over);
        }

        return res;
    }

    void unboundInt::shift(int i){
          for (int d =1 ; d<=i;++d){
            entries.push_front(0);
          }
    }

    bool unboundInt::geq(int i){
        if(entries.length() > 1){return true;}
        else{
            if (*entries.begin() >= (i%BASE)){return true;}
            else {return false;}
        }
    }

    unboundInt unboundInt::divi(int i){
        i = i%BASE;
        unboundInt res;
        res.entries.pop_front();
        int over=0, j;
        bool first;
        QList<int>::iterator iter = entries.end();

        while(this->geq(i) && iter != entries.begin()){
             iter--;
             j=((*iter)+over)/i;
             over = ((*iter)+over)-(j*i);
             res.entries.push_front(j);
             over = over*BASE;

        }

        res = res.cut();

        return res;
    }

    unboundInt unboundInt::sub(int i){
        i = i%BASE;
        unboundInt res;
        res.entries.pop_front();
        int over=i, j;
        bool first;
        QList<int>::iterator iter = entries.begin();

        while(this->geq(i) && iter != entries.end()){
            j = *iter-over;
            if(j <0){
                over =1;
                j = j+BASE;
            }
            else{over = 0;}
            res.entries.push_back(j);
            iter++;
        }

        return res;
    }

    unboundInt unboundInt::cut(){
        unboundInt res;
        res.entries.pop_front();
        QList<int>::iterator iter = entries.end();
        iter--;

        if(*iter != 0 ){res.entries.push_front(*iter);}

        while (iter != entries.begin()){
            iter--;
            res.entries.push_front(*iter);
        }

        return res;
    }

    unboundInt unboundInt::firstOnes(int i){
        unboundInt res;
        if (i>0){
            res.entries.pop_front();
            QList<int>::iterator iter = entries.end();

            for (int j = 1; j<= i;j++){
                iter--;
                res.entries.push_front(*iter);
            }
        }
        return res;
    }

    double unboundInt::toDouble(){
        unboundInt tmp(*this);
        double res= 0, factor = 1, du;
        for (QList<int>::iterator iter = tmp.entries.begin(); iter !=tmp.entries.end(); iter++){
            du = (double) *iter;
            res = res+(du*factor);
            factor = factor*10000.0;
        }
        return res;
    }
