#include "Logger.h"
#include "EnvFactor.h"
#include "Fragment.h"

Logger::Logger(std::string dir, params_s* params){
  this->params = params;
  this->data_dir_path = (dir += "data/");

  DIR* data = opendir(this->data_dir_path.c_str());
  if (data){
      closedir(data);
  }
  else if (ENOENT == errno){
    this->make_data_directory();
  }

  this->make_run_directory();
  this->write_metadata();
  this->make_envFactor_directory();
  this->make_symlinks_to_vis_tools();
}

void Logger::make_data_directory(){
  printf("It doesn't look like you have a data directory.\n");
  printf("Creating one at $(MPFM_DIR)/data.\n");

  mkdir(this->data_dir_path.c_str(), 0700);
}

void Logger::make_run_directory(){

  std::string dirname;
  time_t rawtime;
  time (&rawtime);
  this->timeinfo = localtime (&rawtime);

  if (this->params->RUN_DATA_DIR != ""){
    dirname = this->params->RUN_DATA_DIR;
  }
  else{
    dirname = std::to_string(rawtime);
  }

  std::string path = this->data_dir_path + dirname + "/";

  this->run_dir_path = path;
  mkdir(path.c_str(), 0700);
}

void Logger::make_envFactor_directory(){
  std::string envFactor_path = this->run_dir_path + "envFactors/";
  this->envFactor_dir_path = envFactor_path;
  mkdir(envFactor_path.c_str(), 0700);
}

void Logger::make_symlinks_to_vis_tools(){
  std::string vis_tool_path = this->data_dir_path + "../vis-tools/";

  // view-env-factor.py
  std::string view_env_sym_link_path = this->run_dir_path + "env-factor.py";
  std::string view_env_factor_path = vis_tool_path + "env-factor.py";
  symlink(view_env_factor_path.c_str(), view_env_sym_link_path.c_str());

  // view all
  std::string view_all_sym_link_path = this->run_dir_path + "all-env-factors.py";
  std::string view_all_path = vis_tool_path + "all-env-factors.py";
  symlink(view_all_path.c_str(), view_all_sym_link_path.c_str());
}

void Logger::write_metadata(){
  std::ofstream metadata_file;
  std::string metadata_file_path = this->run_dir_path + "metadata.txt";


  metadata_file.open(metadata_file_path.c_str());
  metadata_file << "RUNTIME: " << asctime(this->timeinfo);
  metadata_file << "RANDOM_SEED_VALUE: " << RANDOM_SEED_VALUE << "\n\n";

  metadata_file << "======================================\n";
  metadata_file << "PARAMETER VALUES\n";
  metadata_file << "======================================\n\n";

  metadata_file << "BOARD_SIZE: " << this->params->BOARD_SIZE << "\n";
  metadata_file << "N_ENV_FACTORS: " << this->params->N_ENV_FACTORS << "\n";

  metadata_file << "FRAGMENT_AMOUNT_LOW: " << this->params->FRAGMENT_AMOUNT_LOW << "\n";
  metadata_file << "FRAGMENT_AMOUNT_HI: " << this->params->FRAGMENT_AMOUNT_HI << "\n";
  metadata_file << "FRAGMENT_H_VALUE: " << this->params->FRAGMENT_H_VALUE << "\n";

  metadata_file << "ENV_FACTOR_CUTOFF: " << this->params->ENV_FACTOR_CUTOFF << "\n";
  metadata_file << "ENV_FACTOR_H_VALUE: " << this->params->ENV_FACTOR_H_VALUE << "\n";

  metadata_file.close();
}

void Logger::write_envFactor(EnvFactor* envFactor){
  std::ofstream envFactor_file;
  std::string envFactor_file_path = this->envFactor_dir_path + "envFactor" + std::to_string(envFactor->get_id()) + ".csv";

  envFactor_file.open(envFactor_file_path.c_str());

  int board_size = envFactor->get_board_size();
  int val;
  std::string val_str;
  for (int j = board_size-1; j >= 0; j--){
    for (int i = 0; i < board_size; i++){
      val = envFactor->get_cell_value(i,j);
      val_str = std::to_string(val);
      envFactor_file << val_str;
      if (i < board_size- 1){
        envFactor_file << ",";
      }
    }
    envFactor_file << "\n";
  }
}

void Logger::write_fragment(Fragment* fragment){
  std::ofstream fragment_file;
  std::string fragment_file_path = this->run_dir_path + "fragment.csv";

  fragment_file.open(fragment_file_path.c_str());

  int board_size = fragment->get_board_size();
  int val;
  std::string val_str;
  for (int j = board_size-1; j >= 0; j--){
    for (int i = 0; i < board_size; i++){
      val = fragment->get_cell_value(i,j);
      val_str = std::to_string(val);
      fragment_file << val_str;
      if (i < board_size- 1){
        fragment_file << ",";
      }
    }
    fragment_file << "\n";
  }
}
