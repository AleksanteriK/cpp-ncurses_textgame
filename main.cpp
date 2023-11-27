/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2023 by Aleksanteri Koivisto                            *
 *   juho.koivisto00@outlook.com                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
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
#include <thread> /*Making a syscall in it's own thread*/
#include <cstdlib>  /*For syscalls*/
/*Thread doesn't seem to work on my compiler at the moment*/
#include "environment.h"
#include "player.h"
#include "gamewindows.h"
#include "gamefunctions.h"
#include "language.h"
#include "titles_menus.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define WINDOWS_RESIZE_HANDLING
#endif

#if defined(__unix__) || defined(__linux__)
#include <csignal>
#include <unistd.h>
#define UNIX_RESIZE_HANDLING
#endif

/*Windows-specific code for handling resize*/
#ifdef WINDOWS_RESIZE_HANDLING
int HandleWindowsResizeToSmall() {
  HWND consoleWindow;
  consoleWindow = GetConsoleWindow();
    if (consoleWindow == NULL) {
        std::cerr <<"Error retrieving window handle. Error code: "<< GetLastError() <<std::endl;
        return 1;  /*Return an error*/
    }

    if (!IsWindowVisible(consoleWindow)) {
        std::cerr << "Error: Console window is not visible." << std::endl;
        return 1;  // Return an error*/
    }

    SMALL_RECT windowSize = {0, 0, 123, 43};
    if (!SetConsoleWindowInfo(consoleWindow, TRUE, &windowSize)) {
        std::cerr<<"Error setting window size. Error code: "<< GetLastError() <<std::endl;
        return 1;  /*Return error*/
    }

    std::cout<<"Window handle: "<<consoleWindow<<std::endl;
    std::cout<<"Setting window size to: "<< windowSize.Right - windowSize.Left + 1
    <<"x"<<windowSize.Bottom - windowSize.Top + 1<<std::endl;

    return 0;  /*Return 0 to indicate success*/
  }
#endif

/*Linux-specific code for handling resize*/
#ifdef LINUX_RESIZE_HANDLING
void HandleLinuxResize(int signo) {
    //NULL
}
#endif


#define MIDDLE_Y_AXIS (LINES/2)
#define MIDDLE_X_AXIS (COLS/2)

int main(void) {
  Language selectedLanguage;
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

  clear();
  endwin();

#ifdef WINDOWS_RESIZE_HANDLING
  int terminalchoice=0;
  int check_err = -1;
  std::cout<<"/EN/ Choose your terminal window's size"<<std::endl;
  std::cout<<"/EN/ You can either choose to play in a prefixed small window"<<std::endl;
  std::cout<<"/EN/ or you can expand the window to fullscreen or somewhere between"<<std::endl;
  std::cout<<"/EN/ but the size must be at least 45 characters tall and 125 characters wide"<<std::endl;
  std::cout<<"/EN/ Insert 1 and press enter if you want to play in a small window"<<std::endl;
  std::cout<<"/EN/ Insert 2 and press enter if you want to play in your own specified window size\n"<<std::endl;
  std::cout<<"                            !!!NOTE!!!"<<std::endl;
  std::cout<<"      Set the terminal window size before you continue with F2\n"<<std::endl;
  std::cout<<"-------------------------------------------------------------------------------------"<<std::endl;
  std::cout<<"/FI/ Valitse terminaalisi ikkunan koko"<<std::endl;
  std::cout<<"/FI/ Voit valita joko pelata valmiiksi maaritellyssä pienessa ikkunassa"<<std::endl;
  std::cout<<"/FI/ tai voit laajentaa ikkunan koko naytolle tai johonkin silta valilta"<<std::endl;
  std::cout<<"/FI/ mutta ikkunan koon on oltava vahintaan 45 merkkia korkea ja 125 merkkia levea\n"<<std::endl;
  std::cout<<"/FI/ Syota 1 pelataksesi pienessa ikkunassa"<<std::endl;
  std::cout<<"/FI/ Syota 2 pelataksesi omassa maaritetyssa ikkunakoossa\n"<<std::endl;
  std::cout<<"                           !!!HUOM!!! "<<std::endl;
  std::cout<<"     Aseta terminaali-ikkunan koko ennen kuin jatkat F2:lla\n"<<std::endl;

  /*do {
    std::cin>>terminalchoice;

    if (terminalchoice==1) {
      check_err=ResizeWindowsTerminalToSmall();
      if (check_err == 1) {
        std::cout<<"Error setting window size using mode con command."<<std::endl;
        std::cout<<"Choose other option"<<std::endl;
        std::cout<<"Virhe ikkunakoon asettamisessa kayttaen mode con -komentoa." <<std::endl;
        std::cout<<"Valitse toinen vaihtoehto.\n"<<std::endl;
      }

    }

    else if (terminalchoice==2) {
      check_err = 0;
      std::cout<<"Starting the game...";
    }

    else {
      std::cout<<"Invalid choice. Please enter 1 or 2."<<std::endl;
      std::cout<<"Virhe, syota joko 1 tai 2."<<std::endl;
    }

  } while ((terminalchoice != 1 && terminalchoice != 2) || check_err != 0 );*/

  do {
    std::cin>>terminalchoice;

    if (terminalchoice==1) {
      check_err=HandleWindowsResizeToSmall();

      /*if (check_err==1) {
        system("mode con:cols=125 lines=45");

        if (system("mode con:cols=125 lines=45") != 0) {
          int debugpause;
          std::cout<<"Error setting window size using mode con command."<<std::endl;
          std::cout<<"Choose other option"<<std::endl;
          std::cout<<"Virhe ikkunakoon asettamisessa kayttaen mode con -komentoa." <<std::endl;
          std::cout<<"Valitse toinen vaihtoehto.\n"<<std::endl;
          std::cin>>debugpause;
          check_err = 0;
        }

      }
      
      else {
        check_err = 0;
      }*/
    }

    else if (terminalchoice==2) {
      check_err = 0;
      std::cout<<"Starting the game...";
    }

    else {
      std::cout<<"Invalid choice. Please enter 1 or 2."<<std::endl;
      std::cout<<"Virhe, syota joko 1 tai 2."<<std::endl;
    }

  } while ((terminalchoice != 1 && terminalchoice != 2) || check_err != 0 );
    
#endif

#ifdef LINUX_RESIZE_HANDLING
    //NULL
#endif

  initscr();
  clear();
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