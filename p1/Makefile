all: main clean
CC = gcc
CFLAGS  = -c -Wall -Wshadow -g
DEP = main.o listcreat.o


listcreat.o: listcreat.c listcreat.h
	$(CC) $(CFLAGS) listcreat.c

main: $(DEP)
	$(CC) $(CFLAGS) $@.c
	$(CC) -g -o $@ $^

clean:
	rm -f *.o all