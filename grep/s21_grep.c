#include "s21_grep.h"

#include "grep_flags.h"

int main(int argc, char *argv[]) {
  char c = '\0';
    if (argc == 3) {
        entry_point('e', argv[1], argv[2]);
    } else if (argc == 4) {
        if ((c = getopt(argc, argv, ":e:i:v:c:l:n:h:s:f:o:")) != -1) {
            if (c == '?') {
                printf("Error comandline argv!!");
            } else {
                entry_point(c, optarg, argv[optind]);
            }
        }
    } else {
        printf("Error argv!");
    }
  return 0;
}

void entry_point(char option, char *pattern, char *filename) {
  FILE *f;
  if ((f = fopen(filename, "r")) != NULL) {
    switch (option) {
      case 'e':
        e_param(f, pattern);
        break;
      case 'i':
        i_param(f, pattern);
        break;
      case 'v':
        v_param(f, pattern);
        break;
      case 'c':
        c_param(f, pattern);
        break;
      case 'l':
        l_param(f, pattern, filename);
        break;
      case 'n':
        n_param(f, pattern);
        break;
      case 'h':
        e_param(f, pattern);
        break;
      case 's':
        e_param(f, pattern);
        break;
      case 'f':
        f_param(f, pattern);
        break;
      case 'o':
        o_param(f, pattern);
        break;
    }
    fclose(f);
  } else {
    if (option != 's') {
      printf("File error!!");
    }
  }
}

char *add_char(char *res, int *len, int i, char c) {
  if (i == *len) {
    char *buf = (char *)malloc(*len * 2 * sizeof(char));
    for (int j = 0; j < *len; j++) {
      buf[j] = res[j];
    }
    *len *= 2;
    free(res);
    res = buf;
  }
  res[i] = c;
  return res;
}

char *read_line(FILE *f) {
  char ch = '\0';
  int len = 1, i = 0;
  int flag = 1;
  char *line = (char *)malloc(len * sizeof(char));
  while (flag && (ch = fgetc(f)) != EOF) {
    line = add_char(line, &len, i, ch);
    if (ch == '\n') {
      flag = 0;
    }
    i++;
  }
  line = add_char(line, &len, i, '\0');
  return line;
}

char *get_lower_line(char *line) {
  int len = 1, i = 0;
  while (line[i] != '\n' && line[i] != '\0') {
    i++;
    len++;
  }
  char *lower_line = (char *)malloc(len * sizeof(char));
  for (int i = 0; i < len; i++) {
    lower_line[i] = tolower(line[i]);
  }
  return lower_line;
}

int check_line(char *pattern, char *line, int flag) {
  regex_t regex;
  int reti, flag_result;
    if (flag) {
        reti = regcomp(&regex, pattern, REG_ICASE);
    } else {
        reti = regcomp(&regex, pattern, REG_EXTENDED);
    }
  reti = regexec(&regex, line, 0, NULL, 0);
  if (!reti) {
    flag_result = 1;
  } else if (reti == REG_NOMATCH) {
    flag_result = 0;
  } else {
    flag_result = -1;
  }
  regfree(&regex);
  return flag_result;
}

char **get_patterns(FILE *p) {
  char *pattern;
  int count = len_patterns(p);
  if (count != -1) {
    char **patterns = (char **)malloc(count * 2 * sizeof(char *));
    for (int i = 0; i < count; i++) {
      pattern = read_line(p);
      if (strlen(pattern) != 1) {
        pattern[strlen(pattern) - 1] = '\0';
      }
      patterns[i] = pattern;
    }
    return patterns;
  } else {
    printf("Fseek error!");
    return NULL;
  }
}

int len_patterns(FILE *p) {
  int count = 0;
  char ch = '\0';
  if (fseek(p, 0, SEEK_SET) == 0) {
    while ((ch = fgetc(p)) != EOF) {
      if (ch == '\n') {
        count++;
      }
    }
  } else {
    count = -1;
  }
  if (fseek(p, 0, SEEK_SET) != 0) {
    count = -1;
  }
  return count;
}
