#include "Aaron.h"
#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "ReadMapCommand.h"
#include "Room.h"
#include "ZOOrkEngine.h"


int main() {
    Item* map = new Item("map", "A faded zoo map showing the main paths, animal areas, and a marked back gate.");
    map->setUseCommand(std::make_shared<ReadMapCommand>(map));

    Item* flashlight = new Item("flashlight", "An old flashlight. It might help you see inside dark areas like the aquarium tunnel.");

    Item* keycard = new Item("keycard", "A staff keycard with a scratched zoo logo on it.");

    Item* bolt_cutters = new Item("bolt_cutters", "A heavy pair of bolt cutters. They look strong enough to cut chains.");

    Item* meat = new Item("meat", "A piece of raw meat. It smells terrible, but it might distract a dangerous animal.");

    Item* rope = new Item("rope", "A long rope that could help you climb or reach something high.");

    Item* desk_key = new Item("desk_key", "A small key. It probably opens a desk or cabinet somewhere.");

    Item* battery = new Item("battery", "A spare battery. It might be useful for powering something.");

    Item* warning_note = new Item("warning_note", "The note says: 'Do not enter the lion enclosure without a distraction.'");

    Item* gate_chain = new Item("gate_chain", "A thick chain wrapped around the back gate. You will need something strong to cut it.");


    Character* c = new Aaron("aaron", "A dude from La Trobe University who got randomly spawn in this game");

    std::shared_ptr<Room> zoo_entrance = std::make_shared<Room>("Zoo Entrance", "You are standing at the front entrance of the abandoned zoo. The main gate behind you is locked with a heavy chain, and old ticket signs swing quietly in the wind. A cracked path leads deeper into the zoo.");
    std::shared_ptr<Room> ticket_booth = std::make_shared<Room>("Ticket Booth", "You step inside the dusty ticket booth. Faded brochures are scattered across the counter, and the glass window is covered in fingerprints. There might still be something useful hidden among the papers.");
    std::shared_ptr<Room> main_path = std::make_shared<Room>("Main Path","You are on the main path of the zoo. Overgrown plants cover the walkway, and broken direction signs point toward different animal areas. This looks like the central route through the zoo.");
    std::shared_ptr<Room> reptile_house = std::make_shared<Room>("Reptile House", "You enter the reptile house. The air is warm and damp, and empty glass tanks line the walls. Somewhere in the darkness, you hear a faint scraping sound.");
    std::shared_ptr<Room> aquarium_tunnel = std::make_shared<Room>("Aquarium Tunnel", "You walk into the aquarium tunnel. The glass walls are cracked, and dark water presses against them from both sides. Without enough light, it is hard to see what lies ahead.");
    std::shared_ptr<Room> bird_aviary = std::make_shared<Room>("Bird Aviary", "You enter the bird aviary. Torn netting hangs from the ceiling, and feathers cover the ground. A narrow wooden platform leads up toward the higher cages.");
    std::shared_ptr<Room> staff_office = std::make_shared<Room>("Staff Office", "You enter the staff office. Old schedules, warning notices, and animal feeding records are pinned to the walls. A locked desk sits in the corner, as if someone left in a hurry.");
    std::shared_ptr<Room> storage_shed = std::make_shared<Room>("Storage Shed", "You enter the storage shed. Rusty tools, broken cages, and cleaning supplies are stacked against the walls. This place looks dangerous, but it may contain something useful.");
    std::shared_ptr<Room> lion_enclosure = std::make_shared<Room>("Lion Enclosure", "You step into the lion enclosure. Tall grass covers the ground, and claw marks scar the wooden barriers. The exit path is nearby, but this area feels unsafe.");
    std::shared_ptr<Room> back_gate = std::make_shared<Room>("Back Gate", "You reach the back gate of the zoo. The metal gate is locked, but the road outside is visible through the bars. This could be your way out if you can open it.");


    zoo_entrance->addItem(map);

    ticket_booth->addItem(desk_key);

    main_path->addItem(flashlight);
    main_path->addCharacter(c);

    reptile_house->addItem(battery);

    aquarium_tunnel->addItem(keycard);

    bird_aviary->addItem(rope);

    staff_office->addItem(warning_note);

    storage_shed->addItem(bolt_cutters);
    storage_shed->addItem(meat);

    back_gate->addItem(gate_chain);


    Passage::createBasicPassage(zoo_entrance.get(), ticket_booth.get(), "west", true);
    Passage::createBasicPassage(zoo_entrance.get(), main_path.get(), "east", true);
    Passage::createBasicPassage(zoo_entrance.get(), staff_office.get(), "south", true);

    Passage::createBasicPassage(main_path.get(), bird_aviary.get(), "north", true);
    Passage::createBasicPassage(main_path.get(), reptile_house.get(), "east", true);
    Passage::createBasicPassage(main_path.get(), aquarium_tunnel.get(), "south", true);

    Passage::createBasicPassage(staff_office.get(), storage_shed.get(), "south", true);

    Passage::createBasicPassage(aquarium_tunnel.get(), lion_enclosure.get(), "south", true);
    Passage::createBasicPassage(storage_shed.get(), lion_enclosure.get(), "east", true);

    Passage::createBasicPassage(lion_enclosure.get(), back_gate.get(), "east", true);

    ZOOrkEngine zoork(zoo_entrance);

    zoork.run();

    return 0;
}
