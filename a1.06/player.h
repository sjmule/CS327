#ifndef PLAYER_H
#define PLAYER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {} player;

void createPlayer();

void initializeVisible(player* p);

int** getVisible(player* p);

void setVisible(player* p);

void clearVisible(player* p);

void cleanupPlayer();

#ifdef __cplusplus
class Player : public Character
{
  public:
	  int** visible;
};
}
#endif

#endif
