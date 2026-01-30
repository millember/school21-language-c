#ifndef S21_SPRINTF_CORE_H
#define S21_SPRINTF_CORE_H

#include <stdarg.h>

#include "../s21_string.h"
#include "s21_sprintf_types.h"

int handle_specifier(char* buffer, s21_size buf_offset, const char** fmt,
                     va_list* args, int* written_len);

#endif  // S21_SPRINTF_CORE_H
