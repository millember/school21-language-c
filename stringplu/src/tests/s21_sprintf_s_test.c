#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(s21_sprintf_s_test_1) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  const char* a = "21kazan";
  int n1 = s21_sprintf(str1, "[%10s]", a);
  int n2 = sprintf(str2, "[%10s]", a);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(s21_sprintf_s_test_2) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  const char* a = "21kazan";

  ck_assert_int_eq(s21_sprintf(str1, "[%-10s]", a),
                   sprintf(str2, "[%-10s]", a));
  ck_assert_str_eq(str1, str2);
}

END_TEST

START_TEST(s21_sprintf_s_test_3) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  const char* a = "21kazan";

  ck_assert_int_eq(s21_sprintf(str1, "[%*s]", 10, a),
                   sprintf(str2, "[%*s]", 10, a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_s_test_4) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  const char* a = "21kazan";

  ck_assert_int_eq(s21_sprintf(str1, "[%-10.*s]", 4, a),
                   sprintf(str2, "[%-10.*s]", 4, a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_s_test_5) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  const char* a = "21kazan";

  ck_assert_int_eq(s21_sprintf(str1, "[%-*.*s]", 10, 4, a),
                   sprintf(str2, "[%-*.*s]", 10, 4, a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_s_test_6) {
  const int SIZE = 100;
  const char* str = "01234567890123456789";
  char expected[SIZE];
  char actual[SIZE];
  strcpy(expected, str);
  strcpy(actual, str);
  const char* a = "kazan";
  const char* pattern = "%10s";
  int n1 = sprintf(expected, pattern, a);
  int n2 = s21_sprintf(actual, pattern, a);
  ck_assert_str_eq(expected, actual);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(s21_sprintf_s_test_7) {
  const int SIZE = 100;
  char expected[SIZE];
  char actual[SIZE];
  const char* str = "123\0abc";
  const char* pattern = "%s";
  int n1 = sprintf(expected, pattern, str);
  int n2 = s21_sprintf(actual, pattern, str);
  ck_assert_str_eq(expected, actual);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(s21_sprintf_s_test_8) {
  const int SIZE = 100;
  char expected[SIZE];
  char actual[SIZE];
  const char* str = "\0";
  const char* pattern = "%s";
  int n1 = sprintf(expected, pattern, str);
  int n2 = s21_sprintf(actual, pattern, str);
  ck_assert_str_eq(expected, actual);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_sprintf_null) {
  char str1[100];
  char str2[100];

  int n1 = s21_sprintf(str1, "%s", S21_NULL);
  int n2 = sprintf(str2, "%s", NULL);

  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_sprintf_null_with_width) {
  char str1[100];
  char str2[100];

  int n1 = s21_sprintf(str1, "%10s", S21_NULL);
  int n2 = sprintf(str2, "%10s", NULL);

  ck_assert_str_eq(str1, str2);  // Ожидается "     (null)"
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_sprintf_zero_padding) {
  char str1[100];
  char str2[100];
  const char* text = "test";

  int n1 = s21_sprintf(str1, "%010s", text);
  int n2 = sprintf(str2, "%010s", text);

  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_sprintf_precision_greater_than_length) {
  char str1[100];
  char str2[100];
  const char* text = "hello";

  // Точность больше длины строки
  int n1 = s21_sprintf(str1, "%.10s", text);
  int n2 = sprintf(str2, "%.10s", text);

  ck_assert_str_eq(str1, str2);  // Ожидается "hello" (без изменений)
  ck_assert_int_eq(n1, n2);
}
END_TEST

Suite* s21_sprintf_s_suite(void) {
  Suite* suite = suite_create("s21_sprintf_s");
  TCase* tcase_core = tcase_create("case_sprintf_s");
  tcase_add_test(tcase_core, s21_sprintf_s_test_1);
  tcase_add_test(tcase_core, s21_sprintf_s_test_2);
  tcase_add_test(tcase_core, s21_sprintf_s_test_3);
  tcase_add_test(tcase_core, s21_sprintf_s_test_4);
  tcase_add_test(tcase_core, s21_sprintf_s_test_5);
  tcase_add_test(tcase_core, s21_sprintf_s_test_6);
  tcase_add_test(tcase_core, s21_sprintf_s_test_7);
  tcase_add_test(tcase_core, s21_sprintf_s_test_8);
  tcase_add_test(tcase_core, test_sprintf_null);
  tcase_add_test(tcase_core, test_sprintf_null_with_width);
  tcase_add_test(tcase_core, test_sprintf_zero_padding);
  tcase_add_test(tcase_core, test_sprintf_precision_greater_than_length);

  suite_add_tcase(suite, tcase_core);
  return suite;
}