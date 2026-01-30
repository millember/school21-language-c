#include <check.h>
#include <stdio.h>

#include "../s21_string.h"

START_TEST(test_c_basic) {
  char buf1[32];
  char buf2[32];

  int r1 = s21_sprintf(buf1, "%c", 'A');
  int r2 = sprintf(buf2, "%c", 'A');

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_c_width) {
  char buf1[32];
  char buf2[32];

  int r1 = s21_sprintf(buf1, "%5c", 'X');
  int r2 = sprintf(buf2, "%5c", 'X');

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_c_minus) {
  char buf1[32];
  char buf2[32];

  int r1 = s21_sprintf(buf1, "%-5c", 'X');
  int r2 = sprintf(buf2, "%-5c", 'X');

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_c_zero) {
  char buf1[32];
  char buf2[32];

  // clang считает %05c UB, поэтому надо отключить -Wformat в Makefile
  int r1 = s21_sprintf(buf1, "%05c", 'X');
  int r2 = sprintf(buf2, "%05c", 'X');

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

Suite* sprintf_c_suite(void) {
  Suite* s = suite_create("s21_sprintf %c");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_c_basic);
  tcase_add_test(tc, test_c_width);
  tcase_add_test(tc, test_c_minus);
  tcase_add_test(tc, test_c_zero);

  suite_add_tcase(s, tc);
  return s;
}
