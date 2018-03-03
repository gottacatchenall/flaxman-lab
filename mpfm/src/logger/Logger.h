#ifndef LOGGER_H
#define LOGGER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string>
#include <fstream>

#include "cmd_line_opts.h"
#include "EnvFactor.h"
#include "include.h"

class EnvFactor;

class Logger{
  private:
    std::string data_dir_path;
    std::string run_dir_path;
    std::string envFactor_dir_path;
    params_s* params;
    struct tm *timeinfo;
  public:
    Logger(std::string dir, params_s *params);
    void make_data_directory();
    void make_run_directory();
    void write_metadata();
    void make_envFactor_directory();
    void write_envFactor(EnvFactor* envFactor);
};

#endif
