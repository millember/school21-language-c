#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"
extern int s21_sscanf_c(const char** str, char* out, int width, int suppress);
// test1
START_TEST(s21_sscanf_c_test_first) {
  char ch1 = 0, ch2 = 0;

  int res1 = s21_sscanf("abc", "%c", &ch1);
  int res2 = sscanf("abc", "%c", &ch2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq((int)ch1, (int)ch2);
}
END_TEST

// test2

START_TEST(s21_sscanf_c_test_space) {
  char ch1 = 0, ch2 = 0;

  int res1 = s21_sscanf(" abc", "%c", &ch1);
  int res2 = sscanf(" abc", "%c", &ch2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq((int)ch1, (int)ch2);
  ck_assert_int_eq((int)ch1, (int)' ');
}
END_TEST

// test3
START_TEST(s21_sscanf_c_test_width) {
  char buf1[10] = {0}, buf2[10] = {0};

  int res1 = s21_sscanf("xyz", "%2c", buf1);
  int res2 = sscanf("xyz", "%2c", buf2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res1, 1);
  ck_assert_mem_eq(buf1, buf2, 2);

  ck_assert_int_eq(buf1[0], buf2[0]);
  ck_assert_int_eq(buf1[1], buf2[1]);
}
END_TEST

// test4
START_TEST(s21_sscanf_c_test_suppress) {
  char ch1 = 'X', ch2 = 'X';

  int res1 = s21_sscanf("AV", "%*c%c", &ch1);
  int res2 = sscanf("AV", "%*c%c", &ch2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq((int)ch1, (int)ch2);
}
END_TEST

Suite* s21_sscanf_c_suite(void) {
  Suite* s = suite_create("s21_sscanf_c");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, s21_sscanf_c_test_first);
  tcase_add_test(tc_core, s21_sscanf_c_test_space);
  tcase_add_test(tc_core, s21_sscanf_c_test_width);
  tcase_add_test(tc_core, s21_sscanf_c_test_suppress);

  suite_add_tcase(s, tc_core);
  return s;
}
