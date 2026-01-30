#include "s21_test.h"

void test_string(SRunner* runner) {
  srunner_add_suite(runner, s21_strncpy_suite());
  srunner_add_suite(runner, s21_strlen_suite());
  srunner_add_suite(runner, strerror_suite());
  srunner_add_suite(runner, s21_memchr_suite());
  srunner_add_suite(runner, s21_memcmp_suite());
  srunner_add_suite(runner, s21_memcpy_suite());
  srunner_add_suite(runner, s21_memset_suite());
  srunner_add_suite(runner, strchr_suite());
  srunner_add_suite(runner, strcspn_suite());
  srunner_add_suite(runner, strncat_suite());
  srunner_add_suite(runner, s21_strncmp_suite());
  srunner_add_suite(runner, strpbrk_suite());
  srunner_add_suite(runner, strrchr_suite());
  srunner_add_suite(runner, strstr_suite());
  srunner_add_suite(runner, s21_strtok_suite());
  srunner_add_suite(runner, s21_test_more_suite());
}

void test_sprintf(SRunner* runner) {
  srunner_add_suite(runner, s21_sprintf_percent_suite());
  srunner_add_suite(runner, s21_sprintf_f_suite());
  srunner_add_suite(runner, s21_sprintf_e_suite());
  srunner_add_suite(runner, s21_sprintf_E_suite());
  srunner_add_suite(runner, s21_sprintf_g_suite());
  srunner_add_suite(runner, s21_sprintf_G_suite());
  srunner_add_suite(runner, sprintf_c_suite());
  srunner_add_suite(runner, suite_s21_p());
  srunner_add_suite(runner, s21_sprintf_u_suite());
  srunner_add_suite(runner, s21_sprintf_s_suite());
  srunner_add_suite(runner, s21_sprintf_d_suite());
  srunner_add_suite(runner, s21_sprintf_i_suite());
  srunner_add_suite(runner, s21_sprintf_x_suite());
  srunner_add_suite(runner, s21_sprintf_o_suite());
}

void test_sscanf(SRunner* runner) {
  srunner_add_suite(runner, s21_sscanf_c_suite());
  srunner_add_suite(runner, s21_sscanf_d_suite());
  srunner_add_suite(runner, s21_sscanf_f_integration_suite());
  srunner_add_suite(runner, s21_sscanf_p_integration_suite());
  srunner_add_suite(runner, s21_sscanf_percent_suite());
  srunner_add_suite(runner, s21_sscanf_basic_suite());
  srunner_add_suite(runner, s21_sscanf_x_suite());
  srunner_add_suite(runner, s21_insert_suite());
  srunner_add_suite(runner, s21_to_lower_suite());
  srunner_add_suite(runner, s21_trim_suite());
  srunner_add_suite(runner, s21_sscanf_more_suite());
  srunner_add_suite(runner, s21_to_upper_suite());
}

int main(void) {
  int failed = 0;
  SRunner* runner = srunner_create(NULL);

  test_string(runner);
  test_sprintf(runner);
  test_sscanf(runner);
  srunner_run_all(runner, CK_NORMAL);
  failed += srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
