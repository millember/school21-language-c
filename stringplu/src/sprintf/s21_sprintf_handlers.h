#ifndef S21_SPRINTF_HANDLERS_H
#define S21_SPRINTF_HANDLERS_H
#include "../s21_string.h"
#include "s21_sprintf_types.h"
#include "s21_string_utils.h"

int s21_handle_c(char* buf, char c, flags_t flags, int width, int precision);
int s21_handle_d(char* buf, long val, flags_t flags, int width, int prec);
int s21_handle_f(char* buf, long double val, char spec, flags_t flags,
                 int width, int precision);
int s21_handle_s(char* buf, const char* str, flags_t flags, int width,
                 int precision);
int s21_handle_u(char* buf, unsigned long val, flags_t flags, int width,
                 int precision);
int s21_handle_percent(char* buf, flags_t flags, int width);
int s21_handle_x(char* buf, unsigned long val, char spec, flags_t flags,
                 int width, int precision);
int s21_handle_o(char* buf, unsigned long val, char spec, flags_t flags,
                 int width, int precision);
int s21_handle_p(char* buf, void* ptr, flags_t flags, int width);

#endif
