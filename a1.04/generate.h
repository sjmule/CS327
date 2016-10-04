#ifndef GENERATE_H
#define GENERATE_H

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

#endif
