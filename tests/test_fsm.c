#include "../inc/test.h"

START_TEST(test_userInput1) {
  Params_t *p = getParamInstance();
  if (p != NULL) {
    userInput(Down, false);
    ck_assert_int_eq(p->cur_tetr->name, 0);
    ck_assert_int_ne(p->next_tetr->name, 0);
    p->info->pause = START_PAUSE;
  }
}
END_TEST

START_TEST(test_fsm1) {
  Params_t *p = getParamInstance();
  if (p != NULL) {
    restart(p);
    p->next_tetr->name = kI;
    fillFigureTetromino(p->next_tetr->field->arr, p->next_tetr->name);
    spawn(p);
    ck_assert_int_ne(p->cur_tetr->name, 0);
    ck_assert_int_eq(p->cur_tetr->y, SPAWN_Y_COORD);
    ck_assert_int_eq(p->cur_tetr->x, SPAWN_X_COORD);
    ck_assert_int_eq(p->state, MOVING);
    ck_assert_int_eq(p->info->pause, NO_PAUSE);

    pausehandle(p);
    ck_assert_int_eq(p->state, PAUSE);
    ck_assert_int_eq(p->info->pause, SIMPLE_PAUSE);
    pausehandle(p);
    ck_assert_int_eq(p->state, MOVING);
    ck_assert_int_eq(p->info->pause, NO_PAUSE);

    p->cur_tetr->x = 0;
    p->info->field[SPAWN_Y_COORD + 3][0] = 1;
    // 0 0 0 0 0 0 ....
    // 1 0 0 0 0 0 ....
    movedown(p);
    ck_assert_int_eq(p->state, MOVING);
    ck_assert_int_eq(p->cur_tetr->y, SPAWN_Y_COORD + 1);
    // for (int i = 0; i < WIDTH; i++) {
    //   for (int j = 0; j < HEIGHT; j++) {
    //     printf("%2d ", p->info->field[i][j]);
    //   }
    //   putchar('\n');
    // }
    // 1 1 1 1 0 0 ....
    // 1 0 0 0 0 0 ....
    movedown(p);
    ck_assert_int_eq(p->state, ATTACHING);
    ck_assert_int_eq(p->cur_tetr->y, SPAWN_Y_COORD + 1);
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(p->info->field[0][i + 0], 1);
    }
    // 1 1 1 1 0 0 ....
    // 1 0 0 0 0 0 ....
    moveright(p);
    ck_assert_int_eq(p->cur_tetr->x, 1);
    ck_assert_int_eq(p->info->field[0][0], 0);
    // 0 1 1 1 1 0 ....
    // 1 0 0 0 0 0 ....
    movedown(p);
    ck_assert_int_eq(p->state, MOVING);
    ck_assert_int_eq(p->cur_tetr->y, SPAWN_Y_COORD + 2);
    ck_assert_int_eq(p->info->field[0][2], 0);
    // 0 0 0 0 0 0 ....
    // 1 1 1 1 1 0 ....
    moveleft(p);
    ck_assert_int_eq(p->cur_tetr->x, 1);
    ck_assert_int_eq(p->cur_tetr->y, SPAWN_Y_COORD + 2);
    p->info->field[SPAWN_Y_COORD + 3][0] = 0;
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(p->info->field[1][1 + i], 1);
    }
    // 0 0 0 0 0 0 ....
    // 1 1 1 1 1 0 ....
    p->info->field[SPAWN_Y_COORD + 3][0] = 0;
    // 0 0 0 0 0 0 ....
    // 0 1 1 1 1 0 ....
    moveleft(p);
    ck_assert_int_eq(p->cur_tetr->x, 0);
    ck_assert_int_eq(p->cur_tetr->y, SPAWN_Y_COORD + 2);
    ck_assert_int_eq(p->info->field[1][4], 0);
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(p->info->field[1][i], 1);
    }
    // 0 0 0 0 0 0 ....
    // 1 1 1 1 0 0 ....

    rotate(p);
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(p->info->field[i][2], 1);
    }
    // 0 0 1 0 0 0 ....
    // 0 0 1 0 0 0 ....
    // 0 0 1 0 0 0 ....
    // 0 0 1 0 0 0 ....
    p->info->field[SPAWN_Y_COORD + 4][1] = 1;
    // 0 0 1 0 0 0 ....
    // 0 0 1 0 0 0 ....
    // 0 1 1 0 0 0 ....
    // 0 0 1 0 0 0 ....
    rotate(p);
    p->info->field[SPAWN_Y_COORD + 4][1] = 0;
    // 0 0 1 0 0 0 ....
    // 0 0 1 0 0 0 ....
    // 0 0 1 0 0 0 ....
    // 0 0 1 0 0 0 ....
    rotate(p);
    rotate(p);
    rotate(p);

    // 0 0 0 0 0 0 ....
    // 1 1 1 1 0 0 ....
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(p->info->field[1][i], 1);
    }

    attach(p);
    ck_assert_int_eq(p->state, SPAWN);
    pinUnpinTetromino(p->cur_tetr, p->info->field, false);
    p->cur_tetr->x = 0;
    p->cur_tetr->y = SPAWN_Y_COORD + 1;
    pinUnpinTetromino(p->cur_tetr, p->info->field, true);
    // 1 1 1 1 0 0 ....
    // 0 0 0 0 0 0 ....
    ck_assert_int_eq(checkLineField(0, p->info->field, false), 0);
    attach(p);

    ck_assert_int_eq(p->state, START);
    ck_assert_int_eq(p->info->pause, END_PAUSE);

    p->info->score = 2000;
    p->info->high_score = 1000;
    save(p);
    ck_assert_int_eq(p->info->high_score, 2000);
    escape(p);
    ck_assert_int_eq(p->state, EXIT);
    GameInfo_t info = updateCurrentState();
    ck_assert_ptr_null(info.field);
  }
  freeParamInstance();
}
END_TEST

Suite *test_fsm(void) {
  Suite *s = suite_create("fsm");
  TCase *tc_core = tcase_create("fsm");

  tcase_add_test(tc_core, test_userInput1);
  tcase_add_test(tc_core, test_fsm1);

  suite_add_tcase(s, tc_core);

  return s;
}
