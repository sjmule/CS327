#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <netinet/in.h>
#include <argp.h>
#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <ncurses.h>
#include "character.h"
#include "monster.h"
#include "player.h"

#define X 80
#define Y 21

#define INTELLIGENT 0x1
#define TELEPATHIC  0x2
#define TUNNELING   0x4
#define ERRATIC     0x8

typedef struct ROOM room;

struct ROOM
{
	int number;
	int x;
	int y;
	int height;
	int width;
};

class Dungeon
{
  public:
		int map[Y][X];
		int hardness[Y][X];
		int numRooms;
		room* rooms;
		int numMonsters;
		Monster** monsters;
		int level;
		int stairUpX;
		int stairUpY;
		int stairDownX;
		int stairDownY;
};

extern Dungeon* aincrad;
extern Player* kirito;
extern int monCount;
extern int turn;

int monstersAlive();

#endif
