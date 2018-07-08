#include "Logger.h"
#include "EnvFactor.h"
#include "Fragment.h"
#include "Individual.h"
#include "TimeTracker.h"
#include "GeneTracker.h"
#include "genetic_map.h"

Logger::Logger(std::string dir){
    double start_time = time_tracker->get_start_time();
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

    time_tracker->add_time_in_logger(start_time);
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

    if (params->RUN_DATA_DIR != ""){
        dirname = params->RUN_DATA_DIR;
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

std::string Logger::make_patch_directory(std::string gen_dir){
    std::string patch_dir_path = gen_dir + "patches/";
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

    // ld.py
    std::string ld_symlink_path = this->run_dir_path + "ld.py";
    std::string ld_path = vis_tool_path + "ld.py";
    symlink(ld_path.c_str(), ld_symlink_path.c_str());
}

void Logger::write_metadata(){
    std::ofstream metadata_file;
    std::string metadata_file_path = this->run_dir_path + "metadata.txt";


    metadata_file.open(metadata_file_path.c_str());
    metadata_file << "RUNTIME: " << asctime(this->timeinfo);
    metadata_file << "RANDOM_SEED_VALUE: " << params->RANDOM_SEED_VALUE << "\n\n";

    metadata_file << "======================================\n";
    metadata_file << "PARAMETER VALUES\n";
    metadata_file << "======================================\n\n";

    metadata_file << "BOARD_SIZE: " << params->BOARD_SIZE << "\n";
    metadata_file << "N_ENV_FACTORS: " << params->N_ENV_FACTORS << "\n";

    metadata_file << "FRAGMENT_AMOUNT_LOW: " << params->FRAGMENT_AMOUNT_LOW << "\n";
    metadata_file << "FRAGMENT_AMOUNT_HI: " << params->FRAGMENT_AMOUNT_HI << "\n";
    metadata_file << "FRAGMENT_H_VALUE: " << params->FRAGMENT_H_VALUE << "\n";

    metadata_file << "ENV_FACTOR_CUTOFF: " << params->ENV_FACTOR_CUTOFF << "\n";
    metadata_file << "ENV_FACTOR_H_VALUE: " << params->ENV_FACTOR_H_VALUE << "\n";

    metadata_file << "======================================\n";
    metadata_file << "LOCI\n";
    metadata_file << "======================================\n\n";

    metadata_file << "FITNESS LOCI: [ ";

    for (int i = 0; i < params->N_ENV_FACTORS; i++){
        metadata_file << genetic_map->fitness_loci[i] << ", ";
    }
    metadata_file << "]\n";

    metadata_file.close();
}

void Logger::write_envFactor(EnvFactor* envFactor){
    double start_time = time_tracker->get_start_time();
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

    time_tracker->add_time_in_logger(start_time);
}

void Logger::write_fragment_map(Fragment* fragment){
    double start_time = time_tracker->get_start_time();
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

    time_tracker->add_time_in_logger(start_time);
}

void Logger::write_fragmentation_data(int gen, int x, int y){
    double start_time = time_tracker->get_start_time();
    std::ofstream fragment_file;
    std::string fragment_file_path = this->fragment_dir_path + "fragment_data.csv";

    fragment_file.open(fragment_file_path.c_str(), std::fstream::app);
    fragment_file << gen << ", " << x << ", " << y << "\n";

    time_tracker->add_time_in_logger(start_time);
}

void Logger::write_generation_map(std::string gen_dir_path, std::vector<std::vector<int>> map){
    std::ofstream indivs_file;
    std::string file_path = gen_dir_path + "generation_map.csv";

    indivs_file.open(file_path.c_str(), std::fstream::app);

    int board_size = params->BOARD_SIZE;
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

std::string Logger::get_patch_file(std::string patch_dir_path, int x, int y){
    return patch_dir_path + std::to_string(x) + "_" + std::to_string(y) + ".csv";
}


void Logger::write_patch_data(std::string patch_dir_path, int x, int y, int locus, double allele_val, double freq){
    std::string patch_file_path = this->get_patch_file(patch_dir_path, x, y);

    std::ofstream patch_file;
    patch_file.open(patch_file_path.c_str(), std::fstream::app);

    patch_file << std::to_string(locus) + "," + std::to_string(allele_val) + "," + std::to_string(freq) + "\n";

}

void Logger::write_global_ld(std::string gen_dir_path, int l1, double al1_val, int l2, double al2_val, double ld){
    std::string ld_file_path = gen_dir_path + "ld.csv";

    std::ofstream ld_file;
    ld_file.open(ld_file_path.c_str(), std::fstream::app);

    ld_file << std::to_string(l1) + "," + std::to_string(al1_val) + "," + std::to_string(l2)  + "," + std::to_string(al2_val) + "," + std::to_string(ld) + "\n";
}

void Logger::write_fitness_ld(std::string gen_dir_path, int l1, double al1_val, int l2, double al2_val, double ld){
    std::string ld_file_path = gen_dir_path + "fitness_ld.csv";

    std::ofstream ld_file;
    ld_file.open(ld_file_path.c_str(), std::fstream::app);

    ld_file << std::to_string(l1) + "," + std::to_string(al1_val) + "," + std::to_string(l2)  + "," + std::to_string(al2_val) + "," + std::to_string(ld) + "\n";
}

void Logger::write_generation_data(int gen, std::vector<std::vector<int>> map, int n_total){
    double start_time = time_tracker->get_start_time();
    std::string gen_dir_path = this->make_gen_directory(gen);
    std::string patch_dir_path = this->make_patch_directory(gen_dir_path);

    this->write_generation_map(gen_dir_path, map);

    // locus by locus
    int n_loci = params->N_LOCI;
    int N = params->BOARD_SIZE;
    int patch_size;
    double freq;
    std::vector<allele*> alleles;

    double f_al1, f_al2, f_both, ld;

    int k_val = params->N_ENV_FACTORS;
    int l1,l2;
    for (int i1 = 0; i1 < k_val; i1++){
        l1 = genetic_map->fitness_loci[i1];
        alleles = gene_tracker->get_locus_vector(l1);
        for (int i2 = i1+1; i2 < k_val; i2++){
            l2 = genetic_map->fitness_loci[i2];
            for (allele* al1: alleles){
                for (dependent_allele* al2 : al1->loci[l2]){
                    // overall ld
                    f_both = double(al2->n_total)/double(4*n_total);
                    f_al1 = double(al1->n_total)/double(2*n_total);
                    f_al2 = double(gene_tracker->find_allele(al2->locus, al2->allele_val)->n_total)/double(2*n_total);

                    if (!(f_al1 >= 0.0 && f_al1 <= 1.0) || !((f_al2 >= 0.0 && f_al2 <= 1.0)) || !(f_both >= 0.0 && f_both <= 1.0)){
                        printf("ld assert\n");
                    }


                    if (f_al1 != 0 && f_al2 != 0){
                        ld = (f_al1 * f_al2) - f_both;
                        this->write_fitness_ld(gen_dir_path, l1, al1->allele_val, l2, al2->allele_val, ld);
                    }


                }
            }
        }
    }




    for (int l1 = 0; l1 < n_loci; l1++){
        alleles = gene_tracker->get_locus_vector(l1);
        for (allele* al1: alleles){

            for (int i = 0; i < N; i++){
                for (int j = 0; j < N; j++){
                    if (al1->freq_map[i][j] > 0){
                        patch_size = map[i][j];
                        freq = double(al1->freq_map[i][j])/ double(2*patch_size);
                        this->write_patch_data(patch_dir_path, i, j, al1->locus, al1->allele_val, freq);
                    }
                }
            }

            for (int l2 = l1+1; l2 < n_loci; l2++){
                for (dependent_allele* al2 : al1->loci[l2]){
                    // overall ld
                    f_both = double(al2->n_total)/double(4*n_total);
                    f_al1 = double(al1->n_total)/double(2*n_total);
                    f_al2 = double(gene_tracker->find_allele(al2->locus, al2->allele_val)->n_total)/double(2*n_total);

                    if (!(f_al1 >= 0.0 && f_al1 <= 1.0) || !((f_al2 >= 0.0 && f_al2 <= 1.0)) || !(f_both >= 0.0 && f_both <= 1.0)){
                        //assert(f_al1 >= 0.0 && f_al1 <= 1.0);
                        //assert(f_al2 >= 0.0 && f_al2 <= 1.0);
                        //assert(f_both >= 0.0 && f_both <= 1.0);
                        printf("ld assert\n");
                    }



                    ld = (f_al1 * f_al2) - f_both;
                    if (f_al1 != 0 && f_al2 != 0){
                        ld = (f_al1 * f_al2) - f_both;
                        this->write_global_ld(gen_dir_path, l1, al1->allele_val, l2, al2->allele_val, ld);
                    }
                }
            }
        }
    }

    time_tracker->add_time_in_logger(start_time);
}
