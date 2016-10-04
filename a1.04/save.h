#ifndef SAVE_H
#define SAVE_H

#include "dungeon.h"
#include "generate.h"

#define _itos(x,y) ((x >> y) & 0xFF)
#define _stoi(x) (x[3] << 24) | (x[2] << 16) | (x[1] << 8) | (x[0])

unsigned int version;

FILE* file;

void saveDungeon(char* path, int debug);

void loadDungeon(char* path, int debug);

#endif
