#ifndef SAVE_H
#define SAVE_H

#include "generate.h"

#define _itos(x,y) ((x >> y) & 0xFF)
#define _stoi(x) (x[3] << 24) | (x[2] << 16) | (x[1] << 8) | (x[0])

void saveDungeon(char* path);

void loadDungeon(char* path);

#endif
