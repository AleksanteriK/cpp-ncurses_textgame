#include "gamefunctions.h"

#define MIDDLE_Y_AXIS (LINES/2)
#define MIDDLE_X_AXIS (COLS/2)

std::string Userinput() {
    return "Temp";  /*Placeholder return value*/
}

void WriteDialogue() {
    /*Logic for game-related output, conversations, and text*/
}

void PrintDebugInfo(float& first_debug_item, char& line_col_exceeding) {
   if (LINES>=45 && LINES<=75) {
  attron(COLOR_PAIR(6));
  mvaddstr(LINES - 7, COLS - 15, "Terminal size:");
  mvprintw(LINES - 6, COLS - 15, "Lines: %d",LINES);
  mvprintw(LINES - 5, COLS - 15, "Cols: %d",COLS);
  mvprintw(LINES - 4, COLS - 15, "mid_y: %d", MIDDLE_Y_AXIS);
  mvprintw(LINES - 3, COLS - 15, "mid_x: %d", MIDDLE_X_AXIS);
  mvprintw(LINES - 2, COLS - 15, "terminal_window_size: %f", first_debug_item);
  mvprintw(LINES - 1, COLS - 15, "exceeding variable: %c", line_col_exceeding);
  attroff(COLOR_PAIR(6));
  }

  else {
  attron(COLOR_PAIR(6));
  mvaddstr(40, 1, "Terminal size:");
  mvprintw(41, 1, "Lines: %d",LINES);
  mvprintw(42, 1, "Cols: %d",COLS);
  mvprintw(43, 1, "mid_y: %d", MIDDLE_Y_AXIS);
  mvprintw(45, 1, "mid_x: %d", MIDDLE_X_AXIS);
  mvprintw(46, 1, "terminal_window_size: %f",first_debug_item);
  mvprintw(47, 1, "exceeding variable: %c", line_col_exceeding);
  attroff(COLOR_PAIR(6));
  }
}