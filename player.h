#ifndef PLAYER_H
#define PLAYER_H

#include "inventory.h"
#include "gun.h"

class Player {
public:
    int position_x;
    int position_y;
    Inventory PlayerInventory;

    Player(int startX, int startY);

    void MoveRight();
    void MoveLeft();
    void MoveForward();
    void MoveBack();
    int ReturnPosition_y();
    int ReturnPosition_x();
};

#endif