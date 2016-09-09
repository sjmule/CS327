EXES = main
OBJS = dungeon.o generate.o
CFLAGS = -g -Wall -Werror

DEPS = generate.h

main: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	gcc -o $@ -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o
