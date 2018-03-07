
#include "cmd_line_opts.h"
#include "params_struct.h"
#include <getopt.h>

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

    printf("\t[--frag-lo <double>]\n");
    printf("\t\t The low end proportion of tiles that will be marked fragmented by end of run.\n");

    printf("\t[--frag-hi <double>]\n");
    printf("\t\t The high end proportion of tiles that will be marked fragmented by end of run.\n");

    printf("\t[-g <integer>]\n");
    printf("\t\t The size of the lattice. Integer is the length of one side.\n");

    printf("\t[-p <string>]\n");
    printf("\t\t The name of the directory for data for this run.\n");

    printf("\n\n");
}

char* get_execuable_path(char *dirNameBuffer, int bufSize){

#ifdef __APPLE__ // MAC
  uint32_t size = bufSize;

  if (_NSGetExecutablePath(dirNameBuffer, &size) != 0) {
    // Buffer size is too small.
    printf("Length of path to executable was too long.\n");
    printf("Adjust buffer size in main.cc\n");
    exit(-1);
  }
#else // LINUX
  const char *linkName = "/proc/self/exe";
  const int ret = int(readlink(linkName, dirNameBuffer, bufSize - 1));

  if (ret == -1) {
    printf("Permission to read executable path was denied.\n");
    exit(-1);
  }

  dirNameBuffer[ret] = 0;
#endif
  // Cut of after last slash
  int last_slash;
  int ascii_slash = 47;
  for (int i = 0; i < bufSize; i++){
    if (dirNameBuffer[i] == ascii_slash){
      last_slash = i;
    }
  }
  for (int i = last_slash+1; i < bufSize; i++){
    dirNameBuffer[i] = 0;
  }
  return dirNameBuffer;
}


params_s* get_options(int argc, char *argv[], params_s* opts){
    int opt;

    static struct option long_options[] =
      {
        {"frag-lo", required_argument, 0, 0},
        {"frag-hi", required_argument, 0, 0},
        {0, 0, 0, 0}
      };

    int option_index = 0;

    while ((opt = getopt_long(argc, argv, "e:fL:fH:g:p:h:?", long_options, &option_index)) != -1) {
        switch (opt) {
            // frag-lo
            case 0:
                opts->FRAGMENT_AMOUNT_LOW = atof(optarg);
                break;
            // frag-hi
            case 1:
                opts->FRAGMENT_AMOUNT_HI = atof(optarg);
                break;
            case 'e':
                opts->N_ENV_FACTORS = atoi(optarg);
                break;
            case 'g':
                opts->BOARD_SIZE = atoi(optarg);
                break;
            case 'p':
                opts->RUN_DATA_DIR = optarg;
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
