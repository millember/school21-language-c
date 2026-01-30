#include "s21_string.h"

char* s21_strrchr(const char* str, int c) {
  char* result = S21_NULL;

  if (str != S21_NULL) {
    unsigned char ch = (unsigned char)c;
    const char* end = str + s21_strlen(str);

    if (ch == '\0') {
      result = (char*)end;
    } else {
      while (end >= str && result == S21_NULL) {
        if (*end == ch) result = (char*)end;
        end--;
      }
    }
  }

  return result;
}