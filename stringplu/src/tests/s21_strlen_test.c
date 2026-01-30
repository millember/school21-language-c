#include <check.h>
#include <stddef.h>

// Объявляем функцию локально, как требуется
extern size_t s21_strlen(const char* str);

// Тест: пустая строка
START_TEST(test_strlen_empty) {
  const char* str = "";
  ck_assert_uint_eq(s21_strlen(str), 0U);
}
END_TEST

// Тест: строка из одного символа
START_TEST(test_strlen_single_char) {
  const char* str = "a";
  ck_assert_uint_eq(s21_strlen(str), 1U);
}
END_TEST

// Тест: слово "hello"
START_TEST(test_strlen_hello) {
  const char* str = "hello";
  ck_assert_uint_eq(s21_strlen(str), 5U);
}
END_TEST

// Тест: цифровая строка
START_TEST(test_strlen_digits) {
  const char* str = "1234567890";
  ck_assert_uint_eq(s21_strlen(str), 10U);
}
END_TEST

// Функция для создания тестового набора
Suite* s21_strlen_suite(void) {
  Suite* s = suite_create("s21_strlen");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strlen_empty);
  tcase_add_test(tc_core, test_strlen_single_char);
  tcase_add_test(tc_core, test_strlen_hello);
  tcase_add_test(tc_core, test_strlen_digits);

  suite_add_tcase(s, tc_core);
  return s;
}
