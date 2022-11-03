#include "grep_flags.h"

void e_param(FILE *f, char *pattern) {
  char *line;
  while (feof(f) == 0) {
    line = read_line(f);
    if (check_line(pattern, line, 0) == 1) {
      printf("%s", line);
    }
    free(line);
  }
}

void i_param(FILE *f, char *pattern) {
  char *line;
  while (feof(f) == 0) {
    line = read_line(f);
    if (check_line(pattern, line, 1) == 1) {
      printf("%s", line);
    }
    free(line);
  }
}

void v_param(FILE *f, char *pattern) {
  char *line;
  while (feof(f) == 0) {
    line = read_line(f);
    if (check_line(pattern, line, 0) == 0) {
      printf("%s", line);
    }
    free(line);
  }
}

void c_param(FILE *f, char *pattern) {
  char *line;
  int count = 0;
  while (feof(f) == 0) {
    line = read_line(f);
    if (check_line(pattern, line, 0) == 1) {
      count++;
    }
    free(line);
  }
  printf("%d\n", count);
}

void l_param(FILE *f, char *pattern, char *filename) {
  char *line;
  int flag = 0;
  while (feof(f) == 0) {
    line = read_line(f);
    if (check_line(pattern, line, 0) == 1) {
      flag = 1;
    }
    free(line);
  }
  if (flag) {
    printf("%s\n", filename);
  }
}

void n_param(FILE *f, char *pattern) {
  char *line;
  int count = 1;
  while (feof(f) == 0) {
    line = read_line(f);
    if (check_line(pattern, line, 0) == 1) {
      printf("%d:%s", count, line);
    }
    free(line);
    count++;
  }
}

void f_param(FILE *f, char *filename) {
  FILE *p;
  char **patterns;
  char *line;
  if ((p = fopen(filename, "r")) != NULL) {
    patterns = get_patterns(p);
    int count = len_patterns(p);
    while (feof(f) == 0) {
      line = read_line(f);
      for (int i = 0; i < count; i++) {
        if (check_line(patterns[i], line, 0) == 1) {
          printf("%s", line);
          break;
        }
      }
      free(line);
    }
    for (int i = 0; i < count; i++) {
      free(patterns[i]);
    }
    free(patterns);
  } else {
    printf("File error!");
  }
}

void o_param(FILE *f, char *pattern) {
  char *line, *subline;
  int pattern_len = (int)strlen(pattern);
  subline = (char *)malloc(pattern_len * 2 * sizeof(char));
  while (feof(f) == 0) {
    line = read_line(f);
    for (int i = 0; i < ((int)strlen(line) - pattern_len); i++) {
      for (int j = 0; j < pattern_len; j++) {
        subline[j] = line[i + j];
      }
      subline[pattern_len] = '\0';
      if (strcmp(pattern, subline) == 0) {
        printf("%s\n", pattern);
      }
    }
    free(line);
  }
  free(subline);
}
