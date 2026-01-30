#include "s21_test.h"

START_TEST(s21_sprintf_percent_test_1) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%%"), sprintf(str2, "%%"));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_percent_test_2) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "school%%21"),
                   sprintf(str2, "school%%21"));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_percent_test_3) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%%school%%21"),
                   sprintf(str2, "%%school%%21"));
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* s21_sprintf_percent_suite(void) {
  Suite* suite = suite_create("s21_sprintf_u");
  TCase* tcase_core = tcase_create("case_sprintf_u");
  tcase_add_test(tcase_core, s21_sprintf_percent_test_1);
  tcase_add_test(tcase_core, s21_sprintf_percent_test_2);
  tcase_add_test(tcase_core, s21_sprintf_percent_test_3);

  suite_add_tcase(suite, tcase_core);
  return suite;
}