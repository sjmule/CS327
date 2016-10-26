#include "dungeon.h"
#include "character.h"
#include "monster.h"

class Monster : public Character
{
	int attributes;
	char playerX;
	char playerY;
	public:
		// Getters
		int getAttributes() { return attribues; }
		char getPlayerX() { return playerX; }
		char getPlayerY() { return playerY; }
		// Setters
		void setAttributes(int i) { attributes = i; }
		void setPlayerX(char c) { playerX = c; }
		void setPlayerY(char c) { playerY = c; }
};
