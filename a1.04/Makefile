EXES = main
OBJS = dungeon.o generate.o save.o binheap.o routing.o move.o
CFLAGS = -g -Wall -Werror

DEPS = dungeon.h generate.h save.h binheap.h routing.h move.h

main: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	gcc -o $@ -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o
