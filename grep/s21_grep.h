#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void entry_point(char option, char *pattern, char *filename);
int check_line(char *pattern, char *line, int flag);
int len_patterns(FILE *p);
char *read_line(FILE *f);
char *add_char(char *res, int *len, int i, char c);
char **get_patterns(FILE *p);
