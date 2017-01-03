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

#include "combicalc.h"

void combiCalc::findDist(bool *withInt, const std::string &str, dist &curDist, int &vars){
    *withInt = false;
    curDist = NONEDIST;

    if (str == "berd"){
        curDist = BERNOULLI;
        vars = 1;
        *withInt = true;
    }
    else if (str == "betd"){
        curDist = BETA;
        vars = 2;
    }
    else if (str == "bind"){
        curDist = BINO;
        vars = 2;
        *withInt = true;
    }
    else if (str == "caud"){
        curDist = CAUCHY;
        vars = 2;
    }
    else if (str == "chid"){
        curDist = CHI;
        vars = 1;
    }
    else if (str == "expd"){
        curDist = EXPO;
        vars = 1;
    }
    else if (str == "extd"){
        curDist = EXTREME;
        vars = 2;
    }
    else if (str == "fisd"){
        curDist = FISHER;
        vars = 2;
    }
    else if (str == "hypd"){
        curDist = HYPERGEO;
        vars = 3;
        *withInt = true;
    }
    else if (str == "gamd"){
        curDist = GAMMA;
        vars = 2;
    }
    else if (str == "geod"){
        curDist = GEO;
        vars = 1;
    }
    else if (str == "lapd"){
        curDist = LAPLACE;
        vars = 2;
    }
    else if (str == "logd"){
        curDist = LOGNORMAL;
        vars = 2;
    }
    else if (str == "lgsd"){
        curDist = LOGISTIC;
        vars = 2;
    }
    else if (str == "negd"){
        curDist = NEGATIVE;
        vars = 2;
        *withInt = true;
    }
    else if (str == "nord"){
        curDist = NORMAL;
        vars = 2;
    }
    else if (str == "pard"){
        curDist = PARETO;
        vars = 2;
    }
    else if (str == "poid"){
        curDist = POISSON;
        vars = 1;
        *withInt = true;
    }
    else if (str == "rayd"){
        curDist = RAYLEIGH;
        vars = 1;
    }
    else if (str == "stud"){
        curDist = STUDENT;
        vars = 1;
    }
    else if (str == "trid"){
        curDist = TRIANGULAR;
        vars = 3;
    }
    else if (str == "weid"){
        curDist = WEIBULL;
        vars = 2;
    }
    else if (str == "unid"){
        curDist = UNIFORM;
        vars = 2;
    }
}

combiCalc::fctn combiCalc::findFunc(std::string &str){
    fctn func = NONE;

    if (str == "pdf") func = PDF;
    else if (str == "cdf") func = CDF;
    else if (str == "haz") func = HAZARD;
    else if (str == "qua") func = QUANTILE;

    return func;
}

combiCalc::fctn combiCalc::findProperty(std::string &str){
    fctn func = NONE;

    if (str == "mean") func = MEAN;
    else if (str == "median") func = MEDIAN;
    else if (str == "mode") func = MODE;
    else if (str == "kurt") func = KURT;
    else if (str == "kurtEx") func = KURTEX;
    else if (str == "skew") func = SKEWNESS;
    else if (str == "stDev") func = STANDDEV;
    else if (str == "var") func = VARIANCE;

    return func;
}

double combiCalc::func1dist(bool *error, double a, double b, fctn func, dist curDist){
    double res = 0.0;

    try{
    if (curDist == CHI){
        boost::math::chi_squared_distribution<double> dist(a);
        if (func == PDF) res = pdf(dist,b);
        else if (func == CDF) res = cdf(dist,b);
        else if (func == HAZARD) res = hazard(dist,b);
        else if (func == QUANTILE) res = quantile(dist,b);
    }
    else if (curDist == EXPO){
        boost::math::exponential_distribution<double> dis(a);
        if (func == PDF)res = pdf(dis,b);
        else if (func == CDF) res = cdf(dis,b);
        else if (func == HAZARD) res = hazard(dis,b);
        else if (func == QUANTILE) *error = true;
    }
    else if (curDist == GEO){
        boost::math::geometric_distribution<double> dis(a);
        if (func == PDF)res = pdf(dis,b);
        else if (func == CDF) res = cdf(dis,b);
        else if (func == HAZARD) res = hazard(dis,b);
        else if (func == QUANTILE) *error = true;
    }
    else if (curDist == RAYLEIGH){
        boost::math::rayleigh_distribution<double> dist(a);
        if (func == PDF) res = pdf(dist,b);
        else if (func == CDF) res = cdf(dist,b);
        else if (func == HAZARD) res = hazard(dist,b);
        else if (func == QUANTILE) res = quantile(dist,b);
    }
    else if (curDist == STUDENT){
        boost::math::students_t_distribution<double> dist(a);
        if (func == PDF) res = pdf(dist,b);
        else if (func == CDF) res = cdf(dist,b);
        else if (func == HAZARD) res = hazard(dist,b);
        else if (func == QUANTILE) res = quantile(dist,b);

    }

    }
    catch ( ... ){
        *error = true;
    }
    return res;
}

double combiCalc::func2dist(bool *error, double a, double b, double c, fctn func, dist curDist){
    double res = 0.0;

    try{
        if (curDist == BETA){
            boost::math::beta_distribution<double> dist(a,b);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
         else if (curDist == CAUCHY){
            boost::math::cauchy_distribution<double> dist(a,b);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
        else if (curDist == EXTREME){
            boost::math::extreme_value_distribution<double> dist(a,b);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
        else if (curDist == FISHER){
            boost::math::fisher_f_distribution<double> dist(a,b);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
        else if (curDist == GAMMA){
            boost::math::gamma_distribution<double> dist(a,b);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
        else if (curDist == LAPLACE){
            boost::math::laplace_distribution<double> dist(a,b);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
        else if (curDist == LOGNORMAL){
            boost::math::lognormal_distribution<double> dist(a,b);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
        else if (curDist == LOGISTIC){
            boost::math::logistic_distribution<double> dist(a,b);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
        else if (curDist == NORMAL){
            boost::math::normal_distribution<double> dist(a,b);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
        else if (curDist == PARETO){
            boost::math::pareto_distribution<double> dist(b,a);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
        else if (curDist == WEIBULL){
            boost::math::weibull_distribution<double> dist(a,b);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
        else if (curDist == UNIFORM){
            boost::math::uniform_distribution<double> dist(a,b);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
    }
    catch ( ... ){
        *error = true;
    }
    return res;
}

double combiCalc::func3dist(bool *error, double a, double b, double c, double d, fctn func, dist curDist){
    double res = 0.0;

    try{
        if (curDist == TRIANGULAR){
            boost::math::triangular_distribution<double> dist(a,b,c);
            if (func == PDF) res = pdf(dist,d);
            else if (func == CDF) res = cdf(dist,d);
            else if (func == HAZARD) res = hazard(dist,d);
            else if (func == QUANTILE) res = quantile(dist,d);
        }
    }
    catch ( ... ){
        *error = true;
    }

    return res;
}

double combiCalc::func1intDist(bool *error, double a, unsigned int b, fctn func, dist curDist){
    double res = 0.0;

    try{
        if (curDist == BERNOULLI){
            boost::math::bernoulli_distribution<double> dist(a);
            if (func == PDF) res = pdf(dist,b);
            else if (func == CDF) res = cdf(dist,b);
            else if (func == HAZARD) res = hazard(dist,b);
            else if (func == QUANTILE) res = quantile(dist,b);
        }
        else if (curDist == POISSON){
            boost::math::poisson_distribution<double> dist(a);
            if (func == PDF) res = pdf(dist,b);
            else if (func == CDF) res = cdf(dist,b);
            else if (func == HAZARD) res = hazard(dist,b);
            else if (func == QUANTILE) res = quantile(dist,b);
        }
    }
    catch ( ... ){
        *error = true;
    }

    return res;
}

double combiCalc::func2intDist(bool *error, unsigned int a, double b, unsigned int c, fctn func, dist curDist){
    double res = 0.0;

    try{
        if (curDist == BINO){
            boost::math::binomial_distribution<double> dist(a,b);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
        else if (curDist == NEGATIVE){
            boost::math::negative_binomial_distribution<double> dist(a,b);
            if (func == PDF) res = pdf(dist,c);
            else if (func == CDF) res = cdf(dist,c);
            else if (func == HAZARD) res = hazard(dist,c);
            else if (func == QUANTILE) res = quantile(dist,c);
        }
    }
    catch ( ... ){
        *error = true;
    }

    return res;
}

double combiCalc::func3intDist(bool *error, unsigned int a, unsigned int b, unsigned int c, unsigned int d, fctn func, dist curDist){
    double res = 0.0;

    try{
        if (curDist == HYPERGEO){
            boost::math::hypergeometric_distribution<double> dist(a,b,c);
            if (func == PDF) res = pdf(dist,d);
            else if (func == CDF) res = cdf(dist,d);
            else if (func == HAZARD) res = hazard(dist,d);
            else if (func == QUANTILE) res = quantile(dist,d);
        }
    }
    catch ( ... ){
        *error = true;
    }

    return res;
}

//Here the properties start///////////////////////////////////////////////////////////

double combiCalc::prop1dist(bool *error, double a, fctn func, dist curDist){
    double res = 0.0;

    try{
    if (curDist == CHI){
        boost::math::chi_squared_distribution<double> dist(a);
        if (func == MEAN) res = mean(dist);
        else if (func == MEDIAN) res = median(dist);
        else if (func == MODE) res = mode(dist);
        else if (func == KURT) res = kurtosis(dist);
        else if (func == KURTEX) res = kurtosis_excess(dist);
        else if (func == STANDDEV) res = standard_deviation(dist);
        else if (func == SKEWNESS) res = skewness(dist);
        else if (func == VARIANCE) res = variance(dist);
    }
    else if (curDist == EXPO){
        boost::math::exponential_distribution<double> dist(a);
        if (func == MEAN) res = mean(dist);
        else if (func == MEDIAN) res = median(dist);
        else if (func == MODE) res = mode(dist);
        else if (func == KURT) res = kurtosis(dist);
        else if (func == KURTEX) res = kurtosis_excess(dist);
        else if (func == STANDDEV) res = standard_deviation(dist);
        else if (func == SKEWNESS) res = skewness(dist);
        else if (func == VARIANCE) res = variance(dist);
    }
    else if (curDist == GEO){
        boost::math::geometric_distribution<double> dist(a);
        if (func == MEAN) res = mean(dist);
        else if (func == MEDIAN) res = median(dist);
        else if (func == MODE) res = mode(dist);
        else if (func == KURT) res = kurtosis(dist);
        else if (func == KURTEX) res = kurtosis_excess(dist);
        else if (func == STANDDEV) res = standard_deviation(dist);
        else if (func == SKEWNESS) res = skewness(dist);
        else if (func == VARIANCE) res = variance(dist);
    }
    if (curDist == POISSON){
        boost::math::poisson_distribution<double> dist(a);
        if (func == MEAN) res = mean(dist);
        else if (func == MEDIAN) res = median(dist);
        else if (func == MODE) res = mode(dist);
        else if (func == KURT) res = kurtosis(dist);
        else if (func == KURTEX) res = kurtosis_excess(dist);
        else if (func == STANDDEV) res = standard_deviation(dist);
        else if (func == SKEWNESS) res = skewness(dist);
        else if (func == VARIANCE) res = variance(dist);
    }
    else if (curDist == RAYLEIGH){
        boost::math::rayleigh_distribution<double> dist(a);
        if (func == MEAN) res = mean(dist);
        else if (func == MEDIAN) res = median(dist);
        else if (func == MODE) res = mode(dist);
        else if (func == KURT) res = kurtosis(dist);
        else if (func == KURTEX) res = kurtosis_excess(dist);
        else if (func == STANDDEV) res = standard_deviation(dist);
        else if (func == SKEWNESS) res = skewness(dist);
        else if (func == VARIANCE) res = variance(dist);
    }
    else if (curDist == STUDENT){
        boost::math::students_t_distribution<double> dist(a);
        if (func == MEAN) res = mean(dist);
        else if (func == MEDIAN) res = median(dist);
        else if (func == MODE) res = mode(dist);
        else if (func == KURT) res = kurtosis(dist);
        else if (func == KURTEX) res = kurtosis_excess(dist);
        else if (func == STANDDEV) res = standard_deviation(dist);
        else if (func == SKEWNESS) res = skewness(dist);
        else if (func == VARIANCE) res = variance(dist);
    }
    else if (curDist == BERNOULLI){
        boost::math::bernoulli_distribution<double> dist(a);
        if (func == MEAN) res = mean(dist);
        else if (func == MEDIAN) res = median(dist);
        else if (func == MODE) res = mode(dist);
        else if (func == KURT) res = kurtosis(dist);
        else if (func == KURTEX) res = kurtosis_excess(dist);
        else if (func == STANDDEV) res = standard_deviation(dist);
        else if (func == SKEWNESS) res = skewness(dist);
        else if (func == VARIANCE) res = variance(dist);
    }

    }
    catch ( ... ){
        *error = true;
    }
    return res;
}

double combiCalc::prop2dist(bool *error, double a, double b, fctn func, dist curDist){
    double res = 0.0;

    try{
        if (curDist == BETA){
            boost::math::beta_distribution<double> dist(a,b);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
         else if (curDist == CAUCHY){
            boost::math::cauchy_distribution<double> dist(a,b);
            if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
        }
        else if (curDist == EXTREME){
            boost::math::extreme_value_distribution<double> dist(a,b);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
        else if (curDist == FISHER){
            boost::math::fisher_f_distribution<double> dist(a,b);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
        else if (curDist == GAMMA){
            boost::math::gamma_distribution<double> dist(a,b);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
        else if (curDist == LAPLACE){
            boost::math::laplace_distribution<double> dist(a,b);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
        else if (curDist == LOGISTIC){
            boost::math::logistic_distribution<double> dist(a,b);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
        else if (curDist == LOGNORMAL){
            boost::math::lognormal_distribution<double> dist(a,b);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
        else if (curDist == NORMAL){
            boost::math::normal_distribution<double> dist(a,b);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
        else if (curDist == PARETO){
            boost::math::pareto_distribution<double> dist(a,b);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
        else if (curDist == WEIBULL){
            boost::math::weibull_distribution<double> dist(a,b);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
        else if (curDist == UNIFORM){
            boost::math::uniform_distribution<double> dist(a,b);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }

    }
    catch ( ... ){
        *error = true;
    }
    return res;
}

double combiCalc::prop3dist(bool *error, double a, double b, double c, fctn func, dist curDist){
    double res = 0.0;

    try{
        if (curDist == TRIANGULAR){
            boost::math::triangular_distribution<double> dist(a,b,c);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
    }
    catch ( ... ){
        *error = true;
    }

    return res;
}

double combiCalc::prop1intDist(bool *error, unsigned int a, fctn func, dist curDist){
    double res = 0.0;

    try{
        if (curDist == POISSON){
            boost::math::poisson_distribution<double> dist(a);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
    }
    catch ( ... ){
        *error = true;
    }

    return res;
}

double combiCalc::prop2intDist(bool *error, unsigned int a, double b, fctn func, dist curDist){
    double res = 0.0;

    try{
        if (curDist == BINO){
            boost::math::binomial_distribution<double> dist(a,b);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
        else if (curDist == NEGATIVE){
            boost::math::negative_binomial_distribution<double> dist(a,b);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
    }
    catch ( ... ){
        *error = true;
    }

    return res;
}

double combiCalc::prop3intDist(bool *error, unsigned int a, unsigned int b, unsigned int c, fctn func, dist curDist){
    double res = 0.0;

    try{
        if (curDist == HYPERGEO){
            boost::math::hypergeometric_distribution<double> dist(a,b,c);
            if (func == MEAN) res = mean(dist);
            else if (func == MEDIAN) res = median(dist);
            else if (func == MODE) res = mode(dist);
            else if (func == KURT) res = kurtosis(dist);
            else if (func == KURTEX) res = kurtosis_excess(dist);
            else if (func == STANDDEV) res = standard_deviation(dist);
            else if (func == SKEWNESS) res = skewness(dist);
            else if (func == VARIANCE) res = variance(dist);
        }
    }
    catch ( ... ){
        *error = true;
    }

    return res;
}

QString DistDat::print(unsigned int precision) {
    QString res, help;
    StdStrToQStr(name,res);
    res = res.append("(");
    for (int i = 0; i< iDat.size(); i++) {
        help = help.number(iDat[i]);
        res = res.append(help);
        res = res.append(",");
    }
    for (int i = 0; i< dDat.size(); i++) {
        help = help.number(dDat[i],'g',precision);
        res = res.append(help);
        res = res.append(",");
    }
    res.chop(1);
    res = res.append(")");
    return res;
}

bool DistDat::prop(combiCalc &cc, numReal &nr, std::string &fctn) {
    double       d = 0.0;
    unsigned int i;
    bool         res = false;

    combiCalc::fctn fu = cc.findProperty(fctn);
    if (fu != combiCalc::NONE) {
        if(iDat.size() == 0) {
            if (dDat.size() == 1)
                d = cc.prop1dist(&res,dDat[0],fu,dist);
            if (dDat.size() == 2)
                d = cc.prop2dist(&res,dDat[0],dDat[1],fu,dist);
            if (dDat.size() == 3)
                d = cc.prop3dist(&res,dDat[0],dDat[1],dDat[2],fu,dist);
        } else {
            if (iDat.size() == 1 && dDat.size() == 0) {
                i = iDat[0];
                d = cc.prop1intDist(&res,i,fu,dist);
            }
            if (iDat.size() == 1 && dDat.size() == 1) {
                d = cc.prop2intDist(&res,iDat[0],dDat[0],fu,dist);
            }
            if (iDat.size() == 3) {
                d = cc.prop3intDist(&res,iDat[0],iDat[1],iDat[2],fu,dist);
            }
        }
    }
    else res = true;
    res = res || d != d;
    nr.set(d);
    return !res;
}
