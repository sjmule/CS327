#include "pqueue.h"

void queueInit(pqueue* q, int size)
{
	printf("initializing queue\n");
	q->queue = malloc(size * sizeof(entity*));
	q->size = size;
	int i = 0;
	for(; i < size; ++i)
	{
		q->queue[i] = NULL;
	}
	printf("set to null\n");
}

void pqInsert(pqueue* q, entity* character)
{
	if(q->queue[0] == NULL)
	{
		q->queue[0] = character;
		return;
	}
	else
	{
		int i = 0;
		for(; i < q->size; ++i)
		{
			if(q->queue[i] == NULL)
				break;
			if(character->turn <= q->queue[i]->turn)
			{
				if(q->queue[i]->symbol == '@')
					++i;
				break;
			}
		}
		entity* temp = character;
		entity* temp2 = NULL;
		for(; i < q->size; ++i)
		{
			temp2 = q->queue[i];
			q->queue[i] = temp;
			temp = temp2;
		}
	}
}

entity* removeMin(pqueue* q)
{
	entity* toReturn = q->queue[0];
	entity* temp = NULL;
	int i = 1;
	for(; i < q->size; ++i)
	{
		q->queue[i-1] = q->queue[i];
	}
	q->queue[i-1] = NULL;
	return toReturn;
}
