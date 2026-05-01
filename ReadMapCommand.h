//
// Created by Ngo Quy Duong on 30/4/26.
//

#ifndef ZOORK_READMAPCOMMAND_H
#define ZOORK_READMAPCOMMAND_H
#include "Command.h"



class ReadMapCommand : public Command {
public:
    explicit ReadMapCommand(GameObject *obj) : Command(obj) {};
    void execute() override;
    std::string getCommandName() const override;
};

#endif //ZOORK_READMAPCOMMAND_H