#include "gmock/gmock.h"
#include "Random.h"

class MockRandom : public Random {
    public:
        MockRandom() : Random(RANDOM_SEED_VALUE) {}
        MOCK_METHOD0(std_normal, float());
        MOCK_METHOD2(uniform_float, float(float a, float b));
        MOCK_METHOD2(uniform_int, int(int a, int b));
};
