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

#define X 80
#define Y 21

#define INTELLIGENT 0x1
#define TELEPATHIC  0x2
#define TUNNELING   0x4
#define ERRATIC     0x8

typedef struct ENTITY entity;

struct ENTITY
{
	char symbol;
	int x;
	int y;
	int speed;
	int turn;
	int alive;
};

typedef struct PLAYER player;

struct PLAYER
{
	entity* base;
};

typedef struct MONSTER monster;

struct MONSTER
{
	entity* base;
	int attributes;
	int playerX;
	int playerY;
};

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
	int map[Y][X];
	int hardness[Y][X];
	int numRooms;
	room* rooms;
	int numMonsters;
	monster* monsters;
};

extern dungeon aincrad;
extern player kirito;
extern int monCount;
extern int turn;

#endif
