#ifndef MONSTER_H
#define MONSTER_H

class Monster : public Character
{
  public:
	  int attributes;
	  char playerX;
	  char playerY;
};

void createMonsters();

void cleanupMonsters();

#endif
