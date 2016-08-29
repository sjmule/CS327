#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generate.h"

dungeon_t aincrad;

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
