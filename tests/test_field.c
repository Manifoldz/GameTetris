#include "../inc/test.h"

START_TEST(test_checkLineField1) {
  Error_t err = kOk;
  Matrix_t *game_field = createMatrix(HEIGHT, WIDTH, &err);
  if (err == kOk) {
    ck_assert_int_eq(checkLineField(HEIGHT - 1, game_field->arr, true), false);
    for (int i = 0; i < WIDTH; i++) {
      game_field->arr[HEIGHT - 1][i] = 1;
    }
    ck_assert_int_eq(checkLineField(HEIGHT - 1, game_field->arr, true), true);
    game_field->arr[HEIGHT - 1][0] = 0;
    ck_assert_int_eq(checkLineField(HEIGHT - 1, game_field->arr, true), false);
    game_field->arr[HEIGHT - 1][0] = 1;
    ck_assert_int_eq(checkLineField(HEIGHT - 1, game_field->arr, true), true);
    game_field->arr[HEIGHT - 1][9] = 0;
    ck_assert_int_eq(checkLineField(HEIGHT - 1, game_field->arr, true), false);
    for (int i = 0; i < WIDTH; i++) {
      game_field->arr[HEIGHT - 3][i] = 1;
    }
    ck_assert_int_eq(checkLineField(HEIGHT - 3, game_field->arr, true), true);
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeMatrix(&game_field);
}
END_TEST

START_TEST(test_checkLineField2) {
  Error_t err = kOk;
  Matrix_t *game_field = createMatrix(HEIGHT, WIDTH, &err);
  if (err == kOk) {
    ck_assert_int_eq(checkLineField(HEIGHT - 1, game_field->arr, false), true);
    for (int i = 0; i < WIDTH; i++) {
      game_field->arr[HEIGHT - 1][i] = 1;
    }
    ck_assert_int_eq(checkLineField(HEIGHT - 1, game_field->arr, false), false);
    game_field->arr[HEIGHT - 1][0] = 0;
    ck_assert_int_eq(checkLineField(HEIGHT - 1, game_field->arr, false), false);
    game_field->arr[HEIGHT - 1][0] = 1;
    ck_assert_int_eq(checkLineField(HEIGHT - 1, game_field->arr, false), false);
    game_field->arr[HEIGHT - 1][9] = 0;
    ck_assert_int_eq(checkLineField(HEIGHT - 1, game_field->arr, false), false);
    game_field->arr[HEIGHT - 3][0] = 1;
    ck_assert_int_eq(checkLineField(HEIGHT - 3, game_field->arr, false), false);
    ck_assert_int_eq(checkLineField(HEIGHT - 4, game_field->arr, false), true);
  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeMatrix(&game_field);
}
END_TEST

START_TEST(test_shiftDownField1) {
  Error_t err = kOk;
  Matrix_t *game_field = createMatrix(HEIGHT, WIDTH, &err);
  if (err == kOk) {
    for (int i = 0; i < WIDTH; i++) {
      game_field->arr[HEIGHT - 1][i] = 1;
    }
    ck_assert_int_eq(checkLineField(HEIGHT - 1, game_field->arr, true), true);
    shiftDownField(HEIGHT - 1, game_field->arr);
    ck_assert_int_eq(checkLineField(HEIGHT - 1, game_field->arr, true), false);

    for (int i = 0; i < WIDTH; i++) {
      game_field->arr[HEIGHT - 1][i] = 1;
    }

    game_field->arr[HEIGHT - 3][WIDTH - 1] = 1;
    game_field->arr[HEIGHT - 3][WIDTH - 2] = 1;

    for (int i = 0; i < WIDTH; i++) {
      game_field->arr[HEIGHT - 4][i] = 1;
    }
    ck_assert_int_eq(checkLineField(HEIGHT - 4, game_field->arr, true), true);
    shiftDownField(HEIGHT - 5, game_field->arr);
    ck_assert_int_eq(checkLineField(HEIGHT - 4, game_field->arr, true), true);
    shiftDownField(HEIGHT - 2, game_field->arr);
    ck_assert_int_eq(checkLineField(HEIGHT - 4, game_field->arr, true), false);
    ck_assert_int_eq(checkLineField(HEIGHT - 3, game_field->arr, true), true);
    ck_assert_int_eq(game_field->arr[HEIGHT - 2][WIDTH - 1], 1);
    ck_assert_int_eq(game_field->arr[HEIGHT - 2][WIDTH - 2], 1);
    ck_assert_int_eq(checkLineField(HEIGHT - 1, game_field->arr, true), true);

  } else {
    ck_assert_int_eq(err, kErrMem);
  }
  freeMatrix(&game_field);
}
END_TEST

START_TEST(test_moveHorTetromino1) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);
  tetr1->name = kI;
  fillFigureTetromino(tetr1->field->arr, tetr1->name);
  int **game_field = create2DimArr(HEIGHT, WIDTH, &err);
  cleanArr(HEIGHT, WIDTH, game_field);
  if (err == kOk) {
    tetr1->y = 5;
    tetr1->x = 5;
    pinUnpinTetromino(tetr1, game_field, true);

    for (int i = 0; i < FIGURE_WIDTH; i++) {
      ck_assert_int_eq(game_field[6][i + 5], kI);
    }

    moveHorTetromino(tetr1, game_field, true);
    for (int i = 0; i < FIGURE_WIDTH; i++) {
      ck_assert_int_eq(game_field[6][i + 6], kI);
    }

    moveHorTetromino(tetr1, game_field, false);
    moveHorTetromino(tetr1, game_field, false);
    for (int i = 0; i < FIGURE_WIDTH; i++) {
      ck_assert_int_eq(game_field[6][i + 4], kI);
    }
  }

  freeTetromino(&tetr1);
  free(game_field);
}
END_TEST

START_TEST(test_moveHorTetromino2) {
  Error_t err = kOk;
  Tetromino_t *tetr1 = createTetromino(&err);
  tetr1->name = kZ;
  fillFigureTetromino(tetr1->field->arr, tetr1->name);
  int **game_field = create2DimArr(HEIGHT, WIDTH, &err);
  cleanArr(HEIGHT, WIDTH, game_field);
  if (err == kOk) {
    tetr1->y = 0;
    tetr1->x = 0;
    pinUnpinTetromino(tetr1, game_field, true);

    ck_assert_int_eq(game_field[0][0], kZ);
    ck_assert_int_eq(game_field[0][1], kZ);
    ck_assert_int_eq(game_field[1][1], kZ);
    ck_assert_int_eq(game_field[1][2], kZ);

    moveHorTetromino(tetr1, game_field, true);

    ck_assert_int_eq(game_field[0][1], kZ);
    ck_assert_int_eq(game_field[0][2], kZ);
    ck_assert_int_eq(game_field[1][2], kZ);
    ck_assert_int_eq(game_field[1][3], kZ);

    moveHorTetromino(tetr1, game_field, false);
    moveHorTetromino(tetr1, game_field, false);

    ck_assert_int_eq(game_field[0][0], kZ);
    ck_assert_int_eq(game_field[0][1], kZ);
    ck_assert_int_eq(game_field[1][1], kZ);
    ck_assert_int_eq(game_field[1][2], kZ);
  }

  freeTetromino(&tetr1);
  free(game_field);
}
END_TEST

Suite *test_game_field(void) {
  Suite *s = suite_create("game_field");
  TCase *tc_core = tcase_create("game_field");

  tcase_add_test(tc_core, test_checkLineField1);
  tcase_add_test(tc_core, test_checkLineField2);

  tcase_add_test(tc_core, test_shiftDownField1);

  tcase_add_test(tc_core, test_moveHorTetromino1);
  tcase_add_test(tc_core, test_moveHorTetromino2);

  suite_add_tcase(s, tc_core);

  return s;
}
