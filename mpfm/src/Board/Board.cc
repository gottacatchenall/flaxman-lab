
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
  for (int i = 0; i < this->N_ENV_FACTORS; i++){
    this->envFactors[i] = new EnvFactor(i, this->BOARD_SIZE);
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
