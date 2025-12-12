#include "s21_cat.h"

int main(int argc, char *argv[]) {
  CatFlag flag = {0};
  int num = 1;
  int last = '\n';
  int has_files = 0;

  if (argc > 1) {
    parse_f(argc, argv, &flag);
    for (int i = optind; i < argc; i++) {
      print_f(argv[i], flag, &num, &last);
      has_files = 1;
    }
  }

  if (!has_files) {
    process_f(stdin, flag, &num, &last);
  }

  return 0;
}

void parse_f(int argc, char **argv, CatFlag *flags) {
  int opt;
  const char *sh_op = "beEnstTv";
  while ((opt = getopt_long(argc, argv, sh_op, long_options, NULL)) != -1) {
    switch (opt) {
      case 'b':
        flags->number_nonblank = 1;
        break;
      case 'e':
        flags->s_ends = 1;
        flags->s_nonprinting = 1;
        break;
      case 'E':
        flags->s_ends = 1;
        break;
      case 'n':
        flags->number = 1;
        break;
      case 's':
        flags->squeeze_blank = 1;
        break;
      case 't':
        flags->s_tabs = 1;
        flags->s_nonprinting = 1;
        break;
      case 'T':
        flags->s_tabs = 1;
        break;
      case 'v':
        flags->s_nonprinting = 1;
        break;
      default:
        fprintf(stderr, "Usage: %s [-benstv] [file...]", argv[0]);
        break;
    }
  }
  if (flags->number_nonblank) flags->number = 0;
}

void proc_np(int ch) {
  if (ch < 32 && ch != '\t' && ch != '\n')
    printf("^%c", ch + 64);
  else if (ch == 127)
    printf("^?");
  else if (ch > 127 && ch < 160)
    printf("M-^%c", ch - 64);
  else if (ch >= 160)
    printf("M-%c", ch - 128);
  else
    putchar(ch);
}

void proc_ch(int ch, CatFlag flag) {
  if (flag.s_tabs && ch == '\t')
    printf("^I");
  else if (flag.s_ends && ch == '\n')
    printf("$\n");
  else if (flag.s_nonprinting)
    proc_np(ch);
  else
    putchar(ch);
}

int skip_l(CatFlag flag, int last, int ch, int *sq) {
  int result = 0;

  if (flag.squeeze_blank && last == '\n' && ch == '\n') {
    result = *sq;
    *sq = 1;
  } else if (flag.squeeze_blank) {
    *sq = 0;
  }

  return result;
}

void print_n(CatFlag flag, int last, int ch, int *num) {
  if (last == '\n') {
    int should = (flag.number && !flag.number_nonblank) ||
                 (flag.number_nonblank && ch != '\n');
    if (should) printf("%6d\t", (*num)++);
  }
}

void process_f(FILE *stream, CatFlag flag, int *num, int *last) {
  int ch;
  int sq = 0;
  while ((ch = fgetc(stream)) != EOF) {
    int should_skip = skip_l(flag, *last, ch, &sq);

    if (!should_skip) {
      print_n(flag, *last, ch, num);
      proc_ch(ch, flag);
    }

    *last = ch;
  }
}

void print_f(const char *filename, CatFlag flag, int *num, int *last) {
  FILE *file = fopen(filename, "r");
  if (file) {
    process_f(file, flag, num, last);
    fclose(file);
  } else
    fprintf(stderr, "cat: %s: No such file or directory", filename);
}