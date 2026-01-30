#include "s21_string.h"

char* s21_strchr(const char* str, int c) {
  char* result = S21_NULL;

  if (str != S21_NULL) {
    const char* ptr = str;
    unsigned char ch = (unsigned char)c;

    while (*ptr != ch && *ptr != '\0') {
      ptr++;
    }
    if (*ptr == ch) {
      result = (char*)ptr;
    }
  }
  return result;
}