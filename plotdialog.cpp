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

#include "plotdialog.h"

plotDialog::plotDialog(QFileDialog *fi, bool b, parser *pars, QWidget *parent) :
    files(fi), kernel(pars), QDialog(parent)
{
    QString labelStr;
    labelStr = "Insert a ";
    if (b) labelStr = labelStr.append("complex");
    else labelStr = labelStr.append("real");
    cplx = b;
    labelStr = labelStr.append(" function in the variable <i>x</i> and MACE will plot it");

    plotData = &pars->variableData;

    setWindowTitle("Plot");
    setWindowIcon(QIcon("icons/MaceLogo.png"));

    grid = new QGridLayout;
    vbox = new QVBoxLayout;
    lbox = new QVBoxLayout;
    sBox = new QVBoxLayout;
    cbox = new QHBoxLayout;
    hbox = new QHBoxLayout;
    fBox = new QHBoxLayout;
    mainbox = new QHBoxLayout;
    xbox = new QHBoxLayout;
    ybox = new QHBoxLayout;
    closeBut = new QPushButton("Close");
    helpBut = new QPushButton("Help");
    newBut = new QPushButton("Plot");
    saveBut = new QPushButton("Save");

    xFrame = new QGroupBox("x Axis");
    yFrame = new QGroupBox("y Axis");
    fctnFrame = new QGroupBox("Function");
    sizeFrame = new QGroupBox("Size");

    small = new QRadioButton("small");
    medium = new QRadioButton("medium");
    large = new QRadioButton("large");
    small->setChecked(true);

    errorM = new QErrorMessage;
    errorM->setWindowIcon(QIcon("icons/MaceLogo.png"));
    errorM->setWindowTitle("ERROR");
    errorM->setWindowFlags(errorM->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    info = new QLabel(labelStr);

    f = new QLabel("<font color=\"#0000ff\">f(x)</font> = ");
    g = new QLabel("<font color=\"#ff0000\">g(x)</font> = ");
    h = new QLabel("<font color=\"#00ff00\">h(x)</font> = ");
    i = new QLabel("<font color=\"#ffa500\">i(x)</font> = ");
    j = new QLabel("<font color=\"#800080\">j(x)</font> = ");
    k = new QLabel("<font color=\"#493d26\">k(x)</font> = ");
    l = new QLabel("<font color=\"#00af8f\">l(x)</font> = ");

    fl = new QLineEdit;
    gl = new QLineEdit;
    hl = new QLineEdit;
    il = new QLineEdit;
    jl = new QLineEdit;
    kl = new QLineEdit;
    ll = new QLineEdit;

    pMin = -10.0;
    pMax = 10.0;
    vMin = -10.0;
    vMax = 10.0;

    xSize = 400;
    ySize = 400;

    helpInfo = new QTextEdit;

    helpInfo->setMaximumSize(400,80);
    helpInfo->setReadOnly(true);
    helpInfo->setHidden(true);

    pm = new QPixmap(400,400);
    sPic = new QPixmap(650,420);
    paint = new QPainter(pm);
    sPaint = new QPainter(sPic);
    makeVisible();

    lb = new QLabel;
    lb->setPixmap(*pm);

    if (cplx) {
        cbox->addWidget(f);
        cbox->addWidget(fl);
        fctnFrame->setLayout(cbox);
    }
    else {
        grid->addWidget(f,0,0,1,1);
        grid->addWidget(fl,0,1,1,1);
        grid->addWidget(g,1,0,1,1);
        grid->addWidget(gl,1,1,1,1);
        grid->addWidget(h,2,0,1,1);
        grid->addWidget(hl,2,1,1,1);
        grid->addWidget(i,3,0,1,1);
        grid->addWidget(il,3,1,1,1);
        grid->addWidget(j,4,0,1,1);
        grid->addWidget(jl,4,1,1,1);
        grid->addWidget(k,5,0,1,1);
        grid->addWidget(kl,5,1,1,1);
        grid->addWidget(l,6,0,1,1);
        grid->addWidget(ll,6,1,1,1);
        fctnFrame->setLayout(grid);
    }

    sBox->addWidget(small);
    sBox->addWidget(medium);
    sBox->addWidget(large);
    sizeFrame->setLayout(sBox);

    fBox->addWidget(fctnFrame);
    fBox->addWidget(sizeFrame);

    xto = new QLabel("to");
    xfrom = new QLabel("from");
    yto = new QLabel("to");
    yfrom = new QLabel("from");

    xMin = new QLineEdit("-10.0");
    xMax = new QLineEdit("10.0");
    yMin = new QLineEdit("-10.0");
    yMax = new QLineEdit("10.0");

    xbox->addWidget(xfrom);
    xbox->addWidget(xMin);
    xbox->addWidget(xto);
    xbox->addWidget(xMax);
    xFrame->setLayout(xbox);

    ybox->addWidget(yfrom);
    ybox->addWidget(yMin);
    ybox->addWidget(yto);
    ybox->addWidget(yMax);
    yFrame->setLayout(ybox);

    hbox->addWidget(newBut);
    hbox->addWidget(saveBut);
    hbox->addWidget(helpBut);
    hbox->addWidget(closeBut);

    lbox->addLayout(fBox);
    lbox->addWidget(xFrame);
    lbox->addWidget(yFrame);
    lbox->addWidget(helpInfo);
    lbox->addLayout(hbox);

    //vbox->addWidget(info);

    //vbox->addWidget(lb);
    //vbox->addWidget(glWidget);

    mainbox->addLayout(lbox);
    mainbox->addLayout(vbox);

    setLayout(mainbox);

    DataBase plotData;

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QObject::connect(this->newBut,SIGNAL(clicked()),this,SLOT(replot()));
    QObject::connect(this->closeBut,SIGNAL(clicked()),this,SLOT(finish()));
    QObject::connect(this->saveBut,SIGNAL(clicked()),this,SLOT(save()));
    QObject::connect(this->helpBut,SIGNAL(clicked()),this,SLOT(show_info()));
    QObject::connect(this->small,SIGNAL(clicked()),this,SLOT(smallPlot()));
    QObject::connect(this->medium,SIGNAL(clicked()),this,SLOT(medPlot()));
    QObject::connect(this->large,SIGNAL(clicked()),this,SLOT(largePlot()));

    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

plotDialog::~plotDialog()
{
    delete errorM;
}

void plotDialog::finish() {
    close();
}

int plotDialog::countFctn() {
    int res = 0;

    if (fl->text().size()>0) res++;
    if (gl->text().size()>0) res++;
    if (hl->text().size()>0) res++;
    if (il->text().size()>0) res++;
    if (jl->text().size()>0) res++;
    if (kl->text().size()>0) res++;
    if (ll->text().size()>0) res++;

    return res;
}

void plotDialog::makeVisible(){

    /*std::vector<std::pair<QString,MColor> > function;

    if (fl->text().size()>0) {
        function.push_back(std::pair<QString,MColor>(fl->text(),MColor(0,0,1)));
    }
    if (gl->text().size()>0) {
        function.push_back(std::pair<QString,MColor>(gl->text(),MColor(1,0,0)));
    }
    if (hl->text().size()>0) {
        function.push_back(std::pair<QString,MColor>(hl->text(),MColor(0,1,0)));
    }
    if (il->text().size()>0) {
        function.push_back(std::pair<QString,MColor>(il->text(),MColor(250.0/255.0,165.0/255.0,0)));
    }
    if (fl->text().size()>0) {
        function.push_back(std::pair<QString,MColor>(jl->text(),MColor(128.0/255.0,0,128.0/255.0)));
    }
    if (kl->text().size()>0) {
        function.push_back(std::pair<QString,MColor>(kl->text(),MColor(68.0/255.0,62.0/255.0,38.0/255.0)));
    }
    if (ll->text().size()>0) {
        function.push_back(std::pair<QString,MColor>(ll->text(),MColor(0,175.0/255.0,143.0/255.0)));
    }*/

    if(cplx){
        cplxPlot(memory);
        helpInfo->setHtml(kernel->factory->get_plotInfo("Plot a complex function"));
        update();
    }
    else{
        plotting(memory);
        helpInfo->setHtml(kernel->factory->get_plotInfo("Plot a real function"));
        update();
    }
}

void plotDialog::plot() {
    double hMin, hMax;

    hMin = xMin->text().toDouble();
    hMax = xMax->text().toDouble();

    if (hMin < hMax) {
        pMin = hMin;
        pMax = hMax;

        hMin = yMin->text().toDouble();
        hMax = yMax->text().toDouble();

        if (hMin < hMax) {
            vMin = hMin;
            vMax = hMax;

            makeVisible();
            lb->setPixmap(*pm);
        }
    }
}

void plotDialog::save() {
    if ((fl->text().size() > 0 && cplx) ||
            (fl->text().size() > 0 || gl->text().size() > 0 || hl->text().size() > 0 || il->text().size() > 0 ||
             jl->text().size() > 0 || kl->text().size() > 0 ||  ll->text().size() > 0)) {
        doSave();
    }
}

void plotDialog::doSave() {
    QString fileOpened = files->getSaveFileName(this,tr("Save"),"plot",tr("PNG (*.png)"));
    if(fileOpened != ""){
        QFile file(fileOpened);
        if (file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QColor blub;
            int yDist=ySize;
            QImage logo("icons/MaceLogo.png");
            QRectF rect(xSize+190,10,60,60);
            QString mStr = "MACE 1.4.0", content;
            blub.setRgb(225,245,232);
            sPaint->end();
            *sPic = sPic->scaled(xSize+260,ySize+20);
            sPaint->begin(sPic);
            sPaint->setPen(blub);
            sPaint->fillRect(0,0,xSize+260,ySize+20,blub);
            blub.setRgb(0,140,0);
            sPaint->setPen(blub);
            sPaint->drawText(xSize+192,87,mStr);
            blub.setRgb(0,0,0);
            sPaint->setPen(blub);

            if (ll->text().size() >0) {
                blub.setRgb(0,175,143);
                sPaint->setPen(blub);
                sPaint->drawText(xSize+20,yDist,"l(x)");
                blub.setRgb(0,0,0);
                sPaint->setPen(blub);
                content = ll->text();
                content = content.prepend("= ");
                sPaint->drawText(xSize+45,yDist,content);
                yDist-=20;
            }
            if (kl->text().size() >0) {
                blub.setRgb(68,62,38);
                sPaint->setPen(blub);
                sPaint->drawText(xSize+20,yDist,"k(x)");
                blub.setRgb(0,0,0);
                sPaint->setPen(blub);
                content = kl->text();
                content = content.prepend("= ");
                sPaint->drawText(xSize+45,yDist,content);
                yDist-=20;
            }
            if (jl->text().size() >0) {
                blub.setRgb(128,0,128);
                sPaint->setPen(blub);
                sPaint->drawText(xSize+20,yDist,"j(x)");
                blub.setRgb(0,0,0);
                sPaint->setPen(blub);
                content = jl->text();
                content = content.prepend("= ");
                sPaint->drawText(xSize+45,yDist,content);
                yDist-=20;
            }
            if (il->text().size() >0) {
                blub.setRgb(250,165,0);
                sPaint->setPen(blub);
                sPaint->drawText(xSize+20,yDist,"i(x)");
                blub.setRgb(0,0,0);
                sPaint->setPen(blub);
                content = il->text();
                content = content.prepend("= ");
                sPaint->drawText(xSize+45,yDist,content);
                yDist-=20;
            }
            if (hl->text().size() >0) {
                blub.setRgb(0,255,0);
                sPaint->setPen(blub);
                sPaint->drawText(xSize+20,yDist,"h(x)");
                blub.setRgb(0,0,0);
                sPaint->setPen(blub);
                content = hl->text();
                content = content.prepend("= ");
                sPaint->drawText(xSize+45,yDist,content);
                yDist-=20;
            }
            if (gl->text().size() >0) {
                blub.setRgb(255,0,0);
                sPaint->setPen(blub);
                sPaint->drawText(xSize+20,yDist,"g(x)");
                blub.setRgb(0,0,0);
                sPaint->setPen(blub);
                content = gl->text();
                content = content.prepend("= ");
                sPaint->drawText(xSize+45,yDist,content);
                yDist-=20;
            }
            if (fl->text().size() >0) {
                blub.setRgb(0,0,255);
                sPaint->setPen(blub);
                sPaint->drawText(xSize+20,yDist,"f(x)");
                blub.setRgb(0,0,0);
                sPaint->setPen(blub);
                content = fl->text();
                content = content.prepend("= ");
                sPaint->drawText(xSize+45,yDist,content);
                yDist-=20;
            }
            yDist -= 40;

            if (cplx) content = "imag:";
            else content = "y:";
            content = content.append(" from ");
            content = content.append(yMin->text());
            content = content.append(" to ");
            content = content.append(yMax->text());
            sPaint->drawText(xSize+20,yDist,content);

            yDist -= 20;

            if (cplx) content = "real:";
            else content = "x:";
            content = content.append(" from ");
            content = content.append(xMin->text());
            content = content.append(" to ");
            content = content.append(xMax->text());
            sPaint->drawText(xSize+20,yDist,content);

            sPaint->drawPixmap(10,10,xSize,ySize,*pm,0,0,xSize,ySize);
            sPaint->drawImage(rect,logo);
            sPic->save(fileOpened);
        }
    }
}

void plotDialog::show_info(){
    if(helpInfo->isHidden()){
        helpInfo->setHidden(false);
        layout()->setSizeConstraint(QLayout::SetFixedSize);
    }
    else{
        helpInfo->setHidden(true);
        layout()->setSizeConstraint(QLayout::SetFixedSize);
    }
}

void plotDialog::cplxPlot(QString str){

    const double saturation = 1.0;

    QString labelStr = "";
    bool error = false,b;
    numCplx r, d;
    QColor color;
    double realHelp, imagHelp;
    double hue, lightness;
    double leftLowHue, leftLowLightness, aboveRightHue, aboveRightLightness;

    str =fl->text();
    if (str.size() > 0) {
        QString errorString;
        Function func;
        if (kernel->cplxFuncInterface(str,func,errorString,plotData)) {
            for (int i = 0; i < xSize && !error; i++){
                for (int j = 0; j < ySize && !error; j++){
                    realHelp = (double) i;
                    realHelp = ((pMax - pMin)*realHelp/xSize) + pMin;
                    imagHelp = (double) j;
                    imagHelp = ((vMin - vMax)*imagHelp/ySize) + vMax;
                    d.set(realHelp,imagHelp);
                    d.val = func.eval(d.val,b);
                    r.val = kernel->distC.cplxC.toPolar(d.val);
                    r = kernel->distC.cplxC.polarToSphere(r);

                    hue = r.imag()/(2*PI);
                    if (hue >1.0){
                        hue = 1.0;
                    }
                    if (hue < 0.0){
                        hue = 0.0;
                    }

                    lightness  = r.real()/PI;
                    if (lightness >1.0){
                        lightness = 1.0;
                    }
                    if (lightness < 0.0){
                        lightness = 0.0;
                    }
                    if (i == 190 && j == 10){
                        if (hue > 0.5) aboveRightHue = hue-0.5;
                        else aboveRightHue = hue+0.5;
                        aboveRightLightness = 1.0- lightness;
                    }
                    else if(j == 190 && i == 10){
                        if (hue > 0.5) leftLowHue = hue-0.5;
                        else leftLowHue = hue+0.5;
                        leftLowLightness = 1.0- lightness;
                    }
                    color.setHslF(hue, saturation, lightness);

                    paint->fillRect(i,j,1,1,color);
                }
            }
        }
        else errorM->showMessage(errorString);
        labelStr = fl->text();
        insertSpec(labelStr);
        labelStr = labelStr.prepend("f(x) = <font color=\"#0000ff\">");
        labelStr = labelStr.append("</font>");
    }
    if (labelStr.size() ==0 ) labelStr = "Insert a complex function in the variable <i>x</i> and MACE will plot it";
    info->setText(labelStr);
}

void plotDialog::plotting(QString str){
    QString labelStr = "", errMsg;
    double  res, help, xDist, xForm;
    int j, k, xFormI, count, fctnNr = 0;
    QColor blub;

    paint->fillRect(0,0,(int) xSize,(int) ySize,Qt::white);

    blub.setRgb(0,0,0);
    paint->setPen(blub);

    if (0.0 < vMax && 0.0 > vMin) {
        res = - (vMax*ySize/(vMin - vMax));
        j = (int) res;
        paint->drawLine(0,j,(int) xSize,j);
        xDist = pMax - pMin;
        xForm = log(xDist)/log(10.0);
        if (xForm < 0.0) xForm -= 1.0;
        xFormI = (int) xForm;
        xFormI--;
        xForm = (double) xFormI;
        if (xForm > 0.0) xForm = pow(10,xForm);
        else xForm = 1.0/(pow(10,-xForm));
        help = 0.0;
        count = 0;
        while (help < pMax) {
            help += xForm;
            count++;
            res = xSize - (help*xSize/(pMin - pMax)) + (pMax*xSize/(pMin - pMax));
            k = (int) res;
            if (count % 5 != 0) paint->drawLine(k,j,k,j+6);
            else if (count % 10 != 0) paint->drawLine(k,j,k,j+9);
            else paint->drawLine(k,j,k,j+12);
        }
        help = 0.0;
        count = 0;
        while (help > pMin) {
            help -= xForm;
            count++;
            res = xSize - (help*xSize/(pMin - pMax)) + (pMax*xSize/(pMin - pMax));
            k = (int) res;
            if (count % 5 != 0) paint->drawLine(k,j,k,j+6);
            else if (count % 10 != 0) paint->drawLine(k,j,k,j+9);
            else paint->drawLine(k,j,k,j+12);
        }
    }
    if (0.0 < pMax && 0.0 > pMin) {
        res = xSize + (pMax*xSize/(pMin - pMax));
        j = (int) res;
        paint->drawLine(j,0,j,(int) ySize);
        xDist = vMax - vMin;
        xForm = log(xDist)/log(10.0);
        if (xForm < 0.0) xForm -= 1.0;
        xFormI = (int) xForm;
        xFormI--;
        xForm = (double) xFormI;
        if (xForm > 0.0) xForm = pow(10,xForm);
        else xForm = 1.0/(pow(10,-xForm));
        help = 0.0;
        count = 0;
        while (help < vMax) {
            help += xForm;
            count++;
            res = (help*ySize/(vMin - vMax)) - (vMax*ySize/(vMin - vMax));
            k = (int) res;
            if (count % 5 != 0) paint->drawLine(j,k,j-6,k);
            else if (count % 10 != 0) paint->drawLine(j,k,j-9,k);
            else paint->drawLine(j,k,j-12,k);
        }
        help = 0.0;
        count = 0;
        while (help > vMin) {
            help -= xForm;
            count++;
            res = (help*ySize/(vMin - vMax)) - (vMax*ySize/(vMin - vMax));
            k = (int) res;
            if (count % 5 != 0) paint->drawLine(j,k,j-6,k);
            else if (count % 10 != 0) paint->drawLine(j,k,j-9,k);
            else paint->drawLine(j,k,j-12,k);
        }
    }

    labelStr = "";
    if (fl->text().size() >0) {
        if (labelStr.size() > 0) labelStr = labelStr.append(", ");
        labelStr = labelStr.append("<font color=\"#0000ff\">f(x)</font>");
        blub.setRgb(0,0,255);
        paint->setPen(blub);
        fctnNr++;
        drawFctn(fl->text(), errMsg, "#0000ff");
    }
    if (gl->text().size() >0) {
        if (labelStr.size() > 0) labelStr = labelStr.append(", ");
        labelStr = labelStr.append("<font color=\"#ff0000\">g(x)</font>");
        blub.setRgb(255,0,0);
        paint->setPen(blub);
        fctnNr++;
        drawFctn(gl->text(), errMsg, "#ff0000");
    }
    if (hl->text().size() >0) {
        if (labelStr.size() > 0) labelStr = labelStr.append(", ");
        labelStr = labelStr.append("<font color=\"#00ff00\">h(x)</font>");
        blub.setRgb(0,255,0);
        paint->setPen(blub);
        fctnNr++;
        drawFctn(hl->text(), errMsg, "#00ff00");
    }
    if (il->text().size() >0) {
        if (labelStr.size() > 0) labelStr = labelStr.append(", ");
        labelStr = labelStr.append("<font color=\"#ffa500\">i(x)</font>");
        blub.setRgb(250,165,0);
        paint->setPen(blub);
        fctnNr++;
        drawFctn(il->text(), errMsg, "#ffa500");
    }
    if (jl->text().size() >0) {
        if (labelStr.size() > 0) labelStr = labelStr.append(", ");
        labelStr = labelStr.append("<font color=\"#800080\">j(x)</font>");
        blub.setRgb(128,0,128);
        fctnNr++;
        paint->setPen(blub);
        drawFctn(jl->text(), errMsg, "#800080");
    }
    if (kl->text().size() >0) {
        if (labelStr.size() > 0) labelStr = labelStr.append(", ");
        labelStr = labelStr.append("<font color=\"#493d26\">k(x)<font>");
        blub.setRgb(68,62,38);
        fctnNr++;
        paint->setPen(blub);
        drawFctn(kl->text(), errMsg,"#493d26" );
    }
    if (ll->text().size() >0) {
        if (labelStr.size() > 0) labelStr = labelStr.append(", ");
        labelStr = labelStr.append("<font color=\"#00af8f\">l(x)</font>");
        blub.setRgb(0,175,143);
        paint->setPen(blub);
        fctnNr++;
        drawFctn(ll->text(), errMsg, "#00af8f");
    }
    if (labelStr.size() ==0 ) labelStr = "Insert a real function in the variable x and MACE will plot it";
    info->setText(labelStr);
    if (errMsg.size()>0) errorM->showMessage(errMsg);
}

void plotDialog::writeErrMsg(QString &ErrMsg, const QString color) {
    QString help;

    ErrMsg = ErrMsg.append("<font color=\"");
    ErrMsg = ErrMsg.append(color);
    ErrMsg = ErrMsg.append("\">");
    kernel->validC->getErrMsg(help);
    ErrMsg = ErrMsg.append(help);
    ErrMsg = ErrMsg.append("<font><br>");
}

void plotDialog::drawFctn(QString str,QString &ErrMsg, const QString color) {
    std::string eStr;
    double real, res;
    int j, k, last;
    numCplx r;
    numReal nr;
    int mi;
    errorType errT;
    bool error = false, e, hasPlot = false;
    bool discrete = false;
    bool errorBefore = false;

    for (int i = 0; i <xSize; i++){
        real = (double) i;
        real = ((pMax - pMin)*real/xSize) + pMin;

        nr.set(real);
        r.set(kernel->rFctnInterface(&error, &discrete, str, &nr, plotData),0);

        if (discrete) break;
        if(!error && r.norm() <999999){
            hasPlot = true;
            res = r.real();
            res = (res*ySize/(vMin - vMax)) - (vMax*ySize/(vMin - vMax));
            j = (int) res;
            if (i>0 && !errorBefore){
                k = i-1;
                paint->drawLine(k,last,i,j);
            }
            last = j;
            errorBefore = false;
        }
        else {
            errorBefore = true;
            kernel->validC->eval(e,errT,eStr);
            if (errT != ERRINFCTN && errT !=ERRDIST && errT !=ERRFUNCDIST && errT != DONTGETREAL
                    && errT !=ERRPROPDIST && errT != NOERR && errT != DIVBYZERO) {
                hasPlot = true;
                writeErrMsg(ErrMsg,color);
                break;
            }
        }
    }
    kernel->validC->eval(e,errT,eStr);
    if (errT == ERRDIST || errT == NOTIR || errT == POWERR) {
        discrete = true;
        ErrMsg.clear();
    }
    if (discrete) {
        hasPlot = false;
        int iMax = (int) pMax, iMin = (int) pMin;
        real = -ySize*vMax/(vMin-vMax);
        last = (int) real;
        for (int i = iMin; i <= iMax; i++) {
            real = (double) i;
            res = xSize*real/(pMax-pMin)-xSize*pMin/(pMax-pMin);
            k = (int) res;
            mi=i;
            //r.set(kernel->rFctnInterface(&error, &discrete, str, &mi),0);
            if (!error) {
                hasPlot = true;
                real = r.real();
                res = (real*ySize/(vMin - vMax)) - (vMax*ySize/(vMin - vMax));
                j = (int) res;
                if (j == last) j++;
                paint->drawLine(k,last,k,j);
            }
            else {
                kernel->validC->eval(e,errT,eStr);
                if (errT != ERRINFCTN && errT != ERRDIST && errT !=ERRFUNCDIST
                 && errT !=ERRPROPDIST && errT != INTTOLARGE && errT != DIVBYZERO
                 && errT != NOTINT && errT != INTNEG  && errT != SINTTOLARGE) {
                    hasPlot = true;
                    writeErrMsg(ErrMsg,color);
                    break;
                }
            }
        }
    }
    if (!hasPlot) writeErrMsg(ErrMsg,color);
}

void plotDialog::replot(DataBase *Data) {

    int intX = (int) xSize;
    int intY = (int) ySize;

    if (Data != 0) {
        plotData=Data;
    }

    paint->end();
    *pm = pm->scaled(intX,intY);
    lb->setPixmap(*pm);
    paint->begin(pm);
    plot();
}

void plotDialog::smallPlot() {
    xSize = 400;
    ySize = 400;

    paint->end();
    helpInfo->setMaximumHeight(80);
    *pm = pm->scaled(400,400);
    lb->setPixmap(*pm);
    paint->begin(pm);
    plot();
}

void plotDialog::medPlot() {
    xSize = 500;
    ySize = 500;
    paint->end();
    helpInfo->setMaximumHeight(160);
    *pm = pm->scaled(500,500);
    lb->setPixmap(*pm);
    paint->begin(pm);
    plot();
}

void plotDialog::largePlot() {
    xSize = 800;
    ySize = 600;
    paint->end();
    helpInfo->setMaximumHeight(245);
    *pm = pm->scaled(800,600);
    lb->setPixmap(*pm);
    paint->begin(pm);
    plot();
}



