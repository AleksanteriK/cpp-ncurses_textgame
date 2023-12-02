#ifndef WOODS_CLASSES_H
#define WOODS_CLASSES_H

#include <ncurses.h>
#include <curses.h>
#include <iostream>

class Tree {
  public:
    int x_livingarea;
    int y_livingarea; //placeholders

    Tree(int x_livingarea, int y_livingarea);
};

class ThickTree : public Tree {
  public:

    ThickTree(int x_livingarea, int y_livingarea);

    void SpawnThick(int up_y, int up_x, 
                    int mid_y, int mid_x,
                    int bottom_y, int bottom_x);

    int SpawnThick_in_Window(WINDOW *win, int up_y, int up_x, 
                              int mid_y, int mid_x,
                              int bottom_y, int bottom_x);
};

class ThinTree : public Tree {
  public:

    ThinTree(int x_livingarea, int y_livingarea);

    void SpawnThin(int up_y, int up_x, 
                   int mid_y, int mid_x,
                   int bottom_y, int bottom_x);

    int SpawnThin_in_Window(WINDOW *win, int up_y, int up_x, 
                              int mid_y, int mid_x,
                              int bottom_y, int bottom_x);
};

class Esker {
  public:
  int width; //placeholder

    Esker(int width);

    void SpawnEsker(int up_y, int up_x, 
                    int mid_y, int mid_x);

    void SpawnEsker_in_Window(WINDOW *win, int up_y, int up_x, 
                              int mid_y, int mid_x);
    void SpawnBig_Esker_in_Window(WINDOW *win, int up_y, int up_x, 
                              int mid_y, int mid_x);
};

class Cabin {
  public:
  std::string owner_name; //placeholder

    Cabin(std::string owner_name);

    void SpawnCabin(int top_y, int top_x,
                    int upmid_y, int upmid_x,
                    int bottom_y, int bottom_x);

    void SpawnCabin_in_Window(WINDOW *win, int top_y, int top_x,
                              int mid_y, int mid_x,
                              int bottom_y, int bottom_x);
};

#endif