#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_normal_found) {
  const char* haystack = "hello world";
  const char* needle = "world";
  char* result = s21_strstr(haystack, needle);
  char* expected = strstr(haystack, needle);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "world");
}
END_TEST

START_TEST(test_middle_found) {
  const char* haystack = "hello";
  const char* needle = "lo";
  char* result = s21_strstr(haystack, needle);
  char* expected = strstr(haystack, needle);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "lo");
}
END_TEST

START_TEST(test_not_found) {
  const char* haystack = "hello";
  const char* needle = "x";
  char* result = s21_strstr(haystack, needle);
  char* expected = strstr(haystack, needle);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_multiple_matches) {
  const char* haystack = "aaa";
  const char* needle = "aa";
  char* result = s21_strstr(haystack, needle);
  char* expected = strstr(haystack, needle);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "aaa");
}
END_TEST

START_TEST(test_empty_needle) {
  const char* haystack = "test";
  const char* needle = "";
  char* result = s21_strstr(haystack, needle);
  char* expected = strstr(haystack, needle);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_ptr_eq(result, haystack);
}
END_TEST

START_TEST(test_both_empty) {
  const char* haystack = "";
  const char* needle = "";
  char* result = s21_strstr(haystack, needle);
  char* expected = strstr(haystack, needle);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_ptr_eq(result, haystack);
}
END_TEST

START_TEST(test_empty_haystack) {
  const char* haystack = "";
  const char* needle = "a";
  char* result = s21_strstr(haystack, needle);
  char* expected = strstr(haystack, needle);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_null_haystack) {
  const char* needle = "test";
  char* result = s21_strstr(S21_NULL, needle);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_null_needle) {
  const char* haystack = "test";
  char* result = s21_strstr(haystack, S21_NULL);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_both_null) {
  char* result = s21_strstr(S21_NULL, S21_NULL);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_needle_longer_than_haystack) {
  const char* haystack = "abc";
  const char* needle = "abcd";
  char* result = s21_strstr(haystack, needle);
  char* expected = strstr(haystack, needle);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_exact_match) {
  const char* haystack = "exact";
  const char* needle = "exact";
  char* result = s21_strstr(haystack, needle);
  char* expected = strstr(haystack, needle);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "exact");
}
END_TEST

START_TEST(test_case_sensitive) {
  const char* haystack = "Hello World";
  const char* needle = "world";
  char* result = s21_strstr(haystack, needle);
  char* expected = strstr(haystack, needle);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_special_characters) {
  const char* haystack = "hello\tworld\n";
  const char* needle = "\tw";
  char* result = s21_strstr(haystack, needle);
  char* expected = strstr(haystack, needle);
  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "\tworld\n");
}
END_TEST

START_TEST(test_partial_match_followed_by_full) {
  const char* haystack = "aabaabaaab";
  const char* needle = "aabaa";
  char* result = s21_strstr(haystack, needle);
  char* expected = strstr(haystack, needle);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "aabaabaaab");
}
END_TEST

Suite* strstr_suite(void) {
  Suite* s = suite_create("s21_strstr");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_normal_found);
  tcase_add_test(tc_core, test_middle_found);
  tcase_add_test(tc_core, test_not_found);
  tcase_add_test(tc_core, test_multiple_matches);
  tcase_add_test(tc_core, test_empty_needle);
  tcase_add_test(tc_core, test_both_empty);
  tcase_add_test(tc_core, test_empty_haystack);
  tcase_add_test(tc_core, test_null_haystack);
  tcase_add_test(tc_core, test_null_needle);
  tcase_add_test(tc_core, test_both_null);
  tcase_add_test(tc_core, test_needle_longer_than_haystack);
  tcase_add_test(tc_core, test_exact_match);
  tcase_add_test(tc_core, test_case_sensitive);
  tcase_add_test(tc_core, test_special_characters);
  tcase_add_test(tc_core, test_partial_match_followed_by_full);

  suite_add_tcase(s, tc_core);

  return s;
}
