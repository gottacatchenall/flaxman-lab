
#ifndef FRACTAL_H
#define FRACTAL_H

#include "include.h"

class Fractal{
    private:
        int BOARD_SIZE;
    public:
        Fractal();
        int** generate_fractal(double H_VAL, double CUTOFF);
        double f4(double delta, double a, double b, double c, double d);
        double f3(double delta, double a, double b, double c);
};

#endif
