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

#include "macetextedit.h"
#define MACEBLUE = "#0000A8"

//characteristics:
void Zero::color(QString *str){
    *str = str->prepend("<font color=\"#0000A8\">");
    *str = str->append("</font>");
}

void Positive::color(QString *str){
    *str = str->prepend("<font color=\"red\">");
    *str = str->append("</font>");
}

//in/out states:

void IOstate::write(QString *text, QString str, QTextEdit *e, QScrollBar *bar, Formats newForm){

    format(text, str, newForm);

    insert(text, str, e, newForm);

    stuff(str, e, bar, newForm);
}

In::In(){
    curForm = NO;
    inputPos = -1;
}

void In::format(QString *text, QString str, Formats newForm){

    if (!(newForm == MATRIX || newForm == RESTOREMAT)) {
        insertSpec(str);
    }
    removeLastInput(*text);
    *text = text->append(str);
}

void In::insert(QString *text, QString str, QTextEdit *e, Formats newForm){
    e->setHtml(*text);
}

void In::stuff(QString str, QTextEdit *e, QScrollBar *bar, Formats newForm){

    bar->setValue(bar->maximum());

    curForm = newForm;

    if (curForm == REPLACE) {
        curForm = SCALAR;
    }
}

bool In::scalarInput(){
    return (curForm == SCALAR);
}

bool In::matrixInput(){
    return (curForm == MATRIX || curForm == RESTOREMAT);
}

void In::left(QTextEdit *e){
    if (curForm == SCALAR && cursorPos < inputSize){
        QTextCursor cursor(e->textCursor());
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor);
        e->setTextCursor(cursor);
        cursorPos++;
    }
}

void In::right(QTextEdit *e){
    if (curForm == SCALAR && cursorPos > 0){
        QTextCursor cursor(e->textCursor());
        cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor);
        e->setTextCursor(cursor);
        cursorPos--;
    }
}

QString In::getStr(QString *text){
    int begin, end;

    if (high){
        if (inputPos <= 0) inputPos = text->lastIndexOf("Input:");
        end = text->lastIndexOf("<!--I",inputPos)+10;
        inputPos = text->lastIndexOf("Input:",inputPos-1);
    }
    else{
        inputPos = text->indexOf("Input:",inputPos+1);
        if (inputPos == text->lastIndexOf("Input:")) inputPos = 0;
        end = text->indexOf("<!--I",inputPos)+10;

    }

    begin = inputPos+7;
    end -=begin;
    QString str = text->mid(begin,end);
    QString help = str.right(10);
    str.chop(10);

    if (help == "<!--ISC-->") restore = SCALAR;
    else if (help == "<!--IMA-->"){
        restore = MATRIX;
        begin = str.indexOf("<!--")+4;
        end = str.indexOf("-->");
        end -= begin;
        str = str.mid(begin,end);
    }
    else if (help == "<!--INO-->") restore = NO;

    return str;
}

bool In::up(QString *text, QString *memory, QTextEdit *e, QScrollBar *bar){
    bool res = false;

    QString str;
    int counter = 0;
    do {
        if (inputPos <= 0) counter++;
        str = getStr(text);
    } while (restore == NO && counter < 2);

    if (restore == SCALAR) {
        QString empty;
        empty.clear();
        removeSpec(str);
        *memory = str;
        this->write(text,empty,e,bar,REPLACE);
    }
    else if (restore == MATRIX){
        res = true;
        MatMem = str;

    }
    return res;
}

void In::giveComment(QString *text){
    if(curForm == SCALAR) *text = text->append("<!--ISC-->");
    else if(curForm == MATRIX) *text = text->append("<!--IMA-->");
    else if(curForm == NO) *text = text->append("<!--INO-->");
}

QString In::matStr(){
    return MatMem;
}

Out::Out()
{
   charac = new Zero;
}

Out::~Out(){
    delete charac;
}

void Out::setChar(/*MaceInt characteristic*/){
    Characteristic *newChar;
    /*if(characteristic.larger(0)) newChar = new Positive;
    else*/ newChar = new Zero;
    delete charac;
    charac = 0;
    charac = newChar;
}

void Out::format(QString *text, QString str, Formats newForm){
    charac->color(&str);

    in->giveComment(text);

    if(newForm == SCALAR){
        str = str.prepend("<br> = ");
    }
    else if(newForm == MATRIX){
        QString text = "<table><tr><th><table><tr><th>";
        for (int i= 0; i < (lines)/2; i++){
            text = text.append("</th></tr><tr><th>");
        }
        text = text.append("<span style=\"font-weight:200\">");
        text = text.append(" = ");
        text = text.append("</span>");
        text = text.append("</th></tr>");
        text = text.append("</table></th><th>");
        text = text.append(str);
        text = text.append("</th></tr></table>");
        str = text;
    }
    str = str.append("<br><br>Input: ");
    *text = text->append(str);

    curForm = newForm;
}

void Out::insert(QString *text, QString str, QTextEdit *e, Formats newForm){
    e->setHtml(*text);
}

void Out::stuff(QString str, QTextEdit *e, QScrollBar *bar, Formats newForm){
    bar->setValue(bar->maximum());
}

bool Out::scalarInput(){
    return false;
}

bool Out::matrixInput(){
    return false;
}


void Out::left(QTextEdit *e){
    ;
}

void Out::right(QTextEdit *e){
    ;
}

bool Out::up(QString *text, QString *memory, QTextEdit *e, QScrollBar *bar){
    return false;
}

QString Out::matStr(){
    return "";
}

//main class:
MaceTextEdit::MaceTextEdit(QTextEdit *parent) :
    QTextEdit(parent)
{
    scrollbar = this->verticalScrollBar();
    this->setReadOnly(true);

    setContextMenuPolicy(Qt::NoContextMenu);

    changed = false;
    usesPrevResult = false;

    text = "Input: ";
    help = "";
    insertHtml("Input: ");

    charac = new Zero;

    out.in = &in;

    inOut = &in;
}

MaceTextEdit::~MaceTextEdit()
{

}

void MaceTextEdit::mySetCursor() {
    QTextCursor cursor(this->textCursor());
    cursor.position();
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    this->setTextCursor(cursor);
}

void MaceTextEdit::callWrite(QString str, Formats newForm){
    if (newForm != RESTOREMAT) in.inputPos = -1;
    changed = true;
    inOut->write(&text,str,this,scrollbar,newForm);
}

void MaceTextEdit::stuff(){

    scrollbar->setValue(scrollbar->maximum());

    QTextCursor cursor(this->textCursor());
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    this->setTextCursor(cursor);

    inOut = &out;
}

void MaceTextEdit::zeroWrite(QString str){
    if (inOut != &in) inOut = &in;
    callWrite(str, NO);
}

void MaceTextEdit::standardWrite(QString str){
    if (inOut != &in) inOut = &in;
    callWrite(str, SCALAR);
}

void MaceTextEdit::reset(){
    text.clear();
    result.clear();

    text = "Input: ";

    this->clear();
    insertHtml("Input: ");

    in.curForm = NO;
    out.curForm = NO;
    inOut = &in;
}

void MaceTextEdit::left(){
    inOut->left(this);
}

void MaceTextEdit::right(){
    inOut->right(this);
}

void MaceTextEdit::up(bool b){
    inOut = &in;
    in.high = b;
    QString memory;
    if (inOut->up(&text, &memory, this, scrollbar)){
        emit pleaseMatrix(in.matStr());
    } else {
        inputText(memory);
    }
}

void MaceTextEdit::displayResult(QString str){
    inOut = &out;
    powerCorrect(str);
    result = str;
    callWrite(str, SCALAR);
}

void MaceTextEdit::displaySLEResult(QString str){
    inOut = &out;
    result = "0";
    callWrite(str, NO);
}

void MaceTextEdit::load(QString str){
    int startIndx, endIndx;
    reset();
    text = str;
    setHtml(text);
    stuff();
    inOut = &out;
    if (text.lastIndexOf("<!--ISC-->") < text.lastIndexOf("<!--INO-->") && text.lastIndexOf("<!--IMA-->") < text.lastIndexOf("<!--INO-->"))
        out.curForm = NO;
    else if (text.lastIndexOf("<!--ISC-->") < text.lastIndexOf("<!--IMA-->") && text.lastIndexOf("<!--IMA-->") < text.lastIndexOf("<!--")) {
        out.curForm = MATRIX;
        startIndx = str.lastIndexOf("<!--")+4;
        endIndx = str.lastIndexOf("-->");
        endIndx -= startIndx;
        result = str.mid(startIndx,endIndx);
        storeMatrix(result);
    }
    else {
        out.curForm = SCALAR;

    }
    startIndx=text.lastIndexOf("<font color=\"#")+22;
    endIndx = text.lastIndexOf("</font>")-startIndx;
    result=text.mid(startIndx,endIndx);
}

void MaceTextEdit::displayMatrixResult(QString str, int lines){
    result = str;
    out.lines = lines;
    inOut = &out;
    callWrite(str,MATRIX);
}

bool MaceTextEdit::matrixInput(){
    return inOut->matrixInput();
}

void MaceTextEdit::singleMatrix(QString str){
    inOut = &in;
    callWrite(str,MATRIX);
}

void MaceTextEdit::restoreMatrix(QString str){
    inOut = &in;
    callWrite(str,RESTOREMAT);
}

bool MaceTextEdit::getSingMatrix(){
    return singMatrix;
}

void MaceTextEdit::charWrite(QString str){
    zeroWrite("Characteristic");
    displayResult(str);
}

QString MaceTextEdit::getLastResult(){
    if (out.curForm == MATRIX){
        singleMatrix(result);
    }
    if (out.curForm != SCALAR) result.clear();
    return result;
}

QString MaceTextEdit::getText(){
    return text;
}

//void MaceTextEdit::setChar(/*MaceInt characteristic){
    //out.setChar(/*characteristic*/);
//}
