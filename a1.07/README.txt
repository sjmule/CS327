README Assignment 1.07

This version is a little different.  While the functionality for the previous iterations of the game still exist, it is commented out and ignored.
This version of the game only looks to load a file from the user's home directory in the folder .rlg327.  The file it looks for is monster_desc.txt.
From this file it attempts to parse monsters and convert them into Monster objects in C++ and store them in a vector.
It then prints all the monster information it was able to parse, and quits.

Contained within this archive is a README, Changelog, Makefile, and the following source files:
dungeon.cpp
dungeon.h
generate.cpp
generate.h
save.cpp
save.h
routing.cpp
routing.h
movement.cpp
movement.h
heap.cpp
heap.h
macros.h
pControls.cpp
pControls.h
character.h
player.cpp
player.h
monster.cpp
monster.h
fileParser.cpp
fileParser.h

Running make will compile the source files using the C++ compiler into the executable main.  This project is compiled to the C++11 standard.
