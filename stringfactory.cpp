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

#include "stringfactory.h"
#include "math/kernel/reader.h"

stringFactory::stringFactory()
{
    fctnData a;
    QString help, strHelp;

    QList<int> helpList;

    analFunctions aFctns;
    complexFunctions cFctns;
    arithmetics arith;
    combinatorics combi;
    linearAlgebra linA;
    logics logic;
    calculus calcu;
    controlFctn contF;

    infos = infos.unite(aFctns.get_map());
    infos = infos.unite(cFctns.get_map());
    infos = infos.unite(arith.get_map());
    infos = infos.unite(combi.get_map());
    infos = infos.unite(linA.get_map());
    infos = infos.unite(logic.get_map());
    infos = infos.unite(contF.get_map());
    infos = infos.unite(calcu.get_map());

    a.name = "Characteristics";
    a.code = 10;
    a.variables = 1;
    strHelp = "In Characteristic <i>0</i> all functions of MACE compute with integers, real numbers, complex numbers,";
    strHelp = strHelp.append(" polynomial over complex numbers and matrices with complex numbers as entries. ");
    strHelp = strHelp.append("For <span class=\"nowrap\"><i>n > 0</i></span> all arithmetic operations entered by the keyboard ");
    strHelp = strHelp.append("will by done in residue classes of integers modulo n. The only exception is the power.<br>");
    strHelp = strHelp.append("Moreover for <span class=\"nowrap\"><i>n > 0</i></span> all polynomials have coefficients ");
    strHelp = strHelp.append("and all matrices have entries given by residue classes of integers modulo <i>n</i>.<br>");
    strHelp = strHelp.append("There is a brief introduction to <a href =\"residues\">integral residue classes</a>.<br>");
    strHelp = strHelp.append("If you have selected a characteristic <span class=\"nowrap\"><i>n > 0</i></span>, there will be ");
    strHelp = strHelp.append("a quick primality test for <i>n</i>.<br>");
    strHelp = strHelp.append("If <i>n</i> is neither <i>0</i> nor a prime number, several functions are blocked. This is due the intractable ");
    strHelp = strHelp.append("arithmetics of the integral residue classes modulo <i>n</i> in the case that <i>n</i> is not a prime number.<br>");
    strHelp = strHelp.append("If you enter an integer for an Arithmetic Function, the result will be returned as residue class modulo <i>n</i> ");
    strHelp = strHelp.append("and your entry will interpreted as an integral residue class. ");
    strHelp = strHelp.append("Moreover in characteristic <i>n>0</i> all Analysis Functions, almost all Complex Functions and all Statistical Distributions are blocked,");
    strHelp = strHelp.append("since these functions are not defined in positive characteristics.");

    a.help = strHelp;
    settingInfo.insert("Characteristics",a);

    a.name = "Precision";
    a.code = 40;
    a.variables = 1;
    a.help = "You can choose the precision of the displayed real / complex numbers from 2 to 16. In general the coefficients of a polynomial have the same precision as ";
    a.help = a.help.append("the selected one. The selected precision does not have any effect to the internal computations, but only for the representation of the result. ");
    a.help = a.help.append("The entries of matrices are displayed with precision 6 independent of the selected one. Moreover the selected precision does not have any ");
    a.help = a.help.append("effect to arbitrary precision integers and integral residue classes.");
    settingInfo.insert("Precision",a);

    a.name = "Rows and Columns of Matrices";
    a.code = 20;
    a.variables = 2;
    a.help = "Here you can choose the number of rows and columns of matrices you like to use.";
    settingInfo.insert("Rows and Columns of Matrices",a);

    help = "<br><br>You have the opportunity to choose between three possible sizes of the image of the plotter: small, medium, large<br>";
    help = help.append("In addition you can choose the shown ranges in X and Y direction. By clicking the button \"Save\", you may save your plot in a png file, which contains also all information about your stored picture.");

    strHelp = "Insert a real function in the variable <i>x</i> and MACE will plot it.<br>You may also plot discrete functions. For example plot the Euler totient function <center><i>f(x) = </i>phi<i>(x)</i>.</center><br>";
    strHelp = strHelp.append("You can plot 7 real or discrete functions at the same time.<br>");
    strHelp = strHelp.append("You may also plot functions of statistical distributions or functions defined by using properties of varying statistical distributions. In addition you can use stored variables.<br>");
    strHelp = strHelp.append("For example use the binomial distribution. To use this distribution enter the the first three letters of its name and \"d\": bind. First insert <center>bdist=bind(20,0.3)</center> into the Input Editor and press enter. Now open Plot->Plot a real function and insert for f(x)");
    strHelp = strHelp.append("<center>20*pdf(bdist,x+10).</center> This is 20 times the probability mass function (pdf) of the binomial distribution (bind) for a series of 20 experiments with the success probability 0.3.<br>");
    strHelp = strHelp.append(" Moreover you can also plot the variation of skewness, if you let the probability of success vary in the case of the binomial distribution for 20 experiments. Plot <center>f(x) = skew(bind(20,x)).</center>");
    strHelp = strHelp.append(help);
    plotInfo.insert("Plot a real function",strHelp);

    strHelp = "Insert a complex function in the variable <i>x</i> and MACE will plot it by using a 2D color map. White means <i>0</i>, ";
    strHelp = strHelp.append("red a positive real number, cyan a negative real number, yellow-green a ");
    strHelp = strHelp.append("positive imaginary part and blue-purple a negative imaginary part. ");
    strHelp = strHelp.append("In general light colors mean numbers with a small absolute value and dark colors mean numbers");
    strHelp = strHelp.append(" with a large absolute value.<br>You may plot <i>f(x) = x</i> to get a first idea.<br>");
    strHelp = strHelp.append("For performance the parser of the plotter for complex functions has a restricted grammar. This grammar uses only the functions in the Complex Functions section, all boolean and comparision operators in the Logical ");
    strHelp = strHelp.append("Operations section except of the assignment operator and the arithmetic operations ^, *, /, +, - and unary -. Stored Variables can not be used for the complex plotter.");
    strHelp = strHelp.append(help);
    plotInfo.insert("Plot a complex function",strHelp);

    helpList.append(100);
    helpList.append(111);
    helpList.append(150);
    helpList.append(153);
    dataTypes.insert("integral residue classes",helpList);
    helpList.clear();

    helpList.append(100);
    helpList.append(110);
    helpList.append(111);
    helpList.append(150);
    helpList.append(153);
    dataTypes.insert("numerical complex(double, double)",helpList);
    helpList.clear();

    helpList.append(100);
    helpList.append(125);
    helpList.append(126);
    helpList.append(127);
    helpList.append(150);
    helpList.append(153);
    dataTypes.insert("polynomials with coefficients given by integral residue classes",helpList);
    helpList.clear();

    helpList.append(100);
    helpList.append(126);
    helpList.append(150);
    helpList.append(153);
    dataTypes.insert("polynomials with complex(double,double) coefficients",helpList);
    helpList.clear();

    helpList.append(125);
    helpList.append(127);
    helpList.append(150);
    helpList.append(153);
    dataTypes.insert("polynomials with arbitrary precision complex coefficients",helpList);
    helpList.clear();

    helpList.append(140);
    helpList.append(141);
    helpList.append(142);
    helpList.append(143);
    helpList.append(144);
    helpList.append(145);
    helpList.append(146);
    dataTypes.insert("matrices with entries given by integral residue classes",helpList);
    helpList.clear();

    helpList.append(140);
    helpList.append(141);
    helpList.append(142);
    helpList.append(143);
    helpList.append(144);
    helpList.append(145);
    helpList.append(146);
    helpList.append(147);
    dataTypes.insert("matrices with arbitrary precision complex coefficients",helpList);
    helpList.clear();

    helpList.append(121);
    helpList.append(130);
    helpList.append(125);
    helpList.append(126);
    helpList.append(127);
    helpList.append(150);
    helpList.append(153);
    dataTypes.insert("arbitrary precision integers",helpList);
    helpList.clear();

    helpList.append(122);
    helpList.append(128);
    helpList.append(160);
    helpList.append(150);
    helpList.append(153);
    dataTypes.insert("double precision real numbers",helpList);
    helpList.clear();

    helpList.append(151);
    helpList.append(152);
    dataTypes.insert("booleans",helpList);
    helpList.clear();

    dataTypes.insert("complex functions",helpList);
    helpList.clear();

    dataTypes.insert("strings",helpList);
    helpList.clear();

    typenotes.insert(110, "Complex Functions");
    typenotes.insert(121, "Arithmetics");
    typenotes.insert(122, "Arithmetics");
    typenotes.insert(125, "Arithmetics");
    typenotes.insert(126, "Arithmetics");
    typenotes.insert(128, "Arithmetics");
    typenotes.insert(130, "Combinatorics");
    typenotes.insert(131, "Statistical Distributions");
    typenotes.insert(140, "Linear Algebra");
    typenotes.insert(148, "Linear Algebra");
    typenotes.insert(150, "Logic");
    typenotes.insert(151, "Logic");
    typenotes.insert(152, "Logic");
    typenotes.insert(153, "Logic");
    typenotes.insert(154, "Logic");
    typenotes.insert(155, "Command");
    typenotes.insert(160, "Analysis");
    typenotes.insert(170, "Differential Calculus");
    typenotes.insert(171, "Differential Calculus");
    typenotes.insert(172, "Differential Calculus");
    typenotes.insert(173, "Differential Calculus");
    typenotes.insert(174, "Differential Calculus");
    typenotes.insert(175, "Differential Calculus");
    typenotes.insert(200, "Scripts");


    funcTypes.insert(110, "This function is defined for complex numbers. Thus you may also insert complex numbers.");
    strHelp = "This function is defined for integers or polynomials. Polynomials may have complex coefficients. Thus you may also insert complex numbers as coefficients. ";
    strHelp = strHelp.append("If you have selected a positive ");
    strHelp = strHelp.append("characteristic <i>n</i>, the polynomials have residue classes modulo <i>n</i> as coefficients. ");
    funcTypes.insert(125, strHelp);
    funcTypes.insert(126, strHelp);
    funcTypes.insert(127, strHelp);
    strHelp = "In characteristic 0 this function is defined for (double) real numbers in general. If you choose a positive characteristic or call it for an argument of a function for arbitrary precision integers,";
    strHelp = strHelp.append(" the version for arbitrary precision integers is used");
    funcTypes.insert(128, strHelp);
    funcTypes.insert(122, "In the current release this function is defined for real numbers.");
    funcTypes.insert(130, "This function is defined for positive integers.");
    funcTypes.insert(121, "This function is defined for positive integers.");
    strHelp = "Matrices can have complex numbers as entries. Thus you may also insert complex numbers as entries. ";
    strHelp = strHelp.append("If you have selected a positive characteristic <i>n>0</i>, the matrices have residue classes ");
    strHelp = strHelp.append("modulo <i>n</i> as entries.");
    funcTypes.insert(140, strHelp);
    funcTypes.insert(141, strHelp);
    funcTypes.insert(142, strHelp);
    funcTypes.insert(144, strHelp);
    funcTypes.insert(145, strHelp);
    funcTypes.insert(146, strHelp);
    funcTypes.insert(148, strHelp);
    strHelp = "Matrices can have complex numbers as entries. Thus you may also insert complex numbers as entries. ";
    funcTypes.insert(147, strHelp);
    strHelp = "The operator must have booleans as arguments. Integers are interpreted as booleans (false = 0, true = all other integers).";
    funcTypes.insert(152, strHelp);
    strHelp = "Integers and real numbers are compared by their size. Complex numbers are compared by their norm. Polynomials are compared by their degree. Integral residue classes modulo <i>N</i> are compared by their respective members <i>n</i> with <i>0&lt;=n&lt;N</i>.";
    funcTypes.insert(153, strHelp);
    funcTypes.insert(160, "In the current release this function is defined for real numbers.");
    funcTypes.insert(21, strHelp);
    funcTypes.insert(22, strHelp);
    funcTypes.insert(23, strHelp);
    funcTypes.insert(24, strHelp);
    strHelp = "Systems of linear equations can also be solved for complex numbers. Thus you may also insert complex numbers. ";
    strHelp = strHelp.append("If you have selected a positive characteristic <i>n>0</i>, the system of equations will be solved for ");
    strHelp = strHelp.append("integral residue classes modulo <i>n</i>.");
    funcTypes.insert(143, strHelp);
    strHelp = "For a statistical distribution the following functions are implemented: <ul type=\"bullet\"><li>";
    strHelp = strHelp.append("The Probability Density Function (pdf), which is called Probability Mass Function ");
    strHelp = strHelp.append("in the case of a discrete distribution. In the case of a discrete distribution it returns the probability that the variable has the value <i>x</i>. ");
    strHelp = strHelp.append("In the continuous case the probability that a variable is contained in a measurable set can be computed by the integral of the pdf over this set.");
    strHelp = strHelp.append("</li><li>");
    strHelp = strHelp.append("The Cumulative Distribution Function (cdf). It assigns to <i>x</i> the probability that the variable is less or equal <i>x</i>.");
    strHelp = strHelp.append("</li><li>");
    strHelp = strHelp.append("The Hazard Function (haz). It is defined by");
    strHelp = strHelp.append("<center>haz(x) = pdf(x)/(1-cdf(x)).</center><br>");
    strHelp = strHelp.append("</li></ul>");
    strHelp = strHelp.append("Moreover the following properties of Statistical Distributions are implemented:<ul type=\"bullet\"><li>");
    strHelp = strHelp.append("The Mean or expected Value is the average of all values of a distribution weighted with respect to their respective probabilities.");
    strHelp = strHelp.append("</li><li>");
    strHelp = strHelp.append("The Median separates the lower half and the higher half of the distribution.");
    strHelp = strHelp.append("</li><li>");
    strHelp = strHelp.append("The Mode is the value that appears most often.");
    strHelp = strHelp.append("</li><li>");
    strHelp = strHelp.append("The Skewness is a measure of the asymmetry of the Statistical Distribution.");
    strHelp = strHelp.append("</li><li>");
    strHelp = strHelp.append("The Standard Deviation is a measure for the dispersion from the mean.");
    strHelp = strHelp.append("</li><li>");
    strHelp = strHelp.append("The Variance is a measure how far the values lie from the mean.");
    strHelp = strHelp.append("</li></ul>");

    funcTypes.insert(131, strHelp);
    funcTypes.insert(170, "As argument you can use a differentiable real function in the variable <i>x</i>. Functions in Complex function section, real numbers and the arithmetic operations <i>+, -, *, /, ^</i> can be used to define real functions.");
    funcTypes.insert(171, "As arguments you can use complex differentiable functions.");
    funcTypes.insert(172, "As argument you can use a real function in the variable <i>x</i>. Functions in Complex function section, real numbers and the arithmetic operations <i>+, -, *, /, ^</i> can be used to define real functions.");
    funcTypes.insert(173, "As argument you can use complex differentiable functions.");
    funcTypes.insert(174, "As argument you can use a real function in the variable <i>x</i>. Functions in Complex function section, real numbers and the arithmetic operations <i>+, -, *, /, ^</i> can be used to define real functions.");


    generalTypes.insert(100, "All functions");
    generalTypes.insert(160, "Analysis");
    generalTypes.insert(120, "Arithmetics");
    generalTypes.insert(110, "Complex functions");
    generalTypes.insert(140, "Linear Algebra");
    generalTypes.insert(130, "Statistics");
    generalTypes.insert(150, "Operators and Commands");
    generalTypes.insert(170, "Differential Calculus");
}

QString stringFactory::gen_info(QString str){
    return infos.value(str).help;
}

QString stringFactory::get_info(QString str){
    return infos.value(str).name;
}

int stringFactory::getCode(QString key){
    return infos.value(key).code;
}

int stringFactory::getVariables(QString key){
    return infos.value(key).variables;
}

QString stringFactory::getHtml(QString key){
    return infos.value(key).html;
}

QString stringFactory::func_info(int code){
    return funcTypes.value(code);
}

QString stringFactory::get_typeName(int code){
    return typenotes.value(code);
}

QString stringFactory::get_plotInfo(QString plot){
    return plotInfo.value(plot);
}

QString stringFactory::get_settingInfo(QString setting){
    return settingInfo.value(setting).help;
}

QString stringFactory::help_info(QString str, int code){
    QString res = gen_info(str);
    QString help;
    if (code != 131 && code != 126 && code != 127 && code != 143 && code !=200 && code != 175) {
        res.append("<br>You may enter \"");
        help = infos.value(str).html;
        if (code == 153) insertSpec(help);
        res.append(help);
        res.append("\" to use this function.");
    }
    res.append("<br><br>");
    res.append(func_info(code));
    return res;
}

QString stringFactory::distributions(){
    QString res = ("<font color=\"#188829\"><h1>MACE</h1></font><h4><i>Mathematics Algorithms Calculations Equations</i></h4>");
    res = res.append("<h3>Statistical Distributions</h3>");
    res = res.append("To use a Statistical Distribution enter the first three letter of its name and \"d\". For example use \"expd\" for the Exponential Distribution, \"nord\" for the ");
    res = res.append("Normal (Gaussian) Distribution and \"stud\" for Students T Distribution. The only exception is the Logistic Distribution. Since \"logd\" is used for the Log Normal Distribution, ");
    res = res.append("one must enter \"lgsd\" for the Logistic Distribution. All Distributions are obtained from the boost library. Three functions and six ");
    res = res.append("properties for distributions are implemented here.<br>");
    res = res.append(funcTypes.value(131));
    res = res.append("The Syntax is as the same as in the boost library.<br>");
    res = res.append("You may also plot functions of statistical distributions or functions defined by using properties of varying statistical distributions.<br>");
    res = res.append("For example use the binomial distribution. To use this distribution enter the the first three letters of its name and \"d\": bind. Now plot ");
    res = res.append("<center>f(x) = pdf(bind(20,0.7),x).</center> This is the probability mass function (pdf) of the binomial distribution (bind) for a series of 20 experiments with the success probability 0.7.<br>");
    res = res.append(" Moreover you may also plot the variation of skewness for example, if you let the probability of success vary in the case of the binomial distribution for 20 experiments. Plot <center>f(x) = skew(bind(20,x)).</center>");
    res = res.append("<br>The following Statistical Distributions obtained from boost are provided:");
    res = res.append("<ul>");
    for(QMap<QString, fctnData>::iterator iter = infos.begin(); iter != infos.end(); iter++){
        if(iter.value().code == 131){
            res = res.append("<li><a href=\"");
            res = res.append(iter.key());
            res = res.append("\">");
            res = res.append(iter.value().name);
            res = res.append("</a>");
            res = res.append("</li>");
        }
    }
    res = res.append("</ul>");
    res = res.append("<br><a href =\"hint\">back to general information</a>");
    return res;
}

QString stringFactory::hint(){
    QString res = ("<font color=\"#188829\"><h1>MACE</h1></font><h4><i>Mathematics Algorithms Calculations Equations</i></h4>");

    res = res.append("<ul type=\"bullet\"><li>");
    res = res.append("<a href=\"datatypes\">Data Types</a>");
    res = res.append("</li><li>");
    res = res.append("<a href=\"functions\">Functions</a>");
    res = res.append("</li><li>");
    res = res.append("<a href=\"grammar\">Grammar</a>");
    res = res.append("</li><li>");
    res = res.append("<a href=\"plots\">Plotter</a>");
    res = res.append("</li><li>");
    res = res.append("<a href=\"script\">Scripting Language</a>");
    res = res.append("</li><li>");
    res = res.append("<a href=\"settings\">Settings</a>");
    res = res.append("</li><li>");
    res = res.append("<a href=\"distributions\">Statistical Distributions</a>");
    res = res.append("</li></ul>");

    res = res.append("<h3>General Information</h3>");

    res = res.append("MACE is a Mathematical program for Algorithms, Calculations and Equations. ");
    res = res.append("It is designed to be as easy to run as a hand-held calculator. The goal of ");
    res = res.append("the project is a neat tool covering the Mathematics at university level ");
    res = res.append("and advanced high-school level.<br><br>");

    res = res.append("MACE is an universal mathematical tool and has 160 functions and statistical ");
    res = res.append("distributions from the fields ");

    res = res.append("<ul><li><a href=\"Analysis\">Analysis</a></li>");
    res = res.append("<li><a href=\"Arithmetics\">Arithmetics</a></li>");
    res = res.append("<li><a href=\"Complex functions\">Complex Functions</a></li>");
    res = res.append("<li><a href=\"Differential Calculus\">Differential Calculus</a></li>");
    res = res.append("<li><a href=\"Linear Algebra\">Linear Algebra</a></li>");
    res = res.append("<li><a href=\"Operators and Commands\">Operators and Commands</a></li>");
    res = res.append("<li><a href=\"Statistics\">Statistics</a></li></ul>");

    res = res.append("Among the functions and statistical distributions of MACE you find for example:");

    res = res.append("<ul><li><a href=\"greatest common divisor\">greatest common divisor</a></li>");
    res = res.append("<li><a href=\"log_a(b)\">log_a(b)</a></li>");
    res = res.append("<li><a href=\"solve a system of linear equations\">solve a system of linear equations</a></li><li>");
    res = res.append("<li><a href=\"normal distribution\">normal (Gaussian) distribution</a></li>");
    res = res.append("<li><a href=\"curve sketching\">curve sketching</a></li></ul>");
    //res = res.append("<li><a href=\"curve sketching\">curve sketching</a></li></ul>");
    //    *curve sketching

    res = res.append("All of the statistical distributions and many of the functions are obtained from ");
    res = res.append("boost math. Moreover MACE uses GNU GMP for fast arbitrary precision calculations.<br><br>");

    res = res.append("You may work intuitively with MACE, since MACE decides automatically which data ");
    res = res.append("type is the correct one for your input.<br><br>");

    res = res.append("You can also work with MACE in an advanced way. MACE has a procedural scripting ");
    res = res.append("language using the parser grammar of the main program. You should get some ");
    res = res.append("example scripts with this release of MACE.<br><br>");

    res = res.append("MACE computes with arbitrary precision integers, (double, double) complex ");
    res = res.append("numbers, (double) real numbers and integral residue classes. Moreover it ");
    res = res.append("computes with polynomials and matrices over the complex numbers resp., ");
    res = res.append("integral residue classes. MACE has an advanced plotter for real functions ");
    res = res.append("and for complex functions.<br><br>");

    res = res.append("By pressing the enter key, you can use the result of your previous calculations ");
    res = res.append("for further computations. Moreover you can use the up - and down arrow tabs to ");
    res = res.append("navigate through your entries.<br><br>");

    res = res.append("You may use the keyboard of your computer or the keyboard on the main window of MACE. ");
    res = res.append("The <a href=\"grammar\">grammar</a> of MACE allows yout to compose several arithmetic operations ");
    res = res.append("and functions. The only rule is that you cannot use the ");
    res = res.append("value of a numeric function for an arbitrary precision function. All complex functions and real functions are numerical. ");
    res = res.append("All other functions for polynomials and integers have arbitrary precision. The great exceptions are the extended Euclidean algorithm, ");
    res = res.append("the prime factor decomposition and the system of linear equations. ");
    res = res.append("These functions cannot be called to return the argument of another function. This is due to the fact that these functions do not have a single datum as result.<br>");
    res = res.append("For two real, complex numbers or complex functions <i>a</i> and <i>b</i> one can compute the power <i>a^b</i> by entering it. ");
    res = res.append("For all other data types the power by a positive integer is implemented.<br><br>");
    res = res.append("If you find a bug in MACE, please make sure to tell us about it!<br>");
    res = res.append("Report bugs to jan-christian.rohde@gmx.de.");

    return res;
}

QString stringFactory::license(){
    QString res = ("MACE is free software; you can redistribute it and/or modify ");
    res = res.append("it under the terms of the GNU General Public License as published by ");
    res = res.append(" the Free Software Foundation; either version 3 of the License, or ");
    res = res.append("(at your option) any later version. ");
    res = res.append("<br><br>");
    res = res.append("MACE is distributed in the hope that it will be useful, ");
    res = res.append("but WITHOUT ANY WARRANTY; without even the implied warranty of ");
    res = res.append("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the ");
    res = res.append("GNU General Public License for more details. ");
    res = res.append("<br><br>");
    res = res.append("You should have received a copy of the GNU General Public License ");
    res = res.append("along with MACE; if not, see http://www.gnu.org/licenses.");

    return res;
}

QString stringFactory::residues(){
    QString res = ("<font color=\"#188829\"><h1>MACE</h1></font><h4><i>Mathematics Algorithms Calculations Equations</i></h4>");
    res = res.append("<h3>Integral Residue Classes</h3>");
    res = res.append("Integral residue classes belong to the essential foundations of computer sciences, cryptography, arithmetics and classical algebra.<br>");
    res = res.append("The integral residue classes modulo <i>n</i> are represented by <i>0, 1, &hellip;, n-1</i>. ");
    res = res.append("The addition and multiplication are defined as for usual integers with the additional condition ");
    res = res.append("that one replaces the result by its remainder of the division by <i>n</i>.<br>");
    res = res.append("In practice you should already compute with residue classes modulo <i>12</i> when you look at the clock. ");
    res = res.append("For example if it is 8 o\'clock, it will be <i>2</i> o'clock in <i>6</i> hours. One has <center><i>8+6 = 14= 1&middot;12 +2</i>.</center>");
    res = res.append("This is an example of the addition modulo <i>12</i>.<br>");
    res = res.append("Assume that it is <i>9</i> o'clock. Three times later it is");
    res = res.append("<center><i>3&middot;9 = 27 = 2&middot;12 + 3</i></center>");
    res = res.append("hours later. Thus it is <i>3</i> o'clock. So you have seen an example of the multiplication modulo <i>12</i>.<br>");
    res = res.append("Next we come to the problem of the multiplication modulo <i>12</i>. For example if you multiply");
    res = res.append("<center><i>4&middot;9 = 36 = 3&middot;12</i>,</center>");
    res = res.append("you obtain <i>0</i> modulo <i>12</i>. This makes it impossible to divide by residue classes modulo <i>12</i> in general. ");
    res = res.append("This problem does not appear, if and only if you compute modulo a prime number <i>p</i>. In this case ");
    res = res.append("the integral residue classes modulo <i>p</i> have a quite similar arithmetic like real and ");
    res = res.append("complex numbers. Then one says that the integral residue classes modulo <i>p</i> form a field. ");
    res = res.append("Only in this case the linear algebra (vector spaces, matrices) and polynomials over integral residue classes modulo <i>p</i> behave like the linear algebra and polynomials over ");
    res = res.append("real or complex numbers. This is the reason that several functions are blocked, if you have selected a ");
    res = res.append("characteristic, which is not <i>0</i> or a prime number.<br>");
    res = res.append("<br><a href =\"datatypes\">back to data types</a>");
    res = res.append("<br><a href =\"functions\">back to functions</a>");
    res = res.append("<br><a href =\"settings\">back to settings</a>");
    res = res.append("<br><a href =\"hint\">back to general information</a>");
    return res;
}

QString stringFactory::script(){
    QString res = ("<font color=\"#188829\"><h1>MACE</h1></font><h4><i>Mathematics Algorithms Calculations Equations</i></h4>");
    res = res.append("<h2>Scripting Language</h2>");
    res = res.append("MACE has a procedural scripting Language. The Idea is that you may use the structures and functions of Mace in a more flexible way to solve your problems. ");
    res = res.append("Thus MACE provides the objects you need to work with and you decide what to do with them. From this point of view it is preferable to write procedural scripts instead of object oriented ones.<br>");
    res = res.append("The scripting language has the control structures if / elseif / else, while loops, for loops and break. Scripts can call other scripts and record the variables of sub-scripts to reuse them. ");
    res = res.append("All <a href=\"datatypes\">data types</a> of MACE can be used as variables. Scripts need to be written in txt-files. ");
    res = res.append("With this release of MACE you should get several example scripts, which may help you to understand and to use the scripting language.<br>");

    res = res.append("<h3>Editing and Execution</h3>");
    res = res.append("Use a text editor of your choice to edit a script in a txt-file. For executing a script select: <center>Scripts->Execute a Script</center> Then a file dialog opens and you may select a file containing a script.<br>");
    res = res.append("This way works only for scripts without input - and output data. Alternatively you can insert \"execute(<i>name of the script</i>,<i>input data</i>)->(<i>output data</i>)\" into the input editor.<br>");

    res = res.append("<h3>Command Lines</h3>");
    res = res.append("The user is free to choose the formating style of his code. The scripting language uses the <a href=\"grammar\">parser grammer</a> of the main program. Thus for your scripts you can use all functions of the main program except of the functions in the linear algebra section.");
    res = res.append(" Command lines in the grammar, which are executed silently, end with \";\". Command lines in the grammar, which are executed ");
    res = res.append("visible on the output editor, end with \":\".<br>");

    res = res.append("<h3>Variables</h3>");
    res = res.append("A variable can be of each type, which appears as <a href=\"datatypes\">data type</a> of MACE. Types of variables are automatically determined. ");
    res = res.append("Moreover a declaration of variables is not necessary except of the case of scripts for records, which may be used as lambdas for example. If a variable is used at the first time, it will be generated automatically. The default value is <i>0</i>. ");
    res = res.append("The name space of a variable is the entire script in which it appears.<br>Of course the name of a variable cannot be a number. ");
    res = res.append("This includes that <i>i</i> cannot be the name of a variable, since <i>i</i> denotes an imaginary number. Moreover <i>x</i> ");
    res = res.append("is a monomial and can also not be the name of a variable.<br> ");


    res = res.append("<h3>Input and Output</h3>");
    res = res.append("It is not necessary to have a print or write method for the scripting language, since you can execute visible command lines. ");
    res = res.append("If you like to print out the value of the variable <i>var</i>, just write \"var:\". The input-method ");
    res = res.append("input(<i>name of a variable</i>) opens an input dialog for the value of a variable.<br>");

    res = res.append("<h3>Control Structures</h3>");
    res = res.append("The brackets \"{\", \"}\" appearing in the table below are necessary in each case - even if you write just one command line inside of the if case or a loop. On the other hand you do not need the ");
    res = res.append("brackets \"(\", \")\" around boolean expressions.");
    res = res.append("<br><table border=1><tr>");
    res = res.append("<th><span style=\"font-weight:200\">if / elseif / else</span></th>");
    res = res.append("<th><span style=\"font-weight:200\">if <i>something hopefully boolean</i> { <i> commands </i> } &hellip; elseif <i>something hopefully boolean</i> { <i> commands </i> } &hellip; else { <i>commands</i> }</span></th>");
    res = res.append("</tr><tr>");
    res = res.append("<th><span style=\"font-weight:200\">while loop</span></th>");
    res = res.append("<th><span style=\"font-weight:200\">while <i>something hopefully boolean</i> { <i> commands </i> } </span></th>");
    res = res.append("</tr><tr>");
    res = res.append("<th><span style=\"font-weight:200\">for loop</span></th>");
    res = res.append("<th><span style=\"font-weight:200\">for <i>initialize</i> ; <i>condition</i> ; <i>reinitialize</i> { <i> commands </i> }</span></th>");
    res = res.append("</tr>");
    res = res.append("</table><br><br>");
    res = res.append("Moreover we have the break-command \"break\", which breaks a loop or the script, if it is used outside of a loop.<br>");

    res = res.append("<h3>Sub-Scripts</h3>");
    res = res.append("You can call other scripts by scripts with the command execute(<i>subscript.txt</i>). You can also use a variable var, which stores the ");
    res = res.append("name of a script as its value and write instead execute(var).<br>If you like that the sub-script can get the ");
    res = res.append(" variables <i>v1, &hellip;, vn</i>, write execute(<i>subscript.txt,v1, &hellip;, vn</i>). ");
    res = res.append("For getting the variables in the sub-script ");
    res = res.append("write get(w1, &hellip;, wn</i>) for names <i>wi</i> of variables of the sub-script. This may be done several times at arbitrary ");
    res = res.append("position with arbitrary variables in the sub-script. Moreover the get-command does not need to be executed, if it can be executed.<br>");
    res = res.append("If you like that the sub-script can give back variable values, write execute(<i>subscript.txt</i>)->(<i>r1,&hellip;,rm</i>) or ");
    res = res.append("execute(<i>subscript.txt,v1, &hellip;, vn</i>)->(<i>r1,&hellip;,rm</i>). ");
    res = res.append("For giving the variable values to the calling script ");
    res = res.append("write give(s1, &hellip;, sm</i>) for names <i>sj</i> of variables of the sub-script. This may also be done several times at arbitrary ");
    res = res.append("position with arbitrary variables in the sub-script. Moreover the give-command does not need to be executed, if it can be executed.");
    res = res.append("The give-command does not finish the sub-script like the \"return\" in many other programming languages.<br>");

    res = res.append("<h3>Records</h3>");
    res = res.append("Instead of classes the scripting language yields the feature to record data sets of sub-routines, to read these sets and reuse the sets for sub-scripts again. ");
    res = res.append("By records one can realize structures and lambdas (see the example scripts).<br>");
    res = res.append(" The syntax is similar to the syntax of sub-scripts <center>record(<i>record name</i>,<i>subscript.txt,v1, &hellip;, vn</i>)->(<i>r1,&hellip;,rm</i>).</center>");
    res = res.append(" If a record used at first time, it will be generated automatically by the variables of the used script. If a record is used later again, the subscript uses the data set of the record ");
    res = res.append("and overwrites the data by script variables of the same name.<br>By <i>record name</i>-><i>variable name</i> you can read variables of a data set. But you cannot write directly ");
    res = res.append(" on a data set. Instead you have to use the record command and a sub-script.<br>If you like to use a script more than once for the same record and to initialize ");
    res = res.append(" a variable, only if it does not exist already, write \"init(<i>variable name</i>,<i>variable value</i>)\".<br>Records can have records, if a record is called inside a sub-script used for a record. ");
    res = res.append("You can read the variables inside a hierarchy of records by use iteratively <i>record name</i>->&hellip;-><i>record name</i>-><i>variable name</i>.<br>");
    res = res.append("For deleting a record just write \"deleteRecord(<i>record name</i>)\".<br>It is not allowed to use the input-command inside a record or a script called by a record.<br>");

    res = res.append("<h3>Additional Commands</h3>");
    res = res.append("<ul type=\"bullet\"><li>");
    res = res.append("cplxPlot(<i>a complex function in the variable x</i>) plots a complex function.");
    res = res.append("</li><li>");
    res = res.append("open(<i>name of a html-file</i>) loads the content of a html-file in the output editor.");
    res = res.append("</li><li>");
    res = res.append("plot(<i>up to 7 functions in the variable x seperated by \",\"</i>) plots up to 7 real functions.");
    res = res.append("</li><li>");
    res = res.append("reset: resets the output editor.");
    res = res.append("</li><li>");
    res = res.append("saveAs(<i>name of a html-file</i>) saves the content of the output editor as a html-file.");
    res = res.append("</li><li>");
    res = res.append("setCharacteristic(<i>a non-negative integer</i>) sets the current characteristic.");
    res = res.append("</li><li>");
    res = res.append("setPrecision(<i>an integer between 2 and 16</i>) sets the current precision.");
    res = res.append("</li></ul>");

    res = res.append("<br><a href =\"hint\">back to general information</a>");
    return res;
}

QString stringFactory::auth(){
    QString res = "<font color=\"#188829\"><h2>MACE 1.4.0</h2></font>";
    res = res.append("");
    res = res.append("<br>");
    res = res.append("&copy; 2012-2014 Jan Christian Rohde<br>jan-christian.rohde@gmx.de");
    res = res.append("<br><br>");
    res = res.append("License: GNU General Public License 3");
    return res;
}

QString stringFactory::dataText(){
    QString res = ("<font color=\"#188829\"><h1>MACE</h1></font><h4><i>Mathematics Algorithms Calculations Equations</i></h4>");
    res = res.append("<h3>Data Types</h3>");
    QMap<QString,QList<int> >::iterator genIt = dataTypes.begin();
    res = res.append("<ul type=\"bullet\">");

    while(genIt != dataTypes.end()){
        res = res.append("<li><a href=\"");
        res = res.append(genIt.key());
        res = res.append("\">");
        res = res.append(genIt.key());
        res = res.append("</a></li>");

        genIt++;
    }
    res = res.append("</ul>");
    res = res.append("<br><a href =\"hint\">back to general information</a>");
    return res;
}

QString stringFactory::fctnText(){
    QString res = ("<font color=\"#188829\"><h1>MACE</h1></font><h4><i>Mathematics Algorithms Calculations Equations</i></h4>");
    res = res.append("<h3>Functions</h3>");

    QMap<int,QString>::iterator genIt = generalTypes.begin();
    res = res.append("<ul type=\"bullet\">");

    while(genIt != generalTypes.end()){
        res = res.append("<li><a href=\"");
        res = res.append(genIt.value());
        res = res.append("\">");
        res = res.append(genIt.value());
        res = res.append("</a></li>");

        genIt++;
    }
    res = res.append("</ul>");
    res = res.append("<br><a href =\"hint\">back to general information</a>");
    return res;
}

QString stringFactory::grammarText(){
    QString res = ("<font color=\"#188829\"><h1>MACE</h1></font><h4><i>Mathematics Algorithms Calculations Equations</i></h4>");

    res = res.append("<h3>Grammar</h3>");
    res = res.append("MACE has the following operators:<br>");
    res = res.append("<table border=1><tr>");
    res = res.append("<th><span style=\"font-weight:200\">Precedence</span></th><th><span style=\"font-weight:200\">Name</span></th><th><span style=\"font-weight:200\">Associativity</span></th>");
    res = res.append("</tr><tr>");
    res = res.append("<th><span style=\"font-weight:200\">11</span></th><th><span style=\"font-weight:200\">,</span></th><th><span style=\"font-weight:200\">left to right</span></th>");
    res = res.append("</tr><tr>");
    res = res.append("<th><span style=\"font-weight:200\">10</span></th><th><span style=\"font-weight:200\">=</span></th><th><span style=\"font-weight:200\">left to right</span></th>");
    res = res.append("</tr><tr>");
    res = res.append("<th><span style=\"font-weight:200\">9</span></th><th><span style=\"font-weight:200\">XOR</span></th><th><span style=\"font-weight:200\">left to right</span></th>");
    res = res.append("</tr><tr>");
    res = res.append("<th><span style=\"font-weight:200\">8</span></th><th><span style=\"font-weight:200\">OR, NOR</span></th><th><span style=\"font-weight:200\">left to right</span></th>");
    res = res.append("</tr><tr>");
    res = res.append("<th><span style=\"font-weight:200\">7</span></th><th><span style=\"font-weight:200\">AND</span></th><th><span style=\"font-weight:200\">left to right</span></th>");
    res = res.append("</tr><tr>");
    res = res.append("<th><span style=\"font-weight:200\">6</span></th><th><span style=\"font-weight:200\">==, !=</span></th><th><span style=\"font-weight:200\">left to right</span></th>");
    res = res.append("</tr><tr>");
    res = res.append("<th><span style=\"font-weight:200\">7</span></th><th><span style=\"font-weight:200\">&lt;, &gt;, &lt;=, &gt;=</span></th><th><span style=\"font-weight:200\">left to right</span></th>");
    res = res.append("</tr><tr>");
    res = res.append("<th><span style=\"font-weight:200\">4</span></th><th><span style=\"font-weight:200\">+, -</span></th><th><span style=\"font-weight:200\">right to left</span></th>");
    res = res.append("</tr><tr>");
    res = res.append("<th><span style=\"font-weight:200\">3</span></th><th><span style=\"font-weight:200\">*, /, evalution and composition for complex functions</span></th><th><span style=\"font-weight:200\">right to left</span></th>");
    res = res.append("</tr><tr>");
    res = res.append("<th><span style=\"font-weight:200\">2</span></th><th><span style=\"font-weight:200\">^</span></th><th><span style=\"font-weight:200\">right to left</span></th>");
    res = res.append("</tr><tr>");
    res = res.append("<th><span style=\"font-weight:200\">1</span></th><th><span style=\"font-weight:200\">prefix ++, prefix --, NOT, unary -, (, ), -\></span></th><th><span style=\"font-weight:200\">left to right</th>");
    res = res.append("</tr></table><br><br>");
    res = res.append("Moreover MACE has the following properties:");
    res = res.append("<ul type=\"bullet\"><li>");
    res = res.append("Space characters are ignored.");
    res = res.append("</li><li>");
    res = res.append("The Multiplication Operation \"*\" will be automatically performed, if:");

        res = res.append("<ul type=\"dot\"><li>");
        res = res.append("There is not written an operation between brackets and a numerical term, i or x outside of the brackets.");
        res = res.append("</li><li>");
        res = res.append("There is not written an operation between a numerical term, i or x.");
        res = res.append("</li><li>");
        res = res.append("There is not written an operation between \")\" and \"(\".");
        res = res.append("</li><li>");
        res = res.append("There is not written an operation between the brackets and a function following directly after the brackets.");
        res = res.append("</li><li>");
        res = res.append("There is not written an operation between the brackets and the operation NOT following directly after the brackets.");
        res = res.append("</li><li>");
        res = res.append("The prefix increment and decrement operators ++ and -- have arbitrary primaries as arguments. ");
        res = res.append("If the argument is constant, <i>1</i> added. If the argument is a variable, <i>1</i> added and the result is stored in the variable.");
        res = res.append("</li></ul>");

    res = res.append("</li><li>");
    res = res.append("Arguments of functions must appear between brackets directly after the name of the function. Different arguments of the same function have to be separated by commas.");
    res = res.append("</li><li>");
    res = res.append("For Statistical Distributions there are no boolean or arithmetic operations implemented at present. Thus statistic distribution can only be used as the first argument of their functions or the argument of their properties or stored as variables.");
    res = res.append("</li><li>");
    res = res.append("Unary operations can be perfomed at the beginning of the command line or after a binary operation respectively.");
    res = res.append("</li></ul>");
    res = res.append("<br><a href =\"hint\">back to general information</a>");
    return res;
}

QString stringFactory::displayData(QString type){
    QString res;
    int i;

    res = "<h2>";
    res= res.append(type);
    res = res.append("</h2>");

    QList<int> fctns = dataTypes.value(type);

    if(fctns.indexOf(100)>=0){
        res = res.append("This data type can be used for standard arithmetic operations entered by the keyboard.<br>");
    }

    if(type.indexOf("residue")>-1){
        res = res.append("You must choose a positive characteristic in the <a href=\"settings\">settings</a> to use integral residue classes.<br>");
        res = res.append("There is a brief introduction to <a href=\"residues\">integral residue classes</a>.<br>");
    }
    if(type.indexOf("polynomial")>-1){
        res = res.append("By using \"^\", polynomials can be entered in the following form:<br>");
        res = res.append("<div align=\"center\">a<sub>n</sub>x^n+&hellip;+a<sub>1</sub>x+a<sub>0</sub></div><br>");
        res = res.append("By brackets you may perform several arithmetic operations with polynomials. For example polynomial division can be used by entering:");
        res = res.append("<div align=\"center\">(a<sub>n</sub>x^n+&hellip;+a<sub>1</sub>x+a<sub>0</sub>)/(b<sub>m</sub>x^m+&hellip;+b<sub>1</sub>x+b<sub>0</sub>)</div><br>");
    }
    if(type.indexOf("bool")>-1){
        res = res.append("MACE does not have an internal data type boolean. Integers are interpreted as booleans (false = 0, true = all other integers).<br>");
    }
    if (type.indexOf("string")>-1) {
        res = res.append("The composition of strings is defined by using the addition <center>\"abc\"+\"def\"=\"abcdef\".</center>");
        res = res.append("One can remove all occurences of a substring by subtraction <center>\"definition\"-\"i\"=\"defnton\".</center>");
    }
    if (type.indexOf("complex function")>-1) {
        res = res.append("There are two ways to generate complex functions. First terms like for example \"sin(x)\" are automatically interpreted as complex functions. ");
        res = res.append("Second one can write \"func(x^2+1)\" to make clear that a one wants to insert a function. Functions can be stored as variables and used for ");
        res = res.append(" the plotter for real and complex functions. By \"f=sin(x): g=cos(x): f(g)\" for example, you can composite functions and get sin(cos(x)). Moreover by \"f=sin(x): f(i+1):\" for example, you can evalutate your stored function variables. ");
    }

    if (type.indexOf("string") == -1 && type.indexOf("complex function") == -1) {
        res = res.append("It can be used for the following functions: <ul type=\"bullet\">");
    }
    else res = res.append("<br><br>");

    QString help;
    for(QMap<QString, fctnData>::iterator iter = infos.begin(); iter != infos.end(); iter++){
        i = iter.value().code;
        if(fctns.indexOf(i)>=0){
            res = res.append("<li><a href=\"");
            res = res.append(iter.key());
            res = res.append("\">");
            help = iter.value().name; insertSpec(help);
            res = res.append(help);
            res = res.append("</a>");
            res = res.append("</li>");
        }
    }
    res = res.append("</ul>");


    res = res.append("<br><a href =\"datatypes\">back to data types</a>");
    res = res.append("<br><a href =\"hint\">back to general information</a>");

    return res;

}

QString stringFactory::fctnList(int type, QString str){
    QString res , helpStr;
    int i= infos.value(str).code;

    res = "<h2>";
    res= res.append(str);
    res = res.append("</h2>");

    if (type == 0){
        res = "<h2>";
        helpStr = get_info(str); insertSpec(helpStr);
        res= res.append(helpStr);
        res = res.append("</h2>");
        res = res.append(help_info(str,i));
        res = res.append("<br><br>");
        res = res.append("<a href =\"");
        i = i-(i%10);
        res = res.append(generalTypes.value(i));
        res = res.append("\">");
        res = res.append("back to ");
        res = res.append(generalTypes.value(i));
        res = res.append("</a><br><a href=\"");
        res = res.append(generalTypes.value(100));
        res = res.append("\">");
        res = res.append("back to ");
        res = res.append(generalTypes.value(100));
        res = res.append("</a>");
    }
    else{
        QMap<int,QString>::iterator genIt = generalTypes.begin();
        QMap<QString,fctnData>::iterator fctnIt = infos.begin();
        QString help;

        res = res.append("<ul type=\"bullet\">");

        while(fctnIt != infos.end()){


            if(type <= fctnIt.value().code && (type ==100 || fctnIt.value().code < type+10)){
                res = res.append("<li><a href=\"");
                res = res.append(fctnIt.key());
                res = res.append("\">");
                help = fctnIt.value().name; insertSpec(help);
                res = res.append(help);
                res = res.append("</li>");
            }


            fctnIt++;
        }
        res = res.append("</ul>");
    }
    res = res.append("<br><a href =\"hint\">back to general information</a>");

    return res;
}

QString stringFactory::plotText(){
    QString res = ("<font color=\"#188829\"><h1>MACE</h1></font><h4><i>Mathematics Algorithms Calculations Equations</i></h4>");
    res = res.append("<h3>Plotter</h3>");

    res = res.append("<ul type=\"bullet\">");

    QMap<QString,QString>::iterator setIt = plotInfo.begin();
    while(setIt != plotInfo.end()){
        res = res.append("<li>");
        res = res.append("<h4>");
        res = res.append(setIt.key());
        res = res.append("</h4>");

        res = res.append(setIt.value());
        res = res.append("</li>");

        setIt++;
    }
    res = res.append("</ul>");
    res = res.append("<br><a href =\"hint\">back to general information</a>");

    return res;
}

QString stringFactory::settingText(){
    QString res = ("<font color=\"#188829\"><h1>MACE</h1></font><h4><i>Mathematics Algorithms Calculations Equations</i></h4>");
    res = res.append("<h3>Settings</h3>");

    res = res.append("<ul type=\"bullet\">");

    QMap<QString,fctnData>::iterator setIt = settingInfo.begin();
    while(setIt != settingInfo.end()){
        res = res.append("<li>");
        res = res.append("<h4>");
        res = res.append(setIt.key());
        res = res.append("</h4>");

        res = res.append(setIt.value().help);
        res = res.append("</li>");

        setIt++;
    }
    res = res.append("</ul>");
    res = res.append("<br><a href =\"hint\">back to general information</a>");

    return res;
}
