#ifndef PLAYER_H
#define PLAYER_H

class Player : public Character
{
	public:
		int** visible;

		void initializeVisible();

		void setVisible();

		void clearVisible();
};

#endif
