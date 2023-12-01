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

    std::vector<int> left_thin_y = {1, 4, 8, 12, 16, 10, 5, 12};
    std::vector<int> left_thin_x = {30, 9, 22, 10, 43, 41, 15, 38};
    std::vector<int> left_thick_y = {6, 10, 19, 15, 18, 10, 17, 1};
    std::vector<int> left_thick_x = {25, 15, 8, 35, 40, 7, 23, 3};

    std::vector<int> right_thin_y = {1, 4, 8, 12, 16, 10, 5, 12};
    std::vector<int> right_thin_x = {27, 9, 22, 11, 39, 33, 15, 38};
    std::vector<int> right_thick_y = {6, 10, 19, 15, 20, 10, 17, 1};
    std::vector<int> right_thick_x = {25, 15, 8, 30, 38, 7, 23, 3};

  for (int i = 0; i < 8; i++) {
      int new_thin_Y = left_thin_y[i] + 1;
      int new_thick_Y = left_thick_y[i] + 1;
      errorcheck = thintree.SpawnThin_in_Window(leftsidetrees, left_thin_y[i], left_thin_x[i], new_thin_Y, left_thin_x[i], new_thin_Y + 1, left_thin_x[i]);
      errorcheck = thicktree.SpawnThick_in_Window(leftsidetrees, left_thick_y[i], left_thick_x[i], new_thick_Y, left_thick_x[i], new_thick_Y + 1, left_thick_x[i]);

      if (errorcheck == 1) {
        attron(COLOR_PAIR(1));
        mvaddstr(MIDDLE_Y_AXIS, MIDDLE_X_AXIS - 10, "Method returned error");
        attroff(COLOR_PAIR(1));
        refresh();
      }
    }

  for (int i = 0; i < 8; i++) {
      int new_thin_Y = right_thin_y[i] + 1;
      int new_thick_Y = right_thick_y[i] + 1;
      errorcheck = thintree.SpawnThin_in_Window(rightsidetrees, right_thin_y[i], right_thin_x[i], new_thin_Y, right_thin_x[i], new_thin_Y + 1, right_thin_x[i]);
      errorcheck = thicktree.SpawnThick_in_Window(rightsidetrees, right_thick_y[i], right_thick_x[i], new_thick_Y, right_thick_x[i], new_thick_Y + 1, right_thick_x[i]);

      if (errorcheck == 1) {
        attron(COLOR_PAIR(1));
        mvaddstr(MIDDLE_Y_AXIS, MIDDLE_X_AXIS - 10, "Method returned error");
        attroff(COLOR_PAIR(1));
        refresh();
      }
    }
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

  int ex[7] = {1, 4, 7, 10, 14, 18, 22};
  int ey[7] = {1, 2, 3, 2, 1, 2, 3};

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