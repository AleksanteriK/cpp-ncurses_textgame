#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

class Dialogue {
public:
    WINDOW *dialogueBox;
    void addDialogue(const std::string& line);
    void printDialogBox(float& terminal_window_size);
    void setHeight(int height);
    void setCurrentLine(int currentLine);

private:
    int height;
    int currentLine;
    std::vector<std::string> dialoguebuffer;
};