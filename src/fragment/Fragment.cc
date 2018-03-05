
#include "Fragment.h"
#include "Fractal.h"

Fragment::Fragment(Random* random, Fractal* fractal, int BOARD_SIZE){
  this->BOARD_SIZE = BOARD_SIZE;
  this->random = random;
  this->fractal = fractal;
  this->fragment_grid = this->fractal->generate_fractal(0, 0.2);
}

void Fragment::fragment_more(){

}

void Fragment::set_cell_value(int x, int y, int val){
  
}

int Fragment::get_cell_value(int x, int y){
  return this->fragment_grid[x][y];
}

int Fragment::get_board_size(){
  return this->BOARD_SIZE;
}
