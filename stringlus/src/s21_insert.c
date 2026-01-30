#include "s21_string.h"

void* s21_insert(const char* src, const char* str, s21_size start_index) {
  void* result = S21_NULL;
  int error = 0;

  if (src == S21_NULL || str == S21_NULL) {
    error = 1;
  } else {
    s21_size src_len = s21_strlen(src);
    s21_size str_len = s21_strlen(str);
    if (start_index > src_len) {
      error = 1;
    } else {
      char* buffer = (char*)malloc((src_len + str_len + 1) * sizeof(char));
      if (buffer == S21_NULL) {
        error = 1;
      } else {
        s21_strncpy(buffer, src, start_index);
        s21_strncpy(buffer + start_index, str, str_len);
        s21_strncpy(buffer + start_index + str_len, src + start_index,
                    src_len - start_index);

        buffer[src_len + str_len] = '\0';
        result = buffer;
      }
    }
  }
  if (error) {
    free(result);
    result = S21_NULL;
  }

  return result;
}