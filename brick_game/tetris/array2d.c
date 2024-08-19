#include "../../inc/backend.h"

int **create2DimArr(int rows, int cols, Error_t *err) {
  if (!isValidCreate(rows, cols, err)) {
    return NULL;
  }
  size_t size = rows * cols * sizeof(int) + rows * sizeof(int *);
  int **arr = safeMalloc(size, err);
  if (*err == kOk) {
    int *ptr_val = (int *)(arr + rows);
    for (int i = 0; i < rows; i++) {
      arr[i] = ptr_val + cols * i;
    }
  }
  return arr;
}

void rotateArea(int **arr, int y1, int x1, int y2, int x2, bool is_clockwise) {
  transposeArea(arr, y1, x1, y2, x2);
  mirrorArea(arr, y1, x1, y2, x2, is_clockwise);
}

void transposeArea(int **arr, int y1, int x1, int y2, int x2) {
  for (int i = y1; i <= y2; i++) {
    for (int j = x1; j <= x2; j++) {
      if (i < j && i - y1 < x2 - x1) {
        swap(&arr[i][j], &arr[j - x1 + y1][i - y1 + x1]);
      }
    }
  }
}

void mirrorArea(int **arr, int y1, int x1, int y2, int x2, bool is_horizont) {
  int more_center = is_horizont ? upDivide(x2 - x1, 2) : upDivide(y2 - y1, 2);
  if (is_horizont) {
    for (int i = y1; i <= y2; i++) {
      for (int j = x1; j < more_center; j++) {
        swap(&arr[i][j], &arr[i][x2 - (j - x1)]);
      }
    }
  } else {
    for (int i = y1; i < more_center; i++) {
      for (int j = x1; j <= x2; j++) {
        swap(&arr[i][j], &arr[y2 - (i - y1)][j]);
      }
    }
  }
}

void cleanArr(int rows, int cols, int **arr) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      arr[i][j] = 0;
    }
  }
}

bool isValidCreate(int rows, int cols, Error_t *err) {
  int res = true;
  if (!err || *err != kOk) {
    res = false;
  } else if (rows <= 0 || cols <= 0) {
    *err = kErrIncorrect;
    res = false;
  }
  return res;
}