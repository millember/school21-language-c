#include <check.h>
#include <stdio.h>

#include "../s21_string.h"

START_TEST(test_sscanf_p_with_prefix) {
  const char* input = "0x7ffee4b5c8ac";
  void* s21_result = S21_NULL;
  void* std_result = S21_NULL;

  int s21_res = s21_sscanf(input, "%p", &s21_result);
  int std_res = sscanf(input, "%p", &std_result);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_p_without_prefix) {
  const char* input = "7ffee4b5c8ac";
  void* s21_result = S21_NULL;
  void* std_result = S21_NULL;

  int s21_res = s21_sscanf(input, "%p", &s21_result);
  int std_res = sscanf(input, "%p", &std_result);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_p_with_leading_spaces) {
  const char* input = "   0x123";
  void* s21_result = S21_NULL;
  void* std_result = S21_NULL;

  int s21_res = s21_sscanf(input, "%p", &s21_result);
  int std_res = sscanf(input, "%p", &std_result);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_p_suppress) {
  const char* input = "0xdeadbeef";

  int s21_res = s21_sscanf(input, "%*p");
  int std_res = sscanf(input, "%*p");

  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_sscanf_p_width) {
  const char* input = "0x12345678";
  void* s21_result = S21_NULL;
  void* std_result = S21_NULL;

  int s21_res = s21_sscanf(input, "%6p", &s21_result);
  int std_res = sscanf(input, "%6p", &std_result);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_p_multiple) {
  const char* input = "0x123 0x456 0x789";
  void* s21_ptrs[3] = {S21_NULL, S21_NULL, S21_NULL};
  void* std_ptrs[3] = {S21_NULL, S21_NULL, S21_NULL};

  int s21_res =
      s21_sscanf(input, "%p %p %p", &s21_ptrs[0], &s21_ptrs[1], &s21_ptrs[2]);
  int std_res =
      sscanf(input, "%p %p %p", &std_ptrs[0], &std_ptrs[1], &std_ptrs[2]);

  ck_assert_int_eq(s21_res, std_res);

  if (s21_res > 0) {
    for (int i = 0; i < s21_res; i++) {
      ck_assert_ptr_eq(s21_ptrs[i], std_ptrs[i]);
    }
  }
}
END_TEST

START_TEST(test_sscanf_p_mixed) {
  const char* input = "Address: 0x12345";
  void* s21_ptr = S21_NULL;
  void* std_ptr = S21_NULL;

  int s21_res = s21_sscanf(input, "Address: %p", &s21_ptr);
  int std_res = sscanf(input, "Address: %p", &std_ptr);

  ck_assert_int_eq(s21_res, std_res);

  if (s21_res == 1 && std_res == 1) {
    ck_assert_ptr_eq(s21_ptr, std_ptr);
  }
}
END_TEST

START_TEST(test_sscanf_p_invalid) {
  const char* input = "0x";
  void* s21_result = S21_NULL;
  void* std_result = S21_NULL;

  int s21_res = s21_sscanf(input, "%p", &s21_result);
  int std_res = sscanf(input, "%p", &std_result);

  ck_assert_int_eq(s21_res, 1);
  ck_assert_int_eq(std_res, 1);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_p_partial) {
  const char* input = "0x123g456";
  void* s21_result = S21_NULL;
  void* std_result = S21_NULL;

  int s21_res = s21_sscanf(input, "%p", &s21_result);
  int std_res = sscanf(input, "%p", &std_result);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_p_null_dest) {
  const char* input = "0x123";
  void* ptr = S21_NULL;

  int s21_res = s21_sscanf(input, "%p", &ptr);
  int std_res = sscanf(input, "%p", &ptr);

  ck_assert_int_eq(s21_res, std_res);
}
END_TEST

START_TEST(test_sscanf_p_mixed_case) {
  const char* input = "0xDeAdBeEf";
  void* s21_result = S21_NULL;
  void* std_result = S21_NULL;

  int s21_res = s21_sscanf(input, "%p", &s21_result);
  int std_res = sscanf(input, "%p", &std_result);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_p_uppercase_prefix) {
  const char* input = "0X123abc";
  void* s21_result = S21_NULL;
  void* std_result = S21_NULL;

  int s21_res = s21_sscanf(input, "%p", &s21_result);
  int std_res = sscanf(input, "%p", &std_result);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_p_max_address) {
  const char* input = "0xFFFFFFFFFFFFFFFF";
  void* s21_result = S21_NULL;
  void* std_result = S21_NULL;

  int s21_res = s21_sscanf(input, "%p", &s21_result);
  int std_res = sscanf(input, "%p", &std_result);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

Suite* s21_sscanf_p_integration_suite(void) {
  Suite* s = suite_create("s21_sscanf_p_integration");
  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, test_sscanf_p_with_prefix);
  tcase_add_test(tc, test_sscanf_p_without_prefix);
  tcase_add_test(tc, test_sscanf_p_with_leading_spaces);
  tcase_add_test(tc, test_sscanf_p_suppress);
  tcase_add_test(tc, test_sscanf_p_width);
  tcase_add_test(tc, test_sscanf_p_multiple);
  tcase_add_test(tc, test_sscanf_p_mixed);
  tcase_add_test(tc, test_sscanf_p_invalid);
  tcase_add_test(tc, test_sscanf_p_partial);
  tcase_add_test(tc, test_sscanf_p_null_dest);
  tcase_add_test(tc, test_sscanf_p_mixed_case);
  tcase_add_test(tc, test_sscanf_p_uppercase_prefix);
  tcase_add_test(tc, test_sscanf_p_max_address);

  suite_add_tcase(s, tc);
  return s;
}
