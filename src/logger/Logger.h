#ifndef LOGGER_H
#define LOGGER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string>
#include <fstream>

#include "cmd_line_opts.h"
#include "include.h"

class EnvFactor;
class Fragment;

class Logger{
  private:
    std::string data_dir_path;
    std::string run_dir_path;
    std::string envFactor_dir_path;
    std::string fragment_dir_path;
    params_s* params;
    struct tm *timeinfo;
  public:
    Logger(std::string dir, params_s *params);
    void make_data_directory();
    void make_run_directory();
    void make_envFactor_directory();
    void make_fragment_directory();
    void make_symlinks_to_vis_tools();
    void write_metadata();
    void write_envFactor(EnvFactor* envFactor);
    void write_fragment_map(Fragment* fragment);
    void write_fragmentation_data(int gen, int x, int y);
};

#endif
