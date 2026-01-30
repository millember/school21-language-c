#include "s21_sprintf_handlers.h"

static void convert_uint_to_hex(unsigned long val, char* buffer, char spec) {
  static const char hex_lower[] = "0123456789abcdef";
  static const char hex_upper[] = "0123456789ABCDEF";
  const char* hex_digits = (spec == 'x') ? hex_lower : hex_upper;
  if (val == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    return;
  }
  char temp[32] = {0};
  int i = 0;
  while (val > 0) {
    temp[i++] = hex_digits[val % 16];
    val /= 16;
  }
  for (int j = 0; j < i; j++) {
    buffer[j] = temp[i - j - 1];
  }
  buffer[i] = '\0';
}

int s21_handle_x(char* buf, unsigned long val, char spec, flags_t flags,
                 int width, int precision) {
  char num_str[32];
  convert_uint_to_hex(val, num_str, spec);
  int len = 0;
  while (num_str[len] != '\0') len++;
  int has_prefix = (flags.sharp && val != 0) ? 2 : 0;
  int prefix_len = has_prefix;
  int zero_pad = 0;
  if (precision > len) zero_pad = precision - len;
  int total_len = len + zero_pad + prefix_len;
  int space_pad = (width > total_len) ? width - total_len : 0;
  int written = 0;
  if (!flags.minus && !flags.zero) {
    for (int i = 0; i < space_pad; i++) {
      if (buf) buf[written] = ' ';
      written++;
    }
  }
  if (has_prefix) {
    if (buf) buf[written] = '0';
    written++;
    if (buf) buf[written] = spec;
    written++;
  }
  if (!flags.minus && flags.zero) {
    for (int i = 0; i < space_pad; i++) {
      if (buf) buf[written] = '0';
      written++;
    }
  }
  for (int i = 0; i < zero_pad; i++) {
    if (buf) buf[written] = '0';
    written++;
  }
  for (int i = 0; i < len; i++) {
    if (buf) buf[written] = num_str[i];
    written++;
  }
  if (flags.minus) {
    for (int i = 0; i < space_pad; i++) {
      if (buf) buf[written] = ' ';
      written++;
    }
  }
  return written;
}