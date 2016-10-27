#include "character.h"
#include "dungeon.h"

// Getters
int getId(character* c) { return ((Character*) c)->id; }
char getSymbol(character* c) { return ((Character*) c)->symbol; }
char getX(character* c) { return ((Character*) c)->x; }
char getY(character* c) { return ((Character*) c)->y; }
char getSpeed(character* c) { return ((Character*) c)->speed; }
int getTurn(character* c) { return ((Character*) c)->turn; }
char getAlive(character* c) { return ((Character*) c)->alive; }

// Setters
void setId(character* c, int i) { ((Character*) c)->id = i; }
void setSymbol(character* c, char s) { ((Character*) c)->symbol = s; }
void setX(character* c, char s) { ((Character*) c)->x = s; }
void setY(character* c, char s) { ((Character*) c)->y = s; }
void setSpeed(character* c, char s) { ((Character*) c)->speed = s; }
void setTurn(character* c, int i) { ((Character*) c)->turn = i; }
void setAlive(character* c, char s) { ((Character*) c)->alive = s; }
