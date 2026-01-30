#include "s21_string.h"

char* s21_strncat(char* dest, const char* src, s21_size n) {
  char* original_dest = dest;

  // Находим конец строки dest
  while (*dest != '\0') {
    dest++;
  }

  // Копируем не более n символов из src
  s21_size i = 0;
  while (i < n && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }

  // Завершаем результирующую строку нулём
  dest[i] = '\0';

  return original_dest;
}