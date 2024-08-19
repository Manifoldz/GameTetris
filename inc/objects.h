/**
 * @file objects.h
 * @brief Header file for all used objects (except fsm)
 */

#ifndef OBJECTS_H
#define OBJECTS_H

/**
 * @brief Names of all possible types of tetrominos
 */
typedef enum { kI = 1, kJ, kL, kO, kS, kT, kZ } NameTetr_t;

/**
 * @brief Names of all possible error
 */
typedef enum { kOk = 0, kErrIncorrect, kErrCalc, kErrMem = 4 } Error_t;

/**
 * @brief Struct with matrix
 * @details cols - int number of columns > 0
 * @details rows - int number of rows > 0
 */
typedef struct {
  int **arr;
  int rows;
  int cols;
} Matrix_t;

/**
 * @brief Struct with tetromino info
 * @details name - name of the type tetromino, int value from 1 to 7
 * @details field - pointer at matrix_t FIGURE_HEIGHT X FIGURE_WIDTH
 * @details y - coordinate (vertical) of the field[0][0], int val from -2 to 18
 * @details x - coordinate (horizont) of the field[0][0], int val from -2 to 8
 */
typedef struct {
  NameTetr_t name;
  Matrix_t *field;
  int y;
  int x;
} Tetromino_t;

/**
 * @brief Struct with all necessary  info of the game for frontend
 * @details field - pointer at game field 2dim arr HEIGHT*WIDTH
 * @details next - pointer at next figure  2dim arr FIGURE_HEIGHT X FIGURE_WIDTH
 * @details score - score of the game
 * @details high_score - local record of the game
 * @details level - level of the game, int val from START_LEVEL to MAX_LEVEL
 * @details speed - speed of the game
 * @details pause - pause of the game, (0-no pause, 1-pause, 2-start, 3-end)
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif
