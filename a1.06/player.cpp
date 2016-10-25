#include "dungeon.h"
#include "character.h"

class Player : public Character
{
	int[Y][X] visible;
	public:
		int[][] getVisible() { return visible; }
		void setVisible(int x, int y);
		Player();
};

void setVisible(int x, int y)
{

}
