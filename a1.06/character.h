#ifndef CHARACTER_H
#define CHARACTER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Character {} character;

int getId(character* c);
char getSymbol(character* c);
char getX(character* c);
char getY(character* c);
char getSpeed(character* c);
int getTurn(character* c);
char getAlive(character* c);

void setId(character* c, int i);
void setSymbol(character* c, char s);
void setX(character* c, char s);
void setY(character* c, char s);
void setSpeed(character* c, char s);
void setTurn(character* c, int i);
void setAlive(character* c, char s);

#ifdef __cplusplus
}
#endif

#endif
