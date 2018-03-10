#include "gmock/gmock.h"
#include "EnvFactor.h"

class MockEnvFactor : public EnvFactor {
    public:
        MockEnvFactor(random, fractal, params, index) : EnvFactor(random, fractal, params, index) {}
        MOCK_METHOD3(set_cell_value, void(int x, int y, int val));
        MOCK_METHOD2(get_cell_value, int(int x, int y));
        MOCK_METHOD0(get_id, int());
        MOCK_METHOD0(get_board_size, int());
        MOCK_METHOD0(generate_fractal, void());
};
