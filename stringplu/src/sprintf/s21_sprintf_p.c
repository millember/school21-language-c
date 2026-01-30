#include <stddef.h>

#include "../sprintf/s21_sprintf_types.h"

int s21_handle_p(char* buf, void* ptr, flags_t flags, int width) {
  unsigned long addr = (unsigned long)ptr;
  char hex[32];
  int hex_len = 0;

  if (addr == 0) {
    hex[hex_len++] = '0';
  } else {
    char digits[] = "0123456789abcdef";
    unsigned long tmp = addr;
    char rev[32];
    int i = 0;
    while (tmp) {
      rev[i++] = digits[tmp & 0xF];
      tmp >>= 4;
    }
    for (int j = i - 1; j >= 0; j--) {
      hex[hex_len++] = rev[j];
    }
  }

  int min_hex_width = hex_len;
  if (flags.zero && !flags.minus && width > 2) {
    min_hex_width = width - 2;
  }

  int pad_hex = (min_hex_width > hex_len) ? min_hex_width - hex_len : 0;
  int content_len = 2 + hex_len + pad_hex;
  int total_len = (width > content_len) ? width : content_len;

  int pos = 0;

  if (!flags.minus) {
    int left_pad = total_len - content_len;
    for (int i = 0; i < left_pad; i++) {
      if (buf) buf[pos] = ' ';
      pos++;
    }
  }

  if (buf) {
    buf[pos] = '0';
    buf[pos + 1] = 'x';
  }
  pos += 2;

  for (int i = 0; i < pad_hex; i++) {
    if (buf) buf[pos] = '0';
    pos++;
  }

  for (int i = 0; i < hex_len; i++) {
    if (buf) buf[pos] = hex[i];
    pos++;
  }

  if (flags.minus) {
    int right_pad = total_len - content_len;
    for (int i = 0; i < right_pad; i++) {
      if (buf) buf[pos] = ' ';
      pos++;
    }
  }

  return total_len;
}
