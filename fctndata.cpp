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

#include "fctndata.h"
#include <iostream>

genFunctions::genFunctions(){

}

QMap<QString,fctnData> analFunctions::get_map(){
    QMap<QString,fctnData> infos;
    QString strHelp, help;
    fctnData a;

    a.name = "Laguerre polynomial";
    a.code =160;
    a.variables = 2;
    strHelp = "This function returns the value of the Laguerre polynomial of degree <i>n</i> at <i>x</i>.";
    strHelp = strHelp.append(" Laguerre polynomials solve Laguerre's differential equation");
    strHelp = strHelp.append("<center>xy''+(1-x)y'+ny = 0.</center>");
    strHelp = strHelp.append("and are defined as");
    strHelp = strHelp.append("<center>exp(x)/n! d<sup>n</sup>/dx<sup>n</sup> (x<sup>n</sup>exp(-x)).</center>");
    a.help = strHelp;
    a.html = "lagPol";
    infos.insert("laguerre", a);

    a.name = "Legendre polynomial";
    a.code =160;
    a.variables = 2;
    strHelp = "This function returns the value of the Legendre polynomial of degree <i>n</i> at <i>x</i> and is defined for <i>x</i> in <i>[-1,1]</i>.";
    strHelp = strHelp.append(" The Legendre polynomials form an orthogonal basis of the Hilbert space <i>L<sup>2</sup>[-1,1]</i> and solve Legendre's differential equation");
    strHelp = strHelp.append("<center>d/dx[(1-x)<sup>2</sup>d/dx f(x)]+n(n+1)f(x) = 0.</center>");
    strHelp = strHelp.append("Legendre polynomials are defined by");
    strHelp = strHelp.append("<center>legPol(n,x) = 1/(2<sup>n</sup>n!) d<sup>n</sup>/dx<sup>n</sup> (x<sup>2</sup>-1)<sup>n</sup>.</center>");
    a.help = strHelp;
    a.html = "legPol";
    infos.insert("legendre", a);

    a.name = "Hermite polynomial";
    a.code =160;
    a.variables = 2;
    strHelp = "This function returns the value of the Hermite polynomial of degree <i>n</i> at <i>x</i> defined as";
    strHelp = strHelp.append("<center>(-1)<sup>n</sup>exp(x<sup>2</sup>) d<sup>n</sup>/dx<sup>n</sup> exp(-x<sup>2</sup>).</center>");
    a.help = strHelp;
    a.html = "herPol";
    infos.insert("hermit", a);

    a.name = "spherical harmonics";
    a.code =160;
    a.variables = 4;
    strHelp = "The Spherical Harmonics are the angular portion of the solution to Laplace's equation in spherical coordinates where azimuthal symmetry is not present.";
    a.help = strHelp;
    a.html = "spHarm";
    infos.insert("spherical harmonics", a);

    a.name = "J (Bessel function)";
    a.code =160;
    a.variables = 2;
    strHelp = "This function returns the value of the Bessel function J<i>(v,x) = </i>J<i>_v(x)</i> of first kind.";
    a.help = strHelp;
    a.html = "J";
    infos.insert("j", a);

    a.name = "Y (Neumann function)";
    a.code =160;
    a.variables = 2;
    strHelp = "The Neumann Function or Bessel Function of second kind Y is defined by using the Bessel function J as";
    strHelp = strHelp.append("<center>Y<i>(v,x) = </i>[J<i>(v,x)</i> cos<i>(v&pi;) - </i>J<i>(-v,x)</i>]/sin<i>(v&pi;)</i>.</center>");
    a.help = strHelp;
    a.html = "Y";
    infos.insert("y", a);

    a.name = "F (elliptic integral of first kind, 2 variables)";
    a.code =160;
    a.variables = 2;
    strHelp = "The Elliptic Integral F(&phi;,k) of first kind is defined as";
    strHelp = strHelp.append("<center><table><tr><th><span style=\"font-weight:200\">&phi;</span></th><th></th></tr><tr><th><span style=\"font-weight:200\">&int;</span></th><th><span style=\"font-weight:200\">(1-k<sup>2</sup>sin<sup>2</sup>x)<sup>-1/2</sup>dx.</span></th></tr><tr><th><span style=\"font-weight:200\">0</span></th><th></th></tr></table></center>");
    a.help = strHelp;
    a.html = "F";
    infos.insert("f", a);

    a.name = "K (elliptic integral of first kind, 1 variable)";
    a.code =160;
    a.variables = 1;
    strHelp = "The Elliptic Integral K(k) of first kind is defined as";
    strHelp = strHelp.append("<center><table><tr><th><span style=\"font-weight:200\">&pi;/2</span></th><th></th></tr><tr><th><span style=\"font-weight:200\">&int;</span></th><th><span style=\"font-weight:200\">(1-k<sup>2</sup>sin<sup>2</sup>x)<sup>-1/2</sup>dx.</span></th></tr><tr><th><span style=\"font-weight:200\">0</span></th><th></th></tr></table></center>");
    a.help = strHelp;
    a.html = "K";
    infos.insert("k", a);

    a.name = "En (exponential integral)";
    a.code =160;
    a.variables = 2;
    strHelp = "The Exponential Integral En is defined as";
    strHelp = strHelp.append("<center><table><tr><th></th><th><span style=\"font-weight:200\">&infin;</span></th><th></th></tr><tr><th><span style=\"font-weight:200\">En(n,x) = </span></th><th><span style=\"font-weight:200\">&int;</span></th><th><span style=\"font-weight:200\">exp(-xt)/t<sup>n</sup> dt</span></th></tr><tr><th></th><th><span style=\"font-weight:200\">1</span></th><th></th></tr></table></center>");
    strHelp = strHelp.append("for an integer <i>n</i> and a double <i>x</i>.");
    a.help = strHelp;
    a.html = "En";
    infos.insert("exponential integral", a);

    a.name = "Ei (exponential integral)";
    a.code =160;
    a.variables = 1;
    strHelp = "The Exponential Integral Ei is defined as";
    strHelp = strHelp.append("<center><table><tr><th></th><th><span style=\"font-weight:200\">&infin;</span></th><th></th></tr><tr><th><span style=\"font-weight:200\">Ei(a) = </span></th><th><span style=\"font-weight:200\">&int;</span></th><th><span style=\"font-weight:200\">exp(-x)/x dx.</span></th></tr><tr><th></th><th><span style=\"font-weight:200\">-a</span></th><th></th></tr></table></center>");
    a.help = strHelp;
    a.html = "Ei";
    infos.insert("exponential integral i", a);

    a.name = "erf (error function)";
    a.code =160;
    a.variables = 1;
    strHelp = "The Error Function is defined by the integral";
    strHelp = strHelp.append("<center>erf(a) =</center>");
    strHelp = strHelp.append("<center><table><tr><th></th><th><span style=\"font-weight:200\">a</span></th><th></th></tr><tr><th><span style=\"font-weight:200\">(2/&radic;&pi;) &middot; </span></th><th><span style=\"font-weight:200\">&int;</span></th><th><span style=\"font-weight:200\">exp(-x<sup>2</sup>)dx.</span></th></tr><tr><th></th><th><span style=\"font-weight:200\">0</span></th><th></th></tr></table></center>");
    a.help = strHelp;
    a.html = "erf";
    infos.insert("error function", a);

    a.name = "gamma_p (incomplete gamma function)";
    a.code =160;
    a.variables = 2;
    strHelp = "The Incomplete Gamma Function is defined by the original gamma function and the integral";
    strHelp = strHelp.append("<center>gamma<sub>p</sub>(a,b) =</center>");
    strHelp = strHelp.append("<center><table><tr><th></th><th><span style=\"font-weight:200\">b</span></th><th></th></tr><tr><th><span style=\"font-weight:200\">1/(&Gamma;(a)) &middot; </span></th><th><span style=\"font-weight:200\">&int;</span></th><th><span style=\"font-weight:200\">x<sup>a-1</sup>exp(-x)dx.</span></th></tr><tr><th></th><th><span style=\"font-weight:200\">0</span></th><th></th></tr></table></center>");
    a.help = strHelp;
    a.html = "gammap";
    infos.insert("gamma_p", a);

    a.name = "beta_i (incomplete beta function)";
    a.code =160;
    a.variables = 3;
    strHelp = "The Incomplete Beta Function is defined by the original Beta function B and the integral";
    strHelp = strHelp.append("<center>beta<sub>i</sub>(a,b,c) =</center>");
    strHelp = strHelp.append("<center><table><tr><th></th><th><span style=\"font-weight:200\">c</span></th><th></th></tr><tr><th><span style=\"font-weight:200\">1/(B(a,b)) &middot; </span></th><th><span style=\"font-weight:200\">&int;</span></th><th><span style=\"font-weight:200\">x<sup>a-1</sup>(1-x)<sup>b-1</sup>dx.</span></th></tr><tr><th></th><th><span style=\"font-weight:200\">0</span></th><th></th></tr></table></center>");
    a.help = strHelp;
    a.html = "betai";
    infos.insert("beta_i", a);

    a.name = "E (elliptic integral of second kind, 1 variable)";
    a.code =160;
    a.variables = 1;
    strHelp = "The Elliptic Integral E(k) of second kind is defined as";
    strHelp = strHelp.append("<center><table><tr><th><span style=\"font-weight:200\">&pi;/2</span></th><th></th></tr><tr><th><span style=\"font-weight:200\">&int;</span></th><th><span style=\"font-weight:200\">(1-k<sup>2</sup>sin<sup>2</sup>x)<sup>1/2</sup>dx.</span></th></tr><tr><th><span style=\"font-weight:200\">0</span></th><th></th></tr></table></center>");
    a.help = strHelp;
    a.html = "E";
    infos.insert("e1", a);

    a.name = "E2 (elliptic integral of second kind, 2 variables)";
    a.code =160;
    a.variables = 2;
    strHelp = "The Elliptic Integral E(&phi;,k) of second kind is defined as";
    strHelp = strHelp.append("<center><table><tr><th><span style=\"font-weight:200\">&phi;</span></th><th></th></tr><tr><th><span style=\"font-weight:200\">&int;</span></th><th><span style=\"font-weight:200\">(1-k<sup>2</sup>sin<sup>2</sup>x)<sup>1/2</sup>dx.</span></th></tr><tr><th><span style=\"font-weight:200\">0</span></th><th></th></tr></table></center>");
    a.help = strHelp;
    a.html = "E2";
    infos.insert("e2", a);

    help ="PI";
    help = help.append(" (elliptic integral of third kind)");
    a.name = help;
    a.code =160;
    a.variables = 3;
    strHelp = "The Elliptic Integral E(n,&phi;,k) of third kind is defined as";
    strHelp = strHelp.append("<center><table><tr><th><span style=\"font-weight:200\">&phi;</span></th><th></th></tr><tr><th><span style=\"font-weight:200\">&int;</span></th><th><th><span style=\"font-weight:200\">(1-n&middot;sin<sup>2</sup>x)<sup>-1</sup>&middot;(1-k<sup>2</sup>&middot;sin<sup>2</sup>x)<sup>-1/2</sup>dx.</span></th></tr><tr><th><span style=\"font-weight:200\">0</span></th><th></th></tr></table></center>");
    a.help = strHelp;
    a.html = "PI";
    infos.insert("pi3", a);

    a.name = "B (Beta function)";
    a.code =160;
    a.variables = 2;
    strHelp = "The Beta Function B can be defined by the <a href=\"gamma\">Gamma Function &Gamma;</a> via";
    strHelp = strHelp.append("<center>B(a,b) = &Gamma;(a)&middot;&Gamma;(b)/&Gamma;(a+b).</center>");
    a.help = strHelp;
    a.html = "B";
    infos.insert("beta", a);

    help = "log gamma";
    a.name = help;
    a.code =160;
    a.variables = 1;
    strHelp = "The Log Gamma Function is defined by ";
    strHelp = strHelp.append("<center>lgamma(a) = ln|&Gamma;(a)|.</center>");
    a.help = strHelp;
    a.html = "lgamma";
    infos.insert("lgamma", a);

    help = "digamma";
    a.name = help;
    a.code =160;
    a.variables = 1;
    strHelp = "The Digamma Function is the logarithmic derivative of gamma";
    strHelp = strHelp.append("<center>digamma(a) = &Gamma;`(a)/&Gamma;(a).</center>");
    a.help = strHelp;
    a.html = "digamma";
    infos.insert("digamma", a);

    help = "derivative of gamma_i";
    a.name = help;
    a.code =160;
    a.variables = 2;
    strHelp = "This is the derivative of the incomplete gamma Function gammai";
    strHelp = strHelp.append("<center>dgammai(a,b) = exp(-b)&middot;b<sup>a-1</sup>/&Gamma;(a).</center>");
    a.help = strHelp;
    a.html = "dgammai";
    infos.insert("dgammai", a);

    help =QString((QChar)0x0393);
    help = help.append(" (Gamma function)");
    a.name = help;
    a.code =160;
    a.variables = 1;
    strHelp = "The Gamma Function is defined by the improper integral";
    strHelp = strHelp.append("<center><table><tr><th></th><th><span style=\"font-weight:200\">&infin;</span></th><th></th></tr><tr><th><span style=\"font-weight:200\">&Gamma;(z) = </span></th><th><span style=\"font-weight:200\">&int;</span></th><th><span style=\"font-weight:200\">exp(-t)t<sup>z-1</sup> dt.</span></th></tr><tr><th></th><th><span style=\"font-weight:200\">0</span></th><th></th></tr></table></center>");
    a.help = strHelp;
    a.html = "gamma";
    infos.insert("gamma", a);

    return infos;
}

QMap<QString,fctnData> complexFunctions::get_map(){
    QMap<QString,fctnData> infos;
    QString strHelp, help;
    fctnData a;

    a.name = "No";
    a.code =0;
    a.variables = 1;
    strHelp = "This is the empty function.";
    a.help = strHelp;
    a.html = "No";
    infos.insert("No", a);

    a.name = "cos";
    a.code =110;
    a.variables = 1;
    strHelp = "The Cosine cos is the trigonometric function which returns the ratio between the adjacent side ";
    strHelp = strHelp.append("to the hypotenuse in a right triangle.");
    a.help = strHelp;
    a.html = "cos";
    infos.insert("cos", a);

    a.name = "conj (complex conjugate)";
    a.code =110;
    a.variables = 1;
    strHelp = "The Complex Conjugate conj of a complex number <i>x+iy</i> is defined by <center>conj(x+iy) = x-iy.</center>";
    a.help = strHelp;
    a.html = "conj";
    infos.insert("conj", a);

    a.name = "sin";
    a.code =110;
    a.variables = 1;
    strHelp = "The Sine sin is the trigonometric function which returns the ratio between the opposite side ";
    strHelp = strHelp.append("to the hypotenuse in a right triangle.");
    a.help = strHelp;
    a.html = "sin";
    infos.insert("sin", a);

    a.name = "arccos";
    a.code =110;
    a.variables = 1;
    strHelp =  "The Arccosine arccos is the inverse function of the trigonometric function cosine.";
    a.help = strHelp;
    a.html = "arccos";
    infos.insert("arccos", a);

    a.name = "arcsin";
    a.code =110;
    a.variables = 1;
    strHelp =  "The Arcsine arcsin is the inverse function of the trigonometric function sine.";
    a.help = strHelp;
    a.html = "arcsin";
    infos.insert("arcsin", a);

    a.name = "cot";
    a.code =110;
    a.variables = 1;
    strHelp = "The Cotangent cot is the ratio of the adjacent by the opposite in a right triangle. It can also be defined as the ";
    strHelp = strHelp.append("quotient of cos by sin.");
    a.help = strHelp;
    a.html = "cot";
    infos.insert("cot", a);

    a.name = "tan";
    a.code =110;
    a.variables = 1;
    strHelp = "The Tangent tan is the ratio of the opposite by the adjacent in a right triangle. It can also be defined as the ";
    strHelp = strHelp.append("quotient of sin by cos.");
    a.help = strHelp;
    a.html = "tan";
    infos.insert("tan", a);

    a.name = "abs";
    a.code =110;
    a.variables = 1;
    strHelp = "The Absolute Value abs of a complex number <center><i>z = x+iy</i></center> is given by <i>&radic;(x<sup>2</sup>+y<sup>2</sup>)</i>.";
    a.help = strHelp;
    a.html = "abs";
    infos.insert("abs", a);

    a.name = "polar";
    a.code =110;
    a.variables = 1;
    strHelp = "Transforms a complex number <i>z</i> to its polar coordinates. The real part of polar<i>(z)</i> is the absolute value of <i>z</i>. ";
    strHelp = strHelp.append("The imaginary part of polar<i>(z)</i> is the angle between <i>z</i> and the positive real semi axis.");
    a.help = strHelp;
    a.html = "polar";
    infos.insert("polar", a);


    a.name = "arccot";
    a.code =110;
    a.variables = 1;
    strHelp = "The Arccotangent arccot is the inverse function of the trigonometric function cot.";
    a.help = strHelp;
    a.html = "arccot";
    infos.insert("arccot", a);

    a.name = "coth";
    a.code =110;
    a.variables = 1;
    strHelp = "The Hyperbolic Cotangent coth is the hyperbolic analog of the trigonometric function cot.";
    strHelp = strHelp.append(" It is the quotient of cosh by sinh.");
    a.help = strHelp;
    a.html = "coth";
    infos.insert("coth", a);

    a.name = "arcoth";
    a.code =110;
    a.variables = 1;
    strHelp =  "The Hyperbolic Arcotangent arcoth is the inverse function of the hyperbolic cotangent coth.";
    a.help = strHelp;
    a.html = "arcoth";
    infos.insert("arcoth", a);

    a.name = "arctan";
    a.code =110;
    a.variables = 1;
    strHelp =  "The Arctangent arctan is the inverse function of the trigonometric function tangent.";
    a.help = strHelp;
    a.html = "arctan";
    infos.insert("arctan", a);

    a.name = "artanh";
    a.code =110;
    a.variables = 1;
    strHelp =  "The Hyperbolic Arctangent artanh is the inverse function of the hyperbolic function tanh.";
    a.help = strHelp;
    a.html = "artanh";
    infos.insert("artanh", a);

    a.name = "cosh";
    a.code =110;
    a.variables = 1;
    strHelp = "The Hyperbolic Cosine cosh is the hyperbolic analog of the trigonometric function cos.";
    a.help = strHelp;
    a.html = "cosh";
    infos.insert("cosh", a);

    a.name = "sinh";
    a.code =110;
    a.variables = 1;
    strHelp = "The Hyperbolic Sine sinh is the hyperbolic analog of the trigonometric function sin.";
    a.help = strHelp;
    a.html = "sinh";
    infos.insert("sinh", a);

    a.name = "tanh";
    a.code =110;
    a.variables = 1;
    strHelp = "The Hyperbolic Tangent <i>tanh</i> is the hyperbolic analog of the trigonometric function <i>tan</i>.";
    strHelp = strHelp.append(" It is the quotient of <i>sinh</i> by <i>cosh</i>.");
    a.help = strHelp;
    a.html = "tanh";
    infos.insert("tanh", a);

    a.name = "arcosh";
    a.code =110;
    a.variables = 1;
    strHelp = "The Area Hyperbolic Cosine arcosh is the inverse function of the hyperbolic function cosh.";
    a.help = strHelp;
    a.html = "arcosh";
    infos.insert("arcosh", a);

    a.name = "arsinh";
    a.code =110;
    a.variables = 1;
    strHelp = "The Area Hyperbolic Sine arsinh is the inverse function of the hyperbolic function sinh.";
    a.help = strHelp;
    a.html = "arsinh";
    infos.insert("arsinh", a);

    a.name = "exp";
    a.code =110;
    a.variables = 1;
    a.html = "exp";
    a.help =  "The Exponential Function exp(<i>x</i>) provides the power of the Euler number <i>e</i> = 2.71828&hellip; by <i>x</i>.";
    infos.insert("exp", a);

    a.name = "ln";
    a.code =110;
    a.variables = 1;
    strHelp =  "The Natural logarithm ln is the inverse function of exp.";
    a.help = strHelp;
    a.html = "ln";
    infos.insert("ln", a);

    a.name = "log_a(b)";
    a.code =110;
    a.variables = 2;
    strHelp = "log<i>_a</i><i>(b)</i> denotes the logarithm of <i>b</i> to the base <i>a</i>. ";
    strHelp = strHelp.append("That means that for <span class=\"nowrap\"><i>c = </i>log<i>_a</i>(<i>b</i>)</span> one obtains ");
    strHelp = strHelp.append("<span class=\"nowrap\"><i><i>b=a</i><sup><i>c</i></sup>.</span>");
    a.help = strHelp;
    a.html = "log";
    infos.insert("log_a(b)", a);

    a.name = "1/a";
    a.code =111;
    a.variables = 1;
    strHelp = "The inverse <span class=\"nowrap\"><i>1/a</i></span> of <span class=\"nowrap\"><i>a&ne;0</i></span> ";
    strHelp = strHelp.append("satisfies the equation <center><span class=\"nowrap\"><i>a &middot; 1/a = 1.</span></center>");
    a.help = strHelp;
    a.html = "1/";
    infos.insert("1/a", a);

    a.name = "real";
    a.code =110;
    a.variables = 1;
    strHelp = "The real part of a complex number <i>x + iy</i> is <i>x</i>.";
    a.help = strHelp;
    a.html = "real";
    infos.insert("real", a);

    a.name = "imag";
    a.code =110;
    a.variables = 1;
    strHelp = "The imaginary part of a complex number <i>x + iy</i> is <i>y</i>.";
    a.help = strHelp;
    a.html = "imag";
    infos.insert("imag", a);

    help =QString((QChar)0x00B2);
    help = help.prepend("a");
    a.name = help;
    a.code =111;
    a.variables = 1;
    a.help = "The Square <i>a<sup>2</sup></i> of <i>a</i> is the product of <i>a</i> with itself.";
    a.html = "a^2";
    infos.insert("a^2", a);

    help = "root";
    a.name = QString((QChar)0x221A);
    a.code =110;
    a.variables = 1;
    strHelp = QString((QChar)0x221A);
    strHelp = strHelp.prepend("The Square Root ");
    strHelp = strHelp.append("<i>a</i> of <i>a</i> is a number <i>b</i> satisfying <center><i>b&middot;b = a.</i></center>");
    a.help = strHelp;
    a.html ="radic";
    infos.insert(help, a);

    return infos;
}

QMap<QString,fctnData> arithmetics::get_map(){
    QMap<QString,fctnData> infos;
    QString strHelp, help;
    fctnData a;

    a.name = "a!";
    a.code =121;
    a.variables = 1;
    a.help = "The Faculty <i>a!</i> of a positive integer <i>a</i> denotes the product of all integers from <i>1</i> to <i>a</i>.";
    a.html = "fac";
    infos.insert("a!", a);

    help = QString((QChar)0x207F);
    help = help.prepend("a");
    a.name = help;
    a.code =111;
    a.variables = 2;
    strHelp = ("The Power");
    strHelp = strHelp.append(" of <i>a</i> by <i>n</i> denotes the <i>n</i>-fold product of <i>a</i> with itself.");
    a.help = strHelp;
    a.html = "a^n";
    infos.insert("a^n", a);

    a.name = "a choose b";
    a.code =121;
    a.variables = 2;
    strHelp = "The Binomial Coefficient <i>a choose b</i> denotes the number of ways disregarding order that <i>b</i> ";
    strHelp = strHelp.append("objects can be chosen from among <i>a</i> objects.");
    a.help =  strHelp;
    a.html = "chs";
    infos.insert("a choose b", a);

    a.name = "factorial (rising)";
    a.code =128;
    a.variables = 2;
    strHelp = "The Rising Factorial is defined as the product";
    strHelp = strHelp.append("<center>risFac(x,n) = x&middot;(x+1)&middot;&hellip;&middot;(x+n-1)</center>");
    strHelp = strHelp.append("for the integer <i>n</i>.");
    a.help = strHelp;
    a.html = "risFac";
    infos.insert("facris", a);

    a.name = "factorial (falling)";
    a.code =128;
    a.variables = 2;
    strHelp = "The Falling Factorial is defined as the product";
    strHelp = strHelp.append("<center>falFac(x,n) = x&middot;(x-1)&middot;&hellip;&middot;(x-n+1)</center>");
    strHelp = strHelp.append("for the integer <i>n</i>.");
    a.help = strHelp;
    a.html = "falFac";
    infos.insert("facfal", a);

    a.name = "multiset";
    a.code =121;
    a.variables = 2;
    strHelp = "The Multiset denotes the number of ways disregarding order that <i>b</i> objects can be chosen from among";
    strHelp = strHelp.append("<i>a</i> objects with the possibility to choose each selected object again.");
    a.help = strHelp;
    a.html = "mset";
    infos.insert("multiset", a);

    a.name = "Fibonacci number";
    a.code =121;
    a.variables = 1;
    strHelp = "The Fibonacci numbers are a sequence of positive integers. ";
    strHelp = strHelp.append("The Fibonacci number <i>f<sub>0</sub></i> is <i>0</i> and <i>f<sub>1</sub></i> is 1. ");
    strHelp = strHelp.append("All further Fibonacci numbers <i>f<sub>n</sub></i> are defined by the rule");
    strHelp = strHelp.append("<div align=\"center\"><span class=\"nowrap\">f<sub>n</sub> = f<sub>n-1</sub>+f<sub>n-2</sub>.</span></div>");
    strHelp = strHelp.append("The fast increasing Fibonacci numbers describe the growth of a rabbit population.");
    a.help = strHelp;
    a.html = "fib";
    infos.insert("fibonacci number", a);

    a.name = "% (modulo)";
    a.code =125;
    a.variables = 2;
    a.help = "The Remainder <i>a%b</i>  denotes the remainder of <i>a</i> modulo <i>b</i>.";
    a.html = "mod";
    infos.insert("% (modulo)", a);

    a.name = "greatest common divisor";
    a.code =125;
    a.variables = 2;
    strHelp = "The Greatest Common Divisor <span class=\"nowrap\">gcd(<i>a,b</i>)</span> of two integers <i>a</i> and <i>b</i> ";
    strHelp = strHelp.append("is the largest integer dividing <i>a</i> and <i>b</i>. If <i>a</i> and <i>b</i> are polynomials, ");
    strHelp = strHelp.append("the <span class=\"nowrap\">gcd(<i>a,b</i>)</span> is the polynomial of highest degree dividing ");
    strHelp = strHelp.append("<i>a</i> and <i>b</i>. The latter is unique up to the multiplication with a non-zero constant.");
    a.help = strHelp;
    a.html = "gcd";
    infos.insert("greatest common divisor", a);

    a.name = "least common multiple";
    a.code =125;
    a.variables = 2;
    strHelp = "The Least Common Multiple <span class=\"nowrap\">lcm(<i>a,b</i>)</span> of two integers <i>a</i> and <i>b</i> ";
    strHelp = strHelp.append("is the smallest integer divided by <i>a</i> and <i>b</i>. If <i>a</i> and <i>b</i> are polynomials, ");
    strHelp = strHelp.append("the <span class=\"nowrap\">lcm(<i>a,b</i>)</span> is the polynomial of smallest degree divided by ");
    strHelp = strHelp.append("<i>a</i> and <i>b</i>. The latter is unique up to the multiplication with a non-zero constant.");
    a.help = strHelp;
    a.html = "lcm";
    infos.insert("least common multiple", a);

    help =QString((QChar)0x03BB);
    help = help.append(" (Liouville function)");
    a.name = help;
    a.code =121;
    a.variables = 1;
    strHelp = "The Liouville Function &lambda; yields <i>0</i> for <i>a</i>, if <i>a</i> is 0, ";
    strHelp = strHelp.append("-1, if <i>a</i> is the product of an odd number of prime factors or <i>1</i>, if <i>a</i> is the ");
    strHelp = strHelp.append("product of an even number of prime factors. If for a prime factor <i>p</i> the power ");
    strHelp = strHelp.append("<i>p<sup>n</sup></i> divides <i>a</i>, then <i>p</i> counts <i>n</i> times. ");
    a.help = strHelp;
    a.html = "lambda";
    infos.insert("lambda (Liouville function)", a);

    a.name = "number of factors";
    a.code =121;
    a.variables = 1;
    a.help = "This is the number of factors dividing the positive integer <i>a</i> including <i>1</i> and <i>a</i> itself.";
    a.html = "numFac";
    infos.insert("number of factors", a);

    a.name = "sum of factors";
    a.code =121;
    a.variables = 1;
    a.help = "This is the sum of factors dividing the positive integer <i>a</i> including <i>1</i> and <i>a</i> itself.";
    a.html = "sumFac";
    infos.insert("sum of factors", a);

    a.name = "next prime";
    a.code =121;
    a.variables = 1;
    a.help = "This is the probabilistic function mpz_nextprime from GNU GMP assigning to an integer the next greater prime number. For practical purposes it should be adequate as claimed in the documentation of GMP.";
    a.html = "nextPrime";
    infos.insert("next prime", a);

    help =QString((QChar)0x03C6);
    help = help.append(" (Euler totient function)");
    a.name = help;
    a.code =121;
    a.variables = 1;
    strHelp = "The Euler totient function &phi; assigns to a positive integer <i>a</i> the number of positive integers less than <i>a</i>, which do not have any common divisor with <i>a</i> except of <i>1</i>.";
    a.help = strHelp;
    a.html = "phi";
    infos.insert("phi (Euler totient function)", a);

    help =QString((QChar)0x03C0);
    help = help.append(" (prime counting function)");
    a.name =help;
    a.code =121;
    a.variables = 1;
    strHelp = "The Prime Counting Function &pi;<i>(a)</i> counts the number of prime numbers less or equal <i>a</i>.";
    a.help = strHelp;
    a.html = "pi";
    infos.insert("pi (prime counting function)", a);

    help =QString((QChar)0x03C8);
    help = help.append(" (Dedekind function)");
    a.name = help;
    a.code =121;
    a.variables = 1;
    strHelp = "The Dedekind Function &psi; is a multiplicative number theoretic function. For an integer with the prime factor decomposition";
    strHelp = strHelp.append("<div align=\"center\"><span class=\"nowrap\">n = p<sub>1</sub>^a<sub>1</sub>&middot;...&middot;p<sub>n</sub>^a<sub>n</sub></span></div>");
    strHelp = strHelp.append("one obtains");
    strHelp = strHelp.append("<div align=\"center\"><span class=\"nowrap\">&psi;(n) = (p<sub>1</sub>+1)p<sub>1</sub>^(a<sub>1</sub>-1)&middot;...&middot;(p<sub>n</sub>+1)p<sub>n</sub>^(a<sub>n</sub>-1).</span></div>");
    a.help = strHelp;
    a.html = "psi";
    infos.insert("psi (Dedekind function)", a);

    a.name = "smallest prime factor";
    a.code =121;
    a.variables = 1;
    a.help = "This returns the smallest prime factor of an integer.";
    a.html = "smPrm";
    infos.insert("smallest prime factor", a);

    a.name = "extended Euclidean algorithm";
    a.code =127;
    a.variables = 2;
    strHelp = "By the Extended Euclidean Algorithm allows you to expresses the Greatest Common Divisor gcd(<i>a,b</i>) of <i>a</i> and <i>b</i> as the sum";
    strHelp = strHelp.append("<center>gcd(a,b) = s*a + t*b</center> for two factors <i>s</i> and <i>t</i>. ");
    strHelp =strHelp.append("For more information see <a href=\"greatest common divisor\">");
    strHelp = strHelp.append("greatest common divisor</a>.");
    a.help = strHelp;
    a.html = "extEuclAlgo";
    infos.insert("extended Euclidean algorithm", a);

    a.name = "prime factor decomposition";
    a.code =126;
    a.variables = 1;
    strHelp = "This function decomposes an integer or a polynomial into its prime factors. ";
    strHelp = strHelp.append("In the case of an integer a prime number <i>p</i> is only divisible by <i>p, -p, 1</i> and <i>-1</i>. ");
    strHelp = strHelp.append("In the case of polynomials a prime factor is polynomial <i>p</i>, which is only divisible by ");
    strHelp = strHelp.append("polynomials of the form <i>c&middot;p</i> for a constant <i>c</i> and constant polynomials.");
    a.help = strHelp;
    a.html = "primeFacDec";
    infos.insert("prime factor decomposition", a);

    a.name = "primality test";
    a.code =121;
    a.variables = 1;
    strHelp = "This is the probabilistic Primality Test from GNU GMP based on the Miller-Rabin test. ";
    strHelp = strHelp.append("It returns 2, if the entered number is definitely prime, returns 1 if the entered number is probably prime, 0 if not.");
    a.help = strHelp;
    a.html = "prime";
    infos.insert("primality test", a);

    a.name = "Jacobi symbol";
    a.code =121;
    a.variables = 2;
    strHelp = "The Jacobi Symbol is the product of the Legendre Symbols <center>legSym(a,p<sub>1</sub>), &hellip;, legSym(a,p<sub>n</sub></i>),</center> where <i>b</i> has the prime factor decomposition";
    strHelp = strHelp.append("<center>b = p<sub>1</sub> &middot; &hellip; &middot; p<sub>n</sub>.</center>");
    a.help = strHelp;
    a.html = "jac";
    infos.insert("jacobi symbol", a);

    a.name = "Legendre symbol";
    a.code =121;
    a.variables = 2;
    strHelp = "The Legendre symbol is <i>0</i>, if <i>a</i> is divisible by <i>b</i>, <i>1</i>, if <i>a</i> is a square mod <i>b</i>, and <i>-1</i> otherwise, if <i>b</i> is a prime number.";
    strHelp = strHelp.append("");
    a.help = strHelp;
    a.html = "legSym";
    infos.insert("legendre symbol", a);

    a.name = "Lucas number";
    a.code =121;
    a.variables = 1;
    strHelp = "The Lucas numbers are a sequence of positive integers. ";
    strHelp = strHelp.append("The Lucas number <i>f<sub>0</sub></i> is <i>2</i> and <i>f<sub>1</sub></i> is 1. ");
    strHelp = strHelp.append("All further Lucas numbers <i>f<sub>n</sub></i> are defined by the rule");
    strHelp = strHelp.append("<div align=\"center\"><span class=\"nowrap\">f<sub>n</sub> = f<sub>n-1</sub>+f<sub>n-2</sub>.</span></div>");
    a.help = strHelp;
    a.html = "luc";
    infos.insert("lucas number", a);

    help =QString((QChar)0x03B6);
    help = help.append(" (Riemann zeta function)");
    a.name = help;
    a.code =122;
    a.variables = 1;
    strHelp = "The Riemann Zeta Function &zeta; is defined by the infinite series:";
    strHelp = strHelp.append("<center>&zeta;(z) = 1+(1/2)<sup>z</sup>+(1/3)<sup>z</sup>+(1/4)<sup>z</sup>+&hellip;</center>");
    a.help = strHelp;
    a.html = "zeta";
    infos.insert("zeta", a);

    return infos;
}

QMap<QString,fctnData> combinatorics::get_map(){
    QMap<QString,fctnData> infos;
    QString strHelp, help;
    fctnData a;

    a.name = "Bernoulli distribution";
    a.code =131;
    a.variables = 2;
    a.help = "The Bernoulli Distribution describes a single experiment like the toss of a coin. Thus all functions for this ";
    a.help = a.help.append("distribution are only defined for <i>x=0</i> (failure) and <i>x=1</i> (success). The probability ");
    a.help = a.help.append("of success must be selected by <i>a</i> in the range from <i>0</i> to <i>1</i>.");
    a.html = "berd";
    infos.insert("bernoulli distribution", a);

    a.name = "beta distribution";
    a.code =131;
    a.variables = 3;
    strHelp = "The Beta Distribution is a family of continuous distributions. It is parametrized by the ";
    strHelp = strHelp.append("two positive shape parameters <i>a</i> and <i>b</i>. ");
    strHelp = strHelp.append("Its pdf is defined on <i>[0,1]</i> by using the beta function <i>B</i>:<center>f(x;a,b)=(1/B(a,b))x<sup>a-1</sup>(1-x)<sup>b-1</sup></center>");
    a.help = strHelp;
    a.html = "betd";
    infos.insert("beta distribution", a);

    a.name = "binomial distribution";
    a.code =131;
    a.variables = 3;
    a.help = "The Binomial Distribution is a discrete distribution. It describes number of successes <i>x</i> in a sequence of <i>n</i> independent experiments with probability <i>p</i>.";
    a.html = "bind";
    infos.insert("binomial distribution", a);

    a.name = "Cauchy-Lorentz distribution";
    a.code =131;
    a.variables = 3;
    strHelp = "The Cauchy Distribution also known as the Cauchy-Lorentz distribution or Lorentz distribution is a continuous distribution. ";
    strHelp = strHelp.append("Its probability density function is given by <center>f(x;x<sub>0</sub>,&gamma;) = &gamma;/(&pi;((x-x<sub>0</sub>)<sup>2</sup>+&gamma;<sup>2</sup>)).</center>");
    strHelp = strHelp.append("For <i>x<sub>0</sub>=0</i> and <i>&gamma;=1</i> its cdf has the shape of the arctan function.<br> Many properties implemented for other distributions are not defined for the Cauchy Distribution.");
    a.help = strHelp;
    a.html = "caud";
    infos.insert("cauchy distribution", a);

    a.name = "chi squared distribution";
    a.code =131;
    a.variables = 2;
    strHelp = "The Chi Squared distribution is a family of continuous distributions parametrized by one parameter <i>a</i>. If <i>a</i> is chosen to ";
    strHelp = strHelp.append("be a positive integer, the sum of squares of <i>a</i> independent standard normal variables is distributed according to the Chi Squared Distribution.");
    a.help = strHelp;
    a.html = "chid";
    infos.insert("chi squared distribution", a);

    a.name = "exponential distribution";
    a.code =131;
    a.variables = 2;
    a.help = "The Exponential Distribution is a continuous distribution. It has the pdf<center>f(x;a)=a&middot;exp(-ax).</center>";
    a.html = "expd";
    infos.insert("exponential distribution", a);

    a.name = "extreme value distribution";
    a.code =131;
    a.variables = 3;
    strHelp = "The currently implemented Extreme Value Distribution is a Fisher-Tippett distribution. Extreme value distributions describe as the name implies the occurrence of rare extreme values or events ";
    strHelp = strHelp.append("like 100-year floods. The pdf of the implemented extreme value distribution is given by");
    strHelp = strHelp.append("<center>f(x;loc,scale) <br>= 1/scale &middot; exp(-(x-loc)/scale)<br>&middot; exp(-exp(-(x-loc)/scale)).</center>");
    a.help = strHelp;
    a.html = "extd";
    infos.insert("extreme distribution", a);

    a.name = "Fisher F distribution";
    a.code =131;
    a.variables = 3;
    strHelp = "The Fisher F distribution is a continuous distribution. It arises by testing two samples with the same variance. It has the the following pdf defined by the Beta function <i>B</i>:";
    strHelp = strHelp.append("<center>f(x;a,b)</center><center>= b<sup>b/2</sup>a<sup>a/2</sup>x<sup>a/2-1</sup>/[(b+ax)<sup>(a+b)/2</sup>B(a/2,b/2)]</center>");
    a.help = strHelp;
    a.html = "fisd";
    infos.insert("f distribution", a);

    a.name = "gamma distribution";
    a.code =131;
    a.variables = 3;
    strHelp = "The Gamma or Erlang Distribution is a family of continuous distributions parametrized by the shape parameter <i>k</i> ";
    strHelp = strHelp.append("and the scale parameter <i>&theta;</i>. Its pdf is defined by using the Gamma function &Gamma;");
    strHelp = strHelp.append("<center>f(x;k,&theta;) = x<sup>k-1</sup>&middot;exp(-x/&theta;)/&theta;<sup>k</sup>&Gamma;(k).</center>");
    a.help = strHelp;
    a.html = "gamd";
    infos.insert("gamma distribution", a);

    a.name = "hypergeometric distribution";
    a.code =131;
    a.variables = 4;
    strHelp = "The Hypergeometric Distribution describes the number of \"events\" <i>k</i> from a sample <i>n</i> drawn from a total population <i>N</i> without replacement.";
    a.help = strHelp;
    a.html = "hypd";
    infos.insert("hypergeometric distribution", a);

    a.name = "log normal distribution";
    a.code =131;
    a.variables = 3;
    strHelp = "The Log Normal Distribution is a family of continuous distributions. It arises when the logarithm of the random variable is normally distributed. ";
    strHelp = strHelp.append("Moreover it arises if the variable is a product of many independent identically  distributed variables. Its pdf is given by");
    strHelp = strHelp.append("<center>f(x;loc,scale) = 1/(x&middot;scale&radic;(2&pi;))exp(-(ln(x)-loc)<sup>2</sup>/2&middot;scale<sup>2</sup>).</center>");
    a.help = strHelp;
    a.html = "logd";
    infos.insert("log distribution", a);

    a.name = "negative binomial distribution";
    a.code =131;
    a.variables = 3;
    a.help = "The Negative Binomial Distribution is a discrete distribution. It describes the probability of <i>x</i> failures and <i>n</i> successes with success in the last trial in <i>x+n</i> independent experiments with success probability <i>p</i>.";
    a.html = "negd";
    infos.insert("negative distribution", a);

    a.name = "normal (Gaussian) distribution";
    a.code =131;
    a.variables = 3;
    strHelp= "The Normal Distribution also known as Gauss Distribution is a continuous distribution. Its pdf has the shape ";
    strHelp = strHelp.append("of a bell and is given by<center>f(x;&mu;,&sigma;)=1/(&sigma;&radic;(2&pi;)) &middot; exp(-(x-&mu;)<sup>2</sup>/(2&sigma;<sup>2</sup>)).</center>");
    a.help = strHelp;
    a.html = "nord";
    infos.insert("normal distribution", a);

    a.name = "Pareto distribution";
    a.code =131;
    a.variables = 3;
    strHelp = "The Pareto Distribution is a continuous distribution. It describes differences of sizes like for example different wealth of the population. ";
    strHelp = strHelp.append("Its pdf is given by <center>f(x;a,b) = ab<sup>a</sup>/x<sup>a+1</sup></center>.");
    a.help = strHelp;
    a.html = "pard";
    infos.insert("pareto distribution", a);

    a.name = "Poisson distribution";
    a.code =131;
    a.variables = 2;
    a.help = "The Poisson Distribution is a discrete distribution. It describes the probability of the occurrence of <i>x</i> events, which occur with a known mean rate <i>a</i> during a fixed period of time.";
    a.html = "poid";
    infos.insert("poisson distribution", a);

    a.name = "Rayleigh distribution";
    a.code =131;
    a.variables = 2;
    a.help = "The Rayleigh Distribution is a continuous distribution. Its pdf is given by<center>f(x;a)=x&middot;exp(-x<sup>2</sup>/2 a<sup>2</sup>)/a<sup>2</sup>.</center>";
    a.html = "rayd";
    infos.insert("rayleigh distribution", a);

    a.name = "Students T distribution";
    a.code =131;
    a.variables = 2;
    a.help = "The Students T Distribution is a continuous distribution. Its pdf is defined by using the Gamma function &Gamma;<center>f(x;a)</center><center>=&Gamma;((a+1)/2)/[&radic;(a&pi;)&Gamma;(a/2)(1+x<sup>2</sup>/a)<sup>(a+1)/2</sup>].</center>";
    a.html = "stud";
    infos.insert("t distribution", a);

    a.name = "triangular distribution";
    a.code =131;
    a.variables = 4;
    strHelp ="The name of the Triangular Distribution defined for <i>a</i> less than <i>b</i> and <i>b</i> less than c</i> is motivated of the triangular shape of its pdf. For <i>x</i> less than <i>a</i> or <i>x</i> larger than <i>c</i> it is constantly <i>0</i>. ";
    strHelp = strHelp.append("Moreover the pdf increases linearly between <i>a</i> and <i>b</i> and decreases linearly between <i>b</i> and <i>c</i>.");
    a.help = strHelp;
    a.html = "trid";
    infos.insert("triangular distribution", a);

    a.name = "Weibull distribution";
    a.code =131;
    a.variables = 3;
    strHelp = "The Weibull distribution is a continuous distribution. It is often used for failure analysis. It has the pdf";
    strHelp = strHelp.append("<center>f(x;a,b) = (a/b)&middot;(x/b)<sup>a-1</sup>&middot;exp(-(x/b)<sup>a</sup>).</center>");
    a.help = strHelp;
    a.html = "weid";
    infos.insert("weibull distribution", a);

    a.name = "uniform distribution";
    a.code =131;
    a.variables = 3;
    a.help = "The pdf of the Uniform Distribution is constant and larger than <i>0</i> between <i>a</i> and <i>b</i> and vanishes elsewhere.";
    a.html = "unid";
    infos.insert("uniform distribution", a);

    a.name = "geometric distribution";
    a.code =131;
    a.variables = 2;
    a.help = "The Geometric Distribution is a continuous distribution. It describes the probability of the number of failures before first success with respect to the fixed success fraction <i>a</i>.";
    a.html = "geod";
    infos.insert("geometric distribution", a);

    a.name = "Laplace distribution";
    a.code =131;
    a.variables = 3;
    a.help = "The Laplace Distribution is a continuous distribution. It has the pdf";
    a.help = a.help.append("<center>f(x;&mu;,&sigma;) = (1/2&sigma;)&middot;exp(-|x-&mu;|/&sigma;).</center>");
    a.html = "lapd";
    infos.insert("laplace distribution", a);

    a.name = "logistic distribution";
    a.code =131;
    a.variables = 3;
    a.help = "The Logistic Distribution is a continuous distribution. Its cdf is the Logistic Function, which appears in logistic regression and neural networks.";
    a.html = "lgsd";
    infos.insert("logistic distribution", a);

    return infos;
}

QMap<QString,fctnData> logics::get_map(){
    QMap<QString,fctnData> infos;
    fctnData a;

    a.name = "==";
    a.code =150;
    a.variables = 2;
    a.help = "The operation == returns 1 (true) if the first argument is equal to the second one and it returns 0 (false) otherwise.";
    a.html = "==";
    infos.insert("==", a);

    a.name = "<=";
    a.code =153;
    a.variables = 2;
    a.help = "The operation &lt;= returns 1 (true) if the first argument is smaller than the second one or equal to the second one and it returns 0 (false) otherwise.";
    a.html = "<=";
    infos.insert("<=", a);

    a.name = ">=";
    a.code =153;
    a.variables = 2;
    a.help = "The operation &gt;= returns 1 (true) if the first argument is larger than the second one or equal to the second one and it returns 0 (false) otherwise.";
    a.html = ">=";
    infos.insert(">=", a);

    a.name = "!=";
    a.code =150;
    a.variables = 2;
    a.help = "The operation != returns 1 (true) if the both arguments are not equal and it returns 0 (false) otherwise.";
    a.html = "!=";
    infos.insert("!=", a);

    a.name = "<";
    a.code =153;
    a.variables = 2;
    a.help = "The operation &lt; returns 1 (true) if the first argument is smaller than the second one and it returns 0 (false) otherwise.";
    a.html = "<";
    infos.insert("<", a);

    a.name = ">";
    a.code =153;
    a.variables = 2;
    a.help = "The operation &gt; returns 1 (true) if the first argument is larger than the second one and it returns 0 (false) otherwise.";
    a.html = ">";
    infos.insert(">", a);

    a.name = "AND";
    a.code =152;
    a.variables = 2;
    a.help = "The operation AND returns 1 (true) if both of the arguments are true and it returns 0 (false) otherwise.";
    a.html = "AND";
    infos.insert("and", a);

    a.name = "OR";
    a.code =152;
    a.variables = 2;
    a.help = "The operation OR returns 1 (true) if one of the arguments is true and it returns 0 (false) otherwise.";
    a.html = "OR";
    infos.insert("or", a);

    a.name = "NOR";
    a.code =152;
    a.variables = 2;
    a.help = "The operation OR returns 1 (true) if both of the arguments are false and it returns 0 (false) otherwise.";
    a.html = "NOR";
    infos.insert("nor", a);

    a.name = "NOT";
    a.code =152;
    a.variables = 1;
    a.help = "The operation NOT returns 1 (true) if the argument is false and it returns 0 (false) otherwise.";
    a.html = "NOT";
    infos.insert("not", a);

    a.name = "XOR";
    a.code =152;
    a.variables = 2;
    a.help = "The operation XOR returns 1 (true) if one of the arguments is true and the other one is false and it returns 0 (false) otherwise.";
    a.html = "XOR";
    infos.insert("xor", a);

    a.name = "assignment operator ( = )";
    a.code =154;
    a.variables = 2;
    a.help = "The assignment operator stores a variable with the selected name and the selected value. A variable can be of each type, which is used by MACE. ";
    a.help = a.help.append("You can use this variable by inserting the name and overwrite the value by using the assigment operator again whenever you like. Just write <center>\"<i>variableName</i>=<i>variableValue</i>\".</center>");
    a.help = a.help.append("Of course the name of a variable cannot be a number or a polynomial. ");
    a.help = a.help.append("This includes that <i>i</i> cannot be the name of a variable, since <i>i</i> denotes an imaginary number. Moreover <i>x</i> ");
    a.help = a.help.append("is a monomial and can also not be the name of a variable.<br>");
    a.html = "=";
    infos.insert("assignment", a);

    a.name = "IF";
    a.code =151;
    a.variables = 3;
    a.help = "The function IF returns the second argument, if the first is true, and the third one otherwise.";
    a.html = "IF";
    infos.insert("if", a);

    a.name = "init";
    a.code =155;
    a.variables = 2;
    a.help = "The Function Init generates a variable with the selected name and the selected value, if a variable with this name does not already exist.";
    a.help = a.help.append(" Otherwise this function does not do anything.");
    a.html = "init";
    infos.insert("init", a);

    a.name = "delete";
    a.code =155;
    a.variables = 1;
    a.help = "The Function Delete deletes the variable with the selected name, if such a variable exists.";
    a.help = a.help.append(" Otherwise this function does not do anything.");
    a.html = "delete";
    infos.insert("delete", a);

    a.name = "execute";
    a.code =155;
    a.variables = 3;
    a.help = "The Function Execute executes a script written in the selected txt-file with the selected input and output parameters. The number of input and output parameters is optional at your choice.";
    a.help = a.help.append(" If there are more than one input or output paramaters the input or output parameters have to be seperated by commas.");
    a.html = "execute";
    infos.insert("execute", a);

    a.name = "record";
    a.code =155;
    a.variables = 4;
    a.help = "The Function Record executes a script written in the selected txt-file with the selected input and output parameters. The number of input and output parameters is optional at your choice.";
    a.help = a.help.append(" The datas of a script are stored, can be read by <i>record name</i>-><i>variable name</i> and reused for a later sub-script by using record again. ");
    a.help = a.help.append("If there are more than one input or output paramaters the input or output parameters have to be seperated by commas.");
    a.html = "record";
    infos.insert("record", a);

    a.name = "saveAs";
    a.code =155;
    a.variables = 1;
    a.help = "The Function SaveAs saves your computations as a html-file.";
    a.html = "saveAs";
    infos.insert("saveAs", a);

    a.name = "open";
    a.code =155;
    a.variables = 1;
    a.help = "The Function Open opens previous computations from a html-file.";
    a.html = "open";
    infos.insert("open", a);

    a.name = "plot";
    a.code =155;
    a.variables = 1;
    a.help = "The Function Plot allows you to plot up to 7 real functions in the variable <i>x</i>. These functions have to be separated by commas.";
    a.html = "plot";
    infos.insert("plot", a);

    a.name = "cplxPlot";
    a.code =155;
    a.variables = 1;
    a.help = "The Function CplxPlot allows you to plot a complex function in the variable <i>x</i>.";
    a.html = "cplxPlot";
    infos.insert("cplxPlot", a);

    a.name = "setCharacteristic";
    a.code =155;
    a.variables = 1;
    a.help = "The Function SetCharacteristic allows you to select the characteristic.";
    a.html = "setCharacteristic";
    infos.insert("setCharacteristic", a);

    a.name = "setPrecision";
    a.code =155;
    a.variables = 1;
    a.help = "The Function setPrecision allows you to select the setPrecision of the output. The precision must be an integer from 2 to 16.";
    a.html = "setPrecision";
    infos.insert("setPrecision", a);

    a.name = "function";
    a.code =155;
    a.variables = 1;
    a.help = "The Function Func switches to the grammar settings of the complex plotter. The argument of func is parsed as a complex function.";
    a.html = "func";
    infos.insert("function", a);

    a.name = "string";
    a.code =155;
    a.variables = 1;
    a.help = "This Function allows you to insert a text string.";
    a.html = "<i>your text</i>";
    infos.insert("string", a);

    a.name = "deleteRecord";
    a.code =155;
    a.variables = 1;
    a.help = "The Function Delete deletes the record with the selected name, if such a record exists.";
    a.html = "deleteRecord";
    infos.insert("deleteRecord", a);

    return infos;
}

QMap<QString,fctnData> linearAlgebra::get_map(){
    QMap<QString,fctnData> infos;
    QString strHelp;
    fctnData a;

    a.name = "write a matrix";
    a.code =140;
    a.variables = 1;
    a.help = "This function stores a matrix for arithmetic operations (<i>+, -, *</i>) with another matrix.";
    a.html = "writeMatrix";
    infos.insert("write a matrix", a);

    a.name = "+ for matrices";
    a.code =140;
    a.variables = 2;
    a.help = "This function allows you to add two matrices.";
    a.html = "+";
    infos.insert("+ for matrices", a);

    a.name = "- for matrices";
    a.code =140;
    a.variables = 2;
    a.help = "This function allows you to subtract matrices.";
    a.html = "-";
    infos.insert("- for matrices", a);

    a.name = "* for matrices";
    a.code =140;
    a.variables = 2;
    a.help = "This function allows you to multiply two matrices.";
    a.html = "*";
    infos.insert("* for matrices", a);

    a.name = "/ for matrices";
    a.code =146;
    a.variables = 2;
    a.help = "This function allows you to multiply a matrix with the inverse of the second one.";
    a.html = "/";
    infos.insert("/ for matrices", a);


    a.name = "inverse matrix";
    a.code =141;
    a.variables = 1;
    strHelp = "The Inverse Matrix <span class=\"nowrap\"><i>M<sup>-1</sup></i></span> of an <span class=\"nowrap\"><i>n&times;n</i></span> ";
    strHelp = strHelp.append("matrix <i>M</i> satisfies the equation <center>M &middot; M<sup>-1</sup> = I<sub>n</sub>.</center>");
    strHelp = strHelp.append(" It is only defined, if <i>M</i> has maximal <a href=\"rank of a matrix\">rank</a> <i>n</i>.");
    a.help =strHelp;
    a.html = "inverse";
    infos.insert("inverse matrix", a);

    a.name = "determinant of a matrix";
    a.code =145;
    a.variables = 1;
    strHelp = "The Determinant det is an important function for matrices in linear algebra. It is the only function satisfying the following";
    strHelp = strHelp.append(" conditions:<ul type=\"bullet\"><li>linear with respect to each line and column of the matrix</li>");
    strHelp = strHelp.append("<li>antisymmetric: If two lines resp., columns coincide, det vanishes.</li>");
    strHelp = strHelp.append("<li><span class=\"nowrap\">det<i>(I<sub>n</sub>) = 1</i></span> for the ");
    strHelp = strHelp.append("<span class=\"nowrap\"><i>n&times;n</i></span> identity matrix <span class=\"nowrap\"><i>I<sub>n</sub>.</i></span></li></ul>");
    a.help = strHelp;
    a.html = "det";
    infos.insert("determinant of a matrix", a);

    a.name = "minimal polynomial of a matrix";
    a.code =144;
    a.variables = 1;
    a.help = "The Minimal Polynomial of a matrix <i>M</i> is the normalized polynomial <i>p</i> of smallest degree satisfying <i>p(M) = 0.</i>";
    a.html = "miniPoly";
    infos.insert("minimal polynomial of a matrix", a);

    a.name = "characteristic polynomial of a matrix";
    a.code =144;
    a.variables = 1;
    a.help = "The Characteristic Polynomial of an <i>n&times;n</i> matrix <i>M</i> is a normalized polynomial <i>p</i> of degree <i>n</i> satisfying <i>p(M) = 0.</i>";
    a.html = "charPoly";
    infos.insert("characteristic polynomial of a matrix", a);

    a.name = "eigenvalues of a matrix";
    a.code =144;
    a.variables = 1;
    a.help = "The eigenvalues of a matrix are zeros of its Characteristic Polynomial. For each eigenvalue &lambda; there exists a non-trivial sub-vector ";
    a.help = a.help.append("space on which the matrix acts by the multiplication with &lambda;.");
    a.html = "eigenvalue";
    infos.insert("eigenvalues of a matrix", a);

    a.name = "nullspace of a matrix";
    a.code =141;
    a.variables = 1;
    a.help = "The nullspace of a matrix is the kernel of the linear map represented by <i>M</i> with respect to the canonical basis.";
    a.html = "nullspace";
    infos.insert("nullspace of a matrix", a);

    a.name = "image of a matrix";
    a.code =141;
    a.variables = 1;
    a.help = "This function returns a matrix whose columns form a basis of the image of the linear map <i>x &rarr; M&middot;x</i> for the entered matrix <i>M</i>.";
    a.html = "image";
    infos.insert("image of a matrix", a);

    a.name = "rank of a matrix";
    a.code =144;
    a.variables = 1;
    strHelp = "The Rank of a matrix is the maximal number of linearly independent rows resp., columns of a matrix.";
    a.help = strHelp;
    a.html = "rank";
    infos.insert("rank of a matrix", a);

    a.name = "solve a system of linear equations";
    a.code =143;
    a.variables = 1;
    a.help = "This function solves a system of linear equations by using the <a href=\"Gauss algorithm for a matrix\">Gauss Algorithm</a>.";
    infos.insert("solve a system of linear equations", a);

    a.name = "Gauss algorithm for a matrix";
    a.code =141;
    a.variables = 1;
    strHelp = "The Gauss Algorithm transforms a matrix into an upper triangular matrix. The possible steps of this algorithm are";
    strHelp = strHelp.append("<ul type=\"bullet\"><li>interchanging lines</li><li>adding a line to another line</li><li>multiplying a line with a non-zero factor</li></ul>");
    strHelp = strHelp.append("The Gauss Algorithm plays a central role in Linear Algebra and has many applications. For example: Solving systems of linear equations, Computations of the Rank and the Determinant of a matrix.");
    a.help = strHelp;
    a.html = "gauss";
    infos.insert("gauss algorithm for a matrix", a);

    a.name = "transposed matrix";
    a.code =142;
    a.variables = 1;
    a.help = "This function transposes a matrix. That means, it interchanges the columns with the lines of a matrix.";
    a.html = "transpose";
    infos.insert("transposed matrix", a);

    a.name = "trace of a matrix";
    a.code =145;
    a.variables = 1;
    a.help = "The trace of a matrix the sum of the entries of the main diagonal of a matrix.";
    a.html = "trace";
    infos.insert("trace of a matrix", a);

    a.name = "conjugate (change of basis)";
    a.code =146;
    a.variables = 1;
    a.help = "This function is defined for two matrices <i>M</i> and <i>N</i> and returns the conjugate matrix ";
    a.help = a.help.append("<i>N<sup>-1</sup>&middot;M&middot;N</i>. First you enter <i>M</i> and then <i>N</i>. For the linear map represented");
    a.help = a.help.append(" by <i>M</i> with respect to the canonical basis one obtains a change of basis");
    a.help = a.help.append(" from the canonical basis to the basis given by the columns of <i>N</i>.");
    a.html = "conj";
    infos.insert("conjm", a);

    a.name = "Gram-Schmidt orthonormalization";
    a.code =147;
    a.variables = 1;
    a.help = "This is the Gram-Schmidt orthonormalization for the columns of a matrix. That means that the columns";
    a.help = a.help.append(" of the resulting matrix are are pair-wise orthonormal (there is a right angle between them) ");
    a.help = a.help.append("and that the columns have norm 1.0, if the columns are not zero.");
    a.html = "ortho";
    infos.insert("gram schmidt", a);

    a.name = "cross product of two vectors";
    a.code =140;
    a.variables = 1;
    a.help = "This function allows you to compute the cross product of two vectors in dimension 3.";
    a.html = "cross";
    infos.insert("cross product", a);

    a.name = "adjoint matrix";
    a.code =141;
    a.variables = 1;
    a.help = "The adjoint matrix <i>(a<sub>i,j</sub>)</i> of the n &times; n matrix <i>M</i> satisfies that the entry ";
    a.help = a.help.append("<i>a<sub>i,j</sub></i> in row <i>i</i> and column <i>j</i> is the determinant of the ");
    a.help = a.help.append("(n-1) &times; (n-1) matrix obtained from <i>M</i> by removing row <i>i</i> and column <i>j</i>.");
    a.html = "adjoint";
    infos.insert("adjoint matrix", a);

    a.name = "rows of a Matrix";
    a.code =144;
    a.variables = 1;
    a.help = "This function returns the number of rows of a matrix.";
    a.html = "rows";
    infos.insert("rows", a);

    a.name = "columns of a Matrix";
    a.code =144;
    a.variables = 1;
    a.help = "This function returns the number of columns of a matrix.";
    a.html = "columns";
    infos.insert("columns", a);

    a.name = "diagonal matrix";
    a.code =148;
    a.variables = 2;
    a.help = "The Function DiagMatrix generates a matrix with <i>n</i> rows and columns. The main diagonal is filled with entries of the selected value. All other entries are <i>0</i>.";
    a.html = "diagMatrix";
    infos.insert("diagMatrix", a);

    a.name = "zeroMatrix";
    a.code =148;
    a.variables = 2;
    a.help = "The Function ZeroMatrix generates a zero-matrix with the given number of rows and columns.";
    a.html = "zeroMatrix";
    infos.insert("zeroMatrix", a);

    a.name = "getEntry for matrices";
    a.code =148;
    a.variables = 3;
    a.help = "The Function getEntry allows you to get the entry of a matrix in the selected row and column.";
    a.html = "getEntry";
    infos.insert("getEntry", a);

    a.name = "setEntry for matrices";
    a.code =148;
    a.variables = 4;
    a.help = "The Function setEntry allows you to set the entry of a matrix in the selected row and column.";
    a.html = "setEntry";
    infos.insert("setEntry", a);

    a.name = "printMatrix";
    a.code =148;
    a.variables = 1;
    a.help = "The Function printMatrix prints a matrix into a string with the content \"matrix(<i>number of rows</i>,<i>number of columns</i>,(<i>list of entries</i>))\".";
    a.html = "printMatrix";
    infos.insert("printMatrix", a);

    return infos;
}

QMap<QString,fctnData> calculus::get_map(){
    QMap<QString,fctnData> infos;
    QString strHelp, help;
    fctnData a;

    a.name = "extrema";
    a.code =170;
    a.variables = 1;
    a.help = "The extrema are computed by finding the zeroes of the differential. It may appear that not all extrema are found. If no local extrema are found, it does not necessarily mean that the function does not have an local extreme value.";
    a.html = "extrema";
    infos.insert("extrema", a);

    a.name = "zeroes";
    a.code =170;
    a.variables = 1;
    a.help = "This function uses different numerical methods to find the zeroes of a function. If no zeroes are found, it does not necessarily mean that the function does not have a zero.";
    a.html = "zeroes";
    infos.insert("zeroes", a);

    a.name = "inflexion points";
    a.code =170;
    a.variables = 1;
    a.help = "The inflexion points are computed by finding the zeroes of the second dirivative. It may appear that not all inflexion points are found. If no inflexion points are found, it does not necessarily mean that the function does not have an inflexion point.";
    a.html = "inflexion";
    infos.insert("inflexion points", a);

    a.name = "normal";
    a.code =171;
    a.variables = 2;
    a.help = "The normal of a function is computed at a point <i>x<sub>0</sub></i>.";
    a.html = "normal";
    infos.insert("normal", a);

    a.name = "tangent";
    a.code =171;
    a.variables = 2;
    a.help = "The tangent of a function is computed at a point <i>x<sub>0</sub></i>.";
    a.html = "tangent";
    infos.insert("tangent", a);

    a.name = "derivative";
    a.code =173;
    a.variables = 1;
    a.help = "The derivative of a differentiable function is computed.";
    a.html = "derivative";
    infos.insert("derivative", a);

    a.name = "integral";
    a.code =174;
    a.variables = 3;
    a.help = "This computes the the numerical Simpson integral of a function over the intervall <i>[a,b]</i>. For this computation the interval is subdivided ";
    a.help = a.help.append("into intervals of maximal lenght 0.1. This leads to an estimated error less than 3.47223*10<sup>-8</sup>*(b-a)*f<sup>(4)</sup>(x) for some <i>x</i> between <i>a</i> and <i>b</i>. ");
    a.help = a.help.append("For a correct result you should make sure that the inserted function is defined over the intervall <i>[a,b]</i>.");
    a.html = "integral";
    infos.insert("integral", a);

    a.name = "symmetry";
    a.code =172;
    a.variables = 1;
    a.help = "If <i>1</i> is returned, the inserted function is even. If <i>-1</i> is returned, the inserted function is odd. If <i>0</i> is returned, no symmetry has been detected.";
    a.html = "symmetry";
    infos.insert("symmetry", a);

    a.name = "curve sketching";
    a.code =175;
    a.variables = 1;
    a.help = "Insert a function in the variable <i>x</i>. This function calls the functions symmetry, first, second and third derivative, zeroes, extrema, inflexion points and plots the inserted function.";
    a.html = "curve sketching";
    infos.insert("curve sketching", a);

    a.name = "period of a function";
    a.code =172;
    a.variables = 1;
    a.help = "This function yields the (real) period or a message, if the function does not have a (real) period.";
    a.html = "period";
    infos.insert("period", a);
    return infos;
}

QMap<QString,fctnData> controlFctn::get_map(){
    QMap<QString,fctnData> infos;
    QString strHelp, help;
    fctnData a;

    a.name = "callWriteInput";
    a.code =200;
    a.variables = 1;
    a.help = "Write the input for a variable in the script.";
    infos.insert("callWriteInput", a);

    return infos;
}
