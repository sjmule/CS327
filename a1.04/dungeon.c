#include "dungeon.h"
#include "generate.h"
#include "save.h"
#include "routing.h"
#include "move.h"

dungeon aincrad;
player kirito;

// Program version string
const char *argp_program_version = "Rouge Like Game 327 v0.0.1";
// Program bug address string
const char *argp_program_bug_address = "Scott Mueller <sjmule@comcast.net>";
// Program documentation string
static char doc[] = "A Rouge Like Game developed for ComS 327";

// List of options supported
static struct argp_option options[] =
{
	{"verbose", 'v', 0, 0, "Prints some extra information including cell hardness"},
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

		printf("Player:\n");
		printf("  X: %d\n", kirito.base.x);
		printf("  Y: %d\n", kirito.base.y);

		for(i = 0; i < aincrad.numMonsters; ++i)
		{
			printf("Monster %c:\n", aincrad.monsters[i].base.symbol);
			printf("  X: %d\n", aincrad.monsters[i].base.x);
			printf("  Y: %d\n", aincrad.monsters[i].base.y);
			printf("  Attr: %x\n", aincrad.monsters[i].attributes);
			printf("  Speed: %d\n", aincrad.monsters[i].base.speed);
		}
	}
}

void createMonsters()
{
	int i = 0;
	for(; i < aincrad.numMonsters; ++i)
	{
		monster mon;
		mon.attributes = 0;
		int attr = rand() % 100;
		if(attr < 50)
			mon.attributes = mon.attributes | INTELLIGENT;
		attr = rand() % 100;
		if(attr < 50)
			mon.attributes = mon.attributes | TELEPATHIC;
		attr = rand() % 100;
		if(attr < 50)
			mon.attributes = mon.attributes | TUNNELING;
		attr = rand() % 100;
		if(attr < 50)
			mon.attributes = mon.attributes | ERRATIC;
		attr = (rand() % 15) + 5;
		mon.base.speed = attr;
		while(1)
		{
			mon.base.x = (rand() % (X - 2)) + 1;
			mon.base.y = (rand() % (Y - 2)) + 1;
			if(aincrad.hardness[mon.base.y][mon.base.x] == 0)
				break;
		}
		mon.base.symbol = (rand() % 25) + 97;
		aincrad.monsters[i] = mon;
		aincrad.map[mon.base.y][mon.base.x] = mon.base.symbol;
	}
}

void cleanCell(int x, int y)
{
	int i = 0;
	for(; i < aincrad.numRooms; ++i)
	{
		room temp = aincrad.rooms[i];
		if((x >= temp.x) && (x <= (temp.x + temp.width)))
		{
			if((y >= temp.y) && (y <= (temp.y + temp.height)))
				aincrad.map[y][x] = '.';
		}
		else
			aincrad.map[y][x] = '#';
	}
}

void move(entity* character, int dir)
{
	switch(dir)
	{
		case 0:
			cleanCell(character->x, character->y);
			character->x--;
			character->y--;
			aincrad.map[character->y][character->x] = character->symbol;
			break;
		case 1:
			cleanCell(character->x, character->y);
			character->y--;
			aincrad.map[character->y][character->x] = character->symbol;
			break;
		case 2:
			cleanCell(character->x, character->y);
			character->x++;
			character->y--;
			aincrad.map[character->y][character->x] = character->symbol;
			break;
		case 3:
			cleanCell(character->x, character->y);
			character->x++;
			aincrad.map[character->y][character->x] = character->symbol;
			break;
		case 4:
			cleanCell(character->x, character->y);
			character->x++;
			character->y++;
			aincrad.map[character->y][character->x] = character->symbol;
			break;
		case 5:
			cleanCell(character->x, character->y);
			character->y++;
			aincrad.map[character->y][character->x] = character->symbol;
			break;
		case 6:
			cleanCell(character->x, character->y);
			character->x--;
			character->y++;
			aincrad.map[character->y][character->x] = character->symbol;
			break;
		case 7:
			cleanCell(character->x, character->y);
			character->x--;
			aincrad.map[character->y][character->x] = character->symbol;
			break;
		default:
			break;
	}
}

void moveMonsters(monster mon)
{
	if((mon.attributes & ERRATIC) == 1)
	{

	}
	else
	{
		int dir = rand() % 7;
		move(&mon.base, dir);
	}
	
}

// The arg parser object
static struct argp argp = {options, parse_opt, 0, doc};

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
	arguments.numMonsters = 0;
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	kirito.base.symbol = '@';
	kirito.base.speed = 10;

	if(arguments.load == 1)
		loadDungeon(arguments.loadPath, arguments.verboseMode);
	else
	{
		if(arguments.verboseMode == 1)
			printf("Generating new dungeon\n");	
		aincrad.numRooms = 8;
		aincrad.rooms = malloc(sizeof(room) * 8);
		initializeDungeon();
		createRooms();
		connectRooms();
	}

	if(arguments.save == 1)
		saveDungeon(arguments.savePath, arguments.verboseMode);

	while(1)
	{
		kirito.base.x = (rand() % (X - 2)) + 1;
		kirito.base.y = (rand() % (Y - 2)) + 1;
		if(aincrad.hardness[kirito.base.y][kirito.base.x] == 0)
			break;
	}

	aincrad.numMonsters = arguments.numMonsters;
	aincrad.monsters = malloc(sizeof(monster) * aincrad.numMonsters);

	createMonsters();

	aincrad.map[kirito.base.y][kirito.base.x] = kirito.base.symbol;
	
	dijkstra(kirito.base.x, kirito.base.y, 0);
	dijkstra(kirito.base.x, kirito.base.y, 1);

	printDungeon(arguments.verboseMode);

	free(aincrad.rooms);
	free(aincrad.monsters);

	return 0;
}
