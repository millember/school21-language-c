#include "s21_string.h"

int s21_memcmp(const void* str1, const void* str2, s21_size n) {
  int result = 0;
  const unsigned char* s1 = (const unsigned char*)str1;
  const unsigned char* s2 = (const unsigned char*)str2;
  if ((str1) && (str2) && (n > 0)) {
    for (s21_size i = 0; i < n && !result; i++) {
      if ((s1[i] != s2[i])) {
        result = s1[i] - s2[i];
      }
    }
  }
  return result;
}