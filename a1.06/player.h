#ifndef PLAYER_H
#define PLAYER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Player {} player;

void initializeVisible(player* p);

int** getVisible(player* p);

void setVisible(player* p);

#ifdef __cplusplus
}
#endif

#endif
