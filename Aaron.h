//
// Created by Ngo Quy Duong on 30/4/26.
//

#ifndef ZOORK_AARON_H
#define ZOORK_AARON_H
#include "Character.h"
#include "Item.h"
class Aaron : public Character {
public:
    void talkToCharacter() const override;
    Item* getMap();
    Aaron(const std::string& name, const std::string& description);
};


#endif //ZOORK_AARON_H