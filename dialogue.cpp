#include "dialogue.h"
#include "gamewindows.h"

void Dialogue::SetHeight(int height) {
    this -> height = height;
    }

void Dialogue::SetCurrentLine(int currentline) {
    this -> currentline = currentline;
    }

int Dialogue::GetHeight() {
    return height;
}

int Dialogue::GetCurrentLine() {
    return currentline;
}

void Dialogue::AddDialogue(const std::string& line) {
    if (currentline == 1) {
        /*Erasing the previous text from the line*/
        for (int i = 2; i <= COLS - 34; i++) {
            attron(COLOR_PAIR(1));
            mvwprintw(dialogueBox, currentline, i, " ");
            attroff(COLOR_PAIR(1));
        }
        wrefresh(dialogueBox);
        SetCurrentLine(height - 1);
        attron(COLOR_PAIR(1));
        mvwprintw(dialogueBox, currentline, 2, line.c_str());
        attroff(COLOR_PAIR(1));
        wrefresh(dialogueBox);
    } 
    
    else {
        /*Scrolling effect: Move the content of the line above to the current line*/
        SetCurrentLine(currentline - 1);
        for (int i = 2; i <= COLS - 34; i++) {
            chtype ch = mvwinch(dialogueBox, currentline, i);
            attron(ch & A_COLOR);
            mvwaddch(dialogueBox, currentline + 1, i, ch & A_CHARTEXT);
            attroff(ch & A_COLOR);
        }
        wrefresh(dialogueBox);

        /*Print the new line at the current position*/
        attron(COLOR_PAIR(1));
        mvwprintw(dialogueBox, currentline, 2, line.c_str());
        attroff(COLOR_PAIR(1));
        wrefresh(dialogueBox);
    }
}

void Dialogue::ActivateDialogueBox(float& terminal_window_size) {
    bool bigdialoguebox = FALSE;
    int startRow;
  
    if (COLS > 300) {
        bigdialoguebox = TRUE;
    }
  
    if (terminal_window_size < 2.5 && bigdialoguebox == FALSE) {
        SetHeight(13);
        dialogueBox = newwin(15, COLS, LINES - 15, 0);
        startRow = LINES-12;
        box(dialogueBox, 0, 0);
        //Print the command prompt at the bottom
        mvwprintw(dialogueBox, 13, 1, ">");
        wrefresh(dialogueBox);
        refresh();
    } 

    else if (terminal_window_size >= 2.5 && terminal_window_size <= 3.1 && bigdialoguebox == FALSE) {
        SetHeight(18);
        dialogueBox = newwin(20, COLS, LINES - 20, 0);
        startRow = LINES-17;
        box(dialogueBox, 0, 0);
        //Print the command prompt at the bottom
        mvwprintw(dialogueBox, 18, 1, ">");
        wrefresh(dialogueBox);
        refresh();
    }

    else if (bigdialoguebox == TRUE && LINES > 70) {
        SetHeight(25);
        dialogueBox = newwin(27, COLS, LINES - 27, 0);
        startRow = LINES-24;
        box(dialogueBox, 0, 0);
        //Print the command prompt at the bottom
        mvwprintw(dialogueBox, 25, 1, ">");
        wrefresh(dialogueBox);
        refresh();
    }
}
