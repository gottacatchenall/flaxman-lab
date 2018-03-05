
#ifndef TILE_H
#define TILE_H

#include <unordered_map>
#include "include.h"

class Individual;
class Board;

class Tile{
    private:
      int x;
      int y;
      int n_indiv;

      Board *parentBoard;

      // HASHTABLE of individuals on the tile.
      // KEY is the individual's id
      std::unordered_map<int, Individual*> indivs;
    public:
      Tile(int x, int y, Board *parentBoard);
      void callparentfunc();
};

#endif
