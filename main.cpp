#include <iostream>
#include <string>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include "environment.h"
#include "player.h"
#include "windows.h"
#include "gamefunctions.h"

#define MIDDLE_Y_AXIS (LINES/2)
#define MIDDLE_X_AXIS (COLS/2)

int main(void) {
/*---------------------------Error Checks-----------------------------*/
  initscr();
  clear();
  has_colors();

  if (has_colors()==FALSE) {
    endwin();
    std::cout<<"Your terminal does not support color"<<std::endl;
    napms(3000);
    exit(1);
  }

  if ((LINES<30 || COLS<114) || (LINES<30 && COLS<114)) {
    endwin();
    std::cout<<"Your terminal is too small, expand it!"<<std::endl;
    /*attron(COLOR_PAIR(6));
    mvaddstr(MIDDLE_Y_AXIS,MIDDLE_X_AXIS-5, "Your terminal is too small");
    attroff(COLOR_PAIR(6));*/
    napms(3500);
    return 0;
  }

  start_color();
  init_pair(8, COLOR_BLACK, COLOR_GREEN);  /*Forest*/
  init_pair(7, COLOR_WHITE, COLOR_BLUE); /*Water*/
  init_pair(6, COLOR_RED, COLOR_GREEN); /*Error*/
  init_pair(9, COLOR_BLACK, COLOR_GREEN); /*for menu title and underline*/
  curs_set(0);
/*------------------------------------------------------------------*/

/*-----------------------------PROGRAM------------------------------*/
  PrintPark();
  PrintDebugInfo(); //temp
  refresh();
  napms(10000);
/*------------------------------------------------------------------*/
  endwin();
  return 0;
}