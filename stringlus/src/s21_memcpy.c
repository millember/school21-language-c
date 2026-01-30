#include "s21_string.h"

void* s21_memcpy(void* dest, const void* src, s21_size n) {
  unsigned char* str_dest = (unsigned char*)dest;
  const unsigned char* str_src = (unsigned char*)src;

  for (s21_size i = 0; i < n; i++) str_dest[i] = str_src[i];
  return dest;
}