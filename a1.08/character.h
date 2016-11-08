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
	  char speed;
	  int turn;
	  char alive;
	  int hp;
	  int attDam;
};

#endif
