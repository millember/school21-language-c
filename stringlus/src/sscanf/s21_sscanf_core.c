#include "../s21_string.h"
#include "s21_sscanf_handlers.h"

int s21_sscanf_handle_specifier(const char** src, const char* str_start,
                                char spec, char length, int width, int assign,
                                va_list* args, int* assigned, int* error) {
  int result = 0;
  int local_stop = 0;

  switch (spec) {
    case 'c': {
      char* out = assign ? va_arg(*args, char*) : (char*)S21_NULL;
      result = s21_sscanf_c(src, out, width, assign);
      break;
    }

    case 's': {
      char* out = assign ? va_arg(*args, char*) : (char*)S21_NULL;
      result = s21_sscanf_s(src, out, width, assign);
      break;
    }

    case 'd':
    case 'i': {
      void* out = assign ? va_arg(*args, void*) : S21_NULL;
      result = s21_sscanf_d(src, out, spec, width, assign, length);
      break;
    }

    case 'u':
    case 'o':
    case 'x':
    case 'X': {
      void* out = assign ? va_arg(*args, void*) : S21_NULL;
      result = s21_sscanf_x(src, out, spec, width, assign, length);
      break;
    }

    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G': {
      void* out = assign ? va_arg(*args, void*) : S21_NULL;
      result = s21_sscanf_f(src, out, width, assign, length);
      break;
    }

    case 'p': {
      void** out = assign ? va_arg(*args, void**) : (void**)S21_NULL;
      result = s21_sscanf_p(src, out, width, assign);
      break;
    }

    case '%': {
      result = s21_sscanf_percent(src);
      local_stop = 1;
      break;
    }

    case 'n': {
      int chars_read = (int)(*src - str_start);

      // ВСЕГДА извлекаем аргумент из va_list — это критически важно!
      void* p = va_arg(*args, void*);

      switch (length) {
        case 'h': {
          if (assign && p) {
            *(short*)p = (short)chars_read;
          }
          break;
        }
        case 'l': {
          if (assign && p) {
            *(long*)p = (long)chars_read;
          }
          break;
        }
        default: {
          if (assign && p) {
            *(int*)p = chars_read;
          }
          break;
        }
      }
      local_stop = 1;
      break;
    }

    default:
      *error = 1;
      local_stop = 1;
      break;
  }

  if (!local_stop) {
    if (assign && result == 1) {
      (*assigned)++;
    }
  }
  return 0;
}
