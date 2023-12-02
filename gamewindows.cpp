#include "gamewindows.h"

WINDOW *create_middle_pond(int height, int width, int starty, int startx) {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    wbkgd(local_win, COLOR_PAIR(7));
    wrefresh(local_win);
    return local_win;
}

WINDOW *cr_rightsideof_pond(int height, int width, int starty, int startx) {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    wbkgd(local_win, COLOR_PAIR(7));
    wrefresh(local_win);
    return local_win;
}

WINDOW *cr_leftsideof_pond(int height, int width, int starty, int startx) {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    wbkgd(local_win, COLOR_PAIR(7));
    wrefresh(local_win);
    return local_win;
}

WINDOW *cr_parktrees(int height, int width, int starty, int startx) {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    wbkgd(local_win, COLOR_PAIR(8));
    wrefresh(local_win);
    return local_win;
}

WINDOW *cr_eskers(int height, int width, int starty, int startx) {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    wbkgd(local_win, COLOR_PAIR(8));
    wrefresh(local_win);
    return local_win;
}

WINDOW *Text_window(int height, int width, int starty, int startx) {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    wbkgd(local_win, COLOR_PAIR(1));
    wrefresh(local_win);
    return local_win;
}

void destroy_win(WINDOW *local_win) {
  wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  wrefresh(local_win);
  delwin(local_win);
}