#include "../../inc/backend.h"

Matrix_t *createMatrix(int rows, int cols, Error_t *err) {
  if (!isValidCreate(rows, cols, err)) {
    return NULL;
  }
  Matrix_t *matrix = (Matrix_t *)safeMalloc(sizeof(Matrix_t), err);
  if (*err == kOk) {
    matrix->arr = create2DimArr(rows, cols, err);
  }
  if (*err == kOk) {
    matrix->cols = cols;
    matrix->rows = rows;
    cleanArr(rows, cols, matrix->arr);
  } else {
    freeMatrix(&matrix);
  }
  return matrix;
}

void copyMatrix(Matrix_t *src, Matrix_t *dst) {
  if (src && dst) {
    for (int i = 0; i < src->rows; i++) {
      for (int j = 0; j < src->cols; j++) {
        dst->arr[i][j] = src->arr[i][j];
      }
    }
  }
}

void freeMatrix(Matrix_t **matrix) {
  if (matrix) {
    if (*matrix) {
      free((*matrix)->arr);
      (*matrix)->arr = NULL;
    }
    free(*matrix);
    *matrix = NULL;
  }
}