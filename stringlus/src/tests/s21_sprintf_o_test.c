#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_o_basic) {
  char s21_buf[100];
  char std_buf[100];
  int value = 255;

  int s21_res = s21_sprintf(s21_buf, "%o", value);
  int std_res = sprintf(std_buf, "%o", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_sharp_o) {
  char s21_buf[100];
  char std_buf[100];
  int value = 64;

  int s21_res = s21_sprintf(s21_buf, "%#o", value);
  int std_res = sprintf(std_buf, "%#o", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_o_zero) {
  char s21_buf[100];
  char std_buf[100];
  int value = 0;

  int s21_res = s21_sprintf(s21_buf, "%o", value);
  int std_res = sprintf(std_buf, "%o", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_sharp_o_zero) {
  char s21_buf[100];
  char std_buf[100];
  int value = 0;

  int s21_res = s21_sprintf(s21_buf, "%#o", value);
  int std_res = sprintf(std_buf, "%#o", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_o_precision) {
  char s21_buf[100];
  char std_buf[100];
  int value = 15;

  int s21_res = s21_sprintf(s21_buf, "%.4o", value);
  int std_res = sprintf(std_buf, "%.4o", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_o_width) {
  char s21_buf[100];
  char std_buf[100];
  int value = 15;

  int s21_res = s21_sprintf(s21_buf, "%8o", value);
  int std_res = sprintf(std_buf, "%8o", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_o_minus_flag) {
  char s21_buf[100];
  char std_buf[100];
  int value = 255;

  int s21_res = s21_sprintf(s21_buf, "%-8o", value);
  int std_res = sprintf(std_buf, "%-8o", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_o_zero_flag) {
  char s21_buf[100];
  char std_buf[100];
  int value = 255;

  int s21_res = s21_sprintf(s21_buf, "%08o", value);
  int std_res = sprintf(std_buf, "%08o", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_o_width_precision) {
  char s21_buf[100];
  char std_buf[100];
  int value = 15;

  int s21_res = s21_sprintf(s21_buf, "%8.4o", value);
  int std_res = sprintf(std_buf, "%8.4o", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_o_combination) {
  char s21_buf[100];
  char std_buf[100];
  int value = 64;

  int s21_res = s21_sprintf(s21_buf, "%#08o", value);
  int std_res = sprintf(std_buf, "%#08o", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_o_large_value) {
  char s21_buf[100];
  char std_buf[100];
  unsigned int value = 4294967295U;

  int s21_res = s21_sprintf(s21_buf, "%o", value);
  int std_res = sprintf(std_buf, "%o", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_o_negative_value) {
  char s21_buf[100];
  char std_buf[100];
  int value = -1;

  int s21_res = s21_sprintf(s21_buf, "%o", value);
  int std_res = sprintf(std_buf, "%o", value);

  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

Suite* s21_sprintf_o_suite(void) {
  Suite* s = suite_create("s21_sprintf_o");

  TCase* tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_o_basic);
  tcase_add_test(tc_core, test_sharp_o);
  TCase* tc_advanced = tcase_create("Advanced");
  tcase_add_test(tc_advanced, test_o_zero);
  tcase_add_test(tc_advanced, test_sharp_o_zero);
  tcase_add_test(tc_advanced, test_o_precision);
  tcase_add_test(tc_advanced, test_o_width);
  tcase_add_test(tc_advanced, test_o_minus_flag);
  tcase_add_test(tc_advanced, test_o_zero_flag);
  tcase_add_test(tc_advanced, test_o_width_precision);
  tcase_add_test(tc_advanced, test_o_combination);
  tcase_add_test(tc_advanced, test_o_large_value);
  tcase_add_test(tc_advanced, test_o_negative_value);

  suite_add_tcase(s, tc_core);
  suite_add_tcase(s, tc_advanced);

  return s;
}
