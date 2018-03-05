
#include "Board.h"
#include "Tile.h"
#include "EnvFactor.h"
#include "Random.h"
#include "Logger.h"
#include "Fractal.h"
#include "Fragment.h"

Board::Board (Board* self, Random* random, Fractal* fractal, Logger* logger, int BOARD_SIZE, int N_ENV_FACTORS){
  assert(BOARD_SIZE > 0);
  assert(N_ENV_FACTORS > 0);
  assert(self != NULL);
  assert(random != NULL);

  this->BOARD_SIZE = BOARD_SIZE;
  this->N_ENV_FACTORS = N_ENV_FACTORS;
  this->random = random;
  this->fractal = fractal;
  this->logger = logger;

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
  // EnvFactor Initialization
  // =======================================
  this->envFactors = new EnvFactor*[this->N_ENV_FACTORS];
  for (int i = 0; i < this->N_ENV_FACTORS; i++){
    this->envFactors[i] = new EnvFactor(this->random, this->fractal, i, this->BOARD_SIZE, 0.8, 0.1);
  }

  // Write EnvFactor
  for (int i = 0; i < this->N_ENV_FACTORS; i++){
    logger->write_envFactor(this->envFactors[i]);
  }


  // =======================================
  // Fractal Initialization
  // =======================================
  this->fragment = new Fragment(this->random, this->fractal, this->BOARD_SIZE);
  logger->write_fragment(this->fragment);
}

Tile* Board::get_tile(int x, int y){
  // Remember, this->grid is padded by NULLs on all sides,
  // so, index must be adjusted so (x,y) actually maps to (x,y)
  int i = x + 1;
  int j = y + 1;

  return this->grid[i][j];
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
