#ifndef MOVE_H
#define MOVE_H

#include "dungeon.h"

int switchBoard(monster* mon, int playerX, int playerY);

int inRoom(int x, int y);

void cleanCell(int x, int y);

int valid(entity entity, int tunnel);

int isMoveValid(entity* character, int dir, int tunnel);

void move(entity* character, int dir);

void moveRandom(entity* character, int tunnel);

void moveDeliberately(monster* mon);

void moveMonster(monster* mon);

#endif
