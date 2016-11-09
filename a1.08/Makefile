EXES = main
OBJS = dungeon.o generate.o save.o heap.o routing.o movement.o pControls.o player.o monster.o fileParser.o dice.o utils.o
CFLAGS = -g -Wall -Werror
LIBS = -lncurses

DEPS = dungeon.h generate.h save.h macros.h heap.h routing.h movement.h pControls.h character.h player.h monster.h fileParser.h dice.h utils.h

main: $(OBJS)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.cpp
	g++ $(CFLAGS) $(LIBS) -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o
