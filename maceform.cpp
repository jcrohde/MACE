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

#include "math/interpreter/command.h"
#include "maceform.h"

static void completeScriptString(const QString &inputStr, const QString &outputStr, QString &str) {
    if (inputStr.size() > 0) {
        str = str.append(",");
        str = str.append(inputStr);
    }
    str = str.append(")");
    if (outputStr.size() > 0) {
        str = str.append("->(");
        str = str.append(outputStr);
        str = str.append(")");
    }
}

static void copyResultToInput(MaceTextEdit *texts, inputTextEdit *inputEdit) {
    QString result = texts->getLastResult();
    inputEdit->setPlainText(result);
    QTextCursor cursor(inputEdit->textCursor());
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    inputEdit->setTextCursor(cursor);
}

static void ShowError(QErrorMessage* error, validCheck &validC) {
    if (!validC.isValid()) {
        QString errorMsg;
        validC.getErrMsg(errorMsg);
        error->showMessage(errorMsg);
    }
}

MaceForm::MaceForm(QFileDialog *f, int th, int tw, int ch, int cw, QWidget *parent) : files(f), textHeight(th),
    textWidth(tw), calcHeight(ch), calcWidth(cw), QDialog(parent)
{
    fileOpened = "";

    error = new QErrorMessage;
    error->setWindowFlags(error->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    fctns = new MaceFctnBar;
    vert = new QVBoxLayout;

    mainLayout = new QHBoxLayout;
    left = new QVBoxLayout;
    inputLayout = new QVBoxLayout;
    textLayout = new QSplitter;
    texts = new MaceTextEdit;
    inputEdit = new inputTextEdit();
    inputLabel = new QLabel("Input Editor:");
    inputLabel->setFixedHeight(12);

    factory = new stringFactory;
    kernel.factory = factory;

    selection = new MaceListWidget(factory);
    opwindow = new FctnDialog(factory);
    mats = new matrixEnter(factory);

    buts = new CalcButs(calcHeight, calcWidth, 10, inputEdit);

    nextOperation = false;

    selection->setFixedWidth(5*calcWidth);

    left->addWidget(selection);
    left->addLayout(buts);

    textLayout->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    textLayout->setOrientation(Qt::Vertical);
    textLayout->addWidget(texts);
    textLayout->addWidget(inputLabel);
    textLayout->addWidget(inputEdit);
    textLayout->setCollapsible(1,false);
    textLayout->setCollapsible(2,false);

    mainLayout->addLayout(left);
    mainLayout->addWidget(textLayout);

    copy = new QListWidgetItem;
    memory = new QListWidgetItem;
    change = new QListWidgetItem;
    change->setData(100,"write a matrix");
    change->setData(101,"No");

    vert->addLayout(fctns);
    vert->addLayout(mainLayout);

    this->setLayout(vert);

    error->setWindowTitle("ERROR");
    error->setWindowIcon(QIcon("icons/MaceLogo.png"));

    lines = 2;
    columns = 2;
    prec = 6;

    kernel.validC = &validC;
    kernel.read   = &read;

    QObject::connect(this->selection,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(make_visible(QListWidgetItem*)));
    QObject::connect(opwindow,SIGNAL(inserted()),this,SLOT(getSignal()));
    QObject::connect(mats,SIGNAL(inserted()),this,SLOT(linearAlgebra()));

    QObject::connect(this->fctns,SIGNAL(sendItem(QListWidgetItem*)),this,SLOT(make_visible(QListWidgetItem*)));

    QObject::connect(this->mats,SIGNAL(changeMatrix(QListWidgetItem*)),this,SLOT(make_visible(QListWidgetItem*)));
    QObject::connect(this->mats->but2,SIGNAL(clicked()),this,SLOT(no()));

    QObject::connect(texts,SIGNAL(pleaseCalculate(QString)),this,SLOT(calculate(QString)));
    QObject::connect(texts,SIGNAL(pleaseMatrix(QString)),this,SLOT(matrix(QString)));
    QObject::connect(texts,SIGNAL(storeMatrix(QString)),this,SLOT(storeMatrix(QString)));

    QObject::connect(texts,SIGNAL(inputText(QString)),inputEdit,SLOT(setPlainText(QString)));

    QObject::connect(inputEdit,SIGNAL(calculate(QString)),this,SLOT(calculate(QString)));
    QObject::connect(inputEdit,SIGNAL(up(bool)),texts,SLOT(up(bool)));

    QObject::connect(buts,SIGNAL(reset()),texts,SLOT(reset()));
}

MaceForm::~MaceForm()
{
    delete opwindow;
    delete mats;
    delete error;
}

//general slot for functions, matrices, settings, etc.... . It makes either opwindow or mats visible.
void MaceForm::make_visible(QListWidgetItem *i){

    QVariant func_type;
    QString key;
    func_type = i->data(100);
    key = func_type.toString();
    int fctnCode = factory->getCode(key);

    if(i->text() == "rows / columns" || i->text() == "variables and equations" || i->text() == "columns" || i->text() == "rows and columns"){
        opwindow->change_linesColumns(i);
    }
    else if (fctnCode >= 140 && fctnCode <148){
        linAVisible(i);
    }
    else if(fctnCode > 0){
        opwindow->make_visible(/*characteristic,*/i);
    }
}

//general slot for opwindow

void MaceForm::getSignal(){
    QString str;
    if (opwindow->getFctnCode() == 10){
        setCharacteristic();
    }
    else if(opwindow->getFctnCode() == 20){
        setLinesColumns();
    }
    else if(opwindow->getFctnCode() == 40){
        precision();
    }
    else if(opwindow->getFctnCode() >= 140 && opwindow->getFctnCode() < 148){
        resetLinesColumns();
    }
    else if (opwindow->getFctnCode() == 200) {
        variableValue(opwindow->a);
    }
    else if (opwindow->getFctnCode() >= 100) {
        scalOp();
    }
}

///////////////////////////////////////////////////////////////////
//Settings
///////////////////////////////////////////////////////////////////

//characteristic

void MaceForm::setCharacteristic(){
    //characteristic.set(opwindow->a);
    applyCharacteristic();
}

void MaceForm::applyCharacteristic() {
    QString str;// = characteristic.print();
    str = str.append("<br>");
    str = str.append(block());
    texts->charWrite(str);
}

QString MaceForm::block(){
    QString text = "";

    //texts->setChar(/*characteristic*/);
    /*if (characteristic > 0){
        buts->buti->setEnabled(0);
        buts->butDot->setEnabled(0);
        buts->complex = false;
        selection->posChar = true;
        fctns->posChar = true;
    }
    else{*/
        buts->buti->setEnabled(1);
        buts->butDot->setEnabled(1);
        buts->complex = true;
        selection->posChar = false;
        fctns->posChar = false;
    //}

    int i = 0;//kernel.distC.arithC.smallPrimeTest(characteristic);
    /*if (characteristic > 0 && i != 2){
        selection->set_field(false);
        fctns->set_field(false);
        buts->butDiv->setEnabled(0);
        buts->field = false;

        if(i == 0){
            text = text.append("<br>Since ");
            text = text.append(characteristic.print());
            text = text.append(" is not a prime number, the residue classes modulo ");
            text = text.append(characteristic.print());
            text = text.append(" do not form a field. ");
        }
        else{
            text = text.append("<br>This is larger than the upper bound 1.373.653 of the implemented primality test. ");
        }
        text = text.append("Therefore several functions are blocked due to security reasons.<br>");

    }
    else{
        selection->set_field(true);
        fctns->set_field(true);
        buts->butDiv->setEnabled(1);
        buts->field = true;
    }*/
    return text;
}

//rows and columns

void MaceForm::setLinesColumns(){
    int linHelp = opwindow->pBox->value();
    int colHelp = opwindow->pBox2->value();

    if(linHelp <= 0 || colHelp <= 0){
        QString str = "A matrix must have a positive number of rows and columns.";
        error->showMessage(str);
    }
    else if (linHelp >20 || colHelp > 20){
        QString str = "The numbers of rows and columns of a matrix is restricted by 20 here.";
        error->showMessage(str);
    }
    else{
        lines = linHelp;
        columns = colHelp;
    }
}

//precision

void MaceForm::precision(){
    int linHelp = opwindow->pBox->value();

    if(linHelp < 2){
        QString str = "The minimal precision is 2.";
        error->showMessage(str);
    }
    else if (linHelp > 16){
        QString str = "The maximal precision is 16.";
        error->showMessage(str);
    }
    else{
        prec = linHelp;
    }
}

//plot

void MaceForm::plotten(QString str){
    bool cplx = false;
    if(str.indexOf("complex") > -1){
        cplx = true;
    }
    plotter = new plotDialog(files, cplx, &kernel);
    plotter->show();
}

///////////////////////////////////////////////////////////////////
//Scalar Operations
///////////////////////////////////////////////////////////////////

void MaceForm::sketchingPart(QString command, QString &func) {
    MVar var2;
    QString str = func;
    str = str.prepend("(");
    str = str.prepend(command);
    str = str.append(")");
    texts->zeroWrite(command);
    /*if (kernel.interface(&str,/*characteristic,&var2))
        texts->displayResult(var2.print(6));
    else {
        QString ErrorM;
        kernel.validC->getErrMsg(ErrorM);
        texts->displayResult(ErrorM);
    }*/
}

//huge method for textoperations for scalar operations

void MaceForm::scalOp(){
    if(opwindow->getFctnCode() == 126){
        MVar var;
        QString ing = opwindow->a;
        ing = ing.append(")");
        ing = ing.prepend("prime_factor_decomposition(");
        kernel.valid = false;

        texts->zeroWrite(ing);
        //kernel.interface(&opwindow->a,/*characteristic,*/&var);
        /*if (var.getType() == INT) {
            MaceInt mint;
            var.getInt(&mint);
            if (mpz_cmp_si(mint.entry.get_mpz_t(),0) < 0)
                mpz_mul_si(mint.entry.get_mpz_t(),mint.entry.get_mpz_t(),-1);
            if(kernel.valid) ing = kernel.distC.arithC.factors(mint);
        }
        else if (characteristic == 0) {
            numPoly npoly;
            if (var.getNumPoly(&npoly)) {
                if(kernel.valid) ing = kernel.distC.arithC.factors(npoly);
            }
        } else {
            if (var.getType() == RESTPOLY) {
                restPoly rpoly;
                var.getRestPoly(&rpoly);
                if(kernel.valid) ing = kernel.distC.arithC.factors(rpoly);
            }
        }*/
        if(!kernel.valid){
            kernel.valid = true;
            texts->displayResult("Syntax Error");
        }
        else{
            texts->displayResult(ing);
        }
        inputEdit->setFocus();
    }
    /*else if(opwindow->getOption() == "extended Euclidean algorithm"){
        MVar var, var2;
        kernel.interface(&opwindow->a,characteristic,&var);
        kernel.interface(&opwindow->b,characteristic,&var2);
        QString ing = opwindow->a;
        ing = ing.append(" and ");
        ing = ing.append(opwindow->b);
        ing = ing.append(":");
        ing = ing.prepend("extended Euclidean algorithm for ");

        texts->zeroWrite(ing);
        if (var.getType() == INT && var2.getType() == INT) {
            MaceInt mint, mint1;
            var.getInt(&mint); var2.getInt(&mint1);
            if (mpz_cmp_si(mint.entry.get_mpz_t(),0) < 0)
                mpz_mul_si(mint.entry.get_mpz_t(),mint.entry.get_mpz_t(),-1);
            if (mpz_cmp_si(mint1.entry.get_mpz_t(),0) < 0)
                mpz_mul_si(mint1.entry.get_mpz_t(),mint1.entry.get_mpz_t(),-1);
            if(kernel.valid) ing = kernel.distC.arithC.intExEu(mint,mint1,characteristic);
        } else if (characteristic == 0) {
            if (var.getType() == ALGPOLY || var2.getType() == ALGPOLY) {
                algPoly apoly, apoly1;
                var.getAlgPoly(&apoly); var2.getAlgPoly(&apoly1);
                if(kernel.valid) ing = kernel.distC.arithC.iExEu(apoly,apoly1,characteristic);
            }
        } else {
            if (var.getType() == RESTPOLY || var2.getType() == RESTPOLY) {
                restPoly rpoly, rpoly1;
                var.getRestPoly(&rpoly); var2.getRestPoly(&rpoly1);
                if(kernel.valid) ing = kernel.distC.arithC.iExEu(rpoly,rpoly1,characteristic);
            }
        }

        if(!kernel.valid){
            kernel.valid = true;
            texts->displayResult("Syntax Error");
        }
        else{
            texts->displayResult(ing);
        }
        inputEdit->setFocus();
    }
    else if (opwindow->getOption() == "curve sketching") {
        QString str, dstr, cstr = "func(";
        cstr = cstr.append(opwindow->a);
        cstr = cstr.append(")");
        MVar var, var2;
        kernel.interface(&cstr,characteristic,&var);
        str = "Curve sketching for ";
        texts->zeroWrite(str);
        texts->displayResult(var.print(6));
        sketchingPart("symmetry",cstr);
        sketchingPart("derivative",cstr);
        texts->zeroWrite("second derivative");
        dstr = cstr;
        dstr = dstr.prepend("derivative(derivative(");
        dstr = dstr.append("))");
        if (kernel.interface(&dstr,characteristic,&var2))
            texts->displayResult(var2.print(6));
        else {
            QString ErrorM;
            kernel.validC->getErrMsg(ErrorM);
            texts->displayResult(ErrorM);
        }
        texts->zeroWrite("third derivative");
        dstr = cstr;
        dstr = dstr.prepend("derivative(derivative(derivative(");
        dstr = dstr.append(")))");
        if (kernel.interface(&dstr,characteristic,&var2))
            texts->displayResult(var2.print(6));
        else {
            QString ErrorM;
            kernel.validC->getErrMsg(ErrorM);
            texts->displayResult(ErrorM);
        }
        sketchingPart("zeroes",cstr);
        sketchingPart("extrema",cstr);
        sketchingPart("inflexion",cstr);
        plotter = new plotDialog(files, false, &kernel);
        plotter->show();
        plotter->fl->setText(opwindow->a);
        plotter->replot();
    }*/
    else if(opwindow->getFctnCode() >= 100){
        QString str, key = opwindow->getOption();
        if(key == "a^2"){
            str = str.append(opwindow->a);
            str = str.append("^2");
        }
        else if(key == "a^n"){
            str = str.append(opwindow->a);
            str = str.append("^");
            str = str.append(opwindow->b);
        }
        else if(factory->getCode(key) == 131){
            if(opwindow->tab->currentIndex()==1){
                if(opwindow->mean->isChecked()) str = str.append("mean");
                else if(opwindow->median->isChecked()) str = str.append("median");
                else if(opwindow->mode->isChecked()) str = str.append("mode");
                else if(opwindow->skewness->isChecked()) str = str.append("skew");
                else if(opwindow->standdev->isChecked()) str = str.append("stDev");
                else if(opwindow->variance->isChecked()) str = str.append("var");
                else if(opwindow->kurt->isChecked()) str = str.append("kurt");
                else str = str.append("kurtEx");
                str = str.append("(");
                str = str.append(factory->getHtml(key));
                str = str.append("(");
                str =str.append(opwindow->a);
                if(factory->getVariables(key) > 2){
                    str = str.append(",");
                    str = str.append(opwindow->b);
                }
                if(factory->getVariables(key) > 3){
                    str = str.append(",");
                    str = str.append(opwindow->c);
                }
                str = str.append("))");
            }
            else{
                if(opwindow->pdf->isChecked()) str = str.append("pdf");
                else if(opwindow->cdf->isChecked()) str = str.append("cdf");
                else if(opwindow->hazard->isChecked()) str = str.append("haz");
                else str = str.append("qua");

                str = str.append("(");
                str = str.append(factory->getHtml(key));
                str = str.append("(");

                str = str.append(opwindow->a);

                if(factory->getVariables(key) == 2){
                   str = str.append("),");
                   str = str.append(opwindow->b);
                }
                else if (factory->getVariables(key) == 3){
                    str = str.append(",");
                    str = str.append(opwindow->b);
                    str = str.append("),");
                    str = str.append(opwindow->c);
                }
                else if (factory->getVariables(key) == 4){
                    str = str.append(",");
                    str = str.append(opwindow->b);
                    str = str.append(",");
                    str = str.append(opwindow->c);
                    str = str.append("),");
                    str = str.append(opwindow->d);
                }

                str.append(")");
            }
        }
        else if (opwindow->getFctnCode() == 152 || opwindow->getFctnCode() == 153 || opwindow->getFctnCode() == 154) {
            if (factory->getVariables(key) == 1) {
                str = factory->getHtml(key);
                str = str.append(opwindow->a);
            }
            else {
                str = opwindow->a;
                str = str.append(factory->getHtml(key));
                str = str.append(opwindow->b);
            }
        }
        else if (opwindow->getOption() == "string") {
            str = "\"";
            str = str.append(opwindow->a);
            str = str.append("\"");
        }
        else if (opwindow->getOption() == "execute") {
            str = "execute(";
            str = str.append(opwindow->a);
            completeScriptString(opwindow->b,opwindow->c,str);
        }
        else if (opwindow->getOption() == "record") {
            str = "record(";
            str = str.append(opwindow->a);
            str = str.append(",");
            str = str.append(opwindow->b);
            completeScriptString(opwindow->c,opwindow->d,str);
        }
        else{
            str = str.append(factory->getHtml(key));
            str = str.append("(");
            if (factory->getCode(key) >= 170 && factory->getCode(key) <180) {
                str = str.append("func(");
                str = str.append(opwindow->a);
                str = str.append(")");
            }
            else str = str.append(opwindow->a);
            if(factory->getVariables(key) > 1){
                str = str.append(",");
                str = str.append(opwindow->b);
            }
            if(factory->getVariables(key) > 2){
                str = str.append(",");
                str = str.append(opwindow->c);
            }
            if(factory->getVariables(key) > 3){
                str = str.append(",");
                str = str.append(opwindow->d);
            }
            str = str.append(")");
        }
        inputEdit->insertPlainText(str);
        inputEdit->setFocus();
    }
}

//slot for textedit

bool MaceForm::calculate(QString str, DataBase *data){
    if (str.size() > 0) {
        bool valid = true;
        if (data == 0) {
            reader read;
            read.init(str);
            validC.init();
            if (read.getTokenString("execute(")) {
                if (valid) {
                    valid = read.getStringTillBrackClose(scriptString,validC);
                    if (!valid) validC.setErr(NOBRACKCL);
                }
                if (read.getTokenString("->(") && valid) {
                    valid = read.getStringTillBrackClose(scriptOutString,validC);
                    if (!valid) validC.setErr(NOBRACKCL);
                }
                if (valid) emit callScript();
                ShowError(error,validC);
                return valid;
            }
            else if (read.getTokenString("record(")) {
                if (valid) {
                    valid = read.getStringTillBrackClose(scriptString,validC);
                    if (!valid) validC.setErr(NOBRACKCL);
                }
                if (read.getTokenString("->(") && valid) {
                    valid = read.getStringTillBrackClose(scriptOutString,validC);
                    if (!valid) validC.setErr(NOBRACKCL);
                }
                if (valid ) emit callAction();
                ShowError(error,validC);
                return valid;
            }
            if (executeSpecialCommand(read,kernel.variableData,this,valid)) {
                ShowError(error,validC);
                return valid;
            }
        }
        texts->standardWrite(str);
        //str = kernel.interface(&str, /*characteristic,*/ prec, data);
        valid = valid && !str.contains("Error");
        texts->displayResult(str);
        return valid;
    }
    else copyResultToInput(texts,inputEdit);
    return true;
}

/////////////////////////////////////////////////////////////////////////////
// Linear Algebra
/////////////////////////////////////////////////////////////////////////////

//stops operation
void MaceForm::no() {
    change->setData(101,"No");
}

//makes mats visible

void MaceForm::linAVisible(QListWidgetItem *i){
    QVariant func_type;
    QString key;
    func_type = i->data(100);
    key = func_type.toString();
    int fctnCode = factory->getCode(key);

    bool mtrx = texts->matrixInput();

    if (fctnCode == 140 || fctnCode == 146){
        if (key == "write a matrix") {
            mats->make_visible(lines,columns,/*characteristic,*/i);
        }
        else if (key == "cross product") {
            if (lines == 3 && columns == 1 && mtrx) {
                mats->make_visible(lines,columns,/*characteristic,*/i);
            }
            else {
                change->setData(101,i->data(100));
                lines = 3; columns = 1;
                mtrx = false;
                mats->make_visible(lines,columns,/*characteristic,*/change,true);
            }
        }
        /*else{
            if (mtrx) {
                if (key == "* for matrices") {
                    if (characteristic.larger(0)) lines = rmat.columns;
                    else lines = amat.columns;
                }
                else if (key == "/ for matrices") {
                    if (characteristic.larger(0)) lines = rmat.columns;
                    else lines = amat.columns;
                    columns = lines;
                }
                else {
                    if (characteristic.larger(0)) {lines = rmat.lines; columns = rmat.columns;}
                    else {lines = amat.lines; columns = amat.columns;}
                }
                if (key == "conjm") {
                    if (lines == columns) mats->make_visible(lines,columns,characteristic,i,true);
                    else {
                        change->setData(101,i->data(100));
                        lines = columns;
                        mtrx = false;
                        mats->make_visible(lines,columns,characteristic,change,false,true);
                    }
                }
                else mats->make_visible(lines,columns,characteristic,i);
            }
            else {
                change->setData(101,i->data(100));
                if (key == "conjm") {
                    lines = columns;
                    mats->make_visible(lines,columns,characteristic,change,false,true);
                }
                else mats->make_visible(lines,columns,characteristic,change);
            }
        }*/
    }
    /*else if (fctnCode == 143) mats->make_visible(lines,columns,characteristic,i);
    else{
        if (!mtrx && (lines != columns) && (key == "inverse matrix" || key == "determinant of a matrix"
                                || key == "minimal polynomial of a matrix" || key == "characteristic polynomial of a matrix"
                                            || key == "trace of a matrix" || key == "eigenvalues of a matrix"
                                            || key == "adjoint matrix")) {
            columns = lines;
            mats->make_visible(lines,columns,characteristic,i);
        }
        else if (!mtrx) mats->make_visible(lines,columns,characteristic,i);
        else {
            mats->op = key;
            mats->fctnCode = fctnCode;
            linearAlgebra();
        }
    }*/
}

//slot for writing an old matrix
void MaceForm::matrix(QString str){
    QString error;
    /*if (characteristic.larger(0)){
        rmat = kernel.strToRestMatrix(str,characteristic,error);
        lines = rmat.lines;
        columns = rmat.columns;
        str = rmat.toHtml();
        texts->restoreMatrix(str);
    }
    else {
        amat = kernel.strToAlgMatrix(str,error);
        lines = amat.lines;
        columns = amat.columns;
        str = amat.toHtml();
        texts->restoreMatrix(str);
    }*/
}

bool MaceForm::setMatrix(genMatrix *genMat) {
    QString str;
    bool valid = true;

    /*if (characteristic.larger(0)){
        restMatrix *r = dynamic_cast<restMatrix*>(genMat);
        if (r != 0) {
            rmat = *r;
            lines = rmat.lines;
            columns = rmat.columns;
            str = rmat.toHtml();
            texts->restoreMatrix(str);
        }
        else valid = false;
    }
    else {
        algMatrix *a = dynamic_cast<algMatrix*>(genMat);
        if (a != 0) {
            amat = *a;
            lines = amat.lines;
            columns = amat.columns;
            str = amat.toHtml();
            texts->restoreMatrix(str);
        }
        else valid = false;
    }*/
    return valid;
}

void MaceForm::storeMatrix(QString str){
    QString error;
    /*if (characteristic.larger(0)){
        rmat = kernel.strToRestMatrix(str,characteristic,error);
        lines = rmat.lines;
        columns = rmat.columns;
    }
    else {
        amat = kernel.strToAlgMatrix(str,error);
        lines = amat.lines;
        columns = amat.columns;
    }*/
}

//slot for mats

void MaceForm::linearAlgebra(){
    QString str,estr;
    QString ans;
    kernel.valid = true;
    bool err = false;

    estr.clear();
    bool mtrx = texts->matrixInput();

    /*if(characteristic.larger(0)) {
        if (mats->fctnCode == 140 || mats->fctnCode == 146){
            if (mats->op == "write a matrix"){
                rmat = kernel.strToRestMatrix(mats->matInfo,characteristic,estr);
                if (estr.size() > 0) error->showMessage(estr);
                else {
                    str = rmat.toHtml();
                    texts->singleMatrix(str);
                }
            }
            else{
                restMatrix rmat1  = kernel.strToRestMatrix(mats->matInfo,characteristic,estr);
                if(estr.size() == 0){
                    if (mats->op == "+ for matrices"){
                        str = linAlg.LAP.writeMatOp(&rmat, "+", &rmat1);
                        texts->singleMatrix(str);
                        rmat = rmat+rmat1;
                    }
                    else if(mats->op == "- for matrices"){
                        str = linAlg.LAP.writeMatOp(&rmat, "-", &rmat1);
                        texts->singleMatrix(str);
                        rmat = rmat-rmat1;
                    }
                    else if(mats->op == "* for matrices"){
                        str = linAlg.LAP.writeMatOp(&rmat, "*", &rmat1);
                        texts->singleMatrix(str);
                        rmat = rmat*rmat1;
                    }
                    else if(mats->op == "/ for matrices"){
                        restMatrix rmat2 = rmat/rmat1;
                        if (rmat2.valid) {
                            str = linAlg.LAP.writeMatOp(&rmat, "/", &rmat1);
                            texts->singleMatrix(str);
                            rmat = rmat2;
                        }
                        else err = true;
                    }
                    else if(mats->op == "cross product"){
                        str = linAlg.LAP.writeMatOp(&rmat, "&times;", &rmat1);
                        texts->singleMatrix(str);
                        rmat = rmat.cross(rmat1);
                    }
                    else if(mats->op == "conjm"){
                        str = linAlg.LAP.writeMatOp(&rmat, "conj with", &rmat1);
                        restMatrix rmat2 = rmat*rmat1;
                        err = !rmat.invert(rmat1);
                        if (!err) {
                            rmat = rmat1*rmat2;
                            texts->singleMatrix(str);
                        }
                    }
                    if (err) error->showMessage("Error: The second matrix is not invertible");
                    else texts->displayMatrixResult(rmat.toHtml(),rmat.lines);
                } else error->showMessage(estr);
            }
        }
        else{
            if (!mtrx) rmat = kernel.strToRestMatrix(mats->matInfo,characteristic,estr);
            if (estr.size() == 0) {
                if(mats->fctnCode ==141 || mats->fctnCode == 142  || mats->fctnCode == 147){
                    if(kernel.valid){
                        str = linAlg.matLinADist(&rmat,mats->op);
                        if (str.indexOf("Error") == -1){
                            texts->singleMatrix(str);
                            ans = rmat.toHtml();
                            texts->displayMatrixResult(ans,rmat.lines);
                        }
                        else{
                            error->showMessage(str);
                        }
                    }
                    lines = rmat.lines;
                    columns = rmat.columns;
                }
                else if(mats->fctnCode ==143){
                    texts->zeroWrite("System of linear equations");
                    rmat = kernel.strToRestMatrix(mats->matInfo,characteristic,estr);
                    if(kernel.valid){
                    restMatrix lsg = kernel.strToRestMatrix(mats->resInfo,characteristic,estr);
                    str = linAlg.SLE_dist(rmat,lsg);
                    texts->displaySLEResult(str);
                    }
                }
                else if(mats->fctnCode ==144 || mats->fctnCode ==145){

                    if(!mtrx)rmat = kernel.strToRestMatrix(mats->matInfo,characteristic,estr);
                    if(kernel.valid){
                        str = linAlg.scalarLinADist(&ans, rmat, mats->op);
                        if (str.indexOf("Error") == -1){
                        texts->singleMatrix(ans);
                        texts->displayResult(str);
                        }
                        else{
                            error->showMessage(str);
                        }
                    }
                }
            }
            error->showMessage(estr);
        }
    }
    else{
        if (mats->fctnCode == 140 || mats->fctnCode == 146){
            if (mats->op == "write a matrix"){
                amat = kernel.strToAlgMatrix(mats->matInfo, estr);
                if (estr.size()> 0) error->showMessage(estr);
                else {
                    str = amat.toHtml();
                    texts->singleMatrix(str);
                }
            }
            else{
                algMatrix amat1  = kernel.strToAlgMatrix(mats->matInfo,estr);
                if (estr.size() == 0) {
                    if (mats->op == "+ for matrices"){
                        str = linAlg.LAP.writeMatOp(&amat, "+", &amat1);
                        texts->singleMatrix(str);
                        amat = amat+amat1;
                    }
                    else if(mats->op == "- for matrices"){
                        str = linAlg.LAP.writeMatOp(&amat, "-", &amat1);
                        texts->singleMatrix(str);
                        amat = amat-amat1;
                    }
                    else if(mats->op == "* for matrices"){
                        str = linAlg.LAP.writeMatOp(&amat, "*", &amat1);
                        texts->singleMatrix(str);
                        amat = amat*amat1;
                    }
                    else if(mats->op == "/ for matrices"){
                        algMatrix amat2 = amat/amat1;
                        if (amat2.valid) {
                            str = linAlg.LAP.writeMatOp(&amat, "/", &amat1);
                            texts->singleMatrix(str);
                            amat = amat2;
                        }
                        else err = true;
                    }
                    else if(mats->op == "cross product"){
                        str = linAlg.LAP.writeMatOp(&amat, "&times;", &amat1);
                        texts->singleMatrix(str);
                        amat = amat.cross(amat1);
                    }
                    else if(mats->op == "conjm"){
                        str = linAlg.LAP.writeMatOp(&amat, "conj with", &amat1);
                        algMatrix amat2 = amat*amat1;
                        err = !amat.invert(amat1);
                        if (!err) {
                            amat = amat1*amat2;
                            texts->singleMatrix(str);
                        }
                    }
                    if (err) error->showMessage("Error: The second matrix is not invertible");
                    else texts->displayMatrixResult(amat.toHtml(),amat.lines);
                } else error->showMessage(estr);
            }
        }
        else{
            if (!mtrx) amat = kernel.strToAlgMatrix(mats->matInfo,estr);
            if (estr.size() == 0) {
                if(mats->fctnCode ==141 || mats->fctnCode ==142  || mats->fctnCode ==147){
                    if(kernel.valid){
                        str = linAlg.matLinADist(&amat, mats->op);
                        if (str.indexOf("Error") == -1){
                            texts->singleMatrix(str);
                            ans = amat.toHtml();
                            texts->displayMatrixResult(ans,amat.lines);
                        }
                        else{
                            error->showMessage(str);
                        }
                    }
                    lines = amat.lines;
                    columns = amat.columns;
                }
                else if(mats->fctnCode ==143){
                    texts->zeroWrite("System of linear equations");
                    amat = kernel.strToAlgMatrix(mats->matInfo,estr);
                    if(kernel.valid){
                    algMatrix lsg = kernel.strToAlgMatrix(mats->resInfo,estr);
                    str = linAlg.SLE_dist(amat,lsg);
                    texts->displaySLEResult(str);
                    }
                }
                else if(mats->fctnCode ==144 || mats->fctnCode ==145){

                    if (!mtrx) amat = kernel.strToAlgMatrix(mats->matInfo,estr);
                    if(kernel.valid){
                    str = linAlg.scalarLinADist(&ans, amat, mats->op);
                    if (str.indexOf("Error") == -1) {
                        texts->singleMatrix(ans);
                        texts->displayResult(str);
                    }
                    else{
                        error->showMessage(str);
                    }
                    }
                }
            }
            else error->showMessage(estr);
        }
    }

    if (change->data(101) != "No" ) {
        if (estr.size() == 0) {
            memory->setData(100,change->data(101));
            QVariant func_type = change->data(101);
            if (func_type.toString() == "* for matrices") lines = columns;
            linAVisible(memory);
        }
        change->setData(101,"No");
    }

    inputEdit->setFocus();*/
}

void MaceForm::resetLinesColumns(){
    QString labelStr = opwindow->label->text();
    int linHelp, colHelp;

    if(labelStr == "Choose number of rows / columns:"){
        linHelp = opwindow->pBox->value();
        colHelp = linHelp;
    }
    else if(labelStr == "Choose number of columns:"){
        colHelp = opwindow->pBox->value();
        linHelp = columns;
    }
    else{
        linHelp = opwindow->pBox->value();
        colHelp = opwindow->pBox2->value();
    }
    if(linHelp == 0 || colHelp == 0){
        QString str = "A matrix cannot have 0 rows or 0 columns.";
        error->showMessage(str);
    }
    else if (linHelp >20 || colHelp > 20){
        QString str = "The numbers of rows and columns of a matrix is restricted by 20 here.";
        error->showMessage(str);
    }
    else{
        lines = linHelp;
        columns = colHelp;

        QString txt = opwindow->getOption();
        copy->setData(100,txt);
        copy->setText(factory->get_info(txt));

        //mats->make_visible(lines, columns, characteristic, copy);
    }
}
