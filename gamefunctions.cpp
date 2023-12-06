#include "gamefunctions.h"

#define MIDDLE_Y_AXIS (LINES/2)
#define MIDDLE_X_AXIS (COLS/2)

std::string TESTUserinput(WINDOW* localwin, float& terminal_window_size) {
    std::string input;
    bool isbigdialoguebox = FALSE;
    
    if (COLS > 300) {
        isbigdialoguebox = TRUE;
    }

    if (terminal_window_size < 2.5 && isbigdialoguebox == FALSE) {
        echo();
        wmove(localwin, 13, 2);
        wgetnstr(localwin, &input[0], COLS - 45);
        noecho();
        //Remove trailing newline character
        input.erase('\n');
        std::cout<<input<<std::endl;
    } 

    else if (terminal_window_size >= 2.5 && terminal_window_size <= 3.1 && isbigdialoguebox == FALSE) {
        echo();
        wmove(localwin, 18, 2);
        wgetnstr(localwin, &input[0], COLS - 45);
        noecho();
        //Remove trailing newline character
        input.erase('\n');
        std::cout<<input<<std::endl;
    }

    else if (isbigdialoguebox == TRUE && LINES > 70) {
        echo();
        wmove(localwin, 25, 2);
        wgetnstr(localwin, &input[0], COLS - 45);
        noecho();
        //Remove trailing newline character
        input.erase('\n');
        std::cout<<input<<std::endl;
    }

    return input;
}

void WriteDialogue() {
    /*Logic for game-related output, conversations, and text*/
}

void PrintDebugInfo(float& first_debug_item, char& line_col_exceeding) {
   if (LINES>=45 && LINES<=75) {
  attron(COLOR_PAIR(6));
  mvaddstr(LINES - 8, COLS - 33, "Terminal size:");
  mvprintw(LINES - 7, COLS - 33, "Lines: %d",LINES);
  mvprintw(LINES - 6, COLS - 33, "Cols: %d",COLS);
  mvprintw(LINES - 5, COLS - 33, "mid_y: %d", MIDDLE_Y_AXIS);
  mvprintw(LINES - 4, COLS - 33, "mid_x: %d", MIDDLE_X_AXIS);
  mvprintw(LINES - 3, COLS - 33, "terminal_window_size: %f", first_debug_item);
  mvprintw(LINES - 2, COLS - 33, "exceeding variable: %c", line_col_exceeding);
  attroff(COLOR_PAIR(6));
  }

  else {
  attron(COLOR_PAIR(6));
  mvaddstr(40, 1, "Terminal size:");
  mvprintw(41, 1, "Lines: %d",LINES);
  mvprintw(42, 1, "Cols: %d",COLS);
  mvprintw(43, 1, "mid_y: %d", MIDDLE_Y_AXIS);
  mvprintw(45, 1, "mid_x: %d", MIDDLE_X_AXIS);
  mvprintw(46, 1, "terminal_window_size: %f",first_debug_item);
  mvprintw(47, 1, "exceeding variable: %c", line_col_exceeding);
  attroff(COLOR_PAIR(6));
  }
}