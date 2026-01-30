#include <check.h>
#include <string.h>

#include "../s21_string.h"

extern void* s21_to_lower(const char* str);

// test 1
START_TEST(test_s21_to_lower_null) {
  char* result = (char*)s21_to_lower(NULL);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

// test 2
START_TEST(test_s21_to_lower_empty) {
  char* input = "";
  char* result = (char*)s21_to_lower(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

// test 3
START_TEST(test_s21_to_lower_hello) {
  char* input = "HELLO";
  char* result = (char*)s21_to_lower(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

// test 4
START_TEST(test_s21_to_lower_special) {
  char* input = "123!@#";
  char* result = (char*)s21_to_lower(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "123!@#");
  free(result);
}
END_TEST

// test 5
START_TEST(test_s21_to_lower_mixed) {
  char* input = "AbC123";
  char* result = (char*)s21_to_lower(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "abc123");
  free(result);
}
END_TEST

Suite* s21_to_lower_suite(void) {
  Suite* s = suite_create("s21_to_lower");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_to_lower_null);
  tcase_add_test(tc_core, test_s21_to_lower_empty);
  tcase_add_test(tc_core, test_s21_to_lower_hello);
  tcase_add_test(tc_core, test_s21_to_lower_special);
  tcase_add_test(tc_core, test_s21_to_lower_mixed);

  suite_add_tcase(s, tc_core);
  return s;
}