/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2023 by Aleksanteri Koivisto                            *
 *   juho.koivisto00@outlook.com                                           *
 *                                                                         *
 *   This program and it's source files are free software; you can redis-  *
 *   tribute it and/or modify it under the terms of the GNU General Public *
 *   License as published by the Free Software Foundation; either version 2*
 *   of the License, or (at your option) any later version.                *
 *                                                                         *
 *   This program is distributed in the hope that it will be enter-,       *
 *   taining and fun, but WITHOUT ANY WARRANTY; without even the implied   *
 *   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.      *
 *   See the GNU General Public License for more details.                  *
 *                                                                         *
 *                                                                         *
 ***************************************************************************/

/*********************************************************************

 NAME: Text adventure game / Tekstiseikkailupeli


 DESCRIPTION:


 VERSIONS:
       

       Version history:

**********************************************************************/

/*********************************************************************
                        Other comments  
------------------------------                                          
Minimum window size should be:
Lines(y):45
Cols(x):125               
------------------------------
---------------------------------------------------------------------
There could be a function which is always used when the game want's
save progress. The game creates, if one does not exist, a file and
write down the code there, so if you want to quit and continue later
you can use the password to skip to the point you were last time.
---------------------------------------------------------------------
---------------------------------------------------------------------
Everything graphical in the game is purely aesthetic, the player moves
and the game itself is played in a "hidden" x,y grid.
**********************************************************************/

#include <iostream>
#include <string>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include "environment.h"
#include "player.h"
#include "gamewindows.h"
#include "gamefunctions.h"
#include "language.h"
#include "titles_menus.h"

#if defined(_WIN32) || defined(_WIN64)
#include <ios>
#include <limits>
#include <windows.h>
#include <string.h>
#define WINDOWS_RESIZE_HANDLING
#endif

#if defined(__unix__) || defined(__linux__)
#include <string.h>
#define LINUX_RESIZE_HANDLING
#endif

/*Windows-specific code for handling resize*/
#ifdef WINDOWS_RESIZE_HANDLING

char ask_input() {    
    char cmd[6];
    fgets(cmd, 6, stdin);

    size_t len = strlen(cmd);
    if (len > 0 && cmd[len - 1] == '\n') {
        cmd[len - 1] = '\0';
    } else {
        // Handle the case where the input buffer is too small
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    fflush(stdin);  // Clear any remaining characters in the input buffer
    return cmd[0];
}

int ResizeWindowsTerminalToSmall_SYS() {
    system("mode con:cols=125 lines=45");
    if (system("mode con:cols=125 lines=45") != 0) {
      return 1;
    }

    else {
      return 0;
    }

  }

int ResizeWindowsTerminalToSmall_API(int8_t width, int8_t height) {
    COORD      coord = { width, height };
    SMALL_RECT rmin  = { 0, 0, 1, 1 };
    SMALL_RECT rect  = { 0, 0, width-1, height-1 };

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(Handle, TRUE, &rmin);
    SetConsoleScreenBufferSize(Handle, coord);
    SetConsoleWindowInfo(Handle, TRUE, &rect);

    if (!SetConsoleWindowInfo(Handle, TRUE, &rect)) {
        std::cerr<<"Error setting window size. Error code: "<< GetLastError() <<std::endl;
        return 1;  /*Return error*/
    }

    else {
      return 0;
    }

  }
#endif

/*Linux-specific code for handling resize*/
#ifdef LINUX_RESIZE_HANDLING

char ask_input() {    
    char cmd[6];
    fgets(cmd, 6, stdin);

    size_t len = strlen(cmd);
    if (len > 0 && cmd[len - 1] == '\n') {
        cmd[len - 1] = '\0';
    } else {
        /*If the input buffer is too small*/
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    fflush(stdin);  /*Clear any remaining characters in the input buffer*/
    return cmd[0];
}

int ResizeLinuxTerminal() {
  system("printf '\e[8;45;125t'");
  if (system("printf '\e[8;45;125t'") != 0) {
      return 1;
    }

    else {
      return 0;
    }
}
#endif


#define MIDDLE_Y_AXIS (LINES/2)
#define MIDDLE_X_AXIS (COLS/2)

int main(void) {
  int8_t min_win_x = 125;
  int8_t min_win_y = 45;
  Language selectedLanguage;

  #ifdef WINDOWS_RESIZE_HANDLING
  char input = '\0';
  int check_err = -1;
  int get_return_from_sys_call;

  First_Terminal_Setup();

  /*Flushing the input buffer so the prompt may not freeze*/
  fflush(stdin);

  do {
    input = toupper(ask_input());

    if (input == 'A') {
      check_err = ResizeWindowsTerminalToSmall_API(125, 45);

      if (check_err == 1) {
        std::cout<<"Attempt Failed";
        int get_return_from_sys_call = ResizeWindowsTerminalToSmall_SYS();
        if (get_return_from_sys_call == 1) {
          std::cout<<"Attempt to resize your terminal window wasn't successful, use other option";
        }

        else {
          std::cout<<"Starting the game...";
          check_err = 0;
        }
      }

      else {
        check_err = 0;
      }

    }

    else if (input == 'B') {
      check_err = 0;
      std::cout<<"Starting the game...";
    }

    else {
      std::cout<<"Invalid choice. Please enter A or B."<<std::endl;
      std::cout<<"Virhe, syota joko A tai B."<<std::endl;
    }

  } while ((input != 'A' && input != 'B') || check_err != 0 );
    
#endif

#ifdef LINUX_RESIZE_HANDLING
  char input = '\0';
  int check_err = -1;

  First_Terminal_Setup();

  /*Flushing the input buffer so the prompt may not freeze*/
  fflush(stdin);

  do {
    input = toupper(ask_input());

    if (input == 'A') {
      check_err = ResizeLinuxTerminal();

      if (check_err == 1) {
        std::cout<<"Attempt to resize your terminal window wasn't successful,"<<std::endl;
        std::cout<<"use other option";
        }

        else {
          std::cout<<"Starting the game...";
          check_err = 0;
        }
      }

    else if (input == 'B') {
      check_err = 0;
      std::cout<<"Starting the game...";
    }

    else {
      std::cout<<"Invalid choice. Please enter A or B."<<std::endl;
      std::cout<<"Virhe, syota joko A tai B."<<std::endl;
    }

  } while ((input != 'A' && input != 'B') || check_err != 0 );
  
#endif
/*---------------------------Error Checks-----------------------------*/
  initscr();
  clear();
  has_colors();

  if (has_colors() == FALSE) {
    endwin();
    std::cout<<"Your terminal does not support color"<<std::endl;
    std::cout<<" .. .. ..                         .."<<std::endl;
    std::cout<<"Kayttamasi terminaali ei tue vareja"<<std::endl;
    napms(3000);
    exit(1);
  }

  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK); /*FIRST languagemenu background and text*/
  init_pair(3, COLOR_CYAN, COLOR_CYAN); /*FIRST menu decorations*/
  init_pair(5, COLOR_BLACK, COLOR_CYAN); /*Select language text*/
  init_pair(8, COLOR_BLACK, COLOR_GREEN);  /*Forest*/
  init_pair(7, COLOR_WHITE, COLOR_BLUE); /*Water*/
  init_pair(6, COLOR_RED, COLOR_GREEN); /*Error*/
  init_pair(9, COLOR_BLACK, COLOR_GREEN); /*for menu title and underline*/
  curs_set(0);
/*------------------------------------------------------------------*/

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^PROGRAM^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
  int languagechoice;
  LanguageSelectMenu(MIDDLE_Y_AXIS, MIDDLE_X_AXIS);
  keypad(stdscr, TRUE);
  noecho();
  nodelay(stdscr, TRUE);

  while (languagechoice != KEY_F(1) 
    && languagechoice != KEY_F(2)
    && languagechoice != KEY_F(3)) {
    languagechoice = getch();
    switch (languagechoice) {
        case KEY_F(1):
        clear();
        delwin(stdscr);
        endwin();
        return 0;
        break;

        case KEY_F(2):
        selectedLanguage = Language::ENGLISH;
        break;

        case KEY_F(3):
        selectedLanguage = Language::FINNISH;
        break;

        case KEY_F(10):
        NULL; /*Placeholder*/
        break;

        default:
        NULL;
        break;
    }
  }

  attron(COLOR_PAIR (1));
  mvaddstr(MIDDLE_Y_AXIS+15, MIDDLE_X_AXIS-22, "You have chosen a language / Olet valinnut kielen");
  attroff(COLOR_PAIR (1));
  refresh();
  napms(5000);
  clear();

  /*--------------------First part of the story---------------------*/
  Map ParkMap(15, 15, 3, 3, 7, 7, 15, 15, "Part 1: Into the unknown / Osa 1: Kohti tuntematonta");
  int playerpark_y=ParkMap.playerpos_y;
  int playerpark_x=ParkMap.playerpos_x;
  Player firstplayer(playerpark_x, playerpark_y);
  attron(COLOR_PAIR (1));
  ParkMap.Print_Chapter_text(MIDDLE_Y_AXIS, MIDDLE_X_AXIS-22);
  attroff(COLOR_PAIR (1));
  refresh();
  napms(5000);

  PrintPark();
  PrintDebugInfo(); /*temp*/
  refresh();

  /*test*/
  WINDOW* dialogueBox = newwin(5, 30, LINES-10, MIDDLE_X_AXIS-15);
  box(dialogueBox, 0, 0);
  wrefresh(dialogueBox);
  mvwprintw(dialogueBox, 1, 1, "This is a dialogue box!");
  wrefresh(dialogueBox);
  napms(5000);
  destroy_win(dialogueBox);
  PrintPark();
  PrintDebugInfo(); /*temp*/
  refresh();
  /**/
  
  /*while (playerpark_x != ParkMap.exit_x && playerpark_y != ParkMap.exit_y) {
    
  }
  refresh();*/
  napms(10000); /*temp*/
/*------------------------------------------------------------------*/

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
  endwin();
  return 0;
}