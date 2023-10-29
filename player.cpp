#include "player.h"

#define MIDDLE_Y_AXIS (LINES/2)
#define MIDDLE_X_AXIS (COLS/2)

Player::Player(int startX, int startY) : position_x(startX), position_y(startY) {}

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