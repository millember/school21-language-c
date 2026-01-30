#include "s21_string_utils.h"

#include <string.h>

#include "../s21_string.h"

void prepend_symbols(char* str, int count, char symbol) {
  int len = s21_strlen(str);

  for (int i = len; i >= 0; i--) {
    str[i + count] = str[i];
  }

  for (int i = 0; i < count; i++) {
    str[i] = symbol;
  }
}

void append_spaces(char* str, int count) {
  int len = s21_strlen(str);
  for (int i = 0; i < count; i++) {
    str[len + i] = ' ';
  }
  str[len + count] = '\0';
}

void reverse_string(char* str, int length) {
  for (int i = 0; i < length / 2; i++) {
    char temp = str[i];
    str[i] = str[length - 1 - i];
    str[length - 1 - i] = temp;
  }
}

void number_to_string(char* str, unsigned long long num, int* length) {
  *length = 0;
  if (num == 0) {
    str[0] = '0';
    *length = 1;
  } else {
    unsigned long long temp = num;
    while (temp > 0) {
      str[(*length)++] = '0' + (temp % 10);
      temp /= 10;
    }
    reverse_string(str, *length);
  }
  str[*length] = '\0';
}

void apply_precision(char* str, unsigned long long num, int precision,
                     int* length) {
  if (precision == 0 && num == 0) {
    str[0] = '\0';
    *length = 0;
  } else if (precision > *length) {
    prepend_symbols(str, precision - *length, '0');
  }
}

void apply_width(char* str, int width, flags_t flags, int precision) {
  int len = s21_strlen(str);

  if (width > len) {
    int diff = width - len;

    if (flags.minus) {
      append_spaces(str, diff);
    } else {
      int has_exp = 0;
      for (int i = 0; i < len; i++) {
        if (str[i] == 'e' || str[i] == 'E') {
          has_exp = 1;
          break;
        }
      }
      int can_zero = flags.zero && (has_exp ? 1 : (precision <= 0));

      if (can_zero) {
        int sign_pos = -1;
        if (len > 0 && (str[0] == '+' || str[0] == '-' || str[0] == ' ')) {
          sign_pos = 0;
        }

        prepend_symbols(str, diff, '0');
        if (sign_pos != -1 && diff > 0) {
          char sign = str[diff];
          for (int i = diff; i > 0; i--) str[i] = str[i - 1];
          str[0] = sign;
        }
      } else {
        prepend_symbols(str, diff, ' ');
      }
    }
  }
}

long double s21_pow10(int n) {
  long double r = 1.0L;
  int abs_n = n < 0 ? -n : n;
  for (int i = 0; i < abs_n; i++) {
    r *= 10.0L;
  }
  return n < 0 ? 1.0L / r : r;
}

void fill_float_row_string(long long num, int precision, char* str, int* len,
                           int* round) {
  *round = 0;
  if (num > 0) {
    number_to_string(str, num, len);
  } else {
    for (int i = 0; i < precision; i++) {
      str[i] = '0';
    }
    *len = precision;
  }
  str[*len] = '\0';
}

void split_float_and_fill(long double val, int precision, char* int_str,
                          char* frac_str, int* int_len, int* frac_len,
                          int* round_whole) {
  long long whole = (long long)val;
  long double fraction = val - whole;
  *round_whole = 0;

  if (precision > 0) {
    long double multiplier = s21_pow10(precision + 1);
    long long frac_part = (long long)(fraction * multiplier);
    int round = (frac_part % 10 >= 5);
    frac_part = frac_part / 10 + round;

    long long max_frac = 1;
    for (int i = 0; i < precision; i++) max_frac *= 10;

    if (frac_part >= max_frac) {
      whole += 1;
      frac_part = 0;
      *round_whole = 1;
    }

    fill_float_row_string(frac_part, precision, frac_str, frac_len, &round);
  } else if (precision == 0) {
    long double rounded = val + 0.5L;
    whole = (long long)rounded;
    *round_whole = (rounded - whole > 0.0L || whole > (long long)val);
    if (val == 0.0L) {
      whole = 0;
      *round_whole = 0;
    }
  }

  unsigned long long temp = whole < 0 ? -whole : whole;
  number_to_string(int_str, temp, int_len);
}

void get_exponent_value(long double val, int* exponent) {
  *exponent = 0;
  if (val == 0.0L) return;

  long double temp = val;
  while (temp >= 10.0L) {
    temp /= 10.0L;
    (*exponent)++;
  }
  while (temp < 1.0L && temp > 0.0L) {
    temp *= 10.0L;
    (*exponent)--;
  }
}

void format_exponential(long double val, int precision, char spec, char* result,
                        int* result_len) {
  int exponent = 0;
  get_exponent_value(val, &exponent);
  long double normalized = val;
  if (exponent != 0) normalized = val / s21_pow10(exponent);

  if (precision == 0) {
    normalized = (long long)(normalized + 0.5L);
    char int_str[50];
    int int_len = 0;
    number_to_string(int_str, (unsigned long long)normalized, &int_len);
    s21_strncpy(result, int_str, int_len);
    *result_len = int_len;
  } else {
    int round_occurred = 0;
    format_normalized_float(normalized, precision, result, result_len, 1,
                            &round_occurred);
    if (round_occurred && result[0] == '1' && *result_len == 1) exponent++;
  }

  char exp_char = (spec == 'E' || spec == 'G') ? 'E' : 'e';
  append_exponent(result, result_len, exponent, exp_char);
  result[*result_len] = '\0';
}

void remove_trailing_zeros_g(char* str) {
  int len = s21_strlen(str);
  int dot = -1, e_pos = -1;

  for (int i = 0; i < len; i++) {
    if (str[i] == '.') dot = i;
    if (str[i] == 'e' || str[i] == 'E') e_pos = i;
  }
  if (dot == -1) return;
  int mant_end = (e_pos != -1) ? e_pos : len;
  int last = mant_end - 1;

  while (last > dot && str[last] == '0') {
    last--;
  }

  if (last == dot) {
    if (e_pos != -1) {
      for (int i = dot; i < e_pos; i++) {
        str[i] = str[i + 1];
      }
      int exp_len = len - e_pos;
      for (int i = 0; i < exp_len; i++) {
        str[last + i] = str[e_pos + i];
      }
      str[last + exp_len] = '\0';
    } else {
      str[dot] = '\0';
    }
  } else {
    int new_end = last + 1;
    if (e_pos != -1) {
      int exp_len = len - e_pos;
      for (int i = 0; i < exp_len; i++) {
        str[new_end + i] = str[e_pos + i];
      }
      str[new_end + exp_len] = '\0';
    } else {
      str[new_end] = '\0';
    }
  }
}

void handle_g_format(long double val, int* p, char s, int sharp, char* str,
                     int* len) {
  int exp = 0;
  int orig_p = (*p == -1) ? 6 : *p;
  int use_p = (orig_p == 0) ? 1 : orig_p;
  get_exponent_value(val, &exp);

  int use_e = (exp < -4 || exp >= use_p);
  int eff_p = 0;

  if (use_e) {
    eff_p = (use_p > 0) ? (use_p - 1) : 0;
    if (eff_p < 0) eff_p = 0;
    char eff_s = (s == 'G') ? 'E' : 'e';
    format_exponential(val, eff_p, eff_s, str, len);
  } else {
    eff_p = use_p - 1 - exp;
    if (eff_p < 0) eff_p = 0;
    format_fixed_point(val, eff_p, sharp, str, len);
  }

  if (!sharp) {
    remove_trailing_zeros_g(str);
    *len = s21_strlen(str);
  }

  if (s == 'G') {
    for (int i = 0; i < *len; i++) {
      if (str[i] == 'e') str[i] = 'E';
    }
  }

  *p = eff_p;
}

void format_fixed_point(long double val, int precision, int sharp, char* result,
                        int* result_len) {
  int round_occurred = 0;
  int always_add_dot = (sharp && precision == 0);

  format_normalized_float(val, precision, result, result_len, always_add_dot,
                          &round_occurred);

  if (round_occurred && *result_len == 1 && result[0] == '0') {
    result[0] = '1';
  }
}

void format_normalized_float(long double val, int precision, char* result,
                             int* result_len, int always_add_dot,
                             int* round_occurred) {
  char int_str[50], frac_str[50];
  int i_len = 0, f_len = 0, round_whole;

  split_float_and_fill(val, precision, int_str, frac_str, &i_len, &f_len,
                       &round_whole);

  *round_occurred = round_whole;

  s21_strncpy(result, int_str, i_len);
  result[i_len] = '\0';
  *result_len = i_len;

  if (round_whole) {
    if (i_len == 1 && int_str[0] == '0') {
      result[0] = '1';
      *result_len = 1;
    } else if (i_len > 0) {
      int all_nines = 1;
      for (int i = 0; i < i_len; i++) {
        if (int_str[i] != '9') all_nines = 0;
      }
      if (all_nines) {
        result[0] = '1';
        for (int i = 1; i <= i_len; i++) result[i] = '0';
        *result_len = i_len + 1;
        result[*result_len] = '\0';
      }
    }
  }

  if (always_add_dot || (precision > 0 && f_len > 0)) {
    result[(*result_len)++] = '.';
    if (f_len > 0) {
      s21_strncpy(result + *result_len, frac_str, f_len);
      *result_len += f_len;
    } else if (precision > 0) {
      for (int i = 0; i < precision; i++) {
        result[(*result_len)++] = '0';
      }
    }
  }

  result[*result_len] = '\0';
}

void append_exponent(char* str, int* len, int exponent, char exp_char) {
  char exp_str[5];
  int exp_len = 0;

  str[(*len)++] = exp_char;
  str[(*len)++] = exponent >= 0 ? '+' : '-';

  int abs_exp = exponent < 0 ? -exponent : exponent;
  if (abs_exp < 10) {
    exp_str[0] = '0';
    exp_str[1] = abs_exp + '0';
    exp_len = 2;
  } else {
    number_to_string(exp_str, abs_exp, &exp_len);
  }

  for (int i = 0; i < exp_len; i++) {
    str[(*len)++] = exp_str[i];
  }
}

void apply_sign(char* str, int is_negative, flags_t flags) {
  int len = s21_strlen(str);

  if (len == 0) return;

  int has_sign = (str[0] == '+' || str[0] == '-' || str[0] == ' ');

  if (!has_sign) {
    if (is_negative) {
      prepend_symbols(str, 1, '-');
    } else if (flags.plus) {
      prepend_symbols(str, 1, '+');
    } else if (flags.space) {
      prepend_symbols(str, 1, ' ');
    }
  }
}