#ifndef MAP_CLASS_H
#define MAP_CLASS_H

#include <string>
#include <curses.h>
#include <vector>

class Area {
  public:
    int x;
    int y;
    std::string description;

    Area(int x, int y, const std::string& desc);

    void Describe();
};

class Map {
  public:
    //Getters
    int GetGridSizeY() const;
    int GetGridSizeX() const;
    int GetPlayerPosY() const;
    int GetPlayerPosX() const;
    int GetSecretX() const;
    int GetSecretY() const;
    int GetExitX() const;
    int GetExitY() const;
    std::string GetChapterText() const;
    std::vector<Area> areas;

    //Setters
    void SetGridSizeY(int size);
    void SetGridSizeX(int size);
    void SetPlayerPosY(int posY);
    void SetPlayerPosX(int posX);
    void SetSecretX(int x);
    void SetSecretY(int y);
    void SetExitX(int x);
    void SetExitY(int y);
    void SetChapterText(const std::string& text);

  private:
    std::string chaptertext;
    int gridsize_y;
    int gridsize_x;
    int playerpos_y;
    int playerpos_x;
    int secret_x;
    int secret_y;
    int exit_x;
    int exit_y;
};

#endif