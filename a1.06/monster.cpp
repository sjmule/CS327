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
		int getAttributes(Monster* m) { return m->attribues; }
		char getPlayerX(Monster* m) { return m->playerX; }
		char getPlayerY(Monster* m) { return m->playerY; }
		// Setters
		void setAttributes(Monster* m, int i) { m->attributes = i; }
		void setPlayerX(Monster* m, char c) { m->playerX = c; }
		void setPlayerY(Monster* m, char c) { m->playerY = c; }
};
