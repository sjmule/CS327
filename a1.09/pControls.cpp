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
			good = 2;
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
		if(aincrad->monsters.at(i).alive)
		{
			char *str = (char*) malloc(30);
			Monster mon = aincrad->monsters[i];
			char* up = (char*) malloc(6);
			int updist = 0;
			if(mon.y < kirito->y)
			{
				strcpy(up, "north");
				updist = kirito->y - mon.y;
			}
			else
			{
				strcpy(up, "south");
				updist = mon.y - kirito->y;
			}
			char* left = (char*) malloc(5);
			int leftdist = 0;
			if(mon.x < kirito->x)
			{
				strcpy(left, "west");
				leftdist = kirito->x - mon.x;
			}
			else
			{
				strcpy(left, "east");
				leftdist = mon.x - kirito->x;
			}
			sprintf(str, "%c, %d %s and %d %s", mon.symbol, updist, up, leftdist, left);
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

void wearItem()
{
	mvprintw(1, 0, "Select an item to equip");
	for(int i = 0; i < kirito->inventory.size(); ++i)
	{
		if(kirito->inventory[i] != null)
			mvprintw(i + 2, 0, "%s", kirito->inventory.name);
		else
			mvprintw(i + 2, 0, " ");
	}
	int ch = getch();

}

void takeOffItem()
{

}

void dropItem()
{

}

void expungeItem()
{

}

void listInventory()
{

}

void listEquipment()
{

}

void inspectItem()
{

}

int doCharacterAction(int ch)
{
	if(ch == 'Q')
		return 1;
	else if(ch == 'm')
	{
		displayMonsters();
		printDungeon();
	}
	else if(ch == '>')
	{
		if((kirito->x == aincrad->stairDownX) && (kirito->y == aincrad->stairDownY))
		{
			free(aincrad->rooms);
			aincrad->monsters.clear();
			aincrad->objects.clear();
			createDungeon();
			kirito->clearVisible();
			placeCharacters();
			kirito->setVisible();
			return 3;
		}
		else
			continue;
	}
	else if(ch == '<')
	{
		if((kirito->x == aincrad->stairUpX) && (kirito->y == aincrad->stairUpY))
		{
			free(aincrad->rooms);
			aincrad->monsters.clear();
			aincrad->objects.clear();
			createDungeon();
			kirito->clearVisible();
			placeCharacters();
			kirito->setVisible();
			return 3;
		}
		else
			continue;
	}
	else if(ch == 'w')
		wearItem();
	else if(ch == 't')
		takeOffItem();
	else if(ch == 'd')
		dropItem();
	else if(ch == 'x')
		expungeItem();
	else if(ch == 'i')
		listInventory();
	else if(ch == 'e')
		listEquipment();
	else if(ch == 'I')
		inspectItem();
	else
	{
		int good = movePlayer(ch);
		kirito->setVisible();
		return good;
	}
}
