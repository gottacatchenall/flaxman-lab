
#include "Fragment.h"
#include "Fractal.h"

Fragment::Fragment(Random* random, Fractal* fractal, int BOARD_SIZE){
  this->BOARD_SIZE = BOARD_SIZE;
  this->random = random;
  this->fractal = fractal;
  this->fragment_grid = this->create_fragment_map();
}

int** Fragment::create_fragment_map(){
  int** map = this->fractal->generate_fractal(0.1, .2);

  int total = (this->BOARD_SIZE) * (this->BOARD_SIZE);
  int c = this->count_zeros(map);
  float frac = float(c) / float(total);

  int total_its = 10;
  int it_count = 0;
  int** adj_map;

  // Based on a sample of running this alg 10,000 times, the average number of
  // iterations to reach a value between 0.3 and 0.4 was 3.8.
  // The max iteration value of 10 is reached only rarely, ~2.3% of the time. 

  while((frac < 0.3|| frac > 0.4) && it_count < total_its){
    adj_map = this->fractal->generate_fractal(0.1, 1);

    for (int i = 0; i < this->BOARD_SIZE; i++){
      for (int j = 0; j < this->BOARD_SIZE; j++){
        if (adj_map[i][j] == 0){
          if (frac < 0.3){
            map[i][j] = 0;
          }
          else if (frac > 0.4){
            map[i][j] = 1;
          }
        }
      }
    }

    c = this->count_zeros(map);
    frac = float(c) / float(total);
    free(adj_map);
    it_count++;
  }

  return map;
}

int Fragment::count_zeros(int **map){
  int c = 0;

  for (int i = 0; i < this->BOARD_SIZE; i++){
    for (int j = 0; j < this->BOARD_SIZE; j++){
      if (map[i][j] == 0){
        c++;
      }
    }
  }
  return c;
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
