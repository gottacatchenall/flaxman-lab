
#include "cmd_line_opts.h"

void printHello(){
  printf("\n");
  printf("========================================================\n");
  printf("=                                                      =\n");
  printf("=       Metapopulation Fragmentation Model (mpfm)      =\n");
  printf("=                                            v0.1      =\n");
  printf("=                                                      =\n");
  printf("========================================================\n");
  printf("\n\n");
}

void printUsage(char *name){
    printf("\nUSAGE: %s [options]\n\n", name);

    printf("LIST OF OPTIONS: \n\n");

    printf("\t[-e <integer>]\n");
    printf("\t\t The number of environmental factors.\n");

    printf("\t[-g <integer>]\n");
    printf("\t\t The size of the lattice. Integer is the length of one side.\n");

    printf("\n\n");
}

params_s* get_options(int argc, char *argv[], params_s* opts){
    int opt;


    while ((opt = getopt(argc, argv, "e:g:h:?")) != -1) {
        switch (opt) {
            case 'e':
                opts->N_ENV_FACTORS = atoi(optarg);
                break;
            case 'g':
                opts->BOARD_SIZE = atoi(optarg);
                break;
            case 'h':
            case '?':
            default:
                printUsage(argv[0]);
                exit(-1);
        }
    }
    printHello();
    return opts;
}
