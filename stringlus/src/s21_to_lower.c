#include "s21_string.h"

void* s21_to_lower(const char* str) {
  void* result = S21_NULL;

  if (str != S21_NULL) {
    s21_size length = s21_strlen(str);

    char* buffer = (char*)malloc((length + 1) * sizeof(char));
    if (buffer != S21_NULL) {
      for (s21_size i = 0; i < length; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          buffer[i] = str[i] + 32;
        } else {
          buffer[i] = str[i];
        }
      }
      buffer[length] = '\0';
      result = (void*)buffer;
    }
  }

  return result;
}
