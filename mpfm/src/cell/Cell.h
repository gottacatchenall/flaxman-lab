
#ifndef CELL_H
#define CELL_H

#include <unordered_map>

class Individual;

class Cell{
    private:
      int x;
      int y;
      int n_indiv;

      // HASHTABLE of individuals in the cell.
      // KEY is the individuals id
      std::unordered_map<int, Individual*> indivs;
    public:
      Cell();
      void set_x(int x);
      void set_y(int y);
      int get_x();
      int get_y();


};

#endif
