#ifndef MONSTER_H
#define MONSTER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Monster {} monster;

int getAttributes(monster* m);
char getPlayerX(monster* m);
char getPlayerY(monster* m);

void setAttributes(monster* m, int i);
void setPlayerX(monster* m, char c);
void setPlayerY(monster* m, char c);

#ifdef __cplusplus
}
#endif

#endif
