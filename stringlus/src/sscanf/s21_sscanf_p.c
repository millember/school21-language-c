#include <ctype.h>

#include "../s21_string.h"

int s21_sscanf_p(const char** str, void** out, int width, int assign) {
  int result = 0, digits_read = 0, continue_reading = 1, has_prefix = 0;
  unsigned long long value = 0;
  const char* after_spaces;

  while (isspace(**str)) (*str)++;
  after_spaces = *str;
  if ((width == 0 || width >= 2) && **str == '0' &&
      (*(*str + 1) == 'x' || *(*str + 1) == 'X')) {
    has_prefix = 1;
    (*str) += 2;
    if (width > 0) width -= 2;
  }
  while (continue_reading && (width == 0 || width > 0) && **str) {
    char c = **str;
    unsigned int digit = 0;
    int valid_digit = 0;
    if (c >= '0' && c <= '9') {
      digit = c - '0';
      valid_digit = 1;
    } else if (c >= 'a' && c <= 'f') {
      digit = c - 'a' + 10;
      valid_digit = 1;
    } else if (c >= 'A' && c <= 'F') {
      digit = c - 'A' + 10;
      valid_digit = 1;
    }
    if (valid_digit) {
      digits_read++;
      value = value * 16 + digit;
      (*str)++;
      if (width > 0) {
        width--;
        if (width == 0) continue_reading = 0;
      }
    } else {
      continue_reading = 0;
    }
  }
  if (digits_read > 0 || has_prefix) {
    if (assign && out != S21_NULL) *out = (void*)(uintptr_t)value;
    result = 1;
  } else {
    *str = after_spaces;
    result = 0;
  }
  return result;
}