//
// Created by Richard Skarbez on 5/7/23.
//

#include "NullCommand.h"

void NullCommand::execute() {
    std::cout << "Nothing happens.\n";
}


std::string NullCommand::getCommandName() const {
    return "This item can do something, I guess!.\n";
}