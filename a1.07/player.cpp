#include "dungeon.h"
#include "character.h"
#include "player.h"

void createPlayer()
{
	Player* pc;
	pc = new Player;
	kirito = (player*) pc;
}

int** getVisible(player* p)
{
	return ((Player*) p)->visible;
}

void initializeVisible(player* p)
{
	((Player*) p)->visible = new int*[Y];
	for(int i = 0; i < Y; ++i)
	{
		((Player*) p)->visible[i] = new int[X];
	}
	for(int i = 0; i < Y; ++i)
	{
		for(int j = 0; j < X; ++j)
		{
			((Player*) p)->visible[i][j] = ' ';
		}
	}
	for(int i = 0; i < X; ++i)
	{
		((Player*) p)->visible[0][i] = '-';
		((Player*) p)->visible[Y-1][i] = '-';
	}
	for(int i = 1; i < Y - 1; ++i)
	{
		((Player*) p)->visible[i][0] = '|';
		((Player*) p)->visible[i][X-1] = '|';
	}
}

void setVisible(player* p)
{
	int i = ((Player*) p)->y;
	for(int k = 0; k < 3; ++k)
	{
		if((i - 1) >= 1)
			i -= 1;
		else
			break;
	}
	int j = ((Player*) p)->x;
	for(int k = 0; k < 3; ++k)
	{
		if((j - 1) >= 1)
			j -= 1;
		else
			break;
	}
	for(; i <= (((Player*) p)->y + 3) && i < Y; ++i)
	{
		for(int k = j; k <= (((Player*) p)->x + 3) && k < X; ++k)
		{
			((Player*) p)->visible[i][k] = aincrad.map[i][k];
		}
	}
}

void clearVisible(player* p)
{
	for(int i = 0; i < Y; ++i)
	{
		for(int j = 0; j < X; ++j)
		{
			((Player*) p)->visible[i][j] = ' ';
		}
	}
	for(int i = 0; i < X; ++i)
	{
		((Player*) p)->visible[0][i] = '-';
		((Player*) p)->visible[Y-1][i] = '-';
	}
	for(int i = 1; i < Y - 1; ++i)
	{
		((Player*) p)->visible[i][0] = '|';
		((Player*) p)->visible[i][X-1] = '|';
	}
}

void cleanupPlayer()
{
	delete[] kirito;
}
