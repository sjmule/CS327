#include "generate.h"

dungeon aincrad;

int save = 0;
int load = 0;

FILE *file;

void saveDungeon(char* path)
{
	char* name = strcat(path, "/dungeon");
	file = fopen(name, "w");
	
	unsigned char* head = malloc(6);
	head[0] = 'R';
	head[1] = 'L';
	head[2] = 'G';
	head[3] = '3';
	head[4] = '2';
	head[5] = '7';

	unsigned int version = 0;
	
	char* matrix = malloc(1680);
	int i = 0;
	int j = 0;
	for(; j < Y; ++j)
	{
		printf("encoding hardness\n");
		int k = 0;
		for(; k < X; ++k)
		{
			matrix[i++] = (char) aincrad.hardness[j][k];
		}
	}

	unsigned char* locations = malloc(4 * aincrad.numRooms);
	j = 0;
	for(i = 0; i < aincrad.numRooms; ++i)
	{
		locations[j++] = (unsigned char) aincrad.rooms[i].x;
		locations[j++] = (unsigned char) aincrad.rooms[i].width;
		locations[j++] = (unsigned char) aincrad.rooms[i].y;
		locations[j++] = (unsigned char) aincrad.rooms[i].height;
	}

	unsigned int size = 6 + 1680 + (4 * aincrad.numRooms) + 8;
	
	printf("size: %d\n", size);	

	fwrite(head, 1, 6, file);

	unsigned char v[5] = {0};
	snprintf(v, 5, "%u", htonl(version));
	unsigned char s[5] = {0};
	snprintf(s, 5, "%u", htonl(size));

	fwrite(v, 1, 4, file);
	fwrite(s, 1, 4, file);
	fwrite(matrix, 1, 1680, file);
	fwrite(locations, 1, (4 * aincrad.numRooms), file);

	free(head);
	free(matrix);
	free(locations);
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
				printf("%d", aincrad.hardness[i][j]);
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
		loadDungeon(path);
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
		saveDungeon(path);

	printDungeon(0);

	return 0;
}
