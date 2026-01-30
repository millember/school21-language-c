#include "s21_string.h"

char* s21_strstr(const char* haystack, const char* needle) {
  char* result = S21_NULL;

  if (haystack && needle) {
    if (*needle == '\0') {
      result = (char*)haystack;
    } else {
      s21_size len = s21_strlen(needle);

      for (const char* ptr = haystack; *ptr && !result; ptr++) {
        if (s21_strncmp(ptr, needle, len) == 0) result = (char*)ptr;
      }
    }
  }

  return result;
}