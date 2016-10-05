#ifndef ROUTING_H
#define ROUTING_H

#include "dungeon.h"
#include "binheap.h"

typedef struct ROUTE route;

struct ROUTE
{
	binheap_node_t *hn;
	int posX;
	int posY;
	int fromX;
	int fromY;
	int cost;
};

int openCost[Y][X];
int allCost[Y][X];

int hardnessCost(int y, int x);

int32_t path_cmp(const void* key, const void* with);

void calculateDistances(int playerX, int playerY, int tunnel);

char distToChar(int dist);

void printCosts();

#endif
