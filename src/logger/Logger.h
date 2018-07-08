#ifndef LOGGER_H
#define LOGGER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string>
#include <fstream>

#include "cmd_line_opts.h"
#include "include.h"

class Logger{
    private:
        std::string data_dir_path;
        std::string run_dir_path;
        std::string envFactor_dir_path;
        std::string fragment_dir_path;
        std::string generations_dir_path;
        struct tm *timeinfo;
    public:
        Logger(std::string dir);
        void make_data_directory();
        void make_run_directory();
        void make_envFactor_directory();
        void make_fragment_directory();
        void make_generations_directory();
        std::string make_gen_directory(int gen);
        std::string make_patch_directory(std::string gen_dir);
        void make_symlinks_to_vis_tools();
        void write_metadata();
        void write_envFactor(EnvFactor* envFactor);
        void write_fragment_map(Fragment* fragment);
        void write_fragmentation_data(int gen, int x, int y);
        std::string get_patch_file(std::string patch_dir_path, int x, int y);
        void write_patch_data(std::string patch_dir_path, int x, int y, int locus, double allele_val, double freq);
        void write_generation_map(std::string gen_dir_path, std::vector<std::vector<int>> map);
        void write_global_ld(std::string gen_dir_path, int l1, double al1_val, int l2, double al2_val, double ld);
        void write_fitness_ld(std::string gen_dir_path, int l1, double al1_val, int l2, double al2_val, double ld);
        void write_patch_ld();
        void write_generation_data(int gen, std::vector<std::vector<int>> map, int n_total);
};

#endif
