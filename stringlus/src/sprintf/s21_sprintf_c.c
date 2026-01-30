#include "../sprintf/s21_sprintf_handlers.h"

int s21_handle_c(char* buf, char c, flags_t flags, int width, int precision) {
  (void)precision;  // precision игнорируется для %c //
  int count = 0;
  int padding = 0;
  int i = 0;
  char pad = ' ';

  if (width > 1) {
    padding = width - 1;
  }

  if (flags.minus == 0 && flags.zero) {
    pad = '0';
  }

  if (flags.minus) {
    if (buf) {
      buf[count] = c;
    }
    count++;
  }

  while (i < padding) {
    if (buf) {
      buf[count] = pad;
    }
    count++;
    i++;
  }

  if (!flags.minus) {
    if (buf) {
      buf[count] = c;
    }
    count++;
  }

  return count;
}
