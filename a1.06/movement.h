#ifndef MOVEMENT_H
#define MOVEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dungeon.h"

extern int ncurse;

int switchBoard(monster* mon, int playerX, int playerY);

int inRoom(int x, int y);

void makeTunnel(int x, int y);

int valid(int x, int y, int tunnel);

int isMoveValid(character* entity, int dir, int tunnel);

void doMove(character* entity, int dir);

void moveRandom(monster* character, int tunnel);

void moveDeliberately(monster* mon);

void moveMonster(monster* mon);

#ifdef __cplusplus
}
#endif

#endif
