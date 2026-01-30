#include <ctype.h>

int s21_sscanf_x(const char** str, void* out, char spec, int width, int assign,
                 char length) {
  const char* p = *str;

  int count = 0;

  int base = 10;
  unsigned long long value = 0;

#define CAN_READ() (width <= 0 || count < width)

  while (isspace((unsigned char)*p)) p++;

  int parsed_digit = 0;

  if (spec == 'o') {
    base = 8;
  } else if (spec == 'x') {
    base = 16;
    if (CAN_READ() && *p == '0') {
      p++;
      count++;
      if (CAN_READ() && (*p == 'x' || *p == 'X')) {
        p++;
        count++;
      }
    }
  }

  int parsing = 1;
  while (parsing && CAN_READ()) {
    int digit = -1;
    unsigned char c = *p;
    if (c >= '0' && c <= '9') {
      digit = c - '0';
    } else if (base == 16 && c >= 'a' && c <= 'f') {
      digit = c - 'a' + 10;
    } else if (base == 16 && c >= 'A' && c <= 'F') {
      digit = c - 'A' + 10;
    }

    if (digit >= 0 && digit < base) {
      value = value * base + (unsigned long long)digit;
      p++;
      count++;
      parsed_digit = 1;
    } else {
      parsing = 0;
    }
  }

  int result = 0;
  if (parsed_digit) {
    if (assign) {
      if (length == 'h') {
        *(unsigned short*)out = (unsigned short)value;
      } else if (length == 'l') {
        *(unsigned long*)out = (unsigned long)value;
      } else if (length == 'L') {
        *(unsigned long long*)out = value;
      } else {
        *(unsigned int*)out = (unsigned int)value;
      }
    }
    result = assign;
  }

  *str = p;
  return result;
}
