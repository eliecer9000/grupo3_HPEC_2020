/*
# Course: MP-6171 High Performance Embedded Systems
# Tecnologico de Costa Rica (www.tec.ac.cr)
# Developer Names:
# 	Eliecer Mora (eliecer@estudiantec.cr)
#	Sergio Guillen (guillen_sergio@hotmail.com)
# General purpose: Provide a basic memory leak report for a binary based
#                  on the calls to malloc and free
#
# Usage:
# ./memcheck [ -p ./PROGRAM ] [-h] [-a]
# -a displays the information of the author of the program.
# -h displays the usage message to let the user know how to execute the
#    application
# -p PROGRAM specifies the path to the program binary that will be analyzed
# 
# Inputs: 
#           p   [-p]: path to the program binary that will be analyzed
#
# Output:
#           Report with the number of malloc and free calls
*/

#include <ctype.h>
#include <dlfcn.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void get_help();

void get_help(){
  printf("Usage\n");
  printf("./memcheck [ -p ./PROGRAM ] [-h] [-a]\n");
  printf("-p PROGRAM specifies the path to the program binary that will be");
  printf(" analyzed\n"); 
  printf("-a displays the information of the author of the program.\n");
  printf("-h displays the usage message to let the user know how to");
  printf(" execute the application.\n");
}

int main(int argc, char **argv){
  char *p_value = NULL;
  int index;
  int c;
  int p_provided = 0;

  opterr = 0;

  if (argc == 1){
    get_help();
    return 0;
  }

  while ((c = getopt(argc, argv, "p:ha")) != -1){
    switch (c){
      case 'a':
        printf("Authors:\n");
        printf("Eliecer Mora (eliecer@estudiantec.cr)\n");
        printf("Sergio Guillen (guillen_sergio@hotmail.com)\n");
        return 0;
      case 'h':
        get_help();
        return 0;
      case 'p':
        p_provided = 1;
        p_value = optarg;
        break;
      case '?':
        if (optopt == 'p')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        return 0;
    }
  }
  for (index = optind; index < argc; index++){
    printf("Argument %s is not a valid argument, use -h for help \n",
           argv[index]);
  }

  if (!p_provided){
    printf("path to the binary to run must be specified\n");
    printf("Use -h for help \n");
    return 0;
  }

  char *const args[] = {p_value ,NULL};
  char *const envs[] = {"LD_PRELOAD=../lib/.libs/libmemcheck.so", NULL};
  execve(p_value, args, envs);

  return 0;
}

