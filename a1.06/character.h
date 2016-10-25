#ifndef CHARACTER_H
#define CHARACTER_H

#ifdef __cplusplus
extern "C" {
#endif

int getId();
char getSymbol();
char getX();
char getY();
char getSpeed();
int getTurn();
char getAlive();

void setId(int i);
void setSymbol(char c);
void setX(char c);
void setY(char c);
void setSpeed(char c);
void setTurn(int i);
void setAlive(char c);

#ifdef __cplusplus
}
#endif

#endif
