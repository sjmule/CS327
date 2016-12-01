#include "movement.h"
#include "routing.h"

int switchBoard(Monster* mon, int playerX, int playerY)
{
	int x = mon->x - playerX;
	int y = mon->y - playerY;
	if(x == y)
	{
		if(x < 0)
			return 4;
		if(x > 0)
			return 0;
	}
	else if(x < y)
	{
		if(x < 0)
		{
			if(y < 0)
				return 4;
			else if(y > 0)
				return 2;
			else
				return 3;
		}
		else if(x > 0)
			return 0;
		else
			return 1;
	}
	else
	{
		if(x < 0)
			return 4;
		else if(x > 0)
		{
			if(y < 0)
				return 6;
			else if(y > 0)
				return 0;
			else
				return 7;
		}
		else
			return 5;
	}
	return 8;
}

int inRoom(int x, int y)
{
	int i = 0;
	for(; i < aincrad->numRooms; ++i)
	{
		room temp = aincrad->rooms[i];
		if((x >= temp.x) && (x <= (temp.x + temp.width - 1)))
		{
			if((y >= temp.y) && (y <= (temp.y + temp.height - 1)))
				return i;
		}
	}
	return -1;
}

Character* check(int id, int x, int y)
{
	// if this is a monster
	if(kirito->id != id)
	{
		if((kirito->x == x) && (kirito->y == y))
			return kirito;
		else
		{
			for(unsigned int i = 0; i < aincrad->monsters.size(); ++i)
			{
				if(aincrad->monsters[i].id == id)
					continue;
				else
				{
					if((aincrad->monsters[i].x == x) && (aincrad->monsters[i].y == y) && (aincrad->monsters[i].alive == 1))
						return &aincrad->monsters[i];
				}
			}
		}
	}
	// if this is kirito
	else
	{
		for(unsigned int i = 0; i < aincrad->monsters.size(); ++i)
		{
			if((aincrad->monsters[i].x == x) && (aincrad->monsters[i].y == y) && (aincrad->monsters[i].alive == 1))
				return &aincrad->monsters[i];
		}
	}
	return NULL;
}

Character* checkForOthers(Character* entity, int dir)
{
	int x = entity->x;
	int y = entity->y;

	switch(dir)
	{
		case 0:
			x--;
			y--;
			return check(entity->id, x, y);
		case 1:
			y--;
			return check(entity->id, x, y);
		case 2:
			x++;
			y--;
			return check(entity->id, x, y);
		case 3:
			x++;
			return check(entity->id, x, y);
		case 4:
			x++;
			y++;
			return check(entity->id, x, y);
		case 5:
			y++;
			return check(entity->id, x, y);
		case 6:
			x--;
			y++;
			return check(entity->id, x, y);
		case 7:
			x--;
			return check(entity->id, x, y);
		default:
			return NULL;
	}
}

void makeTunnel(int x, int y)
{
	if(aincrad->map[y][x] == ' ')
		aincrad->map[y][x] = '#';
}

// 0 invalid move, 1 invalid move - recalculate distance, 2 valid move, 3 valid move - recalculate distance
int valid(int x, int y, int tunnel)
{
	if(tunnel == 4) // monster
	{
		if(aincrad->hardness[y][x] == 255)
			return 0;
		else
		{
			if(aincrad->hardness[y][x] == 0) // open space
				return 2;
			else if(aincrad->hardness[y][x] - 85 <= 0) // after digging will be open
				return 3;
			else // dig
			{
				aincrad->hardness[y][x] = aincrad->hardness[y][x] - 85;
				return 1;
			}
		}
	}
	else
	{
		if(aincrad->hardness[y][x] == 0)
			return 2;
		else
			return 0;
	}
}

int isMoveValid(Character* entity, int dir, int tunnel)
{
	int x = entity->x;
	int y = entity->y;

	switch(dir)
	{
		case 0:
			x--;
			y--;
			return valid(x, y, tunnel);
		case 1:
			y--;
			return valid(x, y, tunnel);
		case 2:
			x++;
			y--;
			return valid(x, y, tunnel);
		case 3:
			x++;
			return valid(x, y, tunnel);
		case 4:
			x++;
			y++;
			return valid(x, y, tunnel);
		case 5:
			y++;
			return valid(x, y, tunnel);
		case 6:
			x--;
			y++;
			return valid(x, y, tunnel);
		case 7:
			x--;
			return valid(x, y, tunnel);
		default:
			return 0;
	}
}

void doMove(Character* entity, int dir)
{
	makeTunnel(entity->x, entity->y);
	switch(dir)
	{
		case 0:
			entity->x = entity->x - 1;
			entity->y = entity->y - 1;
			break;
		case 1:
			entity->y = entity->y - 1;
			break;
		case 2:
			entity->x = entity->x + 1;
			entity->y = entity->y - 1;
			break;
		case 3:
			entity->x = entity->x + 1;
			break;
		case 4:
			entity->x = entity->x + 1;
			entity->y = entity->y + 1;
			break;
		case 5:
			entity->y = entity->y + 1;
			break;
		case 6:
			entity->x = entity->x - 1;
			entity->y = entity->y + 1;
			break;
		case 7:
			entity->x = entity->x - 1;
			break;
		default:
			break;
	}
	aincrad->hardness[(int)entity->y][(int)entity->x] = 0;
}

void combat(Character* attack, Character* defence, int ranged)
{
	// if kirito attacking
	if(attack->id == 0)
	{
		int damage = 0;
		if(ranged)
			damage += ((Player*)attack)->equip[2]->damage.roll();
		else
		{
			if(((Player*)attack)->equip[0] != NULL)
				damage += ((Player*)attack)->equip[0]->damage.roll();
			else
				damage += attack->damageDice.roll();
		}
		if(((Player*)attack)->equip[1] != NULL)
			damage += ((Player*)attack)->equip[1]->damage.roll();
		for(int i = 3; i < 12; ++i)
		{
			if(((Player*)attack)->equip[i] != NULL)
				damage += ((Player*)attack)->equip[i]->damage.roll();
		}
		defence->hp -= damage;
		mvprintw(Y+3, 0, "%c's health: %d", defence->symbol, defence->hp);
		refresh();
		if(defence->hp <= 0)
			defence->alive = 0;
	}
	else
	{
		// if kirito is defending
		if(defence->id == 0)
		{
			int dodge = 0;
			for(int i = 0; i < 12; ++i)
			{
				if(((Player*)defence)->equip[i] != NULL)
					dodge += ((Player*)defence)->equip[i]->dodge;
			}
			if(dodge)
			{
				int chance = rand() % 100;
				if(chance <= dodge)
					return;
			}
			int block = 0;
			for(int i = 0; i < 12; ++i)
			{
				if(((Player*)defence)->equip[i] != NULL)
					block += ((Player*)defence)->equip[i]->defence;
			}
			int damage = attack->damageDice.roll() - block;
			if(damage > 0)
				defence->hp -= damage;
			if(defence->hp <= 0)
			{
				defence->hp = 0;
				defence->alive = 0;
			}
		}
	}
}

void relocate(Character* ch, int x, int y)
{
	ch->x = x;
	ch->y = y;
}

void moveRandom(Monster* entity, int tunnel)
{
	int valid = 0;
	int dir = rand() % 8;
	valid = isMoveValid(entity, dir, tunnel);
	if(valid > 1)
	{
		Character* def = checkForOthers(entity, dir);
		if(def == kirito)
		{
			combat(entity, def, 0);
		}
		else
		{
			if(def != NULL)
			{
				relocate(def, entity->x, entity->y);
			}
			doMove(entity, dir);
			if(valid == 3)
			{
				calculateDistances(kirito->x, kirito->y, 0);
				calculateDistances(kirito->x, kirito->y, 1);
			}
		}
	}
	if(valid == 1)
	{
		calculateDistances(kirito->x, kirito->y, 0);
		calculateDistances(kirito->x, kirito->y, 1);
	}
}

void moveDeliberately(Monster* mon)
{
	if(mon->attributes & TELEPATHIC) // is telepathic
	{
		mon->playerX = kirito->x;
		mon->playerY = kirito->y;
		if(mon->attributes & INTELLIGENT) // is intelligent
		{
			int dir = shortestPath(mon->x, mon->y, (mon->attributes & TUNNELING));
			int valid = isMoveValid(mon, dir, (mon->attributes & TUNNELING));
			if(valid > 1)
			{
				Character* def = checkForOthers(mon, dir);
				if(def == kirito)
				{
					combat(mon, def, 0);
				}
				else
				{
					if(def != NULL)
					{
						relocate(def, mon->x, mon->y);
					}
					doMove(mon, dir);
					if(valid == 3)
					{
						calculateDistances(kirito->x, kirito->y, 0);
						calculateDistances(kirito->x, kirito->y, 1);
					}
				}
			}
			if(valid == 1)
			{
				calculateDistances(kirito->x, kirito->y, 0);
				calculateDistances(kirito->x, kirito->y, 1);
			}
		}
		else // is not intelligent
		{
			int dir = switchBoard(mon, mon->playerX, mon->playerY);
			int valid = isMoveValid(mon, dir, (mon->attributes & TUNNELING));
			if(valid > 1)
			{
				Character* def = checkForOthers(mon, dir);
				if(def == kirito)
				{
					combat(mon, def, 0);
				}
				else
				{
					if(def != NULL)
					{
						relocate(def, mon->x, mon->y);
					}
					doMove(mon, dir);
					if(valid == 3)
					{
						calculateDistances(kirito->x, kirito->y, 0);
						calculateDistances(kirito->x, kirito->y, 1);
					}
				}
			}
			if(valid == 1)
			{
				calculateDistances(kirito->x, kirito->y, 0);
				calculateDistances(kirito->x, kirito->y, 1);
			}
		}
	}
	else // is not telepathic
	{
		if(mon->playerX != 0)
		{
			int dir = switchBoard(mon, mon->playerX, mon->playerY);
			int valid = isMoveValid(mon, dir, (mon->attributes & TUNNELING));
			if(valid > 1)
			{
				Character* def = checkForOthers(mon, dir);
				if(def == kirito)
				{
					combat(mon, def, 0);
				}
				else
				{
					if(def != NULL)
					{
						relocate(def, mon->x, mon->y);
					}
					doMove(mon, dir);
					if(valid == 3)
					{
						calculateDistances(kirito->x, kirito->y, 0);
						calculateDistances(kirito->x, kirito->y, 1);
					}
				}
			}
			if(valid == 1)
			{
				calculateDistances(kirito->x, kirito->y, 0);
				calculateDistances(kirito->x, kirito->y, 1);
			}
			if((mon->x == mon->playerX) && (mon->y == mon->playerY))
			{
				mon->playerX = 0;
				mon->playerY = 0;
			}
		}
		else
		{
			moveRandom(mon, (mon->attributes & TUNNELING));
		}
	}
}

void moveMonster(Monster* mon)
{
	mon->turn = mon->turn + (100/mon->speed);
	// if we can see the PC, move towards him
	int playerRoom = inRoom(kirito->x, kirito->y);
	if((playerRoom >=0) && (inRoom(mon->x, mon->y) == playerRoom))
	{
		int dir = switchBoard(mon, kirito->x, kirito->y);
		int valid = isMoveValid(mon, dir, (mon->attributes & TUNNELING));
		if(valid > 1)
		{
			Character* def = checkForOthers(mon, dir);
			if(def == kirito)
			{
				combat(mon, def, 0);
			}
			else
			{
				if(def != NULL)
				{
					relocate(def, mon->x, mon->y);
				}
				doMove(mon, dir);
				if(valid == 3)
				{
					calculateDistances(kirito->x, kirito->y, 0);
					calculateDistances(kirito->x, kirito->y, 1);
				}
			}
		}
		if(valid == 1)
		{
			calculateDistances(kirito->x, kirito->y, 0);
			calculateDistances(kirito->x, kirito->y, 1);
		}
		if(mon->attributes & INTELLIGENT)
		{
			mon->playerX = kirito->x;
			mon->playerY = kirito->y;
		}
		return;
	}
	else
	{
		if(mon->x == kirito->x) // player is above or below monster
		{
			if((mon->y - kirito->y) < 0) // monster is above player
			{
				int i = mon->y;
				int wall = 0;
				for(; i < kirito->y; ++i)
				{
					if(aincrad->hardness[i][(int)mon->x] != 0)
					{
						wall = 1;
						break;
					}
				}
				if(!wall)
				{
					Character* def = checkForOthers(mon, 5);
					if(def == kirito)
					{
						combat(mon, def, 0);
					}
					else
					{
						if(def != NULL)
						{
							relocate(def, mon->x, mon->y);
						}
						doMove(mon, 5);
					}
					if(mon->attributes & INTELLIGENT)
					{
						mon->playerX = kirito->x;
						mon->playerY = kirito->y;
					}
					return;
				}
			}
			else // monster is below player
			{
				int i = kirito->y;
				int wall = 0;
				for(; i < mon->y; ++i)
				{
					if(aincrad->hardness[i][(int)mon->x] != 0)
					{
						wall = 1;
						break;
					}
				}
				if(!wall)
				{
					Character* def = checkForOthers(mon, 1);
					if(def == kirito)
					{
						combat(mon, def, 0);
					}
					else
					{
						if(def != NULL)
						{
							relocate(def, mon->x, mon->y);
						}
						doMove(mon, 1);
					}
					if(mon->attributes & INTELLIGENT)
					{
						mon->playerX = kirito->x;
						mon->playerY = kirito->y;
					}
					return;
				}
			}
		}
		if(mon->y == kirito->y) // player is to left or right of monster
		{
			if((mon->x - kirito->x) < 0) // monster is to left of player
			{
				int i = mon->x;
				int wall = 0;
				for(; i < kirito->x; ++i)
				{
					if(aincrad->hardness[(int)mon->y][i] != 0)
					{
						wall = 1;
						break;
					}
				}
				if(!wall)
				{
					Character* def = checkForOthers(mon, 3);
					if(def == kirito)
					{
						combat(mon, def, 0);
					}
					else
					{
						if(def != NULL)
						{
							relocate(def, mon->x, mon->y);
						}
						doMove(mon, 3);
					}
					if(mon->attributes & INTELLIGENT)
					{
						mon->playerX = kirito->x;
						mon->playerY = kirito->y;
					}
					return;
				}
			}
			else // monster is to right of player
			{
				int i = kirito->x;
				int wall = 0;
				for(; i < mon->x; ++i)
				{
					if(aincrad->hardness[(int)mon->y][i] != 0)
					{
						wall = 1;
						break;
					}
				}
				if(!wall)
				{
					Character* def = checkForOthers(mon, 7);
					if(def == kirito)
					{
						combat(mon, def, 0);
					}
					else
					{
						if(def != NULL)
						{
							relocate(def, mon->x, mon->y);
						}
						doMove(mon, 7);
					}
					if(mon->attributes & INTELLIGENT)
					{
						mon->playerX = kirito->x;
						mon->playerY = kirito->y;
					}
					return;
				}
			}
		}
	}
	// else behave based on characteristics
	if((mon->attributes & ERRATIC) == 1)
	{
		int act = rand() % 100;
		if(act < 50)
		{
			moveRandom(mon, (mon->attributes & TUNNELING));
		}
		else
		{
			if((mon->attributes & INTELLIGENT) || (mon->attributes & TELEPATHIC))
				moveDeliberately(mon);
			else
				moveRandom(mon, (mon->attributes & TUNNELING));
		}
	}
	else if((mon->attributes & INTELLIGENT) || (mon->attributes & TELEPATHIC))
		moveDeliberately(mon);
	else
		moveRandom(mon, (mon->attributes & TUNNELING));
}
