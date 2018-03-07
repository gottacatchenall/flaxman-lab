
#include "EnvFactor.h"
#include "Random.h"
#include "Fractal.h"
#include "params_struct.h"

EnvFactor::EnvFactor(Random* random, Fractal* fractal, params_s* params, int index){
  assert(random != NULL);

  this->id = index;
  this->random = random;
  this->fractal = fractal;
  this->BOARD_SIZE = params->BOARD_SIZE;
  this->H_VALUE = params->ENV_FACTOR_H_VALUE;
  this->CUTOFF = params->ENV_FACTOR_CUTOFF;

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
