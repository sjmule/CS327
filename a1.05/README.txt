README Assignment 1.04
This program creates a basic dungeon map. Bordered by dashes, the dungeon is comprised of 8 rooms depicted by '.' and connected by corridors depicted by '#'.
Each space in the dungeon has a hardness of 0 through 255. 255 designates "immutable" and is reserved for the border of the dungeon. 0 designates open areas and
corresponds to either room or corridor spaces. All other spaces have a value of 1-5.

This program implements the Argp interface for parsing Unix-style argument vectors. Running the executable with --help or --usage will provide flags that may be used with this program.
The dungeon executable can be run by itself to generate a new dungeon, or the flags --save and --load may be included to save/load a dungeon file located in /home/<user>/.rlg327/.
The file is saved in a file name "dungeon".

To specify a save or load location the arguments --save-path PATH and --load-path PATH may be used.
The code for this assignment is split into 3 C files and 2 corresponding header files. The file dungeon.c contains the main method and a method to print the dungeon.
The file generate.c contains all functions used to create the different parts of the dungeon. The file save.c contains the functions responsible for saving and loading the dugeon.

This implementation of our Rouge Like Game implements Dijkstra's algorithm to find the cost of traveling from 1) open spaces, rooms and corridors, and 2) all spaces, to the location of the player character denoted by a @.
The player is randomly placed in an open space in the dungeon, then the distances are calculated. Distances are printed after the basic map as the cost of traveling across open spaces only first, then all spaces.
Distances are displayed on the map as 0-9,a-z,A-Z. For distances greater than the number of characters provided, 61(Z), the dungeon renders normally. All functions used to complete these operations are contained within
routing.c and rely on binheap.c for a binary heap.

This dugeon is initialized with a player character @ and by default 10 monsters. You may specify the number of monsters you wish to initialize the dungeon with by using the flags -n or --nummon followed by a number.
The monsters will be initialized with random attributes and assigned random characters to represent them on the map. Once initialized, the player will randomly move around the map and the monsters will move according to their
characteristics. The movement ends when all the monsters are dead or a monster reaches the player.

Note: This implementation of Dijkstra's uses a binary heap provided by Jeremy Sheaffer unmodified. A bug has been found where this implementation will sometimes cause the program to crash and throw an error with the following message
while completing the binheap_remove_min() operation. *** THE PROFESSOR IS AWARE OF THIS IT WAS BROUGHT UP IN CLASS *** 

*** Error in `./main': double free or corruption (fasttop): <address> ***
Aborted

Uncommenting the added printf statments in the function will show that the error occurs at some point when this function is called. This does not always happen, and is rather rare.

Contained within this archive is a README, Changelog, Makefile, and the following source files:
dungeon.c
dungeon.h
generate.c
generate.h
save.c
save.h
routing.c
routing.h
move.c
move.h
binheap.c
binheap.h

Running make will compile the source files together into the executable main.
