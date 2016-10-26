#include "movement.h"
#include "routing.h"

int switchBoard(monster* mon, int playerX, int playerY)
{
	int x = mon->getX() - playerX;
	int y = mon->getY() - playerY;
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

void killing(monster* enity)
{
	if(entity->id != 0)
	{
		if((entity.getX() == kirito.getX()) && (entity.getY() == kirito.getY()))
			kirito.getAlive() = 0;
	}
	else
	{
		int i = 0;
		for(; i < aincrad.numMonsters; ++i)
		{
			if(entity.getId() == aincrad.monsters[i].getId())
				continue;
			else
			{
				if((entity.getX() == aincrad.monsters[i].getX()) && (entity.getY() == aincrad.monsters[i].getY()))
					aincrad.monsters[i].getAlive() = 0;
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

int isMoveValidMonster(monster* entity, int dir, int tunnel)
{
	int x = entity.getX();
	int y = entity.getY();

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

int isMoveValid(player* entity, int dir)
{
	int x = entity.getX();
	int y = entity.getY();

	switch(dir)
	{
		case 0:
			x--;
			y--;
			return valid(x, y, 0);
		case 1:
			y--;
			return valid(x, y, 0);
		case 2:
			x++;
			y--;
			return valid(x, y, 0);
		case 3:
			x++;
			return valid(x, y, 0);
		case 4:
			x++;
			y++;
			return valid(x, y, 0);
		case 5:
			y++;
			return valid(x, y, 0);
		case 6:
			x--;
			y++;
			return valid(x, y, 0);
		case 7:
			x--;
			return valid(x, y, 0);
		default:
			return 0;
	}
}

void doMoveMonster(monster* entity, int dir)
{
	makeTunnel(entity.getX(), entity.getY());
	switch(dir)
	{
		case 0:
			entity.setX(entity.getX()--);
			entity.setY(entity.getY()--);
			break;
		case 1:
			entity.setY(entity.getY()--);
			break;
		case 2:
			entity.setX(entity.getX()++);
			entity.setY(entity.getY()--);
			break;
		case 3:
			entity.setX(entity.getX()++);
			break;
		case 4:
			entity.setX(entity.getX()++);
			entity.setY(entity.getY()++);
			break;
		case 5:
			entity.setY(entity.getY()++);
			break;
		case 6:
			entity.setX(entity.getX()--);
			entity.setY(entity.getY()++);
			break;
		case 7:
			entity.setX(entity.getX()--);
			break;
		default:
			break;
	}
	aincrad.hardness[entity.getY()][entity.getX()] = 0;
	killing(entity);
}

void doMove(player* entity, int dir)
{
	makeTunnel(entity.getX(), entity.getY());
	switch(dir)
	{
		case 0:
			entity.setX(entity.getX()--);
			entity.setY(entity.getY()--);
			break;
		case 1:
			entity.setY(entity.getY()--);
			break;
		case 2:
			entity.setX(entity.getX()++);
			entity.setY(entity.getY()--);
			break;
		case 3:
			entity.setX(entity.getX()++);
			break;
		case 4:
			entity.setX(entity.getX()++);
			entity.setY(entity.getY()++);
			break;
		case 5:
			entity.setY(entity.getY()++);
			break;
		case 6:
			entity.setX(entity.getX()--);
			entity.setY(entity.getY()++);
			break;
		case 7:
			entity.setX(entity.getX()--);
			break;
		default:
			break;
	}
	aincrad.hardness[entity.getY()][entity.getX()] = 0;
	killing(entity);
}

void moveRandom(monster* entity, int tunnel)
{
	int valid = 0;
	int dir = rand() % 8;
	valid = isMoveValidMonster(entity, dir, tunnel);
	if(valid > 1)
	{
		doMoveMonster(entity, dir);
		if(valid == 3)
		{
			calculateDistances(kirito.getX(), kirito.getY(), 0);
			calculateDistances(kirito.getX(), kirito.getY(), 1);
		}
	}
	if(valid == 1)
	{
		calculateDistances(kirito.getX(), kirito.getY(), 0);
		calculateDistances(kirito.getX(), kirito.getY(), 1);
	}
}

void moveDeliberately(monster* mon)
{
	if(mon->getAttributes() & TELEPATHIC) // is telepathic
	{
		mon->getPlayerX() = kirito.getX();
		mon->getPlayerY() = kirito.getY();
		if(mon->getAttributes() & INTELLIGENT) // is intelligent
		{
			int dir = shortestPath(mon->getX(), mon->getY(), (mon->getAttributes() & TUNNELING));
			int valid = isMoveValidMonster(mon, dir, (mon->getAttributes() & TUNNELING));
			if(valid > 1)
			{
				doMoveMonster(mon, dir);
				if(valid == 3)
				{
					calculateDistances(kirito.getX(), kirito.getY(), 0);
					calculateDistances(kirito.getX(), kirito.getY(), 1);
				}
			}
			if(valid == 1)
			{
				calculateDistances(kirito.getX(), kirito.getY(), 0);
				calculateDistances(kirito.getX(), kirito.getY(), 1);
			}
		}
		else // is not intelligent
		{
			int dir = switchBoard(mon, mon->getPlayerX(), mon->getPlayerY());
			int valid = isMoveValidMonster(mon, dir, (mon->getAttributes() & TUNNELING));
			if(valid > 1)
			{
				doMoveMonster(mon, dir);
				if(valid == 3)
				{
					calculateDistances(kirito.getX(), kirito.getY(), 0);
					calculateDistances(kirito.getX(), kirito.getY(), 1);
				}
			}
			if(valid == 1)
			{
				calculateDistances(kirito.getX(), kirito.getY(), 0);
				calculateDistances(kirito.getX(), kirito.getY(), 1);
			}
		}
	}
	else // is not telepathic
	{
		if(mon->getPlayerX() != 0)
		{
			int dir = shortestPath(mon->getX(), mon->getY(), (mon->getAttributes() & TUNNELING));
			int valid = isMoveValidMonster(mon, dir, (mon->getAttributes() & TUNNELING));
			if(valid > 1)
			{
				doMoveMonster(mon, dir);
				if(valid == 3)
				{
					calculateDistances(kirito.getX(), kirito.getY(), 0);
					calculateDistances(kirito.getX(), kirito.getY(), 1);
				}
			}
			if(valid == 1)
			{
				calculateDistances(kirito.getX(), kirito.getY(), 0);
				calculateDistances(kirito.getX(), kirito.getY(), 1);
			}
			if((mon->getX() == mon->getPlayerX()) && (mon->getY() == mon->getPlayerY()))
			{
				mon->getPlayerX() = 0;
				mon->getPlayerY() = 0;
			}
		}
		else
		{
			moveRandom(mon, (mon->getAttributes() & TUNNELING));
		}
	}
}

void moveMonster(monster* mon)
{
	mon->setTurn(mon->getTurn() + (100/mon->getSpeed()));
	// if we can see the PC, move towards him
	int playerRoom = inRoom(kirito.getX(), kirito.getY());
	if((playerRoom >=0) && (inRoom(mon->getX(), mon->getY()) == playerRoom))
	{
		int dir = switchBoard(mon, kirito.getX(), kirito.getY());
		int valid = isMoveValidMonster(mon, dir, (mon->getAttributes() & TUNNELING));
		if(valid > 1)
		{
			doMoveMonster(mon, dir);
			if(valid == 3)
			{
				calculateDistances(kirito.getX(), kirito.getY(), 0);
				calculateDistances(kirito.getX(), kirito.getY(), 1);
			}
		}
		if(valid == 1)
		{
			calculateDistances(kirito.getX(), kirito.getY(), 0);
			calculateDistances(kirito.getX(), kirito.getY(), 1);
		}
		if(mon->getAttributes() & INTELLIGENT)
		{
			mon->getPlayerX() = kirito.getX();
			mon->getPlayerY() = kirito.getY();
		}
		return;
	}
	else
	{
		if(mon->getX() == kirito.getX()) // player is above or below monster
		{
			if((mon->getY() - kirito.getY()) < 0) // monster is above player
			{
				int i = mon->getY();
				int wall = 0;
				for(; i < kirito.getY(); ++i)
				{
					if(aincrad.hardness[i][mon->getX()] != 0)
					{
						wall = 1;
						break;
					}
				}
				if(!wall)
				{
					doMoveMonster(mon, 5);
					if(mon->getAttributes() & INTELLIGENT)
					{
						mon->getPlayerX() = kirito.getX();
						mon->getPlayerY() = kirito.getY();
					}
					return;
				}
			}
			else // monster is below player
			{
				int i = kirito.getY();
				int wall = 0;
				for(; i < mon->getY(); ++i)
				{
					if(aincrad.hardness[i][mon->getX()] != 0)
					{
						wall = 1;
						break;
					}
				}
				if(!wall)
				{
					doMoveMonster(mon, 1);
					if(mon->getAttributes() & INTELLIGENT)
					{
						mon->getPlayerX() = kirito.getX();
						mon->getPlayerY() = kirito.getY();
					}
					return;
				}
			}
		}
		if(mon->getY() == kirito.getY()) // player is to left or right of monster
		{
			if((mon->getX() - kirito.getX()) < 0) // monster is to left of player
			{
				int i = mon->getX();
				int wall = 0;
				for(; i < kirito.getX(); ++i)
				{
					if(aincrad.hardness[mon->getY()][i] != 0)
					{
						wall = 1;
						break;
					}
				}
				if(!wall)
				{
					doMoveMonster(mon, 3);
					if(mon->getAttributes() & INTELLIGENT)
					{
						mon->getPlayerX() = kirito.getX();
						mon->getPlayerY() = kirito.getY();
					}
					return;
				}
			}
			else // monster is to right of player
			{
				int i = kirito.getX();
				int wall = 0;
				for(; i < mon->getX(); ++i)
				{
					if(aincrad.hardness[mon->getY()][i] != 0)
					{
						wall = 1;
						break;
					}
				}
				if(!wall)
				{
					doMoveMonster(mon, 7);
					if(mon->getAttributes() & INTELLIGENT)
					{
						mon->getPlayerX() = kirito.getX();
						mon->getPlayerY() = kirito.getY();
					}
					return;
				}
			}
		}
	}
	// else behave based on characteristics
	if((mon->getAttributes() & ERRATIC) == 1)
	{
		int act = rand() % 100;
		if(act < 50)
		{
			moveRandom(mon, (mon->getAttributes() & TUNNELING));
		}
		else
		{
			if((mon->getAttributes() & INTELLIGENT) || (mon->getAttributes() & TELEPATHIC))
				moveDeliberately(mon);
			else
				moveRandom(mon, (mon->getAttributes() & TUNNELING));
		}
	}
	else if((mon->getAttributes() & INTELLIGENT) || (mon->getAttributes() & TELEPATHIC))
		moveDeliberately(mon);
	else
		moveRandom(mon, (mon->getAttributes() & TUNNELING));
}
