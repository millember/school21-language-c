#include "../s21_string.h"
#include "s21_sprintf_handlers.h"

int s21_handle_f(char* buf, long double val, char spec, flags_t flags,
                 int width, int precision) {
  char str[100] = {0};
  int length = 0;

  int is_negative = val < 0;
  if (is_negative) val = -val;

  if (precision == -1) precision = 6;
  if (spec == 'f') {
    format_fixed_point(val, precision, flags.sharp, str, &length);
  } else if (spec == 'e' || spec == 'E') {
    format_exponential(val, precision, spec, str, &length);
  } else if (spec == 'g' || spec == 'G') {
    handle_g_format(val, &precision, spec, flags.sharp, str, &length);
  }

  apply_sign(str, is_negative, flags);
  apply_width(str, width, flags, precision);
  length = s21_strlen(str);

  s21_strncpy(buf, str, length + 1);
  return length;
}