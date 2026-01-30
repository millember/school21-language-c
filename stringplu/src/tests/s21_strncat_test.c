#include <check.h>
#include <string.h>

#include "../s21_string.h"

extern char* s21_strncat(char* dest, const char* src, s21_size n);

START_TEST(test_strncat_n_zero) {
  char dest1[256] = "Hi";
  char dest2[256] = "Hi";
  const char* src = " there";
  s21_size n = 0;

  char* result_s21 = s21_strncat(dest1, src, n);
  char* result_std = strncat(dest2, src, n);

  ck_assert_str_eq(result_s21, result_std);
  ck_assert_ptr_eq(result_s21, dest1);
}
END_TEST

START_TEST(test_strncat_partial_copy) {
  char dest1[256] = "A";
  char dest2[256] = "A";
  const char* src = "BCDEFG";
  s21_size n = 3;

  char* result_s21 = s21_strncat(dest1, src, n);
  char* result_std = strncat(dest2, src, n);

  ck_assert_str_eq(result_s21, result_std);
  ck_assert_ptr_eq(result_s21, dest1);
}
END_TEST

START_TEST(test_strncat_empty_dest) {
  char dest1[256] = "";
  char dest2[256] = "";
  const char* src = "test";
  s21_size n = 10;

  char* result_s21 = s21_strncat(dest1, src, n);
  char* result_std = strncat(dest2, src, n);

  ck_assert_str_eq(result_s21, result_std);
  ck_assert_ptr_eq(result_s21, dest1);
}
END_TEST

START_TEST(test_strncat_n_less_than_src_len) {
  char dest1[256] = "123";
  char dest2[256] = "123";
  const char* src = "456";
  s21_size n = 2;

  char* result_s21 = s21_strncat(dest1, src, n);
  char* result_std = strncat(dest2, src, n);

  ck_assert_str_eq(result_s21, result_std);
  ck_assert_ptr_eq(result_s21, dest1);
}
END_TEST

Suite* strncat_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("s21_strncat");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strncat_n_zero);
  tcase_add_test(tc_core, test_strncat_partial_copy);
  tcase_add_test(tc_core, test_strncat_empty_dest);
  tcase_add_test(tc_core, test_strncat_n_less_than_src_len);

  suite_add_tcase(s, tc_core);

  return s;
}
