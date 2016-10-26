EXES = main
OBJS = dungeon.o generate.o save.o heap.o routing.o movement.o pControls.o
CFLAGS = -g -Wall -Werror
LIBS = -lncurses

DEPS = dungeon.h generate.h save.h macros.h heap.h routing.h movement.h pControls.h

main: $(OBJS)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.c $(DEPS)
	gcc -o $@ -c $< $(LIBS)

clean:
	rm -rf $(EXES)
	rm -rf *.o
