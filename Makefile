CXX = g++
CXXFLAGS = -std=c++11
LDFLAGS = -lncurses

textadventure: main.o player.o environment.o windows.o gamefunctions.o
	$(CXX) $(CXXFLAGS) -o textadventure main.o player.o environment.o windows.o gamefunctions.o $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

player.o: player.cpp player.h
	$(CXX) $(CXXFLAGS) -c player.cpp

environment.o: environment.cpp environment.h
	$(CXX) $(CXXFLAGS) -c environment.cpp

windows.o: windows.cpp windows.h
	$(CXX) $(CXXFLAGS) -c windows.cpp

gamefunctions.o: gamefunctions.cpp gamefunctions.h
	$(CXX) $(CXXFLAGS) -c gamefunctions.cpp

clean:
	rm -f *.o textadventure