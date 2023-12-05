#include "player.h"

Player::Player(int position_x, int position_y) {
    this -> position_x = position_x;
    this -> position_y = position_y;
}

void setCommands () {
    
}

void Player::moveRight() {
    position_x++;
}

void Player::moveLeft() {
    position_x--;
}

void Player::moveForward() {
    position_y++;
}

void Player::moveBack() {
    position_y--;
}

int Player::returnPosition_y() {
    return position_y;
}

int Player::returnPosition_x() {
    return position_x;
}