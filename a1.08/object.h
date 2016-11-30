#ifndef OBJECT_H
#define OBJECT_H

#include "dungeon.h"
#include "dice.h"
#include "descriptions.h"

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
};

void loadObjects();

#endif
