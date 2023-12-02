#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include <iostream>
#include <string>
#include <curses.h>

std::string Userinput();

void WriteDialogue();

void PrintDebugInfo(float& first_debug_item, char& line_col_exceeding);

#endif