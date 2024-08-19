/**
 * @file defines.h
 * @brief Header file for all Macros
 */

#ifndef DEFINES_H
#define DEFINES_H

/*

COORDINATES AND SIZE

*/
/**
 * @brief Offset from borders of terminal
 */
#define OFFSET 2
/**
 * @brief Width of the game field (coordinates)
 */
#define WIDTH 10
/**
 * @brief Width of the game field for rendering (chars)
 */
#define VIEW_WIDTH WIDTH * 2
/**
 * @brief Height of the game field (coordinates)
 */
#define HEIGHT 20

/*

Additional information window

*/
/**
 * @brief The start y-coordinate of the additional information window
 */
#define START_INFO_Y OFFSET + 0
/**
 * @brief The start x-coordinate of the additional information window
 */
#define START_INFO_X OFFSET + VIEW_WIDTH + 3
/**
 * @brief Witdth of the additional information window
 */
#define INFO_WIDTH VIEW_WIDTH / 2
/**
 * @brief Height of the additional information window
 */
#define INFO_HEIGHT HEIGHT

/*

TETROMINO PARAMETERS

*/
/**
 * @brief Width of the tetromino figure field
 */
#define FIGURE_WIDTH 4
/**
 * @brief Height of the tetromino figure field
 */
#define FIGURE_HEIGHT 4
/**
 * @brief Start Y-position of the spawned tetromino
 */
#define SPAWN_Y_COORD -2
/**
 * @brief Start X-position of the spawned tetromino
 */
#define SPAWN_X_COORD (WIDTH - FIGURE_WIDTH) / 2

/*

CODES OF CONTROLLER KEYS

*/

/**
 * @brief Code for "p" key - pause
 */
#define KEY_PAUSE 'p'
/**
 * @brief Code for "Esc" - exit the game
 */
#define KEY_ESCAPE 27
/**
 * @brief Code for "Space" - rotate the tetromino
 */
#define KEY_SPACE ' '
/**
 * @brief Code for "Enter" - start/continue the game
 */
#define KEY__ENTER '\n'

/*

SCORE, LEVEL AND SPEED PROCESSING

*/

/**
 * @brief Waiting user input in milliseconds
 */
#define TIMEOUT 50
/**
 * @brief Formula for increase score for each full line
 */
#define SCORE_PROCESS(score) score * 2 + 100
/**
 * @brief Formula for calculating level
 */
#define LEVEL_PROCESS(score) score / 600 + 1
/**
 * @brief Max level of the game
 */
#define MAX_LEVEL 10
/**
 * @brief Formula for calculating speed
 */
#define SPEED_PROCESS(level) level
/**
 * @brief Formula for calculating waiting time for 1 falling down
 */
#define WAITING_TIME(speed) 1 - (speed * 0.08)  // seconds

/*

PAUSE MEANINGS (CODES FOR FRONTEND PART OF GAME)

*/
/**
 * @brief Code no any pause
 */
#define NO_PAUSE 0
/**
 * @brief Code for just regular pause
 */
#define SIMPLE_PAUSE 1
/**
 * @brief Code for pause with cause of start the game
 */
#define START_PAUSE 2
/**
 * @brief Code for pause with cause of game over
 */
#define END_PAUSE 3

/*

ANOTHERS

*/
/**
 * @brief File for reading/writing the game record
 */
#define TETRIS_RECORD_FILE "./build/.tetris_record.txt"

#endif
