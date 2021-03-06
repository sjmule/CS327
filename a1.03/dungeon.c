#include "generate.h"
#include "save.h"
#include "routing.h"

dungeon aincrad;

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
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

void printDungeon(dungeon* temp, int debug)
{
	int i = 0;
	for(; i < Y; ++i)
	{
		int j = 0;
		for(; j < X; ++j)
		{
			printf("%c", temp->map[i][j]);
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
				printf("%d", temp->hardness[i][j]);
			}
			printf("\n");
		}
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
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

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

	int playerX, playerY;
	while(1)
	{
		playerX = (rand() % (X - 2)) + 1;
		playerY = (rand() % (Y - 2)) + 1;
		if(aincrad.hardness[playerY][playerX] == 0)
			break;
	}

	
	aincrad.map[playerY][playerX] = '@';

	printDungeon(&aincrad, arguments.verboseMode);

	dijkstra(playerX, playerY, 0);
	dijkstra(playerX, playerY, 1);

	printCosts();
	
	free(aincrad.rooms);

	return 0;
}
