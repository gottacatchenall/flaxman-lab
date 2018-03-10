#include "gmock/gmock.h"
#include "Fractal.h"

class MockFractal : public Fractal {
    public:
        MockFractal(Random* random, params_s* params) : Fractal(random, params) {}
        MOCK_METHOD2(generate_fractal, int**(double H_VAL, double CUTOFF));
        MOCK_METHOD5(f4, double(double delta, double a, double b, double c, double d));
        MOCK_METHOD4(f3, double(double delta, double a, double b, double c));
};
