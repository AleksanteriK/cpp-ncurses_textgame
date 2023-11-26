#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    int position_x;
    int position_y;

    Player(int startX, int startY);

    void MoveRight();
    void MoveLeft();
    void MoveForward();
    void MoveBack();
    int ReturnPosition_y();
    int ReturnPosition_x();
};

#endif