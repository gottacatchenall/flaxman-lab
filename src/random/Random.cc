#include "Random.h"

Random::Random(int random_seed){
    this->random_seed = random_seed;
    this->generator.seed(this->random_seed);
    this->std_normal_dist = std::normal_distribution<double>(0,1);
}

double Random::std_normal(){
    double val =  this->std_normal_dist(this->generator);
    return val;
}

int Random::uniform_int(int a, int b){
    std::uniform_int_distribution<int> dis(a,b);
    return dis(this->generator);
}

double Random::uniform_float(double a, double b){
    std::uniform_real_distribution<double> dis(a, b);
    return dis(this->generator);
}

double Random::beta(double alpha, double beta){
    std::gamma_distribution<double> dis1(alpha, 1);
    std::gamma_distribution<double> dis2(beta, 1);

    double x1 = dis1(this->generator);
    double x2 = dis2(this->generator);

    double res = double(x1)/double(x1+x2);
    return res;
}
