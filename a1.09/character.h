#ifndef CHARACTER_H
#define CHARACTER_H

#include "dungeon.h"
#include "dice.h"

class Character
{
  public:
	  int id;
	  char symbol;
	  char x;
	  char y;
	  int speed;
	  int turn;
	  char alive;
	  int hp;
	  dice damage;
};

#endif
