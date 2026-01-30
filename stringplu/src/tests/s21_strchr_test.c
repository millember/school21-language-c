#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strchr_find_middle_char) {
  const char* str = "hello";
  int c = 'e';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  if (result != S21_NULL) {
    ck_assert_int_eq(*result, 'e');
  }
}
END_TEST

START_TEST(test_strchr_char_not_found) {
  const char* str = "hello";
  int c = 'x';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_strchr_null_terminator) {
  const char* str = "hello";
  int c = '\0';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  if (result != S21_NULL) {
    ck_assert_int_eq(*result, '\0');
    ck_assert_str_eq(str, "hello");
  }
}
END_TEST

START_TEST(test_strchr_empty_string_null_term) {
  const char* str = "";
  int c = '\0';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  if (result != S21_NULL) {
    ck_assert_int_eq(*result, '\0');
  }
}
END_TEST

START_TEST(test_strchr_first_occurrence) {
  const char* str = "aaa";
  int c = 'a';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  if (result != S21_NULL) {
    ck_assert_ptr_eq(result, str);
    ck_assert_int_eq(*result, 'a');
    ck_assert_str_eq(result, "aaa");
  }
}
END_TEST

START_TEST(test_strchr_null_string) {
  const char* str = S21_NULL;
  int c = 'a';

  char* result = s21_strchr(str, c);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_strchr_space_character) {
  const char* str = "hello world";
  int c = ' ';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  if (result != S21_NULL) {
    ck_assert_int_eq(*result, ' ');
    ck_assert_str_eq(result, " world");
  }
}
END_TEST

START_TEST(test_strchr_digit_character) {
  const char* str = "test123test";
  int c = '2';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  if (result != S21_NULL) {
    ck_assert_int_eq(*result, '2');
    ck_assert_str_eq(result, "23test");
  }
}
END_TEST

START_TEST(test_strchr_special_character) {
  const char* str = "hello@world.com";
  int c = '@';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  if (result != S21_NULL) {
    ck_assert_int_eq(*result, '@');
    ck_assert_str_eq(result, "@world.com");
  }
}
END_TEST

START_TEST(test_strchr_extended_ascii) {
  const char* str = "café";
  int c = 0xE9;

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strchr_long_string) {
  const char* str =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  int c = 'Z';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  if (result != S21_NULL) {
    ck_assert_int_eq(*result, 'Z');
  }
}
END_TEST

START_TEST(test_strchr_repeated_chars) {
  const char* str = "abcabcabc";
  int c = 'b';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  if (result != S21_NULL) {
    ck_assert_int_eq(*result, 'b');
    ck_assert_str_eq(result, "bcabcabc");
  }
}
END_TEST

START_TEST(test_strchr_single_char_string) {
  const char* str = "X";
  int c = 'X';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  if (result != S21_NULL) {
    ck_assert_int_eq(*result, 'X');
  }
}
END_TEST

START_TEST(test_strchr_last_char_only) {
  const char* str = "abcdefghij";
  int c = 'j';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_nonnull(result);
  if (result != S21_NULL) {
    ck_assert_int_eq(*result, 'j');
    ck_assert_str_eq(result, "j");
  }
}
END_TEST

START_TEST(test_strchr_empty_string_non_null) {
  const char* str = "";
  int c = 'a';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str, c);

  ck_assert_ptr_eq(result, expected);
  ck_assert_ptr_null(result);
}
END_TEST

Suite* strchr_suite(void) {
  Suite* s = suite_create("s21_strchr");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strchr_find_middle_char);
  tcase_add_test(tc_core, test_strchr_char_not_found);
  tcase_add_test(tc_core, test_strchr_null_terminator);
  tcase_add_test(tc_core, test_strchr_empty_string_null_term);
  tcase_add_test(tc_core, test_strchr_first_occurrence);
  tcase_add_test(tc_core, test_strchr_null_string);

  tcase_add_test(tc_core, test_strchr_space_character);
  tcase_add_test(tc_core, test_strchr_digit_character);
  tcase_add_test(tc_core, test_strchr_special_character);
  tcase_add_test(tc_core, test_strchr_extended_ascii);
  tcase_add_test(tc_core, test_strchr_long_string);
  tcase_add_test(tc_core, test_strchr_repeated_chars);
  tcase_add_test(tc_core, test_strchr_single_char_string);
  tcase_add_test(tc_core, test_strchr_last_char_only);
  tcase_add_test(tc_core, test_strchr_empty_string_non_null);

  suite_add_tcase(s, tc_core);

  return s;
}
