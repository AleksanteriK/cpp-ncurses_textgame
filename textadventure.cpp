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

/*********************************************************************
                        Other comments  
------------------------------                                          
Minimum window size should be:
Lines(y):30
Cols(x):114               
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
                                                                     */

/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/
#include <iostream>
#include <string>
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
    void SpawnThick(int up_y, int up_x, 
                    int mid_y, int mid_x,
                    int bottom_y, int bottom_x) 
    {
      mvaddstr(up_y, up_x, " /|\\ ");
      mvaddstr(mid_y, mid_x, "//|\\\\ ");
      mvaddstr(bottom_y, bottom_x, "  I  ");
    }

    void SpawnThick_in_Window(WINDOW *win, int up_y, int up_x, 
                              int mid_y, int mid_x,
                              int bottom_y, int bottom_x) 
    {
      mvwprintw(win,up_y, up_x, " /|\\ ");
      mvwprintw(win,mid_y, mid_x, "//|\\\\ ");
      mvwprintw(win,bottom_y, bottom_x, "  I  ");
    }
};

class ThinTree : public Woods {
  public:
    void SpawnThin(int up_y, int up_x, 
                   int mid_y, int mid_x,
                   int bottom_y, int bottom_x) 
    {
      mvaddstr(up_y, up_x, "  ^  ");
      mvaddstr(mid_y, mid_x, " /|\\ ");
      mvaddstr(bottom_y, bottom_x, "  I ");
    }
    void SpawnThin_in_Window(WINDOW *win, int up_y, int up_x, 
                              int mid_y, int mid_x,
                              int bottom_y, int bottom_x) 
    {
      mvwprintw(win,up_y, up_x, "  ^  ");
      mvwprintw(win,mid_y, mid_x, " /|\\ ");
      mvwprintw(win,bottom_y, bottom_x, "  I ");
    }
};
class Esker : public Woods {
  public:
    void SpawnEsker(int up_y, int up_x, 
                    int mid_y, int mid_x) 
    {
      mvaddstr(up_y, up_x, " _");
      mvaddstr(mid_y, mid_x, " / \\");
    }
    void SpawnEsker_in_Window(WINDOW *win, int up_y, int up_x, 
                              int mid_y, int mid_x) 
    {
      mvwprintw(win,up_y, up_x, " _");
      mvwprintw(win,mid_y, mid_x, "/ \\");
    }
};

class Cabin {
  public:
    void SpawnCabin(int top_y, int top_x,
                    int upmid_y, int upmid_x,
                    int mid_y, int mid_x,
                    int lowmid_y, int lowmid_x,
                    int bot_y, int bot_x) 
    {
        mvaddstr(top_y, top_x, " _| ");
        mvaddstr(upmid_y, upmid_x, "/  \\");
        mvaddstr(mid_y, mid_x, "|__|");
        mvaddstr(lowmid_y, lowmid_x, "|_||");
        mvaddstr(bot_y, bot_x, "----");

    }

    void SpawnCabin_in_Window(WINDOW *win, int top_y, int top_x,
                              int upmid_y, int upmid_x,
                              int mid_y, int mid_x,
                              int lowmid_y, int lowmid_x,
                              int bot_y, int bot_x) 
    {
        mvwprintw(win, top_y, top_x, " /\\ ");
        mvwprintw(win, upmid_y, upmid_x, "/  \\");
        mvwprintw(win, mid_y, mid_x, "|__|");
        mvwprintw(win, lowmid_y, lowmid_x, "|||");
        mvwprintw(win, bot_y, bot_x, "###");
        mvwprintw(win, top_y - 1, top_x + 1, "||");
        mvwprintw(win, top_y - 2, top_x + 1, "||");
    }
};
/*--------------------------------------------------------------------*/

class Player {
  public:
    int position_x;
    int position_y;

    Player(int startX, int startY) : position_x(startX), position_y(startY) {}

    void moveRight() {

    }

    void moveLeft() {

    }

    void moveForward() {

    }

    void moveBack() {

    }
};

class Map {  
  public:
    int gridsize_y;
    int gridsize_x;
    int playerpos_y;
    int playerpos_x;

    Map(int grid_y, int grid_x, int player_map_pos_y, int player_map_pos_x)
    : gridsize_y(grid_y), gridsize_x(grid_x), playerpos_y(player_map_pos_y),
      playerpos_x(player_map_pos_x) {}
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
WINDOW *cr_parktrees(int height, int width, int starty, int startx);
WINDOW *cr_eskers(int height, int width, int starty, int startx);
/*-------------------------------------------------------------------*/
/*National park functions*/
void PrintPark();
void PrintParkWoods();
/*-----------------------*/
/*-Game logics functions-*/
std::string Userinput();
void DialogueBox();
/*-----------------------*/
void PrintDebugInfo();

/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/

int main(void)  {
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

/*********************************************************************
*    FUNCTIONS                                                       *
**********************************************************************/

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
  wrefresh(local_win);
  return local_win;
}

/*********************************************************************
 NAME: WINDOWFUNCTION 
 DESCRIPTION: Creates window for printing the trees in the park

Input:
Output:
Used global variables:
REMARKS when using this function:
*********************************************************************/

WINDOW *cr_parktrees(int height, int width, int starty, int startx) {
  WINDOW *local_win;
  local_win = newwin(height, width, starty, startx);
  wbkgd(local_win, COLOR_PAIR(8));
  wrefresh(local_win);
  return local_win;
}

/*********************************************************************
 NAME: WINDOWFUNCTION 
 DESCRIPTION: Creates window for printing the eskers above the pond

Input:
Output:
Used global variables:
REMARKS when using this function:
*********************************************************************/

WINDOW *cr_eskers(int height, int width, int starty, int startx) {
  WINDOW *local_win;
  local_win = newwin(height, width, starty, startx);
  wbkgd(local_win, COLOR_PAIR(8));
  wrefresh(local_win);
  return local_win;
}

/*********************************************************************
 NAME: Userinput
 DESCRIPTION: gets the user input and returns the string

Input:
Output:
Used global variables:
REMARKS when using this function:
*********************************************************************/

std::string Userinput() {
  return "Temp";
}

/*********************************************************************
 NAME: DialogueBox
 DESCRIPTION: Has all the game related output, like see all the conver-
 sations and other game related text

Input:
Output:
Used global variables:
REMARKS when using this function:
*********************************************************************/

void DialogueBox() {

}

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
  Cabin cabin;

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

  cabin.SpawnCabin(23, 85, 24, 85, 25, 85, 26, 85, 27, 85);

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
  nodelay(downleftsideof_pond, TRUE);
  nodelay(stdscr, TRUE);
  keypad(downleftsideof_pond, TRUE);
  keypad(stdscr, TRUE);
  nodelay(downrightsideof_pond, TRUE);
  nodelay(stdscr, TRUE);
  keypad(downrightsideof_pond, TRUE);
  keypad(stdscr, TRUE);
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
  /*Coordinates where the trees are spawned in the windows*/
  int y[6] = {1, 4, 8, 12, 16, 19};
  int x[10] = {15, 23, 3, 9, 30, 35, 42, 19, 34, 15};
  /*Coordinates where the esker is spawned in the window*/
  int ex[7] = {1, 4, 7, 10, 14, 18, 22};
  int ey[7] = {1, 2, 3, 2, 1, 2, 3};

  ThickTree thicktree;
  ThinTree thintree;
  Esker esker;

  WINDOW *leftsidetrees;
  WINDOW *above_esker;
  WINDOW *rightsidetrees;

  leftsidetrees=cr_parktrees(23,47,1,1);
  rightsidetrees=cr_parktrees(23,46,1,COLS-45);
  above_esker=cr_eskers(8,26,1,MIDDLE_X_AXIS-12);

  mvaddstr(MIDDLE_Y_AXIS+10,MIDDLE_X_AXIS, "^ ^^  ^     ^");

  /*Printing the trees to the left*/
  for (int i=0; i<6; i++) {
    int newY=y[i]+1;
    thicktree.SpawnThick_in_Window(leftsidetrees,y[i],x[i],newY,x[i],newY+1,x[i]);
  }

  for (int i=5; i<10; i++) {
    int newY=y[i-5]+1;
    thintree.SpawnThin_in_Window(leftsidetrees,y[i-5],x[i],newY,x[i],newY+1,x[i]);
  }

  /*Printing the trees to the right*/
  for (int i=0; i<6; i++) {
    int newY=y[i]+1;
    thicktree.SpawnThick_in_Window(rightsidetrees,y[i],x[i],newY,x[i],newY+1,x[i]);
  }

  for (int i=5; i<10; i++) {
    int newY=y[i-5]+1;
    thintree.SpawnThin_in_Window(rightsidetrees,y[i-5],x[i],newY,x[i],newY+1,x[i]);
  }
  
  /*Printing the esker above the pond*/
  for (int i=0; i<7; i++) {
    int newY=ey[i]+1;
    esker.SpawnEsker_in_Window(above_esker,ey[i],ex[i],newY,ex[i]);
  }

  nodelay(leftsidetrees, TRUE);
  nodelay(stdscr, TRUE);
  keypad(leftsidetrees, TRUE);
  keypad(stdscr, TRUE);
  nodelay(rightsidetrees, TRUE);
  nodelay(stdscr, TRUE);
  keypad(rightsidetrees, TRUE);
  keypad(stdscr, TRUE);
  nodelay(above_esker, TRUE);
  nodelay(stdscr, TRUE);
  keypad(above_esker, TRUE);
  keypad(stdscr, TRUE);
  wrefresh(leftsidetrees);
  wrefresh(rightsidetrees);
  wrefresh(above_esker);

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