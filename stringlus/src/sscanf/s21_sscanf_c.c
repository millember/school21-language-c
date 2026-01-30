#include "s21_sscanf_handlers.h"

int s21_sscanf_c(const char** str, char* out, int width, int assign) {
  int result = 0;

  if (width <= 0) {
    width = 1;
  }

  if (str && *str) {
    const char* src = *str;
    if (*src == '\0') {
      // пусто — result = 0
    } else {
      int counter = 0;
      while (counter < width && src[counter] != '\0') {
        if (assign && out) {
          out[counter] = src[counter];
        }
        counter++;
      }
      if (counter > 0) {
        *str = src + counter;
        result = (assign && out) ? 1 : 0;  // ← ИСПРАВЛЕНО
      }
    }
  }
  return result;
}