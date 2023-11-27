#include <iostream>
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

void WriteDialogue() {
    /*Logic for game-related output, conversations, and text*/
}

void PrintDebugInfo(/*int& scaleY, int& scaleX*/) {
   if (LINES>=45 && LINES<=75) {
  attron(COLOR_PAIR(6));
  mvaddstr(LINES-LINES+1,COLS-COLS+1, "Terminal size:");
  mvprintw(LINES-LINES+2,COLS-COLS+1, "Lines: %d",LINES);
  mvprintw(LINES-LINES+3,COLS-COLS+1, "Cols: %d",COLS);
  mvprintw(LINES-LINES+4,COLS-COLS+1, "mid_y: %d",MIDDLE_Y_AXIS);
  mvprintw(LINES-LINES+5,COLS-COLS+1, "mid_x: %d",MIDDLE_X_AXIS);
  /*mvprintw(LINES-LINES+6,COLS-COLS+1, "scale_y: %d",scaleY);
  mvprintw(LINES-LINES+7,COLS-COLS+1, "scale_x: %d",scaleX);*/
  attroff(COLOR_PAIR(6));
  }

  else {
  attron(COLOR_PAIR(6));
  mvaddstr(40,1, "Terminal size:");
  mvprintw(41,1, "Lines: %d",LINES);
  mvprintw(42,1, "Cols: %d",COLS);
  mvprintw(43,1, "mid_y: %d",MIDDLE_Y_AXIS);
  mvprintw(44,1, "mid_x: %d",MIDDLE_X_AXIS);
  /*mvprintw(45,1, "scale_y: %d",scaleY);
  mvprintw(46,1, "scale_x: %d",scaleX);*/
  attroff(COLOR_PAIR(6));
  }
}

void TerminalDebug() {
    std::cout<<"/EN/ Your terminal is too small, expand it!"<<std::endl;
    std::cout<<"      ..    ..                                         .."<<std::endl;
    std::cout<<"/FI/ Kayttamasi terminaali on liian pieni, suurenna sita"<<std::endl;
    std::cout<<"                                       "<<std::endl;
    std::cout<<"     tai vaihda terminaalia\n"<<std::endl;
}

void ResizeTerminalInfo_for_Ncurses() {
    mvaddstr(MIDDLE_Y_AXIS, MIDDLE_X_AXIS-17, "------------------------------------------------------");
    mvaddstr(MIDDLE_Y_AXIS+1, MIDDLE_X_AXIS-17,"    Expand the terminal / Suurenna terminaalia");
    mvaddstr(MIDDLE_Y_AXIS+2, MIDDLE_X_AXIS-17, "       F1 to exit        Paina F1 poistuaksesi");
}