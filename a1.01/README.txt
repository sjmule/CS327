README Assignment 1.01
This program creates a basic dungeon map. Bordered by dashes, the dungeon is comprised of 8 rooms depicted by '.' and connected by corridors depicted by '#'.
Each space in the dungeon has a hardness of -1 through 5. -1 designates "immutable" and is reserved for the border of the dungeon. 0 designates open areas and
corresponds to either room or corridor spaces. All other spaces have a value of 1-5.
The code for this assignment is split into 2 C files and a corresponding header file. The file dungeon.c contains the main method and a method to print the dungeon.
The file generate.c contains all functions used to create the different parts of the dungeon.

Contained within this archive is a README, Changelog, Makefile, and the following source files:
dungeon.c
generate.c
generate.h

Running make will compile the source files together into the executable main.
