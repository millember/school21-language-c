#include "s21_string.h"  // ← подключаем, чтобы знать про s21_size

s21_size s21_strlen(const char* str) {
  s21_size len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}