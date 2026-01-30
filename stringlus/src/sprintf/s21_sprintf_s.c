#include "../s21_string.h"
#include "s21_sprintf_handlers.h"

int s21_handle_s(char* buf, const char* str, flags_t flags, int width,
                 int precision) {
  char temp[1024] = {0};
  int length = 0;

  if (str == S21_NULL) {
    s21_strncpy(temp, "(null)", 1023);
  } else {
    s21_strncpy(temp, str, 1023);
  }
  temp[1023] = '\0';

  if (precision >= 0) {
    int actual_len = s21_strlen(temp);
    if (precision < actual_len) {
      temp[precision] = '\0';
    }
  }

  length = s21_strlen(temp);

  if (width > length) {
    int padding = width - length;

    if (flags.minus) {
      append_spaces(temp, padding);
    } else {
      char pad_char = flags.zero ? '0' : ' ';
      prepend_symbols(temp, padding, pad_char);
    }
  }

  length = s21_strlen(temp);
  if (buf != S21_NULL) {
    s21_strncpy(buf, temp, length + 1);
  }

  return length;
}