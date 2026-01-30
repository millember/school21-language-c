#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_basic_match) {
  const char* str1 = "hello";
  const char* str2 = "aeiou";
  char* result = s21_strpbrk(str1, str2);
  char* expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_eq(*result, 'e');
}
END_TEST

START_TEST(test_no_match) {
  const char* str1 = "hello";
  const char* str2 = "xyz";
  char* result = s21_strpbrk(str1, str2);
  char* expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_first_char_match) {
  const char* str1 = "hello";
  const char* str2 = "h";
  char* result = s21_strpbrk(str1, str2);
  char* expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_eq(*result, 'h');
}
END_TEST

START_TEST(test_multiple_chars_first_match) {
  const char* str1 = "hello";
  const char* str2 = "ol";
  char* result = s21_strpbrk(str1, str2);
  char* expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_eq(*result, 'l');
}
END_TEST

START_TEST(test_empty_str1) {
  const char* str1 = "";
  const char* str2 = "a";
  char* result = s21_strpbrk(str1, str2);
  char* expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_empty_str2) {
  const char* str1 = "test";
  const char* str2 = "";
  char* result = s21_strpbrk(str1, str2);
  char* expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_str1_null) {
  const char* str1 = S21_NULL;
  const char* str2 = "abc";
  char* result = s21_strpbrk(str1, str2);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_str2_null) {
  const char* str1 = "test";
  const char* str2 = S21_NULL;
  char* result = s21_strpbrk(str1, str2);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_both_null) {
  const char* str1 = S21_NULL;
  const char* str2 = S21_NULL;
  char* result = s21_strpbrk(str1, str2);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_single_char_strings) {
  const char* str1 = "a";
  const char* str2 = "a";
  char* result = s21_strpbrk(str1, str2);
  char* expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_eq(*result, 'a');
}
END_TEST

START_TEST(test_match_at_end) {
  const char* str1 = "hello";
  const char* str2 = "o";
  char* result = s21_strpbrk(str1, str2);
  char* expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_eq(*result, 'o');
}
END_TEST

START_TEST(test_numbers_match) {
  const char* str1 = "abc123def";
  const char* str2 = "345";
  char* result = s21_strpbrk(str1, str2);
  char* expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_eq(*result, '3');
}
END_TEST

START_TEST(test_special_chars) {
  const char* str1 = "hello world!";
  const char* str2 = " !@";
  char* result = s21_strpbrk(str1, str2);
  char* expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_eq(*result, ' ');
}
END_TEST

START_TEST(test_duplicate_chars_in_str2) {
  const char* str1 = "hello";
  const char* str2 = "lll";
  char* result = s21_strpbrk(str1, str2);
  char* expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_eq(*result, 'l');
}
END_TEST

START_TEST(test_case_sensitive) {
  const char* str1 = "Hello";
  const char* str2 = "AEIOU";
  char* result = s21_strpbrk(str1, str2);
  char* expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_null(result);
}
END_TEST

Suite* strpbrk_suite(void) {
  Suite* s = suite_create("s21_strpbrk");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_basic_match);
  tcase_add_test(tc_core, test_no_match);
  tcase_add_test(tc_core, test_first_char_match);
  tcase_add_test(tc_core, test_multiple_chars_first_match);
  tcase_add_test(tc_core, test_empty_str1);
  tcase_add_test(tc_core, test_empty_str2);
  tcase_add_test(tc_core, test_str1_null);
  tcase_add_test(tc_core, test_str2_null);
  tcase_add_test(tc_core, test_both_null);
  tcase_add_test(tc_core, test_single_char_strings);
  tcase_add_test(tc_core, test_match_at_end);
  tcase_add_test(tc_core, test_numbers_match);
  tcase_add_test(tc_core, test_special_chars);
  tcase_add_test(tc_core, test_duplicate_chars_in_str2);
  tcase_add_test(tc_core, test_case_sensitive);

  suite_add_tcase(s, tc_core);
  return s;
}
