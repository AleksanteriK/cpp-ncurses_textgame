#include "titles_menus.h"

void LanguageSelectMenu(int y, int x) {
  clear();
  bkgd(COLOR_PAIR(1));
  attron(COLOR_PAIR (3));
  mvaddstr(y-6, x-14, "****************************");
  mvaddstr(y-5, x-14, "*");
  mvaddstr(y-5, x+13, "*");
  mvaddstr(y-4, x-14, "*                          *");
  mvaddstr(y-3, x-14, "*");
  mvaddstr(y-3, x+13, "*");
  mvaddstr(y-2, x-14, "*");
  mvaddstr(y-2, x-14, "****************************");
  attroff(COLOR_PAIR (3));

  attron(COLOR_PAIR (5));
  mvaddstr(y-5, x-13, "      Select Language     ");
  mvaddstr(y-3, x-13, "       Valitse Kieli      ");
  attroff(COLOR_PAIR (5));
  mvaddstr(y+3, x-14, "-      F2) English         -");
  mvaddstr(y+4, x-14, "-      F3) Suomi           -");
  mvaddstr(y+5, x-14, "-     F10) About/Tietoja   -");
  mvaddstr(y+10, x-14, "       F1 QUIT/POISTU        ");
  refresh();
};