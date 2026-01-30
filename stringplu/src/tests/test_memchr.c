#include "s21_test.h"

START_TEST(s21_memchr_test_1) {
  const char str[] = "now or never";
  const char c = ' ';

  ck_assert_ptr_eq(s21_memchr(str, c, 10), (memchr(str, c, 10)));
}
END_TEST

START_TEST(s21_memchr_test_2) {
  const char str[] = "now or never";
  const char c = 'N';

  ck_assert_ptr_eq(s21_memchr(str, c, 10), memchr(str, c, 10));
}
END_TEST

START_TEST(s21_memchr_test_3) {
  const char str[] = "";
  s21_size c = ' ';

  ck_assert_ptr_eq(s21_memchr(str, c, 1), memchr(str, c, 1));
}
END_TEST

START_TEST(s21_memchr_test_4) {
  const char str[] = "";
  const char c = ' ';

  ck_assert_ptr_eq(s21_memchr(str, c, strlen(str)),
                   memchr(str, c, strlen(str)));
}
END_TEST

START_TEST(s21_memchr_test_5) {
  const char str[] = "now or never";
  const char c = 'o';

  ck_assert_ptr_eq(s21_memchr(str, c, 10), memchr(str, c, 10));
}
END_TEST

START_TEST(s21_memchr_test_6) {
  const char str[] = "now or never";
  s21_size c = ' ';

  ck_assert_ptr_eq(s21_memchr(str, c, 3), memchr(str, c, 3));
}
END_TEST

START_TEST(s21_memchr_test_7) {
  const char str[] = "now or never";

  ck_assert_ptr_eq(s21_memchr(str, 'v', sizeof(str)),
                   memchr(str, 'v', sizeof(str)));
}
END_TEST

START_TEST(s21_memchr_test_8) {
  const char str[] = "now or never";
  s21_size c = 'l';

  ck_assert_ptr_eq(s21_memchr(str, c, 10), memchr(str, c, 10));
}
END_TEST

START_TEST(s21_memchr_test_9) {
  const char str[] = "now or never";
  s21_size c = 'v';

  ck_assert_ptr_eq(s21_memchr(str, c, 7), memchr(str, c, 7));
}
END_TEST

START_TEST(s21_memchr_test_10) {
  const char str[] = "now or never";
  s21_size c = 'm';

  ck_assert_ptr_eq(s21_memchr(str, c, 10), memchr(str, c, 10));
}
END_TEST

START_TEST(s21_memchr_test_11) { ck_assert_ptr_null(s21_memchr(NULL, 'a', 5)); }
END_TEST

Suite* s21_memchr_suite(void) {
  Suite* suite = suite_create("s21_memchr");
  TCase* tcase_core = tcase_create("case_memchr");
  tcase_add_test(tcase_core, s21_memchr_test_1);
  tcase_add_test(tcase_core, s21_memchr_test_2);
  tcase_add_test(tcase_core, s21_memchr_test_3);
  tcase_add_test(tcase_core, s21_memchr_test_4);
  tcase_add_test(tcase_core, s21_memchr_test_5);
  tcase_add_test(tcase_core, s21_memchr_test_6);
  tcase_add_test(tcase_core, s21_memchr_test_7);
  tcase_add_test(tcase_core, s21_memchr_test_8);
  tcase_add_test(tcase_core, s21_memchr_test_9);
  tcase_add_test(tcase_core, s21_memchr_test_10);
  tcase_add_test(tcase_core, s21_memchr_test_11);

  suite_add_tcase(suite, tcase_core);
  return suite;
}
