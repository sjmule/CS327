#ifndef CHARACTER_H
#define CHARACTER_H

#include "dungeon.h"

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
};

#endif
