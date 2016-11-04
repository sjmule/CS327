#ifndef MONSTER_H
#define MONSTER_H

#include "dungeon.h"

struct DICE
{
	int base;
	int die;
	int sides;
};

class Monster : public Character
{
  public:
	  std::string name;
	  std::string description;
	  int color;
	  int attributes;
	  char playerX;
	  char playerY;
	  DICE speedDice;
		DICE damageDice;
		DICE hpDice;
};

void createRandomMonsters();

#endif
