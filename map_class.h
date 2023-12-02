#ifndef MAP_CLASS_H
#define MAP_CLASS_H

#include <string>
#include <curses.h>

class Map {
  public:
    int gridsize_y;
    int gridsize_x;
    int playerpos_y;
    int playerpos_x;
    int secret_x;
    int secret_y;
    int exit_x;
    int exit_y;
    std::string chaptertext="";

    Map(int gridsize_y, int gridsize_x, int player_pos_y, int player_pos_x,
    int secret_x, int secret_y, int exit_x, int exit_y, std::string entrancetext);
    int ReturnPlayer_y();
    int ReturnPlayer_x();

    /*Prints the name of the chapter which the map in the game is part of*/
    void Print_Chapter_text(int x, int y);
};

#endif