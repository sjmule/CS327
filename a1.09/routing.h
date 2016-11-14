#ifndef ROUTING_H
#define ROUTING_H

#include "dungeon.h"
#include "heap.h"

typedef struct ROUTE route;

struct ROUTE
{
	heap_node_t *hn;
	int posX;
	int posY;
	int fromX;
	int fromY;
	int cost;
};

extern int openCost[Y][X];
extern int allCost[Y][X];

int hardnessCost(int y, int x);

int32_t path_cmp(const void* key, const void* with);

void calculateDistances(int playerX, int playerY, int tunnel);

int shortestPath(int toX, int toY, int tunnel);

char distToChar(int dist);

void printCosts();

#endif
