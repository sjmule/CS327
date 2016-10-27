#include "dungeon.h"
#include "character.h"
#include "monster.h"

// Getters
int getAttributes(monster* m) { return ((Monster*) m)->attributes; }
char getPlayerX(monster* m) { return ((Monster*) m)->playerX; }
char getPlayerY(monster* m) { return ((Monster*) m)->playerY; }

// Setters
void setAttributes(monster* m, int i) { ((Monster*) m)->attributes = i; }
void setPlayerX(monster* m, char c) { ((Monster*) m)->playerX = c; }
void setPlayerY(monster* m, char c) { ((Monster*) m)->playerY = c; }

void createMonsters()
{
  aincrad.monsters = (monster**) malloc(sizeof(Monster) * aincrad.numMonsters);
	static int id = 1;
	int i = 0;
	for(; i < aincrad.numMonsters; ++i)
	{
		Monster* mon;
		mon = new Monster();
		int attributes = 0;
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
			if(aincrad.hardness[y][x] == 0)
      {
        if((x != getX((character*)kirito)) && (y != getY((character*)kirito)))
				  break;
      }
		}
		mon->x = x;
		mon->y = y;
		mon->attributes = attributes;
		mon->id = id;
		mon->symbol = (rand() % 25) + 97;
		mon->speed = (rand() % 15) + 5;
		mon->playerX = 0;
		mon->playerY = 0;
		mon->turn = 0;
		mon->alive = 1;
		aincrad.monsters[i] = (monster *) mon;
		++monCount;
	}
}

void cleanupMonsters()
{
  for(int i = 0; i < aincrad.numMonsters; ++i)
  {
    delete[] aincrad.monsters[i];
  }
  //free(aincrad.monsters);
}
