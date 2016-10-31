#include "dungeon.h"
#include "generate.h"
#include "save.h"
#include "heap.h"
#include "routing.h"
#include "movement.h"
#include "pControls.h"

dungeon aincrad;
player* kirito;
int monCount = 0;
int turn = 0;
int ncurse = 0;
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
	aincrad.monsters = (monster**) malloc(sizeof(monster) * aincrad.numMonsters);
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

	setX((character*)kirito, x);
	setY((character*)kirito, y);

	calculateDistances(getX((character*)kirito), getY((character*)kirito), 0);
	calculateDistances(getX((character*)kirito), getY((character*)kirito), 1);

	createMonsters();
}

void cleanup()
{
	free(aincrad.rooms);
	cleanupMonsters();
}

void printDungeon()
{
	int i = 0;
	int j = 0;
	int** map = getVisible(kirito);
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
	if((aincrad.stairUpX >= (getX((character*)kirito) - 3)) && (aincrad.stairUpX <= (getX((character*)kirito) + 3)))
	{
		if((aincrad.stairUpY >= (getY((character*)kirito) - 3)) && (aincrad.stairUpY <= (getY((character*)kirito) + 3)))
			mvaddch(aincrad.stairUpY + 1, aincrad.stairUpX, '<');
	}
	if((aincrad.stairDownX >= (getX((character*)kirito) - 3)) && (aincrad.stairDownX <= (getX((character*)kirito) + 3)))
	{
		if((aincrad.stairDownY >= (getY((character*)kirito) - 3)) && (aincrad.stairDownY <= (getY((character*)kirito) + 3)))
			mvaddch(aincrad.stairDownY + 1, aincrad.stairDownX, '>');
	}
	mvaddch(getY((character*)kirito) + 1, getX((character*)kirito), getSymbol((character*)kirito));
	for(i = 0; i < aincrad.numMonsters; ++i)
	{
		if(getAlive((character*)aincrad.monsters[i]) == 1)
		{
			if((getX((character*)aincrad.monsters[i]) >= (getX((character*)kirito) - 3)) && (getX((character*)aincrad.monsters[i]) <= (getX((character*)kirito) + 3)))
			{
				if((getY((character*)aincrad.monsters[i]) >= (getY((character*)kirito) - 3)) && (getY((character*)aincrad.monsters[i]) <= (getY((character*)kirito) + 3)))
					mvaddch(getY((character*)aincrad.monsters[i]) + 1, getX((character*)aincrad.monsters[i]), getSymbol((character*)aincrad.monsters[i]));
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
		if(getAlive((character*)aincrad.monsters[i]))
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

	createPlayer();

	setId((character*)kirito, 0);
	setSymbol((character*)kirito, '@');
	setSpeed((character*)kirito, 10);
	setTurn((character*)kirito, 0);
	setAlive((character*)kirito, 1);
	initializeVisible(kirito);

	if(arguments.load)
		loadDungeon(arguments.loadPath, arguments.verboseMode);
	else
	{
		if(arguments.verboseMode)
			printf("Generating new dungeon\n");
		aincrad.numRooms = 8;
		aincrad.rooms = ((room*) (malloc(sizeof(room) * 8)));
		aincrad.numMonsters = arguments.numMonsters;
		createDungeon();
	}

	if(arguments.save)
		saveDungeon(arguments.savePath, arguments.verboseMode);

	free(path);

	placeCharacters();
	setVisible(kirito);

	// Initialize ncurses
	initscr();
	keypad(stdscr, TRUE);
	nonl();
	cbreak();
	noecho();
	curs_set(0);

	printDungeon();

	int quit = 0;
	while(getAlive((character*)kirito) && monstersAlive())
	{
		int print = 0;
		int newFloor = 0;
		if(getTurn((character*)kirito) == turn)
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
					if((getX((character*)kirito) == aincrad.stairDownX) && (getY((character*)kirito) == aincrad.stairDownY))
					{
						cleanup();
						createDungeon();
						clearVisible(kirito);
						placeCharacters();
						setVisible(kirito);
						newFloor = 1;
						turn = 0;
						good = 1;
					}
					else
						continue;
				}
				if(ch == '<')
				{
					if((getX((character*)kirito) == aincrad.stairUpX) && (getY((character*)kirito) == aincrad.stairUpY))
					{
						cleanup();
						createDungeon();
						clearVisible(kirito);
						placeCharacters();
						setVisible(kirito);
						newFloor = 1;
						turn = 0;
						good = 1;
					}
					else
						continue;
				}
				else
				{
					good = movePlayer(kirito, ch);
					setVisible(kirito);
				}
			}
			print = 1;
			if(quit)
				break;
			calculateDistances(getX((character*)kirito), getY((character*)kirito), 0);
			calculateDistances(getX((character*)kirito), getY((character*)kirito), 1);
			setTurn((character*)kirito, getTurn((character*)kirito) + (100/getSpeed((character*)kirito)));
		}
		if(!newFloor)
		{
			int i = 0;
			for(; i < aincrad.numMonsters; ++i)
			{
				if(getTurn((character*)aincrad.monsters[i]) == turn)
				{
					moveMonster(aincrad.monsters[i]);
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
		if(getAlive((character*)kirito))
		{
			mvprintw(0, 0, "You win!");
		}
		else
		{
			mvprintw(0, 0, "Game over");
			refresh();
		}
		getch();
	}

	cleanup();

	cleanupPlayer();

	endwin();

	return 0;
}
