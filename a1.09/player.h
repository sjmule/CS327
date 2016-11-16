#ifndef PLAYER_H
#define PLAYER_H

#include "dungeon.h"
#include "object.h"
#include "dice.h"

class Player : public Character
{
	public:
		std::vector<Object*> inventory;
		std::vector<Object*> equip;
		int** visible;
		void initializeVisible();
		void setVisible();
		void clearVisible();
		Player();
		~Player();
};

#endif
