#include <check.h>
#include <string.h>

#include "../s21_string.h"

extern void* s21_trim(const char* src, const char* trim_chars);

START_TEST(test_s21_insert_src_null) {
  ck_assert_pstr_eq(s21_trim(NULL, "test"), NULL);
}
END_TEST

START_TEST(test_s21_insert_empty_trim_chars) {
  char* input = "   hello   ";
  char* result = (char*)s21_trim(input, " ");
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "hello");
}
END_TEST

START_TEST(test_s21_insert_start_end_trim_1) {
  char* input = "abcHelloabc";
  char* result = (char*)s21_trim(input, "abc");
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello");
}
END_TEST

START_TEST(test_s21_insert_start_end_trim_2) {
  char* input = "123hello321";
  char* result = (char*)s21_trim(input, "123");
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "hello");
}
END_TEST

START_TEST(test_s21_insert_only_trim_chars) {
  char* input = "!!!";
  char* result = (char*)s21_trim(input, "!");
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(test_s21_insert_trim_chars_null) {
  char* input = "no trim";
  char* result = (char*)s21_trim(input, NULL);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "no trim");
}
END_TEST

START_TEST(test_s21_insert_no_chars_src) {
  char* input = "";
  char* result = (char*)s21_trim(input, "abc");
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(test_s21_insert_no_match) {
  char* input = "abc";
  char* result = (char*)s21_trim(input, "xyz");
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "abc");
}
END_TEST

Suite* s21_trim_suite(void) {
  Suite* s = suite_create("s21_trim");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_insert_src_null);
  tcase_add_test(tc_core, test_s21_insert_empty_trim_chars);
  tcase_add_test(tc_core, test_s21_insert_start_end_trim_1);
  tcase_add_test(tc_core, test_s21_insert_start_end_trim_2);
  tcase_add_test(tc_core, test_s21_insert_only_trim_chars);
  tcase_add_test(tc_core, test_s21_insert_trim_chars_null);
  tcase_add_test(tc_core, test_s21_insert_no_chars_src);
  tcase_add_test(tc_core, test_s21_insert_no_match);

  suite_add_tcase(s, tc_core);
  return s;
}
