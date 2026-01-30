#ifndef S21_STRING_UTILS_H
#define S21_STRING_UTILS_H

#include "s21_sprintf_types.h"

void prepend_symbols(char* str, int count, char symbol);
void append_spaces(char* str, int count);
void reverse_string(char* str, int length);
void number_to_string(char* str, unsigned long long num, int* length);
void apply_precision(char* str, unsigned long long num, int precision,
                     int* length);
void apply_sign(char* str, int is_negative, flags_t flags);
void apply_width(char* str, int width, flags_t flags, int precision);
void fill_float_row_string(long long num, int precision, char* str, int* len,
                           int* round);
void split_float_and_fill(long double val, int precision, char* int_str,
                          char* frac_str, int* int_len, int* frac_len,
                          int* round_whole);
void get_exponent_value(long double val, int* exponent);
void format_exponential(long double val, int precision, char spec, char* result,
                        int* result_len);
long double s21_pow10(int n);
void remove_trailing_zeros_g(char* str);
void handle_g_format(long double val, int* precision, char spec, int sharp,
                     char* str, int* length);
void format_fixed_point(long double val, int precision, int sharp, char* result,
                        int* result_len);
void format_normalized_float(long double val, int precision, char* result,
                             int* result_len, int always_add_dot,
                             int* round_occurred);
void append_exponent(char* str, int* len, int exponent, char exp_char);
#endif