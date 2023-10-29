#include "gamefunctions.h"

#define MIDDLE_Y_AXIS (LINES/2)
#define MIDDLE_X_AXIS (COLS/2)

WINDOW *Text_window(int height, int width, int starty, int startx) {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);
    wrefresh(local_win);
    return local_win;
}

std::string Userinput() {
    return "Temp";  /*Placeholder return value*/
}

void DialogueBox() {
    /*Logic for game-related output, conversations, and text*/
}

void PrintDebugInfo() {
   if (LINES<=30) {
  attron(COLOR_PAIR(6));
  mvaddstr(MIDDLE_Y_AXIS+6,MIDDLE_X_AXIS-35, "Terminal size:");
  mvprintw(MIDDLE_Y_AXIS+7,MIDDLE_X_AXIS-35, "Lines: %d",LINES);
  mvprintw(MIDDLE_Y_AXIS+8,MIDDLE_X_AXIS-35, "Cols: %d",COLS);
  mvprintw(MIDDLE_Y_AXIS+9,MIDDLE_X_AXIS-35, "mid_y: %d",MIDDLE_Y_AXIS);
  mvprintw(MIDDLE_Y_AXIS+10,MIDDLE_X_AXIS-35, "mid_x: %d",MIDDLE_X_AXIS);
  attroff(COLOR_PAIR(6));
  }
  
  else if (LINES>30 && LINES<=50) {
  attron(COLOR_PAIR(6));
  mvaddstr(MIDDLE_Y_AXIS+11,MIDDLE_X_AXIS-35, "Terminal size:");
  mvprintw(MIDDLE_Y_AXIS+12,MIDDLE_X_AXIS-35, "Lines: %d",LINES);
  mvprintw(MIDDLE_Y_AXIS+13,MIDDLE_X_AXIS-35, "Cols: %d",COLS);
  mvprintw(MIDDLE_Y_AXIS+14,MIDDLE_X_AXIS-35, "mid_y: %d",MIDDLE_Y_AXIS);
  mvprintw(MIDDLE_Y_AXIS+15,MIDDLE_X_AXIS-35, "mid_x: %d",MIDDLE_X_AXIS);
  attroff(COLOR_PAIR(6));
  }

  else {
  attron(COLOR_PAIR(6));
  mvaddstr(40,1, "Terminal size:");
  mvprintw(41,1, "Lines: %d",LINES);
  mvprintw(42,1, "Cols: %d",COLS);
  mvprintw(43,1, "mid_y: %d",MIDDLE_Y_AXIS);
  mvprintw(44,1, "mid_x: %d",MIDDLE_X_AXIS);
  attroff(COLOR_PAIR(6));
  }
}