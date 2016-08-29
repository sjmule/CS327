#ifndef GENERATE_H
#define GENERATE_H

#define X 81
#define Y 21

typedef struct ROOM room_t;

struct ROOM
{
	int number;
	int x;
	int y;
	int height;
	int width;
};

typedef struct DUNGEON dungeon_t;

struct DUNGEON
{
	char map[Y][X];
	int hardness[Y][X];
	int numRooms;
	room_t rooms[8];
};

extern dungeon_t aincrad;

void setImmutable();

void setHardness();

void setBoundary();

void initializeDungeon();

room_t generateRoom();

int verifyValidity(room_t room, int x, int y);

void placeRoom(room_t room, int x, int y);

void createRooms();

#endif
