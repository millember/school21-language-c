#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../../src/s21_string.h"

START_TEST(test_x_basic) {
  char s21_buf[100];
  char std_buf[100];
  int value = 255;

  int s21_res = s21_sprintf(s21_buf, "%x", value);
  int std_res = sprintf(std_buf, "%x", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_X_basic) {
  char s21_buf[100];
  char std_buf[100];
  int value = 255;

  int s21_res = s21_sprintf(s21_buf, "%X", value);
  int std_res = sprintf(std_buf, "%X", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_sharp_x) {
  char s21_buf[100];
  char std_buf[100];
  int value = 255;

  int s21_res = s21_sprintf(s21_buf, "%#x", value);
  int std_res = sprintf(std_buf, "%#x", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_sharp_X) {
  char s21_buf[100];
  char std_buf[100];
  int value = 255;

  int s21_res = s21_sprintf(s21_buf, "%#X", value);
  int std_res = sprintf(std_buf, "%#X", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_precision) {
  char s21_buf[100];
  char std_buf[100];
  int value = 15;

  int s21_res = s21_sprintf(s21_buf, "%.4x", value);
  int std_res = sprintf(std_buf, "%.4x", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_width) {
  char s21_buf[100];
  char std_buf[100];
  int value = 15;

  int s21_res = s21_sprintf(s21_buf, "%8x", value);
  int std_res = sprintf(std_buf, "%8x", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_zero_value) {
  char s21_buf[100];
  char std_buf[100];
  int value = 0;

  int s21_res = s21_sprintf(s21_buf, "%x", value);
  int std_res = sprintf(std_buf, "%x", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_sharp_with_zero) {
  char s21_buf[100];
  char std_buf[100];
  int value = 0;

  int s21_res = s21_sprintf(s21_buf, "%#x", value);
  int std_res = sprintf(std_buf, "%#x", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_minus_flag) {
  char s21_buf[100];
  char std_buf[100];
  int value = 255;

  int s21_res = s21_sprintf(s21_buf, "%-8x", value);
  int std_res = sprintf(std_buf, "%-8x", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_zero_flag) {
  char s21_buf[100];
  char std_buf[100];
  int value = 255;

  int s21_res = s21_sprintf(s21_buf, "%08x", value);
  int std_res = sprintf(std_buf, "%08x", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_width_precision) {
  char s21_buf[100];
  char std_buf[100];
  int value = 15;

  int s21_res = s21_sprintf(s21_buf, "%8.4x", value);
  int std_res = sprintf(std_buf, "%8.4x", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_combination) {
  char s21_buf[100];
  char std_buf[100];
  int value = 255;

  int s21_res = s21_sprintf(s21_buf, "%#08x", value);
  int std_res = sprintf(std_buf, "%#08x", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_negative_value) {
  char s21_buf[100];
  char std_buf[100];
  int value = -1;

  int s21_res = s21_sprintf(s21_buf, "%x", value);
  int std_res = sprintf(std_buf, "%x", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_large_value) {
  char s21_buf[100];
  char std_buf[100];
  unsigned int value = 0xFFFFFFFF;

  int s21_res = s21_sprintf(s21_buf, "%x", value);
  int std_res = sprintf(std_buf, "%x", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_multiple_values) {
  char s21_buf[100];
  char std_buf[100];
  int val1 = 255;
  int val2 = 4096;

  int s21_res = s21_sprintf(s21_buf, "%x %X", val1, val2);
  int std_res = sprintf(std_buf, "%x %X", val1, val2);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

Suite* s21_sprintf_x_suite(void) {
  Suite* s = suite_create("s21_sprintf_x");

  TCase* tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_x_basic);
  tcase_add_test(tc_core, test_X_basic);
  tcase_add_test(tc_core, test_sharp_x);
  tcase_add_test(tc_core, test_sharp_X);
  tcase_add_test(tc_core, test_precision);
  tcase_add_test(tc_core, test_width);
  tcase_add_test(tc_core, test_zero_value);
  tcase_add_test(tc_core, test_sharp_with_zero);

  TCase* tc_advanced = tcase_create("Advanced");
  tcase_add_test(tc_advanced, test_minus_flag);
  tcase_add_test(tc_advanced, test_zero_flag);
  tcase_add_test(tc_advanced, test_width_precision);
  tcase_add_test(tc_advanced, test_combination);
  tcase_add_test(tc_advanced, test_negative_value);
  tcase_add_test(tc_advanced, test_large_value);
  tcase_add_test(tc_advanced, test_multiple_values);

  suite_add_tcase(s, tc_core);
  suite_add_tcase(s, tc_advanced);

  return s;
}
