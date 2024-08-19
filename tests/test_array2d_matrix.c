#include "../inc/test.h"

START_TEST(test_mirrorArea1) {
  Error_t err = kOk;
  Matrix_t *m1 = createMatrix(3, 3, &err);
  if (err == kOk) {
    fillMatrix1toN(m1);
    // printMatrix(&m1);
    mirrorArea(m1->arr, 0, 0, 2, 2, true);
    // printMatrix(&m1);
    for (int i = 0; i < m1->rows; i++) {
      int val = (i + 1) * m1->cols;
      for (int j = 0; j < m1->cols; j++) {
        ck_assert_int_eq(m1->arr[i][j], val--);
      }
    }
  } else {
    ck_assert_int_eq(err, kErrMem);
  }

  freeMatrix(&m1);
}
END_TEST

START_TEST(test_mirrorArea2) {
  Error_t err = kOk;
  Matrix_t *m1 = createMatrix(2, 2, &err);
  if (err == kOk) {
    fillMatrix1toN(m1);
    // printMatrix(&m1);
    mirrorArea(m1->arr, 0, 0, 1, 1, true);
    // printMatrix(&m1);
    for (int i = 0; i < m1->rows; i++) {
      int val = (i + 1) * m1->cols;
      for (int j = 0; j < m1->cols; j++) {
        ck_assert_int_eq(m1->arr[i][j], val--);
      }
    }
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeMatrix(&m1);
}
END_TEST

START_TEST(test_mirrorArea3) {
  Error_t err = kOk;
  Matrix_t *m1 = createMatrix(1, 1, &err);
  if (err == kOk) {
    fillMatrix1toN(m1);
    // printMatrix(&m1);
    mirrorArea(m1->arr, 0, 0, 0, 0, true);
    // printMatrix(&m1);
    ck_assert_int_eq(m1->arr[0][0], 1);
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeMatrix(&m1);
}
END_TEST

START_TEST(test_mirrorArea4) {
  Error_t err = kOk;
  Matrix_t *m1 = createMatrix(3, 3, &err);
  if (err == kOk) {
    fillMatrix1toN(m1);
    // printMatrix(&m1);
    mirrorArea(m1->arr, 0, 0, 2, 2, false);
    // printMatrix(&m1);
    ck_assert_int_eq(m1->arr[0][0], 7);
    ck_assert_int_eq(m1->arr[0][1], 8);
    ck_assert_int_eq(m1->arr[0][2], 9);

    ck_assert_int_eq(m1->arr[1][0], 4);
    ck_assert_int_eq(m1->arr[1][1], 5);
    ck_assert_int_eq(m1->arr[1][2], 6);

    ck_assert_int_eq(m1->arr[2][0], 1);
    ck_assert_int_eq(m1->arr[2][1], 2);
    ck_assert_int_eq(m1->arr[2][2], 3);

  } else {
    ck_assert_int_eq(err, kErrMem);
  }

  freeMatrix(&m1);
}
END_TEST

START_TEST(test_transposeArea1) {
  Error_t err = kOk;
  Matrix_t *m1 = createMatrix(3, 3, &err);
  if (err == kOk) {
    fillMatrix1toN(m1);
    // printMatrix(&m1);
    transposeArea(m1->arr, 0, 0, 2, 2);
    // printMatrix(&m1);
    int val = 1;
    for (int i = 0; i < m1->cols; i++) {
      for (int j = 0; j < m1->rows; j++) {
        ck_assert_int_eq(m1->arr[j][i], val++);
      }
    }
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeMatrix(&m1);
}
END_TEST

START_TEST(test_transposeArea2) {
  Error_t err = kOk;
  Matrix_t *m1 = createMatrix(2, 2, &err);
  if (err == kOk) {
    fillMatrix1toN(m1);
    // printMatrix(&m1);
    transposeArea(m1->arr, 0, 0, 1, 1);
    // printMatrix(&m1);
    int val = 1;
    for (int i = 0; i < m1->cols; i++) {
      for (int j = 0; j < m1->rows; j++) {
        ck_assert_int_eq(m1->arr[j][i], val++);
      }
    }
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeMatrix(&m1);
}
END_TEST

START_TEST(test_transposeArea3) {
  Error_t err = kOk;
  Matrix_t *m1 = createMatrix(5, 5, &err);
  if (err == kOk) {
    fillMatrix1toN(m1);
    // printMatrix(&m1);
    transposeArea(m1->arr, 0, 0, 1, 1);
    // printMatrix(&m1);
    int val = 1;
    for (int i = 0; i < m1->rows; i++) {
      for (int j = 0; j < m1->cols; j++) {
        if (!((i == 1 && j == 0) || (i == 0 && j == 1))) {
          ck_assert_int_eq(m1->arr[i][j], val);
        }
        val++;
      }
    }
    ck_assert_int_eq(m1->arr[0][1], 6);
    ck_assert_int_eq(m1->arr[1][0], 2);
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeMatrix(&m1);
}
END_TEST

START_TEST(test_rotateArea1) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);
  if (err == kOk) {
    fillFigureTetromino(tetr1->field->arr, kI);
    // printMatrix(tetr1->field);
    rotateArea(tetr1->field->arr, 0, 0, 3, 3, true);
    // printMatrix(tetr1->field);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (j == 2) {
          ck_assert_int_gt(tetr1->field->arr[i][j], 0);
        } else {
          ck_assert_int_eq(tetr1->field->arr[i][j], 0);
        }
      }
    }
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeTetromino(&tetr1);
}
END_TEST

START_TEST(test_rotateArea2) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);
  if (err == kOk) {
    fillFigureTetromino(tetr1->field->arr, kO);
    // printMatrix(tetr1->field);
    rotateArea(tetr1->field->arr, 0, 0, 3, 3, true);
    // printMatrix(tetr1->field);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (j >= 2 && (i == 1 || i == 2)) {
          ck_assert_int_gt(tetr1->field->arr[i][j], 0);
        } else {
          ck_assert_int_eq(tetr1->field->arr[i][j], 0);
        }
      }
    }
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeTetromino(&tetr1);
}
END_TEST

START_TEST(test_rotateArea3) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);
  if (err == kOk) {
    fillFigureTetromino(tetr1->field->arr, kS);
    // printMatrix(tetr1->field);
    rotateArea(tetr1->field->arr, 0, 0, 3, 3, true);
    // printMatrix(tetr1->field);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if ((j == 2 && (i == 0 || i == 1)) || (j == 3 && (i == 1 || i == 2))) {
          ck_assert_int_gt(tetr1->field->arr[i][j], 0);
        } else {
          ck_assert_int_eq(tetr1->field->arr[i][j], 0);
        }
      }
    }
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeTetromino(&tetr1);
}
END_TEST

START_TEST(test_rotateArea4) {
  Error_t err = kOk;
  Matrix_t *m1 = createMatrix(2, 2, &err);
  if (err == kOk) {
    fillMatrix1toN(m1);
    // printMatrix(&m1);
    rotateArea(m1->arr, 0, 0, 1, 1, true);
    // printMatrix(&m1);
    ck_assert_int_eq(m1->arr[0][0], 3);
    ck_assert_int_eq(m1->arr[0][1], 1);
    ck_assert_int_eq(m1->arr[1][0], 4);
    ck_assert_int_eq(m1->arr[1][1], 2);
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeMatrix(&m1);
}
END_TEST

START_TEST(test_rotateArea5) {
  Error_t err = kOk;
  Matrix_t *m1 = createMatrix(1, 1, &err);
  if (err == kOk) {
    fillMatrix1toN(m1);
    // printMatrix(&m1);
    rotateArea(m1->arr, 0, 0, 0, 0, true);
    // printMatrix(&m1);
    ck_assert_int_eq(m1->arr[0][0], 1);
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeMatrix(&m1);
}
END_TEST

START_TEST(test_rotateArea7) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);
  if (err == kOk) {
    fillFigureTetromino(tetr1->field->arr, kS);
    // printMatrix(tetr1->field);
    rotateArea(tetr1->field->arr, 0, 0, 2, 2, true);
    // printMatrix(tetr1->field);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if ((j == 1 && (i == 0 || i == 1)) || (j == 2 && (i == 1 || i == 2))) {
          ck_assert_int_gt(tetr1->field->arr[i][j], 0);
        } else {
          ck_assert_int_eq(tetr1->field->arr[i][j], 0);
        }
      }
    }
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeTetromino(&tetr1);
}
END_TEST

START_TEST(test_copyMatrix1) {
  Error_t err = kOk;
  Matrix_t *matrix1 = createMatrix(4, 4, &err);
  Matrix_t *matrix2 = createMatrix(4, 4, &err);

  if (err == kOk) {
    fillFigureTetromino(matrix1->arr, kS);
    copyMatrix(matrix1, matrix2);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if ((i == 0 && (j == 1 || j == 2)) || (i == 1 && (j == 0 || j == 1))) {
          ck_assert_int_gt(matrix2->arr[i][j], 0);
        } else {
          ck_assert_int_eq(matrix2->arr[i][j], 0);
        }
      }
    }
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeMatrix(&matrix1);
  freeMatrix(&matrix2);
}
END_TEST

START_TEST(test_copyMatrix2) {
  Error_t err = kOk;
  Matrix_t *matrix1 = createMatrix(2, 2, &err);
  Matrix_t *matrix2 = createMatrix(2, 2, &err);

  if (err == kOk) {
    fillMatrix1toN(matrix1);
    copyMatrix(matrix1, matrix2);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        ck_assert_int_eq(matrix2->arr[i][j], matrix1->arr[i][j]);
      }
    }
  }
  freeMatrix(&matrix1);
  freeMatrix(&matrix2);
}

START_TEST(test_isValid1) {
  Error_t err = kOk;
  ck_assert_int_eq(isValidCreate(2, 1, &err), true);

  ck_assert_int_eq(isValidCreate(2, 0, &err), false);
  ck_assert_int_eq(isValidCreate(0, 1, &err), false);
  ck_assert_int_eq(isValidCreate(-1, 1, &err), false);

  err = kErrMem;
  ck_assert_int_eq(isValidCreate(2, 1, &err), false);
  ck_assert_int_eq(isValidCreate(2, 1, NULL), false);
}
END_TEST

START_TEST(test_create2DimArr1) {
  Error_t err = kOk;
  ck_assert_ptr_null(create2DimArr(2, 0, &err));
  ck_assert_ptr_null(create2DimArr(-1, 2, &err));
  err = kErrMem;
  ck_assert_ptr_null(create2DimArr(2, 2, &err));
}
END_TEST

START_TEST(test_createMatrix1) {
  Error_t err = kOk;
  ck_assert_ptr_null(createMatrix(2, 0, &err));
  ck_assert_ptr_null(createMatrix(-1, 2, &err));
  err = kErrMem;
  ck_assert_ptr_null(createMatrix(2, 2, &err));
}
END_TEST

Suite *test_array2d_matrix(void) {
  Suite *s = suite_create("array2d_matrix");
  TCase *tc_core = tcase_create("array2d_matrix");

  tcase_add_test(tc_core, test_mirrorArea1);
  tcase_add_test(tc_core, test_mirrorArea2);
  tcase_add_test(tc_core, test_mirrorArea3);
  tcase_add_test(tc_core, test_mirrorArea4);

  tcase_add_test(tc_core, test_transposeArea1);
  tcase_add_test(tc_core, test_transposeArea2);
  tcase_add_test(tc_core, test_transposeArea3);

  tcase_add_test(tc_core, test_rotateArea1);
  tcase_add_test(tc_core, test_rotateArea2);
  tcase_add_test(tc_core, test_rotateArea3);
  tcase_add_test(tc_core, test_rotateArea4);
  tcase_add_test(tc_core, test_rotateArea5);
  tcase_add_test(tc_core, test_rotateArea7);

  tcase_add_test(tc_core, test_copyMatrix1);
  tcase_add_test(tc_core, test_copyMatrix2);
  tcase_add_test(tc_core, test_isValid1);
  tcase_add_test(tc_core, test_create2DimArr1);
  tcase_add_test(tc_core, test_createMatrix1);

  suite_add_tcase(s, tc_core);

  return s;
}
