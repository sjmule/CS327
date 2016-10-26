#include "character.h"
#include "dungeon.h"

class Character
{
	int id;
	char symbol;
	char x;
	char y;
	char speed;
	int turn;
	char alive;
	public:
		// Getters
		int getId(Character* c) { return c->id; }
		char getSymbol(Character* c) { return c->symbol; }
		char getX(Character* c) { return c->x; }
		char getY(Character* c) { return c->y; }
		char getSpeed(Character* c) { return c->speed; }
		int getTurn(Character* c) { return c->turn; }
		char getAlive(Chaacter* c) { return c->alive; }
		// Setters
		void setId(Character* c, int i) { c->id = i; }
		void setSymbol(Character* c, char s) { c->symbol = s; }
		void setX(Character* c, char s) { c->x = s; }
		void setY(Character* c, char s) { c->y = s; }
		void setSpeed(Character* c, char s) { c->speed = s; }
		void setTurn(Character* c, int i) { c->turn = i; }
		void setAlive(Character* c, char s) { c->alive = s; }
};
