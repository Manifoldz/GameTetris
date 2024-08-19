#include "../../inc/backend.h"

bool checkLineField(int num_row, int **game_field, bool is_full) {
  bool res = true;
  for (int i = 0; i < WIDTH && res; i++) {
    res = (game_field[num_row][i] > 0) == is_full;
  }
  return res;
}

void shiftDownField(int low_border, int **game_field) {
  for (int i = low_border; i >= 0; i--) {
    for (int j = 0; j < WIDTH; j++) {
      if (i == 0) {
        game_field[i][j] = 0;
      } else {
        game_field[i][j] = game_field[i - 1][j];
      }
    }
  }
}

void pinUnpinTetromino(Tetromino_t *tetr, int **game_field, bool is_need_pin) {
  int **arr = tetr->field->arr;
  for (int i = tetr->y; i < tetr->y + FIGURE_HEIGHT; i++) {
    for (int j = tetr->x; j < tetr->x + FIGURE_WIDTH; j++) {
      if (arr[i - tetr->y][j - tetr->x] > 0 && i >= 0 && i < HEIGHT && j >= 0 &&
          j < WIDTH) {
        game_field[i][j] = is_need_pin * tetr->name;
      }
    }
  }
}

bool isDroppedTetromino(Tetromino_t *tetr, int **game_field) {
  bool is_dropped = false;
  int **arr = tetr->field->arr;
  for (int i = tetr->y; i < tetr->y + FIGURE_HEIGHT && !is_dropped; i++) {
    for (int j = tetr->x; j < tetr->x + FIGURE_WIDTH && !is_dropped; j++) {
      if (i >= 0 && arr[i - tetr->y][j - tetr->x] > 0) {
        if (i == HEIGHT - 1 || game_field[i + 1][j] > 0) {
          is_dropped = true;
        }
      }
    }
  }
  return is_dropped;
}

bool isIntersectTetromino(Tetromino_t *tetr, int **game_field) {
  bool is_intersect = false;
  int **arr = tetr->field->arr;
  for (int i = tetr->y; i < tetr->y + FIGURE_HEIGHT && !is_intersect; i++) {
    for (int j = tetr->x; j < tetr->x + FIGURE_WIDTH && !is_intersect; j++) {
      if (i >= 0 && i < HEIGHT && j >= 0 && j < WIDTH) {
        is_intersect = game_field[i][j] && arr[i - tetr->y][j - tetr->x];
      } else if (i >= HEIGHT || j < 0 || j >= WIDTH) {
        is_intersect = arr[i - tetr->y][j - tetr->x];
      }
    }
  }
  return is_intersect;
}

void moveHorTetromino(Tetromino_t *tetr, int **game_field, bool is_to_right) {
  pinUnpinTetromino(tetr, game_field, false);
  int move = is_to_right ? 1 : -1;
  tetr->x += move;
  if (isIntersectTetromino(tetr, game_field)) {
    tetr->x -= move;
  }
  pinUnpinTetromino(tetr, game_field, true);
}