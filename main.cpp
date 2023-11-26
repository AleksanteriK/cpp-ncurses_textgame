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
#include "environment.h"
#include "player.h"
#include "gamewindows.h"
#include "gamefunctions.h"
#include "language.h"
#include "titles_menus.h"

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

  if ((LINES<45 || COLS<125) || (LINES<45 && COLS<125)) {
    endwin();
    std::cout<<"/EN/ Your terminal is too small, expand it and launch again!"<<std::endl;
    std::cout<<"      ..    ..                                         .."<<std::endl;
    std::cout<<"/FI/ Kayttamasi terminaali on liian pieni, suurenna sita"<<std::endl;
    std::cout<<"                                       .."<<std::endl;
    std::cout<<"     tai vaihda terminaalia ja kaynnista uudelleen\n"<<std::endl;
    napms(5000);
    return 0;
  }

  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK); /*FIRST menu background and text*/
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