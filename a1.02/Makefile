EXES = main
OBJS = dungeon.o generate.o save.o
CFLAGS = -g -Wall -Werror

DEPS = generate.h save.h

main: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	gcc -o $@ -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o
