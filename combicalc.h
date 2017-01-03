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

#ifndef COMBICALC_H
#define COMBICALC_H
#include "math/variables/scalar/maceint.h"
#include <QString>
#include <boost/math/distributions.hpp>
#include "math/variables/scalar/numreal.h"
#include "math/kernel/reader.h"


class combiCalc{
public:
    enum fctn{NONE, PDF, CDF, HAZARD, QUANTILE, MEAN, MEDIAN, MODE, KURT, KURTEX, SKEWNESS, STANDDEV, VARIANCE};
    enum dist{NONEDIST, BERNOULLI, EXPO, GAMMA, LAPLACE, LOGNORMAL, LOGISTIC, POISSON, RAYLEIGH, STUDENT, WEIBULL,
              UNIFORM, BETA, BINO, CAUCHY, CHI, EXTREME, FISHER, NEGATIVE, NORMAL, PARETO, TRIANGULAR, GEO, HYPERGEO};

    void findDist(bool *withInt, const std::string &str, dist &curDist, int &vars);
    fctn findFunc(std::string &str);
    fctn findProperty(std::string &str);

    double func1dist(bool *error, double a, double b, fctn func, dist curDist);
    double func2dist(bool *error, double a, double b, double c, fctn func, dist curDist);
    double func3dist(bool *error, double a, double b, double c, double d, fctn func, dist curDist);

    double func1intDist(bool *error, double a, unsigned int b, fctn func, dist curDist);
    double func2intDist(bool *error, unsigned int a, double b, unsigned int c, fctn func, dist curDist);
    double func3intDist(bool *error, unsigned int a, unsigned int b, unsigned int c, unsigned int d, fctn func, dist curDist);

    double prop1dist(bool *error, double a, fctn func, dist curDist);
    double prop2dist(bool *error, double a, double b, fctn func, dist curDist);
    double prop3dist(bool *error, double a, double b, double c, fctn func, dist curDist);

    double prop1intDist(bool *error, unsigned int a, fctn func, dist curDist);
    double prop2intDist(bool *error, unsigned int a, double b, fctn func, dist curDist);
    double prop3intDist(bool *error, unsigned int a, unsigned int b, unsigned int c, fctn func, dist curDist);
};

class DistDat: public MObject {
public:
    combiCalc::dist           dist;
    std::string               name;
    std::vector<double>       dDat;
    std::vector<unsigned int> iDat;

    DistDat() {dDat.clear(); iDat.clear();}

    virtual bool    isZero()                       {return (dDat.size() == 0 && iDat.size() == 0);}
    virtual QString print (unsigned int precision);

    bool prop(combiCalc &cc, numReal &nr, std::string &fctn);
};



#endif // COMBICALC_H
