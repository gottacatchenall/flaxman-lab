#include "gtest/gtest.h"

#include "Board.h"
#include "mock_Fractal.h"
#include "mock_Random.h"
#include "mock_Logger.h"
#include "params_struct.h"


class MockRandom;
class Fractal;
class Logger;
struct params_s;
typedef params_s params_s;

class BoardTest : public ::testing::Test {
    protected:
        MockRandom* random;
        Fractal* fractal;
        Logger* logger;
        params_s* params;

    BoardTest() {
        this->params = new params_s;
        this->random = new MockRandom();
        this->fractal = new MockFractal(this->random, this->params);
        this->logger = new MockLogger("", this->params);
    }

    virtual ~BoardTest() {
    // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
    }

    virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(BoardTest, SetupWithIncorrectParams) {
    Board board(&board, this->random, this->fractal, this->logger, this->params);
}
