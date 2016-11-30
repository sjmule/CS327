#include "pControls.h"
#include "movement.h"

int move(int dir)
{
	int valid = isMoveValid(kirito, dir, 0);
	if(valid)
	{
		Character* def = checkForOthers(kirito, dir);
		if(def != NULL)
			combat(kirito, def);
		else
		{
			doMove(kirito, dir);
			valid += 2;
		}
	}
	return valid;
}

int movePlayer(int ch)
{
	int good = 0;
	switch(ch)
	{
		case '7':
		case 'y':
			good = move(0);
			break;
		case '8':
		case 'k':
			good = move(1);
			break;
		case '9':
		case 'u':
			good = move(2);
			break;
		case '6':
		case 'l':
			good = move(3);
			break;
		case '3':
		case 'n':
			good = move(4);
			break;
		case '2':
		case 'j':
			good = move(5);
			break;
		case '1':
		case 'b':
			good = move(6);
			break;
		case '4':
		case 'h':
			good = move(7);
			break;
		case '5':
		case ' ':
			if(kirito->hp < 100)
				kirito->hp += 4;
			if(kirito->hp > 100)
				kirito->hp = 100;
			good = 2;
			break;
		default:
			break;
	}
	if(good == 4)
	{
		good -= 2;
		for(unsigned int i = 0; i < aincrad->objects.size(); ++i)
		{
			if((aincrad->objects[i]->x == kirito->x) && (aincrad->objects[i]->y == kirito->y))
			{
				int k = 0;
				for(; k < 10; ++k)
				{
					if(kirito->inventory[i] == NULL)
					{
						Object* obj = new Object(aincrad->objects[i]);
						kirito->inventory[k] = obj;
						delete aincrad->objects[i];
						aincrad->objects.erase(aincrad->objects.begin() + i);
						break;
					}
				}
			}
		}
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
	for(int i = 0; i < 10; ++i)
	{
		if(kirito->inventory[i] != NULL)
			mvprintw(i + 2, 0, "%d: %s", i, kirito->inventory[i]->name.c_str());
		else
			mvprintw(i + 2, 0, "%d:                       ", i);
	}
	int ch = getch();
	while((ch < 48 || ch > 57) && ch != 27)
	{
		mvprintw(0, 0, "Please select a slot 0-9");
		ch = getch();
	}
	if(ch == 27)
		return;
	if(kirito->inventory[ch - 48] != NULL)
	{
		if(kirito->inventory[ch - 48]->type == "WEAPON")
		{
			if(kirito->equip[0] != NULL)
			{
				Object* obj = kirito->equip[0];
				kirito->equip[0] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = obj;
			}
			else
			{
				kirito->equip[0] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = NULL;
			}
		}
		else if(kirito->inventory[ch - 48]->type == "OFFHAND")
		{
			if(kirito->equip[1] != NULL)
			{
				Object* obj = kirito->equip[1];
				kirito->equip[1] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = obj;
			}
			else
			{
				kirito->equip[1] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = NULL;
			}
		}
		else if(kirito->inventory[ch - 48]->type == "RANGED")
		{
			if(kirito->equip[2] != NULL)
			{
				Object* obj = kirito->equip[2];
				kirito->equip[2] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = obj;
			}
			else
			{
				kirito->equip[2] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = NULL;
			}
		}
		else if(kirito->inventory[ch - 48]->type == "ARMOR")
		{
			if(kirito->equip[3] != NULL)
			{
				Object* obj = kirito->equip[3];
				kirito->equip[3] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = obj;
			}
			else
			{
				kirito->equip[3] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = NULL;
			}
		}
		else if(kirito->inventory[ch - 48]->type == "HELMET")
		{
			if(kirito->equip[4] != NULL)
			{
				Object* obj = kirito->equip[4];
				kirito->equip[4] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = obj;
			}
			else
			{
				kirito->equip[4] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = NULL;
			}
		}
		else if(kirito->inventory[ch - 48]->type == "CLOAK")
		{
			if(kirito->equip[5] != NULL)
			{
				Object* obj = kirito->equip[5];
				kirito->equip[5] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = obj;
			}
			else
			{
				kirito->equip[5] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = NULL;
			}
		}
		else if(kirito->inventory[ch - 48]->type == "GLOVES")
		{
			if(kirito->equip[6] != NULL)
			{
				Object* obj = kirito->equip[6];
				kirito->equip[6] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = obj;
			}
			else
			{
				kirito->equip[6] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = NULL;
			}
		}
		else if(kirito->inventory[ch - 48]->type == "BOOTS")
		{
			if(kirito->equip[7] != NULL)
			{
				Object* obj = kirito->equip[7];
				kirito->equip[7] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = obj;
			}
			else
			{
				kirito->equip[7] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = NULL;
			}
		}
		else if(kirito->inventory[ch - 48]->type == "AMULET")
		{
			if(kirito->equip[8] != NULL)
			{
				Object* obj = kirito->equip[8];
				kirito->equip[8] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = obj;
			}
			else
			{
				kirito->equip[8] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = NULL;
			}
		}
		else if(kirito->inventory[ch - 48]->type == "LIGHT")
		{
			if(kirito->equip[9] != NULL)
			{
				Object* obj = kirito->equip[9];
				kirito->equip[9] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = obj;
			}
			else
			{
				kirito->equip[9] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = NULL;
			}
		}
		else if(kirito->inventory[ch - 48]->type == "RING")
		{
			if((kirito->equip[10] != NULL) && (kirito->equip[11] != NULL))
			{
				Object* obj = kirito->equip[10];
				kirito->equip[10] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = obj;
			}
			else if(kirito->equip[10] == NULL)
			{
				kirito->equip[10] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = NULL;
			}
			else
			{
				kirito->equip[11] = kirito->inventory[ch - 48];
				kirito->inventory[ch - 48] = NULL;
			}
		}
	}
}

void takeOffItem()
{
	mvprintw(1, 0, "Select an item to take off");
	for(int i = 0; i < 12; ++i)
	{
		if(kirito->equip[i] != NULL)
			mvprintw(i + 2, 0, "%c: %s", 97 + i, kirito->equip[i]->name.c_str());
		else
			mvprintw(i + 2, 0, "%c:                       ", 97 + i);
	}
	int ch = getch();
	while((ch < 97 || ch > 108) && ch != 27)
	{
		mvprintw(0, 0, "Please select a slot a-l");
		ch = getch();
	}
	if(ch == 27)
		return;
	if(kirito->equip[ch - 97] != NULL)
	{
		int i = 0;
		for(; i < 10; ++i)
		{
			if(kirito->inventory[i] == NULL)
				break;
		}
		if(i == 10)
			mvprintw(0, 0, "You have no empty inventory slots");
		else
		{
			kirito->inventory[i] = kirito->equip[ch - 97];
			kirito->equip[ch - 97] = NULL;
		}
	}
}

void dropItem()
{
	mvprintw(1, 0, "Select an item to drop");
	for(int i = 0; i < 10; ++i)
	{
		if(kirito->inventory[i] != NULL)
			mvprintw(i + 2, 0, "%d: %s", i, kirito->inventory[i]->name.c_str());
		else
			mvprintw(i + 2, 0, "%d:                       ", i);
	}
	int ch = getch();
	while((ch < 48 || ch > 57) && ch != 27)
	{
		mvprintw(0, 0, "Please select a slot 0-9");
		ch = getch();
	}
	if(ch == 27)
		return;
	if(kirito->inventory[ch - 48] != NULL)
	{
		Object* obj = new Object(kirito->inventory[ch - 48]);
		obj->x = kirito->x;
		obj->y = kirito->y;
		aincrad->objects.push_back(obj);
		delete kirito->inventory[ch - 48];
		kirito->inventory[ch - 48] = NULL;
	}
}

void expungeItem()
{
	mvprintw(1, 0, "Select an item to remove permanently from the game");
	for(int i = 0; i < 10; ++i)
	{
		if(kirito->inventory[i] != NULL)
			mvprintw(i + 2, 0, "%d: %s", i, kirito->inventory[i]->name.c_str());
		else
			mvprintw(i + 2, 0, "%d:                       ", i);
	}
	int ch = getch();
	while((ch < 48 || ch > 57) && ch != 27)
	{
		mvprintw(0, 0, "Please select a slot 0-9");
		ch = getch();
	}
	if(ch == 27)
		return;
	if(kirito->inventory[ch - 48] != NULL)
	{
		delete kirito->inventory[ch - 48];
		kirito->inventory[ch - 48] = NULL;
	}
}

void listInventory()
{
	mvprintw(1, 1, "Your inventory");
	for(int i = 0; i < 10; ++i)
	{
		if(kirito->inventory[i] != NULL)
			mvprintw(i + 2, 0, "%d: %s", i, kirito->inventory[i]->name.c_str());
		else
			mvprintw(i + 2, 0, "%d:                       ", i);
	}
	getch();
}

void listEquipment()
{
	mvprintw(1, 0, "Your equipped items");
	for(int i = 0; i < 12; ++i)
	{
		if(kirito->equip[i] != NULL)
			mvprintw(i + 2, 0, "%c: %s", i + 97, kirito->equip[i]->name.c_str());
		else
			mvprintw(i + 2, 0, "%c:                       ", i + 97);
	}
	getch();
}

void inspectItem()
{
	mvprintw(1, 0, "Select an item to inspect");
	for(int i = 0; i < 10; ++i)
	{
		if(kirito->inventory[i] != NULL)
			mvprintw(i + 2, 0, "%d: %s", i, kirito->inventory[i]->name.c_str());
		else
			mvprintw(i + 2, 0, "%d                       ", i);
	}
	int ch = getch();
	while((ch < 48 || ch > 57) && ch != 27)
	{
		mvprintw(0, 0, "Please select a slot 0-9");
		ch = getch();
	}
	if(ch == 27)
		return;
	if(kirito->inventory[ch - 48] != NULL)
	{
		for(int i = 0; i < 12; ++i)
		{
			mvprintw(i, 0, "                                              ");
		}
		mvprintw(2, 0, "%s", kirito->inventory[ch - 48]->description.c_str());
	}
	getch();
}

void rangedAttack(int dir)
{
	
}

void attackRanged()
{
	if(kirito->equip[2] != NULL)
	{
		mvprintw(0, 0, "Please select a direction");
		int ch = getch();
		switch(ch)
		{
			case '7':
			case 'y':
				rangedAttack(0);
				break;
			case '8':
			case 'k':
				rangedAttack(1);
				break;
			case '9':
			case 'u':
				rangedAttack(2);
				break;
			case '6':
			case 'l':
				rangedAttack(3);
				break;
			case '3':
			case 'n':
				rangedAttack(4);
				break;
			case '2':
			case 'j':
				rangedAttack(5);
				break;
			case '1':
			case 'b':
				rangedAttack(6);
				break;
			case '4':
			case 'h':
				rangedAttack(7);
				break;
			case '5':
			case ' ':
				break;
			default:
				break;
		}
	}
	else
	{
		mvprintw(0, 0, "No ranged weapon equiped");
		getch();
	}
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
			return 3;
		}
		else
			return 0;
	}
	else if(ch == '<')
	{
		if((kirito->x == aincrad->stairUpX) && (kirito->y == aincrad->stairUpY))
		{
			return 3;
		}
		else
			return 0;
	}
	else if(ch == 'w')
	{
		wearItem();
		printDungeon();
	}
	else if(ch == 't')
	{
		takeOffItem();
		printDungeon();
	}
	else if(ch == 'd')
	{
		dropItem();
		printDungeon();
	}
	else if(ch == 'x')
	{
		expungeItem();
		printDungeon();
	}
	else if(ch == 'i')
	{
		listInventory();
		printDungeon();
	}
	else if(ch == 'e')
	{
		listEquipment();
		printDungeon();
	}
	else if(ch == 'I')
	{
		inspectItem();
		printDungeon();
	}
	else if(ch == 'r')
	{
		attackRanged();
		printDungeon();
	}
	else
	{
		int good = movePlayer(ch);
		return good;
	}
	return 0;
}
