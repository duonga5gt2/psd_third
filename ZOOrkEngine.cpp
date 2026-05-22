//
// Created by Richard Skarbez on 5/7/23.
//

#include "ZOOrkEngine.h"

#include <utility>
#include "Room.h"
#include "Aaron.h"
#include <algorithm>
ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        }

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look") || (command == "inspect")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else if (command == "check") {
            handleCheckInventoryCommand();
        } else if (command == "view") {
            handleViewMapCommand(arguments);
        } else if (command == "talk") {
            handleTalkCommand(arguments);
        } else if (command == "ask") {
            handleAskCommand(arguments);
        }
        else {
            std::cout << "I don't understand that command.\n";
        }
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Go where?\n";
        return;
    }

    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else {
        direction = arguments[0];
    }

    Room* currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);
    player->setCurrentRoom(passage->getTo());
    passage->enter();
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    Room* currentRoom = player->getCurrentRoom();

    if (arguments.empty()) {
        std::cout << "You are in the " << currentRoom->getName() << ".\n";
        std::cout << currentRoom->getDescription() << "\n";
    } else {
        Item* item = currentRoom->getItem(arguments[0]);

        if (item == nullptr) {
            std::cout << "You do not see that here.\n";
        } else {
            std::cout << item->getDescription() << "\n";
        }
    }
}

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Take what?\n";
        return;
    }
    Room* currentRoom = player->getCurrentRoom();
    Item* i = currentRoom->retrieveItem(arguments[0]);
    if (i != nullptr) {
        player->addItemToInventory(i);
    }
    else {
        std::cout << "You cannot take that item here.\n";
    }
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Drop what?\n";
        return;
    }
    Room* currentRoom = player->getCurrentRoom();
    Item* i = player->retrieveItemFromInventory(arguments[0]);
    if (i != nullptr) {
        currentRoom->addItem(i);
        std::cout << i->getName() + " is dropped in the " + currentRoom->getName() << "\n";
    }
    else {
        std::cout << "You do not have that item in your inventory.\n";
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}

void ZOOrkEngine::handleCheckInventoryCommand() {
    player->showInventory();
}

void ZOOrkEngine::handleTalkCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Talk to who?\n";
        return;
    }

    Character* characterInRoom = player->getCurrentRoom()->getCharacter(arguments[0]);

    if (characterInRoom == nullptr) {
        std::cout << "You do not see that character here.\n";
        return;
    }

    characterInRoom->talkToCharacter();
}


void ZOOrkEngine::handleAskCommand(std::vector<std::string> arguments) {
    if (arguments.size() < 2) {
        std::cout << "Ask who for what?\n";
        return;
    }

    std::string characterName = arguments[0];
    std::string itemName = arguments[1];

    Character* characterInRoom = player->getCurrentRoom()->getCharacter(characterName);

    if (characterInRoom == nullptr) {
        std::cout << "You do not see that character here.\n";
        return;
    }

    Aaron* aaron = dynamic_cast<Aaron*>(characterInRoom);

    if (aaron == nullptr) {
        std::cout << characterName << " does not have anything to give you.\n";
        return;
    }

    if (itemName != "map") {
        std::cout << "Aaron does not have that item.\n";
        return;
    }

    Item* map = aaron->getMap();
    player->addItemToInventory(map);

    std::cout << "Aaron gives you a new map.\n";
}

void ZOOrkEngine::handleViewMapCommand(std::vector<std::string> arguments) {
    Item* itemInRoom = player->getCurrentRoom()->getItem("map");
    Item* item = player->getOneItemFromInventory("map");
    if (item == nullptr) {
        if (itemInRoom == nullptr) {
            std::cout << "You need to find the map somewhere in this game.\n";
        }
        else {
            std::cout << "Get the map in this room, bro!.\n";
        }
    }
    else {
        item->use();
    }
}


std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}
