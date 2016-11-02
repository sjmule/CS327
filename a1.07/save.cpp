#include "save.h"

FILE* file;

void saveDungeon(char* path, int debug)
{
	file = fopen(path, "w");

	if(file == NULL)
	{
		printf("Unable to open file for saving.\n");
		exit(-1);
	}
	if(debug == 1)
		printf("Saving dungeon to file located at %s\n", path);

	unsigned char* head = (unsigned char*) malloc(14);
	head[0] = 'R';
	head[1] = 'L';
	head[2] = 'G';
	head[3] = '3';
	head[4] = '2';
	head[5] = '7';

	head[6] = _itos(htonl(version),0);
	head[7] = _itos(htonl(version),8);
	head[8] = _itos(htonl(version),16);
	head[9] = _itos(htonl(version),24);

	char* matrix = (char*) malloc(1680);
	int i = 0;
	int j = 0;
	for(; j < Y; ++j)
	{
		int k = 0;
		for(; k < X; ++k)
		{
			matrix[i++] = (char) aincrad->hardness[j][k];
		}
	}

	unsigned char* locations = (unsigned char*) malloc(4 * aincrad->numRooms);
	j = 0;
	for(i = 0; i < aincrad->numRooms; ++i)
	{
		locations[j++] = (unsigned char) aincrad->rooms[i].x;
		locations[j++] = (unsigned char) aincrad->rooms[i].width;
		locations[j++] = (unsigned char) aincrad->rooms[i].y;
		locations[j++] = (unsigned char) aincrad->rooms[i].height;
	}

	unsigned int size = 14 + 1680 + (4 * aincrad->numRooms);

	head[10] = _itos(htonl(size),0);
	head[11] = _itos(htonl(size),8);
	head[12] = _itos(htonl(size),16);
	head[13] = _itos(htonl(size),24);

	fwrite(head, 1, 14, file);
	fwrite(matrix, 1, 1680, file);
	fwrite(locations, 1, (4 * aincrad->numRooms), file);

	free(head);
	free(matrix);
	free(locations);
	fclose(file);
}

void loadDungeon(char* path, int debug)
{
	file = fopen(path, "r");

	if(file == NULL)
	{
		printf("Unable to open file for loading\n");
		exit(-1);
	}
	if(debug == 1)
		printf("Loading dungeon from file located at %s\n", path);

	unsigned char* head = (unsigned char*) malloc(6);
	fread(head, 1, 6, file);

	if(strcmp((char*) head, "RLG327") != 0)
	{
		printf("Incompatable file type\n");
		exit(-1);
	}

	unsigned char* versionC = (unsigned char*) malloc(4);
	fread(versionC, 1, 4, file);
	unsigned int fileVersion = _stoi(versionC);
	fileVersion = ntohl(fileVersion);

	if(fileVersion != version)
	{
		printf("Incompatable version number\n");
		exit(-1);
	}

	unsigned char* sizeC = (unsigned char*) malloc(4);
	fread(sizeC, 1, 4, file);
	unsigned int size = _stoi(sizeC);
	size = ntohl(size);

	initializeDungeon();

	unsigned char* matrix = (unsigned char*) malloc(1680);
	fread(matrix, 1, 1680, file);

	int i = 0;
	int j = 0;
	for(; j < Y; ++j)
	{
		int k = 0;
		for(; k < X; ++k)
		{
			aincrad->hardness[j][k] = (int) matrix[i++];
		}
	}

	int end = size - 1680 - 14;
	char* locations = (char*) malloc(end);
	fread(locations, 1, end, file);
	int numRooms = end/4;
	aincrad->rooms = (room*) malloc(sizeof(room) * numRooms);
	room room;

	i = 0;
	for(j = 0; j < numRooms; ++j)
	{
		room.x = (int) locations[i++];
		room.width = (int) locations[i++];
		room.y = (int) locations[i++];
		room.height = (int) locations[i++];
		placeRoom(room, room.x, room.y);
	}

	for(i = 0; i < Y; ++i)
	{
		for(j = 0; j < X; ++j)
		{
			if(aincrad->hardness[i][j] == 0)
				if(aincrad->map[i][j] != '.')
					aincrad->map[i][j] = '#';
		}
	}

	free(head);
	free(versionC);
	free(sizeC);
	free(matrix);
	free(locations);
	fclose(file);
}
