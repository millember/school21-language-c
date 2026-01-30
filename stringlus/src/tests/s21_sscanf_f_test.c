#include <check.h>
#include <math.h>
#include <stdio.h>

#include "../s21_string.h"

// Вспомогательные функции сравнения
static int fequal(float a, float b) { return fabsf(a - b) < 1e-5f; }
static int dequal(double a, double b) { return fabs(a - b) < 1e-10; }
static int ldequal(long double a, long double b) {
  return fabsl(a - b) < 1e-15L;
}

START_TEST(test_s21_sscanf_percent_f_width_then_next_float) {
  const char* input = "123.4567";
  float f1_std = 0.0f, f2_std = 0.0f;
  float f1_my = 0.0f, f2_my = 0.0f;

  // Стандартный sscanf
  int r_std = sscanf(input, "%4f %f", &f1_std, &f2_std);
  // Ваша реализация
  int r_my = s21_sscanf(input, "%4f %f", &f1_my, &f2_my);

  // printf("%f, %f ", f1_my, f2_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_int_eq(fequal(f1_std, f1_my), 1);
  ck_assert_int_eq(fequal(f2_std, f2_my), 1);
}
END_TEST

START_TEST(test_s21_sscanf_percent_f_basic) {
  const char* input = "-13.1415";
  float f_std = 0.0f, f_my = 0.0f;
  int r_std = sscanf(input, "%4f", &f_std);
  int r_my = s21_sscanf(input, "%4f", &f_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_int_eq(fequal(f_std, f_my), 1);
}
END_TEST

START_TEST(test_s21_sscanf_percent_f_negative_exponent) {
  const char* input = "-1.23e4";
  float f_std = 0.0f, f_my = 0.0f;
  int r_std = sscanf(input, "%f", &f_std);
  int r_my = s21_sscanf(input, "%f", &f_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_int_eq(fequal(f_std, f_my), 1);
}
END_TEST

START_TEST(test_s21_sscanf_percent_lf_with_spaces) {
  const char* input = "  +42.5";
  double d_std = 0.0, d_my = 0.0;
  int r_std = sscanf(input, "%lf", &d_std);
  int r_my = s21_sscanf(input, "%lf", &d_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_int_eq(dequal(d_std, d_my), 1);
}
END_TEST

START_TEST(test_s21_sscanf_percent_Lf_long_double) {
  const char* input = "1.23456789e-5";
  long double ld_std = 0.0L, ld_my = 0.0L;
  int r_std = sscanf(input, "%Lf", &ld_std);
  int r_my = s21_sscanf(input, "%Lf", &ld_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_int_eq(ldequal(ld_std, ld_my), 1);
}
END_TEST

START_TEST(test_s21_sscanf_percent_f_with_prefix_char) {
  const char* input = "Value: -3.14e+2";
  double d_std = 0.0, d_my = 0.0;
  int r_std = sscanf(input, "Value: %lf", &d_std);
  int r_my = s21_sscanf(input, "Value: %lf", &d_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_int_eq(dequal(d_std, d_my), 1);
}
END_TEST

Suite* s21_sscanf_f_integration_suite(void) {
  Suite* s = suite_create("s21_sscanf_f_integration");
  TCase* tc = tcase_create("floating_point");
  tcase_add_test(tc, test_s21_sscanf_percent_f_width_then_next_float);

  tcase_add_test(tc, test_s21_sscanf_percent_f_basic);
  tcase_add_test(tc, test_s21_sscanf_percent_f_negative_exponent);
  tcase_add_test(tc, test_s21_sscanf_percent_lf_with_spaces);
  tcase_add_test(tc, test_s21_sscanf_percent_Lf_long_double);
  tcase_add_test(tc, test_s21_sscanf_percent_f_with_prefix_char);

  suite_add_tcase(s, tc);
  return s;
}
