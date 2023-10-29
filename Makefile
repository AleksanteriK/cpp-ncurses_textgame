CC=g++
CFLAGS=-std=c++11
LDFLAGS=-lncurses

SOURCES=main.cpp player.cpp environment.cpp windows.cpp gamefunctions.cpp
HEADERS=player.h environment.h windows.h gamefunctions.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=textadventure

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

windows: $(SOURCES) $(HEADERS)
	g++ -m64 -o textadventure.exe $(SOURCES) -lncurses
