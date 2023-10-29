#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <ncurses.h>

/*const char waves[5][3]={ 
    /*Static waves for pond*/

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

/*Displaying elements on the screen, such as ponds, trees, etc.*/
void PrintPark(); 

/*Major function for displaying the national park*/
void PrintParkWoods();


#endif