#include "s21_test.h"

START_TEST(s21_sprintf_d_test_1) {
  char str1[100] = "";
  char str2[100] = "";
  int d = 0;

  ck_assert_int_eq(s21_sprintf(str1, "%d", d), sprintf(str2, "%d", d));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_2) {
  char str1[100] = "";
  char str2[100] = "";

  ck_assert_int_eq(s21_sprintf(str1, "%d", 75), sprintf(str2, "%d", 75));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_3) {
  char str1[100] = {0};
  char str2[100] = {0};
  int a = 63;

  ck_assert_int_eq(s21_sprintf(str1, "%-3d", a), sprintf(str2, "%-3d", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_4) {
  char str1[100] = {0};
  char str2[100] = {0};
  int a = 5;

  ck_assert_int_eq(s21_sprintf(str1, "%3d", a), sprintf(str2, "%3d", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_5) {
  char str1[100] = {0};
  char str2[100] = {0};
  int a = 48;

  ck_assert_int_eq(s21_sprintf(str1, "%+3d", a), sprintf(str2, "%+3d", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_6) {
  char str1[100] = {0};
  char str2[100] = {0};
  int a = 32;

  ck_assert_int_eq(s21_sprintf(str1, "%3.3d", a), sprintf(str2, "%3.3d", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_7) {
  char str1[100] = {0};
  char str2[100] = {0};
  int a = 45;

  ck_assert_int_eq(s21_sprintf(str1, "%-5.5d", a), sprintf(str2, "%-5.5d", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_8) {
  char str1[100] = {0};
  char str2[100] = {0};
  int a = 12;

  ck_assert_int_eq(s21_sprintf(str1, "%*.3d", 2, a),
                   sprintf(str2, "%*.3d", 2, a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_9) {
  char str1[100] = {0};
  char str2[100] = {0};
  int a = 22;

  ck_assert_int_eq(s21_sprintf(str1, "%5.*d", 8, a),
                   sprintf(str2, "%5.*d", 8, a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_10) {
  char str1[100] = {0};
  char str2[100] = {0};
  int a = 105456;

  ck_assert_int_eq(s21_sprintf(str1, "%*.*d", 6, 3, a),
                   sprintf(str2, "%*.*d", 6, 3, a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_11) {
  char str1[100] = {0};
  char str2[100] = {0};
  int a = 45;

  ck_assert_int_eq(s21_sprintf(str1, "%05d", a), sprintf(str2, "%05d", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_12) {
  char str1[100] = {0};
  char str2[100] = {0};
  int a = 12;

  ck_assert_int_eq(s21_sprintf(str1, "%-32.5d", a),
                   sprintf(str2, "%-32.5d", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_13) {
  char str1[100] = {0};
  char str2[100] = {0};
  int a = 22;

  ck_assert_int_eq(s21_sprintf(str1, "% d", a), sprintf(str2, "% d", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_14) {
  char str1[100] = {0};
  char str2[100] = {0};
  int a = 105456;

  ck_assert_int_eq(s21_sprintf(str1, "%*.*d", 4, 3, a),
                   sprintf(str2, "%*.*d", 4, 3, a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_15) {
  char str1[100] = "";
  char str2[100] = "";
  int e = 123;

  ck_assert_int_eq(s21_sprintf(str1, "%d", e), sprintf(str2, "%d", e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_16) {
  char str1[100] = "";
  char str2[100] = "";
  int e = 123;

  ck_assert_int_eq(s21_sprintf(str1, "%*d", 5, e), sprintf(str2, "%*d", 5, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_17) {
  char str1[100] = "";
  char str2[100] = "";
  int b = -66;
  int f = 18;

  ck_assert_int_eq(s21_sprintf(str1, "%.6d %5d", b, f),
                   sprintf(str2, "%.6d %5d", b, f));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_18) {
  char str1[100] = "vhngmjhj";
  char str2[100] = "vhngmjhj";
  int c = 35;

  ck_assert_int_eq(s21_sprintf(str2, "%d", c), sprintf(str1, "%d", c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_19) {
  char str1[100] = "";
  char str2[100] = "";
  short int c = 67;

  ck_assert_int_eq(s21_sprintf(str1, "%hd", c), sprintf(str2, "%hd", c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_d_test_20) {
  char str1[100] = "";
  char str2[100] = "";
  long int c = 65848457;

  ck_assert_int_eq(s21_sprintf(str1, "%ld", c), sprintf(str2, "%ld", c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(test_null_buffer_coverage) {
  flags_t f = {0};
  s21_handle_d(NULL, 42, f, 0, -1);
  s21_handle_d(NULL, -42, f, 5, 3);
  s21_handle_d(NULL, 0, f, 10, 0);
}
END_TEST

START_TEST(test_precision_zero_with_zero_value) {
  char str1[100] = "";
  char str2[100] = "";
  int a = 42;

  ck_assert_int_eq(s21_sprintf(str1, "%+05d", a), sprintf(str2, "%+05d", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_zero_flag_with_minus_sign) {
  char str1[100] = "";
  char str2[100] = "";
  int a = -42;

  ck_assert_int_eq(s21_sprintf(str1, "%05d", a), sprintf(str2, "%05d", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_zero_flag_with_space) {
  char str1[100] = "";
  char str2[100] = "";
  int a = 42;

  ck_assert_int_eq(s21_sprintf(str1, "% 05d", a), sprintf(str2, "% 05d", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_zero_flag_with_precision) {
  char str1[100] = "";
  char str2[100] = "";
  int a = 42;

  ck_assert_int_eq(s21_sprintf(str1, "%05.2d", a), sprintf(str2, "%05.2d", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_precision_zero_with_non_zero) {
  char str1[100] = "";
  char str2[100] = "";
  int a = 123;

  ck_assert_int_eq(s21_sprintf(str1, "%.0d", a), sprintf(str2, "%.0d", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* s21_sprintf_d_suite(void) {
  Suite* suite = suite_create("s21_sprintf_d");
  TCase* tcase_core = tcase_create("case_sprintf_d");
  tcase_add_test(tcase_core, s21_sprintf_d_test_1);
  tcase_add_test(tcase_core, s21_sprintf_d_test_2);
  tcase_add_test(tcase_core, s21_sprintf_d_test_3);
  tcase_add_test(tcase_core, s21_sprintf_d_test_4);
  tcase_add_test(tcase_core, s21_sprintf_d_test_5);
  tcase_add_test(tcase_core, s21_sprintf_d_test_6);
  tcase_add_test(tcase_core, s21_sprintf_d_test_7);
  tcase_add_test(tcase_core, s21_sprintf_d_test_8);
  tcase_add_test(tcase_core, s21_sprintf_d_test_9);
  tcase_add_test(tcase_core, s21_sprintf_d_test_10);
  tcase_add_test(tcase_core, s21_sprintf_d_test_11);
  tcase_add_test(tcase_core, s21_sprintf_d_test_12);
  tcase_add_test(tcase_core, s21_sprintf_d_test_13);
  tcase_add_test(tcase_core, s21_sprintf_d_test_14);
  tcase_add_test(tcase_core, s21_sprintf_d_test_15);
  tcase_add_test(tcase_core, s21_sprintf_d_test_16);
  tcase_add_test(tcase_core, s21_sprintf_d_test_17);
  tcase_add_test(tcase_core, s21_sprintf_d_test_18);
  tcase_add_test(tcase_core, s21_sprintf_d_test_19);
  tcase_add_test(tcase_core, s21_sprintf_d_test_20);
  tcase_add_test(tcase_core, test_null_buffer_coverage);
  tcase_add_test(tcase_core, test_precision_zero_with_zero_value);
  tcase_add_test(tcase_core, test_zero_flag_with_minus_sign);
  tcase_add_test(tcase_core, test_zero_flag_with_space);
  tcase_add_test(tcase_core, test_zero_flag_with_precision);
  tcase_add_test(tcase_core, test_precision_zero_with_non_zero);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

START_TEST(s21_sprintf_i_test_1) {
  char str1[256] = {'\0'};
  char str2[256] = {'\0'};
  const char* format = "%-5i";
  int c = 69;

  ck_assert_int_eq(s21_sprintf(str1, format, c), sprintf(str2, format, c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_i_test_2) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  int c = 69;

  ck_assert_int_eq(s21_sprintf(str1, "%012i", c), sprintf(str2, "%012i", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_i_test_3) {
  char str1[256] = {'\0'};
  char str2[256] = {'\0'};
  int c = 69;

  ck_assert_int_eq(s21_sprintf(str1, "%5.*i", 5, c),
                   sprintf(str2, "%5.*i", 5, c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_i_test_4) {
  char str1[256] = "ghfgfgfg";
  char str2[256] = "ghfgfgfg";
  int c = 69;

  ck_assert_int_eq(
      s21_sprintf(str1, "%.*i %d %4.*i %13d %d", 5, c, -101, 8, 318, 0,
                  -635635),
      sprintf(str2, "%.*i %d %4.*i %13d %d", 5, c, -101, 8, 318, 0, -635635));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_i_test_5) {
  char str1[256] = {'\0'};
  char str2[256] = {'\0'};
  long int c = 6567678684;

  ck_assert_int_eq(s21_sprintf(str1, "%+6.31li", c),
                   sprintf(str2, "%+6.31li", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_i_test_5_1) {
  char str1[256] = {'\0'};
  char str2[256] = {'\0'};
  long long int c = 6567678684;

  ck_assert_int_eq(s21_sprintf(str1, "%+6.31lli", c),
                   sprintf(str2, "%+6.31lli", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_i_test_6) {
  char str1[256] = {'\0'};
  char str2[256] = {'\0'};
  short int c = 6958;

  ck_assert_int_eq(s21_sprintf(str1, "%-16.9hi", c),
                   sprintf(str2, "%-16.9hi", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* s21_sprintf_i_suite(void) {
  Suite* suite = suite_create("s21_sprintf_i");
  TCase* tcase_core = tcase_create("case_sprintf_i");
  tcase_add_test(tcase_core, s21_sprintf_i_test_1);
  tcase_add_test(tcase_core, s21_sprintf_i_test_2);
  tcase_add_test(tcase_core, s21_sprintf_i_test_3);
  tcase_add_test(tcase_core, s21_sprintf_i_test_4);
  tcase_add_test(tcase_core, s21_sprintf_i_test_5);
  tcase_add_test(tcase_core, s21_sprintf_i_test_5_1);
  tcase_add_test(tcase_core, s21_sprintf_i_test_6);
  suite_add_tcase(suite, tcase_core);

  return suite;
}