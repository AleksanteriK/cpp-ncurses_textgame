#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

class Dialogue {
public:
    WINDOW *dialogueBox;
    //std::vector<std::string> dialoguebuffer;
    void AddDialogue(const std::string& line);
    void ActivateDialogueBox(float& terminal_window_size);
    void SetHeight(int height);
    void SetCurrentLine(int currentline);
    int GetCurrentLine();
    int GetHeight();

private:
    int height;
    int currentline;
};