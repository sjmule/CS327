#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "dungeon.h"

int switchBoard(monster* mon, int playerX, int playerY);

int inRoom(int x, int y);

void makeTunnel(int x, int y);

int valid(int x, int y, int tunnel);

int isMoveValid(Character* entity, int dir, int tunnel);

void doMove(Character* entity, int dir);

void moveRandom(Monster* character, int tunnel);

void moveDeliberately(Monster* mon);

void moveMonster(Monster* mon);

#endif
