#include "s21_matrix.h"

void s21_for_create_columns(matrix_t *result, int *flag) {
  for (int i = 0; i < result->rows && *flag == 0; i++) {
    result->matrix[i] = calloc(result->columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
        result->matrix[j] = NULL;
      }
      free(result->matrix);
      result->matrix = NULL;
      *flag = _ERROR;
      result->rows = result->columns = 0;
    }
  }
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = _SUCCS;
  if (!rows || !columns || result == NULL) flag = _UNCOR;
  if (!flag) {
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      flag = _UNCOR;
      result->rows = result->columns = 0;
    } else {
      result->rows = rows;
      result->columns = columns;
      s21_for_create_columns(result, &flag);
    }
  }
  return flag;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_is_matrix_null(matrix_t *A) {
  return (A && A->matrix && A->rows > 0 && A->columns > 0);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;
  if (A->rows == B->rows && A->columns == B->columns && s21_is_matrix_null(A) &&
      s21_is_matrix_null(B)) {
    for (int i = 0; i < A->rows && flag; i++) {
      for (int j = 0; j < A->columns && flag; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          flag = FAILURE;
        }
      }
    }
  } else
    flag = FAILURE;

  return flag;
}

int s21_matrix_operation(matrix_t *A, matrix_t *B, matrix_t *result,
                         char operation) {
  int flag = _SUCCS;

  if (!s21_is_matrix_null(A) || !s21_is_matrix_null(B)) {
    flag = _UNCOR;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    flag = _ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (operation == '+') {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        } else if (operation == '-') {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }

  return flag;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_matrix_operation(A, B, result, '+');
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_matrix_operation(A, B, result, '-');
}

void s21_copy_matrix(matrix_t *from, matrix_t *to) {
  if (s21_is_matrix_null(to)) {
    s21_remove_matrix(to);
  }

  s21_create_matrix(from->rows, from->columns, to);
  for (int i = 0; i < from->rows; i++) {
    for (int j = 0; j < from->columns; j++) {
      to->matrix[i][j] = from->matrix[i][j];
    }
  }
}

double s21_minor_det(int row, int col, matrix_t *src) {
  double det = 0.0;

  matrix_t a = {0};
  matrix_t *A = &a;
  s21_create_matrix(src->rows - 1, src->columns - 1, A);
  int new_rows_i = 0;
  for (int i = 0; i < src->rows; i++) {
    if (i == row) {
      continue;
    }
    int new_cols_i = 0;
    for (int j = 0; j < src->columns; j++) {
      if (j == col) {
        continue;
      }
      A->matrix[new_rows_i][new_cols_i] = src->matrix[i][j];
      new_cols_i++;
    }
    new_rows_i++;
  }
  s21_determinant(A, &det);
  s21_remove_matrix(A);

  return det;
}

void s21_convert_to_minor_matrix(matrix_t *A, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = s21_minor_det(i, j, A);
    }
  }
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int flag = _SUCCS;

  if (!s21_is_matrix_null(A)) {
    flag = _UNCOR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  return flag;
}

void s21_for_mult(matrix_t *A, matrix_t *B, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = _SUCCS;

  if (!s21_is_matrix_null(A) || !s21_is_matrix_null(B)) {
    flag = _UNCOR;
  } else if (A->columns != B->rows) {
    flag = _ERROR;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    s21_for_mult(A, B, result);
  }

  return flag;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = _SUCCS;

  if (!s21_is_matrix_null(A)) {
    flag = _UNCOR;
  } else {
    s21_create_matrix(A->columns, A->rows, result);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return flag;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = _SUCCS;

  if (!s21_is_matrix_null(A)) {
    flag = _UNCOR;
  } else if (A->rows != A->columns) {
    flag = _ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    s21_convert_to_minor_matrix(A, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] =
            ((i + 1 + j + 1) % 2 == 0 ? 1 : -1) * result->matrix[i][j];
      }
    }
  }

  return flag;
}

int s21_determinant(matrix_t *A, double *result) {
  int flag = _SUCCS;
  *result = 0;
  if (!s21_is_matrix_null(A)) {
    flag = _UNCOR;
  } else if (A->rows != A->columns) {
    flag = _ERROR;
  } else {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result = (A->matrix[0][0] * A->matrix[1][1]) -
                (A->matrix[1][0] * A->matrix[0][1]);
    } else {
      matrix_t b = {0};
      matrix_t *B = &b;
      s21_copy_matrix(A, B);
      for (int i = 0; i < A->columns; i++) {
        *result +=
            (i % 2 == 0 ? 1 : -1) * s21_minor_det(0, i, B) * B->matrix[0][i];
      }
      s21_remove_matrix(B);
    }
  }

  return flag;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = _SUCCS;
  double det = 0.0;

  s21_create_matrix(A->rows, A->columns, result);
  s21_determinant(A, &det);

  if (!s21_is_matrix_null(A)) {
    flag = _UNCOR;
  } else if (A->rows != A->columns || det == 0.0) {
    flag = _ERROR;
  } else if (A->rows == 1) {
    result->matrix[0][0] = 1.0 / det;
  } else {
    matrix_t temp = {0};
    s21_calc_complements(A, &temp);
    s21_copy_matrix(&temp, result);
    s21_transpose(result, &temp);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = temp.matrix[i][j] * (1 / det);
      }
    }
    s21_remove_matrix(&temp);
  }
  return flag;
}
