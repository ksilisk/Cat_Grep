#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static struct option long_opts[] = {
    {"number-nonblank", required_argument, NULL, 'b'},
    {"number", required_argument, NULL, 'n'},
    {"squeeze-blank", required_argument, NULL, 's'},
    {0, 0, NULL, 0}};

void entry_point(char option, char *filename);
void non_printing(char ch);
void e_param(FILE *f, int flag);
void t_param(FILE *f, int flag);
void non_param(FILE *f);
void b_param(FILE *f);
void n_param(FILE *f);
void s_param(FILE *f);
void v_param(FILE *f);
