EXES = main
OBJS = dungeon.o generate.o save.o heap.o routing.o movement.o pControls.o character.o player.o monster.o
CFLAGS = -g -Wall -Werror
LIBS = -lncurses

DEPS = dungeon.h generate.h save.h macros.h heap.h routing.h movement.h pControls.h character.h player.h monster.h

main: $(OBJS)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.c $(DEPS)
	gcc $(CFLAGS) $(LIBS) -c $<

%.o: %.cpp
	g++ $(CFLAGS) -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o
