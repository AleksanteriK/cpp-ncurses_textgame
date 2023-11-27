#include "titles_menus.h"

void First_Terminal_Setup() {
  std::cout<<"/EN/ Choose your terminal window's size"<<std::endl;
  std::cout<<"/EN/ You can either choose to play in a prefixed small window"<<std::endl;
  std::cout<<"/EN/ or you can expand the window to fullscreen or somewhere between"<<std::endl;
  std::cout<<"/EN/ but the size must be at least 45 characters tall and 125 characters wide"<<std::endl;
  std::cout<<"/EN/ Insert A and press enter if you want to play in a small window"<<std::endl;
  std::cout<<"/EN/ Insert B and press enter if you want to play in your own specified window size\n"<<std::endl;
  std::cout<<"                            !!!NOTE!!!"<<std::endl;
  std::cout<<"      Expand the terminal window size before you continue with option B\n"<<std::endl;
  std::cout<<"-------------------------------------------------------------------------------------"<<std::endl;
  std::cout<<"/FI/ Valitse terminaalisi ikkunan koko"<<std::endl;
  std::cout<<"/FI/ Voit valita joko pelata valmiiksi maaritellyssa pienessa ikkunassa"<<std::endl;
  std::cout<<"/FI/ tai voit laajentaa ikkunan koko naytolle tai johonkin silta valilta"<<std::endl;
  std::cout<<"/FI/ mutta ikkunan koon on oltava vahintaan 45 merkkia korkea ja 125 merkkia levea\n"<<std::endl;
  std::cout<<"/FI/ Syota A pelataksesi pienessa ikkunassa"<<std::endl;
  std::cout<<"/FI/ Syota B pelataksesi omassa maaritetyssa ikkunakoossa\n"<<std::endl;
  std::cout<<"                           !!!HUOM!!! "<<std::endl;
  std::cout<<"     Suurenna terminaalisi ikkunaa ennen kuin jatkat valinnalla B\n"<<std::endl;
}

void LanguageSelectMenu(int y, int x) {
  clear();
  bkgd(COLOR_PAIR(1));
  attron(COLOR_PAIR (3));
  mvaddstr(y-6, x-14, "****************************");
  mvaddstr(y-5, x-14, "*");
  mvaddstr(y-5, x+13, "*");
  mvaddstr(y-4, x-14, "*                          *");
  mvaddstr(y-3, x-14, "*");
  mvaddstr(y-3, x+13, "*");
  mvaddstr(y-2, x-14, "*");
  mvaddstr(y-2, x-14, "****************************");
  attroff(COLOR_PAIR (3));

  attron(COLOR_PAIR (5));
  mvaddstr(y-5, x-13, "      Select Language     ");
  mvaddstr(y-3, x-13, "       Valitse Kieli      ");
  attroff(COLOR_PAIR (5));
  mvaddstr(y+3, x-14, "-      F2) English         -");
  mvaddstr(y+4, x-14, "-      F3) Suomi           -");
  mvaddstr(y+5, x-14, "-     F10) About/Tietoja   -");
  mvaddstr(y+10, x-14, "       F1 QUIT/POISTU        ");
  refresh();
};