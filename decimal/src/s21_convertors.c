#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag = 0;
  if (dst == NULL) flag = 1;
  clean_decimal(dst);
  if (src < 0) {
    set_sign(dst, S21_NEG);
    src *= (-1);
  }
  dst->bits[0] = src;
  return flag;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = 0;
  if (dst == NULL || !is_decimal_correct(src)) flag = 1;
  s21_decimal buf = {0};
  s21_truncate(src, &buf);
  int sign = get_sign(src);
  if (buf.bits[1] || buf.bits[2] ||
      (get_bit_decimal(buf, BLOCK_BITS - 1) && sign == S21_POS))
    flag = 1;
  else {
    *dst = buf.bits[0];
    if (sign == S21_NEG) *dst *= (-1);
  }
  return flag;
}
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int flag = 0;
  if (dst == NULL || !is_decimal_correct(src))
    flag = 1;
  else {
    double buf = 0.0;
    for (int i = 0; i < MANTISS_BITS; i++) {
      buf += get_bit_decimal(src, i) * pow(2, i);
    }
    double power = pow(10, get_scale(src));
    buf /= power;
    if (get_sign(src) == S21_NEG) buf *= -1;
    *dst = buf;
  }
  return flag;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int flag = 0;
  if (isnan(src) || isinf(src) || dst == NULL || src > MAX_FLOAT_TO_CONVERT)
    flag = 1;
  else {
    clean_decimal(dst);
    float_cast fl = {0};
    fl.fl = src;
    int sign = fl.parts.sign, exp = fl.parts.exponent - 127;
    if (src != 0) {
      double temp = (double)fabs(src);
      int off = 0;
      for (; off < 28 && temp <= 1000000; temp *= 10, off++) {
      }
      temp = round(temp);
      if (exp > -127 && exp < 127) {
        float_cast mant = {0};
        temp = (float)temp;
        for (; (int)temp % 10 == 0 && off > 0; off--, temp /= 10) {
        }
        mant.fl = temp;
        exp = mant.parts.exponent - 127;
        set_bit_decimal(dst, exp, 1);
        int i = 0, j = 0;
        for (i = exp - 1, j = 22; j >= 0; i--, j--) {
          if ((mant.bytes & (1 << j))) set_bit_decimal(dst, i, 1);
        }
        set_sign(dst, sign);
        set_scale(dst, off);
      }
    }
  }
  return flag;
}
