#include "s21_test.h"

START_TEST(s21_strncpy_test_1) {
  char dest_1[20] = {0};
  char dest_2[20] = {0};
  const char src[] = "Follow your heart";
  s21_strncpy(dest_1, src, sizeof(dest_1));
  strncpy(dest_2, src, sizeof(dest_2));
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(s21_strncpy_test_2) {
  char dest_1[50] = {0};
  char dest_2[50] = {0};
  const char src[] = "Follow your heart";
  s21_strncpy(dest_1, src, sizeof(dest_1));
  strncpy(dest_2, src, sizeof(dest_2));
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(s21_strncpy_test_3) {
  char dest_1[10] = {0};
  char dest_2[10] = {0};
  const char src[] = "Follow";
  s21_strncpy(dest_1, src, sizeof(dest_1));
  strncpy(dest_2, src, sizeof(dest_2));
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(s21_strncpy_test_4) {
  char dest_1[10] = {0};
  char dest_2[10] = {0};
  const char src[] = "";
  s21_strncpy(dest_1, src, sizeof(dest_1));
  strncpy(dest_2, src, sizeof(dest_2));
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(s21_strncpy_test_5) {
  char dest_1[10] = "foo";
  char dest_2[10] = "foo";
  const char src[] = "bar";
  s21_strncpy(dest_1, src, sizeof(dest_1));
  strncpy(dest_2, src, sizeof(dest_2));
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(s21_strncpy_test_6) {
  char dest_1[20] = "01234567890123456789";
  char dest_2[20] = "01234567890123456789";
  const char src[] = "school_s21";
  s21_strncpy(dest_1, src, sizeof(dest_1));
  strncpy(dest_2, src, sizeof(dest_2));
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(s21_strncpy_test_7) {
  char dest_1[20] = {0};
  char dest_2[20] = {0};
  const char src[] = "s21_";
  s21_strncpy(dest_1, src, sizeof(dest_1));
  strncpy(dest_2, src, sizeof(dest_2));
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(s21_strncpy_test_8) {
  char dest_1[5] = {0};
  char dest_2[5] = {0};
  const char src[] = "hello world";
  s21_strncpy(dest_1, src, 3);
  strncpy(dest_2, src, 3);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(s21_strncpy_test_9) {
  char dest_1[5] = "test";
  char dest_2[5] = "test";
  const char src[] = "ab";
  s21_strncpy(dest_1, src, 0);
  strncpy(dest_2, src, 0);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(s21_strncpy_test_null_dest) {
  const char src[] = "test";
  char* actual = s21_strncpy(NULL, src, 5);
  ck_assert_ptr_null(actual);
}
END_TEST

START_TEST(s21_strncpy_test_null_src) {
  char dest[10] = {0};
  char* actual = s21_strncpy(dest, NULL, 5);
  ck_assert_ptr_eq(actual, dest);
}
END_TEST

START_TEST(s21_strncpy_test_both_null) {
  char* actual = s21_strncpy(NULL, NULL, 5);
  ck_assert_ptr_null(actual);
}
END_TEST

Suite* s21_strncpy_suite(void) {
  Suite* suite = suite_create("s21_strncpy");
  TCase* tcase_core = tcase_create("case_strncpy");

  tcase_add_test(tcase_core, s21_strncpy_test_1);
  tcase_add_test(tcase_core, s21_strncpy_test_2);
  tcase_add_test(tcase_core, s21_strncpy_test_3);
  tcase_add_test(tcase_core, s21_strncpy_test_4);
  tcase_add_test(tcase_core, s21_strncpy_test_5);
  tcase_add_test(tcase_core, s21_strncpy_test_6);
  tcase_add_test(tcase_core, s21_strncpy_test_7);
  tcase_add_test(tcase_core, s21_strncpy_test_8);
  tcase_add_test(tcase_core, s21_strncpy_test_9);
  tcase_add_test(tcase_core, s21_strncpy_test_null_dest);
  tcase_add_test(tcase_core, s21_strncpy_test_null_src);
  tcase_add_test(tcase_core, s21_strncpy_test_both_null);

  suite_add_tcase(suite, tcase_core);
  return suite;
}