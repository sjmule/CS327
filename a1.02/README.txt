README Assignment 1.02
This program creates a basic dungeon map. Bordered by dashes, the dungeon is comprised of 8 rooms depicted by '.' and connected by corridors depicted by '#'.
Each space in the dungeon has a hardness of 0 through 255. 255 designates "immutable" and is reserved for the border of the dungeon. 0 designates open areas and
corresponds to either room or corridor spaces. All other spaces have a value of 1-5.
This program implements the Argp interface for parsing Unix-style argument vectors. Running the executable with --help or --usage will provide flags that may be used with this program.
The dungeon executable can be run by itself to generate a new dungeon, or the flags --save and --load may be included to save/load a dungeon file located in /home/<user>/.rlg327/.
The file is saved in a file name "dungeon".
To specify a save or load location the arguments --save-path PATH and --load-path PATH may be used.
The code for this assignment is split into 3 C files and 2 corresponding header files. The file dungeon.c contains the main method and a method to print the dungeon.
The file generate.c contains all functions used to create the different parts of the dungeon. The file save.c contains the functions responsible for saving and loading the dugeon.

Contained within this archive is a README, Changelog, Makefile, and the following source files:
dungeon.c
generate.c
generate.h
save.c
save.h

Running make will compile the source files together into the executable main.
