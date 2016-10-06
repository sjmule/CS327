#include "dungeon.h"
#include "generate.h"
#include "save.h"
#include "binheap.h"
#include "routing.h"
#include "move.h"

dungeon aincrad;
player kirito;
int monCount = 0;
int turn = 0;

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

void printDungeon(int debug)
{
	int i = 0;
	for(; i < Y; ++i)
	{
		int j = 0;
		for(; j < X; ++j)
		{
			printf("%c", aincrad.map[i][j]);
		}
		printf("\n");
	}
	if(debug)
	{
		if(debug == 2)
		{
			for(i = 0; i < Y; ++i)
			{
				int j = 0;
				for(; j < X; ++j)
				{
					printf("%d", aincrad.hardness[i][j]);
				}
				printf("\n");
			}

			printCosts();
		}

		printf("Player:\n");
		printf("  X: %d\n", kirito.base->x);
		printf("  Y: %d\n", kirito.base->y);

		for(i = 0; i < aincrad.numMonsters; ++i)
		{
			printf("Monster %c:\n", aincrad.monsters[i].base->symbol);
			printf("  Alive: %d\n", aincrad.monsters[i].base->alive);
			printf("  X: %d\n", aincrad.monsters[i].base->x);
			printf("  Y: %d\n", aincrad.monsters[i].base->y);
			printf("  Attr: %x\n", aincrad.monsters[i].attributes);
			printf("  Speed: %d\n", aincrad.monsters[i].base->speed);
		}
	}
}

// The arg parser object
static struct argp argp = {options, parse_opt, 0, doc};

int monstersAlive()
{
	int i = 0;
	int alive = 0;
	for(; i < aincrad.numMonsters; ++i)
	{
		if(aincrad.monsters[1].base->alive)
			++alive;
	}
	return alive;
}

int main(int argc, char** argv)
{
	version = 0;
	srand((unsigned) time(0));

	char* home = getenv("HOME");
	char* path = strcat(home, "/.rlg327");
	mkdir(path, 0777);
	char* filePath = strcat(path, "/dungeon");

	// Define defaults for the parser
	struct arguments arguments;
	arguments.verboseMode = 0;
	arguments.load = 0;
	arguments.save = 0;
	arguments.loadPath = filePath;
	arguments.savePath = filePath;
	arguments.numMonsters = 10;
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	kirito.base = malloc(sizeof(entity));
	kirito.base->symbol = '@';
	kirito.base->speed = 10;
	kirito.base->turn = 0;
	kirito.base->alive = 1;

	if(arguments.load)
		loadDungeon(arguments.loadPath, arguments.verboseMode);
	else
	{
		if(arguments.verboseMode)
			printf("Generating new dungeon\n");	
		aincrad.numRooms = 8;
		aincrad.rooms = malloc(sizeof(room) * 8);
		initializeDungeon();
		createRooms();
		connectRooms();
	}

	if(arguments.save)
		saveDungeon(arguments.savePath, arguments.verboseMode);

	while(1)
	{
		kirito.base->x = (rand() % (X - 2)) + 1;
		kirito.base->y = (rand() % (Y - 2)) + 1;
		if(aincrad.hardness[kirito.base->y][kirito.base->x] == 0)
			break;
	}

	aincrad.map[kirito.base->y][kirito.base->x] = kirito.base->symbol;

	calculateDistances(kirito.base->x, kirito.base->y, 0);
	calculateDistances(kirito.base->x, kirito.base->y, 1);

	aincrad.numMonsters = arguments.numMonsters;
	aincrad.monsters = malloc(sizeof(monster) * aincrad.numMonsters);

	createMonsters();
	
	printDungeon(arguments.verboseMode);

	while(kirito.base->alive && monstersAlive())
	{
		int print = 0;
		if(kirito.base->turn == turn)
		{
			moveRandom(kirito.base, 1);
			print = 1;
		}
		int i = 0;
		for(; i < aincrad.numMonsters; ++i)
		{
			if(aincrad.monsters[i].base->turn == turn)
			{
				moveMonster(&aincrad.monsters[i]);
				print = 1;
			}
		}
		if(print)
		{
			printDungeon(arguments.verboseMode);
			sleep(1);
		}
		++turn;
	}

	printDungeon(1);

	free(aincrad.rooms);
	free(kirito.base);
	int j = 0;
	for(; j < aincrad.numMonsters; ++j)
	{
		free(aincrad.monsters[j].base);
	}
	free(aincrad.monsters);

	return 0;
}
