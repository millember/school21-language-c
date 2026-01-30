#include <check.h>
#include <stdio.h>

#include "../s21_string.h"

START_TEST(test_1_hello_world) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  int s21_ret = s21_sscanf("  hello world", "%99s", s21_buf);
  int std_ret = sscanf("  hello world", "%99s", std_buf);

  ck_assert_str_eq(s21_buf, "hello");
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_ret, std_ret);
}
END_TEST

START_TEST(test_2_width_limit) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  int s21_ret = s21_sscanf("abc123", "%5s", s21_buf);
  int std_ret = sscanf("abc123", "%5s", std_buf);

  ck_assert_str_eq(s21_buf, "abc12");
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_ret, std_ret);
}
END_TEST

START_TEST(test_3_whitespace_before) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  int s21_ret = s21_sscanf("  \t\nX", "%99s", s21_buf);
  int std_ret = sscanf("  \t\nX", "%99s", std_buf);

  ck_assert_str_eq(s21_buf, "X");
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(s21_ret, std_ret);
}
END_TEST

START_TEST(test_4_suppress_no_second_word) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  int s21_ret = s21_sscanf("test", "%*s%99s", s21_buf);
  int std_ret = sscanf("test", "%*s%99s", std_buf);

  ck_assert_int_eq(s21_ret, 0);
  ck_assert_int_eq(std_ret, -1);

  ck_assert_int_eq(s21_buf[0], 0);
  ck_assert_int_eq(std_buf[0], 0);
}
END_TEST

Suite* s21_sscanf_basic_suite(void) {
  Suite* s = suite_create("s21_sscanf_basic");

  TCase* tc = tcase_create("Core");
  tcase_add_test(tc, test_1_hello_world);
  tcase_add_test(tc, test_2_width_limit);
  tcase_add_test(tc, test_3_whitespace_before);
  tcase_add_test(tc, test_4_suppress_no_second_word);

  suite_add_tcase(s, tc);
  return s;
}
