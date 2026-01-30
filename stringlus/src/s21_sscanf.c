#include <ctype.h>

#include "sscanf/s21_sscanf_core.h"

int s21_sscanf(const char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);

  const char* src = str;
  const char* fmt = format;
  int assigned = 0;
  int error = 0;

  while (fmt && *fmt && src && !error) {
    if (isspace((unsigned char)*fmt)) {
      while (isspace((unsigned char)*fmt)) fmt++; /* пропуск пробелов формата */
      while (isspace((unsigned char)*src)) src++;
      continue;
    }

    if (*fmt != '%') {
      if (*src != *fmt)
        error = 1;
      else {
        src++;
        fmt++;
      }
      continue;
    }

    fmt++;

    int assign = 1;
    if (*fmt == '*') {
      assign = 0;
      fmt++;
    }

    int width = 0;
    while (*fmt >= '0' && *fmt <= '9') {
      width = width * 10 + (*fmt - '0');
      fmt++;
    }

    char length = 0;
    switch (*fmt) {
      case 'h':
      case 'l':
        length = *fmt;
        fmt++;
        if (*fmt == length) fmt++;
        break;
      case 'L':
        length = *fmt;
        fmt++;
        break;
      default:
        break;
    }

    char spec = *fmt ? *fmt++ : '\0';

    s21_sscanf_handle_specifier(&src, str, spec, length, width, assign, &args,
                                &assigned, &error);
  }

  va_end(args);
  return assigned;
}
