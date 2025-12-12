#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int number;
  int number_nonblank;
  int squeeze_blank;
  int s_nonprinting;
  int s_ends;
  int s_tabs;
} CatFlag;

static struct option long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {"show-ends", no_argument, NULL, 'E'},
    {"show-tabs", no_argument, NULL, 'T'},
    {NULL, 0, NULL, 0}};

void print_f(const char *filename, CatFlag flag, int *num, int *last);
void process_f(FILE *stream, CatFlag flag, int *num, int *last);
void parse_f(int argc, char **argv, CatFlag *flags);
void proc_np(int ch);
void proc_ch(int ch, CatFlag flag);
int skip_l(CatFlag flag, int last, int ch, int *sq);
void print_n(CatFlag flag, int last, int ch, int *num);

#endif