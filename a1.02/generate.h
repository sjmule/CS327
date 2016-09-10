#ifndef GENERATE_H
#define GENERATE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

#define X 80
#define Y 21

typedef struct ROOM room;

struct ROOM
{
	int number;
	int x;
	int y;
	int height;
	int width;
};

typedef struct DUNGEON dungeon;

struct DUNGEON
{
	char map[Y][X];
	int hardness[Y][X];
	int numRooms;
	room rooms[8];
};

extern dungeon aincrad;

void setImmutable();

void setHardness();

void setBoundary();

void initializeDungeon();

room generateRoom();

int verifyValidity(room room, int x, int y);

void placeRoom(room room, int x, int y);

void createRooms();

void connectRooms();

#endif
