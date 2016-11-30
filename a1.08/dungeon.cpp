#include "dungeon.h"
#include "generate.h"
#include "save.h"
#include "heap.h"
#include "routing.h"
#include "movement.h"
#include "pControls.h"

Dungeon* aincrad;
Player* kirito;
int turn = 0;
unsigned int version = 0;

// Program version string
const char *argp_program_version = "Rouge Like Game 327 v0.0.1";
// Program bug address string
const char *argp_program_bug_address = "Scott Mueller <sjmule@comcast.net>";
// Program documentation string
static char doc[] = "A Rouge Like Game developed for ComS 327";

// List of options supported
static struct argp_option options[] =
{
	{"verbose", 'v', 0, 0, "Prints some extra information"},
	{"debug", 'd', 0, 0, "Prints a lot of extra information"},
	{"load", 'l', 0, 0, "Load a dungeon from the default location"},
	{"save", 's', 0, 0, "Save the dugeon to the default location"},
	{"load-path", 'r', "PATH", 0, "Load the dungeon at the specified path"},
	{"save-path", 'w', "PATH", 0, "Save the dungeon to the specified path"},
	{"nummon", 'n', "#", 0, "Number of monsters to include in the dungeon"},
	{0}
};

// Argument structure to store the results of command line parsing
struct arguments
{
	// are we in verbose mode?
	int verboseMode;
	// should we load?
	int load;
	// should we save?
	int save;
	// path to load from
	char* loadPath;
	// path to save to
	char* savePath;
	// number of monsters
	int numMonsters;
};

/*
 * @brief	Callback to parse a command line argument
 * @param	key
 * 			The short code key of this argument
 * @param	arg
 *			The argument following the code
 * @param	state
 * 			The state of the arg parser state machine
 * @return	0 if successfully handled the key, ARGP_ERR_UNKNOWN if the key was unknown
 */
error_t parse_opt(int key, char* arg, struct argp_state *state)
{
	struct arguments* arguments = (struct arguments*) state->input;
	switch(key)
	{
		case 'v':
			arguments->verboseMode = 1;
			break;
		case 'd':
			arguments->verboseMode = 2;
			break;
		case 'l':
			arguments->load = 1;
			break;
		case 's':
			arguments->save = 1;
			break;
		case 'r':
			arguments->load = 1;
			arguments->loadPath = arg;
			break;
		case 'w':
			arguments->save = 1;
			arguments->savePath = arg;
			break;
		case 'n':
			arguments->numMonsters = atoi(arg);
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

void createDungeon()
{
	initializeDungeon();
	createRooms();
	connectRooms();
	loadObjects();
}

void placeCharacters()
{
	int x = 0;
	int y = 0;
	while(1)
	{
		x = (rand() % (X - 2)) + 1;
		y = (rand() % (Y - 2)) + 1;
		if(aincrad->hardness[y][x] == 0)
			break;
	}

	kirito->x = x;
	kirito->y = y;

	calculateDistances(kirito->x, kirito->y, 0);
	calculateDistances(kirito->x, kirito->y, 1);

	loadMonsters();
}

void printDungeon()
{
	int i = 0;
	int j = 0;
	int** map = kirito->visible;
	for(; i < X; ++i)
	{
		mvaddch(0, i, ' ');
	}
	for(i = 0; i < Y; ++i)
	{
		for(j = 0; j < X; ++j)
		{
			mvaddch(i + 1, j, map[i][j]);
		}
	}
	if((aincrad->stairUpX >= (kirito->x - 3)) && (aincrad->stairUpX <= (kirito->x + 3)))
	{
		if((aincrad->stairUpY >= (kirito->y - 3)) && (aincrad->stairUpY <= (kirito->y + 3)))
			mvaddch(aincrad->stairUpY + 1, aincrad->stairUpX, '<');
	}
	if((aincrad->stairDownX >= (kirito->x - 3)) && (aincrad->stairDownX <= (kirito->x + 3)))
	{
		if((aincrad->stairDownY >= (kirito->y - 3)) && (aincrad->stairDownY <= (kirito->y + 3)))
			mvaddch(aincrad->stairDownY + 1, aincrad->stairDownX, '>');
	}
	unsigned int k;
	for(k = 0; k < aincrad->objects.size(); ++k)
	{
		if((aincrad->objects.at(k).x >= (kirito->x - 3)) && (aincrad->objects.at(k).x <= (kirito->x + 3)))
		{
			if((aincrad->objects.at(k).y >= (kirito->y - 3)) && (aincrad->objects.at(k).y <= (kirito->y + 3)))
			{
				attron(COLOR_PAIR(aincrad->objects.at(k).color));
				mvaddch(aincrad->objects.at(k).y + 1, aincrad->objects.at(k).x, aincrad->objects.at(k).symbol);
				attroff(COLOR_PAIR(aincrad->objects.at(k).color));
			}
		}
	}
	mvaddch(kirito->y + 1, kirito->x, kirito->symbol);
	for(i = 0; i < aincrad->numMonsters; ++i)
	{
		if(aincrad->monsters.at(i).alive == 1)
		{
			if((aincrad->monsters.at(i).x >= (kirito->x - 3)) && (aincrad->monsters.at(i).x <= (kirito->x + 3)))
			{
				if((aincrad->monsters.at(i).y >= (kirito->y - 3)) && (aincrad->monsters.at(i).y <= (kirito->y + 3)))
				{
					//attron(COLOR_PAIR(aincrad->monsters.at(i).color));
					mvaddch(aincrad->monsters.at(i).y + 1, aincrad->monsters.at(i).x, aincrad->monsters.at(i).symbol);
					//attroff(COLOR_PAIR(aincrad->monsters.at(i).color));
				}
			}
		}
	}
	refresh();
}

// The arg parser object
static struct argp argp = {options, parse_opt, 0, doc};

int monstersAlive()
{
	int i = 0;
	int alive = 0;
	for(; i < aincrad->numMonsters; ++i)
	{
		if(aincrad->monsters.at(i).alive)
			++alive;
	}
	return alive;
}

int main(int argc, char** argv)
{
	srand((unsigned) time(0));

	char* path = (char*) malloc(40);
	strcat(path, getenv("HOME"));
	strcat(path, "/.rlg327");
	mkdir(path, 0777);

	// Define defaults for the parser
	struct arguments arguments;
	arguments.verboseMode = 0;
	arguments.load = 0;
	arguments.save = 0;
	arguments.loadPath = path;
	arguments.savePath = path;
	arguments.numMonsters = 10;
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	kirito = new Player;
	aincrad = new Dungeon;

	parse_descriptions(aincrad, path);

	kirito->id = 0;
	kirito->symbol = '@';
	kirito->speed = 10;
	kirito->turn = 0;
	kirito->alive = 1;
	kirito->initializeVisible();

	if(arguments.load)
		loadDungeon(arguments.loadPath, arguments.verboseMode);
	else
	{
		if(arguments.verboseMode)
			printf("Generating new dungeon\n");
		aincrad->numRooms = 8;
		aincrad->rooms = ((room*) (malloc(sizeof(room) * 8)));
		aincrad->numMonsters = arguments.numMonsters;
		createDungeon();
	}

	if(arguments.save)
		saveDungeon(arguments.savePath, arguments.verboseMode);

	free(path);

	placeCharacters();
	kirito->setVisible();

	// Initialize ncurses
	initscr();
	keypad(stdscr, TRUE);
	nonl();
	cbreak();
	noecho();
	curs_set(0);
	start_color();

	printDungeon();

	int quit = 0;
	while(kirito->alive && monstersAlive())
	{
		int print = 0;
		int newFloor = 0;
		if(kirito->turn == turn)
		{
			int good = 0;
			while(!good)
			{
				int ch = getch();
				if(ch == 'Q')
				{
					quit = 1;
					break;
				}
				if(ch == 'm')
				{
					displayMonsters();
					printDungeon();
				}
				if(ch == '>')
				{
					if((kirito->x == aincrad->stairDownX) && (kirito->y == aincrad->stairDownY))
					{
						free(aincrad->rooms);
						aincrad->monsters.clear();
						aincrad->objects.clear();
						createDungeon();
						kirito->clearVisible();
						placeCharacters();
						kirito->setVisible();
						newFloor = 1;
						turn = 0;
						good = 1;
					}
					else
						continue;
				}
				if(ch == '<')
				{
					if((kirito->x == aincrad->stairUpX) && (kirito->y == aincrad->stairUpY))
					{
						free(aincrad->rooms);
						aincrad->monsters.clear();
						aincrad->objects.clear();
						createDungeon();
						kirito->clearVisible();
						placeCharacters();
						kirito->setVisible();
						newFloor = 1;
						turn = 0;
						good = 1;
					}
					else
						continue;
				}
				else
				{
					good = movePlayer(ch);
					kirito->setVisible();
				}
			}
			print = 1;
			if(quit)
				break;
			calculateDistances(kirito->x, kirito->y, 0);
			calculateDistances(kirito->x, kirito->y, 1);
			kirito->turn = kirito->turn + (100/kirito->speed);
		}
		if(!newFloor)
		{
			int i = 0;
			for(; i < aincrad->numMonsters; ++i)
			{
				if(aincrad->monsters.at(i).turn == turn)
				{
					moveMonster(&aincrad->monsters.at(i));
					print = 1;
				}
			}
		}
		if(print)
		{
			printDungeon();
		}
		if(!newFloor)
			++turn;
	}

	if(!quit)
	{
		printDungeon();
		if(kirito->alive)
		{
			mvprintw(0, 0, "You win!");
			refresh();
		}
		else
		{
			mvprintw(0, 0, "Game over");
			refresh();
		}
		getch();
	}

	free(aincrad->rooms);
	destroy_descriptions(aincrad);
	aincrad->objects.clear();
	aincrad->monsters.clear();
	delete aincrad;

	delete kirito;

	endwin();

	return 0;
}
