#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <curses.h>
#include <ncurses.h>
#include <unistd.h>
#include <vector>


/*Displaying elements on the screen, such as ponds, trees, etc.*/
void PrintPark(/*std::string& terminal_window_size*/); 

/*Major function for displaying the national park*/
void PrintParkWoods(float terminal_window_size, char& line_col_exceeding);

#endif