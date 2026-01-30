#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL) {
    error = 1;
  } else {
    apply_rounding_operation(value, result);
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL) {
    error = 1;
  } else {
    int remainder = apply_rounding_operation(value, result);

    if (remainder % 10 >= 5) {
      int sign = get_sign(*result);
      plus_one(result);
      if (sign) {
        set_sign(result, 1);
      }
    }
  }
  return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL) {
    error = 1;
  } else {
    int remainder = apply_rounding_operation(value, result);

    if (get_sign(value) && remainder >= 10) {
      int sign = get_sign(*result);
      plus_one(result);
      if (sign) {
        set_sign(result, 1);
      }
    }
  }
  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL) {
    error = 1;
  } else {
    *result = value;
    set_sign(result, get_sign(value) ^ 1);
  }
  return error;
}