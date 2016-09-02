include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generate.h"

// Look up "Bresenham's Line Drawing Algorithm" Jeremy says it's not easy and it's ugly
// Fuck it, Dijkstra's, go through lowest hardness

dungeon aincrad;

typedef struct VERTEX vertex;

struct VERTEX
{
	int x;
	int y;
};

vertex* dijkstra(int x1, int y1, int x2, int y2)
{
	vertex path[50];
	

	return path;
}

void connectRooms()
{
	int i = 0;
	for(; i < 7; ++i)
	{
		room first = aincrad.rooms[i];
		room second = aincrad.rooms[i+1];
		int x1 = first.x + first.width;
		int y1 = first.y + first.height;
		int x2 = second.x + second.width;
		int y2 = second.y + second.height;
		vertex* path = dijkstra(x1, y1, x2, y2);
	}
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

int main(int argc, char** argv)
{
	srand((unsigned) time(0));
	initializeDungeon();
	createRooms();
	printDungeon(0);
	
	return 0;
}
