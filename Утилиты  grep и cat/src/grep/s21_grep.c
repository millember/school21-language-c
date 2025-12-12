#include "s21_grep.h"

int main(int argc, char *argv[]) {
  int error = 0;
  grep_data_t data = {0};

  init_options(&data);
  error = check_flags(argc, argv, &data);
  if (!error) open_file(argc, argv, &data);

  cleanup_grep_data(&data);
  return 0;
}

void init_options(grep_data_t *data) {
  flag.e = 0;
  flag.i = 0;
  flag.v = 0;
  flag.c = 0;
  flag.l = 0;
  flag.n = 0;
  flag.h = 0;
  flag.s = 0;
  flag.f = 0;
  flag.o = 0;

  characteristics.lines_count = 0;
  characteristics.files_count = 0;
  characteristics.empty_lines = 0;
  characteristics.e_count = 0;

  data->observable_string = malloc(BUFFSIZE);
  data->observable_size = BUFFSIZE;
  if (data->observable_string) {
    data->observable_string[0] = '\0';
  }
}

void cleanup_grep_data(grep_data_t *data) {
  if (data->observable_string) {
    free(data->observable_string);
    data->observable_string = NULL;
    data->observable_size = 0;
  }
}

void safe_strcat_to_observable(grep_data_t *data, const char *src) {
  if (!data->observable_string || !src) return;

  size_t current_len = strlen(data->observable_string);
  size_t src_len = strlen(src);
  size_t total_len = current_len + src_len + 1;

  if (total_len >= data->observable_size) {
    size_t new_size = total_len * 2;
    char *new_buf = realloc(data->observable_string, new_size);
    if (new_buf) {
      data->observable_string = new_buf;
      data->observable_size = new_size;
    } else {
      return;
    }
  }

  strcat(data->observable_string, src);
}

int check_flags(int argc, char **argv, grep_data_t *data) {
  int error = 0;
  int rez;
  opterr = 0;
  while ((rez = getopt_long(argc, argv, "e:ivclnhsf:o", flags, 0)) != -1) {
    flag.any_flags = 1;
    if (rez == 'e') {
      flag.e = 1;
      ++characteristics.e_count;
      flag_e(data);
    } else if (rez == 'i')
      flag.i = 1;
    else if (rez == 'v')
      flag.v = 1;
    else if (rez == 'c')
      flag.c = 1;
    else if (rez == 'l')
      flag.l = 1;
    else if (rez == 'n')
      flag.n = 1;
    else if (rez == 'h')
      flag.h = 1;
    else if (rez == 's')
      flag.s = 1;
    else if (rez == 'f') {
      flag.f = 1;
      error = flag_f(data);
    } else if (rez == 'o')
      flag.o = 1;
    else if (rez == '?')
      error = 1;
  }
  if (characteristics.empty_lines) flag.o = 0;
  if (!flag.e && !flag.f) safe_strcat_to_observable(data, argv[optind++]);
  return error;
}

void open_file(int argc, char *argv[], grep_data_t *data) {
  characteristics.files_count = argc - optind;
  while (optind < argc) {
    FILE *file;
    if ((file = fopen(argv[optind], "r")) != NULL) {
      find_and_print(argv, file, data);
      fclose(file);
    } else if (!flag.s) {
      fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
    }
    ++optind;
  }
}

void flag_e(grep_data_t *data) {
  if (characteristics.e_count > 1) safe_strcat_to_observable(data, "|");
  safe_strcat_to_observable(data, optarg);
}

int flag_f(grep_data_t *data) {
  FILE *file = NULL;
  char buffer[BUFFSIZE] = {0};
  int error = 0;
  if ((file = fopen(optarg, "r"))) {
    fseek(file, 0, SEEK_SET);
    while (fgets(buffer, BUFFSIZE, file) != NULL) {
      if (buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = 0;
      if (characteristics.e_count > 0) safe_strcat_to_observable(data, "|");
      if (*buffer == '\0') {
        characteristics.empty_lines = 1;
        safe_strcat_to_observable(data, ".");
      } else {
        safe_strcat_to_observable(data, buffer);
      }
      ++characteristics.e_count;
    }
    fclose(file);
  } else {
    fprintf(stderr, "File not found\n");
    error = 1;
  }
  return error;
}

void find_and_print(char *argv[], FILE *file, grep_data_t *data) {
  regex_t regex;
  int cflags = REG_EXTENDED;

  char buffer[BUFFSIZE];
  int nmatch = 1;
  regmatch_t regmatch[1] = {0};
  int status;

  size_t last_line_count;
  size_t file_lines_count = 1;
  characteristics.lines_count = 0;

  if (flag.i) cflags |= REG_ICASE;
  regcomp(&regex, data->observable_string, cflags);

  while (!feof(file)) {
    if (fgets(buffer, BUFFSIZE, file)) {
      status = regexec(&regex, buffer, nmatch, regmatch, 0);
      status = flags_v_o(status);
      if (status != REG_NOMATCH) {
        process_matched_line(buffer, argv, &regex, regmatch, &status,
                             file_lines_count, &last_line_count);
      }
      ++file_lines_count;
    }
  }

  print_flag_c_l_h(argv);
  regfree(&regex);
}

void process_matched_line(char *buffer, char *argv[], regex_t *regex,
                          regmatch_t *regmatch, int *status,
                          size_t file_lines_count, size_t *last_line_count) {
  if (!flag.c && !flag.l) {
    print_headers(argv, file_lines_count);

    if (flag.o && !flag.v) {
      flag_o(buffer, argv, regex, regmatch, status, file_lines_count,
             last_line_count);
    } else {
      print_regular_line(buffer, 1);
    }
  }
  ++characteristics.lines_count;
}

void print_flag_c_l_h(char *argv[]) {
  if (flag.c) {
    if (!flag.h && characteristics.files_count > 1) printf("%s:", argv[optind]);
    if (flag.l && characteristics.lines_count)
      printf("1\n");
    else
      printf("%d\n", characteristics.lines_count);
  }

  if (flag.l && characteristics.lines_count) printf("%s\n", argv[optind]);
}

int flags_v_o(int status) {
  if (flag.v) status = status ? 0 : 1;
  if (flag.v == 1 && flag.o == 1) flag.o = 0;
  return status;
}

void flag_o(char *buffer, char *argv[], regex_t *regex, regmatch_t *regmatch,
            int *status, size_t file_lines_count, size_t *last_line_count) {
  char *ptr = buffer;
  while (!*status && regmatch[0].rm_eo != regmatch[0].rm_so) {
    if (!flag.h && characteristics.files_count > 1 &&
        *last_line_count == file_lines_count)
      printf("%s:", argv[optind]);
    if (flag.n) printf("%lu:", file_lines_count);
    printf("%.*s\n", (int)(regmatch[0].rm_eo - regmatch[0].rm_so),
           ptr + regmatch[0].rm_so);
    ptr += regmatch[0].rm_eo;
    *status = regexec(regex, ptr, 1, regmatch, REG_NOTBOL);
    *last_line_count = file_lines_count;
  }
}

void print_regular_line(char *buffer, int is_new_line) {
  printf("%s", buffer);
  if (buffer[strlen(buffer) - 1] != '\n' && is_new_line) printf("\n");
}

void print_headers(char *argv[], size_t file_lines_count) {
  if (!flag.h && characteristics.files_count > 1) printf("%s:", argv[optind]);
  if (flag.n && !flag.o) printf("%lu:", file_lines_count);
}