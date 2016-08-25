EXES = main
OBJS = langton327.o encode.o
CFLAGS = -g -Wall

DEPS = encode.h

main: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	gcc -o $@ -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o
