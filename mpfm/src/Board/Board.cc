
#include "Board.h"

Board::Board (int BOARD_SIZE, int N_ENV_FACTORS){
  assert(BOARD_SIZE > 0);
  assert(N_ENV_FACTORS > 0);

  this->BOARD_SIZE = BOARD_SIZE;
  this->N_ENV_FACTORS = N_ENV_FACTORS;

  // Initialize Environmental Factors
  this->envFactors = vec_envFactor(N_ENV_FACTORS);
}

void Board::set_address(Board* addr){
  this->self_addr = addr;
}

void Board::init_cells(){
  // Initialize Cells
  this->grid = matrix(this->BOARD_SIZE, std::vector<Cell>(this->BOARD_SIZE));
  for (int i = 0; i < this->BOARD_SIZE; i++){
    for (int j = 0; j < this->BOARD_SIZE; j++){
      this->grid[i][j].set_x(i);
      this->grid[i][j].set_y(j);
      this->grid[i][j].set_parent_board(this->self_addr);
    }
  }
}

void Board::print_hello(){
  printf("hello from board!\n");
}

void Board::init_envFactors(){

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
