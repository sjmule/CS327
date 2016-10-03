#ifndef MONSTER_H
#define MONSTER_H

#include "generate.h"

#define INTELLIGENT 0x1
#define TELEPATHIC  0x2
#define TUNNELING   0x4
#define ERRATIC     0x8

typedef struct MONSTER monster;

struct MONSTER
{
	char symbol;
	int attributes;
	int x;
	int y;
	int speed;
};

#endif
