#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>
#include "item.h"

class Inventory {
public:
    std::vector<Item> items;

    void AddItem(const Item& item);

    void DisplayInventoryTerminal();
};

#endif