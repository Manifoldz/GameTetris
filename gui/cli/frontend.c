#include "../../inc/frontend.h"

void ncursesInit(void) {
  initscr();             // turn on window ncurses
  noecho();              // ignore show input
  curs_set(0);           // invisible cursor
  keypad(stdscr, TRUE);  // mode process spec keys (arrows)
  start_color();         // enable colors

  init_pair(1, COLOR_BLACK, COLOR_RED);
  init_pair(2, COLOR_BLACK, COLOR_CYAN);
  init_pair(3, COLOR_BLACK, COLOR_YELLOW);
  init_pair(4, COLOR_BLACK, COLOR_WHITE);
  init_pair(5, COLOR_BLACK, COLOR_GREEN);
  init_pair(6, COLOR_BLACK, COLOR_BLUE);
  init_pair(7, COLOR_BLACK, COLOR_MAGENTA);

  timeout(TIMEOUT);  // waiting user input while getch()
}

void renderGame(GameInfo_t *info) {
  if (info->pause == START_PAUSE) {
    printStartLay();
  } else if (info->pause == END_PAUSE) {
    printGameOverLay(info);
  } else {
    printField(info->field);
    printAddInfo(info);
  }
  refresh();
}

void cleanAddInfo(void) {
  for (int i = START_INFO_Y; i < INFO_HEIGHT + OFFSET + 2; i++) {
    mvprintw(i, START_INFO_X, "            ");
  }
}

void printGameOverLay(GameInfo_t *info) {
  cleanAddInfo();
  printField(info->field);
  mvprintw(OFFSET + 6, OFFSET + 6, "Game over!");
  if (info->score == info->high_score) {
    mvprintw(OFFSET + 8, OFFSET + 4, "Congratulation!");
    mvprintw(OFFSET + 9, OFFSET + 5, "A new record!");
    mvprintw(OFFSET + 10, OFFSET + 6, "%6d", info->high_score);
  } else {
    mvprintw(OFFSET + 9, OFFSET + 4, "Score %6d", info->score);
    mvprintw(OFFSET + 10, OFFSET + 4, "Record %6d", info->high_score);
  }
  mvprintw(OFFSET + 12, OFFSET + 2, "Enter - the repeat");
}

void printField(int **field) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      attron(COLOR_PAIR(field[i][j]));
      mvprintw(OFFSET + i + 1, OFFSET + 2 * j + 1, "  ");
      attroff(COLOR_PAIR(field[i][j]));
    }
  }
}

void printAddInfo(GameInfo_t *info) {
  // box add info
  printBox(START_INFO_Y - OFFSET, START_INFO_X - OFFSET, INFO_WIDTH,
           INFO_HEIGHT);
  // info
  mvprintw(START_INFO_Y + 1, START_INFO_X + 1, "RECORD");
  mvprintw(START_INFO_Y + 2, START_INFO_X + 1, "%10d", info->high_score);
  mvprintw(START_INFO_Y + 3, START_INFO_X + 1, "SCORE");
  mvprintw(START_INFO_Y + 4, START_INFO_X + 1, "%10d", info->score);
  mvprintw(START_INFO_Y + 5, START_INFO_X + 1, "LEVEL");
  mvprintw(START_INFO_Y + 6, START_INFO_X + 1, "%10d", info->level);
  // next figure
  mvprintw(START_INFO_Y + 7, START_INFO_X + 1, "NEXT");
  for (int i = 0; i < FIGURE_HEIGHT / 2; i++) {
    for (int j = 0; j < FIGURE_WIDTH; j++) {
      attron(COLOR_PAIR(info->next[i][j]));
      mvprintw(START_INFO_Y + 9 + i, START_INFO_X + 3 + 2 * j, "  ");
      attroff(COLOR_PAIR(info->next[i][j]));
    }
  }
  // instructions
  if (info->pause) {
    mvprintw(START_INFO_Y + 13, START_INFO_X + 1, "CONTINUE");
    mvprintw(START_INFO_Y + 14, START_INFO_X + 4, "\"ENTER\"");
  } else {
    mvprintw(START_INFO_Y + 13, START_INFO_X + 1, "PAUSE   ");
    mvprintw(START_INFO_Y + 14, START_INFO_X + 4, "    \"P\"");
  }
  mvprintw(START_INFO_Y + 15, START_INFO_X + 1, "ROTATE");
  mvprintw(START_INFO_Y + 16, START_INFO_X + 4, "\"SPACE\"");
  mvprintw(START_INFO_Y + 17, START_INFO_X + 1, "MOVE");
  mvprintw(START_INFO_Y + 18, START_INFO_X + 5, "ARROWS");
  mvprintw(START_INFO_Y + 19, START_INFO_X + 1, "EXIT");
  mvprintw(START_INFO_Y + 20, START_INFO_X + 6, "\"ESC\"");
}

void printStartLay(void) {
  // box field
  printBox(0, 0, VIEW_WIDTH, HEIGHT);
  mvprintw((HEIGHT + 3) / 2, 9, "Welcome!");
  mvprintw((HEIGHT + 3) / 2 + 1, 5, "Enter - the start");
  refresh();
}

void printBox(int top_y, int left_x, int width, int height) {
  int right_x = left_x + width + 1;
  int bottom_y = top_y + height + 1;

  // first line with corners
  mvaddch(OFFSET + top_y, OFFSET + left_x, ACS_ULCORNER);
  printHLine(top_y, left_x + 1, width);
  mvaddch(OFFSET + top_y, OFFSET + right_x, ACS_URCORNER);

  // vertical lines
  printVLine(top_y + 1, left_x, height);
  printVLine(top_y + 1, right_x, height);

  // last line with corners
  mvaddch(OFFSET + bottom_y, OFFSET + left_x, ACS_LLCORNER);
  printHLine(bottom_y, left_x + 1, width);
  mvaddch(OFFSET + bottom_y, OFFSET + right_x, ACS_LRCORNER);
}

void printHLine(int y, int left_x, int width) {
  for (int i = left_x; i < left_x + width; i++) {
    mvaddch(OFFSET + y, OFFSET + i, ACS_HLINE);
  }
}

void printVLine(int top_y, int x, int height) {
  for (int i = top_y; i < top_y + height; i++) {
    mvaddch(OFFSET + i, OFFSET + x, ACS_VLINE);
  }
}