#include "Logger.h"

Logger::Logger(){
  DIR* dir = opendir("./data");
  if (dir){
      /* Directory exists. */
      closedir(dir);
  }
  else if (ENOENT == errno){
    this->make_data_directory();
  }

}

void Logger::make_data_directory(){
  printf("It doesn't look like you have a data directory.\n");
  printf("Creating one at $(MPFM_DIR)/data.\n");
}
