#ifndef S21_SPRINTF_HANDLERS_H
#define S21_SPRINTF_HANDLERS_H

int s21_sscanf_s(const char** str, char* out, int width, int assign);
int s21_sscanf_c(const char** str, char* out, int width, int assign);
int s21_sscanf_p(const char** str, void** out, int width, int assign);

int s21_sscanf_d(const char** str, void* out, char spec, int width, int assign,
                 char length);
int s21_sscanf_x(const char** str, void* out, char spec, int width, int assign,
                 char length);
int s21_sscanf_f(const char** str, void* out, int width, int assign,
                 char length);

int s21_sscanf_percent(const char** str);
#endif
