#ifndef PLAYER_H
#define PLAYER_H

#include "dungeon.h"

class Player : public Character
{
	public:
		int** visible;

		void initializeVisible();

		void setVisible();

		void clearVisible();
};

#endif
