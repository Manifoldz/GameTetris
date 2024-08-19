/**
 * @file tetris.h
 * @brief Header file for entry point for the game
 */

#ifndef TETRIS_H
#define TETRIS_H

#include "backend.h"
#include "frontend.h"

/**
 * @brief Checks the user input, calls timer and sends signal to fsm
 */
void inputHandler(void);

/**
 * @brief The main game loop
 */
void gameLoop(void);

#endif
