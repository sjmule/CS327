#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "dungeon.h"

Character* checkForOthers(Character* entity, int dir);

int isMoveValid(Character* entity, int dir, int tunnel);

void doMove(Character* entity, int dir);

void combat(Character* attack, Character* defense);

void moveMonster(Monster* mon);

#endif
