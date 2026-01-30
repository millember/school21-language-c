#ifndef S21_TEST_H
#define S21_TEST_H

#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"
#include "../sprintf/s21_sprintf_handlers.h"
#include "../sprintf/s21_sprintf_types.h"

#define MAX_STR_SIZE 20

Suite* s21_memchr_suite(void);
Suite* s21_memcmp_suite(void);
Suite* s21_memcpy_suite(void);
Suite* s21_memset_suite(void);
Suite* s21_strncpy_suite(void);
Suite* s21_strlen_suite(void);
Suite* strerror_suite(void);
Suite* strchr_suite(void);
Suite* strcspn_suite(void);
Suite* strncat_suite(void);
Suite* s21_strncmp_suite(void);
Suite* strpbrk_suite(void);
Suite* strrchr_suite(void);
Suite* strstr_suite(void);
Suite* s21_strtok_suite(void);

Suite* s21_insert_suite(void);
Suite* s21_to_lower_suite(void);
Suite* s21_trim_suite(void);
Suite* s21_to_upper_suite(void);

Suite* s21_sprintf_percent_suite(void);
Suite* s21_sprintf_f_suite(void);
Suite* s21_sprintf_e_suite(void);
Suite* s21_sprintf_E_suite(void);
Suite* s21_sprintf_g_suite(void);
Suite* s21_sprintf_G_suite(void);
Suite* s21_sprintf_d_suite(void);
Suite* s21_sprintf_i_suite(void);
Suite* sprintf_c_suite(void);
Suite* s21_sprintf_x_suite(void);
Suite* s21_sprintf_o_suite(void);
Suite* suite_s21_p(void);
Suite* s21_sprintf_u_suite(void);
Suite* s21_sprintf_s_suite(void);

Suite* s21_sscanf_c_suite(void);
Suite* s21_sscanf_d_suite(void);
Suite* s21_sscanf_f_integration_suite(void);
Suite* s21_sscanf_p_integration_suite(void);
Suite* s21_sscanf_percent_suite(void);
Suite* s21_sscanf_basic_suite(void);
Suite* s21_sscanf_x_suite(void);
Suite* s21_sscanf_more_suite();
Suite* s21_test_more_suite();
#endif
