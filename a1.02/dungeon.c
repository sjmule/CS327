#include "generate.h"

dungeon aincrad;

int save = 0;
int load = 0;

FILE *file;

void saveDungeon(char* path)
{
	char* name = strcat(path, "/dungeon");
	file = fopen(name, "w");

	fclose(file);
}

void loadDungeon(char* path)
{
	char* name = strcat(path, "/dungeon");
	file = fopen(name, "r");

	fclose(file);
}

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
				printf("%d", atoi(aincrad.hardness[i][j]));
			}
			printf("\n");
		}
	}
}

int main(int argc, char** argv)
{
	char* home = getenv("HOME");
	char* path = strcat(home, "/.rlg327");
	mkdir(path, 0777);

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
		loadDungeon();
	else
	{
		srand((unsigned) time(0));
		initializeDungeon();
		createRooms();
		connectRooms();
	}

	if(save == 1)
		saveDungeon();

	printDungeon(0);

	return 0;
}
