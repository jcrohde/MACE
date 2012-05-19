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

#ifndef UNBOUNDINT_H
#define UNBOUNDINT_H
#include <QList>
#include <QString>
#define BASE 10000

class unboundInt
{
public:
    QList<int> entries;

    unboundInt();
    unboundInt(int a);
    unboundInt(QString str);

    unboundInt cut();
    unboundInt divi(int i);
    unboundInt firstOnes(int i);
    bool geq(int i);
    unboundInt mult(int i);
    QString print();
    void shift(int i);
    unboundInt sub(int i);
    double toDouble();
    int toInt();
    unboundInt translate(long int i);

    friend unboundInt operator+( unboundInt a, unboundInt b)
    {
       int over = 0, r=0;

       unboundInt res;
       res.entries.pop_front();

       QList<int>::iterator iter = a.entries.begin();
       QList<int>::iterator iter2 = b.entries.begin();

       while (iter != a.entries.end() || iter2 != b.entries.end() || over >0){


         r = over;
         if(iter != a.entries.end()){r = r+ *iter;}
         if(iter2 != b.entries.end()){r = r+ *iter2;}

       over = r;
       r =r%BASE;
       over = (over-r)/BASE;

       res.entries.append(r);

       if(iter != a.entries.end()){iter++;}
       if(iter2 != b.entries.end()){iter2++;}
   }


    return res;
    }

    unboundInt operator-(unboundInt b ) const
    {
       int over = 0, r=0;

       unboundInt res, a(*this);


       QList<int>::iterator iter = a.entries.begin();
       QList<int>::iterator iter2 = b.entries.begin();


       if(a >= b){
       res.entries.pop_front();
       while (iter != a.entries.end() || iter2 != b.entries.end() || over >0){


         r = over;
         if(iter != a.entries.end()){r = r+ *iter;}
         if(iter2 != b.entries.end()){r = r- *iter2;}


         if (r<0){r+=BASE; over = -1;}
         else {over = 0;}

         res.entries.append(r);

         if(iter != a.entries.end()){iter++;}
         if(iter2 != b.entries.end()){iter2++;}
       }
       }
      return res;
    }

     friend unboundInt operator*( unboundInt a, unboundInt b)
     {

        int i = 0;
        unboundInt res, help;

        if(a !=res && b != res){
        QList<int>::iterator iter = a.entries.begin();

        while(iter!=a.entries.end()){
            help = b.mult(*iter);
            help.shift(i);
            res = res+help;
            i++;
            iter++;
        }
        }
        return res;
    }

    unboundInt operator/(unboundInt b ) const {
        QList<int>::iterator iter;
        unboundInt res, help, q, p, one(1), r, tmp(*this);

        help = tmp;
        if (b.entries.length()== 1){res = help.divi(*b.entries.begin());}
        else if( help >= b){

            iter = b.entries.end();
            iter--;
            while(*iter < BASE/2){
                help = help.mult(2);
                b = b.mult(2);
                iter = b.entries.end();
                iter--;
            }

            while (help.entries.length()>b.entries.length()){
                p = help.firstOnes(b.entries.length()+1);
                iter = help.entries.end();
                iter--;
                q = b.mult(*iter);
                r = one.mult(*iter);

                q.shift(help.entries.length()-b.entries.length()-2);
                r.shift(help.entries.length()-b.entries.length()-2);
                help = help-q;
                res = res+r;

                iter = help.entries.end();
                iter--;
                while (*iter == 0 && help.entries.length()>1){
                    help = help.cut();
                    iter = help.entries.end();
                    iter--;
                }

            }
            if (help>=b){res = res+one;}
        }
        return res;
    }

    bool operator>=(unboundInt b){
        unboundInt a(*this);
        bool yes = true;
        if (a.entries.length() > b.entries.length()){return true;}
        else if (a.entries.length() < b.entries.length()){return false;}
        else {
            QList<int>::iterator iter1 =a.entries.end();
            QList<int>::iterator iter2 =b.entries.end();

            while(iter1 != a.entries.begin()){
                iter1--;
                iter2--;
                if (*iter1 > *iter2){yes = true; break;}
                if (*iter1 < *iter2){yes = false; break;}
            }
            return yes;
        }
    }


    bool operator>(unboundInt b){
        unboundInt a(*this);
        bool yes = false;
        if (a.entries.length() > b.entries.length()){return true;}
        else if (a.entries.length() < b.entries.length()){return false;}
        else {
            QList<int>::iterator iter1 =a.entries.end();
            QList<int>::iterator iter2 =b.entries.end();

            while(iter1 != a.entries.begin()){
                iter1--;
                iter2--;
                if (*iter1 > *iter2){yes = true; break;}
                if (*iter1 < *iter2){yes = false; break;}
            }
            return yes;
        }
    }

    bool operator==(unboundInt b){
        unboundInt a(*this);
        bool yes = true;
        if (a.entries.length() != b.entries.length()){return false;}
        else {
            QList<int>::iterator iter1 =a.entries.end();
            QList<int>::iterator iter2 =b.entries.end();

            while(iter1 != a.entries.begin()){
                iter1--;
                iter2--;
                if (*iter1 != *iter2){yes = false; break;}
                if (*iter1 != *iter2){yes = false; break;}
            }
            return yes;
        }
    }

    bool operator!=(unboundInt b){
        unboundInt a(*this);
        if (a==b){return false;}
        else{return true;}
    }

};

#endif // UNBOUNDINT_H
