CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -lncurses

textadventure: main.o player.o environment.o gamewindows.o gamefunctions.o language.o titles_menus.o
	$(CXX) $(CXXFLAGS) -o textadventure main.o player.o environment.o gamewindows.o gamefunctions.o language.o titles_menus.o $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

player.o: player.cpp player.h
	$(CXX) $(CXXFLAGS) -c player.cpp

environment.o: environment.cpp environment.h
	$(CXX) $(CXXFLAGS) -c environment.cpp

windows.o: gamewindows.cpp gamewindows.h
	$(CXX) $(CXXFLAGS) -c gamewindows.cpp

gamefunctions.o: gamefunctions.cpp gamefunctions.h
	$(CXX) $(CXXFLAGS) -c gamefunctions.cpp

language.o: language.cpp language.h
	$(CXX) $(CXXFLAGS) -c language.cpp

titles_menus.o: titles_menus.cpp titles_menus.h
	$(CXX) $(CXXFLAGS) -c titles_menus.cpp
clean:
	rm -f *.o textadventure