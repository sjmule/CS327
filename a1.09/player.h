#ifndef PLAYER_H
#define PLAYER_H

#include "dungeon.h"

class Player : public Character
{
	public:
		vector<Object> inventory;
		Object* carry = new Object[10];
		int** visible;
		void initializeVisible();
		void setVisible();
		void clearVisible();
};

#endif
