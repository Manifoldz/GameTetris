/**
 * @file test.h
 * @brief Header file for all tests
 */

#ifndef TESTS_H
#define TESTS_H

#include <check.h>  // for unit testing

#include "backend.h"

/**
 * @brief Tests for 2 dimensional array and matrix (Matrix_t) operations
 * @return Suite with testcases
 */
Suite *test_array2d_matrix(void);

/**
 * @brief Tests for tetrominos(Tetromino_t) operations
 * @return Suite with testcases
 */
Suite *test_tetromino(void);

/**
 * @brief Tests for game field operations
 * @return Suite with testcases
 */
Suite *test_game_field(void);

/**
 * @brief Tests for game info (GameInfo_t) and param (Params_t)
 * @return Suite with testcases
 */
Suite *test_param_gameinfo(void);

/**
 * @brief Tests for finite state machine operations
 * @return Suite with testcases
 */
Suite *test_fsm(void);

/**
 * @brief Anothers tests
 * @return Suite with testcases
 */
Suite *test_common(void);

/**
 * @brief Fills a matrix with the consecutive numbers 1,2,3,4...
 * @param matrix The matrix to fill
 */
void fillMatrix1toN(Matrix_t *matrix);

/**
 * @brief Prints a matrix for debugging
 * @param matrix The matrix to print
 */
void printMatrix(Matrix_t *matrix);

#endif
