#include "dialog.h"
#include "gamewindows.h"

void Dialogue::setHeight(int newHeight) {
        height = newHeight;
        dialoguebuffer.resize(newHeight);
    }

void Dialogue::setCurrentLine(int currentLine) {
        currentLine = currentLine;
    }

void Dialogue::addDialogue(const std::string& line) {
        dialoguebuffer[currentLine] = line;
        currentLine = (currentLine + 1) % height;
    }

void Dialogue::printDialogBox(float& terminal_window_size) {
    WINDOW *dialogueBox;
    bool bigdialoguebox = FALSE;
    int startRow;
  
    if (COLS > 300) {
        bigdialoguebox = TRUE;
    }
  
    if (terminal_window_size < 2.5 && bigdialoguebox == FALSE) {
        setHeight(12);
        setCurrentLine(0);
        dialogueBox = newwin(15, COLS, LINES - 15, 0);
        dialoguebuffer.resize(12, "");
        startRow = LINES-12;
        box(dialogueBox, 0, 0);
        // Print the command prompt at the bottom
        mvwprintw(dialogueBox, 13, 1, "|> ");

        // Print the dialogue lines
        attron(COLOR_PAIR(7)); //debug
        for (int i = 0; i < height; ++i) {
            mvwprintw(dialogueBox, startRow + i, 0, dialoguebuffer[(currentLine + i) % height].c_str());
        }
        attroff(COLOR_PAIR(7)); //debug
        wrefresh(dialogueBox);
        refresh();
    } 

    else if (terminal_window_size >= 2.5 && terminal_window_size <= 3.1 && bigdialoguebox == FALSE) {
        setHeight(17);
        setCurrentLine(0);
        dialogueBox = newwin(20, COLS, LINES - 20, 0);
        dialoguebuffer.resize(17, "");
        startRow = LINES-17;
        box(dialogueBox, 0, 0);
        // Print the command prompt at the bottom
        mvwprintw(dialogueBox, 18, 1, "|> ");

        // Print the dialogue lines
        attron(COLOR_PAIR(7)); //debug
        for (int i = 0; i < height; ++i) {
            mvwprintw(dialogueBox, startRow + i, 0, dialoguebuffer[(currentLine + i) % height].c_str());
        }
        attroff(COLOR_PAIR(7)); //debug
        wrefresh(dialogueBox);
        refresh();
    }

    else if (bigdialoguebox == TRUE && LINES > 70) {
        setHeight(24);
        setCurrentLine(0);
        dialogueBox = newwin(27, COLS, LINES - 27, 0);
        dialoguebuffer.resize(24, "");
        startRow = LINES-24;
        box(dialogueBox, 0, 0);
        // Print the command prompt at the bottom
        mvwprintw(dialogueBox, 25, 1, "|> ");

        // Print the dialogue lines
        attron(COLOR_PAIR(7)); //debug
        for (int i = 0; i < height; ++i) {
            mvwprintw(dialogueBox, startRow + i, 0, dialoguebuffer[(currentLine + i) % height].c_str());
        }
        attroff(COLOR_PAIR(7));
        wrefresh(dialogueBox);
        refresh();
    }
}
