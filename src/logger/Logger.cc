#include "Logger.h"
#include "EnvFactor.h"
#include "Fragment.h"
#include "Individual.h"

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
    this->make_fragment_directory();
    this->make_generations_directory();
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

void Logger::make_fragment_directory(){
    std::string fragment_path = this->run_dir_path + "fragment/";
    this->fragment_dir_path = fragment_path;
    mkdir(fragment_path.c_str(), 0700);
}

void Logger::make_generations_directory(){
    std::string gens_path = this->run_dir_path + "generations/";
    this->generations_dir_path = gens_path;
    mkdir(gens_path.c_str(), 0700);
}

std::string Logger::make_gen_directory(int gen){
    std::string gen_dir_path = this->generations_dir_path + std::to_string(gen) + "/";
    mkdir(gen_dir_path.c_str(), 0700);
    return gen_dir_path;
}

std::string Logger::make_patch_directory(std::string gen_dir, int x, int y){
    std::string patch_dir_path = gen_dir + "patch" + std::to_string(x) + "_" + std::to_string(y) + "/";
    mkdir(patch_dir_path.c_str(), 0700);
    return patch_dir_path;
}


void Logger::make_symlinks_to_vis_tools(){
    std::string vis_tool_path = this->data_dir_path + "../vis-tools/";

    // all-env-factors.py
    std::string all_env_factors_symlink_path = this->run_dir_path + "all-env-factors.py";
    std::string all_env_factors_path = vis_tool_path + "all-env-factors.py";
    symlink(all_env_factors_path.c_str(), all_env_factors_symlink_path.c_str());

    // fragmentation-map.py
    std::string fragmentation_map_symlink_path = this->run_dir_path + "fragmentation-map.py";
    std::string fragmentation_map_path = vis_tool_path + "fragmentation-map.py";
    symlink(fragmentation_map_path.c_str(), fragmentation_map_symlink_path.c_str());

    // fragmentation-over-time.py
    std::string fragmentation_over_time_symlink_path = this->run_dir_path + "fragmentation-over-time.py";
    std::string fragmentation_over_time_path = vis_tool_path + "fragmentation-over-time.py";
    symlink(fragmentation_over_time_path.c_str(), fragmentation_over_time_symlink_path.c_str());

    // single-env-factor.py
    std::string single_env_factor_symlink_path = this->run_dir_path + "single-env-factor.py";
    std::string single_env_factor_path = vis_tool_path + "single-env-factor.py";
    symlink(single_env_factor_path.c_str(), single_env_factor_symlink_path.c_str());

    // population.py
    std::string population_symlink_path = this->run_dir_path + "populations.py";
    std::string population_path = vis_tool_path + "populations.py";
    symlink(population_path.c_str(), population_symlink_path.c_str());
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

void Logger::write_fragment_map(Fragment* fragment){
    std::ofstream fragment_file;
    std::string fragment_file_path = this->fragment_dir_path + "fragment_map.csv";

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

void Logger::write_fragmentation_data(int gen, int x, int y){
    std::ofstream fragment_file;
    std::string fragment_file_path = this->fragment_dir_path + "fragment_data.csv";

    fragment_file.open(fragment_file_path.c_str(), std::fstream::app);
    fragment_file << gen << ", " << x << ", " << y << "\n";
}


void Logger::write_generation_data(int gen, std::vector<std::vector<int>> map){
    std::string gen_dir_path = this->make_gen_directory(gen);
    //std::string patch_dir_path = this->make_patch_directory(gen_dir_path, patch_x, patch_y);

    std::ofstream indivs_file;
    std::string file_path = gen_dir_path + std::to_string(gen) + ".csv";

    indivs_file.open(file_path.c_str(), std::fstream::app);

    int board_size = this->params->BOARD_SIZE;
    int val;
    std::string val_str;

    for (int j = board_size-1; j >= 0; j--){
        for (int i = 0; i < board_size; i++){
            val = map[i][j];
            indivs_file << std::to_string(val);
            if (i < board_size- 1){
                indivs_file << ",";
            }
        }
        indivs_file << "\n";
    }
}
