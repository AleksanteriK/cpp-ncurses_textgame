#include "gun.h"

Gun::Gun (int ammo) {
    this -> ammo = ammo;
}

int Gun::returnAmmo() {
    return ammo;
}

void Gun::UseGun () {
    ammo--;
}