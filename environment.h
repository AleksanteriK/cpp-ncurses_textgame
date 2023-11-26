#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <ncurses.h>
#include <string>

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
      
    }

    void SpawnThick_in_Window(WINDOW *win, int up_y, int up_x, 
                              int mid_y, int mid_x,
                              int bottom_y, int bottom_x) 
    {
      
    }
};

class ThinTree : public Woods {
  public:
    void SpawnThin(int up_y, int up_x, 
                   int mid_y, int mid_x,
                   int bottom_y, int bottom_x) 
    {
      
    }
    void SpawnThin_in_Window(WINDOW *win, int up_y, int up_x, 
                              int mid_y, int mid_x,
                              int bottom_y, int bottom_x) 
    {
      
    }
};
class Esker : public Woods {
  public:
    void SpawnEsker(int up_y, int up_x, 
                    int mid_y, int mid_x) 
    {
      
    }
    void SpawnEsker_in_Window(WINDOW *win, int up_y, int up_x, 
                              int mid_y, int mid_x) 
    {
      
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

    }

    void SpawnCabin_in_Window(WINDOW *win, int top_y, int top_x,
                              int upmid_y, int upmid_x,
                              int mid_y, int mid_x,
                              int lowmid_y, int lowmid_x,
                              int bot_y, int bot_x) 
    {
        
    }
};

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

/*Displaying elements on the screen, such as ponds, trees, etc.*/
void PrintPark(); 

/*Major function for displaying the national park*/
void PrintParkWoods();

#endif