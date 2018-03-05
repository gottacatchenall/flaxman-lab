
#include "Genome.h"

Genome::Genome(Individual* individual, Random* random){
  this->individual = individual;
  this->random = random;
}

Genome* Genome::mate(Genome* mate_genome){
  return mate_genome;
}

void Genome::crossing_over(Genome* a, Genome* b, Genome* result){

}
