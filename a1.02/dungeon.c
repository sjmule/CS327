#include "generate.h"

dungeon aincrad;

void saveDungeon()
{

}

void loadDungeon()
{

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

	char* home = getenv("HOME");
	char* path = strcat(home, "/.rlg327");
	printf("%s\n", path);
	mkdir(path, 0777);

	return 0;
}
