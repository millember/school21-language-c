#include <ctype.h>
#include <limits.h>

int s21_sscanf_s(const char** str, char* out, int width, int assign) {
  int result = 0;

  if (str && *str) {
    int count = 0;

    while (**str && isspace(**str)) {
      (*str)++;
    }

    const char* start = *str;
    int max_chars = (width > 0 && width < INT_MAX) ? width : INT_MAX;

    while (*start && !isspace(*start) && count < max_chars) {
      if (assign && out) {
        out[count] = *start;
      }

      start++;
      count++;
    }

    if (count > 0) {
      if (assign && out) {
        out[count] = '\0';
      }
      *str = start;
      result = assign;
    }
  }

  return result;
}
