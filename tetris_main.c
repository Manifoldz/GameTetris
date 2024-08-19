#include "inc/tetris.h"

/**
 * @todo delete unistd.h
 */
#include <unistd.h>

int main(void) {
  ncursesInit();
  srand(time(NULL));
  gameLoop();
  flushinp();  // clear stdin after game
  endwin();    // turn off window ncurses
  return 0;
}

void gameLoop(void) {
  GameInfo_t info = {0};
  do {
    info = updateCurrentState();
    if (info.field != NULL) {
      renderGame(&info);
      inputHandler();
    }
  } while (info.field != NULL);
}

void inputHandler(void) {
  bool hold = false;           // plug
  UserAction_t action = Down;  // default

  if (isTimeUp()) {
    userInput(Down, hold);
  } else {
    flushinp();
    int key = getch();
    bool is_recognized = true;
    if (key == KEY__ENTER)
      action = Start;
    else if (key == KEY_PAUSE)
      action = Pause;
    else if (key == KEY_ESCAPE)
      action = Terminate;
    else if (key == KEY_LEFT)
      action = Left;
    else if (key == KEY_RIGHT)
      action = Right;
    else if (key == KEY_UP)
      action = Up;
    else if (key == KEY_DOWN)
      action = Down;
    else if (key == KEY_SPACE)
      action = Action;
    else
      is_recognized = false;

    if (is_recognized) {
      userInput(action, hold);
    }
  }
}