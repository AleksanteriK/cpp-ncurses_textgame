#ifndef CHAPTERS_H
#define CHAPTERS_H
#include <curses.h>
#include <string>
class Chapter {
public:
    std::string introduction_text = "";
    std::string ending_text = ""; //the ending text will be set depending on the outcome

    void setIntroduction_text(std::string introduction_text);
    void setEnding_text(std::string ending_text);
    void Print_Introduction_text(int y, int x);
    void Print_Ending_text(int y, int x);
};

#endif