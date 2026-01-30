#include <ctype.h>
#include <math.h>

#include "s21_sscanf_handlers.h"

int s21_sscanf_f(const char** str, void* out, int width, int assign,
                 char length) {
  const char* p = *str;

  int count = 0;
#define CAN_READ() ((width <= 0) || (count < width))

  while (isspace((unsigned char)*p)) p++;
  const char* start = p;

  int sign = 1;
  if (CAN_READ() && (*p == '+' || *p == '-')) {
    sign = (*p == '-') ? -1 : 1;
    p++;
    count++;
  }

  long double value = 0.0L;
  while (CAN_READ() && isdigit((unsigned char)*p)) {
    value = value * 10 + (*p - '0');
    p++;
    count++;
  }

  if (CAN_READ() && *p == '.') {
    p++;
    count++;
    long double frac = 0.1L;

    while (CAN_READ() && isdigit((unsigned char)*p)) {
      value += (*p - '0') * frac;
      frac *= 0.1L;
      p++;
      count++;
    }
  }

  if (CAN_READ() && (*p == 'e' || *p == 'E')) {
    p++;
    count++;
    int exp_sign = 1;
    if (CAN_READ() && (*p == '+' || *p == '-')) {
      exp_sign = (*p == '-') ? -1 : 1;
      p++;
      count++;
    }
    int exponent = 0;
    while (CAN_READ() && isdigit((unsigned char)*p)) {
      exponent = exponent * 10 + (*p - '0');
      p++;
      count++;
    }
    value *= powl(10.0L, (long double)(exp_sign * exponent));
  }

  if (p != start) {
    value *= sign;
    if (assign) {
      if (length == 'L') {
        *(long double*)out = value;
      } else if (length == 'l') {
        *(double*)out = (double)value;
      } else {
        *(float*)out = (float)value;
      }
    }
  }
  *str = p;
  return (p != start) ? assign : 0;
}