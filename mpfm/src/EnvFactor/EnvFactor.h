
#ifndef ENVFACTOR_H
#define ENVFACTOR_H


class EnvFactor{
    private:
        int sigma;
        int x_0;
        int y_0;
    public:
        double get_random_sigma();
        double Gaussian(point loc);
        double reduce_sigma();
};

#endif
