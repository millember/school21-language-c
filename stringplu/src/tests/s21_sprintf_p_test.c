#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

// ---------------------------
//  ПРОТОТИПЫ ФУНКЦИЙ
// ---------------------------

static void assert_p_format(const char* out, const char* ref);
static void assert_zero_padding(const char* out, const char* ref);
static void run_test_p(const char* fmt, void* ptr, int check_zero_pad);

Suite* suite_s21_p(void);
int main(void);

// ---------------------------
//  ТЕСТЫ
// ---------------------------

START_TEST(test_p_var) {
  int var = 123;
  run_test_p("%p", &var, 0);
}
END_TEST

START_TEST(test_p_null) { run_test_p("%p", NULL, 0); }
END_TEST

START_TEST(test_p_width) {
  int v = 42;
  run_test_p("%15p", &v, 0);
}
END_TEST

START_TEST(test_p_minus) {
  int v = 42;
  run_test_p("%-15p", &v, 0);
}
END_TEST

START_TEST(test_p_zero) {
  int v = 42;
  run_test_p("%015p", &v, 1);
}
END_TEST

Suite* suite_s21_p(void) {
  Suite* s = suite_create("s21_sprintf_%p");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_p_var);
  tcase_add_test(tc, test_p_null);
  tcase_add_test(tc, test_p_width);
  tcase_add_test(tc, test_p_minus);
  tcase_add_test(tc, test_p_zero);

  suite_add_tcase(s, tc);
  return s;
}

// ---------------------------
//  РЕАЛИЗАЦИИ ФУНКЦИЙ
// ---------------------------

// формат: длина, позиция 0x, совпадение хвоста
static void assert_p_format(const char* out, const char* ref) {
  ck_assert_int_eq(strlen(out), strlen(ref));

  const char* pos_out = strstr(out, "0x");
  const char* pos_ref = strstr(ref, "0x");

  ck_assert(pos_out != NULL);
  ck_assert(pos_ref != NULL);

  int pad_out = (int)(pos_out - out);
  int pad_ref = (int)(pos_ref - ref);
  ck_assert_int_eq(pad_out, pad_ref);

  ck_assert_str_eq(pos_out, pos_ref);
}

// нули должны идти ПОСЛЕ "0x"
static void assert_zero_padding(const char* out, const char* ref) {
  const char* pos_out = strstr(out, "0x");
  const char* pos_ref = strstr(ref, "0x");

  int i = 2;
  while (pos_ref[i] == '0') {
    ck_assert_msg(pos_out[i] == '0', "Ожидался ноль после '0x' в позиции %d",
                  i);
    i++;
  }
}

// универсальный тест s21_sprintf
static void run_test_p(const char* fmt, void* ptr, int check_zero_pad) {
  char out[256] = {0};
  char ref[256] = {0};

  int r1 = s21_sprintf(out, fmt, ptr);
  int r2 = sprintf(ref, fmt, ptr);

  // --- ДИАГНОСТИКА ---
  printf("OUT = '%s'\n", out);
  printf("REF = '%s'\n", ref);
  // --------------------

  ck_assert_int_eq(r1, r2);
  assert_p_format(out, ref);

  if (check_zero_pad == 1) {
    assert_zero_padding(out, ref);
  }
}
