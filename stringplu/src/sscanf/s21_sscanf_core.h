#ifndef S21_SSCANF_CORE_H
#define S21_SSCANF_CORE_H

#include <stdarg.h>

int s21_sscanf_handle_specifier(const char** src, const char* str_start,
                                char spec, char length, int width, int assign,
                                va_list* args, int* assigned, int* error);

#endif  // S21_SSCANF_CORE_H
