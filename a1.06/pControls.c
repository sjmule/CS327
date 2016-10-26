#include "pControls.h"
#include "movement.h"

int movePlayer(player* character, int ch)
{
	int good = 0;
	switch(ch)
	{
		case '7':
		case 'y':
			good = isMoveValid(character, 0);
			if(good)
				doMove(character, 0);
			break;
		case '8':
		case 'k':
			good = isMoveValid(character, 1);
			if(good)
				doMove(character, 1);
			break;
		case '9':
		case 'u':
			good = isMoveValid(character, 2);
			if(good)
				doMove(character, 2);
			break;
		case '6':
		case 'l':
			good = isMoveValid(character, 3);
			if(good)
				doMove(character, 3);
			break;
		case '3':
		case 'n':
			good = isMoveValid(character, 4);
			if(good)
				doMove(character, 4);
			break;
		case '2':
		case 'j':
			good = isMoveValid(character, 5);
			if(good)
				doMove(character, 5);
			break;
		case '1':
		case 'b':
			good = isMoveValid(character, 6);
			if(good)
				doMove(character, 6);
			break;
		case '4':
		case 'h':
			good = isMoveValid(character, 7);
			if(good)
				doMove(character, 7);
			break;
		case '5':
		case ' ':
			character->setTurn(character->getTurn() + (100/character->getSpeed());
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
		if(aincrad.monsters[i].getAlive() == 1)
		{
			char *str = malloc(30);
			monster mon = aincrad.monsters[i];
			char* up;
			int updist = 0;
			if(mon.getY() < kirito.getY())
			{
				up = "north";
				updist = kirito.getY() - mon.getY();
			}
			else
			{
				up = "south";
				updist = mon.getY() - kirito.getY();
			}
			char* left;
			int leftdist = 0;
			if(mon.getX() < kirito.getX())
			{
				left = "west";
				leftdist = kirito.getX() - mon.getX();
			}
			else
			{
				left = "east";
				leftdist = mon.getX() - kirito.getX();
			}
			sprintf(str, "%c, %d %s and %d %s", mon.getSymbol(), updist, up, leftdist, left);
			monList[j++] = str;
		}
	}
	refresh();
	while(1)
	{
		int ch = getch();
		if(ch == 27)
			break;
	}
	for(j = 0; j < alive; ++j)
	{
		free(monList[i]);
	}
	free(monList);
}
