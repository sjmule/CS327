#include <stdio.h>
#include <stdlib.h>

#define X 81
#define Y 21

char dungeon[Y][X];
int hardness[Y][X];
int rooms;

void set_immutable()
{
	int i = 0;
	for(i; i < X; ++i)
	{
		hardness[0][i] = -1;
	}
	for(i = 0; i < X; ++i)
	{
		hardness[Y-1][i] = -1;
	}
	for(i = 1; i < Y-1; ++i)
	{
		hardness[i][0] = -1;
		hardness[i][X-2] = -1;
	}
} 

void set_hardness()
{
	int i = 1;
	for(i; i < Y-1; ++i)
	{
		int j = 1;
		for(j; j < X-2; ++j)
		{
			hardness[i][j] = (rand() % 5) + 1;
		}
	}	
}

void initialize_dungeon()
{
	set_immutable();
	printf("set immutable\n");
	set_hardness();
	printf("set hardness\n");
	
	int i = 0;
	for(i; i < Y; ++i)
	{
		int j = 0;
		for(j; j < X; ++j)
		{
			dungeon[i][j] = ' ';
		}
		dungeon[i][X-1] = 0;
	}
	
	rooms = 0;
}

void print_dungeon()
{
	int i = 0;
	for(i; i < Y; ++i)
	{
		printf("%s\n", dungeon[i]);
	}
	for(i = 0; i < Y; ++i)
	{
		int j = 0;
		for(j; j < X; ++j)
		{
			printf("%d", hardness[i][j]);
		}
		printf("\n");
	}
	getchar();
}

void create_rooms()
{
	int attempts = 0;
	while(attempts < 200 && rooms < 20)
	{
		printf("attempt number: %d, rooms made: %d\n", attempts, rooms);
		print_dungeon();

		int x_center = (rand() % (X-3)) + 1;
		int y_center = (rand() % (Y-2)) + 1;
		int north = 0;
		int south = 0;
		int east = 0;
		int west = 0;
		if(hardness[y_center][x_center] != 0 && hardness[y_center][x_center] != -1)
		{
			hardness[y_center][x_center] = 0;
			dungeon[y_center][x_center] = '.';

			int x_size = (rand() % 5) + 4;
			int y_size = (rand() % 5) + 3;
			int tries = 0;

			while((x_size > 0 || y_size > 0) && tries < 500)
			{
				int y = y_center;
				int x = x_center;
				int dir = rand() % 4;
				switch(dir)
				{
					case 0:
						while(y_size > 0)
						{
							if(y-1 == 0)
								break;
							else
							{
								if(hardness[y-1][x] != 0 && hardness[y-2][x])
								{
									hardness[--y][x] = 0;
									dungeon[y][x] = '.';
									--y_size;
								}
								else
								{
									if(north == 0)
										north = y;
									break;
								}
							}
						}
						break;
					case 1:
						while(x_size > 0)
						{
							if(x+1 == X-2)
								break;
							else
							{
								if(hardness[y][x+1] != 0 && hardness[y][x+2] != 0)
								{
									hardness[y][++x] = 0;
									dungeon[y][x] = '.';
									--x_size;
								}
								else
								{
									if(east == 0)
										east = x;
									break;
								}
							}
						}
						break;
					case 2:
						while(y_size > 0)
						{
							if(y+1 == Y-1)
								break;
							else
							{
								if(hardness[y+1][x] != 0 && hardness[y+2][x] != 0)
								{
									hardness[++y][x] = 0;
									dungeon[y][x] = '.';
									--y_size;
								}
								else
								{
									if(south == 0)
										south = y;
									break;
								}
							}
						}
						break;
					case 3:
						while(x_size > 0)
						{
							if(x-1 == 0)
								break;
							else
							{
								if(hardness[y][x-1] != 0 && hardness[y][x-2] != 0)
								{
									hardness[y][--x] = 0;
									dungeon[y][x] = 0;
									--x_size;
								}
								else
								{
									if(west == 0)
										west = x;
									break;
								}
							}
						}
						break;
				}
				++tries;
				if(tries > 100)
					break;
			}
			int i = north;
			for(i; i < south; ++i)
			{
				int j = west;
				for(j; j < east; ++j)
				{
					hardness[i][j] = 0;
					dungeon[i][j] = '.';
				}
			}
			++rooms;
		}
		++attempts;
	}
}

int main(int argc, char** argv)
{
	srand((unsigned) time(0));
	initialize_dungeon();
	printf("initialized dungeon\n");
	create_rooms();
	printf("created rooms\n");
	print_dungeon();
	
	return 0;
}
