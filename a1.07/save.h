#ifndef SAVE_H
#define SAVE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dungeon.h"
#include "generate.h"

#define _itos(x,y) ((x >> y) & 0xFF)
#define _stoi(x) (x[3] << 24) | (x[2] << 16) | (x[1] << 8) | (x[0])

extern unsigned int version;

void saveDungeon(char* path, int debug);

void loadDungeon(char* path, int debug);

#ifdef __cplusplus
}
#endif

#endif
