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
    float std_normal();
    float uniform_float(int a, int b);
    int uniform_int(int a, int b);
};

#endif
