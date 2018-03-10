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
        virtual float std_normal();
        virtual float uniform_float(float a, float b);
        virtual int uniform_int(int a, int b);
};

#endif
