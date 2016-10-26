#include "dungeon.h"
#include "character.h"
#include "player.h"

class Player : public Character
{
	int[Y][X] visible = new int[Y][X];
	public:
		void initializeVisible();
		int[][] getVisible() { return visible; }
		void setVisible(int x, int y);
};

void initializeVisible()
{
	for(int i = 0; i < Y; ++i)
	{
		for(int j = 0; j < X; ++j)
		{
			visible[i][j] = ' ';
		}
	}
	for(int i = 0; i < X; ++i)
	{
		visible[0][i] = '-'
		visible[Y-1][i] = '-';
	}
	for(int i = 1; i < Y - 1; ++i)
	{
		visible[i][0] = '|';
		visible[i][X-1] = '|';
	}
}

void setVisible()
{
	int i = this.y;
	for(int k = 0; k < 3; ++k)
	{
		if((i - 1) >= 1)
			i -= 1;
		else
			break;
	}
	int j = this.x;
	for(int k = 0; k < 3; ++k)
	{
		if((j - 1) >= 1)
			j -= 1;
		else
		 break;
	}
	for(; i <= (y + 3) && i < Y; ++i)
	{
		for(int k = j; k <= (x + 3) && k < X; ++k)
		{
			visible[i][k] = aincrad.map[i][k];
		}
	}
}
