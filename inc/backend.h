/**
 * @file backend.h
 * @brief Header file for all backend (except fsm) of the game
 */

#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>  // use everywhere
#include <stdio.h>    // for file proccessing
#include <stdlib.h>   // work with memory
#include <time.h>     // for random in generation figures

#include "defines.h"
#include "fsm.h"
#include "objects.h"

//
// Field
//

/**
 * @brief Shifts down all cells before low_border included, top line will be 0
 * @param low_border Number of last shifted row
 * @param game_field Pointer at target field
 */
void shiftDownField(int low_border, int **game_field);

/**
 * @brief Checkes that row is full / is empty in game field
 * @param num_row Number of checked row 0<=num_row<=19
 * @param game_field Pointer at analyzed field
 * @param is_full True if check is full line, false if check is empty line
 * @return true if row is full, false otherwise
 */
bool checkLineField(int num_row, int **game_field, bool is_full);

/**
 * @brief Pins/Unpins the tetromino at the game field
 * @param tetr Pointer at target tetromino
 * @param game_field Pointer at the target field
 * @param is_need_pin Put true if need to pin, otherwise false
 * @warning Width and height of tetromino field 4X4, game_field WIDTH X HEIGHT
 */
void pinUnpinTetromino(Tetromino_t *tetr, int **game_field, bool is_need_pin);

/**
 * @brief Showes is the tetromino above filled field (dropped at surface)
 * @param tetr Pointer at analyzed tetromino
 * @param game_field Pointer at the analyzed field
 * @return If dropped true, otherwise false
 * @warning Width and height of tetromino field 4X4, game_field WIDTH X HEIGHT
 */
bool isDroppedTetromino(Tetromino_t *tetr, int **game_field);

/**
 * @brief Showes is the tetromino out or intersectes filled position in field
 * @param tetr Pointer at analyzed tetromino
 * @param game_field Pointer at the analyzed field
 * @return If intersectes true, otherwise false
 * @warning Width and height of tetromino field 4X4, game_field WIDTH X HEIGHT
 */
bool isIntersectTetromino(Tetromino_t *tetr, int **game_field);

/**
 * @brief Try to move tetromino
 * @param tetr Pointer at analyzed tetromino
 * @param game_field Pointer at the analyzed field
 * @param is_to_right True - move right, false - move left
 */
void moveHorTetromino(Tetromino_t *tetr, int **game_field, bool is_to_right);

//
// Tetromino_t
//

/**
 * @brief 2D arr with started positions of all tetrominoes
 */
static const int set_tetromino[7][FIGURE_HEIGHT][FIGURE_WIDTH] = {
    {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{2, 0, 0, 0}, {2, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 0, 3, 0}, {3, 3, 3, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 4, 4, 0}, {0, 4, 4, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 5, 5, 0}, {5, 5, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 6, 0, 0}, {6, 6, 6, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{7, 7, 0, 0}, {0, 7, 7, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

/**
 * @brief Creates tetromino with size 4X4
 * @param err Pointer at err, in case err make *err = kErrMem or kErrIncorrect
 * @return pointer at allocated Tetromino_t or in case err NULL
 */
Tetromino_t *createTetromino(Error_t *err);

/**
 * @brief Frees allocated memory for Tetromino_t *tetr and make it NULL
 * @param tetr Pointer at the pointer at tetromino to free
 */
void freeTetromino(Tetromino_t **tetr);

/**
 * @brief Fills field of 2-dimen arr with patterns of start position tetromino
 * @param arr Pointer at 2-dimen arr, where need to put figure
 * @param new_name One of the type tetromino [1;7]
 */
void fillFigureTetromino(int **arr, NameTetr_t new_name);

/**
 * @brief Randomely generates next figure, filles by new figure, sets new name
 * @param next Pointer at Tetromino_t struct, where need to put new figure
 */
void genNextTetromino(Tetromino_t *next);

/**
 * @brief Rotate tetromino by the rules Super Rotation System
 * @param tetr Pointer at Tetromino_t struct, where need to rotate figure
 * @param is_clockwise True if rotate by clockwise, otherwise false
 * @details I-tetromino rotates 4X4 cells, O-tetromino not rotates, others 3X3
 */
void rotateTetromino(Tetromino_t *tetr, bool is_clockwise);

//
// 2DArray
//

/**
 * @brief Creates 2 dimension array with size rowsXcols
 * @param rows Number of rows in arr, int val >0
 * @param cols Number of columns in arr, int val >0
 * @param err Pointer at err, in case err make *err = kErrMem or kErrIncorrect
 * @return pointer at allocated 2 dimensional array or in case err NULL
 */
int **create2DimArr(int rows, int cols, Error_t *err);

/**
 * @brief Makes all elements of arr equal to 0
 * @param rows Number of rows
 * @param cols Number of columns
 * @param arr Pointer at 2dim-arr, which needed to clean
 */
void cleanArr(int rows, int cols, int **arr);

/**
 * @brief Inplace rotates area [y1x1:y2x2] in 2-dim arr by 90 deg clockwise
 * @param arr Pointer at 2 dimensional array
 * @param y1 Start y-coordinate in arr
 * @param x1 Start x-cordinate in arr
 * @param y2 End y-cordinate in arr
 * @param x2 End x-cordinate in arr
 * @param is_clockwise True if rotate by clockwise, otherwise false
 * @warning Be sure about size and coordinates! Maybe be segvault!
 */
void rotateArea(int **arr, int y1, int x1, int y2, int x2, bool is_clockwise);

/**
 * @brief Inplace transposes area [y1x1:y2x2] in 2-dim arr
 * @param arr Pointer at 2 dimensional array
 * @param y1 Start y-coordinate in arr
 * @param x1 Start x-cordinate in arr
 * @param y2 End y-cordinate in arr
 * @param x2 End x-cordinate in arr
 * @warning Be sure about size and coordinates! Maybe be segvault!
 */
void transposeArea(int **arr, int y1, int x1, int y2, int x2);

/**
 * @brief Inplace mirrors area [y1x1:y2x2] in 2-dim arr
 * @param arr Pointer at 2 dimensional array
 * @param y1 Start y-coordinate in arr
 * @param x1 Start x-cordinate in arr
 * @param y2 End y-cordinate in arr
 * @param x2 End x-cordinate in arr
 * @param is_horizont True if mirror by horizont, false if mirror by vertical
 * @warning Be sure about size and coordinates! Maybe be segvault!
 */
void mirrorArea(int **arr, int y1, int x1, int y2, int x2, bool is_horizont);

/**
 * @brief Checks parameters for creating array and Error_t
 * @param rows Checked number of rows
 * @param cols Checked number of cols
 * @param err Pointer at checked err, makes it kErrIncorrect if rows<=0||cols<=0
 * @return False if rows<=0||cols<=0 or err=NULL or *err != kOk, otherwise true
 */
bool isValidCreate(int rows, int cols, Error_t *err);

//
// Matrix_t
//

/**
 * @brief Creates matrix with size rowsXcols
 * @param rows Number of rows in matrix, int val >0
 * @param cols Number of columns in matrix, int val >0
 * @param err Pointer at err, in case err make *err = kErrMem or kErrIncorrect
 * @return Pointer at allocated Matrix_t or in case err NULL
 */
Matrix_t *createMatrix(int rows, int cols, Error_t *err);

/**
 * @brief Frees allocated memory for matrix and make it NULL
 * @param matrix Pointer at pointer at the matrix to free
 */
void freeMatrix(Matrix_t **matrix);

/**
 * @brief Equals all elements of destination matrix to elements of source matrix
 * @param src Pointer at the source matrix
 * @param dst Pointer at the destination matrix
 */
void copyMatrix(Matrix_t *src, Matrix_t *dst);

//
// GameInfo_t
//

/**
 * @brief Creates object of GameInfo_t
 * @param err Pointer at err, in case err make *err = kErrMem or kErrIncorrect
 * @return Pointer at allocated GameInfo_t or in case err NULL
 */
GameInfo_t *createGameInfo(Error_t *err);

void restartGameInfo(GameInfo_t *info);

/**
 * @brief Frees all allocated memory for GameInfo_t
 * @param info Pointer at pointer at the GameInfo_t to free
 */
void freeGameInfo(GameInfo_t **info);

/**
 * @brief Checks full lines, clean them, displace field, gets score/level/speed
 * @param tetr Pointer at current Tetromino_t
 * @param info Pointer at GameInfo_t
 */
void processScoreLevelSpeed(Tetromino_t *tetr, GameInfo_t *info);

/**
 * @brief Gets data for frontend
 * @details Singleton pattern used for getting through Param_t
 * @warning Frees only once
 */
GameInfo_t updateCurrentState();

//
// Param_t
//

/**
 * @brief Create/Gets Singletone Params_t struct with all params of the game
 * @warning In case err, frees itself, check only NULL return
 * @return Pointer at allocated Params_t or in case err NULL
 */
Params_t *getParamInstance(void);

/**
 * @brief Frees Singletone Params_t struct with all params of the game
 * @warning Frees only once!
 */
void freeParamInstance(void);

//
// Common
//

/**
 * @brief Returns timer state for automatically move down tetromino
 * @return Returns true if time is up, else false
 */
bool isTimeUp(void);

/**
 * @brief Load/save record to/from the file
 * @param is_save True if need to save record, else load from file
 * @param record Pointer at record number
 * @param filename Filename of file
 */
void loadSaveRecord(bool is_save, int *record, const char *filename);

/**
 * @brief Allocates void memory
 * @param size Size_t in bytes
 * @param err Pointer at Error_t, if err make *err = kErrMem or kErrIncorrect
 * @return Void * memory with size or NULL in case malloc Error_t
 * @warning Err must be kOk while call, also don't forget to check err code!
 */
void *safeMalloc(size_t size, Error_t *err);

/**
 * @brief Interchanges value between 2 int pointer
 * @param a Pointer at first int value
 * @param b Pointer at second int value
 */
void swap(int *a, int *b);

/**
 * @brief Divides dividend by divisor with round to up
 * @param dividend What is being divided
 * @param divisor By what divided
 * @return Calculated value
 */
int upDivide(int dividend, int divisor);

#endif
