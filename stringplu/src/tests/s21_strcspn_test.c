#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_no_matching_chars) {
  const char* str1 = "hello";
  const char* str2 = "xyz";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_first_char_match) {
  const char* str1 = "hello";
  const char* str2 = "aeiou";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_middle_match) {
  const char* str1 = "aaabbb";
  const char* str2 = "b";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_immediate_match) {
  const char* str1 = "test";
  const char* str2 = "t";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_empty_str1) {
  const char* str1 = "";
  const char* str2 = "abc";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_empty_str2) {
  const char* str1 = "abc";
  const char* str2 = "";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_null_str1) {
  const char* str1 = S21_NULL;
  const char* str2 = "abc";
  ck_assert_int_eq(s21_strcspn(str1, str2), 0);
}
END_TEST

START_TEST(test_null_str2) {
  const char* str1 = "abc";
  const char* str2 = S21_NULL;
  ck_assert_int_eq(s21_strcspn(str1, str2), s21_strlen(str1));
}
END_TEST

START_TEST(test_both_null) {
  const char* str1 = S21_NULL;
  const char* str2 = S21_NULL;
  ck_assert_int_eq(s21_strcspn(str1, str2), 0);
}
END_TEST

START_TEST(test_both_empty) {
  const char* str1 = "";
  const char* str2 = "";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_single_char_no_match) {
  const char* str1 = "a";
  const char* str2 = "b";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_single_char_match) {
  const char* str1 = "a";
  const char* str2 = "a";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_multiple_matches) {
  const char* str1 = "abcdef";
  const char* str2 = "xyzdef";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_numbers) {
  const char* str1 = "123456789";
  const char* str2 = "567";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_special_chars) {
  const char* str1 = "hello!@#$%";
  const char* str2 = "@#$";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_spaces) {
  const char* str1 = "hello world";
  const char* str2 = " ";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_long_string) {
  const char* str1 = "abcdefghijklmnopqrstuvwxyz";
  const char* str2 = "n";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

Suite* strcspn_suite(void) {
  Suite* s = suite_create("s21_strcspn");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_no_matching_chars);
  tcase_add_test(tc_core, test_first_char_match);
  tcase_add_test(tc_core, test_middle_match);
  tcase_add_test(tc_core, test_immediate_match);
  tcase_add_test(tc_core, test_empty_str1);
  tcase_add_test(tc_core, test_empty_str2);
  tcase_add_test(tc_core, test_null_str1);
  tcase_add_test(tc_core, test_null_str2);
  tcase_add_test(tc_core, test_both_null);
  tcase_add_test(tc_core, test_both_empty);
  tcase_add_test(tc_core, test_single_char_no_match);
  tcase_add_test(tc_core, test_single_char_match);
  tcase_add_test(tc_core, test_multiple_matches);
  tcase_add_test(tc_core, test_numbers);
  tcase_add_test(tc_core, test_special_chars);
  tcase_add_test(tc_core, test_spaces);
  tcase_add_test(tc_core, test_long_string);

  suite_add_tcase(s, tc_core);

  return s;
}