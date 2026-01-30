#include "sprintf/s21_sprintf_core.h"

int s21_sprintf(char* str, const char* format, ...) {
  if (!format) {
    if (str) str[0] = '\0';
    return 0;
  }

  va_list args;
  va_start(args, format);
  const char* fmt = format;
  s21_size buf_len = 0;

  while (*fmt) {
    if (*fmt != '%') {
      if (str) str[buf_len] = *fmt;
      buf_len++;
      fmt++;
    } else {
      int written = 0;
      handle_specifier(str, buf_len, &fmt, &args, &written);
      buf_len += (s21_size)written;
    }
  }

  if (str) str[buf_len] = '\0';
  va_end(args);
  return (int)buf_len;
}
