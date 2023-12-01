#include "player.h"

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