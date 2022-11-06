#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char get_opt;
  int error = 0, count_templates = 0;
  regex_t templates[MAX_COUNT_TEMPLATES];

  while (!error && (get_opt = getopt(argc, argv, ":e:ivclnhsf:o")) != -1) {
    switch (get_opt) {
      case 'f':
        options.f = 1;
        if ((error = read_file_templates(templates, &count_templates, optarg)))
          printf("%s: No such file or directory\n", optarg);
        break;
      case 'e':
        options.e = 1;
        regcomp(&templates[count_templates++], optarg,
                options.i ? REG_ICASE : REG_EXTENDED);
        break;
      case 'i':
        options.i = 1;
        break;
      case 'v':
        options.v = 1;
        break;
      case 'c':
        options.c = 1;
        break;
      case 'l':
        options.l = 1;
        break;
      case 'n':
        options.n = 1;
        break;
      case 'h':
        options.h = 1;
        break;
      case 's':
        options.s = 1;
        break;
      case 'o':
        options.o = 1;
        break;
      default:
        error = 1;
        break;
    }
  }

  if (!error && (optind + 1 - (options.f || options.e)) < argc) {
    if (!(options.f || options.e))
      regcomp(&templates[count_templates++], argv[optind++],
              options.i ? REG_ICASE : REG_EXTENDED);
    if (optind == argc - 1) options.h = 1;
    while (optind < argc) {
      if (print_matches(templates, count_templates, argv[optind]) && !options.s)
        printf("%s: No such file or directory\n", argv[optind]);
      optind++;
    }
  } else
    printf("Error!");

  free_templates(templates, count_templates);

  return 0;
}

int print_matches(regex_t *templates, int count_templates, char *filename) {
  int result, line_len, line_count = 0, match_count = 0, offset = 0;
  char line[MAX_LINE_LENGTH], match = 0;
  FILE *f = fopen(filename, "r");

  !f ? (result = 0) : (result = 1);

  while (result && feof(f) == 0 && fgets(line, MAX_LINE_LENGTH, f)) {
    match = 0;
    line_len = strlen(line);
    line_count++;
    for (int i = 0; i < count_templates; i++) {
      offset = 0;
      regmatch_t regmatch;
      while (!regexec(&templates[i], &line[offset], 1, &regmatch, 0)) {
        if (options.o && !options.v && !options.c && !options.l) {
          if (!offset && !options.h) printf("%s:", filename);
          if (!offset && options.n) printf("%d:", line_count);
          while (regmatch.rm_so < regmatch.rm_eo) {
            printf("%c", line[offset + regmatch.rm_so]);
            regmatch.rm_so++;
          }
          printf("\n");
        }
        match = 1;
        offset += regmatch.rm_eo;
      }
    }
    if (options.v) match = !match;

    match_count += match;

    if (match && !options.c && !options.l && (!options.o || options.v)) {
      if (!options.h) printf("%s:", filename);
      if (options.n) printf("%d:", line_count);
      for (int i = 0; i < line_len && line[i] != '\n'; i++)
        printf("%c", line[i]);
      printf("\n");
    }
  }

  if (options.c) {
    if (!options.h) printf("%s:", filename);
    if (options.l) match_count = 1;
    printf("%d\n", match_count);
  }

  if (options.l)
    if (match_count > 0) printf("%s\n", filename);

  if (result) fclose(f);

  return !result;
}

void free_templates(regex_t *templates, int count) {
  for (int i = 0; i < count; i++) regfree(&templates[i]);
}

int read_file_templates(regex_t *templates, int *count_templates,
                        char *filename) {
  int result, line_len;
  char line[MAX_LINE_LENGTH];
  FILE *f = fopen(filename, "r");

  !f ? (result = 0) : (result = 1);

  while (result && feof(f) == 0 && fgets(line, MAX_LINE_LENGTH, f)) {
    line_len = strlen(line);

    if (line[line_len - 1] == '\n') line[line_len - 1] = '\0';

    regcomp(&templates[(*count_templates)++], line,
            options.i ? REG_ICASE : REG_EXTENDED);
  }

  if (result) fclose(f);

  return !result;
}
