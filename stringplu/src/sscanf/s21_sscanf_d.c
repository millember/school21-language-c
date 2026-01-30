#include <ctype.h>

#include "../s21_string.h"

int parse_base_digit(char ch, int base) {
  unsigned char uch = (unsigned char)ch;
  int digit = -1;

  if (uch >= '0' && uch <= '9') {
    digit = uch - '0';
  } else if (base == 16) {
    if (uch >= 'a' && uch <= 'f') {
      digit = uch - 'a' + 10;
    } else if (uch >= 'A' && uch <= 'F') {
      digit = uch - 'A' + 10;
    }
  }

  if (digit >= base) digit = -1;

  return digit;
}

int s21_sscanf_d(const char** str, void* out, char spec, int width, int assign,
                 char length) {
  const char* p = *str;
  int sign = 1;
  int base = 10;
  int chars_read = 0;
  int digits_read = 0;
  long long value = 0;
  int hex_prefix =
      0;  // флаг, что был префикс "0x" для шестнадцатеричной системы

  // Пропуск пробелов
  while (*p && isspace((unsigned char)*p)) p++;

  // Обработка знака
  if ((width <= 0 || chars_read < width) && (*p == '-' || *p == '+')) {
    if (*p == '-') sign = -1;
    p++;
    chars_read++;  // ← учитываем знак в ширине
    digits_read++;
  }

  // Определение системы счисления для спецификатора 'i'
  if (spec == 'i') {
    if (*p == '0') {
      if (*(p + 1) == 'x' || *(p + 1) == 'X') {
        base = 16;
        hex_prefix = 1;
        p += 2;  // Пропускаем "0x" или "0X"
      } else {
        base = 8;
        // Не пропускаем '0', он будет считан как первая цифра
      }
    } else {
      base = 10;
    }
  }

  int digit = parse_base_digit(*p, base);
  while ((width <= 0 || chars_read < width) && *p && digit != -1) {
    value = value * base + digit;
    digits_read++;
    p++;
    chars_read++;
    digit = parse_base_digit(*p, base);  // ← предзагрузка следующего символа
  }

  // Если для шестнадцатеричной системы был префикс, но не было цифр, то число
  // равно 0
  if (hex_prefix && digits_read == 0) {
    digits_read = 1;  // Условно считаем, что прочитали одну цифру
    value = 0;
  }

  int return_res = 0;
  // Если не прочитано ни одной цифры, то возвращаем 0 (неудачное чтение)
  if (digits_read != 0) {
    value *= sign;

    // Запись результата, если не подавлено
    if (assign && out != S21_NULL) {
      if (length == 'h') {
        *(short*)out = (short)value;
      } else if (length == 'l') {
        *(long*)out = (long)value;
      } else if (length == 'L') {
        *(long long*)out = value;
      } else {
        *(int*)out = (int)value;
      }
    }

    // Обновление указателя на строку
    *str = p;
    return_res = (digits_read && assign);
  }
  // Возвращаем 1, если были прочитаны цифры и не подавлено, иначе 0
  return return_res;
}