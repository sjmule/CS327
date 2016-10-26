#include "movement.h"
#include "routing.h"

int switchBoard(monster* mon, int playerX, int playerY)
{
	int x = getX((character*)mon) - playerX;
	int y = getY((character*)mon) - playerY;
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
	for(; i < aincrad.numRooms; ++i)
	{
		room temp = aincrad.rooms[i];
		if((x >= temp.x) && (x <= (temp.x + temp.width - 1)))
		{
			if((y >= temp.y) && (y <= (temp.y + temp.height - 1)))
				return i;
		}
	}
	return -1;
}

void killing(character* entity)
{
	if(getId(entity) != 0)
	{
		if((getX(entity) == getX((character*)&kirito)) && (getY(entity) == getY((character*)&kirito)))
			setAlive((character*)&kirito, 0);
	}
	else
	{
		int i = 0;
		for(; i < aincrad.numMonsters; ++i)
		{
			if(getId(entity) == getId((character*)&aincrad.monsters[i]))
				continue;
			else
			{
				if((getX(entity) == getX((character*)&aincrad.monsters[i])) && (getY(entity) == getY((character*)&aincrad.monsters[i])))
					setAlive((character*)&aincrad.monsters[i], 0);
			}
		}
	}
}

void makeTunnel(int x, int y)
{
	if(aincrad.map[y][x] == ' ')
		aincrad.map[y][x] = '#';
}

// 0 invalid move, 1 invalid move - recalculate distance, 2 valid move, 3 valid move - recalculate distance
int valid(int x, int y, int tunnel)
{
	if(tunnel == 4) // monster
	{
		if(aincrad.hardness[y][x] == 255)
			return 0;
		else
		{
			if(aincrad.hardness[y][x] == 0) // open space
				return 2;
			else if(aincrad.hardness[y][x] - 85 <= 0) // after digging will be open
				return 3;
			else // dig
			{
				aincrad.hardness[y][x] = aincrad.hardness[y][x] - 85;
				return 1;
			}
		}
	}
	else
	{
		if(aincrad.hardness[y][x] == 0)
			return 2;
		else
			return 0;
	}
}

int isMoveValid(character* entity, int dir, int tunnel)
{
	int x = getX(entity);
	int y = getY(entity);

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

void doMove(character* entity, int dir)
{
	makeTunnel(getX(entity), getY(entity));
	switch(dir)
	{
		case 0:
			setX(entity, getX(entity) - 1);
			setY(entity, getY(entity) - 1);
			break;
		case 1:
			setY(entity, getY(entity) - 1);
			break;
		case 2:
			setX(entity, getX(entity) + 1);
			setY(entity, getY(entity) - 1);
			break;
		case 3:
			setX(entity, getX(entity) + 1);
			break;
		case 4:
			setX(entity, getX(entity) + 1);
			setY(entity, getY(entity) + 1);
			break;
		case 5:
			setY(entity, getY(entity) + 1);
			break;
		case 6:
			setX(entity, getX(entity) - 1);
			setY(entity, getY(entity) + 1);
			break;
		case 7:
			setX(entity, getX(entity) - 1);
			break;
		default:
			break;
	}
	aincrad.hardness[(int)getY(entity)][(int)getX(entity)] = 0;
	killing((character*)entity);
}

void moveRandom(monster* entity, int tunnel)
{
	int valid = 0;
	int dir = rand() % 8;
	valid = isMoveValid((character*)entity, dir, tunnel);
	if(valid > 1)
	{
		doMove((character*)entity, dir);
		if(valid == 3)
		{
			calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 0);
			calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 1);
		}
	}
	if(valid == 1)
	{
		calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 0);
		calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 1);
	}
}

void moveDeliberately(monster* mon)
{
	if(getAttributes(mon) & TELEPATHIC) // is telepathic
	{
		setPlayerX(mon, getX((character*)&kirito));
		setPlayerY(mon, getY((character*)&kirito));
		if(getAttributes(mon) & INTELLIGENT) // is intelligent
		{
			int dir = shortestPath(getX((character*)mon), getY((character*)mon), (getAttributes(mon) & TUNNELING));
			int valid = isMoveValid((character*)mon, dir, (getAttributes(mon) & TUNNELING));
			if(valid > 1)
			{
				doMove((character*)mon, dir);
				if(valid == 3)
				{
					calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 0);
					calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 1);
				}
			}
			if(valid == 1)
			{
				calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 0);
				calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 1);
			}
		}
		else // is not intelligent
		{
			int dir = switchBoard(mon, getPlayerX(mon), getPlayerY(mon));
			int valid = isMoveValid((character*)mon, dir, (getAttributes(mon) & TUNNELING));
			if(valid > 1)
			{
				doMove((character*)mon, dir);
				if(valid == 3)
				{
					calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 0);
					calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 1);
				}
			}
			if(valid == 1)
			{
				calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 0);
				calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 1);
			}
		}
	}
	else // is not telepathic
	{
		if(getPlayerX(mon) != 0)
		{
			int dir = shortestPath(getX((character*)mon), getY((character*)mon), (getAttributes(mon) & TUNNELING));
			int valid = isMoveValid((character*)mon, dir, (getAttributes(mon) & TUNNELING));
			if(valid > 1)
			{
				doMove((character*)mon, dir);
				if(valid == 3)
				{
					calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 0);
					calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 1);
				}
			}
			if(valid == 1)
			{
				calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 0);
				calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 1);
			}
			if((getX((character*)mon) == getPlayerX(mon)) && (getY((character*)mon) == getPlayerY(mon)))
			{
				setPlayerX(mon, 0);
				setPlayerY(mon, 0);
			}
		}
		else
		{
			moveRandom(mon, (getAttributes(mon) & TUNNELING));
		}
	}
}

void moveMonster(monster* mon)
{
	setTurn((character*)mon, getTurn((character*)mon) + (100/getSpeed((character*)mon)));
	// if we can see the PC, move towards him
	int playerRoom = inRoom(getX((character*)&kirito), getY((character*)&kirito));
	if((playerRoom >=0) && (inRoom(getX((character*)mon), getY((character*)mon)) == playerRoom))
	{
		int dir = switchBoard(mon, getX((character*)&kirito), getY((character*)&kirito));
		int valid = isMoveValid((character*)mon, dir, (getAttributes(mon) & TUNNELING));
		if(valid > 1)
		{
			doMove((character*)mon, dir);
			if(valid == 3)
			{
				calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 0);
					calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 1);
				}
			}
			if(valid == 1)
			{
				calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 0);
				calculateDistances(getX((character*)&kirito), getY((character*)&kirito), 1);
		}
		if(getAttributes(mon) & INTELLIGENT)
		{
			getPlayerX(mon) = getX((character*)&kirito);
			getPlayerY(mon) = getY((character*)&kirito);
		}
		return;
	}
	else
	{
		if(getX((character*)mon) == getX((character*)&kirito)) // player is above or below monster
		{
			if((getY((character*)mon) - getY((character*)&kirito)) < 0) // monster is above player
			{
				int i = getY((character*)mon);
				int wall = 0;
				for(; i < getY((character*)&kirito); ++i)
				{
					if(aincrad.hardness[i][(int)getX((character*)mon)] != 0)
					{
						wall = 1;
						break;
					}
				}
				if(!wall)
				{
					doMove((character*)mon, 5);
					if(getAttributes(mon) & INTELLIGENT)
					{
						setPlayerX(mon, getX((character*)&kirito));
						setPlayerY(mon, getY((character*)&kirito));
					}
					return;
				}
			}
			else // monster is below player
			{
				int i = getY((character*)&kirito);
				int wall = 0;
				for(; i < getY((character*)mon); ++i)
				{
					if(aincrad.hardness[i][(int)getX((character*)mon)] != 0)
					{
						wall = 1;
						break;
					}
				}
				if(!wall)
				{
					doMove((character*)mon, 1);
					if(getAttributes(mon) & INTELLIGENT)
					{
						setPlayerX(mon, getX((character*)&kirito));
						setPlayerY(mon, getY((character*)&kirito));
					}
					return;
				}
			}
		}
		if(getY((character*)mon) == getY((character*)&kirito)) // player is to left or right of monster
		{
			if((getX((character*)mon) - getX((character*)&kirito)) < 0) // monster is to left of player
			{
				int i = getX((character*)mon);
				int wall = 0;
				for(; i < getX((character*)&kirito); ++i)
				{
					if(aincrad.hardness[(int)getY((character*)mon)][i] != 0)
					{
						wall = 1;
						break;
					}
				}
				if(!wall)
				{
					doMove((character*)mon, 3);
					if(getAttributes(mon) & INTELLIGENT)
					{
						setPlayerX(mon, getX((character*)&kirito));
						setPlayerY(mon, getY((character*)&kirito));
					}
					return;
				}
			}
			else // monster is to right of player
			{
				int i = getX((character*)&kirito);
				int wall = 0;
				for(; i < getX((character*)mon); ++i)
				{
					if(aincrad.hardness[(int)getY((character*)mon)][i] != 0)
					{
						wall = 1;
						break;
					}
				}
				if(!wall)
				{
					doMove((character*)mon, 7);
					if(getAttributes(mon) & INTELLIGENT)
					{
						setPlayerX(mon, getX((character*)&kirito));
						setPlayerY(mon, getY((character*)&kirito));
					}
					return;
				}
			}
		}
	}
	// else behave based on characteristics
	if((getAttributes(mon) & ERRATIC) == 1)
	{
		int act = rand() % 100;
		if(act < 50)
		{
			moveRandom(mon, (getAttributes(mon) & TUNNELING));
		}
		else
		{
			if((getAttributes(mon) & INTELLIGENT) || (getAttributes(mon) & TELEPATHIC))
				moveDeliberately(mon);
			else
				moveRandom(mon, (getAttributes(mon) & TUNNELING));
		}
	}
	else if((getAttributes(mon) & INTELLIGENT) || (getAttributes(mon) & TELEPATHIC))
		moveDeliberately(mon);
	else
		moveRandom(mon, (getAttributes(mon) & TUNNELING));
}
