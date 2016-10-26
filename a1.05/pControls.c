#include "pControls.h"
#include "movement.h"

int movePlayer(entity* character, int ch)
{
	int good = 0;
	switch(ch)
	{
		case '7':
		case 'y':
			good = isMoveValid(character, 0, 0);
			if(good)
				doMove(character, 0);
			break;
		case '8':
		case 'k':
			good = isMoveValid(character, 1, 0);
			if(good)
				doMove(character, 1);
			break;
		case '9':
		case 'u':
			good = isMoveValid(character, 2, 0);
			if(good)
				doMove(character, 2);
			break;
		case '6':
		case 'l':
			good = isMoveValid(character, 3, 0);
			if(good)
				doMove(character, 3);
			break;
		case '3':
		case 'n':
			good = isMoveValid(character, 4, 0);
			if(good)
				doMove(character, 4);
			break;
		case '2':
		case 'j':
			good = isMoveValid(character, 5, 0);
			if(good)
				doMove(character, 5);
			break;
		case '1':
		case 'b':
			good = isMoveValid(character, 6, 0);
			if(good)
				doMove(character, 6);
			break;
		case '4':
		case 'h':
			good = isMoveValid(character, 7, 0);
			if(good)
				doMove(character, 7);
			break;
		case '5':
		case ' ':
			character->turn += (100/character->speed);
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
		if(aincrad.monsters[i].base->alive == 1)
		{
			char *str = malloc(30);
			monster mon = aincrad.monsters[i];
			char* up;
			int updist = 0;
			if(mon.base->y < kirito.base->y)
			{
				up = "north";
				updist = kirito.base->y - mon.base->y;
			}
			else
			{
				up = "south";
				updist = mon.base->y - kirito.base->y;
			}
			char* left;
			int leftdist = 0;
			if(mon.base->x < kirito.base->x)
			{
				left = "west";
				leftdist = kirito.base->x - mon.base->x;
			}
			else
			{
				left = "east";
				leftdist = mon.base->x - kirito.base->x;
			}
			sprintf(str, "%c, %d %s and %d %s   ", mon.base->symbol, updist, up, leftdist, left);
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
