#include "pControls.h"
#include "movement.h"

int movePlayer(int ch)
{
	int good = 0;
	switch(ch)
	{
		case '7':
		case 'y':
			good = isMoveValid(kirito, 0, 0);
			if(good)
				doMove(kirito, 0);
			break;
		case '8':
		case 'k':
			good = isMoveValid(kirito, 1, 0);
			if(good)
				doMove(kirito, 1);
			break;
		case '9':
		case 'u':
			good = isMoveValid(kirito, 2, 0);
			if(good)
				doMove(kirito, 2);
			break;
		case '6':
		case 'l':
			good = isMoveValid(kirito, 3, 0);
			if(good)
				doMove(kirito, 3);
			break;
		case '3':
		case 'n':
			good = isMoveValid(kirito, 4, 0);
			if(good)
				doMove(kirito, 4);
			break;
		case '2':
		case 'j':
			good = isMoveValid(kirito, 5, 0);
			if(good)
				doMove(kirito, 5);
			break;
		case '1':
		case 'b':
			good = isMoveValid(kirito, 6, 0);
			if(good)
				doMove(kirito, 6);
			break;
		case '4':
		case 'h':
			good = isMoveValid(kirito, 7, 0);
			if(good)
				doMove(kirito, 7);
			break;
		case '5':
		case ' ':
			kirito->turn = kirito->turn + (100/kirito->speed);
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
	char **monList = (char**) malloc(alive * sizeof(char*));
	int j = 0;
	for(; i < aincrad->numMonsters; ++i)
	{
		if(aincrad->monsters[i]->alive)
		{
			char *str = (char*) malloc(30);
			Monster* mon = aincrad->monsters[i];
			char* up = (char*) malloc(6);
			int updist = 0;
			if(mon->y < kirito->y)
			{
				strcpy(up, "north");
				updist = kirito->y - mon->y;
			}
			else
			{
				strcpy(up, "south");
				updist = mon->y - kirito->y;
			}
			char* left = (char*) malloc(5);
			int leftdist = 0;
			if(mon->x < kirito->x)
			{
				strcpy(left, "west");
				leftdist = kirito->x - mon->x;
			}
			else
			{
				strcpy(left, "east");
				leftdist = mon->x - kirito->x;
			}
			sprintf(str, "%c, %d %s and %d %s", mon->symbol, updist, up, leftdist, left);
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
