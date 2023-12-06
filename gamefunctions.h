#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include <iostream>
#include <string>
#include <curses.h>
#include <algorithm>

std::string TESTUserinput(WINDOW* localwin, float& terminal_window_size);

void WriteDialogue();

void PrintDebugInfo(float& first_debug_item, char& line_col_exceeding);

#endif