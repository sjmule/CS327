#ifndef PQUEUE_H
#define PQUEUE_H

#include "dungeon.h"

typedef struct PQUEUE pqueue;

struct PQUEUE
{
	entity** queue;	
	int size;
};

void queueInit(pqueue* q, int size);

void pqInsert(pqueue* q, entity* character);

entity* removeMin(pqueue* q);

#endif