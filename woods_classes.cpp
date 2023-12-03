#include "woods_classes.h"

Tree::Tree(int x_livingarea, int y_livingarea) {
    this -> x_livingarea = x_livingarea;
    this -> y_livingarea = y_livingarea;

}

/*------------------------------------*/
ThickTree::ThickTree(int x_livingarea, int y_livingarea) : Tree(x_livingarea, y_livingarea) {
    
}

void ThickTree::SpawnThick(int up_y, int up_x, int mid_y, int mid_x, int bottom_y, int bottom_x) {
    mvaddstr(up_y, up_x, " /|\\");
    mvaddstr(mid_y, mid_x, "//|\\\\");
    mvaddstr(bottom_y, bottom_x, "   I");
}

int ThickTree::SpawnThick_in_Window(WINDOW *win, int up_y, int up_x, int mid_y, int mid_x, int bottom_y, int bottom_x) {
    mvwprintw(win, up_y, up_x, " /|\\");
    
    if (mvwprintw(win, up_y, up_x, " /|\\") == ERR) {
      attron(COLOR_PAIR(6));
      mvaddstr(LINES-LINES+8,COLS-COLS+1, "Error upspawnthick");
      attroff(COLOR_PAIR(6));
      refresh();
      return 1;
    }

    mvwprintw(win, mid_y, mid_x, "//|\\\\");

    if (mvwprintw(win, mid_y, mid_x, "//|\\\\") == ERR) {
      attron(COLOR_PAIR(6));
      mvaddstr(LINES-LINES+8,COLS-COLS+1, "Error midspawnthick");
      attroff(COLOR_PAIR(6));
      refresh();
      return 1;
    }

    mvwprintw(win, bottom_y, bottom_x, "  I");

    if (mvwprintw(win, bottom_y, bottom_x, "  I") == ERR) {
      attron(COLOR_PAIR(6));
      mvaddstr(LINES-LINES+8,COLS-COLS+1, "Error bottomspawnthick");
      attroff(COLOR_PAIR(6));
      refresh();
      return 1;
    }

    wrefresh(win);

    return 0;
    
}
/*------------------------------------*/

/*------------------------------------*/
ThinTree::ThinTree(int x_livingarea, int y_livingarea) : Tree(x_livingarea, y_livingarea) {
    
}

void ThinTree::SpawnThin(int up_y, int up_x, int mid_y, int mid_x, int bottom_y, int bottom_x) {
    mvaddstr(up_y, up_x, "  ^");
    mvaddstr(mid_y, mid_x, " /|\\");
    mvaddstr(bottom_y, bottom_x, "  I");
}

int ThinTree::SpawnThin_in_Window(WINDOW *win, int up_y, int up_x, int mid_y, int mid_x, int bottom_y, int bottom_x) {
    mvwprintw(win, up_y, up_x, "  ^");

    if (mvwprintw(win, up_y, up_x, "  ^") == ERR) {
      attron(COLOR_PAIR(6));
      mvaddstr(LINES-LINES+8,COLS-COLS+1, "Error upspawnthick");
      attroff(COLOR_PAIR(6));
      refresh();
      return 1;
    }

    mvwprintw(win, mid_y, mid_x, " /|\\");

    if (mvwprintw(win, mid_y, mid_x, " /|\\") == ERR) {
      attron(COLOR_PAIR(6));
      mvaddstr(LINES-LINES+8,COLS-COLS+1, "Error midspawnthick");
      attroff(COLOR_PAIR(6));
      refresh();
      return 1;
    }

      mvwprintw(win, bottom_y, bottom_x, "  I");

      if (mvwprintw(win, bottom_y, bottom_x, "  I") == ERR) {
      attron(COLOR_PAIR(6));
      mvaddstr(LINES-LINES+8,COLS-COLS+1, "Error bottomspawnthick");
      attroff(COLOR_PAIR(6));
      refresh();
      return 1;
    }

      wrefresh(win);

      return 0;
}
/*------------------------------------*/

/*------------------------------------*/
Esker::Esker(int width) {
    this -> width = width; //placeholder
}

void Esker::SpawnEsker(int up_y, int up_x, int mid_y, int mid_x) {
    mvaddstr(up_y, up_x, " _");
    mvaddstr(mid_y, mid_x, " / \\");
}

void Esker::SpawnEsker_in_Window(WINDOW *win, int up_y, int up_x, int mid_y, int mid_x) {
    mvwprintw(win, up_y, up_x, " _");
    mvwprintw(win, mid_y, mid_x, "/ \\");
    wrefresh(win);
}

void Esker::SpawnBig_Esker_in_Window(WINDOW *win, int up_y, int up_x, int mid_y, int mid_x) {
    mvwprintw(win, up_y, up_x, " __");
    mvwprintw(win, mid_y, mid_x, "/  \\");
    wrefresh(win);
}
/*------------------------------------*/

/*------------------------------------*/
Cabin::Cabin(std::string owner_name) {
    this -> owner_name = owner_name; //placeholder
}

void Cabin::SpawnCabin(int top_y, int top_x,
                    int mid_y, int mid_x,
                    int bottom_y, int bottom_x) 
    {
      mvaddstr(top_y, top_x, "  _|");
      mvaddstr(mid_y, mid_x, "/   \\");
      mvaddstr(bottom_y, bottom_x, "|___|");
    }

void Cabin::SpawnCabin_in_Window(WINDOW *win, int top_y, int top_x,
                              int mid_y, int mid_x,
                              int bottom_y, int bottom_x) 
    {
      mvwprintw(win, top_y, top_x, "  _|");
      mvwprintw(win, mid_y, mid_x, "/   \\");
      mvwprintw(win, bottom_y, bottom_x, "|___|");
      wrefresh(win);
    }
/*------------------------------------*/