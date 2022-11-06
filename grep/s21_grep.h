#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUNT_TEMPLATES 1024
#define MAX_LINE_LENGTH 2048

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} flags;

flags options = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int print_matches(regex_t *templates, int count_templates, char *filename);
int read_file_templates(regex_t *templates, int *count_templates,
                        char *filename);
void free_templates(regex_t *templates, int count);
