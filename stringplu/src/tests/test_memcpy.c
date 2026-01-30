#include "s21_test.h"

START_TEST(test_memcpy_norma) {
  void* dest = NULL;
  const void* src = "9876";
  size_t n = 5;
  dest = (char*)calloc(MAX_STR_SIZE, sizeof(char));

  ck_assert_mem_eq(memcpy(dest, src, n), s21_memcpy(dest, src, n), n);

  free(dest);
}
END_TEST

START_TEST(test_memcpy_n_0) {
  void* dest = NULL;
  const void* src = "9876";
  size_t n = 0;
  dest = (char*)calloc(MAX_STR_SIZE, sizeof(char));

  ck_assert_mem_eq(memcpy(dest, src, n), s21_memcpy(dest, src, n), n);

  free(dest);
}
END_TEST

START_TEST(test_memcpy_src_void) {
  void* dest = NULL;
  const void* src = "";
  size_t n = 0;
  dest = (char*)calloc(MAX_STR_SIZE, sizeof(char));

  ck_assert_mem_eq(memcpy(dest, src, n), s21_memcpy(dest, src, n), n);

  free(dest);
}
END_TEST

Suite* s21_memcpy_suite(void) {
  Suite* suite = suite_create("s21_memcpy_suite");
  TCase *tcase_norm, *tcase_n_0, *tcase_src_void;

  tcase_norm = tcase_create("Trivial case");
  tcase_n_0 = tcase_create("n = 0");
  tcase_src_void = tcase_create("src is void");

  tcase_add_test(tcase_norm, test_memcpy_norma);
  tcase_add_test(tcase_n_0, test_memcpy_n_0);
  tcase_add_test(tcase_src_void, test_memcpy_src_void);

  suite_add_tcase(suite, tcase_norm);
  suite_add_tcase(suite, tcase_n_0);
  suite_add_tcase(suite, tcase_src_void);

  return suite;
}