#ifndef MONSTER_H
#define MONSTER_H

#include "dungeon.h"
#include "dice.h"
#include "descriptions.h"

class Monster : public Character
{
  public:
	  std::string name;
	  std::string description;
	  unsigned int color;
	  unsigned int attributes;
	  char playerX;
	  char playerY;
		dice damageDice;
};

void loadMonsters();
void createRandomMonsters();

#endif
