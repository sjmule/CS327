#include "dungeon.h"
#include "character.h"
#include "monster.h"

void loadMonsters()
{
	aincrad->numMonsters = 0;
	static int id = 1;
	unsigned int i;
	for(i = 0; i < aincrad->monster_descriptions.size(); ++i)
	{
		monster_description monDesc = aincrad->monster_descriptions.at(i);
		Monster mon;
		mon.name = monDesc.name;
		mon.description = monDesc.description;
		mon.symbol = monDesc.symbol;
		// unsigned int color = monDesc.color.at(0);
		// init_pair(colors_lookup[color].value, colors_lookup[color].value, COLOR_BLACK);
		mon.color = monDesc.color.at(0);
		mon.attributes = monDesc.abilities;
		mon.speed = monDesc.speed.roll();
		mon.hp = monDesc.hitpoints.roll();
		mon.damageDice = monDesc.damage;
		int x = 0;
		int y = 0;
		while(1)
		{
			x = (rand() % (X - 2)) + 1;
			y = (rand() % (Y - 2)) + 1;
			if(aincrad->hardness[y][x] == 0)
			{
				if((x != kirito->x) && (y != kirito->y))
					break;
			}
		}
		mon.x = x;
		mon.y = y;
		mon.id = id;
		mon.playerX = 0;
		mon.playerY = 0;
		mon.turn = 0;
		mon.alive = 1;
		aincrad->monsters.push_back(mon);
		aincrad->numMonsters++;
	}
}

void createRandomMonsters()
{
	static int id = 1;
	int i = 0;
	for(; i < aincrad->numMonsters; ++i)
	{
		Monster mon;
		unsigned int attributes = 0;
		int attr = rand() % 100;
		if(attr < 50)
			attributes = attributes | INTELLIGENT;
		attr = rand() % 100;
		if(attr < 50)
			attributes = attributes | TELEPATHIC;
		attr = rand() % 100;
		if(attr < 50)
			attributes = attributes | TUNNELING;
		attr = rand() % 100;
		if(attr < 50)
			attributes = attributes | ERRATIC;
		attr = (rand() % 15) + 5;
		int x = 0;
		int y = 0;
		while(1)
		{
			x = (rand() % (X - 2)) + 1;
			y = (rand() % (Y - 2)) + 1;
			if(aincrad->hardness[y][x] == 0)
			{
				if((x != kirito->x) && (y != kirito->y))
					break;
			}
		}
		mon.x = x;
		mon.y = y;
		mon.attributes = attributes;
		mon.id = id;
		mon.symbol = (rand() % 25) + 97;
		mon.speed = (rand() % 15) + 5;
		mon.playerX = 0;
		mon.playerY = 0;
		mon.turn = 0;
		mon.alive = 1;
		mon.color = 5;
		aincrad->monsters.push_back(mon);
	}
}
