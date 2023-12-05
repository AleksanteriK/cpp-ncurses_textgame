#ifndef PLAYER_H
#define PLAYER_H

#include "inventory.h"
#include "gun.h"
#include <string>
#include <vector>

class Player {
public:
    int position_x;
    int position_y;
    Inventory PlayerInventory;
    std::vector<std::string> commands;

    Player(int startX, int startY);

    void setCommands ();
    void moveRight();
    void moveLeft();
    void moveForward();
    void moveBack();
    int returnPosition_y();
    int returnPosition_x();
};

#endif