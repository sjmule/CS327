#include "generate.h"
#include "save.h"
#include "binheap.h"
#include <limits.h>
#include <stdint.h>

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
	{"x-pos", 'x', "X", 0, "Set the starting x position for the player"},
	{"y-pos", 'y', "Y", 0, "Set the starting y position for the player"},
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
	// x position of player
	int xPos;
	// y position of player
	int yPos;
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
		case 'x':
			arguments->xPos = atoi(arg);
			break;
		case 'y':
			arguments->yPos = atoi(arg);
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

typedef struct route {
	binheap_node_t *hn;
	int posX;
	int posY;
	int fromX;
	int fromY;
	int cost;
} route;

int openCost[Y][X];
int allCost[Y][X];

int hardnessCost(int x, int y)
{
	if(aincrad.hardness[y][x] >= 0 && aincrad.hardness[y][x] <= 84)
		return 1;
	if(aincrad.hardness[y][x] >= 85 && aincrad.hardness[y][x] <= 170)
		return 2;
	if(aincrad.hardness[y][x] >= 171 && aincrad.hardness[y][x] <= 254)
		return 3;
}

int32_t path_cmp(const void* key, const void* with)
{
	return ((route *) key)->cost - ((route *) with)->cost;
}

void dijkstra(int fromX, int fromY, int toX, int toY, int tunnel)
{
	static route path[Y][X], *p;
	static int initialized = 0;
	binheap_t h;
	int (*costs)[Y][X] = NULL;
	int x, y;

	if(!initialized)
	{printf("initializing\n");
		for(y = 0; y < Y; ++y)
		{
			for(x = 0; x < X; ++x)
			{
				path[y][x].cost = INT_MAX;
				path[y][x].posY = y;
				path[y][x].posX = x;
				openCost[y][x] = INT_MAX;
				allCost[y][x] = INT_MAX;
			}
		}
	}
	
	printf("initialized\n");

	if(!tunnel)
		costs = &openCost;
	else
		costs = &allCost;

	printf("%p\n", costs);
	printf("%p\n", &openCost);

	for(y = 0; y < Y; ++y)
	{
		for(x = 0; x < X; ++x)
		{
			printf("%d", *costs[y][x]);
			path[y][x].cost = *costs[y][x];
		}
	}
	
	printf("costs set\n");

	*costs[fromY][fromX] = 0;
	path[fromY][fromX].cost = 0;

	binheap_init(&h, path_cmp, NULL);

	for(y = 0; y < Y; ++y)
	{
		for(x = 0; x < X; ++x)
		{
			if(!tunnel)
			{
				if(aincrad.hardness[y][x] == 0)
					path[y][x].hn = binheap_insert(&h, &path[y][x]);
				else
					path[y][x].hn = NULL;
			}
			else
			{
				if(aincrad.hardness[y][x] == 255)
					path[y][x].hn = NULL;
				else
					path[y][x].hn = binheap_insert(&h, &path[y][x]);
			}
		}
	}

printf("bout to start while\n");

	while((p = binheap_remove_min(&h)))
	{
		p->hn = NULL;

		if((p->posY == toY) && (p->posX == toX))
		{
			for(x = toX, y = toY; (x != fromX) || (y != fromY); p = &path[y][x], x = p->fromX, y = p->fromY)
			{
				*costs[y][x] = 0;
			}
			binheap_delete(&h);
			return;
		}
		if((path[p->posY - 1][p->posX - 1].hn) && (path[p->posY - 1][p->posX - 1].cost > p->cost + 1))
		{
			path[p->posY - 1][p->posX - 1].cost = p->cost + 1;
			*costs[p->posY - 1][p->posX - 1] = p->cost + 1;
			path[p->posY - 1][p->posX - 1].fromY = p->posY;
			path[p->posY - 1][p->posX - 1].fromX = p->posX;
			binheap_decrease_key(&h, path[p->posY - 1][p->posX - 1].hn);
		}
		if((path[p->posY - 1][p->posX    ].hn) && (path[p->posY - 1][p->posX    ].cost > p->cost + 1))
		{
			path[p->posY - 1][p->posX    ].cost = p->cost + 1;
			*costs[p->posY - 1][p->posX    ] = p->cost + 1;
			path[p->posY - 1][p->posX    ].fromY = p->posY;
			path[p->posY - 1][p->posX    ].fromX = p->posX;
			binheap_decrease_key(&h, path[p->posY - 1][p->posX    ].hn);
		}
		if((path[p->posY - 1][p->posX + 1].hn) && (path[p->posY - 1][p->posX + 1].cost > p->cost + 1))
		{
			path[p->posY - 1][p->posX + 1].cost = p->cost + 1;
			*costs[p->posY - 1][p->posX + 1] = p->cost + 1;
			path[p->posY - 1][p->posX + 1].fromY = p->posY;
			path[p->posY - 1][p->posX + 1].fromX = p->posX;
			binheap_decrease_key(&h, path[p->posY - 1][p->posX + 1].hn);
		}
		if((path[p->posY    ][p->posX - 1].hn) && (path[p->posY    ][p->posX - 1].cost > p->cost + 1))
		{
			path[p->posY    ][p->posX - 1].cost = p->cost + 1;
			*costs[p->posY    ][p->posX - 1] = p->cost + 1;
			path[p->posY    ][p->posX - 1].fromY = p->posY;
			path[p->posY    ][p->posX - 1].fromX = p->posX;
			binheap_decrease_key(&h, path[p->posY    ][p->posX - 1].hn);
		}
		if((path[p->posY    ][p->posX + 1].hn) && (path[p->posY    ][p->posX + 1].cost > p->cost + 1))
		{
			path[p->posY    ][p->posX + 1].cost = p->cost + 1;
			*costs[p->posY    ][p->posX + 1] = p->cost + 1;
			path[p->posY    ][p->posX + 1].fromY = p->posY;
			path[p->posY    ][p->posX + 1].fromX = p->posX;
			binheap_decrease_key(&h, path[p->posY    ][p->posX + 1].hn);
		}
		if((path[p->posY + 1][p->posX - 1].hn) && (path[p->posY + 1][p->posX - 1].cost > p->cost + 1))
		{
			path[p->posY + 1][p->posX - 1].cost = p->cost + 1;
			*costs[p->posY + 1][p->posX - 1] = p->cost + 1;
			path[p->posY + 1][p->posX - 1].fromY = p->posY;
			path[p->posY + 1][p->posX - 1].fromX = p->posX;
			binheap_decrease_key(&h, path[p->posY + 1][p->posX - 1].hn);
		}
		if((path[p->posY + 1][p->posX    ].hn) && (path[p->posY + 1][p->posX    ].cost > p->cost + 1))
		{
			path[p->posY + 1][p->posX    ].cost = p->cost + 1;
			*costs[p->posY + 1][p->posX    ] = p->cost + 1;
			path[p->posY + 1][p->posX    ].fromY = p->posY;
			path[p->posY + 1][p->posX    ].fromX = p->posX;
			binheap_decrease_key(&h, path[p->posY + 1][p->posX    ].hn);
		}
		if((path[p->posY + 1][p->posX + 1].hn) && (path[p->posY + 1][p->posX + 1].cost > p->cost + 1))
		{
			path[p->posY + 1][p->posX + 1].cost = p->cost + 1;
			*costs[p->posY + 1][p->posX + 1] = p->cost + 1;
			path[p->posY + 1][p->posX + 1].fromY = p->posY;
			path[p->posY + 1][p->posX + 1].fromX = p->posX;
			binheap_decrease_key(&h, path[p->posY + 1][p->posX + 1].hn);
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
	arguments.xPos = (rand() % 78) + 1;
	arguments.yPos = (rand() % 19) + 1;
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

	printDungeon(&aincrad, arguments.verboseMode);

	int fromX, fromY, toX, toY;
	while(1)
	{
		fromX = (rand() % (X - 2)) + 1;
		fromY = (rand() % (Y - 2)) + 1;
		if(aincrad.hardness[fromY][fromX] == 0)
			break;
	}
	while(1)
	{
		toX = (rand() % (X - 2)) + 1;
		toY = (rand() % (Y - 2)) + 1;
		if(aincrad.hardness[toY][toX] == 0)
			break;
	}

	printf("going to call dijkstra\n");

	dijkstra(fromX, fromY, toX, toY, 0);

	int i = 0;
	for(; i < Y; ++i)
	{
		int j = 0;
		for(; j < X; ++j)
		{
			if(openCost[i][j] == 0)
				printf("0");
			else
				printf(" ");
		}
		printf("\n");
	}

	free(aincrad.rooms);

	return 0;
}
