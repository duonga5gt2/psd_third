//
// Created by Richard Skarbez on 5/7/23.
//

#include "Player.h"

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}


void Player::addItemToInventory(Item* item) {
    inventory.push_back(item);
    std::cout << item->getName() + " is added to your Inventory\n";
}



Item* Player::retrieveItemFromInventory(const std::string& itemName) {
    if (inventory.empty()) {
        std::cout << "No items in inventory.\n" << std::endl;
        return nullptr;
    }
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == itemName) {
            Item* item = (*it);
            inventory.erase(it);
            return item;
        }
    }
    return nullptr;

}


void Player::showInventory() const {
    if (inventory.empty()) {
        std::cout << "No items in inventory.\n" << std::endl;
    }
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        std::cout << (*it)->getName() + ": " +(*it)->getDescription() + " " + (*it)->getCommandName() + "\n"<< std::endl;
    }
}


bool Player::isItemAvailable(const std::string& itemName) const {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == itemName) {
            return true;
        }
    }
    return false;
}


Item* Player::getOneItemFromInventory(const std::string& itemName) const {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == itemName) {
            return (*it);
        }
    }

    return nullptr;
}

void Player::talkToCharacter() const {
    std::cout << "Talking to yourself will not help much.\n";
}