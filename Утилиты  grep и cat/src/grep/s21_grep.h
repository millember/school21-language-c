#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 8192

typedef struct {
  char *observable_string;
  size_t observable_size;
} grep_data_t;

struct characteristics {
  int lines_count;
  int files_count;
  int empty_lines;
  int e_count;
} characteristics;

struct option flags[] = {
    {"e", no_argument, 0, 'e'}, {"i", no_argument, 0, 'i'},
    {"v", no_argument, 0, 'v'}, {"c", no_argument, 0, 'c'},
    {"l", no_argument, 0, 'l'}, {"n", no_argument, 0, 'n'},
    {"h", no_argument, 0, 'h'}, {"s", no_argument, 0, 's'},
    {"f", no_argument, 0, 'f'}, {"o", no_argument, 0, 'o'},
};

struct flag {
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
  int any_flags;
} flag;

void init_options(grep_data_t *data);
void cleanup_grep_data(grep_data_t *data);
void safe_strcat_to_observable(grep_data_t *data, const char *src);
int check_flags(int argc, char **argv, grep_data_t *data);
void open_file(int argc, char *argv[], grep_data_t *data);
void flag_e(grep_data_t *data);
int flag_f(grep_data_t *data);
void find_and_print(char *argv[], FILE *file, grep_data_t *data);
void print_flag_c_l_h(char *argv[]);
int flags_v_o(int status);
void flag_o(char *buffer, char *argv[], regex_t *regex, regmatch_t *regmatch,
            int *status, size_t file_lines_count, size_t *last_line_count);
void print_regular_line(char *buffer, int is_new_line);
void print_headers(char *argv[], size_t file_lines_count);
void process_matched_line(char *buffer, char *argv[], regex_t *regex,
                          regmatch_t *regmatch, int *status,
                          size_t file_lines_count, size_t *last_line_count);

#endif