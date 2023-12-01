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
 *   However, all the rights are reserved regarding the game's story itself*
 *   and all the fictional characters who are making appearance            *
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
       

       Version history: 1.12.2023 ~830 lines of code

**********************************************************************/

/*********************************************************************
                          Other comments  
------------------------------                                          
Minimum window size:
Lines(y):45
Cols(x):125   
------------------------------
---------------------------------------------------------------------
The printing cases differ based on the size of the terminal stepwise
with the following lines and cols sizes:

Lines(y):55
Cols(x):160   //for most laptops might get these values on fullscreen

Lines(y):62
Cols(x):230

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
#include <cmath>
#include "environment.h"
#include "player.h"
#include "gamewindows.h"
#include "gamefunctions.h"
#include "language.h"
#include "titles_menus.h"
#include "map_class.h"
#include "woods_classes.h"

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
        /*Handling the case where the input buffer is too small*/
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    fflush(stdin);  /*Clear any remaining characters in the input buffer*/
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
        return 1;
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
  
  /*Defining the size of the terminal window and storing the information
   So that it can be used easily when conditionally printing the game's
   aesthetics depending on the window's size. At the same time checks
   if the user's own decided window size is too small to play the game
   if none of these following conditions are true*/

  float terminal_window_size;

  /*if either in following condition checks lines or cols are bigger than
  their condition 1 or 2, save which one is and then pass it to printing functions*/
  char condition_exceeding_var = 'n'; /*Default value null*/

  if (LINES >= 45 && COLS >= 125 && LINES < 53 && COLS < 160) {
      terminal_window_size = 1; /*smallest possible*/
  }

  else if (LINES >= 53 && COLS < 160 && COLS >= 125) {
      terminal_window_size = 1.5;
      condition_exceeding_var = 'l'; /*if LINES is bigger than for condition 1*/
    }

  else if (LINES < 53 && COLS >= 160 && LINES >= 45) {
      terminal_window_size = 1.5;
      condition_exceeding_var = 'c'; /*if COLS is bigger than for condition 1*/
    }
  
  else if (LINES >= 53 && COLS >= 160 && LINES < 62 && COLS < 230) {
      terminal_window_size = 2; /*breakpoint for visuals if the window is medium big*/
  }

  else if (LINES >= 62 && COLS < 230 && COLS >= 160) {
      terminal_window_size = 2.5;
      condition_exceeding_var = 'l'; /*if LINES is bigger than for condition 2*/
    }

    else if (LINES < 62 && COLS >= 230 && LINES >= 53) {
      terminal_window_size = 2.5;
      condition_exceeding_var = 'c'; /*if COLS is bigger than for condition 2*/
    }

  else if (LINES >= 62 && COLS >= 230) {
    terminal_window_size = 3; /*breakpoint for visuals if the window is fullscreen or >*/
  }

  else if (LINES < 45 || COLS < 125) {
    attron(COLOR_PAIR (1));
    mvaddstr(MIDDLE_Y_AXIS, MIDDLE_X_AXIS-18, "The terminal size you chose is too small");
    mvaddstr(MIDDLE_Y_AXIS+1, MIDDLE_X_AXIS-18, "Restart the game and expand it more");

    mvaddstr(MIDDLE_Y_AXIS+3, MIDDLE_X_AXIS-18, "Valitsemasi ikkunan koko on liian pieni");
    mvaddstr(MIDDLE_Y_AXIS+4, MIDDLE_X_AXIS-18, " ..                         ......");
    mvaddstr(MIDDLE_Y_AXIS+5, MIDDLE_X_AXIS-18, "Kaynnista peli uudestaan ja saada ikkuna isommaksi");
    attroff(COLOR_PAIR (1));
    refresh();
    napms(5000);
    endwin();
    return 0;
  }

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
  napms(1000);
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
  napms(1000);

  PrintPark(/*terminal_window_size*/);
  PrintParkWoods(terminal_window_size, condition_exceeding_var);
  //PrintDebugInfo(terminal_window_size, condition_exceeding_var); /*temp*/
  refresh();

  /*----------test----------*/
  WINDOW* dialogueBox = newwin(7, 35, LINES-8, MIDDLE_X_AXIS-18);
  box(dialogueBox, 0, 0);
  wrefresh(dialogueBox);
  mvwprintw(dialogueBox, 1, 1, "This is a dialogue box!");
  wrefresh(dialogueBox);
  napms(5000);
  //PrintPark(/*terminal_window_size*/);
  //PrintParkWoods(terminal_window_size);
  //PrintDebugInfo(); /*temp*/
  //refresh();
  /*------------------------*/
  
  /*while (playerpark_x != ParkMap.exit_x && playerpark_y != ParkMap.exit_y) {
    
  }
  refresh();*/
  //napms(10000); /*temp*/
  int end_debug; /*temp*/
  while (end_debug != KEY_F(1)) {
    end_debug=getch(); /*temp*/
  }

  destroy_win(dialogueBox);
  delwin(dialogueBox);

/*------------------------------------------------------------------*/

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
  endwin();
  return 0;
}