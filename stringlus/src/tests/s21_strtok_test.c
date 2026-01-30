#include <check.h>
#include <string.h>

#include "../s21_string.h"
extern char* s21_strtok(char* str, const char* delim);

// test 1 поменяла
START_TEST(test_s21_strtok_comma) {
  char s21_input[] = "hello,world,test";
  char input[] = "hello,world,test";
  const char delim[] = ",";

  char* s21_token = s21_strtok(s21_input, delim);
  char* token = strtok(input, delim);

  while (s21_token && token) {
    ck_assert_str_eq(s21_token, token);
    s21_token = s21_strtok(S21_NULL, delim);
    token = strtok(NULL, delim);
  }

  ck_assert_ptr_eq(s21_token, NULL);
  ck_assert_ptr_eq(token, NULL);
}
END_TEST

// test 2 поменяла
START_TEST(test_s21_strtok_colons) {
  char s21_input[] = "a::b:::c";
  char input[] = "a::b:::c";
  const char delim[] = ":";

  char* s21_token = s21_strtok(s21_input, delim);
  char* token = strtok(input, delim);

  while (s21_token && token) {
    ck_assert_str_eq(s21_token, token);
    s21_token = s21_strtok(S21_NULL, delim);
    token = strtok(NULL, delim);
  }

  ck_assert_ptr_eq(s21_token, NULL);
  ck_assert_ptr_eq(token, NULL);
}
END_TEST

// test 3 поменяла
START_TEST(test_s21_strtok_spaces) {
  char s21_input[] = "   word   ";
  char input[] = "   word   ";
  const char delim[] = " ";

  char* s21_token = s21_strtok(s21_input, delim);
  char* token = strtok(input, delim);

  ck_assert_ptr_ne(s21_token, NULL);
  ck_assert_ptr_ne(token, NULL);
  ck_assert_str_eq(s21_token, token);

  s21_token = s21_strtok(S21_NULL, delim);
  token = strtok(NULL, delim);

  ck_assert_ptr_eq(s21_token, NULL);
  ck_assert_ptr_eq(token, NULL);
}
END_TEST

// test 4 поменяла
START_TEST(test_s21_strtok_empty_str) {
  char s21_input[] = "";
  char input[] = "";

  ck_assert_ptr_eq(s21_strtok(s21_input, ","), NULL);
  ck_assert_ptr_eq(strtok(input, ","), NULL);
}
END_TEST

// test 5 поменяла
START_TEST(test_s21_strtok_single) {
  char s21_input[] = "single";
  char input[] = "single";
  const char delim[] = ",";

  char* s21_token = s21_strtok(s21_input, delim);
  char* token = s21_strtok(input, delim);
  ck_assert_str_eq(s21_token, token);

  s21_token = s21_strtok(S21_NULL, delim);
  token = strtok(NULL, delim);

  ck_assert_ptr_eq(s21_token, NULL);
  ck_assert_ptr_eq(token, NULL);
}

Suite* s21_strtok_suite(void) {
  Suite* s = suite_create("s21_strtok");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_strtok_comma);
  tcase_add_test(tc_core, test_s21_strtok_colons);
  tcase_add_test(tc_core, test_s21_strtok_spaces);
  tcase_add_test(tc_core, test_s21_strtok_empty_str);
  tcase_add_test(tc_core, test_s21_strtok_single);

  suite_add_tcase(s, tc_core);
  return s;
}
