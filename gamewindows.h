#ifndef GAMEWINDOWS_H
#define GAMEWINDOWS_H

#include <ncurses.h>

WINDOW *create_middle_pond(int height, int width, int starty, int startx);
WINDOW *cr_leftsideof_pond(int height, int width, int starty, int startx);
WINDOW *cr_rightsideof_pond(int height, int width, int starty, int startx);
WINDOW *cr_parktrees(int height, int width, int starty, int startx);
WINDOW *cr_eskers(int height, int width, int starty, int startx);

#endif