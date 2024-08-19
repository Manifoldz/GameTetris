/**
 * @file fsm.h
 * @brief Header file for all functions related to finite state machine
 */

#ifndef FSM_H
#define FSM_H

#include "objects.h"

/**
 * @brief Describes all allowed user choice (action)
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @brief Describes all possible the game state
 */
typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  PAUSE,
  SHIFTING,
  ATTACHING,
  EXIT,
} TetrisState_t;

/**
 * @brief Struct with all information about game
 * @details info - pointer at game info for rendering of game
 * @details cur_tetr - pointer at current tetromino
 * @details next_tetr - pointer at next tetromino
 * @details state - current game state
 */
typedef struct {
  GameInfo_t *info;
  Tetromino_t *cur_tetr;
  Tetromino_t *next_tetr;
  TetrisState_t state;
} Params_t;

/**
 * @brief Typedef for function pointer for fsm realization
 */
typedef void (*func)(Params_t *param);

/**
 * @brief Makes cur tetr.=next tetr., sets at the start position, gen next tetr
 * @param param - pointer at main struct with all information about game
 */
void spawn(Params_t *param);

/**
 * @brief Sets state "PAUSE" or "MOVING" in turn
 * @param param - pointer at main struct with all information about game
 */
void pausehandle(Params_t *param);

/**
 * @brief Saves the game and sets state "EXIT"
 * @param param - pointer at main struct with all information about game
 */
void escape(Params_t *param);

/**
 * @brief If possible, moves current tetromino to the left
 * @param param - pointer at main struct with all information about game
 */
void moveleft(Params_t *param);

/**
 * @brief If possible, moves current tetromino to the right
 * @param param - pointer at main struct with all information about game
 */
void moveright(Params_t *param);

/**
 * @brief If possible, moves down tetromino, if not sets state "ATTACHING"
 * @param param - pointer at main struct with all information about game
 */
void movedown(Params_t *param);

/**
 * @brief Checks full lines and end game, update score, sets "START" or "SPAWN"
 * @param param - pointer at main struct with all information about game
 */
void attach(Params_t *param);

/**
 * @brief Rotates tetromino, if possible
 * @param param - pointer at main struct with all information about game
 */
void rotate(Params_t *param);

/**
 * @brief If new record - saves that into the file
 * @param param - pointer at main struct with all information about game
 */
void save(Params_t *param);

/**
 * @brief Clears field and sets state "START"
 * @param param - pointer at main struct with all information about game
 */
void restart(Params_t *param);

/**
 * @brief 2D arr with function pointers for fsm realization
 */
static const func fsm_table[7][8] = {
    {spawn, NULL, escape, NULL, NULL, NULL, NULL, NULL},
    {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},
    {NULL, pausehandle, escape, moveleft, moveright, NULL, movedown, rotate},
    {pausehandle, NULL, escape, NULL, NULL, NULL, NULL, NULL},
    {movedown, movedown, movedown, movedown, movedown, movedown, movedown},
    {attach, attach, attach, attach, attach, attach, attach, attach},
    {escape, escape, escape, escape, escape, escape, escape}};

/**
 * @brief Function for change game state, calls from interface
 * @param action - user action (trigger for fsm)
 * @param hold - shows if the key is held down (trigger for fsm)
 */
void userInput(UserAction_t action, bool hold);

#endif
