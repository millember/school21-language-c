#include "s21_decimal.h"

// для обычного децимала

// Обнуление всех битов децимала
void clean_decimal(s21_decimal *decimal) {
  decimal->bits[0] = decimal->bits[1] = decimal->bits[2] = decimal->bits[3] = 0;
}

// Проверка на ноль децимала
int is_zero_decimal(s21_decimal *decimal) {
  return (decimal->bits[0] == 0 && decimal->bits[1] == 0 &&
          decimal->bits[2] == 0);
}

// Получение бита по индексу
int get_bit_decimal(s21_decimal decimal, int idx) {
  int bit_int = idx / 32;
  int bit = idx % 32;
  return (decimal.bits[bit_int] >> bit) & 1;
}

// установка бита по индексу
void set_bit_decimal(s21_decimal *decimal, int idx, int bit_value) {
  int bit_int = idx / 32;
  int bit = idx % 32;
  if (bit_value) {
    decimal->bits[bit_int] |= (1u << bit);  // Установить бит в 1
  } else {
    decimal->bits[bit_int] &= ~(1u << bit);  // Установить бит в 0
  }
}

// Получение знака
int get_sign(s21_decimal decimal) { return (decimal.bits[3] >> 31) & 1; }

// Установка знака
void set_sign(s21_decimal *decimal, int sign) {
  if (sign)
    decimal->bits[3] |= (1u << 31);
  else
    decimal->bits[3] &= ~(1u << 31);
}

// Получение степени
int get_scale(s21_decimal decimal) { return (decimal.bits[3] >> 16) & 0xFF; }

// Установка степени
void set_scale(s21_decimal *decimal, int scale) {
  decimal->bits[3] &= ~(0xFF << 16);
  decimal->bits[3] |= (scale << 16);
}

void decimal_to_big_decimal(s21_decimal decimal, s21_big_decimal *big_decimal) {
  clean_big_decimal(big_decimal);
  big_decimal->bits[0] = decimal.bits[0];
  big_decimal->bits[1] = decimal.bits[1];
  big_decimal->bits[2] = decimal.bits[2];
  big_decimal->bits[6] = decimal.bits[3];
}
void big_decimal_to_decimal(s21_big_decimal big_decimal, s21_decimal *decimal) {
  clean_decimal(decimal);
  decimal->bits[0] = big_decimal.bits[0];
  decimal->bits[1] = big_decimal.bits[1];
  decimal->bits[2] = big_decimal.bits[2];
  decimal->bits[3] = big_decimal.bits[6];
}

int is_decimal_correct(s21_decimal decimal) {
  int flag = 1;
  int scale = get_scale(decimal);
  if (scale > 28 || scale < 0) flag = 0;
  s21_decimal_bit3 bit_3;
  bit_3.bit = decimal.bits[3];
  if (bit_3.parts.zero_bit1 != 0 || bit_3.parts.zero_bit2 != 0) flag = 0;
  return flag;
}

void plus_one(s21_decimal *decimal) {
  int flag = 0;
  for (int i = 0; i < MANTISS_BITS && !flag; i++) {
    if (get_bit_decimal(*decimal, i) == 0) {
      set_bit_decimal(decimal, i, 1);
      flag = 1;
    } else
      set_bit_decimal(decimal, i, 0);
  }
}

int bit_not_zero(s21_decimal decimal) {
  int flag = -1;
  for (int i = 2; i >= 0 && flag == -1; i--) {
    if (decimal.bits[i] != 0) flag = i;
  }
  return flag;
}

int div_on_ten(s21_decimal *decimal, int scale) {
  unsigned long long current_value;
  int j = 0, remainder = 0, fractional_part = 0;
  for (int i = 0; i < scale; i++) {
    j = bit_not_zero(*decimal);
    current_value = decimal->bits[j];
    for (; j >= 0; j--) {
      if (j == 0) {
        decimal->bits[j] = current_value / 10;
        remainder = current_value % 10;
      } else {
        remainder = current_value % 10;
        decimal->bits[j] = current_value / 10;
        current_value = remainder * (MAX_32bit) + decimal->bits[j - 1];
      }
      if (remainder != 0) fractional_part = 10;
    }
  }
  decimal->bits[3] = 0;
  return remainder + fractional_part;
}

int apply_rounding_operation(s21_decimal value, s21_decimal *result) {
  int scale = get_scale(value);

  if (scale != 0) {
    int sign = get_sign(value);
    s21_decimal buf = {0};
    buf = value;
    int remainder = 0;
    remainder = div_on_ten(&buf, scale);

    *result = buf;
    if (sign) {
      set_sign(result, 1);
    }
    return remainder;
  } else {
    *result = value;
    return 0;
  }
}

int compare_absolute_values(s21_decimal decim_1, s21_decimal decim_2) {
  s21_big_decimal big1, big2;
  decimal_to_big_decimal(decim_1, &big1);
  decimal_to_big_decimal(decim_2, &big2);

  int scale1 = get_scale(decim_1);
  int scale2 = get_scale(decim_2);

  // Выравниваем scale, умножая на 10 число с меньшим scale
  if (scale1 < scale2) {
    int diff = scale2 - scale1;
    for (int i = 0; i < diff; i++) {
      increase_scale_big(&big1);
    }
  } else if (scale2 < scale1) {
    int diff = scale1 - scale2;
    for (int i = 0; i < diff; i++) {
      increase_scale_big(&big2);
    }
  }

  // Сравниваем big_decimal
  if (is_big_decimal_greater(big1, big2)) {
    return 2;  // |decim_1| > |decim_2|
  } else if (is_big_decimal_greater(big2, big1)) {
    return 1;  // |decim_1| < |decim_2|
  } else {
    return 0;  // равны
  }
}

// для большого децимала

void clean_big_decimal(s21_big_decimal *big_decimal) {
  for (int i = 0; i < 7; i++) {
    big_decimal->bits[i] = 0;
  }
}

int is_zero_big_decimal(s21_big_decimal *big_decimal) {
  return (big_decimal->bits[3] == 0 && big_decimal->bits[4] == 0 &&
          big_decimal->bits[5] == 0);
}
void normalize_scales(s21_big_decimal *big_decimal_1,
                      s21_big_decimal *big_decimal_2) {
  int pow_1 = get_scale_big(*big_decimal_1);
  int pow_2 = get_scale_big(*big_decimal_2);
  int diff = pow_1 - pow_2;

  if (diff > 0) {
    for (int i = 0; i < diff; i++) {
      increase_scale_big(big_decimal_2);
    }
    // Обновляем scale у big_decimal_2
    s21_decimal_bit3 bit3;
    bit3.bit = big_decimal_2->bits[6];
    bit3.parts.power_bit = pow_1;
    big_decimal_2->bits[6] = bit3.bit;
  } else if (diff < 0) {
    for (int i = 0; i < -diff; i++) {
      increase_scale_big(big_decimal_1);
    }
    // Обновляем scale у big_decimal_1
    s21_decimal_bit3 bit3;
    bit3.bit = big_decimal_1->bits[6];
    bit3.parts.power_bit = pow_2;
    big_decimal_1->bits[6] = bit3.bit;
  }
}

int get_bit_big_decimal(s21_big_decimal big_decimal, int idx) {
  int bit_int = idx / 32;
  int bit = idx % 32;
  return (big_decimal.bits[bit_int] >> bit) & 1;
}
void set_bit_big_decimal(s21_big_decimal *big_decimal, int idx, int bit_value) {
  int bit_int = idx / 32;
  int bit = idx % 32;
  if (bit_value) {
    big_decimal->bits[bit_int] |= (1u << bit);  // Установить бит в 1
  } else {
    big_decimal->bits[bit_int] &= ~(1u << bit);  // Установить бит в 0
  }
}

int shift_big_left(s21_big_decimal *big_decimal, int step) {
  int flag = 0, buf[7] = {0};
  for (int k = 0; k < step; k++) {
    for (int i = 0; i < 6; i++) {
      buf[i] = get_bit_big_decimal(*big_decimal, (i + 1) * BLOCK_BITS - 1);
    }
    for (int i = 6; i > 0 && !flag; i--) {
      if (get_bit_big_decimal(*big_decimal, BIG_BITS - 1)) flag = 1;
      big_decimal->bits[i] <<= 1;
      set_bit_big_decimal(big_decimal, i * BLOCK_BITS, buf[i - 1]);
    }
    big_decimal->bits[0] <<= 1;
  }
  return flag;
}
void shift_big_right(s21_big_decimal *big_decimal, int step) {
  int buf[7] = {0};
  for (int k = 0; k < step; k++) {
    for (int i = 0; i < 6; i++) {
      buf[i] = get_bit_big_decimal(*big_decimal, (i + 1) * BLOCK_BITS);
    }
    for (int i = 0; i < 6; i++) {
      big_decimal->bits[i] >>= 1;
      set_bit_big_decimal(big_decimal, (i + 1) * BLOCK_BITS - 1, buf[i]);
    }
    big_decimal->bits[6] >>= 1;
  }
}

void normalize_big_to_decimal(s21_big_decimal *big_decimal, int *temp_scale,
                              s21_decimal *result) {
  int sign = (*big_decimal).bits[6] >> 31;
  int should_round = 0;

  while (*temp_scale > 28) {
    div_on_ten_big(big_decimal);
    (*temp_scale)--;
  }

  int last_remainder = 0;
  while (!can_big_decimal_fit_in_decimal(*big_decimal) && *temp_scale > 0) {
    last_remainder = div_on_ten_big_with_remainder(big_decimal);
    (*temp_scale)--;
  }

  if (last_remainder > 0) {
    should_round = 0;

    if (last_remainder > 5) {
      should_round = 1;
    } else if (last_remainder == 5) {
      if (get_bit_big_decimal(*big_decimal, 0)) {
        should_round = 1;
      }
    }

    if (should_round) {
      s21_big_decimal one = {{1, 0, 0, 0, 0, 0, 0}};
      add_big_decimal(*big_decimal, one, big_decimal);

      if (!can_big_decimal_fit_in_decimal(*big_decimal)) {
        sub_big_decimal(*big_decimal, one, big_decimal);
      }
    }
  }

  if (can_big_decimal_fit_in_decimal(*big_decimal) && *temp_scale >= 0 &&
      *temp_scale <= 28) {
    big_decimal_to_decimal(*big_decimal, result);
    set_scale(result, *temp_scale);
    if (sign) {
      set_sign(result, 1);
    }
  }
}

int can_big_decimal_fit_in_decimal(s21_big_decimal big) {
  // Проверяем, что биты с 96 по 191 равны 0
  // bits[3], bits[4], bits[5] должны быть 0
  return (big.bits[3] == 0 && big.bits[4] == 0 && big.bits[5] == 0);
}

void find_highest_bits(s21_big_decimal big_decimal_1,
                       s21_big_decimal big_decimal_2, int *bit_1, int *bit_2) {
  for (int i = BIG_MANTISS_BITS - 1; i >= 0 && (!(*bit_1) || !(*bit_2)); i--) {
    if (*bit_1 == 0 && get_bit_big_decimal(big_decimal_1, i)) *bit_1 = i;
    if (*bit_2 == 0 && get_bit_big_decimal(big_decimal_2, i)) *bit_2 = i;
  }
}

int get_scale_big(s21_big_decimal big_decimal) {
  s21_decimal_bit3 buf;
  buf.bit = big_decimal.bits[6];
  int scale = buf.parts.power_bit;
  return scale;
}

void shift_mantissa_left_big(s21_big_decimal *big_decimal, unsigned int steps) {
  for (unsigned int s = 0; s < steps; s++) {
    for (int i = 191; i >= 0; i--) {
      int temp_bit = 0;
      if (i > 0) temp_bit = get_bit_big_decimal(*big_decimal, i - 1);
      set_bit_big_decimal(big_decimal, i, temp_bit);
    }
  }
}

void increase_scale_big(s21_big_decimal *big_decimal) {
  s21_big_decimal temp = {0};
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};

  mul_big_decimal(*big_decimal, ten, &temp);

  // Копируем результат
  for (int i = 0; i < 7; i++) {
    big_decimal->bits[i] = temp.bits[i];
  }

  // Увеличиваем scale в bits[6]
  s21_decimal_bit3 bit3;
  bit3.bit = big_decimal->bits[6];
  bit3.parts.power_bit++;
  big_decimal->bits[6] = bit3.bit;
}

void div_on_ten_big(s21_big_decimal *big_decimal) {
  unsigned long long carry = 0;
  for (int i = 5; i >= 0; --i) {
    unsigned long long current = (carry << 32) + big_decimal->bits[i];
    big_decimal->bits[i] = current / 10;
    carry = current % 10;
  }
}

int is_big_decimal_greater(s21_big_decimal big_decimal_1,
                           s21_big_decimal big_decimal_2) {
  int flag = 0;
  int out = 0;

  // Сравниваем только биты 0-5 (мантисса), bits[6] содержит scale и знак
  for (int i = 5; i >= 0 && !flag && !out; i--) {
    if (big_decimal_1.bits[i] != big_decimal_2.bits[i]) {
      out = 1;  // числа точно не равны
      if (big_decimal_1.bits[i] > big_decimal_2.bits[i]) {
        flag = 1;  // первое число больше
      }
    }
  }

  return flag;
}

// Добавьте эту функцию для правильного увеличения scal

// Получение знака из big_decimal
int get_sign_from_big(s21_big_decimal big) { return (big.bits[6] >> 31) & 1; }

// Деление big_decimal на 10 с сохранением остатка
int div_on_ten_big_with_remainder(s21_big_decimal *big_decimal) {
  unsigned long long carry = 0;
  unsigned long long current;
  int remainder = 0;

  // Обрабатываем только мантиссу (биты 0-5)
  for (int i = 5; i >= 0; --i) {
    current = (carry << 32) + big_decimal->bits[i];
    big_decimal->bits[i] = (unsigned int)(current / 10);
    carry = current % 10;
  }

  remainder = (int)carry;
  return remainder;
}

// Банковское округление для decimal
void bank_round_decimal(s21_decimal *value, int remainder) {
  if (remainder > 5 || (remainder == 5 && (value->bits[0] & 1))) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_add(*value, one, value);
  }
}

int compare_big_decimals(s21_big_decimal b1, s21_big_decimal b2) {
  int result = 0;

  for (int i = 5; i >= 0 && result == 0; i--) {
    if (b1.bits[i] > b2.bits[i]) {
      result = 1;
    } else if (b1.bits[i] < b2.bits[i]) {
      result = -1;
    }
  }

  return result;
}

void prepare_big_decimals(s21_decimal d1, s21_decimal d2, s21_big_decimal *b1,
                          s21_big_decimal *b2, int *scale1, int *scale2,
                          int *max_scale) {
  decimal_to_big_decimal(d1, b1);
  decimal_to_big_decimal(d2, b2);
  *scale1 = get_scale(d1);
  *scale2 = get_scale(d2);
  *max_scale = (*scale1 > *scale2) ? *scale1 : *scale2;
}

void align_scales(s21_big_decimal *v1, s21_big_decimal *v2, int scale1,
                  int scale2, int max_scale) {
  if (scale1 < max_scale) {
    int diff = max_scale - scale1;
    for (int i = 0; i < diff; i++) {
      increase_scale_big(v1);
    }
  }
  if (scale2 < max_scale) {
    int diff = max_scale - scale2;
    for (int i = 0; i < diff; i++) {
      increase_scale_big(v2);
    }
  }
}

int process_big_decimal_result(s21_big_decimal r, int max_scale, int final_sign,
                               s21_decimal *result) {
  int error = OK;

  if (max_scale <= 28 && can_big_decimal_fit_in_decimal(r)) {
    big_decimal_to_decimal(r, result);
    set_scale(result, max_scale);
    if (final_sign) set_sign(result, 1);
  } else {
    while (max_scale > 0 && !can_big_decimal_fit_in_decimal(r)) {
      div_on_ten_big(&r);
      max_scale--;
    }

    if (max_scale >= 0 && can_big_decimal_fit_in_decimal(r)) {
      big_decimal_to_decimal(r, result);
      set_scale(result, max_scale);
      if (final_sign) set_sign(result, 1);
    } else {
      error = (final_sign) ? UNINF_OR_LESSINF : INF_OR_BIGGERINF;
    }
  }

  return error;
}