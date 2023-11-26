#include "player.h"

#define MIDDLE_Y_AXIS (LINES/2)
#define MIDDLE_X_AXIS (COLS/2)

Player::Player(int position_x, int position_y) {
    this -> position_x = position_x;
    this -> position_y = position_y;
}

void Player::MoveRight() {
    position_x++;
}

void Player::MoveLeft() {
    position_x--;
}

void Player::MoveForward() {
    position_y++;
}

void Player::MoveBack() {
    position_y--;
}

int Player::ReturnPosition_y() {
    return position_y;
}

int Player::ReturnPosition_x() {
    return position_x;
}