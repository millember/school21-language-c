#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

// Тест 1: sscanf("  42", " %d", &x)
START_TEST(test_whitespace_before_digit) {
  const char* input = "  42";
  const char* format = " %d";

  int x_std = 0, x_my = 0;
  int ret_std = sscanf(input, format, &x_std);
  int ret_my = s21_sscanf(input, format, &x_my);

  ck_assert_int_eq(ret_my, ret_std);
  ck_assert_int_eq(x_my, x_std);
}
END_TEST

// Тест 2: sscanf("42", "x%d", &x) → несовпадение литерала
START_TEST(test_literal_mismatch) {
  const char* input = "42";
  const char* format = "x%d";

  int x_std = -999, x_my = -999;
  int ret_std = sscanf(input, format, &x_std);
  int ret_my = s21_sscanf(input, format, &x_my);

  ck_assert_int_eq(ret_my, ret_std);
  ck_assert_int_eq(x_my, x_std);  // оба должны остаться -999
}
END_TEST

// Тест 3: sscanf("a10", "a%d", &x)
START_TEST(test_literal_match_then_digit) {
  const char* input = "a10";
  const char* format = "a%d";

  int x_std = 0, x_my = 0;
  int ret_std = sscanf(input, format, &x_std);
  int ret_my = s21_sscanf(input, format, &x_my);

  ck_assert_int_eq(ret_my, ret_std);
  ck_assert_int_eq(x_my, x_std);
}
END_TEST

// Тест 4: sscanf("123abc", "%d%n", &x, &n)
START_TEST(test_percent_n) {
  const char* input = "123abc";
  const char* format = "%d%n";

  int x_std = 0, n_std = 0;
  int x_my = 0, n_my = 0;

  int ret_std = sscanf(input, format, &x_std, &n_std);
  int ret_my = s21_sscanf(input, format, &x_my, &n_my);

  ck_assert_int_eq(ret_my, ret_std);  // %n не влияет на возврат
  ck_assert_int_eq(x_my, x_std);
  ck_assert_int_eq(n_my, n_std);
}
END_TEST

// Тест 5: sscanf("hello", "%5s%n", buf, &n)
START_TEST(test_width_and_percent_n) {
  const char* input = "hello";
  const char* format = "%5s%n";

  char buf_std[100] = {0}, buf_my[100] = {0};
  int n_std = 0, n_my = 0;

  int ret_std = sscanf(input, format, buf_std, &n_std);
  int ret_my = s21_sscanf(input, format, buf_my, &n_my);

  ck_assert_int_eq(ret_my, ret_std);
  ck_assert_str_eq(buf_my, buf_std);
  ck_assert_int_eq(n_my, n_std);
}
END_TEST

// Тест 6: sscanf("%", "%%")
START_TEST(test_percent_literal_match) {
  const char* input = "%";
  const char* format = "%%";

  // Нет аргументов — просто проверяем возврат
  int ret_std = sscanf(input, format);
  int ret_my = s21_sscanf(input, format);

  ck_assert_int_eq(ret_my, ret_std);  // оба = 0 (нет присвоений)
}
END_TEST

// Тест 7: sscanf("x", "%%")
START_TEST(test_percent_literal_mismatch) {
  const char* input = "x";
  const char* format = "%%";

  int ret_std = sscanf(input, format);
  int ret_my = s21_sscanf(input, format);

  ck_assert_int_eq(ret_my, ret_std);  // оба = 0 (ошибка, нет присвоений)
}
END_TEST

// Тест 8: sscanf("%%", "%%%%")
START_TEST(test_double_percent_literal) {
  const char* input = "%%";
  const char* format = "%%%%";

  int ret_std = sscanf(input, format);
  int ret_my = s21_sscanf(input, format);

  ck_assert_int_eq(ret_my, ret_std);  // оба = 0, но разбор успешен до конца
}
END_TEST

Suite* s21_sscanf_more_suite(void) {
  Suite* s = suite_create("s21_sscanf");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_whitespace_before_digit);
  tcase_add_test(tc_core, test_literal_mismatch);
  tcase_add_test(tc_core, test_literal_match_then_digit);
  tcase_add_test(tc_core, test_percent_n);
  tcase_add_test(tc_core, test_width_and_percent_n);
  tcase_add_test(tc_core, test_percent_literal_match);
  tcase_add_test(tc_core, test_percent_literal_mismatch);
  tcase_add_test(tc_core, test_double_percent_literal);

  suite_add_tcase(s, tc_core);
  return s;
}