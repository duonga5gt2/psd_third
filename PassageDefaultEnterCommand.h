//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_PASSAGEDEFAULTENTERCOMMAND_H
#define ZOORK_PASSAGEDEFAULTENTERCOMMAND_H


#include "Command.h"

#include <utility>

class PassageDefaultEnterCommand : public Command {
public:
    explicit PassageDefaultEnterCommand(GameObject* g) : Command(g) {}

    void execute() override;
    std::string getCommandName() const override;
};


#endif //ZOORK_PASSAGEDEFAULTENTERCOMMAND_H
