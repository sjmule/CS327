#include "pControls.h"
#include "movement.h"

int movePlayer(player* entity, int ch)
{
	int good = 0;
	switch(ch)
	{
		case '7':
		case 'y':
			good = isMoveValid((character*)entity, 0, 0);
			if(good)
				doMove((character*)entity, 0);
			break;
		case '8':
		case 'k':
			good = isMoveValid((character*)entity, 1, 0);
			if(good)
				doMove((character*)entity, 1);
			break;
		case '9':
		case 'u':
			good = isMoveValid((character*)entity, 2, 0);
			if(good)
				doMove((character*)entity, 2);
			break;
		case '6':
		case 'l':
			good = isMoveValid((character*)entity, 3, 0);
			if(good)
				doMove((character*)entity, 3);
			break;
		case '3':
		case 'n':
			good = isMoveValid((character*)entity, 4, 0);
			if(good)
				doMove((character*)entity, 4);
			break;
		case '2':
		case 'j':
			good = isMoveValid((character*)entity, 5, 0);
			if(good)
				doMove((character*)entity, 5);
			break;
		case '1':
		case 'b':
			good = isMoveValid((character*)entity, 6, 0);
			if(good)
				doMove((character*)entity, 6);
			break;
		case '4':
		case 'h':
			good = isMoveValid((character*)entity, 7, 0);
			if(good)
				doMove((character*)entity, 7);
			break;
		case '5':
		case ' ':
			setTurn((character*)entity, getTurn((character*)entity) + (100/getSpeed((character*)entity)));
			good = 1;
			break;
		default:
			break;
	}
	return good;
}

void displayMonsters()
{
	int offset = 0;
	int i = 0;
	int alive = monstersAlive();
	char **monList = malloc(alive * sizeof(char*));
	int j = 0;
	for(; i < aincrad.numMonsters; ++i)
	{
		if(getAlive((character*)aincrad.monsters[i]))
		{
			char *str = malloc(30);
			monster* mon = aincrad.monsters[i];
			char* up;
			int updist = 0;
			if(getY((character*)mon) < getY((character*)kirito))
			{
				up = "north";
				updist = getY((character*)kirito) - getY((character*)mon);
			}
			else
			{
				up = "south";
				updist = getY((character*)mon) - getY((character*)kirito);
			}
			char* left;
			int leftdist = 0;
			if(getX((character*)mon) < getX((character*)kirito))
			{
				left = "west";
				leftdist = getX((character*)kirito) - getX((character*)mon);
			}
			else
			{
				left = "east";
				leftdist = getX((character*)mon) - getX((character*)kirito);
			}
			sprintf(str, "%c, %d %s and %d %s", getSymbol((character*)mon), updist, up, leftdist, left);
			monList[j++] = str;
		}
	}

	while(1)
	{
		for(i = offset, j = 1; j < 22 && i < alive; ++j, ++i)
		{
			mvprintw(j, 0, monList[i]);
		}
		for(; j < 22; ++j)
		{
			for(i = 0; i < X; ++i)
			{
				mvaddch(j, i, ' ');
			}
		}
		refresh();
		int ch = getch();
		if(ch == KEY_UP)
		{
			if(offset != 0)
				--offset;
		}
		if(ch == KEY_DOWN)
		{
			if(offset != alive)
				++offset;
		}
		if(ch == 27)
			break;
	}

	for(j = 0; j < alive; ++j)
	{
		free(monList[j]);
	}
	free(monList);
}
