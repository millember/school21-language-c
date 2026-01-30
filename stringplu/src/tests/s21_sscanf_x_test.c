#include <check.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#include "../s21_string.h"

// Вспомогательный макрос для unsigned long
#define CK_ASSERT_ULONG_EQ(actual, expected)                                 \
  ck_assert_msg((actual) == (expected), "Expected %lu, got %lu", (expected), \
                (actual))

// Для unsigned long long
#define CK_ASSERT_ULLONG_EQ(actual, expected)                                  \
  ck_assert_msg((actual) == (expected), "Expected %llu, got %llu", (expected), \
                (actual))

// --- Тесты для %u (десятичные) ---
START_TEST(test_s21_sscanf_u_basic) {
  const char* input = "123";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%u", &u_std);
  int r_my = s21_sscanf(input, "%u", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);
}
END_TEST

START_TEST(test_s21_sscanf_u_with_spaces) {
  const char* input = "  456  ";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%u", &u_std);
  int r_my = s21_sscanf(input, "%u", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);
}
END_TEST

START_TEST(test_s21_sscanf_u_leading_zeros) {
  const char* input = "00789";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%u", &u_std);
  int r_my = s21_sscanf(input, "%u", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);
}
END_TEST

START_TEST(test_s21_sscanf_u_invalid_char) {
  const char* input = "123abc";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%u", &u_std);
  int r_my = s21_sscanf(input, "%u", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);  // 123
}
END_TEST

// --- Тесты для %o (восьмеричные) ---
START_TEST(test_s21_sscanf_o_basic) {
  const char* input = "777";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%o", &u_std);
  int r_my = s21_sscanf(input, "%o", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);  // 511
}
END_TEST

START_TEST(test_s21_sscanf_o_invalid_digit) {
  const char* input = "789";  // '8' недопустим в octal
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%o", &u_std);
  int r_my = s21_sscanf(input, "%o", &u_my);
  ck_assert_int_eq(r_my, r_std);   // оба прочитают "7"
  ck_assert_uint_eq(u_std, u_my);  // 7
}
END_TEST

// --- Тесты для %x (шестнадцатеричные) ---
START_TEST(test_s21_sscanf_x_no_prefix) {
  const char* input = "FF";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%x", &u_std);
  int r_my = s21_sscanf(input, "%x", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);  // 255
}
END_TEST

START_TEST(test_s21_sscanf_x_with_0x) {
  const char* input = "0xFF";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%x", &u_std);
  int r_my = s21_sscanf(input, "%x", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);
}
END_TEST

START_TEST(test_s21_sscanf_x_with_0X) {
  const char* input = "0XaB";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%x", &u_std);
  int r_my = s21_sscanf(input, "%x", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);  // 171
}
END_TEST

START_TEST(test_s21_sscanf_x_mixed_case) {
  const char* input = "fF0";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%x", &u_std);
  int r_my = s21_sscanf(input, "%x", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);  // 4016
}
END_TEST

// --- Тесты с модификаторами длины ---
START_TEST(test_s21_sscanf_hu_short) {
  const char* input = "65535";
  unsigned short us_std = 0, us_my = 0;
  int r_std = sscanf(input, "%hu", &us_std);
  int r_my = s21_sscanf(input, "%hu", &us_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(us_std, us_my);
}
END_TEST

START_TEST(test_s21_sscanf_lu_long) {
  const char* input = "4294967295";
  unsigned long ul_std = 0, ul_my = 0;
  int r_std = sscanf(input, "%lu", &ul_std);
  int r_my = s21_sscanf(input, "%lu", &ul_my);
  ck_assert_int_eq(r_my, r_std);
  CK_ASSERT_ULONG_EQ(ul_std, ul_my);
}
END_TEST

// --- Тесты подавления ---
START_TEST(test_s21_sscanf_u_suppress) {
  const char* input = "123 456";
  unsigned int u_my = 0;
  int r_my = s21_sscanf(input, "%*u %u", &u_my);
  int r_std = sscanf(input, "%*u %u", &u_my);
  ck_assert_int_eq(r_my, r_std);  // оба должны вернуть 1
  ck_assert_uint_eq(u_my, 456u);
}
END_TEST

// --- Недопустимый ввод ---
START_TEST(test_s21_sscanf_u_no_digits) {
  const char* input = "abc";
  unsigned int u_my = 0;
  int r_my = s21_sscanf(input, "%u", &u_my);
  int r_std = sscanf(input, "%u", &u_my);
  ck_assert_int_eq(r_my, r_std);  // 0
}
END_TEST

// ============= Тесты длины для %o =============
START_TEST(test_s21_sscanf_ho_octal) {
  const char* input = "177777";  // 65535 в восьмеричной
  unsigned short us_std = 0, us_my = 0;
  int r_std = sscanf(input, "%ho", &us_std);
  int r_my = s21_sscanf(input, "%ho", &us_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(us_std, us_my);
}
END_TEST

START_TEST(test_s21_sscanf_lo_octal) {
  const char* input = "37777777777";  // 4294967295 в octal
  unsigned long ul_std = 0, ul_my = 0;
  int r_std = sscanf(input, "%lo", &ul_std);
  int r_my = s21_sscanf(input, "%lo", &ul_my);
  ck_assert_int_eq(r_my, r_std);
  CK_ASSERT_ULONG_EQ(ul_std, ul_my);
}
END_TEST

// ============= Тесты длины для %x =============
START_TEST(test_s21_sscanf_hx_hex) {
  const char* input = "FFFF";  // 65535
  unsigned short us_std = 0, us_my = 0;
  int r_std = sscanf(input, "%hx", &us_std);
  int r_my = s21_sscanf(input, "%hx", &us_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(us_std, us_my);
}
END_TEST

START_TEST(test_s21_sscanf_lx_hex) {
  const char* input = "FFFFFFFF";  // 4294967295
  unsigned long ul_std = 0, ul_my = 0;
  int r_std = sscanf(input, "%lx", &ul_std);
  int r_my = s21_sscanf(input, "%lx", &ul_my);
  ck_assert_int_eq(r_my, r_std);
  CK_ASSERT_ULONG_EQ(ul_std, ul_my);
}
END_TEST

START_TEST(test_s21_sscanf_llx_hex) {
  const char* input = "FFFFFFFFFFFFFFFF";  // ULLONG_MAX
  unsigned long long ull_std = 0, ull_my = 0;
  int r_std = sscanf(input, "%llx", &ull_std);
  int r_my = s21_sscanf(input, "%llx", &ull_my);
  ck_assert_int_eq(r_my, r_std);
  CK_ASSERT_ULLONG_EQ(ull_std, ull_my);
}
END_TEST

// ============= Тесты ширины для %u =============
START_TEST(test_s21_sscanf_u_width_partial) {
  const char* input = "12345";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%3u", &u_std);
  int r_my = s21_sscanf(input, "%3u", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);  // 123
}
END_TEST

START_TEST(test_s21_sscanf_u_width_exact) {
  const char* input = "789";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%3u", &u_std);
  int r_my = s21_sscanf(input, "%3u", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);  // 789
}
END_TEST

// ============= Тесты ширины для %o =============
START_TEST(test_s21_sscanf_o_width_partial) {
  const char* input = "77777";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%3o", &u_std);
  int r_my = s21_sscanf(input, "%3o", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);  // 777₈ = 511
}
END_TEST

START_TEST(test_s21_sscanf_o_width_stop_at_invalid) {
  const char* input = "7789";  // '8' недопустим в octal
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%3o", &u_std);  // прочитает "77" (2 символа)
  int r_my = s21_sscanf(input, "%3o", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);  // 77₈ = 63
}
END_TEST

// ============= Тесты ширины для %x =============
START_TEST(test_s21_sscanf_x_width_partial) {
  const char* input = "FF00";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%2x", &u_std);
  int r_my = s21_sscanf(input, "%2x", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);  // FF₁₆ = 255
}
END_TEST

START_TEST(test_s21_sscanf_x_width_with_prefix) {
  const char* input = "0xFF00";
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%4x", &u_std);  // читает "0xFF" (4 символа)
  int r_my = s21_sscanf(input, "%4x", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);  // 0xFF = 255
}
END_TEST

START_TEST(test_s21_sscanf_x_width_stop_at_invalid) {
  const char* input = "FFG1";  // 'G' недопустим в hex
  unsigned int u_std = 0, u_my = 0;
  int r_std = sscanf(input, "%3x", &u_std);  // прочитает "FF" (2 символа)
  int r_my = s21_sscanf(input, "%3x", &u_my);
  ck_assert_int_eq(r_my, r_std);
  ck_assert_uint_eq(u_std, u_my);  // 255
}
END_TEST

Suite* s21_sscanf_x_suite(void) {
  Suite* s = suite_create("s21_sscanf_x");
  TCase* tc = tcase_create("unsigned_integers");

  // %u
  tcase_add_test(tc, test_s21_sscanf_u_basic);
  tcase_add_test(tc, test_s21_sscanf_u_with_spaces);
  tcase_add_test(tc, test_s21_sscanf_u_leading_zeros);
  tcase_add_test(tc, test_s21_sscanf_u_invalid_char);

  // %o
  tcase_add_test(tc, test_s21_sscanf_o_basic);
  tcase_add_test(tc, test_s21_sscanf_o_invalid_digit);

  // %x
  tcase_add_test(tc, test_s21_sscanf_x_no_prefix);
  tcase_add_test(tc, test_s21_sscanf_x_with_0x);
  tcase_add_test(tc, test_s21_sscanf_x_with_0X);
  tcase_add_test(tc, test_s21_sscanf_x_mixed_case);

  // length modifiers
  tcase_add_test(tc, test_s21_sscanf_hu_short);
  tcase_add_test(tc, test_s21_sscanf_lu_long);

  // suppress
  tcase_add_test(tc, test_s21_sscanf_u_suppress);

  // edge cases
  tcase_add_test(tc, test_s21_sscanf_u_no_digits);

  tcase_add_test(tc, test_s21_sscanf_ho_octal);
  tcase_add_test(tc, test_s21_sscanf_lo_octal);
  tcase_add_test(tc, test_s21_sscanf_hx_hex);
  tcase_add_test(tc, test_s21_sscanf_lx_hex);
  tcase_add_test(tc, test_s21_sscanf_llx_hex);
  tcase_add_test(tc, test_s21_sscanf_u_width_partial);
  tcase_add_test(tc, test_s21_sscanf_u_width_exact);
  tcase_add_test(tc, test_s21_sscanf_o_width_partial);
  tcase_add_test(tc, test_s21_sscanf_o_width_stop_at_invalid);
  tcase_add_test(tc, test_s21_sscanf_x_width_partial);
  tcase_add_test(tc, test_s21_sscanf_x_width_with_prefix);
  tcase_add_test(tc, test_s21_sscanf_x_width_stop_at_invalid);

  suite_add_tcase(s, tc);
  return s;
}