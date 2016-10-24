#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "dungeon.h"

extern int ncurse;

int switchBoard(monster* mon, int playerX, int playerY);

int inRoom(int x, int y);

void makeTunnel(int x, int y);

int valid(entity entity, int tunnel);

int isMoveValid(entity* character, int dir, int tunnel);

void doMove(entity* character, int dir);

void moveRandom(entity* character, int tunnel);

void moveDeliberately(monster* mon);

void moveMonster(monster* mon);

#endif
