
#include "EnvFactor.h"
#include "Random.h"

EnvFactor::EnvFactor(Random* random, int index, int BOARD_SIZE){
  assert(random != NULL);

  this->id = index;
  this->BOARD_SIZE = BOARD_SIZE;
  this->random = random;

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
  double X[this->BOARD_SIZE+1][this->BOARD_SIZE+1];



  double delta = 1;
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
    delta = delta * double(pow(0.5, 0.5*H));

    for (int i = 0; i < this->BOARD_SIZE; i++){
      for (int j = 0; j < this->BOARD_SIZE; j++){
        X[i][j] = 0.0;
      }
    }

    // interpolate and offset points
    for (int x = d; x < N-d; x+=D){
      for (int y = d; y < N-d; y+=D){
        X[x][y] = this->f4(delta, X[x+d][y+d], X[x+d][y-d], X[x-d][y+d],X[x-d][y-d]);
      }
    }

    delta = delta * double(pow(0.5, 0.5*H));

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
      if (X[i][j] > 0 && X[i][j] < .2){
        this->set_cell_value(i,j,1);
      }
      else{
        this->set_cell_value(i,j,0);
      }
    }
  }
}

double EnvFactor::f4(double delta, int a, int b, int c, int d){
  double avg = double(double(a+b+c+d)/double(4.0));
  double val =  avg + double(delta) * double(this->random->std_normal());
  return val;
}

double EnvFactor::f3(double delta, int a, int b, int c){
  double val = (float(a+b+c)/float(3)) + delta * this->random->std_normal();
  return val;
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

int EnvFactor::get_id(){
  return this->id;
}

int EnvFactor::get_board_size(){
  return this->BOARD_SIZE;
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
