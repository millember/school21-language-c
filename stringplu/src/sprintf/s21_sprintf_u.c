#include "../s21_string.h"
#include "s21_sprintf_handlers.h"

int s21_handle_u(char* buf, unsigned long val, flags_t flags, int width,
                 int precision) {
  char str[256] = {0};
  int length = 0;

  number_to_string(str, (unsigned long long)val, &length);
  apply_precision(str, (unsigned long long)val, precision, &length);
  length = s21_strlen(str);
  apply_width(str, width, flags, precision);

  int result_length = s21_strlen(str);
  s21_strncpy(buf, str, result_length + 1);

  return result_length;
}