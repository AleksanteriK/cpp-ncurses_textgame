#include "chapters.h"

void Chapter::Print_Introduction_text(int y, int x) {
    mvprintw(y,x,"%s",introduction_text.c_str());
}

void Chapter::Print_Ending_text(int y, int x) {
    mvprintw(y,x,"%s",ending_text.c_str());
}

void Chapter::setIntroduction_text(std::string introduction_text) {
    attron(COLOR_PAIR (1));
    this -> introduction_text = introduction_text;
    attroff(COLOR_PAIR (1));
}

void Chapter::setEnding_text(std::string ending_text) {
    attron(COLOR_PAIR (1));
    this -> ending_text = ending_text;
    attroff(COLOR_PAIR (1));
}