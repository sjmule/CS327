#include "dungeon.h"
#include "character.h"
#include "player.h"

void initializeVisible()
{
	p->visible = new int*[Y];
	for(int i = 0; i < Y; ++i)
	{
		p->visible[i] = new int[X];
	}
	for(int i = 0; i < Y; ++i)
	{
		for(int j = 0; j < X; ++j)
		{
			p->visible[i][j] = ' ';
		}
	}
	for(int i = 0; i < X; ++i)
	{
		p->visible[0][i] = '-';
		p->visible[Y-1][i] = '-';
	}
	for(int i = 1; i < Y - 1; ++i)
	{
		p->visible[i][0] = '|';
		p->visible[i][X-1] = '|';
	}
}

void setVisible()
{
	int i = p->y;
	for(int k = 0; k < 3; ++k)
	{
		if((i - 1) >= 1)
			i -= 1;
		else
			break;
	}
	int j = p->x;
	for(int k = 0; k < 3; ++k)
	{
		if((j - 1) >= 1)
			j -= 1;
		else
			break;
	}
	for(; i <= (p->y + 3) && i < Y; ++i)
	{
		for(int k = j; k <= (p->x + 3) && k < X; ++k)
		{
			p->visible[i][k] = aincrad->map[i][k];
		}
	}
}

void clearVisible()
{
	for(int i = 0; i < Y; ++i)
	{
		for(int j = 0; j < X; ++j)
		{
			p->visible[i][j] = ' ';
		}
	}
	for(int i = 0; i < X; ++i)
	{
		p->visible[0][i] = '-';
		p->visible[Y-1][i] = '-';
	}
	for(int i = 1; i < Y - 1; ++i)
	{
		p->visible[i][0] = '|';
		p->visible[i][X-1] = '|';
	}
}
