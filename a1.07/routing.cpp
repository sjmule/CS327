#include "routing.h"

int hardnessCost(int y, int x)
{
	if(aincrad.hardness[y][x] >= 0 && aincrad.hardness[y][x] <= 84)
		return 1;
	if(aincrad.hardness[y][x] >= 85 && aincrad.hardness[y][x] <= 170)
		return 2;
	if(aincrad.hardness[y][x] >= 171 && aincrad.hardness[y][x] <= 254)
		return 3;
	else
		return INT_MAX;
}

int32_t path_cmp(const void* key, const void* with)
{
	return ((route *) key)->cost - ((route *) with)->cost;
}

void calculateDistances(int playerX, int playerY, int tunnel)
{
	static route path[Y][X], *p;
	static int initialized = 0;
	heap_t h;
	int x, y;

	if(!initialized)
	{
		for(y = 0; y < Y; ++y)
		{
			for(x = 0; x < X; ++x)
			{
				openCost[y][x] = INT_MAX;
				allCost[y][x] = INT_MAX;
				openCost[playerY][playerX] = 0;
				allCost[playerY][playerX] = 0;
			}
		}
		initialized = 1;
	}

	for(y = 0; y < Y; ++y)
	{
		for(x = 0; x < X; ++x)
		{
			path[y][x].cost = INT_MAX;
			path[y][x].posY = y;
			path[y][x].posX = x;
		}
	}

	path[playerY][playerX].cost = 0;

	heap_init(&h, path_cmp, NULL);

	for(y = 0; y < Y; ++y)
	{
		for(x = 0; x < X; ++x)
		{
			if(!tunnel)
			{
				if(aincrad.hardness[y][x] == 0)
					path[y][x].hn = heap_insert(&h, &path[y][x]);
				else
					path[y][x].hn = NULL;
			}
			else
			{
				if(aincrad.hardness[y][x] == 255)
					path[y][x].hn = NULL;
				else
					path[y][x].hn = heap_insert(&h, &path[y][x]);
			}
		}
	}

	while((p = (route*) heap_remove_min(&h)))
	{
		p->hn = NULL;
		if((path[p->posY - 1][p->posX - 1].hn) && (path[p->posY - 1][p->posX - 1].cost > p->cost + hardnessCost(p->posY - 1, p->posX - 1)))
		{
			path[p->posY - 1][p->posX - 1].cost = p->cost + hardnessCost(p->posY - 1, p->posX - 1);
			if(!tunnel)
				openCost[p->posY - 1][p->posX - 1] = p->cost + hardnessCost(p->posY - 1, p->posX - 1);
			else
				allCost[p->posY - 1][p->posX - 1] = p->cost + hardnessCost(p->posY - 1, p->posX - 1);
			path[p->posY - 1][p->posX - 1].fromY = p->posY;
			path[p->posY - 1][p->posX - 1].fromX = p->posX;
			heap_decrease_key_no_replace(&h, path[p->posY - 1][p->posX - 1].hn);
		}
		if((path[p->posY - 1][p->posX    ].hn) && (path[p->posY - 1][p->posX    ].cost > p->cost + hardnessCost(p->posY - 1, p->posX)))
		{
			path[p->posY - 1][p->posX    ].cost = p->cost + hardnessCost(p->posY - 1, p->posX);
			if(!tunnel)
				openCost[p->posY - 1][p->posX    ] = p->cost + hardnessCost(p->posY - 1, p->posX);
			else
				allCost[p->posY - 1][p->posX    ] = p->cost + hardnessCost(p->posY - 1, p->posX);
			path[p->posY - 1][p->posX    ].fromY = p->posY;
			path[p->posY - 1][p->posX    ].fromX = p->posX;
			heap_decrease_key_no_replace(&h, path[p->posY - 1][p->posX    ].hn);
		}
		if((path[p->posY - 1][p->posX + 1].hn) && (path[p->posY - 1][p->posX + 1].cost > p->cost + hardnessCost(p->posY - 1, p->posX + 1)))
		{
			path[p->posY - 1][p->posX + 1].cost = p->cost + hardnessCost(p->posY - 1, p->posX + 1);
			if(!tunnel)
				openCost[p->posY - 1][p->posX + 1] = p->cost + hardnessCost(p->posY - 1, p->posX + 1);
			else
				allCost[p->posY - 1][p->posX + 1] = p->cost + hardnessCost(p->posY - 1, p->posX + 1);
			path[p->posY - 1][p->posX + 1].fromY = p->posY;
			path[p->posY - 1][p->posX + 1].fromX = p->posX;
			heap_decrease_key_no_replace(&h, path[p->posY - 1][p->posX + 1].hn);
		}
		if((path[p->posY    ][p->posX - 1].hn) && (path[p->posY    ][p->posX - 1].cost > p->cost + hardnessCost(p->posY, p->posX - 1)))
		{
			path[p->posY    ][p->posX - 1].cost = p->cost + hardnessCost(p->posY, p->posX - 1);
			if(!tunnel)
				openCost[p->posY    ][p->posX - 1] = p->cost + hardnessCost(p->posY, p->posX - 1);
			else
				allCost[p->posY    ][p->posX - 1] = p->cost + hardnessCost(p->posY, p->posX - 1);
			path[p->posY    ][p->posX - 1].fromY = p->posY;
			path[p->posY    ][p->posX - 1].fromX = p->posX;
			heap_decrease_key_no_replace(&h, path[p->posY    ][p->posX - 1].hn);
		}
		if((path[p->posY    ][p->posX + 1].hn) && (path[p->posY    ][p->posX + 1].cost > p->cost + hardnessCost(p->posY, p->posX + 1)))
		{
			path[p->posY    ][p->posX + 1].cost = p->cost + hardnessCost(p->posY, p->posX + 1);
			if(!tunnel)
				openCost[p->posY    ][p->posX + 1] = p->cost + hardnessCost(p->posY, p->posX + 1);
			else
				allCost[p->posY    ][p->posX + 1] = p->cost + hardnessCost(p->posY, p->posX + 1);
			path[p->posY    ][p->posX + 1].fromY = p->posY;
			path[p->posY    ][p->posX + 1].fromX = p->posX;
			heap_decrease_key_no_replace(&h, path[p->posY    ][p->posX + 1].hn);
		}
		if((path[p->posY + 1][p->posX - 1].hn) && (path[p->posY + 1][p->posX - 1].cost > p->cost + hardnessCost(p->posY + 1, p->posX - 1)))
		{
			path[p->posY + 1][p->posX - 1].cost = p->cost + hardnessCost(p->posY + 1, p->posX - 1);
			if(!tunnel)
				openCost[p->posY + 1][p->posX - 1] = p->cost + hardnessCost(p->posY + 1, p->posX - 1);
			else
				allCost[p->posY + 1][p->posX - 1] = p->cost + hardnessCost(p->posY + 1, p->posX - 1);
			path[p->posY + 1][p->posX - 1].fromY = p->posY;
			path[p->posY + 1][p->posX - 1].fromX = p->posX;
			heap_decrease_key_no_replace(&h, path[p->posY + 1][p->posX - 1].hn);
		}
		if((path[p->posY + 1][p->posX    ].hn) && (path[p->posY + 1][p->posX    ].cost > p->cost + hardnessCost(p->posY + 1, p->posX)))
		{
			path[p->posY + 1][p->posX    ].cost = p->cost + hardnessCost(p->posY + 1, p->posX);
			if(!tunnel)
				openCost[p->posY + 1][p->posX    ] = p->cost + hardnessCost(p->posY + 1, p->posX);
			else
				allCost[p->posY + 1][p->posX    ] = p->cost + hardnessCost(p->posY + 1, p->posX);
			path[p->posY + 1][p->posX    ].fromY = p->posY;
			path[p->posY + 1][p->posX    ].fromX = p->posX;
			heap_decrease_key_no_replace(&h, path[p->posY + 1][p->posX    ].hn);
		}
		if((path[p->posY + 1][p->posX + 1].hn) && (path[p->posY + 1][p->posX + 1].cost > p->cost + hardnessCost(p->posY + 1, p->posX + 1)))
		{
			path[p->posY + 1][p->posX + 1].cost = p->cost + hardnessCost(p->posY + 1, p->posX + 1);
			if(!tunnel)
				openCost[p->posY + 1][p->posX + 1] = p->cost + hardnessCost(p->posY + 1, p->posX + 1);
			else
				allCost[p->posY + 1][p->posX + 1] = p->cost + hardnessCost(p->posY + 1, p->posX + 1);
			path[p->posY + 1][p->posX + 1].fromY = p->posY;
			path[p->posY + 1][p->posX + 1].fromX = p->posX;
			heap_decrease_key_no_replace(&h, path[p->posY + 1][p->posX + 1].hn);
		}
	}

	heap_delete(&h);
}

int shortestPath(int fromX, int fromY, int tunnel)
{
	if(tunnel)
	{
		int min = INT_MAX;
		int dir = 8;
		if(allCost[fromY-1][fromX-1] < min)
		{
			min = allCost[fromY-1][fromX-1];
			dir = 0;
		}
		if(allCost[fromY-1][fromX] < min)
		{
			min = allCost[fromY-1][fromX];
			dir = 1;
		}
		if(allCost[fromY-1][fromX+1] < min)
		{
			min = allCost[fromY-1][fromX+1];
			dir = 2;
		}
		if(allCost[fromY][fromX+1] < min)
		{
			min = allCost[fromY][fromX+1];
			dir = 3;
		}
		if(allCost[fromY+1][fromX+1] < min)
		{
			min = allCost[fromY+1][fromX+1];
			dir = 4;
		}
		if(allCost[fromY+1][fromX] < min)
		{
			min = allCost[fromY+1][fromX];
			dir = 5;
		}
		if(allCost[fromY+1][fromX-1] < min)
		{
			min = allCost[fromY+1][fromX-1];
			dir = 6;
		}
		if(allCost[fromY][fromX-1] < min)
		{
			min = allCost[fromY][fromX-1];
			dir = 7;
		}
		return dir;
	}
	else
	{
		int min = INT_MAX;
		int dir = 8;
		if(openCost[fromY-1][fromX-1] < min)
		{
			min = openCost[fromY-1][fromX-1];
			dir = 0;
		}
		if(openCost[fromY-1][fromX] < min)
		{
			min = openCost[fromY-1][fromX];
			dir = 1;
		}
		if(openCost[fromY-1][fromX+1] < min)
		{
			min = openCost[fromY-1][fromX+1];
			dir = 2;
		}
		if(openCost[fromY][fromX+1] < min)
		{
			min = openCost[fromY][fromX+1];
			dir = 3;
		}
		if(openCost[fromY+1][fromX+1] < min)
		{
			min = openCost[fromY+1][fromX+1];
			dir = 4;
		}
		if(openCost[fromY+1][fromX] < min)
		{
			min = openCost[fromY+1][fromX];
			dir = 5;
		}
		if(openCost[fromY+1][fromX-1] < min)
		{
			min = openCost[fromY+1][fromX-1];
			dir = 6;
		}
		if(openCost[fromY][fromX-1] < min)
		{
			min = openCost[fromY][fromX-1];
			dir = 7;
		}
		return dir;
	}
}

char distToChar(int dist)
{
	if((dist >= 0) && (dist <= 9))
		return (char) 48 + dist;
	if((dist >= 10) && (dist <= 35))
		return (char) 97 + (dist - 10);
	if((dist >= 36) && (dist <= 61))
		return (char) 65 + (dist - 36);
	else
		return (char) 21;
}

void printCosts()
{
	int i = 0;
	for(; i < Y; ++i)
	{
		int j = 0;
		for(; j < X; ++j)
		{
			if(openCost[i][j] != INT_MAX)
			{
				char c = distToChar(openCost[i][j]);
				if(c != 21)
					printf("%c", c);
				else
					printf("%c", aincrad.map[i][j]);
			}
			else
				printf("%c", aincrad.map[i][j]);
		}
		printf("\n");
	}

	for(i = 0; i < Y; ++i)
	{
		int j = 0;
		for(; j < X; ++j)
		{
			if(allCost[i][j] != INT_MAX)
			{
				char c = distToChar(allCost[i][j]);
				if(c != 21)
					printf("%c", c);
				else
					printf("%c", aincrad.map[i][j]);
			}
			else
				printf("%c", aincrad.map[i][j]);
		}
		printf("\n");
	}

}
