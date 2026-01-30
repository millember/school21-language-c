#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (is_zero_decimal(&value_1)) clean_decimal(&value_1);
  if (is_zero_decimal(&value_2)) clean_decimal(&value_2);
  clean_decimal(result);

  s21_arifmetic_error error = OK;
  int final_sign = (get_sign(value_1) && get_sign(value_2)) ? 1 : 0;

  if (get_sign(value_1) != get_sign(value_2)) {
    int sign1 = get_sign(value_1);
    int sign2 = get_sign(value_2);
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);

    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    int scale1 = 0, scale2 = 0, max_scale = 0;

    prepare_big_decimals(value_1, value_2, &v1, &v2, &scale1, &scale2,
                         &max_scale);

    // Используем новую функцию
    align_scales(&v1, &v2, scale1, scale2, max_scale);

    int cmp = compare_big_decimals(v1, v2);

    if (cmp == 0) {
      clean_decimal(result);
    } else if (cmp > 0) {
      sub_big_decimal(v1, v2, &r);
      final_sign = sign1;
    } else {
      sub_big_decimal(v2, v1, &r);
      final_sign = sign2;
    }

    normalize_big_to_decimal(&r, &max_scale, result);

    if (final_sign && !is_zero_decimal(result)) {
      set_sign(result, 1);
    }
  } else {
    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    int scale1 = 0, scale2 = 0, max_scale = 0;

    prepare_big_decimals(value_1, value_2, &v1, &v2, &scale1, &scale2,
                         &max_scale);

    // Используем ту же функцию
    align_scales(&v1, &v2, scale1, scale2, max_scale);

    add_big_decimal(v1, v2, &r);
    error = process_big_decimal_result(r, max_scale, final_sign, result);
  }

  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (is_zero_decimal(&value_1)) clean_decimal(&value_1);
  if (is_zero_decimal(&value_2)) clean_decimal(&value_2);
  s21_arifmetic_error error = OK;
  int sign_res = 0, temp_scale = 0;
  clean_decimal(result);
  if (get_sign(value_1) == S21_NEG && get_sign(value_2) == S21_NEG) {
    s21_decimal tmp_value_1 = value_1;
    value_1 = value_2;
    value_2 = tmp_value_1;
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
  } else if (get_sign(value_1) != get_sign(value_2)) {
    sign_res = (get_sign(value_1) ? 1 : 0);
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    error = s21_add(value_1, value_2, result);
  } else {
    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    decimal_to_big_decimal(value_1, &v1);
    decimal_to_big_decimal(value_2, &v2);
    (get_scale(value_1) - get_scale(value_2)) > 0
        ? set_scale(&value_2, get_scale(value_1))
        : set_scale(&value_1, get_scale(value_2));
    temp_scale = get_scale(value_1);
    normalize_scales(&v1, &v2);
    if (is_big_decimal_greater(v2, v1)) {
      s21_big_decimal tmp_value_2 = v1;
      v1 = v2;
      v2 = tmp_value_2;
      set_sign(result, 1);
    }
    sub_big_decimal(v1, v2, &r);
    normalize_big_to_decimal(&r, &temp_scale, result);
    if (temp_scale <= 28) {
      big_decimal_to_decimal(r, result);
      set_scale(result, get_scale(value_1));
    } else {
      error = INF_OR_BIGGERINF;
    }
  }
  if (sign_res == 1) set_sign(result, 1);
  if (error == INF_OR_BIGGERINF && get_sign(*result)) error = UNINF_OR_LESSINF;
  return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (is_zero_decimal(&value_1)) clean_decimal(&value_1);
  if (is_zero_decimal(&value_2)) clean_decimal(&value_2);
  s21_arifmetic_error error = OK;
  int sign_res = 0, temp_scale = 0;
  clean_decimal(result);
  s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
  decimal_to_big_decimal(value_1, &v1);
  decimal_to_big_decimal(value_2, &v2);
  if (get_sign(value_1) != get_sign(value_2)) sign_res = S21_NEG;
  temp_scale = get_scale(value_1) + get_scale(value_2);
  mul_big_decimal(v1, v2, &r);
  if (is_zero_big_decimal(&r) && temp_scale <= 28) {
    big_decimal_to_decimal(r, result);
    set_scale(result, temp_scale);
  } else if (!is_zero_big_decimal(&r) || temp_scale > 28) {
    while (!is_zero_big_decimal(&r) && temp_scale != 0) {
      div_on_ten_big(&r);
      temp_scale--;
    }
  }
  if (is_zero_big_decimal(&r)) {
    big_decimal_to_decimal(r, result);
    set_scale(result, temp_scale);
  } else {
    error = INF_OR_BIGGERINF;
  }
  if (error == INF_OR_BIGGERINF && sign_res) error = UNINF_OR_LESSINF;
  return error;
}

void sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  int overflow_bit = 0, tmp_res = 0, i = 0;
  for (; i < BIG_MANTISS_BITS; i++) {
    tmp_res = get_bit_big_decimal(value_1, i) -
              get_bit_big_decimal(value_2, i) - overflow_bit;
    overflow_bit = tmp_res < 0;
    tmp_res = abs(tmp_res);
    set_bit_big_decimal(result, i, tmp_res % 2);
  }
}

void mul_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  int count = 0, i = 0;
  for (; i < BIG_MANTISS_BITS; i++) {
    if (get_bit_big_decimal(value_2, i)) {
      shift_mantissa_left_big(&value_1, i - count);
      add_big_decimal(value_1, *result, result);
      count = i;
    }
  }
}

void add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  int tmp_res = 0, overflow_bit = 0, i = 0;
  for (; i < BIG_MANTISS_BITS; i++) {
    tmp_res = get_bit_big_decimal(value_1, i) +
              get_bit_big_decimal(value_2, i) + overflow_bit;
    overflow_bit = tmp_res / 2;
    tmp_res %= 2;
    set_bit_big_decimal(result, i, tmp_res);
  }
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arifmetic_error error = OK;
  if (!is_zero_decimal(&value_2)) {
    int scale = 0, result_scale = 0, temp_scale = 0, i = 0;
    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    decimal_to_big_decimal(value_1, &v1);
    decimal_to_big_decimal(value_2, &v2);
    if (get_sign(value_1) != get_sign(value_2)) {
      set_sign(result, 1);
    }
    scale = div_big_decimal(v1, v2, &r);
    set_scale(&value_1, get_scale(value_1) + scale);
    temp_scale = get_scale(value_1) - get_scale(value_2);
    if (temp_scale > 0) {
      result_scale = 0;
    } else if (temp_scale < 0) {
      for (i = 0; i <= abs(temp_scale); i++) {
        increase_scale_big(&r);
      }
      result_scale = 0;
    }
    if (result_scale >= 0) {
      big_decimal_to_decimal(r, result);
      set_scale(result, result_scale);
    } else {
      error = INF_OR_BIGGERINF;
    }
  } else {
    error = s21_NAN;
  }
  if (error == INF_OR_BIGGERINF && get_sign(*result)) error = UNINF_OR_LESSINF;
  return error;
}

int div_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result) {
  int b_1 = 0, b_2 = 0, bit_2 = 0, scale = 0, diff = 0, tmp_scale = 0;
  s21_big_decimal tmp = {0};
  find_highest_bits(value_1, value_2, &b_1, &b_2);
  bit_2 = b_2;
  for (int i = 0; i < MANTISS_BITS && !is_zero_big_decimal(&value_1); i++) {
    if (i > 0) {
      shift_big_left(&value_2, 1);
      increase_scale_big(result);
      increase_scale_big(&value_1);
      tmp_scale++;
    }
    tmp_scale += scale;
    b_1 = b_2 = 0;
    find_highest_bits(value_1, value_2, &b_1, &b_2);
    diff = b_2 - bit_2;
    if (diff < 0) diff = 0;
    for (; diff >= 0 && !is_zero_big_decimal(&value_1);) {
      if (is_big_decimal_greater(value_2, value_1)) {
        set_bit_big_decimal(&tmp, 0, 0);
      } else {
        sub_big_decimal(value_1, value_2, &value_1);
        set_bit_big_decimal(&tmp, 0, 1);
      }
      diff--;
      if (diff >= 0) {
        shift_big_right(&value_2, 1);
        shift_big_left(&tmp, 1);
      }
    }
    if (diff >= 0) shift_big_left(&tmp, diff + 1);
    shift_big_right(&tmp, 1);
    add_big_decimal(*result, tmp, result);
    clean_big_decimal(&tmp);
  }
  return tmp_scale;
}