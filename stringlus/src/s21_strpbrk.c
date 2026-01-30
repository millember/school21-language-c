#include "s21_string.h"

char* s21_strpbrk(const char* str1, const char* str2) {
  char* result = S21_NULL;

  if (str1 && str2) {
    for (const char* s1 = str1; *s1 && !result; s1++) {
      if (s21_strchr(str2, *s1)) {
        result = (char*)s1;
      }
    }
  }

  return result;
}