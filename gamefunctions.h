#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include <string>
#include <ncurses.h>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>

WINDOW *Text_window(int height, int width, int starty, int startx);

std::string Userinput();

void WriteDialogue();

void PrintDebugInfo();

#endif