#include "../../inc/backend.h"

void spawn(Params_t *param) {
  copyMatrix(param->next_tetr->field, param->cur_tetr->field);
  param->cur_tetr->name = param->next_tetr->name;
  param->cur_tetr->y = SPAWN_Y_COORD;
  param->cur_tetr->x = SPAWN_X_COORD;
  genNextTetromino(param->next_tetr);
  param->state = MOVING;
  if (param->info->pause != NO_PAUSE) {
    param->info->pause = NO_PAUSE;
    param->info->score = 0;
  }
}

void pausehandle(Params_t *param) {
  if (param->state == PAUSE) {
    param->info->pause = NO_PAUSE;
    param->state = MOVING;
  } else {
    param->info->pause = SIMPLE_PAUSE;
    param->state = PAUSE;
  }
}

void escape(Params_t *param) {
  save(param);
  param->state = EXIT;
}

void moveleft(Params_t *param) {
  moveHorTetromino(param->cur_tetr, param->info->field, false);
  param->state = MOVING;
}

void moveright(Params_t *param) {
  moveHorTetromino(param->cur_tetr, param->info->field, true);
  param->state = MOVING;
}

void movedown(Params_t *param) {
  pinUnpinTetromino(param->cur_tetr, param->info->field, false);
  if (isDroppedTetromino(param->cur_tetr, param->info->field)) {
    param->state = ATTACHING;
  } else {
    param->cur_tetr->y++;
    param->state = MOVING;
  }
  pinUnpinTetromino(param->cur_tetr, param->info->field, true);
}

void attach(Params_t *param) {
  processScoreLevelSpeed(param->cur_tetr, param->info);
  save(param);
  if (!checkLineField(0, param->info->field, false) ||
      param->info->level > MAX_LEVEL) {
    restart(param);
  } else {
    param->state = SPAWN;
  }
}

void rotate(Params_t *param) {
  pinUnpinTetromino(param->cur_tetr, param->info->field, false);
  rotateTetromino(param->cur_tetr, true);
  if (isIntersectTetromino(param->cur_tetr, param->info->field)) {
    rotateTetromino(param->cur_tetr, false);
  }
  pinUnpinTetromino(param->cur_tetr, param->info->field, true);
  param->state = MOVING;
}

void save(Params_t *param) {
  if (param->info->score > param->info->high_score) {
    loadSaveRecord(true, &param->info->score, TETRIS_RECORD_FILE);
    param->info->high_score = param->info->score;
  }
}

void restart(Params_t *param) {
  restartGameInfo(param->info);
  param->info->pause = END_PAUSE;
  param->state = START;
}

void userInput(UserAction_t action, bool hold) {
  hold = hold;  // plug
  Params_t *param = getParamInstance();
  func fsm_act = fsm_table[param->state][action];
  if (fsm_act != NULL) {
    fsm_act(param);
  }
}
