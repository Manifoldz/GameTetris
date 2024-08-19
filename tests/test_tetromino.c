#include "../inc/test.h"

START_TEST(test_rotateTetromino1) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);
  if (err == kOk) {
    tetr1->name = kO;
    fillFigureTetromino(tetr1->field->arr, tetr1->name);
    // printMatrix(tetr1->field);
    rotateTetromino(tetr1, true);
    // printMatrix(tetr1->field);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (i < 2 && (j == 1 || j == 2)) {
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

START_TEST(test_rotateTetromino2) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);
  if (err == kOk) {
    tetr1->name = kI;
    fillFigureTetromino(tetr1->field->arr, tetr1->name);
    // printMatrix(tetr1->field);
    rotateTetromino(tetr1, true);
    rotateTetromino(tetr1, true);
    // printMatrix(tetr1->field);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (i == 2) {
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

START_TEST(test_rotateTetromino3) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);
  if (err == kOk) {
    tetr1->name = kT;
    fillFigureTetromino(tetr1->field->arr, tetr1->name);
    // printMatrix(tetr1->field);
    rotateTetromino(tetr1, true);
    rotateTetromino(tetr1, true);
    // printMatrix(tetr1->field);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if ((i == 1 && j < 3) || (i == 2 && j == 1)) {
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

START_TEST(test_fillFigureTetromino1) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);
  if (err == kOk) {
    tetr1->name = kL;
    fillFigureTetromino(tetr1->field->arr, tetr1->name);
    // printMatrix(tetr1->field);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if ((i == 1 && j < 3) || (i == 0 && j == 2)) {
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

START_TEST(test_genNextTetromino1) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);
  Tetromino_t *tetr2 = createTetromino(&err);

  if (err == kOk) {
    tetr1->name = kL;
    genNextTetromino(tetr1);
    tetr2->name = tetr1->name;
    fillFigureTetromino(tetr2->field->arr, tetr2->name);
    // printMatrix(tetr1->field);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        ck_assert_int_eq(tetr1->field->arr[i][j], tetr2->field->arr[i][j]);
      }
    }
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeTetromino(&tetr1);
  freeTetromino(&tetr2);
}
END_TEST

START_TEST(test_isIntersectTetromino1) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);

  if (err == kOk) {
    Matrix_t *game_field = createMatrix(HEIGHT, WIDTH, &err);
    if (err == kOk) {
      tetr1->y = 0;
      tetr1->x = 0;
      tetr1->name = kI;
      fillFigureTetromino(tetr1->field->arr, tetr1->name);
      // printMatrix(tetr1->field);
      ck_assert_int_eq(isIntersectTetromino(tetr1, game_field->arr), false);
      tetr1->x = -1;
      ck_assert_int_eq(isIntersectTetromino(tetr1, game_field->arr), true);
      tetr1->name = kO;
      fillFigureTetromino(tetr1->field->arr, tetr1->name);
      // printMatrix(tetr1->field);
      ck_assert_int_eq(isIntersectTetromino(tetr1, game_field->arr), false);
      game_field->arr[19][0] = 1;
      tetr1->y = 18;
      ck_assert_int_eq(isIntersectTetromino(tetr1, game_field->arr), true);
      tetr1->x = 0;
      ck_assert_int_eq(isIntersectTetromino(tetr1, game_field->arr), false);
    }
    freeMatrix(&game_field);
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeTetromino(&tetr1);
}
END_TEST

START_TEST(test_isDroppedTetromino1) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);

  if (err == kOk) {
    Matrix_t *game_field = createMatrix(HEIGHT, WIDTH, &err);
    if (err == kOk) {
      tetr1->y = 0;
      tetr1->x = 0;
      tetr1->name = kI;
      fillFigureTetromino(tetr1->field->arr, tetr1->name);
      // printMatrix(tetr1->field);
      ck_assert_int_eq(isDroppedTetromino(tetr1, game_field->arr), false);
      game_field->arr[2][0] = 1;
      ck_assert_int_eq(isDroppedTetromino(tetr1, game_field->arr), true);
      tetr1->name = kO;
      fillFigureTetromino(tetr1->field->arr, tetr1->name);
      // printMatrix(tetr1->field);
      ck_assert_int_eq(isDroppedTetromino(tetr1, game_field->arr), false);
      tetr1->x = -1;
      ck_assert_int_eq(isIntersectTetromino(tetr1, game_field->arr), false);
      ck_assert_int_eq(isDroppedTetromino(tetr1, game_field->arr), true);
      tetr1->y = 17;
      ck_assert_int_eq(isDroppedTetromino(tetr1, game_field->arr), false);
      tetr1->y = 18;
      ck_assert_int_eq(isIntersectTetromino(tetr1, game_field->arr), false);
      ck_assert_int_eq(isDroppedTetromino(tetr1, game_field->arr), true);
    }
    freeMatrix(&game_field);
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeTetromino(&tetr1);
}
END_TEST

START_TEST(test_pinUnpinTetromino1) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);

  if (err == kOk) {
    Matrix_t *game_field = createMatrix(HEIGHT, WIDTH, &err);
    if (err == kOk) {
      tetr1->y = 18;
      tetr1->x = 0;
      tetr1->name = kI;
      fillFigureTetromino(tetr1->field->arr, tetr1->name);
      // printMatrix(tetr1->field);
      ck_assert_int_eq(isDroppedTetromino(tetr1, game_field->arr), true);
      pinUnpinTetromino(tetr1, game_field->arr, true);
      for (int i = 0; i < 4; i++) {
        ck_assert_int_eq(game_field->arr[19][i], 1);
      }
      tetr1->y = 16;
      ck_assert_int_eq(isDroppedTetromino(tetr1, game_field->arr), false);
      tetr1->name = kS;
      fillFigureTetromino(tetr1->field->arr, tetr1->name);
      rotateTetromino(tetr1, true);
      // printMatrix(tetr1->field);
      ck_assert_int_eq(isDroppedTetromino(tetr1, game_field->arr), true);
      tetr1->x = 5;
      ck_assert_int_eq(isDroppedTetromino(tetr1, game_field->arr), false);
      tetr1->y = 17;
      ck_assert_int_eq(isDroppedTetromino(tetr1, game_field->arr), true);

      pinUnpinTetromino(tetr1, game_field->arr, true);
      ck_assert_int_gt(game_field->arr[17][6], 0);
      ck_assert_int_gt(game_field->arr[18][6], 0);
      ck_assert_int_gt(game_field->arr[18][7], 0);
      ck_assert_int_gt(game_field->arr[19][7], 0);

      tetr1->name = kL;
      fillFigureTetromino(tetr1->field->arr, tetr1->name);
      rotateTetromino(tetr1, true);
      tetr1->y = 13;
      ck_assert_int_eq(isDroppedTetromino(tetr1, game_field->arr), false);
      tetr1->y = 14;
      ck_assert_int_eq(isDroppedTetromino(tetr1, game_field->arr), true);
      pinUnpinTetromino(tetr1, game_field->arr, true);

      ck_assert_int_gt(game_field->arr[14][6], 0);
      ck_assert_int_gt(game_field->arr[15][6], 0);
      ck_assert_int_gt(game_field->arr[16][6], 0);
      ck_assert_int_gt(game_field->arr[16][7], 0);

      ck_assert_int_gt(game_field->arr[17][6], 0);
      ck_assert_int_gt(game_field->arr[18][6], 0);
      ck_assert_int_gt(game_field->arr[18][7], 0);
      ck_assert_int_gt(game_field->arr[19][7], 0);
    }
    freeMatrix(&game_field);
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeTetromino(&tetr1);
}
END_TEST

START_TEST(test_createTetromino1) {
  Error_t err = kErrMem;
  ck_assert_ptr_null(createTetromino(&err));
  ck_assert_ptr_null(createTetromino(NULL));
}
END_TEST

Suite *test_tetromino(void) {
  Suite *s = suite_create("tetromino");
  TCase *tc_core = tcase_create("tetromino");

  tcase_add_test(tc_core, test_rotateTetromino1);
  tcase_add_test(tc_core, test_rotateTetromino2);
  tcase_add_test(tc_core, test_rotateTetromino3);

  tcase_add_test(tc_core, test_genNextTetromino1);

  tcase_add_test(tc_core, test_isIntersectTetromino1);
  tcase_add_test(tc_core, test_isDroppedTetromino1);

  tcase_add_test(tc_core, test_pinUnpinTetromino1);

  tcase_add_test(tc_core, test_fillFigureTetromino1);
  tcase_add_test(tc_core, test_createTetromino1);

  suite_add_tcase(s, tc_core);

  return s;
}
