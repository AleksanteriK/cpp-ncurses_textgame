#include "map_class.h"

Map::Map(int gridsize_y, int gridsize_x, int player_pos_y, int player_pos_x, 
int secret_x, int secret_y, int exit_x, int exit_y, std::string chaptertext) {
    this -> gridsize_y = gridsize_y;
    this -> gridsize_x = gridsize_x;
    this -> playerpos_y = player_pos_y;
    this -> playerpos_x = player_pos_x;
    this -> secret_x = secret_x;
    this -> secret_y = secret_y;
    this -> exit_x = exit_x;
    this -> exit_y = exit_y;
    this -> chaptertext = chaptertext;
}

int Map::ReturnPlayer_y() {
  return playerpos_y;
}
int Map::ReturnPlayer_x() {
  return playerpos_x;
}

void Map::Print_Chapter_text(int y, int x) {
  mvprintw(y,x,"%s",chaptertext.c_str());
}