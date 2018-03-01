
#include "Board.h"
#include "Tile.h"
#include "EnvFactor.h"
#include <random>

Board::Board (Board* self, int BOARD_SIZE, int N_ENV_FACTORS, int ENV_FACTOR_MODE){
  assert(BOARD_SIZE > 0);
  assert(N_ENV_FACTORS > 0);
  assert(self != NULL);

  this->BOARD_SIZE = BOARD_SIZE;
  this->N_ENV_FACTORS = N_ENV_FACTORS;
  this->ENV_FACTOR_MODE = ENV_FACTOR_MODE;

  // =======================================
  // Grid Initialization
  // =======================================

  // Initiallize Grid 2D-Array

  // Size is BOARD_SIZE+2 so entire thing is surrounded by NULLs to avoid
  // issues with indexing surrounding Tiles at edges or corner.

  this->grid = new Tile**[this->BOARD_SIZE+2];
  for (int i = 0; i < this->BOARD_SIZE+2; i++) {
    this->grid[i] = new Tile*[BOARD_SIZE+2];
  }

  // Initialize Edges to NULL
  int max_index = this->BOARD_SIZE+1;
  for (int i = 0; i < this->BOARD_SIZE+2; i++){
    this->grid[i][0] = NULL;
    this->grid[i][max_index] = NULL;
    this->grid[0][i] = NULL;
    this->grid[max_index][i] = NULL;
  }

  // Initiallize Tiles
  int x,y;
  for (int i = 1; i < this->BOARD_SIZE+1; i++){
    for (int j = 1; j < this->BOARD_SIZE+1; j++){
      // adjust indecies
      x = i - 1;
      y = j - 1;
      this->grid[i][j] = new Tile(x,y, self);
    }
  }

  // =======================================
  // EnvFactor Allocation
  // =======================================
  this->envFactors = new EnvFactor*[this->N_ENV_FACTORS];
}

Tile* Board::get_tile(int x, int y){
  // Remember, this->grid is padded by NULLs on all sides,
  // so, index must be adjusted so (x,y) actually maps to (x,y)
  int i = x + 1;
  int j = y + 1;

  return this->grid[i][j];
}


void Board::init_envFactors(){

  int** points = this->get_envFactor_points();

  int x,y;
  for (int i = 0; i < this->N_ENV_FACTORS; i++){
    x = points[i][0];
    y = points[i][1];
    this->envFactors[i] = new EnvFactor(i, x, y, this->BOARD_SIZE);
  }

  this->envFactors[3]->print_env_factor();
}

int** Board::get_envFactor_points(){
  // Initialize a 2d array of points with dimensions (N_ENV_FACTORS x 2)
  int** points = new int*[this->N_ENV_FACTORS];
  for (int i = 0; i < this->N_ENV_FACTORS; i++){
    points[i] = new int[2];
    points[i][0] = 0;
    points[i][1] = 0;
  }

  if(this->ENV_FACTOR_MODE == ENV_FACTOR_MODE_GRADIENT){

  }

  else if(this->ENV_FACTOR_MODE == ENV_FACTOR_MODE_NICHE){

  }

  else if(this->ENV_FACTOR_MODE == ENV_FACTOR_MODE_RANDOM){
    this->get_random_envFactor_points(points);
  }

  return points;
}

void Board::get_random_envFactor_points(int **points){
  std::default_random_engine generator;
  generator.seed(time(0));
  std::uniform_int_distribution<int> distribution(0,this->BOARD_SIZE);

  for (int i = 0; i < this->N_ENV_FACTORS; i++){
    points[i][0] = distribution(generator);
    points[i][1] = distribution(generator);
  }
}

void Board::allocate_individuals(){
    // TODO
}

void Board::migrate(){
    // TODO
}

void Board::next_gen(){
    // TODO
}
