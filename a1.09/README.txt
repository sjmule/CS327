README Assignment 1.08
This program creates a basic dungeon map. Bordered by dashes, the dungeon is comprised of 8 rooms depicted by '.' and connected by corridors depicted by '#'.
Each space in the dungeon has a hardness of 0 through 255. 255 designates "immutable" and is reserved for the border of the dungeon. 0 designates open areas and
corresponds to either room or corridor spaces. All other spaces have a value of 1-5.

This program implements the Argp interface for parsing Unix-style argument vectors. Running the executable with --help or --usage will provide flags that may be used with this program.
The dungeon executable can be run by itself to generate a new dungeon, or the flags --save and --load may be included to save/load a dungeon file located in /home/<user>/.rlg327/.
The file is saved in a file name "dungeon".

To specify a save or load location the arguments --save-path PATH and --load-path PATH may be used.

Fog-of-war was introduced in this version. The logic for determining this is contained within the file Player.cpp. The player character now has a line of sign equivalent to 3 spaces in all directions.
The map displayed is what the player has seen and is only updated when the space falls within the player's range of vision.

Combat has now been added. Instead of characters dying when another moves into a space occupied by another, the monster who was in the space moves to an empty space.
If the character attempts to move into the player's space, or the player attempts to move into a monster's space, combat takes place and the characters suffer damage to their HP based on the attacker's damage.
The player character starts with 100 HP.

This game implements several keyboard keys for use of controlling the gameplay.
The keys 7,8,9,6,3,2,1,4 and y,k,u,l,n,j,b,h may be used to control moving the player to the cell in the upper left, up, upper right, right, lower right, down, lower left, and left respectively.
Moving up and down stairs may be accomplished by using > or < when standing on the corresponding symbol on the map.
The player may skip his turn by pressing either 5 or the space bar.
Pressing m will display a list of monsters in the dungeon. The up and down arrow keys may be used to navigate through this menu if all monsters are not displayed. The escape key will exit this display.
The game may be exited at anytime using shift+q when a menu is not displayed.

Moving onto an item will add it to the player's inventory.
The following commands may be used to interact with items the player picks up.
To wear an item, press w.  This will display a list of items in the player's inventory and will ask the player for the index of the item to equip.
To take off an item, press t. This will display a list of items equipped to the player and will ask the player for the index of the item to remove.
To drop an item, press d. This will display a list of items in the player's inventory and will ask the player for the index of the item to drop.
To expunge an item from the game, press x. This will display a list of items in the player's inventory and will ask the player for the index of the item to expunge.
To list the player's current inventory, press i.
To list the player's currently equipped items, press e.
To inspect an item, press shift+i. This will display a list of items in the player's inventory and will ask the player for the index of the item to display the description for.
Selections may be exited out of by pressing the escape key.

*This program uses the files descriptions.cpp and descriptions.h with utils.cpp and utils.h for file parsing. This code was provided by Professor Sheaffer and modified slightly to work with the existing code.
The monster and object descriptions are parsed from files located in the user's home directory in the folder .rlg327. The files are monster_desc.txt and object_desc.txt respectively.
Once these files are parsed, they are converted into Monster and Object objects and rendered onto the map.

*This program uses the files dice.cpp and dice.h which were provided by Professor Sheaffer to consturct dice objects.

Contained within this archive is a README, Changelog, Makefile, and the following source files:
character.h
descriptions.cpp
descriptions.h
dice.cpp
dice.h
dungeon.cpp
dungeon.h
generate.cpp
generate.h
heap.cpp
heap.h
macros.h
monster.cpp
monster.h
movement.cpp
movement.h
object.cpp
object.h
pControls.cpp
pControls.h
player.cpp
player.h
routing.cpp
routing.h
save.cpp
save.h
utils.cpp
utils.h

Running make will compile the source files using the C++ compiler into the executable main.  This project is compiled to the C++11 standard.
