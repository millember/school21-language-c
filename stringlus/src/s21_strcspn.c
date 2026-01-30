#include "s21_string.h"

s21_size s21_strcspn(const char* str1, const char* str2) {
  s21_size result = 0;

  if (str1 == S21_NULL) {
    result = 0;
  } else if (str2 == S21_NULL) {
    result = s21_strlen(str1);
  } else {
    const char* p = str1;
    while (*p && !s21_strchr(str2, *p)) {
      p++;
    }
    result = p - str1;
  }

  return result;
}