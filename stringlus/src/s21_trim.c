#include "s21_string.h"

void* s21_trim(const char* src, const char* trim_chars) {
  void* result = S21_NULL;

  if (src != S21_NULL) {
    s21_size src_len = s21_strlen(src);
    s21_size start = 0, end = src_len;
    if (trim_chars == S21_NULL) {
      result = malloc(src_len + 1);
      if (result) {
        s21_memcpy(result, src, src_len + 1);
      }
    } else {
      while (src[start] != '\0' &&
             s21_strchr(trim_chars, src[start]) != S21_NULL) {
        start++;
      }
      while (end > start && s21_strchr(trim_chars, src[end - 1]) != S21_NULL) {
        end--;
      }

      s21_size len = end - start;
      result = malloc(len + 1);
      if (result) {
        s21_memcpy(result, src + start, len);
        ((char*)result)[len] = '\0';
      }
    }
  }
  return result;
}
