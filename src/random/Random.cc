#include "Random.h"
#include "TimeTracker.h"
#include "params_struct.h"

Random::Random(int random_seed){
    this->random_seed = random_seed;
    this->generator.seed(this->random_seed);
    this->std_normal_dist = std::normal_distribution<double>(0,1);
    this->n_offspring_dist = std::poisson_distribution<int>(params->AVG_NUM_OFFSPRING_PER_FEMALE);
    this->n_crossover_events_dist = std::poisson_distribution<int>(params->GENOME_LENGTH_IN_CENTIMORGANS);
}

double Random::std_normal(){
    double val =  this->std_normal_dist(this->generator);
    return val;
}

double Random::normal(double mu, double sigma){
    std::normal_distribution<double> dis(mu, sigma);
    return dis(this->generator);
}

int Random::uniform_int(int a, int b){
    std::uniform_int_distribution<int> dis(a,b);
    return dis(this->generator);
}

double Random::uniform_float(double a, double b){
    std::uniform_real_distribution<double> dis(a, b);
    return dis(this->generator);
}

int Random::n_offspring(){
    double start_time = time_tracker->get_start_time();
    int val = this->n_offspring_dist(this->generator);
    time_tracker->add_time_in_random(start_time);
    return val;
}

int Random::n_crossover_events(){
    double start_time = time_tracker->get_start_time();
    int val = this->n_crossover_events_dist(this->generator);
    time_tracker->add_time_in_random(start_time);
    return val;
}

double Random::beta(double alpha, double beta){
    std::gamma_distribution<double> dis1(alpha, 1);
    std::gamma_distribution<double> dis2(beta, 1);

    double x1 = dis1(this->generator);
    double x2 = dis2(this->generator);

    double res = double(x1)/double(x1+x2);
    return res;
}
