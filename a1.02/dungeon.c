#include "generate.h"
#include "save.h"

dungeon aincrad;

int save = 0;
int load = 0;

void printDungeon(int debug)
{
	int i = 0;
	for(; i < Y; ++i)
	{
		int j = 0;
		for(; j < X; ++j)
		{
			printf("%c", aincrad.map[i][j]);
		}
		printf("\n");
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
	version = 0;

	char* home = getenv("HOME");
	char* path = strcat(home, "/.rlg327");
	mkdir(path, 0777);
	char* filePath = strcat(path, "/dungeon");

	if(argc > 1)
	{
		if(strcmp(argv[1], "--save") == 0)
			save = 1;
		else if(strcmp(argv[1], "--load") == 0)
			load = 1;
		if(argc == 3)
		{
			if(strcmp(argv[2], "--save") == 0)
				save = 1;
			else if(strcmp(argv[2], "--load") == 0)
				load = 1;
		}
	}

	if(load == 1)
		loadDungeon(filePath);
	else
	{
		srand((unsigned) time(0));
		aincrad.numRooms = 8;
		aincrad.rooms = malloc(sizeof(room) * 8);
		initializeDungeon();
		createRooms();
		connectRooms();
	}

	if(save == 1)
		saveDungeon(filePath);

	printDungeon(0);

	free(aincrad.rooms);

	return 0;
}
