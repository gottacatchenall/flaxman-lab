#ifndef CMD_LINE_OPTS_H
#define CMD_LINE_OPTS_H

#include "include.h"
#include "params_struct.h"
#include <unistd.h>

#if __APPLE__
    #include <mach-o/dyld.h>
#endif

struct params_s;
typedef params_s params_s;

void printHello();
void printUsage(char* name);
params_s* get_options(int argc, char*argv[], params_s* opts);
char* get_execuable_path(char* dirNameBuffer, int bufSize);


#endif
