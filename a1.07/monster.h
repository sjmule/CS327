#ifndef MONSTER_H
#define MONSTER_H

#include "dungeon.h"

class Monster : public Character
{
  public:
	  string name;
	  string description;
	  int color; 
	  int attributes;
	  char playerX;
	  char playerY;
	  dice die;
};

void createRandomMonsters();

void cleanupMonsters();

#endif
