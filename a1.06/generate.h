#ifndef GENERATE_H
#define GENERATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dungeon.h"

void setImmutable();

void setHardness();

void setBoundary();

void initializeDungeon();

room generateRoom();

int verifyValidity(room room, int x, int y);

void placeRoom(room room, int x, int y);

void createRooms();

void connectRooms();

#ifdef __cplusplus
}
#endif

#endif
