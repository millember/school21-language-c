#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
// 0 - OK
#define _SUCCS 0
// 1 - Ошибка, некорректная матрица
#define _UNCOR 1
// 2 - Ошибка вычисления (несовпадающие размеры матриц;
// матрица, для которой нельзя провести вычисления и т.д.)
#define _ERROR 2
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
void s21_for_create_columns(matrix_t *result, int *flag);
int s21_is_matrix_null(matrix_t *A);
void s21_copy_matrix(matrix_t *from, matrix_t *to);
double s21_minor_det(int row, int col, matrix_t *src);
void s21_convert_to_minor_matrix(matrix_t *A, matrix_t *result);
int s21_matrix_operation(matrix_t *A, matrix_t *B, matrix_t *result,
                         char operation);
#endif
