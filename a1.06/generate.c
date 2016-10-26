#include "generate.h"

void setImmutable()
{
	int i = 0;
	for(; i < X; ++i)
	{
		aincrad.hardness[0][i] = 255;
	}
	for(i = 0; i < X; ++i)
	{
		aincrad.hardness[Y-1][i] = 255;
	}
	for(i = 1; i < Y - 1; ++i)
	{
		aincrad.hardness[i][0] = 255;
		aincrad.hardness[i][X-1] = 255;
	}
}

void setHardness()
{
	int i = 1;
	for(; i < Y - 1; ++i)
	{
		int j = 1;
		for(; j < X - 1; ++j)
		{
			aincrad.hardness[i][j] = (rand() % 254) + 1;
		}
	}
}

void setBoundary()
{
	int i = 0;
	for(; i < X; ++i)
	{
		aincrad.map[0][i] = '-';
		aincrad.map[Y-1][i] = '-';
	}
	for(i = 1; i < Y - 1; ++i)
	{
		aincrad.map[i][0] = '|';
		aincrad.map[i][X-1] = '|';
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
	}

	setBoundary();

	aincrad.numRooms = 0;
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
	if(x + room.width + 1 != X - 2)
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
	room.x = x;
	room.y = y;
	room.number = aincrad.numRooms;
	aincrad.rooms[aincrad.numRooms] = room;
	aincrad.numRooms++;
}

void createRooms()
{
	int attempts = 0;
	while(attempts < 2000 && aincrad.numRooms < 8)
	{
		room room = generateRoom();

		int x = (rand() % (X-2)) + 1;
		int y = (rand() % (Y-2)) + 1;

		if(aincrad.hardness[y][x] != 0 && aincrad.hardness[y][x] != 255)
		{
			if(y + room.height >= Y - 1)
			{
				++attempts;
				continue;
			}
			if(x + room.width >= X - 1)
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
	int up = rand() % 9;
	aincrad.stairUpX = aincrad.rooms[up].x + (rand() % aincrad.rooms[up].width);
	aincrad.stairUpY = aincrad.rooms[up].y + (rand() % aincrad.rooms[up].height);
	int down = 0;
	while(1)
	{
		down = rand() % 9;
		if(down != up)
			break;
	}
	aincrad.stairDownX = aincrad.rooms[down].x + (rand() % aincrad.rooms[down].width);
	aincrad.stairDownY = aincrad.rooms[down].y + (rand() % aincrad.rooms[down].height);
}

void connectRooms()
{
	int i = 0;
	for(; i < 7; ++i)
	{
		room first = aincrad.rooms[i];
		room second = aincrad.rooms[i+1];
		// first room left and above second
		int x1 = first.x + (rand() % first.width);
		int x2 = second.x + (rand() % second.width);
		int y1 = first.y + (rand() % first.height);
		int y2 = second.y + (rand() % second.height);
		if(x1 <= x2 && y1 <= y2)
		{
			int i = x1;
			for(; i < x2; ++i)
			{
				if(aincrad.hardness[y1][i] != 0)
				{
					aincrad.hardness[y1][i] = 0;
					aincrad.map[y1][i] = '#';
				}
			}
			for(i = y1; i < y2; ++i)
			{
				if(aincrad.hardness[i][x2] != 0)
				{
					aincrad.hardness[i][x2] = 0;
					aincrad.map[i][x2] = '#';
				}
			}
		}
		// first room left and below second
		else if(x1 <= x2 && y1 >= y2)
		{
			int i = x1;
			for(; i <= x2; ++i)
			{
				if(aincrad.hardness[y1][i] != 0)
				{
					aincrad.hardness[y1][i] = 0;
					aincrad.map[y1][i] = '#';
				}
			}
			for(i = y2; i < y1; ++i)
			{
				if(aincrad.hardness[i][x2] != 0)
				{
					aincrad.hardness[i][x2] = 0;
					aincrad.map[i][x2] = '#';
				}
			}
		}
		// first room right and above second
		else if(x1 >= x2 && y1 <= y2)
		{
			int i = x2;
			for(; i <= x1; ++i)
			{
				if(aincrad.hardness[y2][i] != 0)
				{
					aincrad.hardness[y2][i] = 0;
					aincrad.map[y2][i] = '#';
				}
			}
			for(i = y1; i < y2; ++i)
			{
				if(aincrad.hardness[i][x1] != 0)
				{
					aincrad.hardness[i][x1] = 0;
					aincrad.map[i][x1] = '#';
				}
			}
		}
		// first room right and below second
		else if(x1 >= x2 && y1 >= y2)
		{
			int i = x2;
			for(; i < x1; ++i)
			{
				if(aincrad.hardness[y2][i] != 0)
				{
					aincrad.hardness[y2][i] = 0;
					aincrad.map[y2][i] = '#';
				}
			}
			for(i = y2; i < y1; ++i)
			{
				if(aincrad.hardness[i][x1] != 0)
				{
					aincrad.hardness[i][x1] = 0;
					aincrad.map[i][x1] = '#';
				}
			}
		}
	}
}

void createMonsters()
{
	static int id = 1;
	int i = 0;
	for(; i < aincrad.numMonsters; ++i)
	{
		monster mon;
		mon.base = malloc(sizeof(entity));
		mon.attributes = 0;
		int attr = rand() % 100;
		if(attr < 50)
			mon.attributes = mon.attributes | INTELLIGENT;
		attr = rand() % 100;
		if(attr < 50)
			mon.attributes = mon.attributes | TELEPATHIC;
		attr = rand() % 100;
		if(attr < 50)
			mon.attributes = mon.attributes | TUNNELING;
		attr = rand() % 100;
		if(attr < 50)
			mon.attributes = mon.attributes | ERRATIC;
		attr = (rand() % 15) + 5;
		mon.base->speed = attr;
		while(1)
		{
			mon.base->x = (rand() % (X - 2)) + 1;
			mon.base->y = (rand() % (Y - 2)) + 1;
			if(aincrad.hardness[mon.base->y][mon.base->x] == 0)
				break;
		}
		mon.base->id = id++;
		mon.base->symbol = (rand() % 25) + 97;
		mon.playerX = 0;
		mon.playerY = 0;
		mon.base->turn = 0;
		mon.base->alive = 1;
		aincrad.monsters[i] = mon;
		++monCount;
	}
}
