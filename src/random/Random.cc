#include "Random.h"

Random::Random(int random_seed){
  this->random_seed = random_seed;
  this->generator.seed(this->random_seed);
  this->std_normal_dist = std::normal_distribution<double>(0,1);
}

float Random::std_normal(){
  float val =  this->std_normal_dist(this->generator);
  return val;
}
