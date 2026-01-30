#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

extern int s21_strncmp(const char* str1, const char* str2, s21_size n);

START_TEST(test_strncmp_equal_strings) {
  const char* s1 = "abc";
  const char* s2 = "abc";
  s21_size n = 5;
  int res_s21 = s21_strncmp(s1, s2, n);
  int res_std = strncmp(s1, s2, n);
  ck_assert_int_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strncmp_partial_equal) {
  const char* s1 = "abc";
  const char* s2 = "abd";
  s21_size n = 2;
  int res_s21 = s21_strncmp(s1, s2, n);
  int res_std = strncmp(s1, s2, n);
  ck_assert_int_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strncmp_less) {
  const char* s1 = "abc";
  const char* s2 = "abd";
  s21_size n = 3;
  int res_s21 = s21_strncmp(s1, s2, n);
  int res_std = strncmp(s1, s2, n);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_int_lt(res_s21, 0);
}
END_TEST

START_TEST(test_strncmp_greater) {
  const char* s1 = "abd";
  const char* s2 = "abc";
  s21_size n = 3;
  int res_s21 = s21_strncmp(s1, s2, n);
  int res_std = strncmp(s1, s2, n);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_int_gt(res_s21, 0);
}
END_TEST

START_TEST(test_strncmp_empty_strings) {
  const char* s1 = "";
  const char* s2 = "";
  s21_size n = 10;
  int res_s21 = s21_strncmp(s1, s2, n);
  int res_std = strncmp(s1, s2, n);
  ck_assert_int_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strncmp_first_nonempty) {
  const char* s1 = "a";
  const char* s2 = "";
  s21_size n = 1;
  int res_s21 = s21_strncmp(s1, s2, n);
  int res_std = strncmp(s1, s2, n);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_int_gt(res_s21, 0);
}
END_TEST

START_TEST(test_strncmp_second_nonempty) {
  const char* s1 = "";
  const char* s2 = "a";
  s21_size n = 1;
  int res_s21 = s21_strncmp(s1, s2, n);
  int res_std = strncmp(s1, s2, n);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_int_lt(res_s21, 0);
}
END_TEST

START_TEST(test_strncmp_help_equal_prefix) {
  const char* s1 = "hello";
  const char* s2 = "help";
  s21_size n = 4;
  int res_s21 = s21_strncmp(s1, s2, n);
  int res_std = strncmp(s1, s2, n);
  ck_assert_int_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strncmp_help_less) {
  const char* s1 = "hello";
  const char* s2 = "help";
  s21_size n = 5;
  int res_s21 = s21_strncmp(s1, s2, n);
  int res_std = strncmp(s1, s2, n);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_int_lt(res_s21, 0);
}
END_TEST

Suite* s21_strncmp_suite(void) {
  Suite* s = suite_create("s21_strncmp");
  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, test_strncmp_equal_strings);
  tcase_add_test(tc, test_strncmp_partial_equal);
  tcase_add_test(tc, test_strncmp_less);
  tcase_add_test(tc, test_strncmp_greater);
  tcase_add_test(tc, test_strncmp_empty_strings);
  tcase_add_test(tc, test_strncmp_first_nonempty);
  tcase_add_test(tc, test_strncmp_second_nonempty);
  tcase_add_test(tc, test_strncmp_help_equal_prefix);
  tcase_add_test(tc, test_strncmp_help_less);

  suite_add_tcase(s, tc);
  return s;
}
