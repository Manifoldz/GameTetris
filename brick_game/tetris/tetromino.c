#include "../../inc/backend.h"

Tetromino_t *createTetromino(Error_t *err) {
  if (!err || *err != kOk) {
    return NULL;
  }
  Tetromino_t *tetr = (Tetromino_t *)safeMalloc(sizeof(Tetromino_t), err);
  if (*err == kOk) {
    tetr->field = createMatrix(FIGURE_HEIGHT, FIGURE_WIDTH, err);
    if (*err == kOk) {
      tetr->name = 0;
      tetr->y = 0;
      tetr->x = 0;
    } else {
      freeTetromino(&tetr);
    }
  }
  return tetr;
}

void freeTetromino(Tetromino_t **tetr) {
  if (tetr) {
    if (*tetr) {
      freeMatrix(&(*tetr)->field);
    }
    free(*tetr);
    *tetr = NULL;
  }
}

void rotateTetromino(Tetromino_t *tetr, bool is_clockwise) {
  int rows = tetr->field->rows;
  int cols = tetr->field->cols;
  if (tetr->name == kI) {
    rotateArea(tetr->field->arr, 0, 0, rows - 1, cols - 1, is_clockwise);
  } else if (tetr->name != kO) {
    rotateArea(tetr->field->arr, 0, 0, rows - 2, cols - 2, is_clockwise);
  }
}

void genNextTetromino(Tetromino_t *next) {
  next->name = 1 + rand() % 7;
  fillFigureTetromino(next->field->arr, next->name);
}

void fillFigureTetromino(int **arr, NameTetr_t new_name) {
  if (arr && new_name >= 1 && new_name <= 7) {
    for (int i = 0; i < FIGURE_HEIGHT; i++) {
      for (int j = 0; j < FIGURE_WIDTH; j++) {
        arr[i][j] = set_tetromino[new_name - 1][i][j];
      }
    }
  }
}