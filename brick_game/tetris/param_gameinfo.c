#include "../../inc/backend.h"

Params_t *getParamInstance(void) {
  static Params_t *instance = NULL;
  if (instance == NULL) {
    Error_t err = kOk;
    instance = (Params_t *)safeMalloc(sizeof(Params_t), &err);
    if (err == kOk) {
      instance->info = createGameInfo(&err);
      instance->cur_tetr = createTetromino(&err);
      instance->next_tetr = createTetromino(&err);
      instance->state = START;
      if (err != kOk) {
        freeTetromino(&instance->cur_tetr);
        freeTetromino(&instance->next_tetr);
        freeGameInfo(&instance->info);
        free(instance);
        instance = NULL;
      } else {
        genNextTetromino(instance->next_tetr);
        instance->info->next = instance->next_tetr->field->arr;
      }
    }
  }

  return instance;
}

void freeParamInstance(void) {
  static bool is_freed = false;
  if (!is_freed) {
    Params_t *instance = getParamInstance();
    if (instance) {
      freeTetromino(&instance->cur_tetr);
      freeTetromino(&instance->next_tetr);
      freeGameInfo(&instance->info);
      free(instance);
      is_freed = true;
    }
  }
}

GameInfo_t *createGameInfo(Error_t *err) {
  if (!err) {
    return NULL;
  }
  GameInfo_t *info = (GameInfo_t *)safeMalloc(sizeof(GameInfo_t), err);
  if (*err == kOk) {
    info->field = create2DimArr(HEIGHT, WIDTH, err);
    if (*err == kOk) {
      info->score = 0;
      info->next = NULL;
      info->high_score = 0;
      info->pause = START_PAUSE;  // for frontend recognize welcome banner
      restartGameInfo(info);
      loadSaveRecord(false, &(info->high_score), TETRIS_RECORD_FILE);
    } else {
      free(info);
      info = NULL;
    }
  }
  return info;
}

void restartGameInfo(GameInfo_t *info) {
  /* While restart the game score maybe != 0, because frontend
  need to recognize new record, new record for front if cur_score == record
   */
  info->level = LEVEL_PROCESS(0);
  info->speed = SPEED_PROCESS(info->level);
  cleanArr(HEIGHT, WIDTH, info->field);
}

void freeGameInfo(GameInfo_t **info) {
  if (info) {
    if (*info) {
      free((*info)->field);
      (*info)->field = NULL;
      (*info)->next = NULL;
    }
    free(*info);
    *info = NULL;
  }
}

void processScoreLevelSpeed(Tetromino_t *tetr, GameInfo_t *info) {
  int score = 0;
  for (int i = tetr->y; i < tetr->y + FIGURE_HEIGHT; i++) {
    if (i > 0 && i < HEIGHT && checkLineField(i, info->field, true)) {
      shiftDownField(i, info->field);
      score = SCORE_PROCESS(score);
    }
  }
  info->score += score;
  info->level = LEVEL_PROCESS(info->score);
  info->speed = SPEED_PROCESS(info->level);
}

GameInfo_t updateCurrentState() {
  GameInfo_t info = {0};
  Params_t *instance = getParamInstance();
  if (instance) {
    info = *instance->info;
    if (instance->state == EXIT) {
      freeParamInstance();
      info.field = NULL;
    }
  }
  return info;
}

bool isTimeUp(void) {
  static struct timespec start = {0, 0};
  static double time_failing = 0;
  bool is_time_up = false;
  Params_t *param = getParamInstance();
  if (param->info->pause == NO_PAUSE) {
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_failing +=
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    if (time_failing > WAITING_TIME(param->info->speed)) {
      is_time_up = true;
      time_failing = 0;
    }
  }
  if (param->state == MOVING) {
    clock_gettime(CLOCK_MONOTONIC, &start);
  }
  return is_time_up;
}
