#include "s21_sprintf_core.h"

#include "s21_sprintf_handlers.h"

static void parse_flags(const char** format, flags_t* flags);
static int parse_width(const char** format, va_list* args);
static int parse_precision(const char** format, va_list* args);
static void parse_length(const char** format, char* length);

int handle_specifier(char* buffer, s21_size buf_offset, const char** fmt,
                     va_list* args, int* written_len) {
  int result = 0;
  int handled = 0;
  int written = 0;

  (*fmt)++;

  flags_t flags = {0};
  parse_flags(fmt, &flags);

  int width = parse_width(fmt, args);
  // Обработка отрицательной ширины
  if (width < 0) {
    flags.minus = 1;
    width = -width;
  }

  int precision = -1;
  if (**fmt == '.') {
    (*fmt)++;
    precision = parse_precision(fmt, args);
  }

  char length[3] = {0};
  parse_length(fmt, length);

  char spec = **fmt ? *((*fmt)++) : '\0';

  switch (spec) {
    case 'c': {
      char ch = (char)va_arg(*args, int);
      written = s21_handle_c(buffer ? &buffer[buf_offset] : S21_NULL, ch, flags,
                             width, precision);
      handled = 1;
      break;
    }

    case 'd':
    case 'i': {
      long val = 0;
      switch (length[0]) {
        case 'h':
          val = (short)va_arg(*args, int);
          break;
        case 'l':
          val = va_arg(*args, long);
          break;
        default:
          val = va_arg(*args, int);
          break;
      }
      written = s21_handle_d(buffer ? &buffer[buf_offset] : S21_NULL, val,
                             flags, width, precision);
      handled = 1;
      break;
    }

    case 'n': {
      int* pos_ptr = va_arg(*args, int*);
      if (pos_ptr) {
        *pos_ptr = (int)buf_offset;
      }
      handled = 1;
      written = 0;
      break;
    }

    case 'u': {
      unsigned long val = 0;
      switch (length[0]) {
        case 'h':
          val = (unsigned short)va_arg(*args, unsigned int);
          break;
        case 'l':
          val = va_arg(*args, unsigned long);
          break;
        default:
          val = va_arg(*args, unsigned int);
          break;
      }
      written = s21_handle_u(buffer ? &buffer[buf_offset] : S21_NULL, val,
                             flags, width, precision);
      handled = 1;
      break;
    }

    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G': {
      long double val = 0;
      switch (length[0]) {
        case 'L':
          val = va_arg(*args, long double);
          break;
        default:
          val = (long double)va_arg(*args, double);
          break;
      }
      written = s21_handle_f(buffer ? &buffer[buf_offset] : S21_NULL, val, spec,
                             flags, width, precision);
      handled = 1;
      break;
    }

    case 's': {
      const char* str_arg = va_arg(*args, const char*);
      written = s21_handle_s(buffer ? &buffer[buf_offset] : S21_NULL, str_arg,
                             flags, width, precision);
      handled = 1;
      break;
    }

    case '%': {
      written = s21_handle_percent(buffer ? &buffer[buf_offset] : S21_NULL,
                                   flags, width);
      handled = 1;
      break;
    }

    case 'x':
    case 'X':
    case 'o': {
      unsigned long val = 0;
      switch (length[0]) {
        case 'h':
          val = (unsigned short)va_arg(*args, unsigned int);
          break;
        case 'l':
          val = va_arg(*args, unsigned long);
          break;
        default:
          val = va_arg(*args, unsigned int);
          break;
      }

      if (spec == 'o') {
        written = s21_handle_o(buffer ? &buffer[buf_offset] : S21_NULL, val,
                               spec, flags, width, precision);
      } else {
        written = s21_handle_x(buffer ? &buffer[buf_offset] : S21_NULL, val,
                               spec, flags, width, precision);
      }
      handled = 1;
      break;
    }

    case 'p': {
      void* ptr = va_arg(*args, void*);
      written = s21_handle_p(buffer ? &buffer[buf_offset] : S21_NULL, ptr,
                             flags, width);
      handled = 1;
      break;
    }
  }

  if (!handled) {
    if (buffer) buffer[buf_offset] = '%';  // копируем как есть
    buf_offset++;

    if (spec) {
      if (buffer) buffer[buf_offset] = spec;
      buf_offset++;
    }

    *written_len = 2;
  } else {
    if (written < 0) {
      result = -1;
    } else {
      *written_len = written;
    }
  }

  return result;
}

// Вспомогательные парсеры:
static void parse_flags(const char** format, flags_t* flags) {
  while (**format) {
    switch (**format) {
      case '-':
        flags->minus = 1;
        (*format)++;
        break;
      case '+':
        flags->plus = 1;
        (*format)++;
        break;
      case ' ':
        flags->space = 1;
        (*format)++;
        break;
      case '#':
        flags->sharp = 1;
        (*format)++;
        break;
      case '0':
        flags->zero = 1;
        (*format)++;
        break;
      default:
        // завершение без break цикла (разрешено)
        return;
    }
  }
}

static int parse_width(const char** format, va_list* args) {
  int width = 0;
  if (**format == '*') {
    (*format)++;
    width = va_arg(*args, int);
  } else {
    while (**format >= '0' && **format <= '9') {
      width = width * 10 + (**format - '0');
      (*format)++;
    }
  }
  return width;
}

static int parse_precision(const char** format, va_list* args) {
  int prec = 0;
  if (**format == '*') {
    (*format)++;
    prec = va_arg(*args, int);
  } else {
    while (**format >= '0' && **format <= '9') {
      prec = prec * 10 + (**format - '0');
      (*format)++;
    }
  }
  return prec;
}

static void parse_length(const char** format, char* length) {
  if (**format == 'h' || **format == 'l') {
    length[0] = *(*format)++;
    if (**format == length[0]) {
      (*format)++;
    }
  } else if (**format == 'L') {
    length[0] = *(*format)++;
  }
}
