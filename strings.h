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

#ifndef STRINGS_H
#define STRINGS_H
#include <QString>


QString hints(){
    QString res = ("<h4>Data types</h4> MACE computes with double, (double, double) complex numbers and rest classes in <b>Z</b>/(n). ");
    res = res.append("For several functions MACE calculates with arbitrary precision integers, rational numbers and elements of ");
    res = res.append("<b>Q</b>(i), if arbitrary precision is needed. Moreover polynomials and matrices over <b>Z</b>/(n), ");
    res = res.append("(double, double) complex numbers and arbitrary precision <b>Q</b>(i) are implemented.<br>");

    res = res.append("<h4>Arithmetic Operations</h4>By using brackets, it is possible to ");
    res = res.append("compose several arithmetic operations.<br>");

    res = res.append("<h4>Powers</h4> For two real numbers a and b one can compute the power a^b by entering it. ");
    res = res.append("For all other types of data only the power by a positive integer is implemented.<br>");

    res = res.append("<h4>Matrices and Linear Equations</h4> First choose the number of columns and lines and then press ");
    res = res.append("the \"write matrix\" button or the button of another function for matrices of your choice. For the addition, ");
    res = res.append("subtraction and multiplication of matrices you find seperate buttons in the \"Linear Algebra\" section. ");
    res = res.append("If you like to solve a system of linear equations given by Ax = b for a matrix A and a vector b, first choose the ");
    res = res.append("lines and columns for A and press the \"linear equation\" button then.<br>");

    res = res.append("<h4>Polynomials</h4> Polynomials can be entered in the form \"a_nx^n+...+a_1x+a_0\". In characteristic n>0 the ");
    res = res.append("polynomials are defined over <b>Z</b>/(n) and in characteristic 0 polynomials can have complex coefficients.<br>");

    return res;
}

QString lic(){
    QString res = ("MACE is free software; you can redistribute it and/or modify ");
    res = res.append("it under the terms of the GNU Lesser General Public License as published by ");
    res = res.append(" the Free Software Foundation; either version 3 of the License, or ");
    res = res.append("(at your option) any later version. ");
    res = res.append("<br><br>");
    res = res.append("MACE is distributed in the hope that it will be useful, ");
    res = res.append("but WITHOUT ANY WARRANTY; without even the implied warranty of ");
    res = res.append("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the ");
    res = res.append("GNU Lesser General Public License for more details. ");
    res = res.append("<br><br>");
    res = res.append("You should have received a copy of the GNU Lesser General Public License ");
    res = res.append("along with MACE; if not, see http://www.gnu.org/licenses/. ");

    return res;
}
#endif // STRINGS_H


QString auth(){
    QString res = "<h2>MACE 1.0</h2>";
    res = res.append("<br>");
    res = res.append("&copy; 2012 Jan Christian Rohde <a href=\"mailto:jan-christian.rohde@gmx.de\">jan-christian.rohde@gmx.de</a>");
    res = res.append("<br><br>");
    res = res.append("License: GNU Lesser General Public License 3");
    return res;
}
