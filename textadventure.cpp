/***************************************************************************
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

/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/
#include <iostream>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES AND CONSTANTS                                  *
*--------------------------------------------------------------------*/
/* Control flags */
#define DEBUG 

/* Global constants */

#define MIDDLE_Y_AXIS (LINES/2)
#define MIDDLE_X_AXIS (COLS/2)

const char waves[5][3]={'~',' ','~',' ','~',' ',' ',' ',' ',' ','~',' ','~',' ','~'};

/* Global variables */

/* Global structures/classes */

//player should may be a window

//checkpoint system, like a password.

/*There could be a function which is always used when the game want's
save progress. The game creates, if one does not exist, a file and
write down the code there, so if you want to quit and continue later
you can use the password to skip to the point you were last time.
and there should be also

/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

void PrintPark();
WINDOW *create_middle_pond(int height, int width, int starty, int startx);
WINDOW *leftsideof_pond(int height, int width, int starty, int startx);
WINDOW *rightsideof_pond(int height, int width, int starty, int startx);
void PrintStation();

/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/

int main(void)  {
  initscr();
  clear();
  has_colors();

   if (has_colors() == FALSE) {
    endwin();
    std::cout<<"Your terminal does not support color"<<std::endl;
    usleep(5000000);
    exit(1);
  }

  start_color();
  init_pair(8, COLOR_BLACK, COLOR_GREEN);  /*Forest*/
  init_pair(7, COLOR_WHITE, COLOR_BLUE); /*Water*/
  init_pair(6, COLOR_RED, COLOR_BLACK); /*Error*/
  init_pair(9, COLOR_BLACK, COLOR_GREEN); /*for menu title and underline*/
  curs_set(0);

  /*std::cout<<"Middle Y = "<<MIDDLE_Y_AXIS<<std::endl;
  std::cout<<"Middle X = "<<MIDDLE_X_AXIS<<std::endl;*/

  PrintPark();
  endwin();
  return 0;
}

  
/*********************************************************************
*    FUNCTIONS                                                       *
**********************************************************************/


/*********************************************************************
 NAME: PrintPark
 DESCRIPTION: Prints the national park area

Input:
Output:
Used global variables:
REMARKS when using this function:
*********************************************************************/

void PrintPark() {
  clear();
  bkgd(COLOR_PAIR(8));
  refresh();
  WINDOW *middle_pond;
  WINDOW *leftsideof_pond;
  WINDOW *rightsideof_pond;
  middle_pond=create_middle_pond(10,10,MIDDLE_Y_AXIS-5,MIDDLE_X_AXIS-4);

  for (int i=0;i<5;i++) {
    for (int j=0;j<3;j++) {
      mvwprintw(middle_pond,i+1,j+2,"%c",waves[i][j]);
    }
  }

  for (int i=0;i<5;i++) {
    for (int j=0;j<3;j++) {
      mvwprintw(middle_pond,i+4,j+3,"%c",waves[i][j]);
    }
  }

  nodelay(middle_pond, TRUE);
  nodelay(stdscr, TRUE);
  keypad(middle_pond, TRUE);
  keypad(stdscr, TRUE);
  noecho();
  cbreak();
  wrefresh(middle_pond);
  napms(5000);
}

/*********************************************************************
 NAME: WINDOWFUNCTION
 DESCRIPTION: Prints the middle of the pond in national park

Input:
Output:
Used global variables:
REMARKS when using this function:
*********************************************************************/

WINDOW *create_middle_pond(int height, int width, int starty, int startx) {
  WINDOW *local_win;
  local_win = newwin(height, width, starty, startx);
  wbkgd(local_win, COLOR_PAIR(7));
  /*mvwaddch(local_win, height / 1, width / 1, '~');
  mvwaddch(local_win, height / 2, width / 2, '~');
  mvwaddch(local_win, height / 3, width / 3, '~');*/
  wrefresh(local_win);
  return local_win;
}

/*********************************************************************
 NAME: WINDOWFUNCTION
 DESCRIPTION: Prints the right side of the pond in national park

Input:
Output:
Used global variables:
REMARKS when using this function:
*********************************************************************/

WINDOW *rightsideof_pond(int height, int width, int starty, int startx) {
  
}

/*********************************************************************
 NAME: WINDOWFUNCTION 
 DESCRIPTION: Prints the left side of the pond in national park

Input:
Output:
Used global variables:
REMARKS when using this function:
*********************************************************************/

WINDOW *leftsideof_pond(int height, int width, int starty, int startx) {

}

