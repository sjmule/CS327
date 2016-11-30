#ifndef OBJECT_H
#define OBJECT_H

#include "dungeon.h"
#include "dice.h"
#include "descriptions.h"

static const std::string objectStrings[] = {"NOTYPE", "WEAPON", "OFFHAND", "RANGED", "LIGHT", "ARMOR", "HELMET", "CLOAK", "GLOVES", "BOOTS",
                              "AMULET", "RING", "SCROLL", "BOOK", "FLASK", "GOLD", "AMMUNITION", "FOOD", "WAND", "CONTAINER"};

class Object
{
  public:
    std::string name;
    std::string description;
    unsigned int color;
    char symbol;
    int hit, dodge, defence, weight, speed, attribute, value;
    dice damage;
    int x, y;
    std::string type;
    Object();
    Object(Object* ob);
};

void loadObjects();

#endif
