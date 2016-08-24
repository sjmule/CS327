EXES = main
OBJS = langton327.o
DEPS = encode.h

main: $(OBJS)
	gcc -o langton327 $^ -g -Wall

%.0: %.c $(DEPS)
	gcc -o $@ -c $<

clean:
	rm -rf *.o
