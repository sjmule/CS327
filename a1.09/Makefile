EXES = main
OBJS = dungeon.o generate.o save.o heap.o routing.o movement.o pControls.o player.o monster.o descriptions.o dice.o utils.o object.o
CFLAGS = -g -Wall -Werror
LIBS = -lncurses

DEPS = dungeon.h generate.h save.h macros.h heap.h routing.h movement.h pControls.h character.h player.h monster.h descriptions.h dice.h utils.h object.h

main: $(OBJS)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.cpp
	g++ $(CFLAGS) $(LIBS) -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o
