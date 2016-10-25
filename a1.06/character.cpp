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
		int getId() const { return id; }
		char getSymbol const { return symbol; }
		char getX const { return x; }
		char getY const { return y; }
		char getSpeed const { return speed; }
		int getTurn const { return turn; }
		char getAlive const { return alive; }
		// Setters
		void setId(int i) { id = i; }
		void setSymbol(char c) { symbol = c; }
		void setX(char c) { x = c; }
		void setY(char c) { y = c; }
		void setSpeed(char c) { speed = c; }
		
};
