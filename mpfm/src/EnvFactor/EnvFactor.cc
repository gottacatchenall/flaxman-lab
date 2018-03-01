
#include "EnvFactor.h"
#include <random>

EnvFactor::EnvFactor(int index, int x0, int y0, int BOARD_SIZE){
  this->id = index;
  this->x0 = x0;
  this->y0 = y0;
  this->BOARD_SIZE = BOARD_SIZE;

  // Initialize envFactor_grid

  // Size is BOARD_SIZE+2 so entire thing is surrounded by NULLs to avoid
  // issues with indexing surrounding Tiles at edges or corner.
  int n = this->BOARD_SIZE+2;

  this->envFactor_grid = new int*[n];
  for (int i = 0; i < n; i++){
    this->envFactor_grid[i] = new int[n];
  }

  // Init to 0s
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      this->envFactor_grid[i][j] = 0;
    }
  }

  // Generate the Theta Map
  this->run_random_walk();
}

void EnvFactor::run_random_walk(){
  double base_prob = ENV_FACTOR_MARKOV_GENERATION_BASE_PROB;
  int c;
  double rand_between_0and1;

  this->set_cell_value(this->x0, this->y0, 1);

  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0,1.0);

  int count = 0;
  for (int i = 0; i < this->BOARD_SIZE; i++){
    for (int j = 0; j < this->BOARD_SIZE; j++){
      c = this->count_surrounding_ones(i,j);
      rand_between_0and1 =  distribution(generator);
      //printf("RANDMAX: %d\n", RAND_MAX);
      //printf("rand: %f\n", rand_between_0and1);
      if (c > 5){
        this->set_cell_value(i,j, 1);
      }
      else{
        if (c == 0){
          c = 1;
        }
        if (rand_between_0and1 < c * base_prob){
          count++;
          this->set_cell_value(i,j, 1);
        }
      }
    }
  }
  printf("was true %d times\n", count);
}

int EnvFactor::count_surrounding_ones(int x, int y){
  int c = 0;

  if (this->get_cell_value(x+1,y+1) == 1){ c++; }
  if (this->get_cell_value(x+1,y) == 1){ c++; }
  if (this->get_cell_value(x+1,y-1) == 1){ c++; }
  if (this->get_cell_value(x,y+1) == 1){ c++; }
  if (this->get_cell_value(x,y-1) == 1){ c++; }
  if (this->get_cell_value(x-1,y+1) == 1){ c++; }
  if (this->get_cell_value(x-1,y) == 1){ c++; }
  if (this->get_cell_value(x-1,y-1) == 1){ c++; }

  return c;
}

void EnvFactor::set_cell_value(int x, int y, int val){
  // Because this->envFactor_grid is wrapped in 0s,
  // indecies have to be adjusted.
  int i = x + 1;
  int j = y + 1;

  this->envFactor_grid[i][j] = val;
}

int EnvFactor::get_cell_value(int x, int y){
  // Because this->envFactor_grid is wrapped in 0s,
  // indecies have to be adjusted.
  int i = x + 1;
  int j = y + 1;
  return this->envFactor_grid[i][j];
}

void EnvFactor::print_env_factor(){

  printf("ENV_FACTOR #%d\n\n", this->id);
  for (int j = this->BOARD_SIZE-1; j >= 0; j--){
    for (int i = 0; i < this->BOARD_SIZE; i++){
      printf("%d ", this->get_cell_value(i,j));
    }
    printf("\n");
  }

  printf("source: (%d, %d)\n", this->x0, this->y0);
}
