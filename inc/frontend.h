/**
 * @file frontend.h
 * @brief Header file for all frontend of the game
 */

#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>  // framework for terminal UI

#include "defines.h"
#include "fsm.h"
#include "objects.h"

/**
 * @brief Turns on all ncurses settings
 */
void ncursesInit(void);

/**
 * @brief Shows the terminal UI
 * @param info Pointer at info struct with information for rendering
 */
void renderGame(GameInfo_t *info);

/**
 * @brief Shows game field
 * @param field Pointer at 2d array with the main game field
 */
void printField(int **field);

/**
 * @brief Shows additional information box
 * @param info Pointer at info struct with information for rendering
 */
void printAddInfo(GameInfo_t *info);

/**
 * @brief Prints the start lay (welcome screen)
 */
void printStartLay(void);

/**
 * @brief Prints the game over lay (bye screen)
 * @param info Pointer at info struct with information for rendering
 */
void printGameOverLay(GameInfo_t *info);

/**
 * @brief Clean all position of the additional information box
 */
void cleanAddInfo(void);

/**
 * @brief Prints a box at top_y, bottom_y, left_x, right_x (borders included)
 * @param top_y Y-coordinate of the upper left corner of the box
 * @param left_x X-coordinate of the upper left corner of the box
 * @param width Width of the box
 * @param height Height of the box
 * @warning At the upper left corner of the box starts border of the box
 */
void printBox(int start_y, int start_x, int width, int height);

/**
 * @brief Prints a horizontal line at the y-row at [left_x;right_x) columns
 * @param y Row, where the line is printed
 * @param left_x Start position of the line
 * @param width Width of the line
 */
void printHLine(int y, int left_x, int width);

/**
 * @brief Prints a vertical line at the x-column at [top_y;bottom_y) rows
 * @param x Column, where the line is printed
 * @param top_y Start position of the line
 * @param height Length of the line
 */
void printVLine(int x, int top_y, int height);

#endif
