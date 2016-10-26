#include "dungeon.h"
#include "generate.h"
#include "save.h"
#include "heap.h"
#include "routing.h"
#include "movement.h"
#include "pControls.h"

dungeon aincrad;
player kirito;
int monCount = 0;
int turn = 0;
int ncurse = 0;

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
	struct arguments* arguments = state->input;
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
	aincrad.monsters = malloc(sizeof(monster) * aincrad.numMonsters);
}

void placeCharacters()
{
	int x = 0;
	int y = 0;
	while(1)
	{
		x = (rand() % (X - 2)) + 1;
		y = (rand() % (Y - 2)) + 1;
		if(aincrad.hardness[y][x] == 0)
			break;
	}
	kirito.setX(x);
	kirito.setY(y);

	calculateDistances(kirito.getX(), kirito.getY(), 0);
	calculateDistances(kirito.getX(), kirito.getY(), 1);

	createMonsters();
}

void cleanup()
{
	free(aincrad.rooms);
	free(aincrad.monsters);
}

void printDungeon()
{
	int i = 0;
	int j = 0;
	int** map = kirito.getVisible();
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
	if((aincrad.stairUpX >= (kirito.getX() - 3)) && (aincrad.stairUpX <= (kirito.getX() + 3)))
	{
		if((aincrad.stairUpY >= (kirito.getY() - 3)) && (aincrad.stairUpY <= (kirito.getY() + 3)))
			mvaddch(aincrad.stairUpY + 1, aincrad.stairUpX, '<');
	}
	if((aincrad.stairDownX >= (kirito.getX() - 3)) && (aincrad.stairDownX <= (kirito.getX() + 3)))
	{
		if((aincrad.stairDownY >= (kirito.getY() - 3)) && (aincrad.stairDownY <= (kirito.getY() + 3)))
			mvaddch(aincrad.stairDownY + 1, aincrad.stairDownX, '<');
	}
	mvaddch(kirito.getY() + 1, kirito.getX(), kirito.getSymbol());
	for(i = 0; i < aincrad.numMonsters; ++i)
	{
		if(aincrad.monsters[i].getAlive() == 1)
		{
			if((aincrad.monsters[i].getX() >= (kirito.getX() - 3)) && (aincrad.monsters[i].getX() <= (kirito.getX() + 3)))
			{
				if((aincrad.monsters[i].getY() >= (kirito.getY() - 3)) && (aincrad.monsters[i].getY() <= (kirito.getY() + 3)))
					mvaddch(aincrad.monsters[i].getY() + 1, aincrad.monsters[i].getX(), aincrad.monsters[i].getSymbol());
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
	for(; i < aincrad.numMonsters; ++i)
	{
		if(aincrad.monsters[i].getAlive())
			++alive;
	}
	return alive;
}

int main(int argc, char** argv)
{
	version = 0;
	srand((unsigned) time(0));

	char* path = malloc(40);
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

	kirito.setId(0);
	kirito.setSymbol('@');
	kirito.setSpeed(10);
	kirito.setTurn(0);
	kirito.setAlive(1);

	if(arguments.load)
		loadDungeon(arguments.loadPath, arguments.verboseMode);
	else
	{
		if(arguments.verboseMode)
			printf("Generating new dungeon\n");
		aincrad.numRooms = 8;
		aincrad.rooms = malloc(sizeof(room) * 8);
		aincrad.numMonsters = arguments.numMonsters;
		createDungeon();
	}

	if(arguments.save)
		saveDungeon(arguments.savePath, arguments.verboseMode);

	free(path);

	placeCharacters();

	// Initialize ncurses
	initscr();
	keypad(stdscr, TRUE);
	nonl();
	cbreak();
	noecho();

	printDungeon();

	int quit = 0;
	while(kirito.getAlive() && monstersAlive())
	{
		int print = 0;
		int newFloor = 0;
		if(kirito.getTurn() == turn)
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
					if((kirito.getX() == aincrad.stairDownX) && (kirito.getY() == aincrad.stairDownY))
					{
						cleanup();
						createDungeon();
						placeCharacters();
						newFloor = 1;
						turn = 0;
						good = 1;
					}
					else
						continue;
				}
				if(ch == '<')
				{
					if((kirito.getX() == aincrad.stairUpX) && (kirito.getY() == aincrad.stairUpY))
					{
						cleanup();
						createDungeon();
						placeCharacters();
						newFloor = 1;
						turn = 0;
						good = 1;
					}
					else
						continue;
				}
				else
					good = movePlayer(kirito, ch);
			}
			print = 1;
			if(quit)
				break;
			calculateDistances(kirito.getX(), kirito.getY(), 0);
			calculateDistances(kirito.getX(), kirito.getY(), 1);
			kirito.setTurn(kirito.getTurn() + (100/kirito.getSpeed()));
		}
		if(!newFloor)
		{
			int i = 0;
			for(; i < aincrad.numMonsters; ++i)
			{
				if(aincrad.monsters[i].getTurn() == turn)
				{
					moveMonster(&aincrad.monsters[i]);
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
		mvprintw(0, 0, "Game over");
		refresh();
		getch();
	}

	cleanup();

	endwin();

	return 0;
}
