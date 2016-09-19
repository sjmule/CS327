EXES = main
OBJS = dungeon.o generate.o save.o binheap.o
CFLAGS = -g -Wall -Werror

DEPS = generate.h save.h binheap.h

main: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	gcc -o $@ -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o
