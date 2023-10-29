#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    int position_x;
    int position_y;

    Player(int startX, int startY);

    void moveRight();
    void moveLeft();
    void moveForward();
    void moveBack();
};

#endif