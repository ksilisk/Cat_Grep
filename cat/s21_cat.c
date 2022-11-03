#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int flag = 1, op_index = 0;
  char c = '\0';
  if (argc < 3) {
    printf("No comandline argv!!");
    flag = 0;
  }
  if ((c = getopt_long(argc, argv, ":b:e:n:s:t:v:E:T:", long_opts,
                       &op_index)) != -1 &&
      flag) {
    if (c == '?') {
      printf("Error comandline argv!!");
      flag = 0;
    } else {
      entry_point(c, optarg);
    }
  } else if (flag) {
    entry_point('0', argv[optind]);
  }
  return 0;
}

void entry_point(char option, char *filename) {
  FILE *f;
  if ((f = fopen(filename, "r")) != NULL) {
    switch (option) {
      case 'b':
        b_param(f);
        break;
      case 'e':
        e_param(f, 1);
        break;
      case 'E':
        e_param(f, 0);
        break;
      case 'n':
        n_param(f);
        break;
      case 's':
        s_param(f);
        break;
      case 't':
        t_param(f, 1);
        break;
      case 'T':
        t_param(f, 0);
        break;
      case 'v':
        v_param(f);
        break;
      case '0':
        non_param(f);
        break;
    }
    fclose(f);
  } else {
    printf("File error!!");
  }
}

void non_param(FILE *f) {
  char ch = '\0';
  while ((ch = fgetc(f)) != EOF) {
    printf("%c", ch);
  }
}

void b_param(FILE *f) {
  char ch = '\0';
  int count = 1;
  while ((ch = fgetc(f)) != EOF) {
    if (ch != '\n') {
      printf("%6d\t", count++);
      while (ch != '\n' && ch != EOF) {
        printf("%c", ch);
        ch = fgetc(f);
      }
      printf("\n");
    } else {
      printf("\n");
    }
  }
}

void e_param(FILE *f, int flag) {
  char ch = '\0';
  while ((ch = fgetc(f)) != EOF) {
    if (ch == '\n') {
      printf("$");
    }
    flag ? non_printing(ch) : printf("%c", ch);
  }
}

void n_param(FILE *f) {
  char ch = '\0';
  int count = 1;
  while ((ch = fgetc(f)) != EOF) {
    printf("%6d\t", count++);
    while (ch != '\n' && ch != EOF) {
      printf("%c", ch);
      ch = fgetc(f);
    }
    printf("\n");
  }
}

void s_param(FILE *f) {
  char ch = '\0';
  int count = 1;
  while ((ch = fgetc(f)) != EOF) {
    if (ch == '\n') {
      if (count < 2) {
        printf("%c", ch);
        count++;
      }
    } else {
      count = 0;
      printf("%c", ch);
    }
  }
}

void t_param(FILE *f, int flag) {
  char ch = '\0';
  while ((ch = fgetc(f)) != EOF) {
    if (ch == '\t') {
      printf("^I");
    } else {
      flag ? non_printing(ch) : printf("%c", ch);
    }
  }
}

void v_param(FILE *f) {
  char ch = '\0';
  while ((ch = fgetc(f)) != EOF) {
    non_printing(ch);
  }
}

void non_printing(char ch) {
  if (ch < -96) {
    printf("M-^%c", ch + 192);
  } else if (ch < 0) {
    printf("M-%c", ch + 128);
  } else if (ch == 9 || ch == 10) {
    printf("%c", ch);
  } else if (ch < 32) {
    printf("^%c", ch + 64);
  } else if (ch < 127) {
    printf("%c", ch);
  } else {
    printf("^?");
  }
}
