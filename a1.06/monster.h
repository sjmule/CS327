#ifndef MONSTER_H
#define MONSTER_H

#ifdef __cplusplus
extern "C" {
#endif

int getAttributes();
char getPlayerX();
char getPlayerY();

void setAttributes(int i);
void setPlayerX(char c);
void setPlayerY(char c);

#ifdef __cplusplus
}
#endif

#endif
