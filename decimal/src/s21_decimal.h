#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BIG_BITS 224
#define BIG_MANTISS_BITS 192
#define BITS_SIGN 127
#define MANTISS_BITS 96
#define MAX_32bit 4294967296
#define BLOCK_BITS 32
#define MAX_FLOAT_TO_CONVERT 79228157791897854723898736640.0f
#define MAX_DEC powf(2.0f, 96.0f) - 1.0
#define MIN_DEC -powf(2.0f, 96.0f) + 1.0

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct s21_big_decimal {
  unsigned int bits[7];
} s21_big_decimal;

typedef union s21_decimal_bit3 {
  int bit;
  struct {
    unsigned int zero_bit2 : 16;
    unsigned int power_bit : 8;
    unsigned int zero_bit1 : 7;
    unsigned int sign_bit : 1;
  } parts;
} s21_decimal_bit3;

typedef enum s21_decimal_sign {
  S21_POS,
  S21_NEG,
} s21_decimal_sign;

typedef union float_cast {
  float fl;
  struct {
    unsigned int mantisa : 23;
    unsigned int exponent : 8;
    unsigned int sign : 1;
  } parts;
  unsigned int bytes;
} float_cast;

typedef enum s21_arifmetic_error {
  OK,
  INF_OR_BIGGERINF,
  UNINF_OR_LESSINF,
  s21_NAN,
} s21_arifmetic_error;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal decimal_1, s21_decimal decimal_2);
int s21_is_less_or_equal(s21_decimal decimal_1, s21_decimal decimal_2);
int s21_is_greater(s21_decimal decimal_1, s21_decimal decimal_2);
int s21_is_greater_or_equal(s21_decimal decimal_1, s21_decimal decimal_2);
int s21_is_equal(s21_decimal decimal_1, s21_decimal decimal_2);
int s21_is_not_equal(s21_decimal decimal_1, s21_decimal decimal_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int can_big_decimal_fit_in_decimal(s21_big_decimal big);

// вспомогательные функции децимала
void clean_decimal(s21_decimal *decimal);
int is_zero_decimal(s21_decimal *decimal);
int get_bit_decimal(s21_decimal decimal, int idx);
void set_bit_decimal(s21_decimal *decimal, int idx, int bit_value);
int get_sign(s21_decimal decimal);
void set_sign(s21_decimal *decimal, int sign);
int get_scale(s21_decimal decimal);
void set_scale(s21_decimal *decimal, int scale);
int is_decimal_correct(s21_decimal decimal);
void plus_one(s21_decimal *decimal);
int bit_not_zero(s21_decimal decimal);
int div_on_ten(s21_decimal *decimal, int scale);
int compare_absolute_values(s21_decimal decim_1, s21_decimal decim_2);
int apply_rounding_operation(s21_decimal value, s21_decimal *result);

// вспомогательные функции большого децимала
void clean_big_decimal(s21_big_decimal *big_decimal);
int is_zero_big_decimal(s21_big_decimal *big_decimal);
int get_bit_big_decimal(s21_big_decimal big_decimal, int idx);
void set_bit_big_decimal(s21_big_decimal *big_decimal, int idx, int bit_value);
int shift_big_left(s21_big_decimal *big_decimal, int step);
void shift_big_right(s21_big_decimal *big_decimal, int step);
void normalize_big_to_decimal(s21_big_decimal *big_decimal, int *temp_scale,
                              s21_decimal *result);
void normalize_scales(s21_big_decimal *big_decimal_1,
                      s21_big_decimal *big_decimal_2);
void find_highest_bits(s21_big_decimal big_decimal_1,
                       s21_big_decimal big_decimal_2, int *bit_1, int *bit_2);
int get_scale_big(s21_big_decimal big_decimal);
void shift_mantissa_left_big(s21_big_decimal *big_decimal, unsigned int steps);
void increase_scale_big(s21_big_decimal *big_decimal);
void div_on_ten_big(s21_big_decimal *big_decimal);
int is_big_decimal_greater(s21_big_decimal big_decimal_1,
                           s21_big_decimal big_decimal_2);
void bank_round_decimal(s21_decimal *value, int remainder);
int div_on_ten_big_with_remainder(s21_big_decimal *big_decimal);
int get_sign_from_big(s21_big_decimal big);
int compare_big_decimals(s21_big_decimal b1, s21_big_decimal b2);
void prepare_big_decimals(s21_decimal d1, s21_decimal d2, s21_big_decimal *b1,
                          s21_big_decimal *b2, int *scale1, int *scale2,
                          int *max_scale);
void align_scales(s21_big_decimal *v1, s21_big_decimal *v2, int scale1,
                  int scale2, int max_scale);
int process_big_decimal_result(s21_big_decimal r, int max_scale, int final_sign,
                               s21_decimal *result);
int can_big_decimal_fit_in_decimal(s21_big_decimal big);
// преобразования
void decimal_to_big_decimal(s21_decimal decimal, s21_big_decimal *big_decimal);
void big_decimal_to_decimal(s21_big_decimal big_decimal, s21_decimal *decimal);

void add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
void sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
void mul_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
int div_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result);

#endif
