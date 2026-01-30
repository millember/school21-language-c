#include "s21_decimal.h"

int s21_is_less(s21_decimal decim_1, s21_decimal decim_2) {
  int flag = 0;
  int sign_1 = get_sign(decim_1);
  int sign_2 = get_sign(decim_2);
  
  // Если числа равны (включая -0 == 0), то не меньше
  if (s21_is_equal(decim_1, decim_2)) {
    return 0;
  }
  
  // Теперь точно знаем, что числа не равны
  
  if (sign_1 != sign_2) {
    // Если знаки разные
    flag = (sign_1 == 1);  // Отрицательное меньше положительного
  } else {
    // Если знаки одинаковые
    int compare_result = compare_absolute_values(decim_1, decim_2);
    
    if (sign_1 == 0) { // оба положительные
      flag = (compare_result == 1);
    } else { // оба отрицательные
      flag = (compare_result == 2);
    }
  }
  
  return flag;
}
int s21_is_equal(s21_decimal decim_1, s21_decimal decim_2) {
  int flag = 0;

  // Проверяем, являются ли оба числа нулями (независимо от знака)
  if (is_zero_decimal(&decim_1) && is_zero_decimal(&decim_2)) {
    flag = 1;
  } else {
    // Если не нули, то сравниваем знаки и абсолютные значения
    if (get_sign(decim_1) != get_sign(decim_2)) {
      flag = 0;
    } else {
      flag = (compare_absolute_values(decim_1, decim_2) == 0);
    }
  }

  return flag;
}

int s21_is_less_or_equal(s21_decimal decim_1, s21_decimal decim_2) {
  return (s21_is_less(decim_1, decim_2)) || (s21_is_equal(decim_1, decim_2));
}

int s21_is_greater(s21_decimal decim_1, s21_decimal decim_2) {
  return s21_is_less(decim_2, decim_1);
}

int s21_is_greater_or_equal(s21_decimal decim_1, s21_decimal decim_2) {
  return (!(s21_is_less(decim_1, decim_2))) || (s21_is_equal(decim_1, decim_2));
}

int s21_is_not_equal(s21_decimal decim_1, s21_decimal decim_2) {
  return !s21_is_equal(decim_1, decim_2);
}