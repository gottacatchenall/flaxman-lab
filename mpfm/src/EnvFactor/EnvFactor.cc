
#include "EnvFactor.h"
#include "Random.h"

EnvFactor::EnvFactor(Random* random, int index, int BOARD_SIZE){
  assert(random != NULL);

  this->id = index;
  this->BOARD_SIZE = BOARD_SIZE;
  this->random = random;

  /*
  // DEBUG
  double xf = this->random->std_normal();
  printf("envFactor: %d, xf: %f\n", this->id, xf);
  return;
  // END DEBUG
  */

  // Initialize envFactor_grid
  int n = this->BOARD_SIZE;

  this->envFactor_grid = new int*[n];
  for (int i = 0; i < n; i++){
    this->envFactor_grid[i] = new int[n];
  }

  // Init to 0s
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      this->envFactor_grid[i][j] = 0;
    }
  }

  // Generate the Theta Map
  this->generate_fractal();
}

void EnvFactor::generate_fractal(){
  float X[this->BOARD_SIZE+1][this->BOARD_SIZE+1];

  int delta = 1;
  int N = this->BOARD_SIZE;
  int maxlevel = log2(this->BOARD_SIZE);

  double H = ENV_FACTOR_H_VALUE;

  int D = N;
  int d = N/2;

  // Init corner values
  X[0][0] = delta*this->random->std_normal();
  X[0][N] = delta*this->random->std_normal();
  X[N][0] = delta*this->random->std_normal();
  X[N][N] = delta*this->random->std_normal();

  for (int stage = 0; stage < maxlevel; stage++){
    delta = delta * pow(0.5, 0.5*H);

    // interpolate and offset points
    for (int x = d; x < N-d; x+=D){
      for (int y = d; y < N-d; y+=D){
        X[x][y] = this->f4(delta, X[x+d][y+d], X[x+d][y-d], X[x-d][y+d],X[x-d][y-d]);
      }
    }

    delta = delta * pow(0.5, 0.5*H);

    // boundary grid points
    for (int x = d; x < N-d; x+=D){
      X[x][0] = this->f3(delta, X[x+d][0], X[x-d][0], X[x][d]);
      X[x][N] = this->f3(delta, X[x+d][N], X[x-d][N], X[x][N-d]);
      X[0][x] = this->f3(delta, X[0][x+d], X[0][x-d], X[d][x]);
      X[N][x] = this->f3(delta, X[N][x+d], X[N][x-d], X[N-d][x]);
    }

    // interpolate and offset interior grid points

    for (int x = d; x < N-d; x+=D){
      for (int y = D; y < N-d; y+=D){
        X[x][y] = this->f4(delta, X[x][y+d], X[x][y-d], X[x+d][y], X[x-d][y]);
      }
    }

    for (int x = D; x < N-d; x+=D){
      for (int y = d; y < N-d; y+=D){
        X[x][y] = this->f4(delta, X[x][y+d], X[x][y-d], X[x+d][y], X[x-d][y]);
      }
    }

    D = D/2;
    d = d/2;
  }

  for (int i = 0; i < this->BOARD_SIZE; i++){
    for (int j = 0; j < this->BOARD_SIZE; j++){
      if (X[i][j] > 0.1){
        this->set_cell_value(i,j,0);
      }
      else{
        this->set_cell_value(i,j,1);
      }
    }
  }
}

double EnvFactor::f4(int delta, int a, int b, int c, int d){
  return (float(a+b+c+d)/float(4)) + delta * this->random->std_normal();
}

double EnvFactor::f3(int delta, int a, int b, int c){
  return (float(a+b+c)/float(3)) + delta * this->random->std_normal();
}


int EnvFactor::count_surrounding_ones(int x, int y){
  int c = 0;

  if (this->get_cell_value(x+1,y+1) == 1){ c++; }
  if (this->get_cell_value(x+1,y) == 1){ c++; }
  if (this->get_cell_value(x+1,y-1) == 1){ c++; }
  if (this->get_cell_value(x,y+1) == 1){ c++; }
  if (this->get_cell_value(x,y-1) == 1){ c++; }
  if (this->get_cell_value(x-1,y+1) == 1){ c++; }
  if (this->get_cell_value(x-1,y) == 1){ c++; }
  if (this->get_cell_value(x-1,y-1) == 1){ c++; }

  return c;
}

int EnvFactor::get_cell_value(int x, int y){
  return this->envFactor_grid[x][y];
}

void EnvFactor::set_cell_value(int x, int y, int val){
  this->envFactor_grid[x][y] = val;
}


void EnvFactor::print_env_factor(){
  printf("\n\nENV_FACTOR #%d\n", this->id);
  for (int j = this->BOARD_SIZE-1; j >= 0; j--){
    for (int i = 0; i < this->BOARD_SIZE; i++){
      printf("%d ", this->get_cell_value(i,j));
    }
    printf("\n");
  }
}
