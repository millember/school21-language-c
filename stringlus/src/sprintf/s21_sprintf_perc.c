#include "../s21_string.h"
#include "s21_sprintf_handlers.h"

int s21_handle_percent(char* buf, flags_t flags, int width) {
  char str[256] = "%";
  int length = 1;

  apply_width(str, width, flags, -1);
  length = s21_strlen(str);

  s21_strncpy(buf, str, length + 1);

  return length;
}