#include <check.h>
#include <stdio.h>

#include "../s21_string.h"

START_TEST(test_percent_match_return_1) {
  const char* str = "%";
  const char* format = "%%";
  int s21_result = s21_sscanf(str, format);
  int std_result = sscanf(str, format);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_percent_no_match_return_0) {
  const char* str = "x";
  const char* format = "%%";
  int s21_result = s21_sscanf(str, format);
  int std_result = sscanf(str, format);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_double_percent_match) {
  const char* str = "%%";
  const char* format = "%%%%";
  int s21_result = s21_sscanf(str, format);
  int std_result = sscanf(str, format);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

Suite* s21_sscanf_percent_suite(void) {
  Suite* s = suite_create("s21_sscanf_percent");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_percent_match_return_1);
  tcase_add_test(tc_core, test_percent_no_match_return_0);
  tcase_add_test(tc_core, test_double_percent_match);
  suite_add_tcase(s, tc_core);

  return s;
}
