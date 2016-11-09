#ifndef MONSTER_H
#define MONSTER_H

#include "dungeon.h"
#include "dice.h"

class Monster : public Character
{
  public:
	  std::string name;
	  std::string description;
	  int color;
	  int attributes;
	  char playerX;
	  char playerY;
	  dice speedDice;
		dice damageDice;
		dice hpDice;
};

void createRandomMonsters();

#endif
