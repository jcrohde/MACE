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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "numbertheory.h"
#include <parser.h>
#include "strings.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    test = new myMenuBar;
    setMenuBar(test);


    secBar = new SecMenuBar;
    this->addToolBar(secBar);

    infos = new helpDialog();

    text1="";
        ui->line->setAlignment(Qt::AlignRight);
        ans=0;
        charac = 0;
        memory = "";

        lines = 2;
        columns = 2;

        ganz = false;
        cplx = false;
        linAlg = false;
        poly = false;
        nth = false;
        alg = false;

        sb = ui->line->verticalScrollBar();

        QObject::connect(ui->but1,SIGNAL(clicked()),this,SLOT(addi()));
        QObject::connect(ui->but2,SIGNAL(clicked()),this,SLOT(subs()));
        QObject::connect(ui->but3,SIGNAL(clicked()),this,SLOT(mult()));
        QObject::connect(ui->but4,SIGNAL(clicked()),this,SLOT(divi()));
        QObject::connect(ui->but5,SIGNAL(clicked()),this,SLOT(mod()));
        QObject::connect(ui->equal,SIGNAL(clicked()),this,SLOT(em()));
        QObject::connect(ui->one,SIGNAL(clicked()),this,SLOT(mone()));
        QObject::connect(ui->two,SIGNAL(clicked()),this,SLOT(mtwo()));
        QObject::connect(ui->three,SIGNAL(clicked()),this,SLOT(mthree()));
        QObject::connect(ui->four,SIGNAL(clicked()),this,SLOT(mfour()));
        QObject::connect(ui->five,SIGNAL(clicked()),this,SLOT(mfive()));
        QObject::connect(ui->six,SIGNAL(clicked()),this,SLOT(msix()));
        QObject::connect(ui->seven,SIGNAL(clicked()),this,SLOT(mseven()));
        QObject::connect(ui->eight,SIGNAL(clicked()),this,SLOT(meight()));
        QObject::connect(ui->nine,SIGNAL(clicked()),this,SLOT(mnine()));
        QObject::connect(ui->zero,SIGNAL(clicked()),this,SLOT(mzero()));
        QObject::connect(ui->reset,SIGNAL(clicked()),this,SLOT(mreset()));
        QObject::connect(ui->dot,SIGNAL(clicked()),this,SLOT(mdot()));
	
	QObject::connect(ui->ibut,SIGNAL(clicked()),this,SLOT(mi()));
        QObject::connect(ui->klammA,SIGNAL(clicked()),this,SLOT(mkla()));
        QObject::connect(ui->klammZ,SIGNAL(clicked()),this,SLOT(mklz()));
        QObject::connect(ui->xbut,SIGNAL(clicked()),this,SLOT(mx()));
        QObject::connect(ui->powerbut,SIGNAL(clicked()),this,SLOT(mpower()));

        QObject::connect(ui->cbut,SIGNAL(clicked()),this,SLOT(mC()));
	
	QObject::connect(ui->bgcd,SIGNAL(clicked()),this,SLOT(mgcd()));
	QObject::connect(ui->blcm,SIGNAL(clicked()),this,SLOT(mlcm()));
	QObject::connect(ui->bExEu,SIGNAL(clicked()),this,SLOT(mExEu()));

        QObject::connect(ui->primebut,SIGNAL(clicked()),this,SLOT(mPrime()));
        QObject::connect(ui->pFacBut,SIGNAL(clicked()),this,SLOT(mPrimeDec()));
        QObject::connect(ui->phiBut,SIGNAL(clicked()),this,SLOT(mphi()));
        QObject::connect(ui->fiboBut,SIGNAL(clicked()),this,SLOT(mfibo()));

        QObject::connect(ui->lambdabut,SIGNAL(clicked()),this,SLOT(mlambda()));
        QObject::connect(ui->psibut,SIGNAL(clicked()),this,SLOT(mpsi()));
        QObject::connect(ui->facbut,SIGNAL(clicked()),this,SLOT(mfacnum()));
        QObject::connect(ui->pibut,SIGNAL(clicked()),this,SLOT(mpi()));
        QObject::connect(ui->facSumbut,SIGNAL(clicked()),this,SLOT(mfacsum()));

        QObject::connect(this->secBar->charAction,SIGNAL(triggered()),this,SLOT(setChar()));



        QObject::connect(ui->writeMatrixBut,SIGNAL(clicked()),this,SLOT(mWriteMatrix()));
        QObject::connect(ui->SLEBut,SIGNAL(clicked()),this,SLOT(mSLESolve()));
        QObject::connect(ui->transBut,SIGNAL(clicked()),this,SLOT(mtranspose()));
        QObject::connect(ui->gaussBut,SIGNAL(clicked()),this,SLOT(mgauss()));
        QObject::connect(ui->invBut,SIGNAL(clicked()),this,SLOT(mmatInv()));

        QObject::connect(ui->rankBut,SIGNAL(clicked()),this,SLOT(mrank()));
        QObject::connect(ui->detBut,SIGNAL(clicked()),this,SLOT(mdet()));
        QObject::connect(ui->charPolyBut,SIGNAL(clicked()),this,SLOT(mcharPoly()));
        QObject::connect(ui->miniPolyBut,SIGNAL(clicked()),this,SLOT(mminiPoly()));

        QObject::connect(ui->matMultBut,SIGNAL(clicked()),this,SLOT(mmatMult()));
        QObject::connect(ui->matAddBut,SIGNAL(clicked()),this,SLOT(mmatAdd()));
        QObject::connect(ui->matSubBut,SIGNAL(clicked()),this,SLOT(mmatSub()));


        QObject::connect(ui->LineBox,SIGNAL(valueChanged(int)),this,SLOT(setLine(int)));
        QObject::connect(ui->ColumnBox,SIGNAL(valueChanged(int)),this,SLOT(setColumn(int)));

        QObject::connect(this->test->closeAction,SIGNAL(triggered()),this,SLOT(close()));
        QObject::connect(this->test->licenseAction,SIGNAL(triggered()),this,SLOT(showInfo()));
        QObject::connect(this->test->hintAction,SIGNAL(triggered()),this,SLOT(showHints()));
        QObject::connect(this->test->authorAction,SIGNAL(triggered()),this,SLOT(showAuthor()));

        QObject::connect(ui->facBut,SIGNAL(clicked()),this,SLOT(mfac()));

        QObject::connect(ui->sinBut,SIGNAL(clicked()),this,SLOT(msin()));
        QObject::connect(ui->arcsinBut,SIGNAL(clicked()),this,SLOT(marcsin()));
        QObject::connect(ui->cosBut,SIGNAL(clicked()),this,SLOT(mcos()));
        QObject::connect(ui->arccosBut,SIGNAL(clicked()),this,SLOT(marccos()));
        QObject::connect(ui->tanBut,SIGNAL(clicked()),this,SLOT(mtan()));
        QObject::connect(ui->arctanBut,SIGNAL(clicked()),this,SLOT(marctan()));
        QObject::connect(ui->cotBut,SIGNAL(clicked()),this,SLOT(mcot()));
        QObject::connect(ui->arccotBut,SIGNAL(clicked()),this,SLOT(marccot()));
        QObject::connect(ui->expBut,SIGNAL(clicked()),this,SLOT(mexp()));
        QObject::connect(ui->logBut,SIGNAL(clicked()),this,SLOT(mlog()));
        QObject::connect(ui->xBut,SIGNAL(clicked()),this,SLOT(minv()));
        QObject::connect(ui->xyBut,SIGNAL(clicked()),this,SLOT(mPower()));
        QObject::connect(ui->logABut,SIGNAL(clicked()),this,SLOT(mlogA()));
        QObject::connect(ui->rootBut,SIGNAL(clicked()),this,SLOT(msqrt()));
        QObject::connect(ui->binoBut,SIGNAL(clicked()),this,SLOT(mbino()));
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showInfo(){
    QObject::connect(this->infos->but,SIGNAL(clicked()),this->infos,SLOT(close()));
    infos->setEdit(lic(),300,550);
    infos->exec();
}

void MainWindow::showHints(){
    QObject::connect(this->infos->but,SIGNAL(clicked()),this->infos,SLOT(close()));
    infos->setEdit(hints(),500,400);
    infos->exec();
}

void MainWindow::showAuthor(){
    QObject::connect(this->infos->but,SIGNAL(clicked()),this->infos,SLOT(close()));
    infos->setEdit(auth(),170,430);
    infos->exec();
}

void MainWindow::standardWrite(){
    if (linAlg){
        memory = memory.append(str1);
        str1 = "";
    }

    str = memory;
    if(!linAlg && str != "" && text1 != "") {str = str.append("<br>");}
    if(text1 != ""){str = str.append(text1);}

    ui->line->setHtml(str);

    sb->setValue(sb->maximum());
    linAlg = false;
    if (text1.indexOf("e")>-1){memory = str; text1 = "";}
}

void MainWindow::mdot()
{
    text1+=ui->dot->text();
    this->standardWrite();
}



void MainWindow::mreset()
{
    memory = "";
    text1="";
    ui->line->clear();
}
void MainWindow::mone()
{


    text1+=ui->one->text();
    this->standardWrite();

}
void MainWindow::mtwo()
{

    text1+=ui->two->text();
    this->standardWrite();

}
void MainWindow::mthree()
{

    text1+=ui->three->text();
    this->standardWrite();

}
void MainWindow::mfour()
{

    text1+=ui->four->text();
    this->standardWrite();

}
void MainWindow::mfive()
{

    text1+=ui->five->text();
    this->standardWrite();

}
void MainWindow::msix()
{

    text1+=ui->six->text();
    this->standardWrite();

}
void MainWindow::mseven()
{

    text1+=ui->seven->text();
    this->standardWrite();

}
void MainWindow::meight()
{

    text1+=ui->eight->text();
    this->standardWrite();

}
void MainWindow::mnine()
{

    text1+=ui->nine->text();
    this->standardWrite();

}
void MainWindow::mzero()
{

    text1+=ui->zero->text();
    this->standardWrite();

}
void MainWindow::mkla()
{

    text1+="(";
    this->standardWrite();

}
void MainWindow::mklz()
{

    text1+=")";
    this->standardWrite();

}
void MainWindow::mi()
{

    text1+="i";
    this->standardWrite();

}
void MainWindow::mx()
{

    text1+="x";
    this->standardWrite();

}
void MainWindow::mpower()
{

    text1+="^";
    this->standardWrite();

}
void MainWindow::mC()
{
    text1=text1.left(text1.size()-1);
    this->standardWrite();
}
void MainWindow::addi()         //Addition
{
    text1.append("+");
    this->standardWrite();
}
void MainWindow::subs()         //Substraction
{
    text1.append("-");
    this->standardWrite();
}
void MainWindow::mult()          //Multiplaction
{
    text1.append("*");
    this->standardWrite();
}
void MainWindow::divi()          //Division
{
    text1.append("/");
    this->standardWrite();
}



//Here the number theoretic functions///////////////////////////////////////////////////////

void MainWindow::showNThDialog(QString op){

    nthWindow = new opWindow(op);
    QWidget::connect(this->nthWindow->but,SIGNAL(clicked()),this->nthWindow,SLOT(accept()));
    nthWindow->exec();
    if (this->nthWindow->ok){

        if(memory != "" && text1 != "") {
            memory = memory.append("<br>");
        }
        memory = memory.append(text1);
        text1= "";

        memory= memory.append(str1);
        str1 = "";

        if (this->nthWindow->a.indexOf("x")>-1 || this->nthWindow->b.indexOf("x")>-1){
            if (charac == 0){
                if(op == "factors_of"){
                   realParsNComp(this->nthWindow->a, &pol, charac);
                }
                else{
                    realParsNComp(this->nthWindow->a, &apol, charac);
                    realParsNComp(this->nthWindow->b, &apol1, charac);
                }

            }
            else{
                realParsNComp(this->nthWindow->a, &rpol, charac);
                realParsNComp(this->nthWindow->b, &rpol1, charac);

            }
        }
        else{
            if (op == "sin" || op == "cos" || op == "tan" || op == "cot" || op == "exp" || op == "ln" || op == "1/"
                 || op == "^" || op == "sqrt" || op == "log_" || op == "arcsin" || op == "arccos" || op == "arctan" || op == "arccot"){
                dans = this->nthWindow->a.toDouble();
                dans1 = this->nthWindow->b.toDouble();
            }
            else{
              inum = this->nthWindow->a.toInt();
              inum1 = this->nthWindow->b.toInt();
            }
        }
      if(memory != "") {memory = memory.append("<br>");}
      if (op == "%" || op == "^"){
        memory = memory.append(this->nthWindow->a);
        memory = memory.append(op);
        memory = memory.append(this->nthWindow->b);
        memory = memory.append(" = ");
      }
      else if (op == "choose"){
        memory = memory.append(this->nthWindow->a);
        memory = memory.append(" ");
        memory = memory.append(op);
        memory = memory.append(" ");
        memory = memory.append(this->nthWindow->b);
        memory = memory.append(" = ");
      }
      else if (op == "exp_" || op == "log_"){
        memory = memory.append(op);
        memory = memory.append(this->nthWindow->a);
        memory = memory.append("(");
        memory = memory.append(this->nthWindow->b);
        memory = memory.append(") = ");
      }
      else if (op == "!"){
        memory = memory.append(this->nthWindow->a);
        memory = memory.append("!");
        memory = memory.append(" = ");
      }
      else if (op == "1/"){
        memory = memory.append("1/");
        memory = memory.append(this->nthWindow->a);
        memory = memory.append(" = ");
      }
      else if(op == "gcd" || op == "lcm"){
          memory = memory.append(op);
          memory = memory.append("(");
          memory = memory.append(this->nthWindow->a);
          memory = memory.append(",");
          memory = memory.append(this->nthWindow->b);
          memory = memory.append(") = ");
      }
      else if(op == "extended Euklid"){
          memory = memory.append(op);
          memory = memory.append("(");
          memory = memory.append(this->nthWindow->a);
          memory = memory.append(",");
          memory = memory.append(this->nthWindow->b);
          memory = memory.append("): ");
      }
      else{
          memory = memory.append(op);
          memory = memory.append("(");
          memory = memory.append(this->nthWindow->a);
          memory = memory.append(") = ");
      }
    }
}

void MainWindow::mod()          //Rest
{
    showNThDialog("%");
    if (this->nthWindow->ok){
      if (this->nthWindow->a.indexOf("x")==-1 && this->nthWindow->b.indexOf("x")==-1){
        if(inum1 != 0){ians = inum%inum1;}
        else {ians = inum;}
        text1 = text1.number(ians);
      }
      else{
        if (charac == 0){
           aanspol = apol%apol1;
           aanspol=aanspol.normalize();
           text1=aanspol.print();
        }
        else {
            ranspol = rpol%rpol1;
            ranspol=ranspol.normalize();
            text1=ranspol.print();
        }
      }
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}
void MainWindow::mgcd()          //greatest common divisor
{
    showNThDialog("gcd");
    if (this->nthWindow->ok){
        if (this->nthWindow->a.indexOf("x")==-1 && this->nthWindow->b.indexOf("x")==-1){
          ians = gcd(inum,inum1);
          text1 = text1.number(ians);
        }
          else{
            if (charac == 0){
               aanspol = gcd(apol,apol1);
               aanspol=aanspol.normalize();
               text1=aanspol.print();
            }
            else {
                ranspol = gcd(rpol,rpol1);
                ranspol=ranspol.normalize();
                text1=ranspol.print();
            }
          }
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
  }
  delete this->nthWindow;
}
void MainWindow::mlcm()          //least common multiple
{
    showNThDialog("lcm");
    if (this->nthWindow->ok){

        if (this->nthWindow->a.indexOf("x")==-1 && this->nthWindow->b.indexOf("x")==-1){
          ians = lcm(inum,inum1);
          text1 = text1.number(ians);
        }
          else{
            if (charac == 0){

                aanspol = lcm(apol,apol1);
                aanspol=aanspol.normalize();
                text1=aanspol.print();
            }
            else {
                ranspol = lcm(rpol,rpol1);
                ranspol=ranspol.normalize();
                text1=ranspol.print();
            }
          }
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
  delete this->nthWindow;
}
void MainWindow::mExEu()          //extended Eukledian algorithm
{
    showNThDialog("extended Euklid");
    if (this->nthWindow->ok){
        if (this->nthWindow->a.indexOf("x")==-1 && this->nthWindow->b.indexOf("x")==-1){
          res=exEu(inum,inum1,1);
          ans=(res.first*inum)+(res.second*inum1);
          text1 = text1.number(ans);
          text1.append("=");
          str = text1.number(res.first);
          text1.append(str);
          text1.append("*");
          str = str.number(inum);
          text1.append(str);
          text1.append("+");
          str = str.number(res.second);
          text1.append(str);
          text1.append("*");
          str = str.number(inum1);
          text1.append(str);
        }
        else{
        if (charac != 0){
          rrespol = exEu(rpol,rpol1,charac);
          ranspol =(rrespol.first*rpol)+(rrespol.second*rpol1);
          ranspol=ranspol.normalize();
          strResult=ranspol.print();
          strResult.append("=(");
          rrespol.first=rrespol.first.normalize();
          text1 = rrespol.first.print();
          strResult.append(text1);
          strResult.append(")*(");
          rpol.normalize();
          text1 = rpol.print();
          strResult.append(text1);
          strResult.append(") + (");
          rrespol.second=rrespol.second.normalize();
          text1 = rrespol.second.print();
          strResult.append(text1);
          strResult.append(")*(");
          rpol1=rpol1.normalize();
          text1 = rpol1.print();
          strResult.append(text1);
          strResult.append(")");
          text1 = strResult;
      }
      else{
          arespol = exEu(apol,apol1,1);
          aanspol =(arespol.first*apol)+(arespol.second*apol1);
          aanspol=aanspol.normalize();
          strResult=aanspol.print();
          strResult.append("=(");
          arespol.first=arespol.first.normalize();
          text1 = arespol.first.print();
          strResult.append(text1);
          strResult.append(")*(");
          apol=apol.normalize();
          text1 = apol.print();
          strResult.append(text1);
          strResult.append(") + (");
          arespol.second=arespol.second.normalize();
          text1 = arespol.second.print();
          strResult.append(text1);
          strResult.append(")*(");
          apol1=apol1.normalize();
          text1 = apol1.print();
          strResult.append(text1);
          strResult.append(")");
          text1 = strResult;
      }
      }
        memory = memory.append(text1);
        text1 = "";
        standardWrite();
    }
    delete this->nthWindow;
}
void MainWindow::mPrimeDec()          //prime factor decomposition
{
    showNThDialog("factors_of");
    if (this->nthWindow->ok){
        if (this->nthWindow->a.indexOf("x")==-1 && this->nthWindow->b.indexOf("x")==-1){
          ints = primeFac(inum);
          text1 = intsToString(ints);
        }
        else{
          if (charac == 0){
             text1 = pol.factors();
             if (text1.indexOf("no")>-1){text1 = "sorry, i have not found the roots";}
          }
          else {
              text1 = "(In this release the method is not yet implemented for polynomials in positive characteristics.)";
          }
        }
        memory = memory.append(text1);
        text1 = "";
        standardWrite();
    }
    delete this->nthWindow;
}

void MainWindow::mPrime()          //smallest prime number
{
    showNThDialog("prime");
    if (this->nthWindow->ok){
      ians = prime(inum);
      text1 = text1.number(ians);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}

void MainWindow::mphi()          //Euler phi function
{
    showNThDialog("phi");
    if (this->nthWindow->ok){
      ians = phi(inum);
      text1 = text1.number(ians);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}


void MainWindow::mfibo()          //Fibonacci number
{
    showNThDialog("Fibonacci");
    if (this->nthWindow->ok){
        if(inum >50000 || this->nthWindow->a.length()>5){
            text1 = "This function is restricted to numbers less or equal 20000.<br>";
            memory = memory.append(text1);
            memory = memory.append("The result and the time needed for the computation increase rapidly.");}
        else{
           ubinum = fibo(inum);
           text1 = ubinum.print();
           memory = memory.append(text1);
       }
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}
void MainWindow::mfacnum()          //number of factors
{
    showNThDialog("factor_number");
    if (this->nthWindow->ok){
      ians = facnum(inum);
      text1 = text1.number(ians);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}
void MainWindow::mlambda()          //Liouville function
{
    showNThDialog("lambda");
    if (this->nthWindow->ok){
      ians = lambda(inum);
      text1 = text1.number(ians);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}
void MainWindow::mpsi()          //Dedekind psi function
{
    showNThDialog("psi");
    if (this->nthWindow->ok){
      ians = psi(inum);
      text1 = text1.number(ians);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}
void MainWindow::mpi()          //pi function
{
    showNThDialog("pi");
    if (this->nthWindow->ok){
      ians = pi(inum);
      text1 = text1.number(ians);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}
void MainWindow::mfacsum()          //pi function
{
    showNThDialog("factor_sum");
    if (this->nthWindow->ok){
      ians = facsum(inum);
      text1 = text1.number(ians);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}
void MainWindow::mfac()          //pi function
{
    showNThDialog("!");
    if (this->nthWindow->ok){
        if(inum >=10000 || this->nthWindow->a.length()>5){
            text1 = "This function is restricted to numbers less than 10000.<br>";
            memory = memory.append(text1);
            memory = memory.append("The result and the time needed for the computation increase rapidly.");}
        else{
           ubians = fac(inum);
           text1 = ubians.print();
           memory = memory.append(text1);
        }
        text1 = "";
        standardWrite();
    }
    delete this->nthWindow;
}

////////////////////////Functions/////////////////////////

void MainWindow::msin(){
    showNThDialog("sin");
    if (this->nthWindow->ok){
      dans = sin(dans);
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}
void MainWindow::marcsin(){
    showNThDialog("arcsin");
    if (this->nthWindow->ok){

       if (dans > 1){
           int k= dans;
           if (k%2==1){k += 1;}
           dans = dans-k;
       }
       else if (dans <-1){
             int k = -dans;
             if (k%2==1){k += 1;}
             dans = dans+k;
       }

       double a = -PI/2, b = PI/2, c;

       for (int i= 1;i <= 50; i++){
            c = (a+b)/2;
            if (sin(c) < dans){a= c;}
            else{b = c;}
       }

      dans = c;
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}

void MainWindow::mcos(){
    showNThDialog("cos");
    if (this->nthWindow->ok){
      dans = cos(dans);
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}
void MainWindow::marccos(){
    showNThDialog("arccos");
    if (this->nthWindow->ok){

       if (dans > 1){
          int k= dans;
          if (k%2==1){k += 1;}
          dans = dans-k;
       }
       else if (dans <-1){
            int k = -dans;
            if (k%2==1){k += 1;}
            dans = dans+k;
       }

       double a = 0, b = PI, c;

       for (int i= 1;i <= 50; i++){
            c = (a+b)/2;
            if (cos(c) < dans){b= c;}
            else{a = c;}
       }

      dans = c;
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}

void MainWindow::mtan(){
    showNThDialog("tan");
    if (this->nthWindow->ok){
      dans = tan(dans);
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}
void MainWindow::marctan(){
    showNThDialog("arctan");
    if (this->nthWindow->ok){
       double a = -PI/2, b = PI/2, c;

       for (int i= 1;i <= 50; i++){
            c = (a+b)/2;
            if (tan(c) < dans){a= c;}
            else{b = c;}
       }

      dans = c;
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}

void MainWindow::mcot(){
    showNThDialog("cot");
    if (this->nthWindow->ok){
      dans = tan(dans);
      dans = 1/dans;
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}
void MainWindow::marccot(){
    showNThDialog("arccot");
    if (this->nthWindow->ok){
       double a = 0, b = PI, c;

       for (int i= 1;i <= 50; i++){
            c = (a+b)/2;
            if ((1/tan(c)) < dans){b= c;}
            else{a = c;}
       }

      dans = c;
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}
void MainWindow::mexp(){
    showNThDialog("exp");
    if (this->nthWindow->ok){
      dans = exp(dans);
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}

void MainWindow::mlog(){
    showNThDialog("ln");
    if (this->nthWindow->ok){
      dans = log(dans);
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}

void MainWindow::minv(){
    showNThDialog("1/");
    if (this->nthWindow->ok){
      dans = 1/dans;
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}

void MainWindow::mPower(){
    showNThDialog("^");
    if (this->nthWindow->ok){
      dans = exp(dans1*log(dans));
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}

void MainWindow::mlogA(){
    showNThDialog("log_");
    if (this->nthWindow->ok){
      dans = log(dans1)/log(dans);
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}

void MainWindow::msqrt(){
    showNThDialog("sqrt");
    if (this->nthWindow->ok){
      dans = exp(log(dans)/2);
      text1 = text1.number(dans);
      memory = memory.append(text1);
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}

void MainWindow::mbino(){
    showNThDialog("choose");
    if (this->nthWindow->ok){
        if(inum >=10000 || this->nthWindow->a.length()>5){
            text1 = "This function is restricted to numbers less than 10000.<br>";
            memory = memory.append(text1);
            memory = memory.append("The result and the time needed for the computation increase rapidly.");}
        else{
            ubians = bino(inum,inum1);
            text1 = ubians.print();
            memory = memory.append(text1);
        }
      text1 = "";
      standardWrite();
    }
    delete this->nthWindow;
}

//////////////////////////////////////////////////////////


void MainWindow::setChar(){
    chDia = new charDialog;
    QObject::connect(this->chDia->but,SIGNAL(clicked()),this,SLOT(setChar2()));
    chDia->exec();
    delete chDia;
}

void MainWindow::setChar2(){
    charac = this->chDia->charBox->cleanText().toInt();
    this->chDia->close();
    memory = str;
    text1 = "";

    if(memory != "" && str1 == "") {memory = memory.append("<br>");}
    memory = memory.append("The characteristic has changed to ");
    memory = memory.append(this->chDia->charBox->cleanText());

    str1 = "";

    if (charac > 0){
      ui->ibut->setEnabled(0);
      ui->dot->setEnabled(0);
    }
    else{
        ui->ibut->setEnabled(1);
        ui->dot->setEnabled(1);
    }

    if (charac > 0 && charac != prime(charac)){
       ui->but4->setEnabled(0);

       ui->SLEBut->setEnabled(0);
       ui->gaussBut->setEnabled(0);
       ui->invBut->setEnabled(0);

       ui->rankBut->setEnabled(0);
       ui->detBut->setEnabled(0);
       ui->charPolyBut->setEnabled(0);
       ui->miniPolyBut->setEnabled(0);
       ui->bgcd->setEnabled(0);
       ui->blcm->setEnabled(0);
       ui->bExEu->setEnabled(0);
       ui->pFacBut->setEnabled(0);
       ui->but5->setEnabled(0);

       memory = memory.append("<br>WARNING: ");
       memory = memory.append(this->chDia->charBox->cleanText());
       memory = memory.append(" is not a prime number. Several functions are disabled.");
    }
    else{
        ui->but4->setEnabled(1);
        ui->SLEBut->setEnabled(1);
        ui->gaussBut->setEnabled(1);
        ui->invBut->setEnabled(1);
        ui->rankBut->setEnabled(1);
        ui->detBut->setEnabled(1);
        ui->charPolyBut->setEnabled(1);
        ui->miniPolyBut->setEnabled(1);

        ui->bgcd->setEnabled(1);
        ui->blcm->setEnabled(1);
        ui->bExEu->setEnabled(1);
        ui->pFacBut->setEnabled(1);
        ui->but5->setEnabled(1);
    }
    ui->line->setHtml(memory);
    sb->setValue(sb->maximum());
}

///Linear Algebra///////////////////////////////////////////////////////////

void MainWindow::err(QString errMsg){
    if(memory != "" && text1 != ""){memory = memory.append("<br>");}
    if(text1 != "") {
        memory = memory.append(text1);
        memory = memory.append("<br>");
    }
    text1 = "";
    str1 = "";
    memory = memory.append("Error: ");
    memory = memory.append(errMsg);
    standardWrite();
}

void MainWindow::linASwitch(){
    showDialog("Enter a matrix:");
    if (ui->msg->matInfo.indexOf("No") ==-1){
        if (charac > 0){
           rtmat = strToRestMatrix(ui->msg->matInfo,charac);
        }
        else{
            if (alg){amat = strToAlgMatrix(ui->msg->matInfo);}
            else {mat = strToMatrix(ui->msg->matInfo);}
        }
      linAlg = true;
    }
}

void MainWindow::correctMemory(){
    if(memory != "" && text1 != ""){memory = memory.append("<br>");}
    if(text1 != "") {
        memory = memory.append(text1);
        text1 = "";
    }
    if (memory.right(4)=="<br>"){memory = memory.left(memory.size()-4);}
    str1 = "";
}

void MainWindow::linAWrite(){

    if(memory != "" && text1 != ""){memory = memory.append("<br>");}
    if(text1 != "") {
        memory = memory.append(text1);
        text1 = "";
    }
    if (memory.right(4)=="<br>"){memory = memory.left(memory.size()-4);}
    str = memory;

    if (!alg){
      str1="<table><tr><th>";
      if (charac > 0){
          str1 = str1.append(restMatrixToHtml(rtmat));
      }
      else{
          str1 = str1.append(matrixToHtml(mat));
      }
      str1= str1.append("</th></tr></table>");

      str = str.append(str1);
      linAlg = true;
    }
    else{
        linAlg = false;
    }
    ui->line->setHtml(str);
    sb->setValue(sb->maximum());
}

void MainWindow::showDialog(QString text){

  delete ui->msg;
  ui->msg = new myDialog(lines, columns, text);
  QObject::connect(ui->msg->but,SIGNAL(clicked()),ui->msg,SLOT(accept()));
  QObject::connect(ui->msg->but2,SIGNAL(clicked()),ui->msg,SLOT(close()));
  ui->msg->give();
}

void MainWindow::setLine(int v)
{
    if (v != lines){
      lines = v;
    }
}
void MainWindow::setColumn(int v)
{
    if (v != columns){
      columns = v;
    }
}
void MainWindow::mWriteMatrix(){

    if (linAlg){memory = memory.append(str1);}

showDialog("Enter a matrix:");

if (ui->msg->matInfo.indexOf("No") ==-1){
    if (charac > 0){
       rtmat = strToRestMatrix(ui->msg->matInfo,charac);
    }
    else{
        mat = strToMatrix(ui->msg->matInfo);
    }
  linAWrite();
  linAlg = true;
}

}

void MainWindow::mSLESolve(){

    alg = true;
    showDialog("For the system Ax = b of linear equations enter the matrix A:");
    
    if (ui->msg->matInfo.indexOf("No") ==-1){
    
    if (charac > 0){
        rtmat1 = strToRestMatrix(ui->msg->matInfo,charac);
    }
    else{
        amat1 = strToAlgMatrix(ui->msg->matInfo);
    }

    delete ui->msg;
    ui->msg = new myDialog(lines, 1, "Enter the vector b:");
    QObject::connect(ui->msg->but,SIGNAL(clicked()),ui->msg,SLOT(accept()));
    QObject::connect(ui->msg->but2,SIGNAL(clicked()),ui->msg,SLOT(close()));
    ui->msg->give();

    if (ui->msg->matInfo.indexOf("No") ==-1){
    if (linAlg){memory = memory.append(str1);linAlg = false;}
    correctMemory();
    if (charac > 0){
        rtmat = rtmat1;
        rtmat1 = strToRestMatrix(ui->msg->matInfo,charac);
        rrtmat = rtmat.solve(rtmat1);
        memory = memory.append(writeRestGauss(rtmat,rtmat1, rrtmat,charac));
        memory = memory.append("interpretation: the set of solutions is given by");
        memory = memory.append(rrtmat.interpretation());
    }
    else{
        amat = amat1;
        amat1 = strToAlgMatrix(ui->msg->matInfo);
        armat = amat.solve(amat1);
        memory = memory.append(writeAlgGauss(amat,amat1, armat));
        memory = memory.append("interpretation: the set of solutions is given by");
        memory = memory.append(armat.interpretation());
    }

    linAWrite();
    
    }
    }
    alg = false;
}

void MainWindow::mtranspose(){

    linASwitch();

    if (ui->msg->matInfo.indexOf("No") ==-1){
        if (linAlg){memory = memory.append(str1);linAlg = false;}
        correctMemory();
        if (charac > 0){
            rtmat1 = rtmat.transpose();
            memory = memory.append(writeRestMatOp(rtmat,"transposed:", rtmat1));
            rtmat = rtmat1;
        }
        else{
            mat1 = mat.transpose();
            memory = memory.append(writeMatOp(mat,"transposed:", mat1));
            mat = mat1;
        }
        alg = true;
        linAWrite();
        alg = false;
    }

}

void MainWindow::mgauss(){
    alg = true;
    linASwitch();
    if (ui->msg->matInfo.indexOf("No") ==-1){
        if (linAlg){memory = memory.append(str1);linAlg = false;}

        correctMemory();
        if (charac > 0){
            rtmat1 = rtmat;
            rtmat = rtmat.gauss();
            memory = memory.append(writeRestMatOp(rtmat1,"after Gauss algorithm:", rtmat));
        }
        else{
            amat1 = amat;
            amat = amat.gauss();
            memory = memory.append(writeAlgMatOp(amat1,"after Gauss algorithm:", amat));
        }

      linAWrite();
    }

    alg = false;
}

void MainWindow::mmatInv(){
if(lines == columns){
    alg = true;
    linASwitch();
    if (ui->msg->matInfo.indexOf("No") ==-1){
        if (linAlg){memory = memory.append(str1);linAlg = false;}

        correctMemory();
        if (charac > 0){
            rest tester(0,charac);
            rtmat1 = rtmat.invert();
            if (rtmat1.lines != 1 || *rtmat.element(1,1) != tester){
                memory = memory.append(writeRestMatOp(rtmat,"inverted:", rtmat1));
                linAWrite();
            }
            else{
                err("the matrix does not have maximal rank");
            }
        }
        else{
            algCplx tester(0,0);
            amat1 = amat.invert();
            if (amat1.lines != 1 || *amat.element(1,1) != tester){
                memory = memory.append(writeAlgMatOp(amat,"inverted:", amat1));
                linAWrite();
            }
            else{
                err("the matrix does not have maximal rank");
            }
        }

    }

    alg = false;
}
    else{
        err("the inverse matrix is only for quadratic matrices defined");
    }
}

void MainWindow::mrank(){
    alg = true;
    linASwitch();
    if (ui->msg->matInfo.indexOf("No") ==-1){
        if (linAlg){memory = memory.append(str1);linAlg = false;}

        correctMemory();
        if (charac > 0){
            inum = rtmat.rank();
            str = str.number(inum);
            memory = memory.append(writeRestMatSingOp(rtmat," has rank ", str));
        }
        else{

           inum = amat.rank();
           str = str.number(inum);
           memory = memory.append(writeAlgMatSingOp(amat," has rank ", str));
       }

       linAWrite();
    }
    alg = false;
}

void MainWindow::mdet(){
    if(lines == columns){

    linASwitch();
    if (ui->msg->matInfo.indexOf("No") ==-1){
        if (linAlg){memory = memory.append(str1);linAlg = false;}
        correctMemory();
        if (charac > 0){
            rans = rtmat.det();
            memory = memory.append(writeRestMatSingOp(rtmat," has determinant ", rans.print()));
        }
        else{
            cnum = mat.det();
            memory = memory.append(writeMatSingOp(mat," has determinant ", cnum.print()));
        }
        alg = true;
        linAWrite();
        alg = false;
    }
}
    else{
        err("the determinant is only for quadratic matrices defined");
    }
}

void MainWindow::mcharPoly(){
    if(lines == columns){

    linASwitch();
    if (ui->msg->matInfo.indexOf("No") ==-1){
        if (linAlg){memory = memory.append(str1);linAlg = false;}
        correctMemory();
        if (charac > 0){
            rpol = rtmat.charPoly();
            memory = memory.append(writeRestMatSingOp(rtmat," has characteristic polynomial ", rpol.print()));
        }
        else{
            pol = mat.charPoly();
            memory = memory.append(writeMatSingOp(mat," has characteristic polynomial ", pol.print()));
        }

        alg = true;
        linAWrite();
        alg = false;
    }
}
    else{
        err("the characteristic polynomial is only for quadratic matrices defined");
    }
}

void MainWindow::mminiPoly(){

    if(lines == columns){
    alg = true;
    linASwitch();
    if (ui->msg->matInfo.indexOf("No") ==-1){

        if (linAlg){memory = memory.append(str1);linAlg = false;}
        correctMemory();

        if (charac > 0){
            rpol = rtmat.miniPoly();
            memory = memory.append(writeRestMatSingOp(rtmat," has minimal polynomial ", rpol.print()));

        }
        else{
            apol = amat.miniPoly();
            memory = memory.append(writeAlgMatSingOp(amat," has minimal polynomial ", apol.print()));
        }
      linAWrite();
    }
    alg = false;
}
    else{
        err("the minimal polynomial is only for quadratic matrices defined");
    }
}

void MainWindow::mmatMult(){
    if (linAlg){
      if ((charac > 0 && rtmat.columns == lines) || (charac == 0 && mat.columns == lines)){
      showDialog("Enter a matrix:");
      if (ui->msg->matInfo.indexOf("No") ==-1){
          if (charac > 0){
                rtmat1 = strToRestMatrix(ui->msg->matInfo, charac);
                memory = memory.append(writeRestMatOp(rtmat,"*", rtmat1));
                rtmat = rtmat*rtmat1;
                linAWrite();
          }
          else{
                mat1 = strToMatrix(ui->msg->matInfo);
                memory = memory.append(writeMatOp(mat,"*", mat1));
                mat = mat*mat1;
                linAWrite();
          }
      }
      }
      else{
        err("the number of columns of the first factor must coincide with the number of lines of the second factor");
      }
    }
    else{
      err("enter a matrix");
    }
}

void MainWindow::mmatAdd(){
    if (linAlg){
      if ((charac > 0 && rtmat.lines ==lines && rtmat.columns == columns) || (charac == 0 &&mat.lines ==lines && mat.columns == columns)){
      showDialog("Enter a matrix:");
      if (ui->msg->matInfo.indexOf("No") ==-1){
          if (charac > 0){
                rtmat1 = strToRestMatrix(ui->msg->matInfo, charac);
                memory = memory.append(writeRestMatOp(rtmat,"+", rtmat1));
                rtmat = rtmat+rtmat1;
                linAWrite();
          }
          else{
                mat1 =strToMatrix(ui->msg->matInfo);
                memory = memory.append(writeMatOp(mat,"+", mat1));
                mat = mat+mat1;
                linAWrite();
          }
      }
    }
    else{
      err("the matrices must have the numbers of lines and columns");
    }
    }
    else{
        err("enter a matrix");
    }
}

void MainWindow::mmatSub(){
    if (linAlg){
      if ((charac > 0 && rtmat.lines ==lines && rtmat.columns == columns) || (charac == 0 &&mat.lines ==lines && mat.columns == columns)){
      showDialog("Enter a matrix:");
      if (ui->msg->matInfo.indexOf("No") ==-1){
          if (charac > 0){
              rtmat1 = strToRestMatrix(ui->msg->matInfo, charac);
              memory = memory.append(writeRestMatOp(rtmat,"-", rtmat1));
              rtmat = rtmat-rtmat1;
              linAWrite();
          }
          else{
              mat1 =strToMatrix(ui->msg->matInfo);
              memory = memory.append(writeMatOp(mat,"-", mat1));
              mat = mat-mat1;
              linAWrite();
          }
      }
      }
      else{
          err("the matrices must have the numbers of lines and columns");
      }
    }
    else{
        err("enter a matrix");
    }
}

////////////////////////////////////////////////////////////////////////////



void MainWindow::em()
{
    if (memory != "") {memory = memory.append("<br>");}
    memory = memory.append(text1);
    if (text1.indexOf("x")>-1){
        if (charac > 0 ){
            realParsNComp(text1, &ranspol,charac);
            ranspol=ranspol.normalize();
            text1 = ranspol.print();
        }
        else{
            realParsNComp(text1, &anspol,charac);
            anspol=anspol.normalize();
            text1 = anspol.print();
        }
    }
    else{
        if (charac > 0 ){
            realParsNComp(text1, &rans,charac);
            text1 = rans.print();
        }
        else if(text1.indexOf("i")>-1){
            realParsNComp(text1, &cans,10);
            text1 = cans.print();
        }
        else{
            realParsNComp(text1, &dans,charac);
            text1=text1.number(dans);
        }
    }

    standardWrite();
}
