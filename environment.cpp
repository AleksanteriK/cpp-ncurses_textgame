#include "environment.h"
#include "gamewindows.h"
#include "woods_classes.h"

#define MIDDLE_Y_AXIS (LINES/2)
#define MIDDLE_X_AXIS (COLS/2)

const char waves[5][3]={ /*Static waves for pond*/
    {'~', ' ', '~'},
    {' ', ' ', ' '},
    {'~', ' ', '~'},
    {' ', ' ', ' '},
    {'~', ' ', '~'}
};

/*-------------------------Enviroment functions-----------------------------*/
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

  middle_pond = create_middle_pond(10, 10, MIDDLE_Y_AXIS - 5, MIDDLE_X_AXIS - 4);
  leftsideof_pond = cr_leftsideof_pond(6, 5, MIDDLE_Y_AXIS - 3, MIDDLE_X_AXIS - 9);
  rightsideof_pond = cr_rightsideof_pond(6, 5, MIDDLE_Y_AXIS - 3, MIDDLE_X_AXIS + 6);
  downrightsideof_pond = cr_rightsideof_pond(1 , 3, MIDDLE_Y_AXIS + 3, MIDDLE_X_AXIS + 6);
  downleftsideof_pond = cr_leftsideof_pond(1, 3, MIDDLE_Y_AXIS + 3, MIDDLE_X_AXIS - 7);
  upleftsideof_pond = cr_leftsideof_pond(1, 3, MIDDLE_Y_AXIS-4, MIDDLE_X_AXIS - 7);
  uprightsideof_pond = cr_rightsideof_pond(1, 3, MIDDLE_Y_AXIS - 4, MIDDLE_X_AXIS+6);

  /*Creating the waves for the whole pond*/
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      mvwprintw(middle_pond, i + 1, j + 3, "%c", waves[i][j]);
      mvwprintw(leftsideof_pond, i + 1, j + 1, "%c", waves[i][j]);
      mvwprintw(rightsideof_pond, i + 1, j + 1, "%c", waves[i][j]);
    }
  }
  /*Printing for the bottom of the middle pond*/
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      mvwprintw(middle_pond, i + 4, j + 3, "%c", waves[i][j]);
    }
  }

  wrefresh(middle_pond);
  wrefresh(leftsideof_pond);
  wrefresh(rightsideof_pond);
  wrefresh(downleftsideof_pond);
  wrefresh(downrightsideof_pond);
  wrefresh(upleftsideof_pond);
  wrefresh(uprightsideof_pond);
  refresh();
}

void PrintParkWoods(float terminal_window_size, char& line_col_exceeding) {
  int errorcheck;

  ThickTree thicktree(3,3);
  ThinTree thintree(3,3);
  Esker esker(10);

  WINDOW *leftsidetrees;
  WINDOW *above_esker;
  WINDOW *rightsidetrees;

  if (terminal_window_size == 1 && line_col_exceeding == 'n') {
    leftsidetrees = cr_parktrees(23, 47, 1, 1);
    rightsidetrees = cr_parktrees(23, 46, 1, COLS - 47);
    above_esker = cr_eskers(14, 26, 1, MIDDLE_X_AXIS - 12);
  }

  else if (terminal_window_size == 1.5 && line_col_exceeding == 'c') {
    leftsidetrees = cr_parktrees(23, 70, 1, 1);
    rightsidetrees = cr_parktrees(23, 70, 1, COLS - 69);
    above_esker = cr_eskers(14, 26, 1, MIDDLE_X_AXIS - 12);
    }

  else if (terminal_window_size == 1.5 && line_col_exceeding == 'l') {
    leftsidetrees = cr_parktrees(30, 47, 1, 1);
    rightsidetrees = cr_parktrees(30, 46, 1, COLS - 47);
    above_esker = cr_eskers(19, 26, 1, MIDDLE_X_AXIS - 12);
  } 
  
  else if (terminal_window_size == 2 && line_col_exceeding == 'n') {
    leftsidetrees = cr_parktrees(30, 70, 1, 1);
    rightsidetrees = cr_parktrees(30, 70, 1, COLS - 69);
    above_esker = cr_eskers(19, 26, 1, MIDDLE_X_AXIS - 12);
  } 

  else if (terminal_window_size == 2.5 && line_col_exceeding == 'c') {
    leftsidetrees = cr_parktrees(30, 100, 1, 1);
    rightsidetrees = cr_parktrees(30, 100, 1, COLS - 100);
    above_esker = cr_eskers(19, 26, 1, MIDDLE_X_AXIS - 12);
  } 

  else if (terminal_window_size == 2.5 && line_col_exceeding == 'l') {
    leftsidetrees = cr_parktrees(33, 70, 1, 1);
    rightsidetrees = cr_parktrees(33, 70, 1, COLS - 69);
    above_esker = cr_eskers(23, 26, 1, MIDDLE_X_AXIS - 12);
  } 
  
  else if (terminal_window_size == 3 && line_col_exceeding == 'n') {
    leftsidetrees = cr_parktrees(33, 100, 1, 1);
    rightsidetrees = cr_parktrees(33, 100, 1, COLS - 100);
    above_esker = cr_eskers(23, 26, 1, MIDDLE_X_AXIS - 12);
  }

  /*Coordinates where the trees are spawned in the windows*/
  int y[6] = {1, 4, 8, 12, 16, 19};
  int x[10] = {15, 23, 3, 9, 30, 35, 42, 19, 34, 15};
  /*Coordinates where the esker is spawned in the window*/
  int ex[7] = {1, 4, 7, 10, 14, 18, 22};
  int ey[7] = {1, 2, 3, 2, 1, 2, 3};

  // Printing the trees to the left
  for (int i = 0; i < 6; i++) {
    int newY = y[i] + 1;
    errorcheck = thicktree.SpawnThick_in_Window(leftsidetrees, y[i], x[i], newY, x[i], newY + 1, x[i]);

    if (errorcheck == 1) {
      attron(COLOR_PAIR (1));
      mvaddstr(MIDDLE_Y_AXIS, MIDDLE_X_AXIS-10, "Method returned error");
      attroff(COLOR_PAIR (1));
      refresh();
    }
  }

  for (int i = 5; i < 10; i++) {
    int newY = y[i - 5] + 1;
    errorcheck = thintree.SpawnThin_in_Window(leftsidetrees, y[i - 5], x[i], newY, x[i], newY + 1, x[i]);

    if (errorcheck == 1) {
      attron(COLOR_PAIR (1));
      mvaddstr(MIDDLE_Y_AXIS, MIDDLE_X_AXIS-10, "Method returned error");
      attroff(COLOR_PAIR (1));
      refresh();
    }
  }

  // Printing the trees to the right
  for (int i = 0; i < 6; i++) {
    int newY = y[i] + 1;
    errorcheck = thicktree.SpawnThick_in_Window(rightsidetrees, y[i], x[i], newY, x[i], newY + 1, x[i]);

    if (errorcheck == 1) {
      attron(COLOR_PAIR (1));
      mvaddstr(MIDDLE_Y_AXIS, MIDDLE_X_AXIS-10, "Method returned error");
      attroff(COLOR_PAIR (1));
      refresh();
    }
  }

  for (int i = 5; i < 10; i++) {
    int newY = y[i - 5] + 1;
    errorcheck = thintree.SpawnThin_in_Window(rightsidetrees, y[i - 5], x[i], newY, x[i], newY + 1, x[i]);

    if (errorcheck == 1) {
      attron(COLOR_PAIR (1));
      mvaddstr(MIDDLE_Y_AXIS, MIDDLE_X_AXIS-10, "Method returned error");
      attroff(COLOR_PAIR (1));
      refresh();
    }
  }

  // Printing the esker above the pond
  for (int i = 0; i < 7; i++) {
    int newY = ey[i] + 1;
    esker.SpawnEsker_in_Window(above_esker, ey[i], ex[i], newY, ex[i]);
  }

  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  noecho();
  cbreak();
  wrefresh(leftsidetrees);
  wrefresh(rightsidetrees);
  wrefresh(above_esker);
  refresh();
}
/*------------------------------------------------------------------------*/