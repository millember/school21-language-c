#include <check.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

// Вспомогательная функция для безопасного сравнения
static void compare_strerror(int errnum) {
  const char* std_result = strerror(errnum);
  char* my_result = s21_strerror(errnum);

  // Проверяем, что обе функции вернули не NULL
  ck_assert_ptr_nonnull(std_result);
  ck_assert_ptr_nonnull(my_result);

  // Сравниваем строки
  ck_assert_str_eq(my_result, std_result);
}

// Макрос для удобства
#define TEST_STRERROR(err)                                   \
  START_TEST(test_strerror_##err) { compare_strerror(err); } \
  END_TEST

// Тесты с известными кодами
TEST_STRERROR(0)
TEST_STRERROR(1)
TEST_STRERROR(2)
TEST_STRERROR(EINVAL)
TEST_STRERROR(ENOENT)
TEST_STRERROR(EACCES)
TEST_STRERROR(ENOMEM)
TEST_STRERROR(EBADF)
TEST_STRERROR(EEXIST)
TEST_STRERROR(ERANGE)
TEST_STRERROR(EDOM)
TEST_STRERROR(EFBIG)
TEST_STRERROR(ENOSPC)

// Тесты с граничными/нестандартными значениями
START_TEST(test_strerror_negative) { compare_strerror(-1); }
END_TEST

START_TEST(test_strerror_large_positive) { compare_strerror(9999); }
END_TEST

START_TEST(test_strerror_large_negative) { compare_strerror(-999); }
END_TEST

// Проверка консистентности (должна возвращать тот же указатель/строку)
START_TEST(test_strerror_consistency) {
  const char* std1 = strerror(5);
  const char* std2 = strerror(5);
  char* my1 = s21_strerror(5);
  char* my2 = s21_strerror(5);

  ck_assert_ptr_nonnull(std1);
  ck_assert_ptr_nonnull(my1);

  // Сравниваем содержимое
  ck_assert_str_eq(my1, std1);
  ck_assert_str_eq(my2, std2);
  ck_assert_str_eq(my1, my2);
}
END_TEST

// Тест для "верхней границы" — просто проверим, что не падает
START_TEST(test_strerror_upper_boundary) {
  // Просто вызовем — должно вернуть валидную строку
  char* my = s21_strerror(1000);
  const char* std = strerror(1000);
  ck_assert_ptr_nonnull(my);
  ck_assert_ptr_nonnull(std);
  ck_assert_str_eq(my, std);
}
END_TEST

// =============== Сборка Suite ===============
Suite* strerror_suite(void) {
  Suite* s = suite_create("s21_strerror");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strerror_0);
  tcase_add_test(tc_core, test_strerror_1);
  tcase_add_test(tc_core, test_strerror_2);
  tcase_add_test(tc_core, test_strerror_EINVAL);
  tcase_add_test(tc_core, test_strerror_ENOENT);
  tcase_add_test(tc_core, test_strerror_EACCES);
  tcase_add_test(tc_core, test_strerror_ENOMEM);
  tcase_add_test(tc_core, test_strerror_EBADF);
  tcase_add_test(tc_core, test_strerror_EEXIST);
  tcase_add_test(tc_core, test_strerror_ERANGE);
  tcase_add_test(tc_core, test_strerror_EDOM);
  tcase_add_test(tc_core, test_strerror_EFBIG);
  tcase_add_test(tc_core, test_strerror_ENOSPC);

  tcase_add_test(tc_core, test_strerror_negative);
  tcase_add_test(tc_core, test_strerror_large_positive);
  tcase_add_test(tc_core, test_strerror_large_negative);
  tcase_add_test(tc_core, test_strerror_consistency);
  tcase_add_test(tc_core, test_strerror_upper_boundary);

  suite_add_tcase(s, tc_core);
  return s;
}