#include "move.h"
#include "routing.h"

/*********************************/
/*                               */
/*            0 1 2              */
/*             \|/               */
/*            7-*-3              */
/*             /|\               */
/*            6 5 4              */
/*                               */
/*       mon.pos - pc.pos        */
/*                               */
/* 0: x == y && x >  0 && y >  0 */
/* 1: x <  y && x == 0 && y >  0 */
/* 2: x <  y && x <  0 && y <  0 */
/* 3: x <  y && x <  0 && y == 0 */
/* 4: x == y && x <  0 && y <  0 */
/* 5: x >  y && x == 0 && y <  0 */
/* 6: x >  y && x >  0 && y <  0 */
/* 7: x >  y && x >  0 && y == 0 */
/*                               */
/*********************************/

int inRoom(int x, int y)
{
	int i = 0;
	for(; i < aincrad.numRooms; ++i)
	{
		room temp = aincrad.rooms[i];
		if((x >= temp.x) && (x <= (temp.x + temp.width)))
		{
			if((y >= temp.y) && (y <= (temp.y + temp.height)))
				return i;
		}
	}
	return -1;
}

void cleanCell(int x, int y)
{
	if(inRoom(x, y) >= 0)
		aincrad.map[y][x] = '.';
	else
		aincrad.map[y][x] = '#';
}

// 0 invalid move, 1 invalid move - recalculate distance, 2 valid move, 3 valid move - recalculate distance
int valid(entity entity, int tunnel)
{
	if(tunnel == 4) // monster
	{
		if(aincrad.hardness[entity.y][entity.x] != 255)
			return 0;
		else
		{
			if(aincrad.hardness[entity.y][entity.x] == 0) // open space
				return 2;
			else if(aincrad.hardness[entity.y][entity.x] - 85 <= 0) // after digging will be open
				return 3;
			else // dig
			{
				aincrad.hardness[entity.y][entity.x] = aincrad.hardness[entity.y][entity.x] - 85;
				return 1;
			}
		}
	}
	else if(tunnel == 1) // player
	{
		if(aincrad.hardness[entity.y][entity.x] != 255)
			return 0;
		else
			return 3;
	}
	else
	{
		if(aincrad.hardness[entity.y][entity.x] == 0)
			return 2;
		else
			return 0;
	}
}

int isMoveValid(entity* character, int dir, int tunnel)
{
	entity temp = *character;
	switch(dir)
	{
		case 0:
			temp.x--;
			temp.y--;
			return valid(temp, tunnel);
		case 1:
			temp.y--;
			return valid(temp, tunnel);
		case 2:
			temp.x++;
			temp.y--;
			return valid(temp, tunnel);
		case 3:
			temp.x++;
			return valid(temp, tunnel);
		case 4:
			temp.x++;
			temp.y++;
			return valid(temp, tunnel);
		case 5:
			temp.y++;
			return valid(temp, tunnel);
		case 6:
			temp.x--;
			temp.y++;
			return valid(temp, tunnel);
		case 7:
			temp.x--;
			return valid(temp, tunnel);
		default:
			return 0;
	}
}

void move(entity* character, int dir)
{
	cleanCell(character->x, character->y);	
	switch(dir)
	{
		case 0:
			character->x--;
			character->y--;
			break;
		case 1:
			character->y--;
			break;
		case 2:
			character->x++;
			character->y--;
			break;
		case 3:
			character->x++;
			break;
		case 4:
			character->x++;
			character->y++;
			break;
		case 5:
			character->y++;
			break;
		case 6:
			character->x--;
			character->y++;
			break;
		case 7:
			character->x--;
			break;
		default:
			break;
	}
	aincrad.map[character->y][character->x] = character->symbol;
	aincrad.hardness[character->y][character->x] = 0;
	character->turn += (100/character->speed);
}

void moveRandom(entity* character, int tunnel)
{
	int valid = 0;
	while(!valid)
	{
		int dir = rand() % 8;
		valid = isMoveValid(character, dir, tunnel);
		if(valid < 1)
		{	
			move(character, dir);
			if(valid == 3)
			{
				calculateDistances(kirito.base->x, kirito.base->y, 0);
				calculateDistances(kirito.base->x, kirito.base->y, 1);
			}
		}
		if(valid == 1)
		{
			calculateDistances(kirito.base->x, kirito.base->y, 0);
			calculateDistances(kirito.base->x, kirito.base->y, 1);
		}	
	}
}

void moveDeliberately(monster* mon)
{
	if(mon->attributes & TELEPATHIC) // is telepathic
	{
		mon->playerX = kirito.base.x;
		mon->playerY = kirito.base.y;
		if(mon->attributes & INTELLIGENT) // is intelligent
		{
			// TODO implement shortestPath in routing.c
			int dir = shortestPath(mon->base->x, mon->base->y, mon->playerX, mon->playerY, (mon->attributes & TUNNELING));
			int valid = isMoveValid(mon->base, dir, (mon->attributes & TUNNELING));
			if(valid < 1)
			{
				move(mon->base, dir);
				if(valid == 3)
				{
					calculateDistances(kirito.base->x, kirito.base->y, 0);
					calculateDistances(kirito.base->x, kirito.base->y, 1);
				}
			}
			if(valid == 1)
			{
				calculateDistances(kirito.base->x, kirito.base->y, 0);
				calculateDistances(kirito.base->x, kirito.base->y, 1);
			}
		}
		else // is not intelligent
		{
			// find direction of player
			//
			// TODO
			
		}
	}
	else // is not telepathic
	{
		if(mon->playerX != 0)
		{
			// find direction of last known position of player
			//
			// TODO
		}
	}
}

void moveMonster(monster* mon)
{
	// if we can see the PC, move towards him
	int playerRoom = inRoom(kirito.base->x, kirito.base->y);
	if(playerRoom >=0)
	{
		if(inRoom(mon->base->x, mon->base->y) == playerRoom)
		{
			// move towards player
			//
			// TODO
			if(mon->attributes & INTELLIGENT)
			{
				mon->playerX = kirito.base->x;
				mon->playerY = kirito.base->y;
			}
			return;
		}
		else
		{
			if(mon->base->x == kirito.base->x)
			{
				 if((mon->base->y - kirito.base->y) < 0)
				 {
					int i = mon->base->y;
					int wall = 0;
					for(; i < kirito.base->y; ++i)
					{
						if(aincrad.hardness[i][mon->base->x] != 0)
						{
							wall = 1;
							break;
						}
					}
					if(!wall)
					{
						// move down towards player
						//
						// TODO
						if(mon->attributes & INTELLIGENT)
						{
							mon->playerX = kirito.base->x;
							mon->playerY = kirito.base->y;
						}
						return;
					}
				 }
				 else
				 {
					int i = kirito.base->y;
					int wall = 0;
					for(; i < mon->base->y; ++i)
					{
						if(aincrad.hardness[i][mon->base->x] != 0)
						{
							wall = 1;
							break;
						}
					}
					if(!wall)
					{
						// move up towards player
						//
						// TODO
						if(mon->attributes & INTELLIGENT)
						{
							mon->playerX = kirito.base->x;
							mon->playerY = kirito.base->y;
						}
						return;
					}
				 }
			}
			if(mon->base->y == kirito.base->y)
			{
				 if((mon->base->x - kirito.base->x) < 0)
				 {
					int i = mon->base->x;
					int wall = 0;
					for(; i < kirito.base->x; ++i)
					{
						if(aincrad.hardness[mon->base->y][i] != 0)
						{
							wall = 1;
							break;
						}
					}
					if(!wall)
					{
						// move right towards player
						//
						// TODO
						if(mon->attributes & INTELLIGENT)
						{
							mon->playerX = kirito.base->x;
							mon->playerY = kirito.base->y;
						}
						return;
					}
				 }
				 else
				 {
					int i = kirito.base->x;
					int wall = 0;
					for(; i < mon->base->x; ++i)
					{
						if(aincrad.hardness[mon->base->y][i] != 0)
						{
							wall = 1;
							break;
						}
					}
					if(!wall)
					{
						// move left towards player
						//
						// TODO
						if(mon->attributes & INTELLIGENT)
						{
							mon->playerX = kirito.base->x;
							mon->playerY = kirito.base->y;
						}
						return;
					}
				 }
			}
		}
	}
	// else bahave based on characteristics
	if((mon->attributes & ERRATIC) == 1)
	{
		int act = rand() % 100;
		if(act < 50)
		{
			moveRandom(mon->base, (mon->attributes & TUNNELING));
		}
		else
		{
			if((mon->attributes & INTELLIGENT) || (mon->attributes & TELEPATHIC))
				moveDeliberately(mon);
			else
				moveRandom(move->base, (mon->attributes & TUNNELING));
		}
	}
	else if((mon->attributes & INTELLIGENT) || (mon->attributes & TELEPATHIC))	
		moveDeliberately(mon);
	else
		moveRandom(mon->base, (mon->attributes & TUNNELING));
}
