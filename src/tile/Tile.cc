#include "Tile.h"
#include "Board.h"

Tile::Tile(int x, int y, Board* parentBoard){
  this->n_indiv = 0;
  this->x = x;
  this->y = y;
  this->parentBoard = parentBoard;
}

void Tile::callparentfunc(){
}
