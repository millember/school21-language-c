#include "s21_string.h"

int s21_strncmp(const char* str1, const char* str2, s21_size n) {
  s21_size i = 0;
  int result = 0;

  while (i < n && result == 0) {
    unsigned char c1 = (unsigned char)str1[i];
    unsigned char c2 = (unsigned char)str2[i];

    if (c1 != c2) {
      result = (int)c1 - (int)c2;
    } else if (c1 == '\0') {
      break;
    }
    i++;
  }

  return result;
}