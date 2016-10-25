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
};

class Player : public Character
{
	int[Y][X];
};

class Monster : public Character
{
	int attributes;
	char playerX;
	char playerY;

};
