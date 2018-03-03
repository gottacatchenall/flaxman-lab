#ifndef LOGGER_H
#define LOGGER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string>

#include "include.h"

class Logger{
  private:
    std::string data_dir_path;
    std::string run_dir_path;
  public:
    Logger(std::string dir);
    void make_data_directory();
    void make_run_directory();
    void make_envFactor_directory();
};

#endif
