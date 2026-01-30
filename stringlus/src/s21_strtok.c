#include "s21_string.h"

char* s21_strtok(char* str, const char* delim) {
  static char* next_token = S21_NULL;
  char* current_token = S21_NULL;

  if (str != S21_NULL) {
    next_token = str;
  }

  if (next_token != S21_NULL) {
    while (*next_token != '\0' && s21_strchr(delim, *next_token) != S21_NULL) {
      next_token++;
    }

    if (*next_token != '\0') {
      current_token = next_token;

      while (*next_token != '\0' &&
             s21_strchr(delim, *next_token) == S21_NULL) {
        next_token++;
      }

      if (*next_token != '\0') {
        *next_token = '\0';
        next_token++;
      } else {
        next_token = S21_NULL;
      }
    } else {
      next_token = S21_NULL;
    }
  }

  return current_token;
}