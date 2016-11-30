#include "dungeon.h"
#include "character.h"
#include "player.h"

void Player::initializeVisible()
{
	this->visible = new int*[Y];
	for(int i = 0; i < Y; ++i)
	{
		this->visible[i] = new int[X];
	}
	for(int i = 0; i < Y; ++i)
	{
		for(int j = 0; j < X; ++j)
		{
			this->visible[i][j] = ' ';
		}
	}
	for(int i = 0; i < X; ++i)
	{
		this->visible[0][i] = '-';
		this->visible[Y-1][i] = '-';
	}
	for(int i = 1; i < Y - 1; ++i)
	{
		this->visible[i][0] = '|';
		this->visible[i][X-1] = '|';
	}
}

void Player::setVisible()
{
	int i = this->y;
	for(int k = 0; k < 3; ++k)
	{
		if((i - 1) >= 1)
			i -= 1;
		else
			break;
	}
	int j = this->x;
	for(int k = 0; k < 3; ++k)
	{
		if((j - 1) >= 1)
			j -= 1;
		else
			break;
	}
	for(; i <= (this->y + 3) && i < Y; ++i)
	{
		for(int k = j; k <= (this->x + 3) && k < X; ++k)
		{
			this->visible[i][k] = aincrad->map[i][k];
		}
	}
}

void Player::clearVisible()
{
	for(int i = 0; i < Y; ++i)
	{
		for(int j = 0; j < X; ++j)
		{
			this->visible[i][j] = ' ';
		}
	}
	for(int i = 0; i < X; ++i)
	{
		this->visible[0][i] = '-';
		this->visible[Y-1][i] = '-';
	}
	for(int i = 1; i < Y - 1; ++i)
	{
		this->visible[i][0] = '|';
		this->visible[i][X-1] = '|';
	}
}

Player::Player()
{
	this->id = 0;
	this->symbol = '@';
	this->speed = 10;
	this->turn = 0;
	this->alive = 1;
	this->initializeVisible();
	this->hp = 100;
	dice damage;
	damage.set(0, 1, 4);
	this->damageDice = damage;
	this->inventory.reserve(10);
	this->equip.reserve(12);
	for(int i = 0; i < 10; ++i)
	{
		this->inventory[i] = NULL;
		this->equip[i] = NULL;
	}
	this->equip[10] = NULL;
	this->equip[11] = NULL;
}

Player::~Player()
{
	for(int i = 0; i < Y; ++i)
	{
		delete[] this->visible[i];
	}
	delete[] this->visible;
	for(int i = 0; i < 10; ++i)
	{
		delete this->inventory[i];
		delete this->equip[i];
	}
	delete this->equip[10];
	delete this->equip[11];
	this->inventory.clear();
	this->equip.clear();
}
