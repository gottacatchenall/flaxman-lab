
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
