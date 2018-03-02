#ifndef LOGGER_H
#define LOGGER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "include.h"

class Logger{
  private:
  public:
    Logger();
    void make_data_directory();
};

#endif
