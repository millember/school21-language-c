#include <check.h>
#include <string.h>

#include "../s21_string.h"
extern void* s21_insert(const char* src, const char* str, s21_size start_index);

START_TEST(test_s21_insert_src_null) {
  ck_assert_ptr_eq(s21_insert(NULL, "test", 0), NULL);
}
END_TEST

START_TEST(test_s21_insert_str_null) {
  ck_assert_ptr_eq(s21_insert("test", NULL, 0), NULL);
}
END_TEST

START_TEST(test_s21_insert_src_empty) {
  void* res = s21_insert("", "Hi", 0);
  ck_assert_ptr_ne(res, NULL);
  ck_assert_str_eq((char*)res, "Hi");
  free(res);
}
END_TEST

START_TEST(test_s21_insert_at_end) {
  void* res = s21_insert("Hello", " World", 5);
  ck_assert_ptr_ne(res, NULL);
  ck_assert_str_eq((char*)res, "Hello World");
  free(res);
}
END_TEST

START_TEST(test_s21_insert_at_middle) {
  void* res = s21_insert("abc", "XYZ", 1);
  ck_assert_ptr_ne(res, NULL);
  ck_assert_str_eq((char*)res, "aXYZbc");
  free(res);
}
END_TEST

START_TEST(test_s21_insert_str_empty) {
  void* res = s21_insert("test", "", 2);
  ck_assert_ptr_ne(res, NULL);
  ck_assert_str_eq((char*)res, "test");
  free(res);
}
END_TEST

START_TEST(test_s21_insert_index) {
  ck_assert_ptr_eq(s21_insert("abc", "xyz", 10), NULL);
}
END_TEST

Suite* s21_insert_suite(void) {
  Suite* s = suite_create("s21_insert");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_insert_src_null);
  tcase_add_test(tc_core, test_s21_insert_str_null);
  tcase_add_test(tc_core, test_s21_insert_src_empty);
  tcase_add_test(tc_core, test_s21_insert_at_end);
  tcase_add_test(tc_core, test_s21_insert_at_middle);
  tcase_add_test(tc_core, test_s21_insert_str_empty);
  tcase_add_test(tc_core, test_s21_insert_index);

  suite_add_tcase(s, tc_core);
  return s;
}
