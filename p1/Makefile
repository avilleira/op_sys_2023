CC = gcc
CFLAGS  = -c -Wall -Wshadow -g
DEP = main.o listcreat.o
all: main clean


main: $(DEP)
	$(CC) -g -o $@ $^

%.o: %.c listcreat.h
	$(CC) $(CFLAGS) $<

.PHONY: clean
clean:
	rm -f *.o 