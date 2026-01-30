#include "s21_test.h"

START_TEST(s21_sprintf_u_test_1) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  unsigned int a = -12;
  unsigned int b = 4;

  ck_assert_int_eq(s21_sprintf(str1, "%u %u", a, b),
                   sprintf(str2, "%u %u", a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_u_test_2) {
  const int SIZE = 900;
  char str1[SIZE];
  char str2[SIZE];
  unsigned int a = 875;
  unsigned int b = 42;

  ck_assert_int_eq(s21_sprintf(str1, "[%-*u] [%-*u]", 5, a, 5, b),
                   sprintf(str2, "[%-*u] [%-*u]", 5, a, 5, b));
  ck_assert_str_eq(str1, str2);
}

END_TEST
START_TEST(s21_sprintf_u_test_3) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  unsigned long int a = 87598456842684154;
  unsigned long int b = 42154884226858222;

  ck_assert_int_eq(s21_sprintf(str1, "%lu %lu", a, b),
                   sprintf(str2, "%lu %lu", a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_u_test_4) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  unsigned int a = 3;
  unsigned int b = 4;

  ck_assert_int_eq(s21_sprintf(str1, "[%-10.*u] [%-10.5u]", 5, a, b),
                   sprintf(str2, "[%-10.*u] [%-10.5u]", 5, a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_u_test_5) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  unsigned int b = 4;

  ck_assert_int_eq(s21_sprintf(str1, "[%-10.*u]", 5, b),
                   sprintf(str2, "[%-10.*u]", 5, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_u_test_6) {
  const int SIZE = 1000;
  char str1[SIZE];
  char str2[SIZE];
  unsigned long int a = 87598456842684154;
  unsigned long int b = 42154884226858222;

  ck_assert_int_eq(s21_sprintf(str1, "[%-100lu] [%-100lu]", a, b),
                   sprintf(str2, "[%-100lu] [%-100lu]", a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_u_test_7) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  unsigned short int a = 2;
  unsigned short int b = -3;

  ck_assert_int_eq(s21_sprintf(str1, "[%7.6hu] [%7.6hu]", a, b),
                   sprintf(str2, "[%7.6hu] [%7.6hu]", a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_u_test_8) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  unsigned short int b = 3;

  ck_assert_int_eq(s21_sprintf(str1, "[%-7.6hu]", b),
                   sprintf(str2, "[%-7.6hu]", b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_u_test_9) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  unsigned short int b = 0;

  ck_assert_int_eq(s21_sprintf(str1, "[%-7.0hu]", b),
                   sprintf(str2, "[%-7.0hu]", b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* s21_sprintf_u_suite(void) {
  Suite* suite = suite_create("s21_sprintf_u");
  TCase* tcase_core = tcase_create("case_sprintf_u");
  tcase_add_test(tcase_core, s21_sprintf_u_test_1);
  tcase_add_test(tcase_core, s21_sprintf_u_test_2);
  tcase_add_test(tcase_core, s21_sprintf_u_test_3);
  tcase_add_test(tcase_core, s21_sprintf_u_test_4);
  tcase_add_test(tcase_core, s21_sprintf_u_test_5);
  tcase_add_test(tcase_core, s21_sprintf_u_test_6);
  tcase_add_test(tcase_core, s21_sprintf_u_test_7);
  tcase_add_test(tcase_core, s21_sprintf_u_test_8);
  tcase_add_test(tcase_core, s21_sprintf_u_test_9);

  suite_add_tcase(suite, tcase_core);
  return suite;
}