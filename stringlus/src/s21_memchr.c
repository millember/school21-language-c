#include "s21_string.h"

void* s21_memchr(const void* str, int c, s21_size n) {
  void* result = S21_NULL;
  unsigned char chr = (unsigned char)c;
  char* s = (char*)str;
  if (str != S21_NULL) {
    for (s21_size i = 0; i < n && !result; i++) {
      if (chr == s[i]) {
        result = (void*)(s + i);
      }
    }
  }
  return result;
}