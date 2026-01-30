#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strrchr_basic) {
  char str[] = "hello";
  int c = 'l';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_first_char) {
  char str[] = "hello";
  int c = 'h';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_not_found) {
  char str[] = "hello";
  int c = 'x';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_multiple_occurrences) {
  char str[] = "aaa";
  int c = 'a';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_null_terminator) {
  char str[] = "hello";
  int c = '\0';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_empty_string) {
  char str[] = "";
  int c = '\0';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_null_string) {
  char* str = S21_NULL;
  int c = 'a';
  char* result = s21_strrchr(str, c);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_strrchr_single_char_found) {
  char str[] = "a";
  int c = 'a';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_single_char_not_found) {
  char str[] = "a";
  int c = 'b';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_long_string) {
  char str[] = "this is a longer string with multiple characters";
  int c = 'i';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_uppercase_lowercase) {
  char str[] = "Hello World";
  int c = 'o';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_numbers) {
  char str[] = "1234567890";
  int c = '5';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_special_chars) {
  char str[] = "hello!@#$%^&*()world";
  int c = '!';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

Suite* strrchr_suite(void) {
  Suite* s = suite_create("s21_strrchr");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strrchr_basic);
  tcase_add_test(tc_core, test_strrchr_first_char);
  tcase_add_test(tc_core, test_strrchr_not_found);
  tcase_add_test(tc_core, test_strrchr_multiple_occurrences);
  tcase_add_test(tc_core, test_strrchr_null_terminator);
  tcase_add_test(tc_core, test_strrchr_empty_string);
  tcase_add_test(tc_core, test_strrchr_null_string);
  tcase_add_test(tc_core, test_strrchr_single_char_found);
  tcase_add_test(tc_core, test_strrchr_single_char_not_found);
  tcase_add_test(tc_core, test_strrchr_long_string);
  tcase_add_test(tc_core, test_strrchr_uppercase_lowercase);
  tcase_add_test(tc_core, test_strrchr_numbers);
  tcase_add_test(tc_core, test_strrchr_special_chars);

  suite_add_tcase(s, tc_core);

  return s;
}
