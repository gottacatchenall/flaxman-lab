#include "Cell.h"

Cell::Cell(){
  this->n_indiv = 0;
}

void Cell::set_x(int x){
  this->x = x;
}

void Cell::set_y(int y){
  this->y = y;
}

int Cell::get_x(){
  return this->x;
}

int Cell::get_y(){
  return this->y;
}
