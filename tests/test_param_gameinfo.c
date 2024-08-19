#include "../inc/test.h"

START_TEST(test_createGameInfo1) {
  Error_t err = kOk;
  GameInfo_t *info = createGameInfo(&err);
  if (err == kOk) {
    ck_assert_ptr_nonnull(info);
    ck_assert_ptr_nonnull(info->field);
    ck_assert_int_eq(info->score, 0);
    ck_assert_ptr_null(info->next);
    ck_assert_int_eq(info->pause, START_PAUSE);
    ck_assert_int_eq(info->level, 1);
  }

  freeGameInfo(&info);
}
END_TEST

START_TEST(test_createGameInfo2) {
  GameInfo_t *info = createGameInfo(NULL);
  ck_assert_ptr_null(info);
  Error_t err = kErrMem;
  info = createGameInfo(&err);
  ck_assert_ptr_null(info);
  freeGameInfo(&info);
}
END_TEST

START_TEST(test_getParamInstance1) {
  Params_t *p = getParamInstance();
  if (p != NULL) {
    ck_assert_ptr_nonnull(p->info);
    ck_assert_ptr_nonnull(p->cur_tetr);
    ck_assert_ptr_nonnull(p->next_tetr);
    ck_assert_ptr_nonnull(p->info->next);
    ck_assert_ptr_eq(p->info->next, p->next_tetr->field->arr);
    GameInfo_t info = updateCurrentState();
    ck_assert_ptr_nonnull(info.next);
    ck_assert_int_eq(info.pause, START_PAUSE);

    ck_assert_int_eq(isTimeUp(), 0);
    p->state = MOVING;
    p->info->pause = NO_PAUSE;
    ck_assert_int_eq(isTimeUp(), 1);
    p->info->speed = SPEED_PROCESS(MAX_LEVEL);
    ck_assert_int_eq(isTimeUp(), 0);

    unsigned long long waste_time = 0;

    while (!isTimeUp()) {
      waste_time++;
    }

    printf("waste time counted%lld\n", waste_time);

    // p->state = EXIT;
    // info = updateCurrentState();
    // ck_assert_ptr_null(info.field);
  }
  // freeParamInstance();
}
END_TEST

START_TEST(test_processScoreLevelSpeed1) {
  Error_t err = kOk;
  Tetromino_t *tetr = createTetromino(&err);
  GameInfo_t *info = createGameInfo(&err);

  if (err == kOk) {
    tetr->name = kI;
    tetr->y = HEIGHT - 2;
    tetr->x = 0;
    for (int i = 4; i < WIDTH; i++) {
      info->field[HEIGHT - 1][i] = 1;
    }
    info->field[HEIGHT - 2][7] = 1;
    fillFigureTetromino(tetr->field->arr, tetr->name);
    pinUnpinTetromino(tetr, info->field, true);
    processScoreLevelSpeed(tetr, info);
    ck_assert_int_eq(info->field[HEIGHT - 1][7], 1);
    ck_assert_int_eq(info->score, SCORE_PROCESS(0));
    int save_score = info->score;
    ck_assert_int_eq(info->level, LEVEL_PROCESS(info->score));
    ck_assert_int_eq(info->speed, SPEED_PROCESS(info->level));
    rotateTetromino(tetr, true);

    tetr->y = 2;
    info->field[0][7] = 1;

    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < WIDTH; j++) {
        info->field[i + 2][j] = 1;
      }
    }
    pinUnpinTetromino(tetr, info->field, true);
    processScoreLevelSpeed(tetr, info);
    ck_assert_int_eq(info->field[2][7], 1);
    ck_assert_int_eq(info->score, save_score + SCORE_PROCESS(SCORE_PROCESS(0)));
    ck_assert_int_eq(info->level, LEVEL_PROCESS(info->score));
    ck_assert_int_eq(info->speed, SPEED_PROCESS(info->level));
  }

  freeTetromino(&tetr);
  freeGameInfo(&info);
}

Suite *test_param_gameinfo(void) {
  Suite *s = suite_create("param_gameinfo");
  TCase *tc_core = tcase_create("param_gameinfo");

  tcase_add_test(tc_core, test_getParamInstance1);

  tcase_add_test(tc_core, test_createGameInfo1);
  tcase_add_test(tc_core, test_createGameInfo2);

  tcase_add_test(tc_core, test_processScoreLevelSpeed1);

  suite_add_tcase(s, tc_core);

  return s;
}
