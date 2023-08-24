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

const char waves[5][3]={ /*Static waves for pond*/
    {'~', ' ', '~'},
    {' ', ' ', ' '},
    {'~', ' ', '~'},
    {' ', ' ', ' '},
    {'~', ' ', '~'}
};

/* Global variables */

/* Global structures/classes */

/*-----------------------ENVIRONMENT CLASSES-------------------------*/
class Woods {
  public:
    int x_livingarea;
    int y_livingarea;
};

class ThickTree : public Woods {
  public:
    void Spawn(int up_y, int up_x, 
                        int mid_y, int mid_x,
                        int bottom_y, int bottom_x) 
    { /*Upper part of the tree*/
      mvaddstr(up_y, up_x, " /|\\ ");
      mvaddstr(mid_y, mid_x, "//|\\\\ ");
      mvaddstr(bottom_y, bottom_x, "  I  ");
    }
};

class ThinTree : public Woods {
  public:
    void Spawn(int up_y, int up_x, 
                        int mid_y, int mid_x,
                        int bottom_y, int bottom_x) 
    {
      mvaddstr(up_y, up_x, "  ^  ");
      mvaddstr(mid_y, mid_x, " /|\\ ");
      mvaddstr(bottom_y, bottom_x, " I ");
    }
};
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/
/*                      Window functions                             */
WINDOW *Text_window(int height, int width, int starty, int startx);
WINDOW *create_middle_pond(int height, int width, int starty, int startx);
WINDOW *cr_leftsideof_pond(int height, int width, int starty, int startx);
WINDOW *cr_rightsideof_pond(int height, int width, int starty, int startx);
/*-------------------------------------------------------------------*/
void PrintPark();
void PrintParkWoods();
void PrintStation();
void PrintDebugInfo();

/*There could be a function which is always used when the game want's
save progress. The game creates, if one does not exist, a file and
write down the code there, so if you want to quit and continue later
you can use the password to skip to the point you were last time.

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
    napms(3000);
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
  /*-----------------------------------------------------------------*/
  PrintDebugInfo();
  refresh();
  napms(5000);
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
  WINDOW *downleftsideof_pond;
  WINDOW *rightsideof_pond;
  WINDOW *downrightsideof_pond;
  WINDOW *upleftsideof_pond;
  WINDOW *uprightsideof_pond;
  middle_pond=create_middle_pond(10,10,MIDDLE_Y_AXIS-5,MIDDLE_X_AXIS-4);
  leftsideof_pond=cr_leftsideof_pond(6,5,MIDDLE_Y_AXIS-3,MIDDLE_X_AXIS-9);
  rightsideof_pond=cr_rightsideof_pond(6,5,MIDDLE_Y_AXIS-3,MIDDLE_X_AXIS+6);
  downrightsideof_pond=cr_rightsideof_pond(1,3,MIDDLE_Y_AXIS+3,MIDDLE_X_AXIS+6);
  downleftsideof_pond=cr_leftsideof_pond(1,3,MIDDLE_Y_AXIS+3,MIDDLE_X_AXIS-7);
  upleftsideof_pond=cr_leftsideof_pond(1,3,MIDDLE_Y_AXIS-4,MIDDLE_X_AXIS-7);
  uprightsideof_pond=cr_rightsideof_pond(1,3,MIDDLE_Y_AXIS-4,MIDDLE_X_AXIS+6);

  /*Creating the waves for the whole pond*/
  for (int i=0; i<5; i++) {
    for (int j=0; j<3; j++) {
      mvwprintw(middle_pond, i+1, j+3, "%c", waves[i][j]);
      mvwprintw(leftsideof_pond, i+1, j+1, "%c", waves[i][j]);
      mvwprintw(rightsideof_pond, i+1, j+1, "%c", waves[i][j]);
    }
  }
  /*Printing for the bottom of the middle pond*/
  for (int i=0; i<5; i++) {
    for (int j=0; j<3; j++) {
      mvwprintw(middle_pond, i+4, j+3, "%c", waves[i][j]);
    }
  }
  /*--------------------------------------*/

  nodelay(middle_pond, TRUE);
  nodelay(stdscr, TRUE);
  keypad(middle_pond, TRUE);
  keypad(stdscr, TRUE);
  nodelay(leftsideof_pond, TRUE);
  nodelay(stdscr, TRUE);
  keypad(leftsideof_pond, TRUE);
  keypad(stdscr, TRUE);
  nodelay(rightsideof_pond, TRUE);
  nodelay(stdscr, TRUE);
  keypad(rightsideof_pond, TRUE);
  keypad(stdscr, TRUE);
  /*--------------------------------*/
  nodelay(downleftsideof_pond, TRUE);
  nodelay(stdscr, TRUE);
  keypad(downleftsideof_pond, TRUE);
  keypad(stdscr, TRUE);
  nodelay(downrightsideof_pond, TRUE);
  nodelay(stdscr, TRUE);
  keypad(downrightsideof_pond, TRUE);
  keypad(stdscr, TRUE);
  /*-------------------------------*/
  nodelay(upleftsideof_pond, TRUE);
  nodelay(stdscr, TRUE);
  keypad(upleftsideof_pond, TRUE);
  keypad(stdscr, TRUE);
  nodelay(uprightsideof_pond, TRUE);
  nodelay(stdscr, TRUE);
  keypad(uprightsideof_pond, TRUE);
  keypad(stdscr, TRUE);

  noecho();
  cbreak();
  wrefresh(middle_pond);
  wrefresh(leftsideof_pond);
  wrefresh(rightsideof_pond);
  wrefresh(downleftsideof_pond);
  wrefresh(downrightsideof_pond);
  wrefresh(upleftsideof_pond);
  wrefresh(uprightsideof_pond);

  PrintParkWoods();
  refresh();
  /*clear(); 
    bkgd(COLOR_PAIR(8));
    refresh();
    WINDOW *middle_pond;
    WINDOW *leftsideof_pond;
    WINDOW *rightsideof_pond;
    middle_pond = create_middle_pond(10, 10, MIDDLE_Y_AXIS - 5, MIDDLE_X_AXIS - 4);
    leftsideof_pond = cr_leftsideof_pond(6, 6, MIDDLE_Y_AXIS - 3, MIDDLE_X_AXIS - 10);
    rightsideof_pond = cr_rightsideof_pond(6, 5, MIDDLE_Y_AXIS - 3, MIDDLE_X_AXIS + 6);

    nodelay(middle_pond, TRUE);
    nodelay(stdscr, TRUE);
    keypad(middle_pond, TRUE);
    keypad(stdscr, TRUE);
    nodelay(leftsideof_pond, TRUE);
    nodelay(stdscr, TRUE);
    keypad(leftsideof_pond, TRUE);
    keypad(stdscr, TRUE);
    nodelay(rightsideof_pond, TRUE);
    nodelay(stdscr, TRUE);
    keypad(rightsideof_pond, TRUE);
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    
    int wave_frame = 0;
    int delay = 100; // Time delay in milliseconds

    while (true) {
        // Creating the waves for the middle pond
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 3; j++) {
                mvwprintw(middle_pond, i + 1, j + 3, "%c", waves[(i + wave_frame) % 5][j]);
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 3; j++) {
                mvwprintw(middle_pond, i + 4, j + 3, "%c", waves[(i + wave_frame) % 5][j]);
            }
        }
        
        wrefresh(middle_pond);
        wrefresh(leftsideof_pond);
        wrefresh(rightsideof_pond);

        napms(delay);
        wave_frame++;
    }*/
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

WINDOW *cr_rightsideof_pond(int height, int width, int starty, int startx) {
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
 DESCRIPTION: Prints the left side of the pond in national park

Input:
Output:
Used global variables:
REMARKS when using this function:
*********************************************************************/

WINDOW *cr_leftsideof_pond(int height, int width, int starty, int startx) {
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
 NAME: PrintParkWoods 
 DESCRIPTION: Prints the trees, paths, rocks etc in the national park

Input:
Output:
Used global variables:
REMARKS when using this function:
*********************************************************************/

void PrintParkWoods() {
  mvaddstr(MIDDLE_Y_AXIS+11,MIDDLE_X_AXIS, "^ ^^  ^     ^"); //test
  ThickTree test;
  test.Spawn(4,5,5,5,6,5);
}

/*********************************************************************
 NAME: PrintDebugInfo 
 DESCRIPTION: Prints in to the corner of the screen some data what is
 helpful during the development

Input:
Output:
Used global variables:
REMARKS when using this function:
*********************************************************************/

void PrintDebugInfo() {
  if (LINES<=30) {
  mvaddstr(MIDDLE_Y_AXIS+10,MIDDLE_X_AXIS+45, "Terminal size:");
  mvprintw(MIDDLE_Y_AXIS+11,MIDDLE_X_AXIS+45, "Lines: %d",LINES);
  mvprintw(MIDDLE_Y_AXIS+12,MIDDLE_X_AXIS+45, "Cols: %d",COLS);
  }
  
  else if (LINES>30 && LINES<=50) {
  mvaddstr(MIDDLE_Y_AXIS+19,MIDDLE_X_AXIS+45, "Terminal size:");
  mvprintw(MIDDLE_Y_AXIS+20,MIDDLE_X_AXIS+45, "Lines: %d",LINES);
  mvprintw(MIDDLE_Y_AXIS+21,MIDDLE_X_AXIS+45, "Cols: %d",COLS);
  }

  else {
  mvaddstr(1,1, "Terminal size:");
  mvprintw(2,1, "Lines: %d",LINES);
  mvprintw(3,1, "Cols: %d",COLS);
  }
}