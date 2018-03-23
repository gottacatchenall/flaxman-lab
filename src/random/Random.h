#ifndef RANDOM_H
#define RANDOM_H

#include "include.h"
#include <random>

class Random{
    private:
        int random_seed;
        std::mt19937 generator;
        //double std_normal_gen;
        std::normal_distribution<double> std_normal_dist;
    public:
        Random(int random_seed);
        double std_normal();
        double normal(double mu, double sigma);
        double uniform_float(double a, double b);
        int uniform_int(int a, int b);
        double beta(double alpha, double beta);
};

#endif
