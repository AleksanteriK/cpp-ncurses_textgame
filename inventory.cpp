#include "inventory.h"

void Inventory::AddItem(const Item& item) {
    items.push_back(item);
}

void Inventory::DisplayInventoryTerminal() {
    std::cout << "Inventory:" << std::endl;
    for (const auto& item : items) {
        std::cout << "- " << item.name << std::endl;
    }
}