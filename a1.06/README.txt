README Assignment 1.06
This program creates a basic dungeon map. Bordered by dashes, the dungeon is comprised of 8 rooms depicted by '.' and connected by corridors depicted by '#'.
Each space in the dungeon has a hardness of 0 through 255. 255 designates "immutable" and is reserved for the border of the dungeon. 0 designates open areas and
corresponds to either room or corridor spaces. All other spaces have a value of 1-5.

This program implements the Argp interface for parsing Unix-style argument vectors. Running the executable with --help or --usage will provide flags that may be used with this program.
The dungeon executable can be run by itself to generate a new dungeon, or the flags --save and --load may be included to save/load a dungeon file located in /home/<user>/.rlg327/.
The file is saved in a file name "dungeon".

To specify a save or load location the arguments --save-path PATH and --load-path PATH may be used.
The code for this assignment is split into 3 C files and 2 corresponding header files. The file dungeon.c contains the main method and a method to print the dungeon.
The file generate.c contains all functions used to create the different parts of the dungeon. The file save.c contains the functions responsible for saving and loading the dungeon.

This implementation of our Rouge Like Game implements Dijkstra's algorithm to find the cost of traveling from 1) open spaces, rooms and corridors, and 2) all spaces, to the location of the player character denoted by a @.
The player is randomly placed in an open space in the dungeon, then the distances are calculated. Distances are printed after the basic map as the cost of traveling across open spaces only first, then all spaces.
Distances are displayed on the map as 0-9,a-z,A-Z. For distances greater than the number of characters provided, 61(Z), the dungeon renders normally. All functions used to complete these operations are contained within
routing.c and rely on heap.c for a heap.

This dungeon is initialized with a player character @ and by default 10 monsters. You may specify the number of monsters you wish to initialize the dungeon with by using the flags -n or --nummon followed by a number.
The monsters will be initialized with random attributes and assigned random characters to represent them on the map.

Once initialized, the player and monsters are placed randomly through the dungeon. The dungeon is printed using ncurses and the player may be controlled using the numpad or y,u,h,j,k,l,b,n keys.
The monster list can be printed at any time using the m key and can be scrolled through using the up and down arrow keys. You can exit this display with the escape key.

Stairs are designated on the map with < for stairs up and > for stairs down and can be used by pressing the corresponding key while standing on the icon.
Moving to a new floor will generate a completely new dungeon with new monsters.

Pressing shift+q quits the game when not displaying the monster list.

This iteration of the game mixes C++ with C code. While most of the logic is done with C, the player, monster, and entity structs have been converted into Player, Monster, and Character classes.
The related header files provide and interface for the C code to access the member variables within the C++ classes.

Fog-of-war was introduced in this version. The logic for determining this is contained within the file Player.cpp. The player character now has a line of sign equivalent to 3 spaces in all directions.
The map displayed is what the player has seen and is only updated when the space falls within the player's range of vision.

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
heap.c
heap.h
macros.h
pControls.c
pControls.h
character.cpp
character.h
player.cpp
player.h
monster.cpp
monster.h

Running make will compile the source files using the C or C++ compiler respectively and link them together using the C++ compiler into the executable main.
