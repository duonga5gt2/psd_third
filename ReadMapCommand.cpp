#include "ReadMapCommand.h"
#include <iostream>

void ReadMapCommand::execute() {
    std::cout <<
"                                            Bird Aviary[rope]\n"
"                                                  |\n"
"Ticket Booth[desk_key] -- Zoo Entrance[map] -- Main Path[flashlight, Aaron from La Trobe] -- Reptile House[battery]\n"
"                               |                  |\n"
"                         Staff Office       Aquarium Tunnel\n"
"                        [warning_note]         [keycard]\n"
"                               |                  |\n"
"                        Storage Shed ------- Lion Enclosure -- Back Gate\n"
"                   [bolt_cutters, meat]                       [gate_chain]\n";
}

std::string ReadMapCommand::getCommandName() const {
    return "Gives you an overview of the map.\n";
}


