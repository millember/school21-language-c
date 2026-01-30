#include "s21_sscanf_handlers.h"

int s21_sscanf_percent(const char** src) {
  int res = -1;
  if (**src == '%') {
    (*src)++;
    res = 1;
  }
  return res;
}