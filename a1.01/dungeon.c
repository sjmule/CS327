#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define X 81
#define Y 21

typedef struct room
{
	int number;
	int x;
	int y;
	int height;
	int width;
}room;

typedef struct dungeon
{
	char map[Y][X];
	int hardness[Y][X];
	int numRooms;
	room rooms[8];
}dungeon;

dungeon aincrad;

void setImmutable()
{
	int i = 0;
	for(; i < X - 1; ++i)
	{
		aincrad.hardness[0][i] = -1;
	}
	for(i = 0; i < X - 1; ++i)
	{
		aincrad.hardness[Y-1][i] = -1;
	}
	for(i = 1; i < Y - 1; ++i)
	{
		aincrad.hardness[i][0] = -1;
		aincrad.hardness[i][X-2] = -1;
	}
} 

void setHardness()
{
	int i = 1;
	for(; i < Y - 1; ++i)
	{
		int j = 1;
		for(; j < X - 2; ++j)
		{
			aincrad.hardness[i][j] = (rand() % 5) + 1;
		}
	}	
}

void setBoundary()
{
	int i = 0;
	for(; i < X - 1; ++i)
	{
		aincrad.map[0][i] = '-';
	}
	for(i = 0; i < X - 1; ++i)
	{
		aincrad.map[Y-1][i] = '-';
	}
	for(i = 1; i < Y - 1; ++i)
	{
		aincrad.map[i][0] = '|';
		aincrad.map[i][X-2] = '|';
	}
}

void initializeDungeon()
{
	setImmutable();
	setHardness();
	
	int i = 0;
	for(; i < Y; ++i)
	{
		int j = 0;
		for(; j < X; ++j)
		{
			aincrad.map[i][j] = ' ';
		}
		aincrad.map[i][X-1] = 0;
	}
	
	setBoundary();

	aincrad.numRooms = 0;
}

void printDungeon(int debug)
{
	int i = 0;
	for(; i < Y; ++i)
	{
		printf("%s\n", aincrad.map[i]);
	}
	if(debug)
	{
		for(i = 0; i < Y; ++i)
		{
			int j = 0;
			for(; j < X; ++j)
			{
				printf("%d", aincrad.hardness[i][j]);
			}
			printf("\n");
		}
		getchar();
	}
}

room generateRoom()
{
	room temp;
	temp.height = (rand() % 6) + 3;
	temp.width = (rand() % 5) + 4;
	return temp;
}

int verifyValidity(room room, int x, int y)
{
	int error = 0;
	int i = y;
	// Verify no overlap
	for(; i < y + room.height + 1; ++i)
	{
		int j = x;
		for(; j < x + room.width + 1; ++j)
		{
			if(aincrad.hardness[i][j] == 0)
				++error;
		}
	}
	// Verify not placing directly next to another room
	if(y != 1)
	{
		for(i = x; i < x + room.width + 1; ++i)
		{
			if(aincrad.hardness[y-1][i] == 0)
				++error;
		}
	}
	if(y + room.height + 1 != Y - 2)
	{
		int next = y + room.height + 1;
		for(i = x; i < x + room.width + 1; ++i)
		{
			if(aincrad.hardness[next][i] == 0)
				++error;
		}
	}
	if(x != 1)
	{
		for(i = y; i < y + room.height + 1; ++i)
		{
			if(aincrad.hardness[i][x-1] == 0)
				++error;
		}
	}
	if(x + room.width + 1 != X - 3)
	{
		int next = x + room.width + 1; 
		for(i = y; i < y + room.height + 1; ++i)
		{
			if(aincrad.hardness[i][next] == 0)
				++error;
		}
	}
	return error;
}

void placeRoom(room room, int x, int y)
{
	int i = y;
	for(; i < y + room.height; ++i)
	{
		int j = x;
		for(; j < x + room.width; ++j)
		{
			aincrad.hardness[i][j] = 0;
			aincrad.map[i][j] = '.';
		}
	}
	room.number = aincrad.numRooms;
	room.x = x;
	room.y = y;
	aincrad.rooms[aincrad.numRooms] = room;
	aincrad.numRooms++;
}

void createRooms()
{
	int attempts = 0;
	while(attempts < 2000 && aincrad.numRooms < 8)
	{
		room room = generateRoom();

		int x = (rand() % (X-3)) + 1;
		int y = (rand() % (Y-2)) + 1;

		if(aincrad.hardness[y][x] != 0 && aincrad.hardness[y][x] != -1)
		{
			if(y + room.height >= Y - 1)
			{	
				++attempts;
				continue;
			}
			if(x + room.width >= X - 2)
			{
				++attempts;
				continue;
			}
			int valid = verifyValidity(room, x, y);
			if(valid)
			{
				++attempts;
				continue;
			}
			else
			{
				attempts = 0;
				placeRoom(room, x, y);
			}
		}
		++attempts;
	}
}

int main(int argc, char** argv)
{
	srand((unsigned) time(0));
	initializeDungeon();
	createRooms();
	printDungeon(0);
	
	return 0;
}
