#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generate.h"

dungeon aincrad;

void connectRooms()
{
	int i = 0;
	for(; i < 7; ++i)
	{
		room first = aincrad.rooms[i];
		room second = aincrad.rooms[i+1];
		if(first.x <= second.x && first.y <= second.y)
		{
			printf("first x1: %d y1: %d x2: %d y2: %d\n", first.x, first.y, second.x, second.y);
			int i = first.x;
			for(; i < second.x; ++i)
			{
				if(aincrad.hardness[first.y][i] !=0)
				{
					aincrad.hardness[first.y][i] = 0;
					aincrad.map[first.y][i] = '#';
				}
			}
			for(i = first.y; i < second.y; ++i)
			{
				if(aincrad.hardness[i][second.x] != 0)
				{
					aincrad.hardness[i][second.x] = 0;
					aincrad.map[i][second.x] = '#';
				}
			}
		}
		else if(first.x <= second.x && first.y >= second.y)
		{
			printf("second x1: %d y1: %d x2: %d y2: %d\n", first.x, first.y, second.x, second.y);
			int i = first.x;
			for(; i < second.x; ++i)
			{
				if(aincrad.hardness[first.y][i] !=0)
				{
					aincrad.hardness[first.y][i] = 0;
					aincrad.map[first.y][i] = '#';
				}
			}
			for(i = second.y; i < first.y; ++i)
			{
				if(aincrad.hardness[i][second.x] != 0)
				{
					aincrad.hardness[i][second.x] = 0;
					aincrad.map[i][second.x] = '#';
				}
			}
		}
		else if(first.x >= second.x && first.y <= second.y)
		{
			printf("third x1: %d y1: %d x2: %d y2: %d\n", first.x, first.y, second.x, second.y);
			int i = second.x;
			for(; i < first.x; ++i)
			{
				if(aincrad.hardness[second.y][i] !=0)
				{
					aincrad.hardness[second.y][i] = 0;
					aincrad.map[second.y][i] = '#';
				}
			}
			for(i = first.y; i < second.y; ++i)
			{
				if(aincrad.hardness[i][first.x] != 0)
				{
					aincrad.hardness[i][first.x] = 0;
					aincrad.map[i][first.x] = '#';
				}
			}
		}
		else if(first.x >= second.x && first.y >= second.y)
		{
			printf("fourth x1: %d y1: %d x2: %d y2: %d\n", first.x, first.y, second.x, second.y);
			int i = second.x;
			for(; i < first.x; ++i)
			{
				if(aincrad.hardness[second.y][i] !=0)
				{
					aincrad.hardness[second.y][i] = 0;
					aincrad.map[second.y][i] = '#';
				}
			}
			for(i = second.y; i < first.y; ++i)
			{
				if(aincrad.hardness[i][first.x] != 0)
				{
					aincrad.hardness[i][first.x] = 0;
					aincrad.map[i][first.x] = '#';
				}
			}
		}
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
	}
}

int main(int argc, char** argv)
{
	srand((unsigned) time(0));
	initializeDungeon();
	createRooms();
	connectRooms();
	printDungeon(0);
	
	return 0;
}
