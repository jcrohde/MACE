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

#include "gui/fctndialog.h"


FctnDialog::FctnDialog(stringFactory *fac, QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Mace");
    setWindowIcon(QIcon("icons/MaceLogo.png"));

    vbox = new QVBoxLayout;
    funcVars = new QVBoxLayout;
    hbox = new QHBoxLayout;
    grid = new QGridLayout;
    radioGrid = new QGridLayout;

    radioBox = new QVBoxLayout;
    mlay = new QHBoxLayout;

    pBox = new QSpinBox;
    pBox2 = new QSpinBox;

    pdf = new QRadioButton("pdf (probability density function)");
    cdf = new QRadioButton("cdf (cumulative distribution function)");
    hazard = new QRadioButton("haz (hazard function)");
    quantile = new QRadioButton("qua (quantile)");
    pdf->setChecked(true);

    kurt = new QRadioButton("kurtosis");
    kurtex = new QRadioButton("kurtosis excess");
    mean = new QRadioButton("mean");
    median = new QRadioButton("median");
    mode = new QRadioButton("mode");
    skewness = new QRadioButton("skewness");
    standdev = new QRadioButton("standard deviation");
    variance = new QRadioButton("variance");
    mean->setChecked(true);

    tab = new QTabWidget;

    statFunc = new QGroupBox("");
    statVars = new QGroupBox("");

    help = new QPushButton("Help");
    but = new QPushButton("Ok");
    but2 = new QPushButton("No");

    line1 = new MaceLineEdit;
    line2 = new MaceLineEdit;
    line3 = new MaceLineEdit;
    line4 = new MaceLineEdit;

    label1 = new QLabel;
    label2 = new QLabel;
    label3 = new QLabel;
    label4 = new QLabel;

    pLabel = new QLabel;
    pLabel2 = new QLabel;

    grid->addWidget(label1,0,0,1,1);
    grid->addWidget(line1,0,1,1,1);
    grid->addWidget(label2,1,0,1,1);
    grid->addWidget(line2,1,1,1,1);
    grid->addWidget(label3,2,0,1,1);
    grid->addWidget(line3,2,1,1,1);
    grid->addWidget(label4,3,0,1,1);
    grid->addWidget(line4,3,1,1,1);
    grid->addWidget(pLabel,4,0,1,1);
    grid->addWidget(pBox,4,1,1,1);
    grid->addWidget(pLabel2,5,0,1,1);
    grid->addWidget(pBox2,5,1,1,1);

    info = new QTextEdit;
    vertic = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    factory = fac;

    label = new QLabel(labelStr);

    vbox->addWidget(label);

    vbox->addLayout(grid);

    info->setMaximumSize(237,120);
    info->setReadOnly(true);
    info->setHidden(true);

    vbox->addWidget(info);
    vbox->addItem(vertic);

    hbox->addWidget(but);
    hbox->addWidget(but2);
    hbox->addWidget(help);
    vbox->addLayout(hbox);

    radioBox->addWidget(pdf);
    radioBox->addWidget(cdf);
    radioBox->addWidget(hazard);
    radioBox->addWidget(quantile);
    statFunc->setLayout(radioBox);

    radioGrid->addWidget(mean,0,0,1,1);
    radioGrid->addWidget(skewness,0,1,1,1);
    radioGrid->addWidget(median,1,0,1,1);
    radioGrid->addWidget(standdev,1,1,1,1);
    radioGrid->addWidget(mode,2,0,1,1);
    radioGrid->addWidget(variance,2,1,1,1);
    radioGrid->addWidget(kurt,3,0,1,1);
    radioGrid->addWidget(kurtex,3,1,1,1);
    statVars->setLayout(radioGrid);

    mlay->addLayout(vbox);

    statFunc->setFlat(true);
    statVars->setFlat(true);

    tab->addTab(statFunc,"Functions");
    tab->addTab(statVars,"Properties");

    mlay->addWidget(tab);
    setLayout(mlay);

    quantile->setHidden(true);
    kurt->setHidden(true);
    kurtex->setHidden(true);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QWidget::connect(but2,SIGNAL(clicked()),this,SLOT(close()));
    QWidget::connect(but,SIGNAL(clicked()),this,SLOT(agree()));
    QWidget::connect(help,SIGNAL(clicked()),this,SLOT(show_info()));
    QWidget::connect(tab,SIGNAL(currentChanged(int)),this,SLOT(statSwitch(int)));

    QObject::connect(line2,SIGNAL(entered()),this,SLOT(agree()));
    QObject::connect(line1,SIGNAL(entered()),this,SLOT(nextLine()));
}

FctnDialog::~FctnDialog()
{

}

void FctnDialog::agree(){
        ok = true;
        a = line1->text();
        b = line2->text();
        c = line3->text();
        d = line4->text();
        this->close();
        emit inserted();
}

void FctnDialog::show_info(){
    if(info->isHidden())
        info->setHidden(false);
    else{
        info->setHidden(true);
        layout()->setSizeConstraint(QLayout::SetFixedSize);
    }
}

void FctnDialog::statSwitch(int i){
    int j = factory->getVariables(op);
    labelFormat(i!=1);
    if(j == 2){
        label2->setHidden(i == 1);
        line2->setHidden(i == 1);
    }
    else if (j==3){
        label3->setHidden(i == 1);
        line3->setHidden(i == 1);
    }
    else{
        label4->setHidden(i == 1);
        line4->setHidden(i == 1);
    }
}

void FctnDialog::change_linesColumns(QListWidgetItem *i){
    QString key, text;
    QVariant func_type;
    func_type = i->data(100);
    key = func_type.toString();
    fctnCode = factory->getCode(key);

    tab->setHidden(true);

    op = key;
    text = i->text();

    setWindowTitle("linear Algebra");

    linesFormat(1,0,0);
    label1->setHidden(true);
    line1->setHidden(true);
    pLabel->setVisible(true);
    pBox->setVisible(true);
    pLabel2->setHidden(text == "columns" || text == "rows / columns");
    pBox2->setHidden(text == "columns" || text == "rows / columns");
    pBox->setRange(1,20); pBox->setValue(2);
    pBox2->setRange(1,20); pBox2->setValue(2);

    pBox->setValue(2);
    if (text == "columns" || text == "rows / columns") pBox2->setValue(2);

    labelStr = "Choose number of ";
    labelStr = labelStr.append(text);
    labelStr = labelStr.append(":");
    label->setText(labelStr);

    if(text == "variables and equations"){
        pLabel->setText("equations:");
        pLabel2->setText("variables:");
    }
    else if(text == "rows / columns"){
        pLabel->setText("rows / columns:");
    }
    else if(text == "columns"){
        pLabel->setText("columns:");
    }
    else{
        pLabel->setText("rows:");
        pLabel2->setText("columns:");
    }

    info->setHtml(factory->help_info(key,factory->getCode(key)));

    info->setHidden(true);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    but->setFocus();
    emit hello();
    this->show();
}

void FctnDialog::make_settings(QString str){
    op = str;

    tab->setHidden(true);

    label1->setVisible(op == "Characteristics");
    line1->setVisible(op == "Characteristics");
    pLabel->setHidden(op == "Characteristics");
    pBox->setHidden(op == "Characteristics");
    pLabel2->setVisible(op == "Rows and Columns of Matrices");
    pBox2->setVisible(op == "Rows and Columns of Matrices");

    setWindowTitle("Settings");
    labelStr = "Choose ";
    labelStr = labelStr.append(str);
    labelStr = labelStr.append(":");
    label->setText(labelStr);

    if (op == "Characteristics"){
        label1->setText("Characteristic = ");
        linesFormat(1,0,0);
        fctnCode = 10;
        line1->setContextMenuPolicy(Qt::NoContextMenu);
        line1->clear();
        line1->all = false;
    }
    else if (op == "Precision"){

        pLabel->setText("Precision:");
        pBox->setRange(2,16);
        pBox->setValue(6);
        linesFormat(1,0,0);
        fctnCode = 40;
    }
    else{
        linesFormat(1,0,0);
        pLabel->setText("rows:");
        pLabel2->setText("columns:");
        fctnCode = 20;
        pBox->setRange(1,20);
        pBox2->setRange(1,20);
        pBox->setValue(2);
        pBox2->setValue(2);
    }

    if(op.contains("Plot")){
        info->setHtml(factory->get_plotInfo(str));
    }
    else{
        info->setHtml(factory->get_settingInfo(str));
    }

    info->setHidden(true);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    but->setFocus();
    emit hello();
    this->show();
}

void FctnDialog::labelFormat(bool fctns){

    if(factory->getCode(op) == 131){
        labelStr = "Select a ";
        if (fctns) labelStr = labelStr.append("function ");
        else labelStr = labelStr.append("property ");
        labelStr = labelStr.append("and compute its value ");
        if (fctns) labelStr=labelStr.append("at x ");
        labelStr= labelStr.append("with<br> respect to the<center>");
        labelStr = labelStr.append(factory->get_info(op));
        labelStr = labelStr.append(" ");
        labelStr = labelStr.append(factory->getHtml(op));
        labelStr = labelStr.append("(");
        int vars = factory->getVariables(op);
        if(vars == 2){
            labelStr = labelStr.append("a");
        }
        else if(vars == 3){
            if (op == "binomial distribution" || op == "negative distribution"){
                labelStr = labelStr.append("n,p");
            }
            else if (op == "normal distribution" || op == "laplace distribution"){
                QString help = QString((QChar)0x03BC);
                help = help.append(",");
                help = help.append(QString((QChar)0x03C3));
                labelStr = labelStr.append(help);
            }
            else if (op == "cauchy distribution"){
                labelStr = labelStr.append("x<sub>0</sub>,");
                labelStr = labelStr.append((QChar)0x03B3);
            }
            else if (op == "extreme distribution" || op =="log distribution" || op =="logistic distribution"){
                labelStr = labelStr.append("loc,scale");
            }
            else if (op == "gamma distribution"){
                labelStr = labelStr.append("k,");
                labelStr = labelStr.append(QString((QChar)0x03B8));
            }
            else{
                labelStr = labelStr.append("a,b");
            }
        }
        else{
            if (op == "hypergeometric distribution"){
                labelStr = labelStr.append("k,n,N");
            }
            else labelStr = labelStr.append("a,b,c");
        }
        labelStr = labelStr.append(")</center> for");

        mean->setDisabled(op == "cauchy distribution");
        kurt->setDisabled(op == "cauchy distribution");
        kurtex->setDisabled(op == "cauchy distribution");
        standdev->setDisabled(op == "cauchy distribution" || op == "f distribution");
        skewness->setDisabled(op == "cauchy distribution");
        variance->setDisabled(op == "cauchy distribution");

        mean->setChecked(op == "f distribution");
        median->setChecked(op == "cauchy distribution");

    }
    else{
        QString opMod;
        if(op == "greatest common divisor"){opMod = "gcd(a,b)";}
        else if(op == "least common multiple"){opMod = "lcm(a,b)";}
        else if(op == "% (modulo)"){opMod = "a % b";}
        else if(op == "lambda (Liouville function)"){opMod =QString((QChar)0x03BB); opMod= opMod.append("(a)");}
        else if(op == "pi (prime counting function)"){opMod =QString((QChar)0x03C0); opMod= opMod.append("(a)");}
        else if(op == "phi (Euler totient function)"){opMod =QString((QChar)0x03C6); opMod= opMod.append("(a)");}
        else if(op == "gamma"){opMod =QString((QChar)0x0393); opMod= opMod.append("(a)");}
        else if(op == "zeta"){opMod =QString((QChar)0x03B6); opMod= opMod.append("(a)");}
        else if(op == "beta"){opMod = "B"; opMod= opMod.append("(a,b)");}
        else if(op == "psi (Dedekind function)"){opMod =QString((QChar)0x03C8); opMod= opMod.append("(a)");}
        else if(op == "a^2"){opMod =QString((QChar)0x00B2); opMod= opMod.prepend("a");}
        else if(op == "a^n"){opMod = "a^b";}
        else if(op == "a^b"){opMod = "a^b";}
        else if(op == "fibonacci number"){opMod = "the Fibonacci number f<sub>a</sub>";}
        else if(op == "root"){opMod =QString((QChar)0x221A); opMod= opMod.append("a");}
        else if(op == "k"){opMod = "K(k)";}
        else if(op == "laguerre"){opMod = "the Laguerre polynomial of degree <i>n</i> at <i>x</i>";}
        else if(op == "legendre"){opMod = "the Legendre polynomial of degree <i>n</i> at <i>x</i>";}
        else if(op == "hermit"){opMod = "the Hermite polynomial of degree <i>n</i> at <i>x</i>";}
        else if(op == "e2"){opMod = QString((QChar)0x03C6);opMod = opMod.prepend("E2(");opMod = opMod.append(",k)");}
        else if(op == "e1"){opMod = "E(k)";}
        else if(op == "exponential integral") {opMod = "En";}
        else if(op == "exponential integral i") {opMod = "Ei";}
        else if(op == "f"){opMod = QString((QChar)0x03C6);opMod = opMod.prepend("F(");opMod = opMod.append(",k)");;}
        else if(op == "j"){opMod = "J<sub>v</sub>(x)";}
        else if(op == "y"){opMod = "Y<sub>v</sub>(x)";}
        else if(op == "lucas number"){opMod = "Lucas number";}
        else if(op == "pi3"){opMod =opMod = QString((QChar)0x03C6);opMod = opMod.prepend("PI(n,");opMod = opMod.append(",k)");;}
        else if (op == "primality test") opMod = "Primality Test (2=Yes, 1=Seems So, 0=No)";
        else if (op == "facris") opMod = "the rising factorial";
        else if (op == "facfal") opMod = "the falling factorial";
        else {opMod = op;}

        labelStr = "";
        if (fctnCode == 200) {
            labelStr = "Input for a script";
        }
        else if (factory->getCode(op) == 152 || factory->getCode(op) == 153) {
            labelStr = "a ";
            if      (opMod == "xor") labelStr = labelStr.append("XOR");
            else if (opMod ==  "or") labelStr = labelStr.append("OR");
            else if (opMod == "and") labelStr = labelStr.append("AND");
            else if (opMod == "not") labelStr = labelStr.prepend("NOT ");
            else                     labelStr = labelStr.append(opMod);
        }
        else if (op == "assignment") labelStr = "Assignment operator";
        else if ( factory->getCode(op) != 151)  {
            if (factory->getCode(op) !=155 && factory->getCode(op) != 148) labelStr = "Compute ";
            labelStr = labelStr.append(opMod);
        }
        if (factory->getCode(op) == 152  || factory->getCode(op) == 153)
            if (op != "not") labelStr = labelStr.append(" b");

        if (opMod == "abs" || opMod == "cos" || opMod == "arccos" || opMod == "cot" ||opMod == "arccot" ||
          opMod == "conj" || opMod == "sin" || opMod == "arcsin" || opMod == "arcoth" || opMod == "coth" ||
          opMod == "tan" || opMod == "tanh" || opMod == "artanh" || opMod == "arctan" || opMod == "exp" || opMod == "ln"
          ||opMod == "arcosh" || opMod == "arsinh" || opMod == "polar" || opMod == "cosh" || opMod == "sinh"){
            labelStr = labelStr.append("(a)");
        }
        else if(opMod == "factor sum" || opMod == "Fibonacci number"){
            labelStr = labelStr.append(" of a");
        }
        else if (opMod == "multiset"){
            labelStr = labelStr.append(" of size b from a elements");
        }

        if (fctnCode != 151 && fctnCode != 200) labelStr = labelStr.append(" for");
    }
    label->setText(labelStr);
}

void FctnDialog::linesFormat(int i, int code, int index){
    label2->setVisible(i>2 ||(i==2 && (code !=131 || index != 1)));
    line2->setVisible(i>2 ||(i==2 && (code !=131 || index != 1)));

    label3->setVisible(i>3 ||(i==3 && (code !=131 || index != 1)));
    line3->setVisible(i>3 ||(i==3 && (code !=131 || index != 1)));

    label4->setVisible(i==4 && (code !=131 || index != 1));
    line4->setVisible(i==4 && (code !=131 || index != 1));
}

void FctnDialog::selectLabels(){
    if(fctnCode == 131){
        int var = factory->getVariables(op);

        if(var == 2){
            label1->setText("a = ");
            label2->setText("x = ");
        }
        else if(var == 3){
            if(op == "binomial distribution" || op == "negative distribution"){
                label1->setText("n = ");
                label2->setText("p = ");
            }
            else if (op == "normal distribution" || op == "laplace distribution"){
                QString help = QString((QChar)0x03BC);
                help = help.append(" = ");
                label1->setText(help);
                help = QString((QChar)0x03C3);
                help = help.append(" = ");
                label2->setText(help);
            }
            else if (op == "cauchy distribution"){
                label1->setText("x<sub>0</sub> = ");
                QString help = QString((QChar)0x03B3);
                help = help.append(" = ");
                label2->setText(help);
            }
            else if (op == "extreme distribution" || op =="log distribution" || op =="logistic distribution"){
                label1->setText("loc = ");
                label2->setText("scale = ");
            }
            else if (op == "gamma distribution"){
                label1->setText("k = ");
                QString help = QString((QChar)0x03B8);
                help = help.append(" = ");
                label2->setText(help);
            }
            else{
                label1->setText("a = ");
                label2->setText("b = ");
            }
            label3->setText("x = ");
        }
        else{
            if (op == "hypergeometric distribution"){
                label1->setText("k = ");
                label2->setText("n = ");
                label3->setText("N = ");
            }
            else {
                label1->setText("a = ");
                label2->setText("b = ");
                label3->setText("c = ");
            }
            label4->setText("x = ");
        }
    }
    else if (fctnCode == 200) {
        QString str = op;
        str = str.append(" = ");
        label1->setText(str);
    }
    else if (fctnCode == 170 || fctnCode == 173 || fctnCode == 175) {
        QString str = "f(x) = ";
        label1->setText(str);
    }
    else if (fctnCode == 171) {
        QString str = "f(x) = ";
        label1->setText(str);
        label2->setText("x<sub>0</sub> = ");
    }
    else if (fctnCode == 174) {
        label1->setText("f(x) = ");
        label2->setText("a = ");
        label3->setText("b = ");
    }
    else{
        if(op == "j" || op == "y"){
            label1->setText("v = ");
            label2->setText("x = ");
        }
        else if(op == "if"){
            label1->setText("if");
            label2->setText("then");
            label3->setText("else");
        }
        else if (op == "legendre" || op == "laguerre" || op == "exponential integral" || op == "hermit"){
            label1->setText("n = ");
            label2->setText("x = ");
        }
        else if (op == "facfal" || op == "facris"){
            label1->setText("x = ");
            label2->setText("n = ");
        }
        else if (op == "assignment" || op == "init" || op == "delete"){
            label1->setText("name = ");
            label2->setText("value = ");
        }
        else if (op == "execute"){
            label1->setText("script = ");
            label2->setText("input = ");
            label3->setText("output = ");
        }
        else if (op == "record"){
            label1->setText("record name = ");
            label2->setText("script = ");
            label3->setText("input = ");
            label4->setText("output = ");
        }
        else if (op == "saveAs" || op == "open"){
            label1->setText("filename = ");
        }
        else if (op == "function" || op == "plot" || op == "cplxPlot") {
            label1->setText("f(x) = ");
        }
        else if (op == "k" || op == "e1"){
            label1->setText("k = ");
        }
        else if (op == "zeroMatrix"){
            label1->setText("rows = ");
            label2->setText("columns = ");
        }
        else if (op == "diagMatrix"){
            label1->setText("rows / columns = ");
            label2->setText("diag-entries = ");
        }
        else if (op == "getEntry" || op == "setEntry"){
            label1->setText("matrix = ");
            label2->setText("row = ");
            label3->setText("column = ");
            label4->setText("value = ");
        }
        else if (op == "e2" || op == "f"){
            QString help = QString((QChar)0x03C6);
            help = help.append(" = ");
            label1->setText(help);
            label2->setText("k = ");
        }
        else if (op == "pi3"){
            label1->setText("n = ");
            QString help = QString((QChar)0x03C6);
            help = help.append(" = ");
            label2->setText(help);
            label3->setText("k = ");
        }
        else if (op == "spherical harmonics"){
            label1->setText("n = ");
            label2->setText("m = ");
            QString help = QString((QChar)0x03B8);
            help = help.append(" = ");
            label3->setText(help);
            help = QString((QChar)0x03C6);
            help = help.append(" = ");
            label4->setText(help);
        }
        else{
            label1->setText("a = ");
            label2->setText("b = ");
            label3->setText("c = ");
            label4->setText("d = ");
        }
    }
}

void FctnDialog::make_visible(/*MaceInt characteristic,*/ QListWidgetItem *item){

    ok = false;

    QVariant func_type;
    func_type = item->data(100);
    op = func_type.toString();
    fctnCode = factory->getCode(op);

    info->setHtml(factory->help_info(op,fctnCode));
    if (fctnCode == 200) {
        func_type = item->data(101);
        op = func_type.toString();
    }

    pLabel->setHidden(true);
    pBox->setHidden(true);
    pLabel2->setHidden(true);
    pBox2->setHidden(true);
    label1->setVisible(true);
    line1->setVisible(true);

    line1->setContextMenuPolicy(Qt::DefaultContextMenu);

    if(fctnCode >= 100){
        setWindowTitle(factory->get_typeName(fctnCode));

        labelFormat(!tab->currentIndex());
        selectLabels();
    }

    line1->all = true;

    tab->setVisible(fctnCode == 131);
    linesFormat(factory->getVariables(op),fctnCode,tab->currentIndex());

    line1->clear();
    line2->clear();
    line3->clear();
    line4->clear();


    this->setMaximumHeight(80);

    if(fctnCode <100){
        line1->all = false;
    }
    else {
        line1->all = true;
        line2->all = true;
        line3->all = true;
        line4->all = true;
    }

    info->setHidden(true);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    but->setFocus();

    emit hello();
    this->show();
}

int FctnDialog::getFctnCode(){
    return fctnCode;
}

QString FctnDialog::getOption(){
    return op;
}

void FctnDialog::nextLine(){
    if(line2->isVisible()){
        line2->setFocus();
    }
    else{
        agree();
    }
}

