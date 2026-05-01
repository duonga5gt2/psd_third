
#include "Aaron.h"
#include "ReadMapCommand.h"
#include <memory>
void Aaron::talkToCharacter() const {
    std::cout << "Aaron: Hey, you look lost.\n";
    std::cout << "Aaron: If you need another map, type: ask aaron map\n";
}


Item* Aaron::getMap() {
    Item* map = new Item("map", "A nicely printed map given by Aaron.");
    map->setUseCommand(std::make_shared<ReadMapCommand>(map));

    return map;
}

Aaron::Aaron(const std::string& n, const std::string& d) : Character(n, d) {}
