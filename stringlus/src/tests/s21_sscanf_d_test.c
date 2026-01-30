#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

// test 1
START_TEST(test_s21_sscanf_d_dec) {
  int x1 = 0, x2 = 0;
  int res1 = s21_sscanf("  -42", "%d", &x1);
  int res2 = sscanf("  -42", "%d", &x2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(x1, -42);
}
END_TEST

// test 2
START_TEST(test_s21_sscanf_d_i) {
  int x1 = 0, x2 = 0;
  int res1 = s21_sscanf("0xFF", "%i", &x1);
  int res2 = sscanf("0xFF", "%i", &x2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(x1, 255);
}
END_TEST

// test 3
START_TEST(test_s21_sscanf_d_oct) {
  int x1 = 0, x2 = 0;
  int res1 = s21_sscanf("077", "%i", &x1);
  int res2 = sscanf("077", "%i", &x2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(x1, 63);
}
END_TEST

// test 4
START_TEST(test_s21_sscanf_d_long) {
  long x1 = 0, x2 = 0;
  int res1 = s21_sscanf("123", "%ld", &x1);
  int res2 = sscanf("123", "%ld", &x2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(x1, 123L);
}
END_TEST

// test 5
START_TEST(test_s21_sscanf_d_invalid_oct) {
  int x1 = 0, x2 = 0;
  int res1 = s21_sscanf("09", "%i", &x1);
  int res2 = sscanf("09", "%i", &x2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(x1, x2);
}
END_TEST

// test 6
START_TEST(test_s21_sscanf_d_width) {
  int x1 = 0, x2 = 0;
  int res1 = s21_sscanf("-123", "%3d", &x1);
  int res2 = sscanf("-123", "%3d", &x2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(x1, x2);
}
END_TEST

// test 7
START_TEST(test_s21_sscanf_d_suppress) {
  int x1 = 123, x2 = 123;
  int res1 = s21_sscanf("456", "%*d", &x1);
  int res2 = sscanf("456", "%*d", &x2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(x1, x2);
}
END_TEST

Suite* s21_sscanf_d_suite(void) {
  Suite* s = suite_create("s21_sscanf_d");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_sscanf_d_dec);
  tcase_add_test(tc_core, test_s21_sscanf_d_i);
  tcase_add_test(tc_core, test_s21_sscanf_d_oct);
  tcase_add_test(tc_core, test_s21_sscanf_d_long);
  tcase_add_test(tc_core, test_s21_sscanf_d_invalid_oct);
  tcase_add_test(tc_core, test_s21_sscanf_d_width);
  tcase_add_test(tc_core, test_s21_sscanf_d_suppress);

  suite_add_tcase(s, tc_core);
  return s;
}
