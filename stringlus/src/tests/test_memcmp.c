#include "s21_test.h"

START_TEST(s21_memcmp_test_1) {
  const char str1[] = "";
  const char str2[] = "";

  ck_assert_int_eq(s21_memcmp(str1, str2, 0), memcmp(str1, str2, 0));
}
END_TEST

START_TEST(s21_memcmp_test_2) {
  const char str1[] = "Enjoy the moment";
  const char str2[] = "Enjoy the moment";

  ck_assert_int_eq(s21_memcmp(str1, str2, sizeof(str1)),
                   memcmp(str1, str2, sizeof(str1)));
}
END_TEST

START_TEST(s21_memcmp_test_3) {
  const char str1[] = "Enjoy the moment";
  const char str2[] = "Enjoy the moment";

  ck_assert_int_eq(s21_memcmp(str1, str2, strlen(str1)),
                   memcmp(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(s21_memcmp_test_4) {
  char str1[] = "Enjoy the moment!";
  const char str2[] = "Enjoy the moment.";

  ck_assert_int_eq(s21_memcmp(str1, str2, sizeof(str1)),
                   memcmp(str1, str2, sizeof(str1)));
}
END_TEST

START_TEST(s21_memcmp_test_5) {
  char str1[] = "Enjoy the moment";
  const char str2[] = "the moment Enjoy";

  ck_assert_int_eq(s21_memcmp(str1, str2, sizeof(str1)),
                   memcmp(str1, str2, sizeof(str1)));
}
END_TEST

START_TEST(s21_memcmp_test_6) {
  const char str1[] = "Enjoy the moment ";
  char str2[] = "Enjoy the moment";

  ck_assert_int_eq(s21_memcmp(str1, str2, sizeof(str2)),
                   memcmp(str1, str2, sizeof(str2)));
}
END_TEST

START_TEST(s21_memcmp_test_7) {
  char str1[] = "Enjoy\0 the moment";
  const char str2[] = "Enjoy the moment\0";

  ck_assert_int_eq(s21_memcmp(str1, str2, sizeof(str1)),
                   memcmp(str1, str2, sizeof(str1)));
}
END_TEST

START_TEST(s21_memcmp_test_8) {
  const char str1[] = "Enjoy the moment";
  const char str2[] = "Enjoy the mo ment";

  ck_assert_int_eq(s21_memcmp(str1, str2, 10), memcmp(str1, str2, 10));
}
END_TEST

START_TEST(s21_memcmp_test_9) {
  const char str1[] = "Enjoy the moment";
  const char str2[] = "Enjoy the Moment";

  ck_assert_int_eq(s21_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
}
END_TEST

START_TEST(s21_memcmp_test_10) {
  ck_assert_int_eq(s21_memcmp(NULL, NULL, 5), 0);
}
END_TEST

START_TEST(s21_memcmp_test_11) {
  const char str[] = "test";
  ck_assert_int_eq(s21_memcmp(str, NULL, 5), 0);
}
END_TEST

Suite* s21_memcmp_suite(void) {
  Suite* suite = suite_create("s21_memcmp");
  TCase* tcase_core = tcase_create("case_memcmp");
  tcase_add_test(tcase_core, s21_memcmp_test_1);
  tcase_add_test(tcase_core, s21_memcmp_test_2);
  tcase_add_test(tcase_core, s21_memcmp_test_3);
  tcase_add_test(tcase_core, s21_memcmp_test_4);
  tcase_add_test(tcase_core, s21_memcmp_test_5);
  tcase_add_test(tcase_core, s21_memcmp_test_6);
  tcase_add_test(tcase_core, s21_memcmp_test_7);
  tcase_add_test(tcase_core, s21_memcmp_test_8);
  tcase_add_test(tcase_core, s21_memcmp_test_9);
  tcase_add_test(tcase_core, s21_memcmp_test_10);
  tcase_add_test(tcase_core, s21_memcmp_test_11);

  suite_add_tcase(suite, tcase_core);
  return suite;
}