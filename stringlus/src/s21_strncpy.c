#include "s21_string.h"

char* s21_strncpy(char* dest, const char* src, s21_size n) {
  char* result = dest;

  if (dest != S21_NULL && src != S21_NULL) {
    s21_size i = 0;
    for (; i < n && src[i] != '\0'; i++) {
      dest[i] = src[i];
    }
    for (; i < n; i++) {
      dest[i] = '\0';
    }
  }

  return result;
}