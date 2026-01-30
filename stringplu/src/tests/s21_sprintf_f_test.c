#include "s21_test.h"

START_TEST(s21_sprintf_e_test_2) {
  char str1[20] = {'\0'};
  char str2[20] = {'\0'};
  long double c = 13.28;

  ck_assert_int_eq(s21_sprintf(str1, "%.0Le", c), sprintf(str2, "%.0Le", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_e_test_3) {
  char str1[500] = {'\0'};
  char str2[500] = {'\0'};
  long double c = 1254.0002445343;

  ck_assert_int_eq(s21_sprintf(str1, "%.Le", c), sprintf(str2, "%.Le", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(s21_sprintf_e_test_4) {
  char str1[80] = {'\0'};
  char str2[80] = {'\0'};
  long double c = 0.0000000000033343;

  ck_assert_int_eq(s21_sprintf(str1, "%.13Le", c), sprintf(str2, "%.13Le", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_e_test_5) {
  char str1[1000] = {'\0'};
  char str2[1000] = {'\0'};
  long double c = -254.25376837;

  ck_assert_int_eq(s21_sprintf(str1, "%.15Le", c), sprintf(str2, "%.15Le", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_e_test_6) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  const char* format = "%Le";
  long double c = 87787725337.3737371;

  ck_assert_int_eq(s21_sprintf(str1, format, c), sprintf(str2, format, c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_e_test_7) {
  char str1[20] = {'\0'};
  char str2[20] = {'\0'};
  const char* format = "%019e";
  float c = 0;

  ck_assert_int_eq(s21_sprintf(str1, format, c), sprintf(str2, format, c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_e_test_8) {
  char str1[500] = {'\0'};
  char str2[500] = {'\0'};
  float c = 0;

  ck_assert_int_eq(s21_sprintf(str1, "%11e", c), sprintf(str2, "%11e", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_e_test_9) {
  char str1[1024] = {'\0'};
  char str2[1024] = {'\0'};
  float c1 = 0;
  double c2 = 0;
  long double c3 = 87980.677908;
  float c4 = 3.5;
  double c5 = 0.967844;
  long double c6 = 5576569076.68677546464546;

  ck_assert_int_eq(
      s21_sprintf(str1, "% .0e %.le %Le %e %le %Le", c1, c2, c3, c4, c5, c6),
      sprintf(str2, "% .e %.le %Le %e %le %Le", c1, c2, c3, c4, c5, c6));
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_remove_trailing_zeros_with_exponent) {
  char test1[50] = "123.000e+02";
  remove_trailing_zeros_g(test1);
  ck_assert_str_eq(test1, "123e+02");

  char test2[50] = "1.23000E-03";
  remove_trailing_zeros_g(test2);
  ck_assert_str_eq(test2, "1.23E-03");

  char test3[50] = "0.000e+00";
  remove_trailing_zeros_g(test3);
  ck_assert_str_eq(test3, "0e+00");

  char test4[50] = "1.500e+10";
  remove_trailing_zeros_g(test4);
  ck_assert_str_eq(test4, "1.5e+10");

  char test5[50] = "100.000e-02";
  remove_trailing_zeros_g(test5);
  ck_assert_str_eq(test5, "100e-02");

  char test6[50] = "1.000100e+05";
  remove_trailing_zeros_g(test6);
  ck_assert_str_eq(test6, "1.0001e+05");

  char test7[50] = "123.e+02";
  remove_trailing_zeros_g(test7);
  ck_assert_str_eq(test7, "123e+02");

  char test8[50] = "0.001200e+03";
  remove_trailing_zeros_g(test8);
  ck_assert_str_eq(test8, "0.0012e+03");
}
END_TEST

Suite* s21_sprintf_e_suite(void) {
  Suite* suite = suite_create("s21_sprintf_e");
  TCase* tcase_core = tcase_create("case_sprintf_e");

  tcase_add_test(tcase_core, s21_sprintf_e_test_2);
  tcase_add_test(tcase_core, s21_sprintf_e_test_3);
  tcase_add_test(tcase_core, s21_sprintf_e_test_4);
  tcase_add_test(tcase_core, s21_sprintf_e_test_5);
  tcase_add_test(tcase_core, s21_sprintf_e_test_6);
  tcase_add_test(tcase_core, s21_sprintf_e_test_7);
  tcase_add_test(tcase_core, s21_sprintf_e_test_8);
  tcase_add_test(tcase_core, s21_sprintf_e_test_9);
  tcase_add_test(tcase_core, test_remove_trailing_zeros_with_exponent);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

// sprintf_E

START_TEST(s21_sprintf_E_test_2) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  long double c = 13.28;

  ck_assert_int_eq(s21_sprintf(str1, "%.0LE", c), sprintf(str2, "%.0LE", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_E_test_3) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  long double c = 1254.0002445343;

  ck_assert_int_eq(s21_sprintf(str1, "%.LE", c), sprintf(str2, "%.LE", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(s21_sprintf_E_test_4) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  long double c = 0.0000000000033343;

  ck_assert_int_eq(s21_sprintf(str1, "%.13LE", c), sprintf(str2, "%.13LE", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_E_test_5) {
  char str1[128] = {'\0'};
  char str2[128] = {'\0'};
  long double c = -254.25376837;

  ck_assert_int_eq(s21_sprintf(str1, "%.15LE", c), sprintf(str2, "%.15LE", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_E_test_6) {
  char str1[200] = {'\0'};
  char str2[200] = {'\0'};
  const char* format = "%LE";
  long double c = 87787725337.3737371;

  ck_assert_int_eq(s21_sprintf(str1, format, c), sprintf(str2, format, c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_E_test_7) {
  char str1[50] = {'\0'};
  char str2[50] = {'\0'};
  const char* format = "%019E";
  float c = 0;

  ck_assert_int_eq(s21_sprintf(str1, format, c), sprintf(str2, format, c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_E_test_8) {
  char str1[256] = {'\0'};
  char str2[256] = {'\0'};
  float c = 0;

  ck_assert_int_eq(s21_sprintf(str1, "%11E", c), sprintf(str2, "%11E", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_E_test_9) {
  char str1[128] = {'\0'};
  char str2[128] = {'\0'};
  float c1 = 0;
  double c2 = 0;
  long double c3 = 87980.677908;
  float c4 = 3.5;
  double c5 = 0.967844;
  long double c6 = 5576569076.68677546464546;

  ck_assert_int_eq(
      s21_sprintf(str1, "% .0E %.5E %LE %E %7.1E %LE", c1, c2, c3, c4, c5, c6),
      sprintf(str2, "% .0E %.5E %LE %E %7.1E %LE", c1, c2, c3, c4, c5, c6));
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* s21_sprintf_E_suite(void) {
  Suite* suite = suite_create("s21_sprintf_E");
  TCase* tcase_core = tcase_create("case_sprintf_E");

  tcase_add_test(tcase_core, s21_sprintf_E_test_2);
  tcase_add_test(tcase_core, s21_sprintf_E_test_3);
  tcase_add_test(tcase_core, s21_sprintf_E_test_4);
  tcase_add_test(tcase_core, s21_sprintf_E_test_5);
  tcase_add_test(tcase_core, s21_sprintf_E_test_6);
  tcase_add_test(tcase_core, s21_sprintf_E_test_7);
  tcase_add_test(tcase_core, s21_sprintf_E_test_8);
  tcase_add_test(tcase_core, s21_sprintf_E_test_9);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

// sprintf_f

START_TEST(s21_sprintf_f_test_1) {
  char str1[128] = {'\0'};
  char str2[128] = {'\0'};
  long double c = 24224.5324524552345345;

  ck_assert_int_eq(s21_sprintf(str1, "%Lf", c), sprintf(str2, "%Lf", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f_test_1_1) {
  char str1[128] = {'\0'};
  char str2[128] = {'\0'};
  double c = 1.00000000000000000;

  ck_assert_int_eq(s21_sprintf(str1, "%.3f", c), sprintf(str2, "%.3f", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f_test_2) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  long double val = 96.54;

  ck_assert_int_eq(s21_sprintf(str1, "%#10Lf", val),
                   sprintf(str2, "%#10Lf", val));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f_test_3) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  long double c = 85.24;

  ck_assert_int_eq(s21_sprintf(str1, "%.0Lf", c), sprintf(str2, "%.0Lf", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f_test_4) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  long double c = 35.3374;

  ck_assert_int_eq(s21_sprintf(str1, "%*.*Lf", 5, 8, c),
                   sprintf(str2, "%*.*Lf", 5, 8, c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f_test_5) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  long double c = 15.35;

  ck_assert_int_eq(s21_sprintf(str1, "%-9.13Lf", c),
                   sprintf(str2, "%-9.13Lf", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f_test_6) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  long double c = -99.411525225;

  ck_assert_int_eq(s21_sprintf(str1, "%-16.*Lf", 10, c),
                   sprintf(str2, "%-16.*Lf", 10, c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f_test_7) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  long double c = 5363737373.7377833583;

  ck_assert_int_eq(s21_sprintf(str1, "% 03.8Lf", c),
                   sprintf(str2, "% 03.8Lf", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f_test_8) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  float c = 0;

  ck_assert_int_eq(s21_sprintf(str1, "% f", c), sprintf(str2, "% f", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f_test_9) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  float c1 = 0;
  double c2 = 0;
  long double c3 = 252535.4343453;
  float c4 = 3.5;
  double c5 = 3535.63534534;
  long double c6 = 433343364643.36463643335;

  ck_assert_int_eq(s21_sprintf(str1, "% .0f %*.lf %Lf %.*f %lf %Lf", c1, 3, c2,
                               c3, 8, c4, c5, c6),
                   sprintf(str2, "% .0f %*.lf %Lf %.*f %lf %Lf", c1, 3, c2, c3,
                           8, c4, c5, c6));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f_test_10) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  const char* format = "%10Lf";
  long double c = 15;

  ck_assert_int_eq(s21_sprintf(str1, format, c), sprintf(str2, format, c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f_test_11) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};
  long double c = 85.6;

  ck_assert_int_eq(s21_sprintf(str1, "%+Lf", c), sprintf(str2, "%+Lf", c));
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* s21_sprintf_f_suite(void) {
  Suite* suite = suite_create("s21_sprintf_f");
  TCase* tcase_core = tcase_create("case_sprintf_f");
  tcase_add_test(tcase_core, s21_sprintf_f_test_1);
  tcase_add_test(tcase_core, s21_sprintf_f_test_1_1);
  tcase_add_test(tcase_core, s21_sprintf_f_test_2);
  tcase_add_test(tcase_core, s21_sprintf_f_test_3);
  tcase_add_test(tcase_core, s21_sprintf_f_test_4);
  tcase_add_test(tcase_core, s21_sprintf_f_test_5);
  tcase_add_test(tcase_core, s21_sprintf_f_test_6);
  tcase_add_test(tcase_core, s21_sprintf_f_test_7);
  tcase_add_test(tcase_core, s21_sprintf_f_test_8);
  tcase_add_test(tcase_core, s21_sprintf_f_test_9);
  tcase_add_test(tcase_core, s21_sprintf_f_test_10);
  tcase_add_test(tcase_core, s21_sprintf_f_test_11);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

// sprintf_g
START_TEST(s21_sprintf_g_test_1) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double a = 1235.3256800000;

  ck_assert_int_eq(s21_sprintf(str1, "[%+-.2g]", a),
                   sprintf(str2, "[%+-.2g]", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_g_test_2) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  long double a = 87566852586.365452;
  long double b = 4278521245.38865;

  ck_assert_int_eq(
      s21_sprintf(str1, "[%-*.Lg] [%-*.Lg] [%0Lg]", 15, a, 15, b, a * b),
      sprintf(str2, "[%-*.Lg] [%-*.Lg] [%0Lg]", 15, a, 15, b, a * b));
  ck_assert_str_eq(str1, str2);
}

END_TEST
START_TEST(s21_sprintf_g_test_3) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double a = 87598456842684154;
  double b = -42154884226858222;

  ck_assert_int_eq(s21_sprintf(str1, "[%020.2g] [%0 20.2g]", a, b),
                   sprintf(str2, "[%020.2g] [%0 20.2g]", a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_g_test_4) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double a = 3.14;
  double b = 3.14;

  ck_assert_int_eq(
      s21_sprintf(str1, "[%-10.*g] [%-10.5g] [%+#3.6g]", 1, a, b, a - b),
      sprintf(str2, "[%-10.*g] [%-10.5g] [%+#3.6g]", 1, a, b, a - b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_g_test_5) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double b = 9;

  int n1 = s21_sprintf(str1, "[%-#10.*g]", 5, b);
  int n2 = sprintf(str2, "[%-#10.*g]", 5, b);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(s21_sprintf_g_test_6) {
  const int SIZE = 1000;
  char str1[SIZE];
  char str2[SIZE];
  double a = 87598456842684154;
  double b = 42154884226858222;

  ck_assert_int_eq(s21_sprintf(str1, "[%-15.3g] [%-15g]", a, b),
                   sprintf(str2, "[%-15.3g] [%-15g]", a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_g_test_7) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double a = 2.35987;
  double b = 3.6589;

  ck_assert_int_eq(s21_sprintf(str1, "[%#7.0g] [%+0#7.0g]", a, b),
                   sprintf(str2, "[%#7.0g] [%+0#7.0g]", a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_g_test_8) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double a = 2.35987;
  double b = 3.6589;

  ck_assert_int_eq(s21_sprintf(str1, "[%#7.0g] [%+-#10.0g]", a, b),
                   sprintf(str2, "[%#7.0g] [%+-#10.0g]", a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_g_test_9) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double b = 0;

  ck_assert_int_eq(s21_sprintf(str1, "[%-7.1g]", b),
                   sprintf(str2, "[%-7.1g]", b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_g_test_10) {
  const int SIZE = 1000;
  char str1[SIZE];
  char str2[SIZE];
  double a = 87598456842684154;
  double b = 42154884226858222;

  ck_assert_int_eq(s21_sprintf(str1, "test[%-15.3g] %-15gg", a, b),
                   sprintf(str2, "test[%-15.3g] %-15gg", a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* s21_sprintf_g_suite(void) {
  Suite* suite = suite_create("s21_sprintf_g");
  TCase* tcase_core = tcase_create("case_sprintf_g");
  tcase_add_test(tcase_core, s21_sprintf_g_test_1);
  tcase_add_test(tcase_core, s21_sprintf_g_test_2);
  tcase_add_test(tcase_core, s21_sprintf_g_test_3);
  tcase_add_test(tcase_core, s21_sprintf_g_test_4);
  tcase_add_test(tcase_core, s21_sprintf_g_test_5);
  tcase_add_test(tcase_core, s21_sprintf_g_test_6);
  tcase_add_test(tcase_core, s21_sprintf_g_test_7);
  tcase_add_test(tcase_core, s21_sprintf_g_test_8);
  tcase_add_test(tcase_core, s21_sprintf_g_test_9);
  tcase_add_test(tcase_core, s21_sprintf_g_test_10);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

// sprintf_G
START_TEST(s21_sprintf_G_test_1) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double a = 1235.3256800000;

  ck_assert_int_eq(s21_sprintf(str1, "[%+-.2G]", a),
                   sprintf(str2, "[%+-.2G]", a));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_G_test_2) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  long double a = 87566852586.365452;
  long double b = 4278521245.38865;

  ck_assert_int_eq(
      s21_sprintf(str1, "[%-*.LG] [%-*.LG] [%0LG]", 15, a, 15, b, a * b),
      sprintf(str2, "[%-*.LG] [%-*.LG] [%0LG]", 15, a, 15, b, a * b));
  ck_assert_str_eq(str1, str2);
}

END_TEST
START_TEST(s21_sprintf_G_test_3) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double a = 87598456842684154;
  double b = -42154884226858222;

  ck_assert_int_eq(s21_sprintf(str1, "[%020.2G] [%0 20.2G]", a, b),
                   sprintf(str2, "[%020.2G] [%0 20.2G]", a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_G_test_4) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double a = 3.14;
  double b = 3.14;

  ck_assert_int_eq(
      s21_sprintf(str1, "[%-10.*G] [%-10.5G] %+#3.6G", 1, a, b, a - b),
      sprintf(str2, "[%-10.*G] [%-10.5G] %+#3.6G", 1, a, b, a - b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_G_test_5) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double b = 4;

  ck_assert_int_eq(s21_sprintf(str1, "[%-#10.*G]", 5, b),
                   sprintf(str2, "[%-#10.*G]", 5, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_G_test_6) {
  const int SIZE = 1000;
  char str1[SIZE];
  char str2[SIZE];
  double a = 87598456842684154;
  double b = 42154884226858222;

  ck_assert_int_eq(s21_sprintf(str1, "[%-15.3G] [%-15G]", a, b),
                   sprintf(str2, "[%-15.3G] [%-15G]", a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_G_test_7) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double a = 2.35987;
  double b = 3.6589;

  ck_assert_int_eq(s21_sprintf(str1, "[%#7.0G] [%+0#7.0G]", a, b),
                   sprintf(str2, "[%#7.0G] [%+0#7.0G]", a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_G_test_8) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double a = 2.35987;
  double b = 3.6589;

  ck_assert_int_eq(s21_sprintf(str1, "[%#7.0G] [%+-#10.0G]", a, b),
                   sprintf(str2, "[%#7.0G] [%+-#10.0G]", a, b));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_G_test_9) {
  const int SIZE = 100;
  char str1[SIZE];
  char str2[SIZE];
  double b = 0;

  ck_assert_int_eq(s21_sprintf(str1, "[%-7.1G]", b),
                   sprintf(str2, "[%-7.1G]", b));
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(s21_sprintf_rounding_all_nines) {
  char str1[500] = {'\0'};
  char str2[500] = {'\0'};

  double val2 = 0.999999;
  int len1 = s21_sprintf(str1, "%.5f", val2);
  int len2 = sprintf(str2, "%.5f", val2);

  ck_assert_int_eq(len1, len2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* s21_sprintf_G_suite(void) {
  Suite* suite = suite_create("s21_sprintf_G");
  TCase* tcase_core = tcase_create("case_sprintf_G");
  tcase_add_test(tcase_core, s21_sprintf_G_test_1);
  tcase_add_test(tcase_core, s21_sprintf_G_test_2);
  tcase_add_test(tcase_core, s21_sprintf_G_test_3);
  tcase_add_test(tcase_core, s21_sprintf_G_test_4);
  tcase_add_test(tcase_core, s21_sprintf_G_test_5);
  tcase_add_test(tcase_core, s21_sprintf_G_test_6);
  tcase_add_test(tcase_core, s21_sprintf_G_test_7);
  tcase_add_test(tcase_core, s21_sprintf_G_test_8);
  tcase_add_test(tcase_core, s21_sprintf_G_test_9);
  tcase_add_test(tcase_core, s21_sprintf_rounding_all_nines);
  suite_add_tcase(suite, tcase_core);
  return suite;
}
