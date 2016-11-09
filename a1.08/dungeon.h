#ifndef DUNGEON_H
#define DUNGEON_H

#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <netinet/in.h>
#include <argp.h>
#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <ncurses.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "character.h"
#include "monster.h"
#include "player.h"

using namespace std;

#define X 80
#define Y 21

#define INTELLIGENT 0x01
#define TELEPATHIC  0x02
#define TUNNELING   0x04
#define ERRATIC     0x08
#define PASS				0x10

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
		vector<Monster> monsters;
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
