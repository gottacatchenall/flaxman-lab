
#include "Fractal.h"
#include "Random.h"
#include "params_struct.h"

Fractal::Fractal(){
    this->BOARD_SIZE = params->BOARD_SIZE;
}

double** Fractal::generate_fractal(double H_VAL){
    double X[this->BOARD_SIZE+1][this->BOARD_SIZE+1];

    double delta = 1;
    int N = this->BOARD_SIZE;

    int maxlevel = log2(this->BOARD_SIZE);

    double H = H_VAL;

    int D = N;
    int d = N/2;

    for (int i = 0; i <= N; i++){
        for (int j = 0; j <= N; j++){
            X[i][j] = 0.0;
        }
    }

    // Init corner values
    X[0][0] = delta*random_gen->std_normal();
    X[0][N] = delta*random_gen->std_normal();
    X[N][0] = delta*random_gen->std_normal();
    X[N][N] = delta*random_gen->std_normal();

    for (int stage = 0; stage < maxlevel; stage++){
        delta = delta * double(pow(double(0.5), double(0.5*H)));

        // interpolate and offset points
        for (int x = d; x <= N-d; x+=D){
            for (int y = d; y <= N-d; y+=D){
                X[x][y] = this->f4(delta, X[x+d][y+d], X[x+d][y-d], X[x-d][y+d],X[x-d][y-d]);
            }
        }

        delta = delta * double(pow(double(0.5), double(0.5*H)));

        // boundary grid points
        for (int x = d; x <= N-d; x+=D){
            X[x][0] = this->f3(delta, X[x+d][0], X[x-d][0], X[x][d]);
            X[x][N] = this->f3(delta, X[x+d][N], X[x-d][N], X[x][N-d]);
            X[0][x] = this->f3(delta, X[0][x+d], X[0][x-d], X[d][x]);
            X[N][x] = this->f3(delta, X[N][x+d], X[N][x-d], X[N-d][x]);
        }

        // interpolate and offset interior grid points
        for (int x = d; x <= N-d; x+=D){
            for (int y = D; y <= N-d; y+=D){
                X[x][y] = this->f4(delta, X[x][y+d], X[x][y-d], X[x+d][y], X[x-d][y]);
            }
        }

        for (int x = D; x <= N-d; x+=D){
            for (int y = d; y <= N-d; y+=D){
                X[x][y] = this->f4(delta, X[x][y+d], X[x][y-d], X[x+d][y], X[x-d][y]);
            }
        }

        D = D/2;
        d = d/2;
    }

    int n = this->BOARD_SIZE;
    double** grid = new double*[n];
    for (int i = 0; i < n; i++){
        grid[i] = new double[n];
    }


    double min = X[0][0];
    double max = X[0][0];


    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (X[i][j] > max){
                max = X[i][j];
            }
            if (X[i][j] < min){
                min = X[i][j];
            }
        }
    }

    if (min > 0){
        min = -1*min;
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            grid[i][j] = double(max - X[i][j])/(max-min);
        }
    }

    return grid;
}

int** Fractal::create_binary_map_from_fractal(double** fractal, double CUTOFF){
    int n = this->BOARD_SIZE;

    int** grid = new int*[n];
    for (int i = 0; i < n; i++){
        grid[i] = new int[n];
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (fractal[i][j] > CUTOFF){
                grid[i][j] = 0;
            }
            else{
                grid[i][j] = 1;
            }
        }
    }

    return grid;
}


double Fractal::f4(double delta, double a, double b, double c, double d){
    double sum = a+b+c+d;
    double avg = sum/4.0;
    double val =  avg + double(delta) * double(random_gen->std_normal());
    return val;
}

double Fractal::f3(double delta, double a, double b, double c){
    double sum = a+b+c;
    double avg = sum/3.0;
    double val =  avg + double(delta) * double(random_gen->std_normal());
    return val;
}
