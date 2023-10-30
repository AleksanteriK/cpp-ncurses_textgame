#include "environment.h"
#include "gamewindows.h"
#include <curses.h>
#include <unistd.h>

#define MIDDLE_Y_AXIS (LINES/2)
#define MIDDLE_X_AXIS (COLS/2)

const char waves[5][3]={ /*Static waves for pond*/
    {'~', ' ', '~'},
    {' ', ' ', ' '},
    {'~', ' ', '~'},
    {' ', ' ', ' '},
    {'~', ' ', '~'}
};

void SpawnThick(int up_y, int up_x, int mid_y, int mid_x, int bottom_y, int bottom_x) {
    /*Drawing a thick tree at specified positions*/
    mvaddstr(up_y, up_x, " /|\\ ");
    mvaddstr(mid_y, mid_x, "//|\\\\ ");
    mvaddstr(bottom_y, bottom_x, "  I  ");
}

void SpawnThick_in_Window(WINDOW *win, int up_y, int up_x, int mid_y, int mid_x, int bottom_y, int bottom_x) {
    /*Drawing a thick tree in a window at specified positions*/
    mvwprintw(win, up_y, up_x, " /|\\ ");
    mvwprintw(win, mid_y, mid_x, "//|\\\\ ");
    mvwprintw(win, bottom_y, bottom_x, "  I  ");
}

void SpawnThin(int up_y, int up_x, int mid_y, int mid_x, int bottom_y, int bottom_x) {
    /*Drawing a thin tree at specified positions*/
    mvaddstr(up_y, up_x, "  ^  ");
    mvaddstr(mid_y, mid_x, " /|\\ ");
    mvaddstr(bottom_y, bottom_x, "  I ");
}

void SpawnThin_in_Window(WINDOW *win, int up_y, int up_x, int mid_y, int mid_x, int bottom_y, int bottom_x) {
    /*Drawing a thin tree in a window at specified positions*/
    mvwprintw(win, up_y, up_x, "  ^  ");
    mvwprintw(win, mid_y, mid_x, " /|\\ ");
    mvwprintw(win, bottom_y, bottom_x, "  I ");
}

void SpawnEsker(int up_y, int up_x, int mid_y, int mid_x) {
    /*Drawing an esker at specified positions*/
    mvaddstr(up_y, up_x, " _");
    mvaddstr(mid_y, mid_x, " / \\");
}

void SpawnEsker_in_Window(WINDOW *win, int up_y, int up_x, int mid_y, int mid_x) {
    /*Drawing an esker in a window at specified positions*/
    mvwprintw(win, up_y, up_x, " _");
    mvwprintw(win, mid_y, mid_x, "/ \\");
}

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

  /*-----------------------THESE DOESN'T WORK------------------------*/
  /*cabin.SpawnCabin(23, 85, 24, 85, 25, 85, 26, 85, 27, 85);*/

  /*const int window_cols = getmaxx(stdscr); // Get the number of columns in the current window
  const int window_lines = getmaxy(stdscr); // Get the number of lines in the current window

    /*Scaling factor calculations to adapt to the window size*
  const float scaleX = window_cols / 114.0; // Adjust based on the original window size of 114 columns
  const float scaleY = window_lines / 30.0; // Adjust based on the original window size of 30 lines

    /*Using scaling factors for positioning elements*
  middle_pond = create_middle_pond(10 * scaleY, 10 * scaleX, MIDDLE_Y_AXIS - 5 * scaleY, MIDDLE_X_AXIS - 4 * scaleX);

    for (int i=0; i<5; i++) {
        for (int j=0; j<3; j++) {
            mvwprintw(middle_pond, (i+1) * scaleY, (j+3) * scaleX, "%c", waves[i][j]);
            mvwprintw(leftsideof_pond, (i+1) * scaleY, (j+1) * scaleX, "%c", waves[i][j]);
            mvwprintw(rightsideof_pond, (i+1) * scaleY, (j+1) * scaleX, "%c", waves[i][j]);
        }
    }

    for (int i=0; i<5; i++) {
        for (int j=0; j<3; j++) {
            mvwprintw(middle_pond, (i+4) * scaleY, (j+3) * scaleX, "%c", waves[i][j]);
        }
    }

    cabin.SpawnCabin(23*scaleY, 85*scaleX, 24*scaleY, 85*scaleX, 25*scaleY, 85*scaleX, 26*scaleY, 85*scaleX, 27*scaleY, 85*scaleX);*/
    /*---------------------------------------------------------------*/

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

void PrintParkWoods() {
  /*Coordinates where the trees are spawned in the windows
  int y[6] = {1, 4, 8, 12, 16, 19};
  int x[10] = {15, 23, 3, 9, 30, 35, 42, 19, 34, 15};
  /*Coordinates where the esker is spawned in the window
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

  /*Printing the trees to the left
  for (int i=0; i<6; i++) {
    int newY=y[i]+1;
    thicktree.SpawnThick_in_Window(leftsidetrees,y[i],x[i],newY,x[i],newY+1,x[i]);
  }

  for (int i=5; i<10; i++) {
    int newY=y[i-5]+1;
    thintree.SpawnThin_in_Window(leftsidetrees,y[i-5],x[i],newY,x[i],newY+1,x[i]);
  }

  /*Printing the trees to the right
  for (int i=0; i<6; i++) {
    int newY=y[i]+1;
    thicktree.SpawnThick_in_Window(rightsidetrees,y[i],x[i],newY,x[i],newY+1,x[i]);
  }

  for (int i=5; i<10; i++) {
    int newY=y[i-5]+1;
    thintree.SpawnThin_in_Window(rightsidetrees,y[i-5],x[i],newY,x[i],newY+1,x[i]);
  }
  
  /*Printing the esker above the pond
  for (int i=0; i<7; i++) {
    int newY=ey[i]+1;
    esker.SpawnEsker_in_Window(above_esker,ey[i],ex[i],newY,ex[i]);
  }*/

  ThickTree thicktree;
  ThinTree thintree;
  Esker esker;

  WINDOW *leftsidetrees;
  WINDOW *above_esker;
  WINDOW *rightsidetrees;

  const int window_cols = COLS;
  const int window_lines = LINES;

    /*Scaling factor calculations to adapt to the window size*/
  const float scaleX = window_cols / 125.0; /*Adjusting based on the original window size of 125 columns*/
  const float scaleY = window_lines / 45.0; /*Adjusting based on the original window size of 45 lines*/

  leftsidetrees=cr_parktrees(23*scaleY, 47*scaleX, 1*scaleY, 1*scaleX);
  rightsidetrees=cr_parktrees(23*scaleY, 46*scaleX, 1*scaleY, window_cols - 45*scaleX);
  above_esker=cr_eskers(8*scaleY, 26*scaleX, 1*scaleY, MIDDLE_X_AXIS - 12*scaleX);

    // Adjusting coordinates based on the scaling factors
    int y[6]={1, 4, 8, 12, 16, 19};
    int x[10]={15, 23, 3, 9, 30, 35, 42, 19, 34, 15};
    int ex[7]={1, 4, 7, 10, 14, 18, 22};
    int ey[7]={1, 2, 3, 2, 1, 2, 3};

    for (int i=0; i<6; i++) {
        int newY=y[i]*scaleY+1;
        thicktree.SpawnThick_in_Window(leftsidetrees, y[i]*scaleY, x[i]*scaleX, newY, x[i]*scaleX, newY + 1, x[i]*scaleX);
    }

    for (int i=5; i<10; i++) {
        int newY=y[i-5]*scaleY+1;
        thintree.SpawnThin_in_Window(leftsidetrees, y[i-5]*scaleY, x[i]*scaleX, newY, x[i]*scaleX, newY + 1, x[i]*scaleX);
    }

    for (int i=0; i<6; i++) {
        int newY=y[i]*scaleY+1;
        thicktree.SpawnThick_in_Window(rightsidetrees, y[i]*scaleY, x[i]*scaleX, newY, x[i]*scaleX, newY + 1, x[i]*scaleX);
    }

    for (int i=5; i<10; i++) {
        int newY=y[i-5]*scaleY+1;
        thintree.SpawnThin_in_Window(rightsidetrees, y[i-5]*scaleY, x[i]*scaleX, newY, x[i]*scaleX, newY + 1, x[i]*scaleX);
    }

    for (int i=0; i<7; i++) {
        int newY=ey[i]*scaleY+1;
        esker.SpawnEsker_in_Window(above_esker, ey[i]*scaleY, ex[i]*scaleX, newY, ex[i]*scaleX);
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