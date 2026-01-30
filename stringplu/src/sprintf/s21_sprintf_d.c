#include "../s21_string.h"
#include "s21_sprintf_handlers.h"

int s21_handle_d(char* buf, long val, flags_t flags, int width, int precision) {
  char str_arg[100] = {'\0'};
  int is_negative = (val < 0);
  unsigned long long unsigned_val = is_negative ? -val : val;
  int length = 0;

  number_to_string(str_arg, unsigned_val, &length);
  apply_precision(str_arg, unsigned_val, precision, &length);
  apply_sign(str_arg, is_negative, flags);
  apply_width(str_arg, width, flags, precision);

  int written = s21_strlen(str_arg);
  if (buf) {
    s21_strncpy(buf, str_arg, written + 1);
  }

  return written;
}