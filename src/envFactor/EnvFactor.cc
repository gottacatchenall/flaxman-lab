
#include "EnvFactor.h"
#include "Random.h"
#include "Fractal.h"

EnvFactor::EnvFactor(Random* random, Fractal* fractal, int index, int BOARD_SIZE, double H_VALUE, double CUTOFF){
  assert(random != NULL);

  this->id = index;
  this->BOARD_SIZE = BOARD_SIZE;
  this->random = random;
  this->fractal = fractal;
  this->H_VALUE = H_VALUE;
  this->CUTOFF = CUTOFF;

  // Generate the Theta Map
  this->envFactor_grid = this->fractal->generate_fractal(this->H_VALUE, this->CUTOFF);
}

int EnvFactor::get_cell_value(int x, int y){
  return this->envFactor_grid[x][y];
}

void EnvFactor::set_cell_value(int x, int y, int val){
  this->envFactor_grid[x][y] = val;
}

int EnvFactor::get_id(){
  return this->id;
}

int EnvFactor::get_board_size(){
  return this->BOARD_SIZE;
}
