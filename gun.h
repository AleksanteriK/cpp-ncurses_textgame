#ifndef GUN_H
#define GUN_H

class Gun {
public:
    int ammo;

    Gun (int ammo);

    int returnAmmo();

    void UseGun ();
};

#endif