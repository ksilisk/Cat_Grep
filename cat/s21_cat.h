#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

static struct option long_options[] = {{"number-nonblank", no_argument, 0, 'b'},
                                       {"number", no_argument, 0, 'n'},
                                       {"squeeze-blank", no_argument, 0, 's'},
                                       {0, 0, 0, 0}};

typedef struct {
  int b;
  int n;
  int s;
  int v;
  int E;
  int T;
} flags;

int count_lines = 0;
flags options = {0, 0, 0, 0, 0, 0};

int print_file(char *filename);
void non_print(char c);
