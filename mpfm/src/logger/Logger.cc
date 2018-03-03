#include "Logger.h"

Logger::Logger(std::string dir){

  this->data_dir_path = (dir += "data/");

  DIR* data = opendir(this->data_dir_path.c_str());
  if (data){
      closedir(data);
  }
  else if (ENOENT == errno){
    this->make_data_directory();
  }

  this->make_run_directory();
  this->make_envFactor_directory();

}

void Logger::make_data_directory(){
  printf("It doesn't look like you have a data directory.\n");
  printf("Creating one at $(MPFM_DIR)/data.\n");

  mkdir(this->data_dir_path.c_str(), 0700);
}

void Logger::make_run_directory(){
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);

  std::string dirname = std::to_string(rawtime);
  std::string path = this->data_dir_path + dirname + "/";

  this->run_dir_path = path;
  mkdir(path.c_str(), 0700);
}

void Logger::make_envFactor_directory(){
  std::string envFactor_path = this->run_dir_path + "envFactors/";
  mkdir(envFactor_path.c_str(), 0700);
}
