/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2023 by Aleksanteri Koivisto                            *
 *   juho.koivisto00@outlook.com                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *                                                                         *
 ***************************************************************************/

/*********************************************************************

 NAME: Text adventure game / Tekstiseikkailupeli


 DESCRIPTION:


 VERSIONS:
       

       Version history:

**********************************************************************/

/*********************************************************************
                        Other comments  
------------------------------                                          
Minimum window size should be:
Lines(y):45
Cols(x):125               
------------------------------
---------------------------------------------------------------------
There could be a function which is always used when the game want's
save progress. The game creates, if one does not exist, a file and
write down the code there, so if you want to quit and continue later
you can use the password to skip to the point you were last time.
---------------------------------------------------------------------
---------------------------------------------------------------------
Everything graphical in the game is purely aesthetic, the player moves
and the game itself is played in a "hidden" x,y grid.
**********************************************************************/

#include <iostream>
#include <string>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include "environment.h"
#include "player.h"
#include "gamewindows.h"
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