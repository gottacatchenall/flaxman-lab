#include "gmock/gmock.h"
#include "Logger.h"

class MockLogger : public Logger {
    public:
        MockLogger(std::string str, params_s* params) : Logger(str, params) {}
        MOCK_METHOD0(make_data_directory, void());
        MOCK_METHOD0(make_run_directory, void());
        MOCK_METHOD0(make_envFactor_directory, void());
        MOCK_METHOD0(make_fragment_directory, void());
        MOCK_METHOD0(make_symlinks_to_vis_tools, void());
        MOCK_METHOD0(write_metadata, void());
        MOCK_METHOD1(write_envFactor, void(EnvFactor* envFactor));
        MOCK_METHOD1(write_fragment_map, void(Fragment* fragment));
        MOCK_METHOD3(write_fragmentation_data, void(int gen, int x, int y));
};
