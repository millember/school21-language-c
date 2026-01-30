#include "s21_test.h"

START_TEST(s21_memset_test_1) {
  char actual[] = "Very well!";
  char expected[] = "Very well!";
  s21_memset(actual, 'R', sizeof(actual));
  memset(expected, 'R', sizeof(expected));
  ck_assert_mem_eq(actual, expected, sizeof(actual));
}
END_TEST

START_TEST(s21_memset_test_2) {
  char actual[] = "Very well!";
  char expected[] = "Very well!";
  const char c = 'R';
  s21_memset(actual + 5, c, 6);
  memset(expected + 5, c, 6);
  ck_assert_mem_eq(actual, expected, sizeof(actual));
}
END_TEST

START_TEST(s21_memset_test_3) {
  char actual[] = "Very well!";
  char expected[] = "Very well!";
  s21_memset(actual + 5, 'R', 6);
  memset(expected + 5, 'R', 6);
  ck_assert_mem_eq(actual, expected, sizeof(actual));
}
END_TEST

START_TEST(s21_memset_test_4) {
  int actual[10] = {'\0'};
  int expected[10] = {'\0'};
  const char c = 'r';
  s21_memset(actual, c, sizeof(actual));
  memset(expected, c, sizeof(expected));
  ck_assert_mem_eq(actual, expected, sizeof(actual));
}
END_TEST

START_TEST(s21_memset_test_5) {
  int actual[5] = {'\0'};
  int expected[5] = {'\0'};
  s21_memset(actual, 'r', sizeof(actual));
  memset(expected, 'r', sizeof(expected));
  ck_assert_mem_eq(actual, expected, sizeof(actual));
}
END_TEST

START_TEST(s21_memset_test_6) {
  char actual[10] = {'\0'};
  char expected[10] = {'\0'};
  const char c = '!';
  s21_memset(actual, c, sizeof(actual));
  memset(expected, c, sizeof(expected));
  ck_assert_mem_eq(actual, expected, sizeof(actual));
}
END_TEST

START_TEST(s21_memset_test_7) {
  unsigned char actual[10] = {'\0'};
  unsigned char expected[10] = {'\0'};
  const char c = ' ';
  s21_memset(actual, c, sizeof(actual));
  memset(expected, c, sizeof(expected));
  ck_assert_mem_eq(actual, expected, sizeof(actual));
}
END_TEST

START_TEST(s21_memset_test_8) {
  double actual[10];
  double expected[10];
  const char c = 97;
  s21_memset(actual, c, sizeof(actual));
  memset(expected, c, sizeof(expected));
  ck_assert_mem_eq(actual, expected, sizeof(actual));
}
END_TEST

START_TEST(s21_memset_test_8_1) {
  double actual[10];
  double expected[10];
  const char c = 0;
  s21_memset(actual, c, sizeof(actual));
  memset(expected, c, sizeof(expected));
  ck_assert_mem_eq(actual, expected, sizeof(actual));
}
END_TEST

START_TEST(s21_memset_test_9) {
  char actual[10] = "hippo";
  char expected[10] = "hippo";
  char c = 'p';
  s21_memset(&actual[5], c, sizeof(char));
  memset(&expected[5], c, sizeof(char));
  c = 'o';
  s21_memset(&actual[6], c, sizeof(char));
  memset(&expected[6], c, sizeof(char));
  c = '\0';
  s21_memset(&actual[7], c, sizeof(char));
  memset(&expected[7], c, sizeof(char));
  ck_assert_mem_eq(actual, expected, 8);
  ck_assert_str_eq(actual, expected);
  ck_assert_str_eq(actual, "hippopo");
}
END_TEST

Suite* s21_memset_suite(void) {
  Suite* suite = suite_create("s21_memset");
  TCase* tcase_core = tcase_create("case_memset");
  tcase_add_test(tcase_core, s21_memset_test_1);
  tcase_add_test(tcase_core, s21_memset_test_2);
  tcase_add_test(tcase_core, s21_memset_test_3);
  tcase_add_test(tcase_core, s21_memset_test_4);
  tcase_add_test(tcase_core, s21_memset_test_5);
  tcase_add_test(tcase_core, s21_memset_test_6);
  tcase_add_test(tcase_core, s21_memset_test_7);
  tcase_add_test(tcase_core, s21_memset_test_8);
  tcase_add_test(tcase_core, s21_memset_test_8_1);
  tcase_add_test(tcase_core, s21_memset_test_9);

  suite_add_tcase(suite, tcase_core);
  return suite;
}