#include "map_class.h"

Area::Area(int x, int y, const std::string& desc) : x(x), y(y), description(desc) {

}

void Area::Describe() {
  //nothing yet
}

//Getters
int Map::GetGridSizeY() const {
    return gridsize_y;
}

int Map::GetGridSizeX() const {
    return gridsize_x;
}

int Map::GetPlayerPosY() const {
    return playerpos_y;
}

int Map::GetPlayerPosX() const {
    return playerpos_x;
}

int Map::GetSecretX() const {
    return secret_x;
}

int Map::GetSecretY() const {
    return secret_y;
}

int Map::GetExitX() const {
    return exit_x;
}

int Map::GetExitY() const {
    return exit_y;
}

std::string Map::GetChapterText() const {
    return chaptertext;
}

//Setters
void Map::SetGridSizeY(int size) {
    gridsize_y = size;
}

void Map::SetGridSizeX(int size) {
    gridsize_x = size;
}

void Map::SetPlayerPosY(int posY) {
    playerpos_y = posY;
}

void Map::SetPlayerPosX(int posX) {
    playerpos_x = posX;
}

void Map::SetSecretX(int x) {
    secret_x = x;
}

void Map::SetSecretY(int y) {
    secret_y = y;
}

void Map::SetExitX(int x) {
    exit_x = x;
}

void Map::SetExitY(int y) {
    exit_y = y;
}

void Map::SetChapterText(const std::string& text) {
    chaptertext = text;
}
